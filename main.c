/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:59:13 by abmahfou          #+#    #+#             */
/*   Updated: 2024/09/23 16:29:32 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_data(int ac, char **av, char **env, t_data *data)
{
	char	**env_tmp;

	(void)av;
	env_tmp = ft_strdup_2d(env);
	if (ac != 1)
	{
		printf("minishell doesn't accept any argument\n");
		return (EXIT_FAILURE);
	}
	data->cmd = NULL;
	data->env_copy = NULL;
	data->lexer = NULL;
	data->prompt = NULL;
	get_env_cpy(data, env_tmp);
	free_split(env_tmp);
	return (EXIT_SUCCESS);
}

int	init_prompt(t_data *data)
{
	char	*input;

	input = readline(PROMPT);
	if (!input)
	{
		printf("exit\n");
		return (EXIT_FAILURE);
	}
	data->prompt = input;
	add_history(input);
	ft_parser(data);
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	if (init_data(ac, av, env, &data) == 1)
		return (EXIT_SUCCESS);
	while (1)
	{
		if (init_prompt(&data) == 1)
			break ;
	}
	return (EXIT_SUCCESS);
}
