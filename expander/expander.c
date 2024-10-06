/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:13:52 by abmahfou          #+#    #+#             */
/*   Updated: 2024/10/05 17:29:18 by abmahfou         ###   ########.fr       */
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

int	extra_check(int pos, t_var_name *var_name, char *env_var)
{
	if (ft_isdigit(env_var[pos]))
	{
		var_name->value = get_digit(env_var[pos], pos, var_name, env_var);
		return (1);
	}
	else if (!ft_isalnum(env_var[pos]) && env_var[pos] != '_')
	{
		var_name->value = get_full(env_var, var_name);
		return (1);
	}
	return (0);
}

void	search_name(t_data *data, t_var_name *var_name, char *env_var)
{
	int			i;
	char		*name;
	char		*after;

	i = 0;
	name = NULL;
	after = NULL;
	while (env_var[i])
	{
		if (env_var[i] == '$')
		{
			var_name->pos = i;
			var_name->start = i++;
			if (extra_check(i, var_name, env_var))
				return ;
			var_name->name = get_name(env_var + i, i, var_name);
			after = get_after(env_var, var_name);
		}
		i++;
	}
	var_name->after = after;
	var_name->value = get_var_value(data->env_copy, var_name->name);
}

char	*ft_expand(t_data *data, char *env_var)
{
	t_var_name	*var_name;
	char	*var;

	var_name = malloc(sizeof(t_var_name));
	if (!var_name)
		return (NULL);
	var_name->after = NULL;
	var_name->name = NULL;
	var_name->value = NULL;
	var_name->pos = 0;
	var_name->start = 0;
	var_name->end = 0;
	search_name(data, var_name, env_var);
	var = ft_strjoin(var_name->value, var_name->after);
	return (var);
}
