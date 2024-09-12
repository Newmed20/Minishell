/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 19:47:07 by abmahfou          #+#    #+#             */
/*   Updated: 2024/09/12 11:02:31 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <stdbool.h>
# include "libft/libft.h"

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

typedef struct s_lst
{
	t_token	*head;
	t_token	*tail;
}	t_lst;

t_token	*skip_spaces(t_token *el, int flg);
int		syntax_error(t_lst *lst);
int		print_error(void);

#endif