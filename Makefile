CC = cc
SRC = Game_init.c map_checks.c window_events.c solong_utils.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c error_checkers.c Mini_engine.c initialize_game.c
SRC_BONUS = Game_init.c map_checks_bonus.c window_events.c solong_utils.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c error_checkers.c Mini_engine.c initialize_game.c
OBJS_BONUS = $(SRC_BONUS:.c=.o)
OBJS = $(SRC:.c=.o)
RM = rm -f

CFLAGS = -Wall -Wextra -O3
# -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -Ofast
# LDFLAGS = -lmlx -lXext -lX11 -lm
LDFLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -Ofast
LIBFT = libft/libft.a
PRINTF = printf/libftprintf.a
NAME = so_long
NAME_BONUS = so_long_bs

all: $(NAME)

$(PRINTF):
	make -C printf

$(LIBFT): 
	make -C libft

bonus:$(NAME_BONUS)

$(NAME_BONUS):
	$(CC) $(SRC_BONUS) $(LDFLAGS) $(LIBFT) $(PRINTF) -o $(NAME_BONUS)

$(NAME): $(OBJS) $(PRINTF) $(LIBFT)
	$(CC) $(OBJS) $(LDFLAGS) $(LIBFT) $(PRINTF) -o $(NAME)


clean: 
	$(RM)
	make clean -C printf
	make clean -C libft

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)
	make fclean -C printf
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
