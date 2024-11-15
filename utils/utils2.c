/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:43:59 by abmahfou          #+#    #+#             */
/*   Updated: 2024/11/11 22:21:10 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*skip_spaces(t_token *el, int flg)
{
	while (el && el->type == WHITE_SPACE)
	{
		if (flg && el->next)
			el = el->next;
		else if (!flg && el->prev)
			el = el->prev;
		else
			break ;
	}
	return (el);
}

int	is_special(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '#' || s[i] == '@' || s[i] == '%' || s[i] == '!'
			|| s[i] == '^' || s[i] == '&' || s[i] == '*' || s[i] == '~'
			|| s[i] == '-' || s[i] == '+' || s[i] == '.' 
			|| s[i] == ';' || s[i] == ' '
			|| s[i] == '}' || s[i] == '{' || s[i] == '?' 
			|| s[i] == '$' || s[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	check_empty(t_data *data)
{
	t_token	*token;

	token = data->lexer->tokens;
	while (token)
	{
		if (!ft_strncmp(data->cmd->command, token->content,
				ft_strlen(data->cmd->command) + 1))
			break ;
		token = token->next;
	}
	if (token->next)
		token = skip_spaces(token->next, 1);
	if ((token->type == S_QUOTE || token->type == D_QUOTE)
		&& (token->next->type == S_QUOTE || token->next->type == D_QUOTE))
		return (1);
	return (0);
}

void	ft_free(char *name, char *tmp, char *absolute_path)
{
	free(name);
	free(tmp);
	free(absolute_path);
}

char	*get_heredoc_content(t_tkn_lst *lst, t_data *data)
{
	t_token	*token;
	char	*tmp;
	char	*file;
	char	*full_l;

	token = lst->tokens;
	tmp = NULL;
	file = NULL;
	while (token)
	{
		if ((token)->type == ENV)
			tmp = ft_expand(data, (token));
		else
			tmp = ft_strdup((token)->content);
		full_l = ft_strjoin(file, tmp);
		file = full_l;
		free_str(&tmp);
		token = token->next;
	}
	return (full_l);
}
