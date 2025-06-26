#ifndef SERVER_HPP
#define SERVER_HPP

#include "ftIrcUtils.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "FootballBot.hpp"
#include <map>
#include <vector>
#include <poll.h>
#include <string>
#include <netinet/in.h>

class Client;
class Channel;

class Server {
public:
    Server(int port, const std::string &password);
    
    ~Server();

    void launch();

    void acceptClient();
    
    void processEvents();
    
    void receiveData(Client &client);
    
    void processClientMessage(Client &client);

    void handleAuthentication(Client &client, const std::vector<std::string> &tokens);
    
    void sendWelcomeMessage(Client &client);
    
    void handlePass(Client &client, const std::vector<std::string> &tokens);
    void handleNick(Client &client, const std::vector<std::string> &tokens);
    void handleUser(Client &client, const std::vector<std::string> &tokens);
    void handleQuit(Client &client);
    void handleJoin(Client &client, const std::vector<std::string> &tokens);
    void handlePart(Client &client, const std::vector<std::string> &tokens);
    void handlePrivmsg(Client &sender, const std::vector<std::string> &tokens);
    void handleKick(Server& server, Client& client, const std::vector<std::string>& tokens);
    void handleTopic(Client &client, const std::vector<std::string> &tokens);
    void handleInvite(Client& client, const std::vector<std::string> &tokens);
    void handleMode(Client& client, const std::vector<std::string>& tokens);
    void handleBot(const std::string& channel, Client& sender, const std::string& command);

    const std::string& getServerName() const;
    
    Channel* getChannelByName(const std::string &name);
    
    Client* getClientByNick(const std::string &nickname);
    
    std::map<std::string, Channel> _channels;

private:
    int _port;
    int _serverSocket;
    std::string _password;
    bool _running;
    std::string _serverName;
    std::vector<pollfd> _pollFds;
    std::map<int, Client> _clients;
    struct sockaddr_in _serverAddr;
    FootballBot _footballBot;
};

#endif