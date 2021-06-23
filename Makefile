NAME = ft_container_tester

CC = clang++

CFLAGS = -Wall -Wextra -Werror -std=c++98

INCLUDES = -I containers -I includes


# FILES
MAIN = ft_container_tester

SRC_DIR = srcs

OBJ_DIR = objs


# SRCS & OBJS
SRCS = $(addsuffix .cpp, $(MAIN))

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.cpp=.o))


# MAKE
$(NAME): $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

all: $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
