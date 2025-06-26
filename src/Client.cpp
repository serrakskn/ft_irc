#include "../includes/Client.hpp"
#include <unistd.h>
#include <cstring>
#include <sstream>
#include <sys/socket.h>
#include <cerrno>

Client::Client() : _fd(-1), _registered(false), _pass(false), _port(-1) {}

Client::Client(int fd) : _fd(fd), _registered(false), _pass(false), _port(-1) {}

int Client::getFd() const {
    return _fd;
}

const std::string &Client::getBuffer() const {
    return _buffer;
}

void Client::appendBuffer(const std::string &data) {
    _buffer.append(data);
}

bool Client::getLine(std::string &line) {
    size_t pos = _buffer.find("\r\n");
    if (pos != std::string::npos) {
        line = _buffer.substr(0, pos);
        _buffer.erase(0, pos + 2);
        return true;
    }
    return false;
}

void Client::sendMessage(const std::string &message) {
    std::string msg = message + "\r\n";
    ssize_t sent = send(_fd, msg.c_str(), msg.size(), 0);
    if (sent < 0) {
        if (errno == EPIPE)
            return;
    }
}

std::string Client::getPrefix() const {
    return _nickname + "!" + _username + "@" + _host;
}


void Client::setNickname(const std::string &nickname) {
    _nickname = nickname;
}

void Client::setUsername(const std::string &username) {
    _username = username;
}


void Client::setHost(const std::string &host) {
    _host = host;
}

void Client::setRegistered(bool status) {
    _registered = status;
}

void Client::setPass(bool passed) {
    _pass = passed;
}

const std::string &Client::getNickname() const {
    return _nickname;
}

const std::string &Client::getUsername() const {
    return _username;
}

const std::string &Client::getHost() const {
    return _host;
}

bool Client::isRegistered() const {
    return _registered;
}

bool Client::hasPassed() const {
    return _pass;
}

bool Client::isAuthenticated() const {
    return hasPassed() && !_nickname.empty() && !_username.empty();
}

bool Client::operator==(const Client& other) const {
    return this->getFd() == other.getFd();
}

void Client::setIP(const std::string &ip) {
	_ip = ip;
}

void Client::setPort(int port) {
	_port = port;
}

std::string Client::getIP() const {
	return _ip;
}

int Client::getPort() const {
	return _port;
}
