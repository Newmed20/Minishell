/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 22:38:10 by abmahfou          #+#    #+#             */
/*   Updated: 2024/09/16 22:38:10 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_2d(char **str, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	**ft_strdup_2d(char **_2d)
{
	int		i;
	int		len;
	char	**res;

	i = 0;
	len = 0;
	while (_2d[len])
		len++;
	res = malloc((len + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	while (_2d[i])
	{
		res[i] = ft_strdup(_2d[i]);
		if (!res[i])
		{
			free_2d(res, i);
			return (NULL);
		}
		i++;
	}
	res[i] = NULL;
	return (res);
}
