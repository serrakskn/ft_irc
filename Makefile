NAME = ircserv
SRC = main.cpp \
	src/Server.cpp \
	src/Client.cpp \
	src/Channel.cpp \
	src/ftIrcUtils.cpp \
	src/FootballBot.cpp \
	commands/join.cpp \
	commands/quit.cpp \
	commands/priveMessage.cpp \
	commands/part.cpp \
	commands/kick.cpp \
	commands/invite.cpp \
	commands/nick.cpp \
	commands/pass.cpp \
	commands/user.cpp \
	commands/topic.cpp \
	commands/mode.cpp

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
INCLUDES = -I./
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.cpp=.o))

# Gerekli klasörleri oluşturacak kurallar
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ)
	@echo "$(NAME) başarıyla derlendi!"

clean:
	rm -rf $(OBJ_DIR)
	@echo "Obje dosyaları temizlendi."

fclean: clean
	rm -f $(NAME)
	@echo "Çalıştırılabilir dosya temizlendi."

re: fclean all

# Klasör oluşturacak kural
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/commands
	mkdir -p $(OBJ_DIR)/src

.PHONY: all clean fclean re
