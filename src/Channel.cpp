#include "../includes/Channel.hpp"
#include "../includes/Server.hpp"
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>


void Channel::addClient(Client &client) {

    for (std::vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
        if ((*it)->getFd() == client.getFd()) {
            return;
        }
    }

    _clients.push_back(&client);
    

    removeInvite(client.getNickname());
}


void Channel::removeClient(Client &client) {

    for (std::vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
        if ((*it)->getFd() == client.getFd()) {
            _clients.erase(it);
            break;
        }
    }


    std::string nick = client.getNickname();
    for (std::vector<std::string>::iterator it = _operators.begin(); it != _operators.end(); ++it) {
        if (*it == nick) {
            _operators.erase(it);
            break;
        }
    }
}



void Channel::channelsMessage(const std::string& message, const Client* sender) {
    for (std::vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
        if (!sender || *it != sender) {
            (*it)->sendMessage(message);
        }
    }
}


bool Channel::hasClient(const Client& client) const {
    for (std::vector<Client*>::const_iterator it = _clients.begin(); it != _clients.end(); ++it) {
        if ((*it)->getFd() == client.getFd()) {
            return true;
        }
    }
    return false;
}


int Channel::getClientCount() const {
    return _clients.size();
}


void Channel::addOperator(const std::string& nickname) {
    if (std::find(_operators.begin(), _operators.end(), nickname) == _operators.end()) {
        _operators.push_back(nickname);
    }
}


void Channel::removeOperator(const std::string& nickname) {
    std::vector<std::string>::iterator it = std::find(_operators.begin(), _operators.end(), nickname);
    if (it != _operators.end()) {
        _operators.erase(it);
    }
}


bool Channel::isOperator(const std::string& nickname) const {
    return std::find(_operators.begin(), _operators.end(), nickname) != _operators.end();
}


const std::string &Channel::getName() const {
    return _name;
}


std::vector<Client*>& Channel::getClients() {
    return _clients;
}


Client* Channel::getClientByNickname(const std::string& nickname) {
    for (std::vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
        if ((*it)->getNickname() == nickname) {
            return *it;
        }
    }
    return NULL;
}


std::string Channel::getTopic() const {
    return _topic;
}

std::vector<std::string> Channel::getOperators() const {
    return _operators;
}


void Channel::setTopic(const std::string &topic) {
    _topic = topic;
}


void Channel::broadcastMessage(const std::string& message) {
    for (std::vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
        (*it)->sendMessage(message);
    }
}


void Channel::inviteUser(const std::string& nickname) {
    if (std::find(_invitedUsers.begin(), _invitedUsers.end(), nickname) == _invitedUsers.end()) {
        _invitedUsers.push_back(nickname);
    }
}


bool Channel::isInvited(const std::string& nickname) const {
    return std::find(_invitedUsers.begin(), _invitedUsers.end(), nickname) != _invitedUsers.end();
}


void Channel::removeInvite(const std::string& nickname) {
    std::vector<std::string>::iterator it = std::find(_invitedUsers.begin(), _invitedUsers.end(), nickname);
    if (it != _invitedUsers.end()) {
        _invitedUsers.erase(it);
    }
}


const std::vector<Client*>& Channel::getClients() const {
    return _clients;
}

