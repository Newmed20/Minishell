/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 22:48:22 by abmahfou          #+#    #+#             */
/*   Updated: 2024/10/01 13:02:21 by abmahfou         ###   ########.fr       */
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
	return (cmd);
}

void	fill_command(t_data *data, t_token *token, t_command *cmd)
{
	char	*command;

	ft_is_command(data, cmd, token->content);
	command = ft_strdup(token->content);
	if (!command)
		return ;
	cmd->command = command;
	cmd->cmd_found = true;
}

void	fill_args(t_token *token, t_command *cmd)
{
	char	**args;
	int		i;
	
	i = 0;
	if (cmd->args == NULL)
	{
		args = malloc(sizeof(char *) * 2);
		if (!args)
			return ;
		args[0]	= ft_strdup(token->content);
		args[1] = NULL;
		cmd->args = args;
		cmd->arg_count++;
	}
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
		args[i] = ft_strdup(token->content);
		args[i + 1] = NULL;
		free(cmd->args);
		cmd->args = args;
		cmd->arg_count++;
	}
}

t_redir	*create_heredoc(char *line)
{
	t_redir	*node;
	
	node = init_list();
	if (!node)
		return (NULL);
	node->content = ft_strdup(line);
	if (!node->content)
		return (NULL);
	node->type = HERE_DOC;
	node->next = NULL;
	return (node);
}

void	handle_heredoc(t_token *token, t_command *cmd)
{
	char	*line;

	append_to_list(&cmd->heredoc_delimiters, create_redir(token));
	while (1)
	{
		line = readline("> ");
		if (ft_strncmp(line, cmd->heredoc_delimiters->content,
			ft_strlen(line)) == 0)
			break ;
		append_to_list(&cmd->heredoc_content, create_heredoc(line));
	}
}

t_command	*create_command(t_data *data, t_command *cmd, t_token *token)
{
	if (!cmd->cmd_found)
		fill_command(data, token, cmd);
	fill_args(token, cmd);
	handle_redirections_heredoc(token, cmd);
	return (cmd);
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
	while (tmp)
	{
		if (tmp->type == WORD)
			cmd = create_command(data, cmd, tmp);
		else if (is_redir(tmp))
			handle_redirections_heredoc(tmp, cmd);
		else if (tmp->type == PIPE_LINE)
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

void	ft_parser(t_data *data)
{
	data->lexer = lexer(data->prompt);
	if (!data->lexer)
		return ;
	free_command(&data->cmd);
	if (!syntax_error(data->lexer))
	{
		data->cmd = fill_struct(data);
		if (!data->cmd)
			return ;
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
				printf("CONTENT => %s\n", heredoc->content);
				printf("TYPE => %s\n", print_type(heredoc->type));
				heredoc = heredoc->next;
			}
			printf("------------------------------\n");
			printf("COMMAND => %s\n", tmp->command);
			int i = 0;
			if (!tmp->args)
				return ;
			while (tmp->args[i])
				printf("%s\n", tmp->args[i++]);
			printf("------------------------------\n");
			printf("PATH => %s\n", tmp->full_path);
			tmp = tmp->next;
		}
	}
}
