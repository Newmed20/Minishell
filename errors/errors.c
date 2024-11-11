/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:49:07 by abmahfou          #+#    #+#             */
/*   Updated: 2024/11/11 15:54:49 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_direcotry(const char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf))
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

void	ft_errors(char *comand)
{
	struct stat statbuf;
	
}
