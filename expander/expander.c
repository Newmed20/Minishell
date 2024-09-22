/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:13:52 by abmahfou          #+#    #+#             */
/*   Updated: 2024/09/22 14:49:35 by abmahfou         ###   ########.fr       */
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

/* char	*get_before(char *str, t_var_name *var_name)
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
} */

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

int	extra_check(t_data *data, int pos, t_var_name *var_name)
{
	if (ft_isdigit(data->prompt[pos]))
	{
		var_name->value = get_digit(data->prompt[pos], pos, var_name, data);
		return (1);
	}
	else if (!ft_isalnum(data->prompt[pos]) && data->prompt[pos] != '_')
	{
		var_name->value = get_full(data->prompt, var_name);
		return (1);
	}
	return (0);
}

void	search_name(t_data *data, t_var_name *var_name)
{
	int			i;
	char		*name;
	char		*after;

	i = 0;
	name = NULL;
	after = NULL;
	while (data->prompt[i])
	{
		if (data->prompt[i] == '$')
		{
			var_name->pos = i;
			var_name->start = i++;
			if (extra_check(data, i, var_name))
				return ;
			var_name->name = get_name(data->prompt + i, i, var_name);
			after = get_after(data->prompt, var_name);
		}
		i++;
	}
	var_name->after = after;
	var_name->value = get_var_value(data->env_copy, var_name->name);
}

t_var_name	*ft_expand(t_data *data)
{
	t_var_name	*var_name;

	var_name = malloc(sizeof(t_var_name));
	if (!var_name)
		return (NULL);
	search_name(data, var_name);
	printf("%s\n", ft_strjoin(var_name->value, var_name->after));
	return (var_name);
}
