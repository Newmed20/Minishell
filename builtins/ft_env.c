/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjadid <mjadid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 10:00:34 by mjadid            #+#    #+#             */
/*   Updated: 2024/09/18 04:47:31 by mjadid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int     ft_env(t_data *data)
{
	t_env *tmp;
	tmp = data->env_copy;
	
	while (tmp)
	{
		if(tmp->value)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	exit_status = 0;
	return (0);
}
