/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:07:54 by abmahfou          #+#    #+#             */
/*   Updated: 2024/09/12 10:39:44 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*_unclosed_quotes(t_token **elem, enum e_type type)
{
	while (*elem)
	{
		*elem = (*elem)->next;
		if (!*elem || (*elem)->type == type)
			break ;
	}
	if (!*elem)
		write(2, "syntax error !\n", 15);
	return (*elem);
}

int	_redir_error(t_token *elem)
{
	t_token	*redir;

	redir = skip_spaces(elem->next, 1);
	if (!redir || (redir->type != WORD && redir->type != ENV))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	_pipe_error(t_token *elem)
{
	t_token	*next;
	t_token	*prev;

	next = skip_spaces(elem->next, 1);
	prev = skip_spaces(elem->prev, 0);
	if ((!next || !prev)
		|| (next->type == PIPE_LINE || prev->type == PIPE_LINE))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	syntax_error(t_tkn_lst *lst)
{
	t_token	*token;

	token = lst->head;
	while (token)
	{
		if (token->type == REDIR_IN || token->type == DREDIR_OUT 
			|| token->type == REDIR_OUT || token->type == HERE_DOC)
		{
			if (_redir_error(token))
				return (print_error());
		}
		else if (token->type == PIPE_LINE)
		{
			if (_pipe_error(token))
				return (print_error());
		}
		else if (token->type == S_QUOTE || token->type == D_QUOTE)
		{
			if (!_unclosed_quotes(&token, token->type))
				return (EXIT_FAILURE);
		}
		token = token->next;
	}
	return (EXIT_SUCCESS);
}
