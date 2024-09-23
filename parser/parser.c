/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 22:48:22 by abmahfou          #+#    #+#             */
/*   Updated: 2024/09/23 19:50:00 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_command	*init_cmd(t_command *cmd)
{
	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->command = NULL;
	cmd->arg_count = 0;
	cmd->args = NULL;
	cmd->full_path = NULL;
	cmd->heredoc_content = NULL;
	cmd->heredoc_delimiters = NULL;
	cmd->input_files = NULL;
	cmd->oa_files = NULL;
	cmd->pipe_out = 0;
	cmd->next = NULL;
	return (cmd);
}

t_command	*create_cmd(t_data *data, t_command *cmd, t_tkn_lst *lst)
{
	t_command	*node;
	char		*command;
	char		*args;
	
	node = init_cmd(node);
	if (!node)
		return (NULL);
	if (ft_is_command(data, lst->tokens->content))
		command = ft_strdup(lst->tokens->content);
	return (node);
}

t_command	*fill_struct(t_data *data)
{
	t_command	*cmd;
	t_token		*tmp;

	cmd = init_cmd(cmd);
	tmp = data->lexer->tokens;
	while (tmp)
	{
		if (tmp->type == PIPE_LINE)
		{
			cmd = init_cmd(cmd);
		}
		else if (tmp->type == WORD)
		{
			cmd = create_cmd(data, cmd, tmp);
		}
		tmp = tmp->next;
	}
	return (data->cmd);
}

void	ft_parser(t_data *data)
{
	t_token	*tmp;

	data->lexer = lexer(data->prompt);
	tmp = data->lexer->tokens;
	if (!syntax_error(tmp))
	{
		data->cmd = fill_struct(data);
	}
}
