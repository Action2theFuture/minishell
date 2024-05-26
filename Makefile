# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junsan <junsan@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/11 19:03:01 by junsan            #+#    #+#              #
#    Updated: 2024/05/26 10:44:42 by junsan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= minishell
BONUS 	= minishell_bonus

CC		= cc
LIBFT 	= libft/libft.a
IFLAGS 	= -I ./includes/ -I ./libft/includes/

CFLAGS 	= -Wall -Wextra -Werror -g
LINK_OPT = -lreadline
SRC 	= minishell.c init_minishell.c process_input.c tokenize.c tokenize_utils.c

SRC_DIR = ./src/
OBJ_DIR = ./obj/

SRCS = $(addprefix $(SRC_DIR), $(SRC))
OBJS = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

vpath %.c ./src/

$(NAME) : $(LIBFT) $(OBJS)
	$(CC) $(CFALGS) -o $@ $(OBJS) $(LIBFT) $(LINK_OPT)

$(OBJ_DIR)%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(LIBFT): 
	@make -C libft/

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

all: $(NAME)

clean:
	rm -rf $(OBJ_DIR) $(BONUS_OBJ_DIR)

fclean: clean
	@make -C libft/ fclean
	rm -f $(NAME) $(BONUS)

re: fclean all

.PHONY: all clean fclean re bonus
