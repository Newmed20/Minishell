/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjadid <mjadid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 04:09:22 by mjadid            #+#    #+#             */
/*   Updated: 2024/09/13 05:35:23 by mjadid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_pwd()
{
	char	*directory_path;
	
	directory_path = (char *)malloc(PATH_MAX);
	if (!directory_path)
	{
		perror("minishell: pwd: malloc");
		return (-1);
	}
	if (getcwd(directory_path, PATH_MAX) == NULL)
	{
		perror("minishell: pwd: ");
		free(directory_path);
		return (-1);
	}
	printf("%s\n", directory_path);
	free(directory_path);
	return (0);
}
