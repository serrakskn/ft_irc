#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <vector>

class Client {
	public:
		Client();
		
		Client(int fd);

		int getFd() const;
		
		void appendBuffer(const std::string &data);
		
		bool getLine(std::string &line);
		
		void sendMessage(const std::string &message);
		
		std::string getPrefix() const;

		void setNickname(const std::string &nickname);
		
		void setUsername(const std::string &username);
		
		void setHost(const std::string &host);
		
		void setRegistered(bool status);
		
		void setPass(bool passed);

		const std::string &getNickname() const;
		
		const std::string &getUsername() const;
		
		const std::string &getHost() const;
		
		bool isRegistered() const;
		
		bool hasPassed() const;
		
		const std::string &getBuffer() const;
		
		bool isAuthenticated() const;

		void setIP(const std::string &ip);
		
		void setPort(int port);
		
		std::string getIP() const;
		
		int getPort() const;

		bool operator==(const Client& other) const;

	private:
		int _fd;
		std::string _buffer;
		std::string _nickname;
		std::string _username;
		std::string _host;
		bool _registered;
		bool _pass;

		std::string _ip;
		int _port;
};

#endif // CLIENT_HPP 