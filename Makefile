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
SRC		= env_list.c list_handle.c main.c prompt.c utils.c create_pipe.c

PARSERDIR= ./src/parser/
PARSER	= parser.c parser_utils.c

EXECDIR	= ./src/executer/
EXEC	= access.c executer.c

BUILDIR	= ./src/builtins/
BUILT	=	$(BUILDIR)env/env.c \
 			$(BUILDIR)export/export.c \
 			$(BUILDIR)unset/unset.c \
 			$(BUILDIR)pwd/pwd.c \
 			$(BUILDIR)cd/cd.c \
 			$(BUILDIR)exit/exit.c \
 			$(BUILDIR)echo/echo.c

OBJ		=	$(addprefix $(SRCDIR), $(SRC:.c=.o)) \
			$(addprefix $(EXECDIR), $(EXEC:.c=.o)) \
			$(addprefix $(PARSERDIR), $(PARSER:.c=.o)) \
			$(BUILT:.c=.o)


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



