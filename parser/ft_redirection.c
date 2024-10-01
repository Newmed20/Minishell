/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 10:35:09 by abmahfou          #+#    #+#             */
/*   Updated: 2024/10/01 10:35:57 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redir	*create_redir(t_token *token)
{
	t_redir	*node;

	node = init_list();
	if (!node)
		return (NULL);
	if (token->next->type == WHITE_SPACE)
		node->content = ft_strdup(token->next->next->content);
	else if (token->next->type == WORD)
		node->content = ft_strdup(token->next->content);
	if (!node->content)
		return (NULL);
	node->type = token->type;
	node->next = NULL;
	return (node);
}

int	is_redir(t_token *token)
{
	return (token->type == REDIR_IN || token->type == DREDIR_OUT
		|| token->type == REDIR_OUT || token->type == HERE_DOC);
}

void	handle_redirections_heredoc(t_token *token, t_command *cmd)
{
	if (token->type == REDIR_IN)
		append_to_list(&cmd->input_files, create_redir(token));
	else if (token->type == REDIR_OUT || token->type == DREDIR_OUT)
		append_to_list(&cmd->oa_files, create_redir(token));
	else if (token->type == HERE_DOC)
		handle_heredoc(token, cmd);
}
