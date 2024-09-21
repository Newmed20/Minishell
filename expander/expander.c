/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:13:52 by abmahfou          #+#    #+#             */
/*   Updated: 2024/09/21 16:00:31 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_name(char *str, int start, t_var_name *var_name)
{
	int		i;
	int		j;
	char	*name;

	i = 0;
	j = 0;
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	name = ft_substr(str, 0, i);
	var_name->end = start + i;
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
	before = ft_substr(str, start, len);
	return (before);
}

char	*get_after(char *str, t_var_name *var_name)
{
	int		start;
	int		i;
	int		j;
	char	*after;

	start = var_name->end;
	j = var_name->end;
	i = 0;
	while (str[j] && str[j] != ' ')
	{
		i++;
		j++;
	}
	after = ft_substr(str, start, i);
	return (after);
}

char	*get_full(char *prompt, t_var_name *var)
{
	int		i;
	int		j;
	char	*full;

	i = 0;
	j = var->pos;
	while (prompt[j] && prompt[j] != ' ')
	{
		i++;
		j++;
	}
	full = malloc((i + 1) * sizeof(char));
	if (!full)
		return (NULL);
	ft_strlcpy(full, prompt + var->pos, i + 1);
	return (full);
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
			if (ft_isdigit(data->prompt[i]))
				name = get_digit(data->prompt[i]);
			else if (!ft_isalnum(data->prompt[i]) && data->prompt[i] != '_')
			{
				printf("full => %s\n", get_full(data->prompt, var_name));
				return (NULL);
			}
			var_name->start = i;
			var_name->name = get_name(data->prompt + i, i, var_name);
			before = get_before(data->prompt, var_name);
			after = get_after(data->prompt, var_name);
		}
		i++;
	}
	var_name->value = get_var_value(data->env_copy, var_name->name);
	char	*s = ft_strjoin(before, var_name->value);
	printf("%s\n", ft_strjoin(s, after));
	return (var_name);
}
