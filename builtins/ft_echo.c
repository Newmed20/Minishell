/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjadid <mjadid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 03:08:36 by mjadid            #+#    #+#             */
/*   Updated: 2024/09/17 03:09:07 by mjadid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"      


int    ft_echo(t_command *command)
{
    int	i;
    int	n_flag;

    i = 1;
    n_flag = 0;
    if (command->arg_count > 1 && ft_strcmp(command->args[1], "-n") == 0)
    {
        n_flag = 1;
        i++;
    }
    while (i < command->arg_count)
    {
        write(STDOUT_FILENO, command->args[i], ft_strlen(command->args[i]));
        if (i + 1 < command->arg_count)
            write(STDOUT_FILENO, " ", 1);
        i++;
    }
    if (!n_flag)
        write(STDOUT_FILENO, "\n", 1);
    return (0);
}