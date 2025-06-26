#ifndef FOOTBALL_BOT_HPP
#define FOOTBALL_BOT_HPP

#include <map>
#include <string>

class Client;

class FootballBot {
public:
    FootballBot();
    
    ~FootballBot();

    void initialize();
    
    std::string getFootballerInfo(const std::string& jerseyNumber) const;
    
    bool hasFootballer(const std::string& jerseyNumber) const;

private:
    std::map<std::string, std::string> _legendaryFootballers;
};

#endif