NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g
LDFLAGS = -lreadline -L/Users/abmahfou/.brew/opt/readline/lib
INCLUDES = -I/Users/abmahfou/.brew/opt/readline/include

GREEN=\033[1;32m
YELLOW=\033[1;33m
BLUE=\033[1;34m
NC=\033[0m

HEADER = minishell.h
LXR_HEADER = lexer/lexer.h
LIBFHDR = libft/libft.h

LIBFT = libft/libft.a

SRCS = main.c signals.c \
	   lexer/lexer.c lexer/lexer_utils.c lexer/lexer_utils_2.c  \
	   errors/errors_utils.c errors/syntax_error.c \
	   expander/expander.c expander/env_lst.c \
	   parser/parser.c parser/parser_utils.c parser/check_cmd.c parser/ft_redirection.c parser/ft_heredoc.c parser/parser_extra.c\
	   utils/utils1.c utils/clean_up.c utils/utils2.c utils/utils3.c \
	   builtins/ft_cd.c builtins/ft_echo.c builtins/ft_env.c builtins/ft_pwd.c builtins/ft_export.c builtins/ft_exit.c builtins/ft_unset.c \
	   execution/execution.c execution/heredoc.c execution/pipe.c execution/redirections.c execution/builtins.c \

OBJ_DIR = objs/

OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

$(OBJ_DIR)%.o: %.c $(HEADER) $(LXR_HEADER) $(LIBFHDR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@make -C libft
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)[files compiled]$(NC)"

clean:
	@make clean -C libft
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make fclean -C libft
	@rm -rf $(NAME)
	@echo "$(YELLOW)[files cleaned]$(NC)"

re: fclean all
	@make re -C libft
