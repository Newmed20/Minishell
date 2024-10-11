/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:13:52 by abmahfou          #+#    #+#             */
/*   Updated: 2024/10/10 18:12:13 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_var_value(t_env *env, char *key)
{
	t_env	*tmp;	

	tmp = env;
	if (!key)
		return (NULL);
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key) + 1) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_name(char *str)
{
	int		i;
	char	*name;

	i = 1;
	while (str[i])
		i++;
	name = ft_substr(str, 1, i);
	return (name);
}

void	search_name(t_var_name *var_name, t_token *token)
{
	if (token->next && token->len == 1)
		var_name->value = ft_strjoin(token->content, token->next->content);
	if (token->next && token->len == 2 && ft_isdigit(token->content[1]))
		var_name->value = ft_strdup(token->next->content);
	if ((token->next && token->next->type == WORD) && (token->prev && token->prev->type == WORD))
	{
		var_name->name = get_name(token->content);
		var_name->before = ft_strdup(token->prev->content);
		var_name->after = ft_strdup(token->next->content);
	}
	if (token->next && token->next->type == WORD)
	{
		var_name->name = get_name(token->content);
		var_name->after = ft_strdup(token->next->content);
	}
	if (token->prev && token->prev->type == WORD)
	{
		var_name->name = get_name(token->content);
		var_name->before = ft_strdup(token->prev->content);
	}
	else
		var_name->name = get_name(token->content);
}

char	*ft_expand(t_data *data, t_token *token)
{
	t_var_name	*var_name;
	char		*var;

	var_name = malloc(sizeof(t_var_name));
	if (!var_name)
		return (NULL);
	var_name->after = NULL;
	var_name->name = NULL;
	var_name->value = NULL;
	var_name->before = NULL;
	var_name->pos = 0;
	var_name->start = 0;
	var_name->end = 0;
	search_name(var_name, token);
	if (var_name->value && var_name->value[0] == '$')
		return (var_name->value);
	var_name->value = get_var_value(data->env_copy, var_name->name);
	var = ft_strjoin(var_name->before, var_name->value);
	return (ft_strjoin(var, var_name->after));
}
