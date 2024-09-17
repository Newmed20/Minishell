/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:59:13 by abmahfou          #+#    #+#             */
/*   Updated: 2024/09/17 19:12:54 by abmahfou         ###   ########.fr       */
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
	return (0);
}

int	init_prompt(t_data *data)
{
	char	*input;
	
	input = readline(PROMPT);
	if (!input)
	{
		printf("exit\n");
		return (1);
	}
	data->prompt = input;
	add_history(input);
	search_name(data);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	if (init_data(ac, av, env, &data) == 1)
		return (0);
	while (1)
	{
		if (init_prompt(&data) == 1)
			break ;
	}
	
	return (0);
}
