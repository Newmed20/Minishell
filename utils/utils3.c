/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:52:42 by abmahfou          #+#    #+#             */
/*   Updated: 2024/11/04 18:53:07 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_old_pwd(t_data *data, char *path)
{
	t_env	*tmp;

	tmp = data->env_copy;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "OLDPWD", 6))
			tmp->value = ft_strdup(path);
		tmp = tmp->next;
	}
}

void	update_pwd(t_data *data, char *path)
{
	t_env	*tmp;

	tmp = data->env_copy;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "PWD", 3))
			tmp->value = ft_strdup(path);
		tmp = tmp->next;
	}
}
