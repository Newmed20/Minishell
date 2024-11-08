/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:52:42 by abmahfou          #+#    #+#             */
/*   Updated: 2024/11/08 18:01:32 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_old_pwd(t_data *data, char *path)
{
	t_env	*tmp;

	tmp = data->env_copy;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "OLDPWD", 7))
		{
			free(tmp->value);
			tmp->value = ft_strdup(path);
		}
		tmp = tmp->next;
	}
}

void	update_pwd(t_data *data, char *path)
{
	t_env	*tmp;

	tmp = data->env_copy;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "PWD", 4))
		{
			free(tmp->value);
			tmp->value = ft_strdup(path);
		}
		tmp = tmp->next;
	}
}

int	is_direcotry(const char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf))
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}
