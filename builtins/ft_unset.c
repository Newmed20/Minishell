/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 19:24:48 by abmahfou          #+#    #+#             */
/*   Updated: 2024/10/31 21:42:17 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_env(t_env **env, char *key)
{
	
}

int	_check_var(t_data *data, char *str)
{
	int	i;
	t_env	*tmp;

	i = 0;
	tmp = data->env_copy;
	if (ft_isdigit(str[0]) || str[0] == '=' || is_special(str) || str[0] == '=')
		return (1);
	remove_env(&data->env_copy, str);
	return (0);
}

int	ft_unset(t_data *data)
{
	int		i;
	char	*str;

	i = 1;
	if (data->cmd->args[i])
	{
		while (data->cmd->args[i])
		{
			str = data->cmd->args[i];
			if (_check_var(data, str))
			{
				printf("minishell: export: `%s': not a valid identifier\n", str);
				return (1);
			}
			i++;
		}
	}
	return (0);
}
