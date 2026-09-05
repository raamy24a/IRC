NAME =			ircserv
CC =			c++
CFLAGS =		-Wall -Wextra -Werror -I ./includes -g
CPPFLAGS =		-std=c++98

MKDIR =			mkdir -p
RM =			rm -rf

SRC =			main.cpp Server.cpp Client.cpp Channel.cpp
OBJ =			$(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(addprefix obj/, $(OBJ))
	@$(MKDIR) obj
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(addprefix obj/, $(OBJ)) -o $(NAME)

obj/%.o: src/%.cpp | obj/
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

obj/:
	@$(MKDIR) obj

clean:
	@$(RM) obj/

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re obj 
