/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 05:19:39 by mjadid            #+#    #+#             */
/*   Updated: 2024/11/10 15:14:22 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	display_chdir_error(const char *path)
{
	write(STDERR_FILENO, "minishell: cd: ", 15);
	write(STDERR_FILENO, path, ft_strlen(path));
	write(STDERR_FILENO, ": No such file or directory\n", 29);
}

int	change_directory(const char *path)
{
	if (chdir(path) != 0)
	{
		display_chdir_error(path);
		g_exit_status = 1;
		return (1);
	}
	g_exit_status = 0;
	return (0);
}

int	handle_change_directory(t_data *data, char *path)
{
	char	current_working_dir[PATH_MAX];

	update_old_pwd(data, getcwd(current_working_dir, PATH_MAX));
	if (change_directory(path) != 0)
		return (1);
	getcwd(current_working_dir, PATH_MAX);
	update_pwd(data, current_working_dir);
	return (0);
}

char	*get_home(t_data *data)
{
	t_env	*tmp;

	tmp = data->env_copy;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "HOME", 5) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int	ft_cd(t_data *data, t_command *command)
{
	char	*home_dir;
	char	*path;

	if (!command->args[1] || ft_strncmp(command->args[1], "~", 2) == 0)
	{
		home_dir = get_home(data);
		if (home_dir == NULL)
		{
			write(STDERR_FILENO, "minishell: cd: HOME not set\n", 29);
			g_exit_status = 1;
			return (1);
		}
		path = home_dir;
	}
	else
		path = command->args[1];
	return (handle_change_directory(data, path));
}
