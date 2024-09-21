NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address
LDFLAGS = -lreadline -L/Users/abmahfou/.brew/opt/readline/lib
INCLUDES = -I/Users/abmahfou/.brew/opt/readline/include

HEADER = minishell.h
LIBFHDR = libft/libft.h

SRCS = main.c \
	   lexer/lexer.c lexer/lexer_utils.c lexer/lexer_utils_2.c lexer/print_tokens.c \
	   errors/errors_utils.c errors/syntax_error.c errors/input_errors.c \
	   expander/expander.c expander/env_lst.c expander/expander_utils.c \
	   parser/parser.c \
	   utils/utils1.c
OBJS = $(SRCS:.c=.o)

%.o: %.c $(HEADER) $(LIBFHDR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) libft/libft.a -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
