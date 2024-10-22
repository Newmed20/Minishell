/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 22:48:22 by abmahfou          #+#    #+#             */
/*   Updated: 2024/10/22 14:48:33 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_command	*init_command()
{
	t_command	*cmd;

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
	cmd->next = NULL;
	cmd->cmd_found = false;
	cmd->pipe_out = 0;
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

void	_fill_args(t_token **token, t_command *cmd, t_data *data, char ***args, int pos)
{
	char	*arg;
	char	*full_arg;

	arg = NULL;
	full_arg = NULL;
	get_string(token, data, &full_arg, &arg);
	(*args)[pos] = ft_strdup(full_arg);
	free(full_arg);
	(*args)[pos + 1] = NULL;
	free_split(cmd->args);
	cmd->args = *args;
	if (arg)
		cmd->arg_count++;
}

void	fill_args(t_token **token, t_command *cmd, t_data *data)
{
	char	**args;
	int		i;

	i = 0;
	args = NULL;
	if (!cmd->command)
		return ;
	if (cmd->args == NULL)
		_first_arg(cmd, &args);
	else
	{
		while (cmd->args[i])
			i++;
		args = malloc(sizeof(char *) * (i + 2));
		if (!args)
			return ;
		i = 0;
		while (cmd->args[i])
		{
			args[i] = ft_strdup(cmd->args[i]);
			if (!args[i])
			{
				free(cmd->args[i]);
				return ;
			}
			i++;
		}
		_fill_args(token, cmd, data, &args, i);
	}
}

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

/* void	tokens_loop(t_token **tmp, t_data *data, t_command **cmd)
{
	while (*tmp)
	{
		if ((*tmp)->type == WORD || (*tmp)->type == ENV 
			|| (*tmp)->state == IN_SQUOTE || (*tmp)->state == IN_DQUOTE
			|| (*tmp)->type == D_QUOTE || (*tmp)->type == S_QUOTE)
		{
			*cmd = create_command(data, *cmd, tmp);
			if (!tmp)
				break;
		}
		if (is_redir(*tmp))
		{
			handle_redirections_heredoc(tmp, *cmd, data);
			if (!tmp)
				break;
		}
		if ((*tmp)->type == PIPE_LINE)
		{
			lst_add_back(&data->cmd, *cmd);
			(*cmd)->pipe_out = 1;
			*cmd = init_command();
		}
		*tmp = (*tmp)->next;
	}
} */

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
	while (tmp)
	{
		if (tmp->type == WORD || tmp->type == ENV 
			|| tmp->state == IN_SQUOTE || tmp->state == IN_DQUOTE
			|| tmp->type == D_QUOTE || tmp->type == S_QUOTE)
		{
			cmd = create_command(data, cmd, &tmp);
			if (!tmp)
				break;
		}
		if (is_redir(tmp))
		{
			handle_redirections_heredoc(&tmp, cmd, data);
			if (!tmp)
				break;
		}
		if (tmp->type == PIPE_LINE)
		{
			lst_add_back(&data->cmd, cmd);
			cmd->pipe_out = 1;
			cmd = init_command();
		}
		tmp = tmp->next;
	}
	if (cmd)
		lst_add_back(&data->cmd, cmd);
	return (data->cmd);
}

void	_debug(t_data *data)
{
	t_command	*tmp = data->cmd;
	while (tmp)
	{
		t_redir	*t = tmp->input_files;
		while (t)
		{
			printf("CONTENT => %s\n", t->content);
			printf("TYPE => %s\n", print_type(t->type));
			t = t->next;
		}
		t_redir	*s = tmp->oa_files;
		while (s)
		{
			printf("CONTENT => %s\n", s->content);
			printf("TYPE => %s\n", print_type(s->type));
			s = s->next;
		}
		t_redir	*heredoc = tmp->heredoc_delimiters;
		while (heredoc)
		{
			printf("DELIMITER => %s\n", heredoc->content);
			printf("TYPE => %s\n", print_type(heredoc->type));
			heredoc = heredoc->next;
		}
		printf("------------------------------\n");
		printf("------------------------------\n");
		printf("COMMAND => %s\n", tmp->command);
		int i = 0;
		if (!tmp->args)
			return ;
		while (tmp->args[i])
			printf("%s\n", tmp->args[i++]);
		printf("------------------------------\n");
		printf("------------------------------\n");
		printf("PATH => %s\n", tmp->full_path);
		printf("ARG_COUNT: %d\n", tmp->arg_count);
		tmp = tmp->next;
		printf("\n------------------------------\n");
		// print_token(data->lexer);
	}
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
		_debug(data);
	}
	free_tkn_lst(&data->lexer);
	free_command(&data->cmd);
}
