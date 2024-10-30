/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 01:08:05 by mjadid            #+#    #+#             */
/*   Updated: 2024/10/29 21:45:35 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_var(t_data *data, char *str)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	key = ft_strndup(str, i);
	value = ft_strndup(str + i + 1, ft_strlen(str + i + 1));
	if (!key || !value)
	{
		free(key);
		free(value);
		return (1);
	}
	if (get_var_value(data->env, key))
	{
		free(key);
		free(value);
		return (0);
	}
	add_env(&data->env, key, value);
	free(key);
	free(value);
	return (0);
}

int	ft_export(t_data *data)
{
	int		i;
	int		j;
	char	*str;

	i = 1;
	while (data->cmd->args[i])
	{
		j = 0;
		str = data->cmd->args[i];
		if (ft_isdigit(str[j]) || str[j] == '=')
		{
			printf("minishell: export: `%s': not a valid identifier\n", str);
			return (1);
		}
		if (check_var(data, str))
			return (1);
		i++;
	}
	return (0);
}
