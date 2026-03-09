# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acohaut <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/19 15:02:18 by acohaut           #+#    #+#              #
#    Updated: 2026/03/09 10:45:08 by acohaut          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
NAME		= minishell
INCLUDES	= -I./includes -I./libft

LIBFT		= libft/libft.a

SRCS		= 	srcs/main.c \
			srcs/inputs/get_inputs.c \
			srcs/inputs/tokenizer_inputs.c \
			srcs/inputs/parser_inputs.c \
			srcs/inputs/utils_token.c \
			srcs/inputs/list_token.c \
			srcs/inputs/list_cmd.c \
			srcs/inputs/redirection.c \
			srcs/inputs/heredoc.c \
			srcs/inputs/expander.c \
			srcs/inputs/utils_expander.c \
			srcs/utilities/utils_minishell.c \
			srcs/utilities/errors.c \
			srcs/utilities/errors_exec.c \
			srcs/utilities/free.c \
			srcs/exec_cmds/execute_cmds.c \
			srcs/exec_cmds/exec_for_pipes.c \
			srcs/exec_cmds/redirection_for_exec.c \
			srcs/exec_cmds/utils_exec_cmds.c \
			srcs/signal/signal_minishell.c \
			srcs/signal/signal_heredoc.c \
			srcs/built_in/exit.c \
			srcs/built_in/echo.c \
			srcs/built_in/cd.c \
			srcs/built_in/env.c \
			srcs/built_in/utils_env.c \
			srcs/built_in/export.c \
			srcs/built_in/utils_export.c \
			srcs/built_in/unset.c \
			srcs/built_in/utils_built_in.c \
			srcs/built_in/pwd.c \
			srcs/built_in/utils_env_empty.c \

OBJS		= $(SRCS:srcs/%.c=objs/%.o)

all:		$(NAME)

$(LIBFT):
		@make -s -C libft

objs/%.o:	srcs/%.c
		@mkdir -p $(@D)
		@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME):	$(LIBFT) $(OBJS)
		@echo "                 ███              ███          █████               ████  ████ "
		@echo "                ░░░              ░░░          ░░███               ░░███ ░░███ "
		@echo "█████████████   ████  ████████   ████   █████  ░███████    ██████  ░███  ░███ "
		@echo "░███░░███░░███ ░░███ ░░███░░███ ░░███  ███░░   ░███░░███  ███░░███ ░███  ░███ "
		@echo "░███ ░███ ░███  ░███  ░███ ░███  ░███ ░░█████  ░███ ░███ ░███████  ░███  ░███ "
		@echo "░███ ░███ ░███  ░███  ░███ ░███  ░███  ░░░░███ ░███ ░███ ░███░░░   ░███  ░███ "
		@echo "█████░███ █████ █████ ████ █████ █████ ██████  ████ █████░░██████  █████ █████"
		@echo "░░░░░ ░░░ ░░░░░ ░░░░░ ░░░░ ░░░░░ ░░░░░ ░░░░░░  ░░░░ ░░░░░  ░░░░░░  ░░░░░ ░░░░░"
		@printf "\n"
		@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

clean:
		@rm -rf objs/
		@make clean -s -C libft  
		@echo "Object files removed."

fclean:		clean
		@rm -f $(NAME) 
		@make fclean -s -C libft  
		@echo "Executable removed."

re:		fclean all  

.PHONY:		all clean fclean re bonus
