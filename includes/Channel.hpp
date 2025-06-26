#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#include <vector>
#include "Client.hpp"  
#include "Server.hpp"

class Server;
class Client;

class Channel {
private:
    std::string _name;
    std::string _topic;
    std::string _key;
    std::vector<Client*> _clients;
    std::vector<std::string> _operators;
    std::vector<std::string> _invitedUsers;
    bool _inviteOnly;
    bool _topicRestrictions;
    int _userLimit;
    bool _hasUserLimit;

public:
    Channel(const std::string &name) : _name(name), _inviteOnly(false), _topicRestrictions(false), _userLimit(0), _hasUserLimit(false) {}
    Channel() : _name(""), _inviteOnly(false), _topicRestrictions(false), _userLimit(0), _hasUserLimit(false) {}

    void addClient(Client &client);
    void removeClient(Client &client);
    
    void channelsMessage(const std::string &message, const Client* sender);
    
    bool hasClient(const Client& client) const;
    
    int getClientCount() const;
    
    void addOperator(const std::string& nickname);
    
    void removeOperator(const std::string& nickname);
    
    bool isOperator(const std::string& nickname) const;
    
    Client* getClientByNickname(const std::string& nickname);
    
    void broadcastMessage(const std::string& message);
    
    const std::string &getName() const;

    const std::vector<Client*>& getClients() const;
    
    std::vector<Client*>& getClients();

    std::string getTopic() const;

    std::vector<std::string> getOperators() const;
    
    void setTopic(const std::string &topic);

    void inviteUser(const std::string& nickname);
    
    bool isInvited(const std::string& nickname) const;
    
    void removeInvite(const std::string& nickname);

    bool isInviteOnly() const { return _inviteOnly; }
    
    void setInviteOnly(bool value) { _inviteOnly = value; }
    
    bool hasTopicRestrictions() const { return _topicRestrictions; }
    
    void setTopicRestrictions(bool value) { _topicRestrictions = value; }
    
    bool hasKey() const { return !_key.empty(); }
    
    std::string getKey() const { return _key; }
    
    void setKey(const std::string& key) { _key = key; }
    
    void removeKey() { _key.clear(); }
    
    bool hasUserLimit() const { return _hasUserLimit; }
    
    int getUserLimit() const { return _userLimit; }
    
    void setUserLimit(int limit) { _userLimit = limit; _hasUserLimit = true; }
    
    void removeUserLimit() { _hasUserLimit = false; }
};

#endif 