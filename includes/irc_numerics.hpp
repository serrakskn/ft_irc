#ifndef IRC_NUMERICS_HPP
#define IRC_NUMERICS_HPP

#include <string>

#define RPL_WELCOME(serverName, nick) ":" + serverName + " 001 " + nick + " :Welcome to the IRC network, " + nick
#define RPL_YOURHOST(serverName, nick) ":" + serverName + " 002 " + nick + " :Your host is " + serverName + ", running version 1.0"
#define RPL_CREATED(serverName, nick) ":" + serverName + " 003 " + nick + " :This server was created today"
#define RPL_MYINFO(serverName, nick) ":" + serverName + " 004 " + nick + " " + serverName + " 1.0 o o"

#define RPL_UMODEIS(nick, mode) "221 " + nick + " " + mode
#define RPL_TOPIC(nick, channel, topic) "332 " + nick + " " + channel + " :" + topic
#define RPL_NOTOPIC(nick, channel) "331 " + nick + " " + channel + " :No topic is set for this channel."
#define RPL_TOPICWHOTIME(nick, channel, setby, timestamp) "333 " + nick + " " + channel + " " + setby + " " + std::to_string(timestamp)
#define RPL_NAMREPLY(nick, symbol, channel, users) "353 " + nick + " " + symbol + " " + channel + " :" + users
#define RPL_ENDOFNAMES(nick, channel) "366 " + nick + " " + channel + " :End of /NAMES list"
#define RPL_CHANNELMODEIS(nick, channel, mode, params) "324 " + nick + " " + channel + " " + mode + " " + params
#define RPL_INVITING(nick, target, channel) "341 " + nick + " " + target + " " + channel

#define ERR_NOSUCHNICK(nick, target) "401 " + nick + " " + target + " :No such nick/channel"
#define ERR_NOSUCHSERVER(nick, server) "402 " + nick + " " + server + " :No such server"
#define ERR_NOSUCHCHANNEL(nick, channel) "403 " + nick + " " + channel + " :No such channel"
#define ERR_CANNOTSENDTOCHAN(nick, channel) "404 " + nick + " " + channel + " :Cannot send to channel"
#define ERR_UNKNOWNCOMMAND(nick, command) "421 " + nick + " " + command + " :Unknown command"
#define ERR_NOMOTD(nick) "422 " + nick + " :MOTD file not found"
#define ERR_NONICKNAMEGIVEN(nick) "431 " + nick + " :No nickname given"
#define ERR_ERRONEUSNICKNAME(nick, badnick) "432 " + nick + " " + badnick + " :Erroneous nickname"
#define ERR_NICKNAMEINUSE(nick, newnick) "433 " + nick + " " + newnick + " :Nickname is already in use"
#define ERR_USERNOTINCHANNEL(nick, target, channel) "441 " + nick + " " + target + " " + channel + " :They aren't on that channel"
#define ERR_NOTONCHANNEL(nick, channel) "442 " + nick + " " + channel + " :You're not on that channel"
#define ERR_USERONCHANNEL(nick, target, channel) "443 " + nick + " " + target + " " + channel + " :User is already on channel"
#define ERR_NEEDMOREPARAMS(nick, command) "461 " + nick + " " + command + " :Not enough parameters"
#define ERR_ALREADYREGISTERED(nick) "462 " + nick + " :You may not reregister"
#define ERR_PASSWDMISMATCH(nick) "464 " + nick + " :Password incorrect"

#define ERR_CHANNELISFULL(nick, channel) "471 " + nick + " " + channel + " :Cannot join channel (+l)"
#define ERR_UNKNOWNMODE(nick, mode) "472 " + nick + " " + mode + " :Unknown mode character"
#define ERR_INVITEONLYCHAN(nick, channel) "473 " + nick + " " + channel + " :Cannot join channel (+i)"
#define ERR_BANNEDFROMCHAN(nick, channel) "474 " + nick + " " + channel + " :Cannot join channel (+b)"
#define ERR_BADCHANNELKEY(nick, channel) "475 " + nick + " " + channel + " :Cannot join channel (+k)"
#define ERR_BADCHANMASK(channel) "476 " + channel + " :Invalid channel name"
#define ERR_NOPRIVILEGES(nick) "481 " + nick + " :Permission Denied- You're not an IRC operator"
#define ERR_CHANOPRIVSNEEDED(nick, channel) "482 " + nick + " " + channel + " :You're not channel operator"

#define RPL_JOIN(nick, user, host, channel) ":" + nick + "!" + user + "@" + host + " JOIN :" + channel
#define RPL_PART(nick, user, host, channel, reason) ":" + nick + "!" + user + "@" + host + " PART " + channel + (reason.empty() ? "" : " :" + reason)
#define RPL_PRIVMSG(nick, user, host, target, message) ":" + nick + "!" + user + "@" + host + " PRIVMSG " + target + " :" + message
#define RPL_NOTICE(nick, user, host, target, message) ":" + nick + "!" + user + "@" + host + " NOTICE " + target + " :" + message
#define RPL_MODE_PARAMS(nick, user, host, channel, modes, params) ":" + nick + "!" + user + "@" + host + " MODE " + channel + " " + modes + " " + params
#define RPL_MODE_NO_PARAMS(nick, user, host, channel, modes) ":" + nick + "!" + user + "@" + host + " MODE " + channel + " " + modes
#define RPL_KICK(nick, user, host, channel, target, reason) ":" + nick + "!" + user + "@" + host + " KICK " + channel + " " + target + " :" + reason
#define RPL_QUIT(nick, user, host, reason) ":" + nick + "!" + user + "@" + host + " QUIT :" + reason
#define RPL_INVITE(nick, user, host, target, channel) ":" + nick + "!" + user + "@" + host + " INVITE " + target + " :" + channel

#endif