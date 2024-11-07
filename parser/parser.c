/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 22:48:22 by abmahfou          #+#    #+#             */
/*   Updated: 2024/11/06 17:56:07 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	_fill_args(t_token **token, t_command *cmd, t_data *data, char ***args)
{
	char	*arg;
	char	*full_arg;
	int		i;

	arg = NULL;
	full_arg = NULL;
	i = 0;
	while ((*args)[i])
		i++;
	get_string(token, data, &full_arg, &arg);
	(*args)[i - 1] = ft_strdup(full_arg);
	free(full_arg);
	free_split(cmd->args);
	cmd->args = *args;
	if (arg)
		cmd->arg_count++;
}

void	loop_arg(t_command *cmd, char ***args)
{
	int	i;

	i = 0;
	while (cmd->args[i])
	{
		(*args)[i] = ft_strdup(cmd->args[i]);
		if (!(*args)[i])
		{
			free(cmd->args[i]);
			return ;
		}
		i++;
	}
}

void	fill_args(t_token **token, t_command *cmd, t_data *data)
{
	char	**args;
	int		i;

	i = 0;
	args = NULL;
	if (cmd->args == NULL)
		_first_arg(cmd, &args);
	else
	{
		while (cmd->args[i])
			i++;
		args = malloc(sizeof(char *) * (i + 2));
		if (!args)
			return ;
		loop_arg(cmd, &args);
		args[i + 1] = NULL;
		_fill_args(token, cmd, data, &args);
	}
}

t_command	*fill_struct(t_data *data)
{
	t_command	*cmd;
	t_token		*tmp;

	cmd = init_command();
	if (!cmd)
		return (NULL);
	tmp = data->lexer->tokens;
	if (!tmp)
		return (NULL);
	tokens_loop(data, &tmp, &cmd);
	if (cmd)
		lst_add_back(&data->cmd, cmd);
	return (data->cmd);
}

void	ft_parser(t_data *data)
{
	data->lexer = lexer(data->prompt);
	if (!data->lexer)
	{
		free_tkn_lst(&data->lexer);
		return ;
	}
	if (!syntax_error(data->lexer))
	{
		data->cmd = fill_struct(data);
		if (!data->cmd)
		{
			free_tkn_lst(&data->lexer);
			free_command(&data->cmd);
			return ;
		}
	}
}
