/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:13:52 by abmahfou          #+#    #+#             */
/*   Updated: 2024/10/15 12:30:25 by abmahfou         ###   ########.fr       */
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
			return (ft_strdup(tmp->value));
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

char	*ft_expand(t_data *data, t_token *token)
{
	char	*name;
	char	*value;

	name = NULL;
	value = NULL;
	if (token && token->len == 1)
	{
		value = ft_strdup(token->content);
		return (value);
	}
	else
		name = get_name(token->content);
	value = get_var_value(data->env_copy, name);
	return (value);	
}
