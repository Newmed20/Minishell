/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 10:35:09 by abmahfou          #+#    #+#             */
/*   Updated: 2024/10/09 21:50:54 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redir	*create_redir(t_token *token, t_data *data)
{
	t_redir	*node;

	node = init_list();
	if (!node)
		return (NULL);
	node->type = token->type;
	token = skip_spaces(token->next, 1);
	if (token->type == WORD)
	{
		if (token->next && token->next->type == ENV)
		{
			token = token->next;
			node->content = ft_expand(data, token);
		}
		node->content = ft_strdup(token->content);
	}
	if (token->type == ENV)
		node->content = ft_expand(data, token);
	node->next = NULL;
	return (node);
}

int	is_redir(t_token *token)
{
	return (token->type == REDIR_IN || token->type == APPEND
		|| token->type == REDIR_OUT || token->type == HERE_DOC);
}

void	handle_redirections_heredoc(t_token **token, t_command *cmd, t_data *data)
{
	if ((*token)->type == REDIR_IN)
		append_to_list(&cmd->input_files, create_redir((*token), data));
	else if ((*token)->type == REDIR_OUT || (*token)->type == APPEND)
		append_to_list(&cmd->oa_files, create_redir((*token), data));
	else if ((*token)->type == HERE_DOC)
		handle_heredoc((*token), cmd, data);
	if ((*token)->next->type == WORD)
		(*token) = (*token)->next;
	else
		(*token) = skip_spaces((*token)->next, 1);
	if ((*token)->next && ((*token)->next->type == D_QUOTE
		|| (*token)->next->type == S_QUOTE))
		cmd->heredoc_delimiters->state = 1;
}
