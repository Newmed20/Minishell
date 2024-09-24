/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 19:47:07 by abmahfou          #+#    #+#             */
/*   Updated: 2024/09/24 14:52:37 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include "libft/libft.h"

#define PROMPT "\033[1;31m$ \033[0m"
#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

extern int exit_status;

typedef struct	s_redir t_redir;

enum e_state
{
	IN_SQUOTE,
	IN_DQUOTE,
	GENERAL
};

enum e_type
{
	WORD,
	WHITE_SPACE,
	S_QUOTE,
	D_QUOTE,
	PIPE_LINE,
	NEW_LINE,
	ESCAPE,
	ENV,
	REDIR_IN,
	REDIR_OUT,
	DREDIR_OUT,
	HERE_DOC
};

typedef struct s_token
{
	char			*content;
	int				len;
	enum e_type		type;
	enum e_state	state;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_tkn_lst
{
	t_token	*tokens;
}	t_tkn_lst;

typedef struct	s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct	s_var_name
{
	char	*name;
	char	*value;
	char	*after;
	int		pos;
	int		start;
	int		end;
}	t_var_name;

typedef struct	s_command
{
	char				*command; // The command name (e.g., "echo", "ls")
	char				*full_path; // The full path to the command (e.g., "/bin/echo", "/bin
	char				**args; // Array of arguments including the command
	int					arg_count; // Number of arguments
	t_redir				*input_files; // For input redirection (<)
	t_redir				*oa_files; // For output redirection (>)
	t_redir				*heredoc_delimiters; // For heredoc (<<)
	t_redir				*heredoc_content; // Content of heredoc
	bool				cmd_found; // if found a command
	int					pipe_out; // 1 if this command pipes to next, 0 otherwise
	struct s_command	*next; // Pointer to next command in pipeline
}	t_command;

struct s_redir
{
	void			*content;
	int				type;
	struct s_redir	*next;
};

typedef struct	s_data
{
	char		*prompt;
	t_command	*cmd;
	t_env		*env_copy;
	t_tkn_lst	*lexer;
}	t_data;

t_token	*skip_spaces(t_token *el, int flg);

/* ------------------- errors ------------------- */

int		syntax_error(t_tkn_lst	*lst);
int		print_error(int errror);

/* ------------------- lexer ------------------- */

t_tkn_lst *lexer(char *line);

/* ------------------- utils ------------------- */

char	**ft_strdup_2d(char **_2d);
void	free_2d(char **str, int n);
void	free_split(char **arr);

/* ------------------- expander ------------------- */

t_data 		*get_env_cpy(t_data *data, char **env);
t_var_name	*ft_expand(t_data *data);
char		*get_digit(char c, int pos, t_var_name *name, t_data *data);
char		*get_var_value(t_env *env, char *key);
char		*get_after(char *str, t_var_name *var_name);
char		*get_full(char *prompt, t_var_name *var);

void	ft_parser(t_data *data);
int		ft_is_command(t_data *data, char *cmd);

void	print_token(t_tkn_lst *lst); // !!!!!!!!!!!!!!!

#endif