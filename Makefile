CC      = cc
CFLAGS  = -Wall -Wextra -Werror -D BUFFER_SIZE=42
RM      = rm -f

NAME    = get_next_line.a

SRC     = get_next_line.c get_next_line_utils.c

OBJS    = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c get_next_line.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
