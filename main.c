/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:59:13 by abmahfou          #+#    #+#             */
/*   Updated: 2024/09/17 09:49:34 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_data(int ac, char **av, char **env, t_data *data)
{
	(void)av;
	char	**env_tmp;

	env_tmp = ft_strdup_2d(env);
	if (ac != 1)
	{
		printf("minihell doesn't accept any argument\n");
		return (1);
	}
	data->cmd = NULL;
	data->env_copy = NULL;
	data->lex = NULL;
	data->prompt = NULL;
	get_env_cpy(data, env_tmp);
	t_env	*tmp;
	tmp = data->env_copy;
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	
	if (init_data(ac, av, env, &data) == 1)
		return (0);
	return (0);
}
