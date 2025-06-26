#include "includes/ftIrcUtils.hpp"
#include "includes/Server.hpp"
#include "includes/Client.hpp"
#include "includes/Channel.hpp"
#include <cstdlib>
#include <iostream>
#include <csignal>

void handleSigint(int signum)
{
    if(signum)
        std::cerr << ": exit " << std::endl;
}

int main(int argc, char** argv) {
    signal(SIGPIPE, SIG_IGN);
    signal(SIGINT, handleSigint);
    signal(SIGTERM, handleSigint);

    if (argc != 3) {
        std::cerr << "Kullanım: ./ircserv <port> <password>" << std::endl;
        return 1;
    }

    int port = std::atoi(argv[1]);
    std::string password(argv[2]);

    try {
        Server server(port, password);
        std::cout << "FT_IRC Sunucusu başlatıldı. Port: " << port << std::endl;
        std::cout << "Bağlantılar bekleniyor..." << std::endl;
        server.launch();
    } catch (const std::exception &e) {
        std::cerr << "HATA: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
