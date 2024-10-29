/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjadid <mjadid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 04:09:22 by mjadid            #+#    #+#             */
/*   Updated: 2024/10/29 08:16:39 by mjadid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	ft_pwd(void)
{
	char	*directory_path;
	
	directory_path = (char *)malloc(PATH_MAX);
	if (!directory_path)
	{
		perror("minishell: pwd: malloc");
		exit_status = -1;
		return (-1);
	}
	if (getcwd(directory_path, PATH_MAX) == NULL)
	{
		perror("minishell: pwd: ");
		free(directory_path);
		exit_status = -1;
		return (-1);
	}
	printf("%s\n", directory_path);
	free(directory_path);
	exit_status = 0;
	return (0);
}
