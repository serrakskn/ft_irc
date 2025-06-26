#include "../includes/Server.hpp"
#include "../includes/Channel.hpp"
#include "../includes/Client.hpp"
#include "../includes/irc_numerics.hpp"
#include <iostream>
#include <map>

void Server::handleInvite(Client& client, const std::vector<std::string>& tokens) {

    if (tokens.size() < 3) {
        client.sendMessage(":" + _serverName + " " + ERR_NEEDMOREPARAMS(client.getNickname(), "INVITE"));
        return;
    }

    const std::string& nickname = tokens[1];
    const std::string& channelName = tokens[2];


    Channel* channel = getChannelByName(channelName);
    if (channel == NULL) {
        client.sendMessage(":" + _serverName + " " + ERR_NOSUCHCHANNEL(client.getNickname(), channelName));
        return;
    }


    if (!channel->hasClient(client)) {
        client.sendMessage(":" + _serverName + " " + ERR_NOTONCHANNEL(client.getNickname(), channelName));
        return;
    }


    if (channel->isInviteOnly() && !channel->isOperator(client.getNickname())) {
        client.sendMessage(":" + _serverName + " " + ERR_CHANOPRIVSNEEDED(client.getNickname(), channelName));
        return;
    }


    Client* invitedClient = getClientByNick(nickname);
    if (invitedClient == NULL) {
        client.sendMessage(":" + _serverName + " " + ERR_NOSUCHNICK(client.getNickname(), nickname));
        return;
    }


    if (channel->hasClient(*invitedClient)) {
        client.sendMessage(":" + _serverName + " " + ERR_USERONCHANNEL(client.getNickname(), nickname, channelName));
        return;
    }


    channel->inviteUser(nickname);


    std::string inviteMessage = RPL_INVITE(client.getNickname(), client.getUsername(), client.getHost(), nickname, channelName);
    invitedClient->sendMessage(inviteMessage);


    client.sendMessage(":" + _serverName + " " + RPL_INVITING(client.getNickname(), nickname, channelName));
}

