/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjadid <mjadid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 19:47:07 by abmahfou          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/09/18 04:45:57 by mjadid           ###   ########.fr       */
=======
/*   Updated: 2024/09/17 12:10:45 by abmahfou         ###   ########.fr       */
>>>>>>> abmahfou
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

#define	PROMPT "minishell <$"

extern int exit_status;

typedef struct	s_list_ t_list_;

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
	t_token	*head;
	t_token	*tail;
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
	t_list_				*input_files; // For input redirection (<)
	t_list_				*oa_files; // For output redirection (>)
	t_list_				*heredoc_delimiters; // For heredoc (<<)
	t_list_				*heredoc_content; // Content of heredoc
	int					pipe_out; // 1 if this command pipes to next, 0 otherwise
	struct s_command	*next; // Pointer to next command in pipeline
}	t_command;

struct s_list_
{
	void	*content;
	int		type;
	struct s_list_	*next;
};

typedef struct	s_data
{
	char		*prompt;
	t_command	*cmd;
	t_env		*env_copy;
	t_tkn_lst	*lex;
}	t_data;

t_token	*skip_spaces(t_token *el, int flg);

/* ------------------- errors ------------------- */

int		syntax_error(t_tkn_lst	*lst);
int		print_error(void);

/* ------------------- lexer ------------------- */

t_tkn_lst	*lexer(char *line);

/* ------------------- utils ------------------- */

char	**ft_strdup_2d(char **_2d);

/* ------------------- expander ------------------- */

t_data		*get_env_cpy(t_data *data, char **env);
t_var_name	*search_name(t_data *data);



void	print_token(t_tkn_lst *lst); // !!!!!!!!!!!!!!!

#endif