CC = cc
SRC = Game_init.c map_checks.c window_events.c solong_utils.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c error_checkers.c Mini_engine.c initialize_game.c
OBJS = $(SRC:.c=.o)
RM = rm -f

CFLAGS = -Wall -Wextra
LDFLAGS = -lmlx -lXext -lX11 -lm
LIBFT = libft/libft.a
PRINTF = printf/libftprintf.a
NAME = so_long

all: $(NAME)

$(PRINTF):
	make -C printf

$(LIBFT): 
	make -C libft

$(NAME): $(OBJS) $(PRINTF) $(LIBFT)
	$(CC) $(OBJS) $(LDFLAGS) $(LIBFT) $(PRINTF) -o $(NAME)

clean: 
	$(RM) $(OBJS)
	make clean -C printf
	make clean -C libft

fclean: clean
	$(RM) $(NAME)
	make fclean -C printf
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
