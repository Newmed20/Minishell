/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:46:30 by abmahfou          #+#    #+#             */
/*   Updated: 2024/10/29 12:26:49 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exit(t_data *data)
{
	free_env(&data->env_copy);
	free_tkn_lst(&data->lexer);
	free(data->prompt);
	exit(exit_status);
	return (EXIT_SUCCESS);
}
