/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjadid <mjadid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 05:19:39 by mjadid            #+#    #+#             */
/*   Updated: 2024/10/29 08:27:22 by mjadid           ###   ########.fr       */
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
		exit_status = 1;
		return (1);
	}
	exit_status = 0;
	return (0);
}

int	handle_change_directory(char *path)
{
	char	current_working_dir[PATH_MAX];

	if (change_directory(path) != 0)
	{
		return (1);
	}
	getcwd(current_working_dir, PATH_MAX);
	// printf("%s\n", current_working_dir);  // Print current working directory
	return (0);
}

int	ft_cd(t_command *command)
{
	char	*home_dir;

	if (!command->args[1])
	{
		home_dir = getenv("HOME");
		if (home_dir == NULL)
		{
			write(STDERR_FILENO, "minishell: cd: HOME not set\n", 29);
			exit_status = 1;
			return (1);
		}
		handle_change_directory(home_dir);
		return (0);
	}
	else
		return (handle_change_directory(command->args[1]));
}
