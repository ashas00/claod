NAME	= codexion

CFLAGS	= -Wall -Wextra -Werror -pthread
SRCS	= codexion.c parser.c parse_coders.c create.c logs.c dongl.c monitor.c
OBJS	= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c codexion.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re