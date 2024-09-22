/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:24:34 by abmahfou          #+#    #+#             */
/*   Updated: 2024/09/22 14:49:41 by abmahfou         ###   ########.fr       */
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
		if (ft_strncmp(tmp->key, key, ft_strlen(tmp->key)) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_digit(char c, int pos, t_var_name *name, t_data *data)
{
	char	*res;
	char	*str;
	int		len;
	int		j;

	res = malloc(2 * sizeof(char));
	if (!res)
		return (NULL);
	res[0] = c;
	res[1] = '\0';
	name->name = res;
	free(res);
	j = pos++;
	len = 0;
	while (data->prompt[j] && data->prompt[j] != ' ')
	{
		len++;
		j++;
	}
	str = ft_substr(data->prompt, pos, 32);
	return (str);
}

char	*get_full(char *prompt, t_var_name *var)
{
	int		i;
	int		j;
	int		start;
	char	*full;

	i = 0;
	start = var->pos;
	j = var->pos;
	while (prompt[j] && prompt[j] != ' ')
	{
		i++;
		j++;
	}
	full = ft_substr(prompt, start, i);
	return (full);
}
