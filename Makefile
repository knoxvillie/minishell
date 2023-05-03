# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kfaustin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/14 10:58:53 by kfaustin          #+#    #+#              #
#    Updated: 2023/04/14 10:58:55 by kfaustin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name:
NAME	= minishell

# Compiler and flags
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g
EFLAGS	= -lreadline
RM		= rm -rf

# Sources, objects and dir
SRCDIR	= ./src/
SRC		= env_list.c list_handle.c main.c prompt.c utils.c

LEXERDIR= ./src/lexer/
LEXER	= syntax.c

BUILDIR	= ./src/builtins/
UNSET	= unset/unset.c

OBJ		=	$(addprefix $(SRCDIR), $(SRC:.c=.o)) \
			$(addprefix $(BUILDIR), $(UNSET:.c=.o))
			#$(addprefix $(LEXERDIR), $(LEXER:.c=.o))


# Libft
LIBDIR	= ./includes/libft/
LIBAFT	= libft.a

all: $(NAME)

$(NAME): $(OBJ) libft credit
		@$(CC) $(CFLAGS) $(OBJ) $(LIBAFT) $(EFLAGS) -o $(NAME)

libft:
		@make -C $(LIBDIR)
		@cp $(LIBDIR)$(LIBAFT) .

clean:
		@$(RM) $(OBJ)

fclean: clean
		@make -C $(LIBDIR) fclean
		@$(RM) $(LIBAFT)
		@$(RM) $(NAME)

re: fclean all

credit:
		@echo "███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     "
		@echo "████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     "
		@echo "██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     "
		@echo "██║╚██╔╝██║██║██║╚█f█╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     "
		@echo "██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗"
		@echo "╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝"
		@echo ""



