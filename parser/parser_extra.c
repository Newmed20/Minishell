/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_extra.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:47:26 by abmahfou          #+#    #+#             */
/*   Updated: 2024/10/24 10:07:39 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_command	*create_command(t_data *data, t_command *cmd, t_token **token)
{
	char	*command;
	char	*full_command;

	command = NULL;
	full_command = NULL;
	if (!cmd->cmd_found)
	{
		get_string(token, data, &full_command, &command);
		cmd->command = command;
		cmd->cmd_found = true;
		if (ft_is_command(data, cmd, cmd->command) == 0)
		{
			printf("%s: command not found\n", cmd->command);
			return (cmd);
		}
	}
	fill_args(token, cmd, data);
	return (cmd);
}

void	_first_arg(t_command *cmd, char ***args)
{
	*args = malloc(sizeof(char *) * 2);
	if (!args)
		return ;
	(*args)[0] = ft_strdup(cmd->command);
	if (!(*args)[0])
		return ;
	(*args)[1] = NULL;
	cmd->args = *args;
	cmd->arg_count++;
}

void	tokens_loop(t_data *data, t_token **tmp, t_command **cmd)
{
	while (*tmp)
	{
		if ((*tmp)->type == WORD || (*tmp)->type == ENV 
			|| (*tmp)->state == IN_SQUOTE || (*tmp)->state == IN_DQUOTE
			|| (*tmp)->type == D_QUOTE || (*tmp)->type == S_QUOTE)
		{
			*cmd = create_command(data, *cmd, tmp);
			if (!*tmp)
				break ;
		}
		if (is_redir(*tmp))
		{
			handle_redirections_heredoc(tmp, *cmd, data);
			if (!*tmp)
				break ;
		}
		if ((*tmp)->type == PIPE_LINE)
		{
			lst_add_back(&data->cmd, *cmd);
			(*cmd)->pipe_out = 1;
			*cmd = init_command();
		}
		*tmp = (*tmp)->next;
	}
}
