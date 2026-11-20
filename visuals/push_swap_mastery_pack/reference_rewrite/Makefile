# No-libft reference core: a teaching implementation that mirrors the real
# project's architecture with only standard C. Advanced strategies are
# documented in src/sorting/chunk_stub.c and src/sorting/turk_stub.c.

CC      := cc
CFLAGS  := -Wall -Wextra -Werror -Iinclude

SRCS    := src/core/main.c \
           src/stack/stack.c \
           src/operations/ops.c \
           src/parsing/parse.c \
           src/sorting/sort.c

OBJS    := $(SRCS:.c=.o)
NAME    := psw_core

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
