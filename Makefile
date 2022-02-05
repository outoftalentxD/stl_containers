NAME = app

CC = clang++

CFLAGS = -Wall -Wextra -Werror -std=c++98

SRCS_DIR = ./srcs
HDRS_DIR = .
OBJS_DIR = ./srcs/objs

SRCS = $(wildcard $(addsuffix /*.cpp, $(SRCS_DIR)))
HDRS = $(wildcard $(addsuffix /*.hpp, $(SRCS_DIR)))
OBJS = $(addprefix srcs/objs/, $(notdir $(patsubst %.cpp, %.o, $(SRCS))))

$(OBJS_DIR)/%.o: %.cpp $(HDRS)
	$(CC) $(CFLAGS) -o $@ -c $<
	
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re