#include "../includes/Server.hpp"
#include "../includes/Channel.hpp"
#include "../includes/Client.hpp"
#include "../includes/irc_numerics.hpp"
#include "../includes/ftIrcUtils.hpp"
#include "../includes/FootballBot.hpp"
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <poll.h>
#include <cerrno>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sstream>

Server::Server(int port, const std::string &password)
    : _port(port), _password(password), _running(true), _serverName("ft_irc")
{
    _serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (_serverSocket < 0)
        throw std::runtime_error("Socket creation failed");

    int opt = 1;
    if (setsockopt(_serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        close(_serverSocket);
        throw std::runtime_error("setsockopt failed");
    }

    if (fcntl(_serverSocket, F_SETFL, O_NONBLOCK) < 0) {
        close(_serverSocket);
        throw std::runtime_error("Soket non-blocking moduna ayarlanamadı");
    }

    _serverAddr.sin_family = AF_INET;
    _serverAddr.sin_addr.s_addr = INADDR_ANY;
    _serverAddr.sin_port = htons(_port);

    if (bind(_serverSocket, (struct sockaddr *)&_serverAddr, sizeof(_serverAddr)) < 0) {
        close(_serverSocket);
        std::stringstream ss;
        ss << "Soket " << _port << " portuna bağlanamadı";
        throw std::runtime_error(ss.str());
    }

    if (listen(_serverSocket, 2) < 0) {
        close(_serverSocket);
        throw std::runtime_error("Soket dinleme moduna alınamadı");
    }

    pollfd pfd;
    pfd.fd = _serverSocket;
    pfd.events = POLLIN;
    pfd.revents = 0;
    _pollFds.push_back(pfd);

    std::cout << "Server listening on port " << _port << std::endl;
}


Server::~Server() {
    for (size_t i = 0; i < _pollFds.size(); ++i) {
        close(_pollFds[i].fd);
    }
    std::cout << "Server shutting down." << std::endl;
}


void Server::launch() {
    while (_running) {
        int ret = poll(&_pollFds[0], _pollFds.size(), -1);
        if (ret < 0)
            throw std::runtime_error("poll error");


        if (_pollFds[0].revents & POLLIN)
            acceptClient();


        processEvents();
    }
}


void Server::acceptClient() {
    struct sockaddr_in clientAddr;
    socklen_t addrLen = sizeof(clientAddr);
    int clientFd = accept(_serverSocket, (struct sockaddr *)&clientAddr, &addrLen);
    if (clientFd < 0) {
        if (errno != EAGAIN && errno != EWOULDBLOCK) {
            std::cerr << "İstemci kabul hatası: " << strerror(errno) << std::endl;
        }
        return;
    }


    if (fcntl(clientFd, F_SETFL, O_NONBLOCK) < 0) {
        close(clientFd);
        std::cerr << "İstemci soketi non-blocking moduna ayarlanamadı" << std::endl;
        return;
    }


    Client client(clientFd);


    char ipStr[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(clientAddr.sin_addr), ipStr, INET_ADDRSTRLEN);
    int port = ntohs(clientAddr.sin_port);

    client.setIP(ipStr);
    client.setPort(port);
    client.setHost(ipStr);


    _clients[clientFd] = client;


    _clients[clientFd].sendMessage("You are connected to ft_irc.");


    pollfd pfd;
    pfd.fd = clientFd;
    pfd.events = POLLIN;
    pfd.revents = 0;
    _pollFds.push_back(pfd);

    std::cout << "New client connected: FD " << clientFd << std::endl;
}


void Server::processEvents() {

    for (size_t i = 1; i < _pollFds.size(); ++i) 
    {
        if (_pollFds[i].revents & POLLIN) {
            int fd = _pollFds[i].fd;
            if (_clients.find(fd) == _clients.end())
                continue;
            receiveData(_clients[fd]);
            processClientMessage(_clients[fd]);
        } else if (_pollFds[i].revents & (POLLHUP | POLLERR)) {
            if (_pollFds[i].fd != _serverSocket) {
                Client &client = _clients[_pollFds[i].fd];
                handleQuit(client);
            }
        }
    }
}


void Server::receiveData(Client &client) {
    char buf[1024];
    std::memset(buf, 0, sizeof(buf));
    int bytes = recv(client.getFd(), buf, sizeof(buf) - 1, 0);
    if (bytes <= 0) {

        handleQuit(client);
        return;
    }
    client.appendBuffer(std::string(buf, bytes));
}


void Server::processClientMessage(Client &client) {
    std::string line;
    

    while (client.getLine(line)) {
        if (line.empty())
            continue;
            

        std::vector<std::string> tokens = split(line, ' ');
        if (tokens.empty())
            continue;
            

        std::string command = toUpper(tokens[0]);
        

        if (!client.isAuthenticated()) {
            handleAuthentication(client, tokens);
        } 
        else if (command == "QUIT") {
            handleQuit(client);
            break;
        } else if (command == "JOIN") {
            handleJoin(client, tokens);
        } else if (command == "PART") {
            handlePart(client, tokens);
        } else if (command == "PRIVMSG") {
            handlePrivmsg(client, tokens);
        } else if (command == "KICK") {
            handleKick(*this, client, tokens);
        } else if (command == "TOPIC") {
            handleTopic(client, tokens);
        } else if (command == "INVITE") {
            handleInvite(client, tokens);
        } else if (command == "MODE") {
            handleMode(client, tokens);
        } else if (command == "NICK") {
            handleNick(client, tokens);
        } else if (command == "USER") {
            handleUser(client, tokens);
        } else if (command == "PASS") {
            handlePass(client, tokens);
        } else if (command == "BOT") {
            handleBot("", client, tokens[1]);
        } else {

            client.sendMessage(":" + _serverName + " " + ERR_UNKNOWNCOMMAND(client.getNickname(), command));
        }
    }
}


void Server::handleAuthentication(Client &client, const std::vector<std::string> &tokens) {

    std::string command = toUpper(tokens[0]);

    if (command == "PASS") {
        handlePass(client, tokens);
        return;
    } else if (command == "NICK") {
        handleNick(client, tokens);
    } else if (command == "USER") {
        handleUser(client, tokens);
    }

    else {
        client.sendMessage("ERROR: You must authenticate using PASS, NICK and USER.");
    }
    if (client.isAuthenticated()) {
        client.setRegistered(true);
        sendWelcomeMessage(client);

        std::cout << "New user connected: " 
        << "NICK: " << client.getNickname() 
        << ", USER: " << client.getUsername() 
        << ", IP: " << client.getIP()
        << std::endl;
    }
}

void Server::sendWelcomeMessage(Client &client) {
    client.sendMessage(RPL_WELCOME(_serverName, client.getNickname()));
    client.sendMessage(RPL_YOURHOST(_serverName, client.getNickname()));
    client.sendMessage(RPL_CREATED(_serverName, client.getNickname()));
    client.sendMessage(RPL_MYINFO(_serverName, client.getNickname()));
}

const std::string& Server::getServerName() const {
    return _serverName;
}

Channel* Server::getChannelByName(const std::string &name) {
    std::map<std::string, Channel>::iterator it = _channels.find(name);
    if (it != _channels.end()) {
        return &(it->second);
    }
    return NULL;
}

Client* Server::getClientByNick(const std::string &nickname) {
    for (std::map<int, Client>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
        if (it->second.getNickname() == nickname) {
            return &(it->second);
        }
    }
    return NULL;
}


