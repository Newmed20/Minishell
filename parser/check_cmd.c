/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:41:16 by abmahfou          #+#    #+#             */
/*   Updated: 2024/09/23 17:30:21 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


char	**get_full_path(t_data *data)
{
	char	*full_path;
	char	*paths;

	full_path = NULL;	
	while (data->env_copy)
	{
		if (data->env_copy->key == "PATH")
			full_path = data->env_copy->value;
		data->env_copy->next;
	}
	paths = ft_split(full_path, ':');
	return (paths);
}

int	ft_is_command(t_data *data, char *cmd)
{
	char	**paths;
	int		i;

	i = 0;
	paths = get_full_path(data);
	if (access(cmd, X_OK) == 0)
		return (1);
	else
	{
		while (paths[i])
		{
			if (access(ft_strjoin(paths[i], cmd), X_OK) == 0)
				return (1);
			i++;
		}
	}
	free_2d(paths, i);
	return (0);
}
