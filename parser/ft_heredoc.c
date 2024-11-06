/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 19:52:33 by abmahfou          #+#    #+#             */
/*   Updated: 2024/11/05 12:22:23 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_heredoc(t_token **token, char **redir, char **file)
{
	char	*tmp;

	tmp = NULL;
	while (*token)
	{
		if (((*token)->type == WHITE_SPACE && (*token)->state == GENERAL)
			|| (is_redir(*token) && (*token)->state == GENERAL)
			|| ((*token)->type == PIPE_LINE && (*token)->state == GENERAL))
			break ;
		else if ((*token)->type != S_QUOTE && (*token)->type != D_QUOTE)
			tmp = ft_strdup((*token)->content);
		else if ((*token)->state == IN_DQUOTE || (*token)->state == IN_SQUOTE)
			tmp = ft_strdup((*token)->content);
		*redir = ft_strjoin(*file, tmp);
		if (*file)
			free(*file);
		*file = *redir;
		free_str(&tmp);
		(*token) = (*token)->next;
	}
}

t_redir	*create_delimiter(t_token **token)
{
	t_redir	*node;
	char	*file;
	char	*delimiter;

	file = NULL;
	delimiter = NULL;
	node = init_list();
	if (!node)
		return (NULL);
	node->type = (*token)->type;
	*token = skip_spaces((*token)->next, 1);
	get_heredoc(token, &delimiter, &file);
	node->content = ft_strdup(file);
	free(file);
	node->next = NULL;
	return (node);
}

void	handle_heredoc(t_token **token, t_command *cmd)
{
	append_to_list(&cmd->heredoc_delimiters, create_delimiter(token));
	/* if ((*token)->next 
		&& ((*token)->next->type == D_QUOTE || (*token)->next->type == S_QUOTE))
		cmd->heredoc_delimiters->state = 1; */
}
