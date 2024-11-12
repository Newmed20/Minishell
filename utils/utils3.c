/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:52:42 by abmahfou          #+#    #+#             */
/*   Updated: 2024/11/12 01:18:57 by abmahfou         ###   ########.fr       */
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

int	ft_count(char *executable)
{
	int	i;

	i = 2;
	while (executable[i])
		i++;
	return (i);
}

int	is_executable(t_command *command, char *executable)
{
	char	*path;
	char	*name;
	char	*absolute_path;
	char	*tmp;

	path = NULL;
	absolute_path = NULL;
	absolute_path = getcwd(absolute_path, PATH_MAX);
	if (access(executable, X_OK | F_OK) == 0)
	{
		if (ft_count(executable) == 2)
		{
			printf("bash: ./: is a directory\n");
			return (free(absolute_path), 2);
		}
		name = ft_substr(executable, 2, ft_count(executable));
		tmp = ft_strjoin(absolute_path, "/");
		path = ft_strjoin(tmp, name);
		ft_free(name, tmp, absolute_path);
		command->full_path = ft_strdup(path);
		return (free(path), 1);
	}
	else
		free(absolute_path);
	return (0);
}
