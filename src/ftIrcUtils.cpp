#include "../includes/ftIrcUtils.hpp"
#include "../includes/Server.hpp"
#include "../includes/Client.hpp"
#include <sstream>
#include <vector>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <algorithm>

std::vector<std::string> split(const std::string &s, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(s);
    std::string item;
    
    while (std::getline(ss, item, delimiter)) {
        if (!item.empty())
            tokens.push_back(item);
    }
    return tokens;
}

std::string toUpper(const std::string &str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}
