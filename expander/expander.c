/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:13:52 by abmahfou          #+#    #+#             */
/*   Updated: 2024/09/18 20:51:16 by abmahfou         ###   ########.fr       */
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
		if (ft_strncmp(tmp->key, key, ft_strlen(key)) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_name(char *str, int n, t_var_name *var_name)
{
	int		i;
	int		j;
	char	*name;

	i = 0;
	j = 0;
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	// if (i == 0)
	// 	return (NULL);
	name = malloc((i + 1) * sizeof(char));
	if (!name)
		return (NULL);
	ft_strlcpy(name, str, i + 1);
	var_name->end = n + i;
	return (name);
}

char	*get_before(char *str, t_var_name *var_name)
{
	int		start;
	int		len;
	char	*before;

	start = var_name->pos - 1;
	while (start >= 0 && str[start] != ' ')
		start--;
	start++;
	len = var_name->pos - start;
	before = malloc((len + 1) * sizeof(char));
	if (!before)
		return (NULL);
	ft_strlcpy(before, str + start, len + 1);
	return (before);
}

char	*get_after(char *str, t_var_name *var_name)
{
	int		start;
	int		i;
	char	*after;

	start = var_name->end;
	i = 0;
	while (str[start] && str[start] != ' ')
	{
		i++;
		start++;
	}
	start -= i;
	after = malloc((i + 1) * sizeof(char));
	if (!after)
		return (NULL);
	ft_strlcpy(after, str + start, i + 1);
	return (after);
}

t_var_name	*search_name(t_data *data)
{
	int			i;
	char		*name;
	char		*before;
	char		*after;
	t_var_name	*var_name;

	i = 0;
	name = NULL;
	before = NULL;
	after = NULL;
	var_name = malloc(sizeof(t_var_name));
	if (!var_name)
		return (NULL);
	while (data->prompt[i])
	{
		if (data->prompt[i] == '$')
		{
			var_name->pos = i;
			i++;
			if (!ft_isalnum(data->prompt[i]) && data->prompt[i] != '_')
				break ;
			var_name->start = i;
			name = get_name(data->prompt + i, i, var_name);
			before = get_before(data->prompt, var_name);
			after = get_after(data->prompt, var_name);
		}
		i++;
	}
	var_name->name = name;
	var_name->value = get_var_value(data->env_copy, var_name->name);
	printf("%s=%s\n", var_name->name, var_name->value);
	printf("before: %s\n", before);
	printf("after: %s\n", after);
	return (var_name);
}
