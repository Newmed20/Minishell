/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 10:35:09 by abmahfou          #+#    #+#             */
/*   Updated: 2024/10/16 11:26:41 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_redir(t_token *token)
{
	return (token->type == REDIR_IN || token->type == APPEND
		|| token->type == REDIR_OUT || token->type == HERE_DOC);
}

t_redir	*create_redir(t_token **token, t_data *data)
{
	t_redir	*node;
	char	*tmp;
	char	*file;

	file = NULL;
	tmp = NULL;
	node = init_list();
	if (!node)
		return (NULL);
	node->type = (*token)->type;
	*token = skip_spaces((*token)->next, 1);
	while ((*token))
	{
		if (((*token)->type == WHITE_SPACE && (*token)->state == GENERAL)
			|| (is_redir(*token) && (*token)->state == GENERAL)
			|| ((*token)->type == PIPE_LINE && (*token)->state == GENERAL))
			break;
		if ((*token)->type == ENV && (*token)->state != IN_SQUOTE)
			tmp = ft_expand(data, (*token));
		else if ((*token)->type != S_QUOTE && (*token)->type != D_QUOTE)
			tmp = ft_strdup((*token)->content);
		else if ((*token)->state == IN_DQUOTE || (*token)->state == IN_SQUOTE)
			tmp = ft_strdup((*token)->content);
		file = ft_strjoin(file, tmp);
		if (tmp)
		{
			free(tmp);
			tmp = NULL;
		}
		(*token) = (*token)->next;
	}
	node->content = ft_strdup(file);
	node->next = NULL;
	return (node);
}

void	handle_redirections_heredoc(t_token **token, t_command *cmd, t_data *data)
{
	if ((*token)->type == REDIR_IN)
		append_to_list(&cmd->input_files, create_redir(token, data));
	else if ((*token)->type == REDIR_OUT || (*token)->type == APPEND)
		append_to_list(&cmd->oa_files, create_redir(token, data));
	else if ((*token)->type == HERE_DOC)
		handle_heredoc(token, cmd, data);
	// (*token) = skip_spaces((*token)->next, 1);
	// if ((*token)->next && (*token)->type == WORD)
	// 	*token = (*token)->next;
	// if ((*token)->next && (*token)->type == ENV)
	// 	*token = (*token)->next;
	// if ((*token)->next && ((*token)->next->type == D_QUOTE
	// 	|| (*token)->next->type == S_QUOTE))
	// 	cmd->heredoc_delimiters->state = 1;
}
