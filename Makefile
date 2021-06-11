NAME = sseo_tester

CC = clang++

CFLAGS = -Wall -Wextra -Werror

INCLUDES = -I srcs -I tester_srcs


# FILES
MAIN = main

SRC_DIR = srcs

TESTER_DIR = tester_srcs

OBJ_DIR = objs


# SRCS & OBJS
SRCS = $(addsuffix .cpp, $(MAIN))

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.cpp=.o))

$(NAME): $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS)

$(OBJ_DIR)/%.o: $(TESTER_DIR)/%.cpp
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
