/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjadid <mjadid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 03:08:36 by mjadid            #+#    #+#             */
/*   Updated: 2024/10/28 00:13:51 by mjadid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"      

int	is_option(char **args, int *flag)
{
	int	i;
	int	j;

	i = 0;
	while (args[i])
	{
		if (!ft_strncmp(args[i], "-n", 2))
		{
			j = 2;
			while (args[i][j])
			{
				if (args[i][j] != 'n')
					return (i);
				j++;
			}
			*flag = 0;
		}
		else
			break ;
		i++;
	}
	return (i);
}

int	ft_echo(t_command *s_command)
{
	int	i;
	int	flag;
    char	**args;
    
    args = s_command->args;
	flag = 1;
	i = is_option(args, &flag);
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!args[1] || flag)
		ft_putstr_fd("\n", 1);
	exit_status = 0;
	return (0);
}


// int main(int argc, char **argv)
// {
//     int	exit_status;
//     t_command *s_command;

//     s_command = malloc(sizeof(t_command));
//     s_command->args = argv + 2;
    

//     exit_status = 0;
//     ft_echo(s_command, &exit_status);
//     // printf("exit_status: %d\n", exit_status);
//     return (0);
// }