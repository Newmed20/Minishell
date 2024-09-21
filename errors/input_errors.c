/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 23:00:37 by abmahfou          #+#    #+#             */
/*   Updated: 2024/09/20 11:17:52 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	compare_symbol(t_data *data, char *symbol, int length)
// {
// 	return (!ft_strncmp(data->prompt, symbol, length)
// 		&& (int)(ft_strlen(data->prompt)) == length);
// }

// int	check_standalone_symbols(t_data *data)
// {
// 	if (compare_symbol(data, "|", 1)
// 	|| compare_symbol(data, "&", 1)
// 	|| compare_symbol(data, "<", 1) || compare_symbol(data, ";", 1)
// 	|| compare_symbol(data, "&&", 2) || compare_symbol(data, "||", 2)
// 	|| compare_symbol(data, "<<", 2) || compare_symbol(data, ">>", 2)
// 	|| compare_symbol(data, "|&", 2) || compare_symbol(data, "&|", 2)
// 	|| compare_symbol(data, ">|", 2) || compare_symbol(data, "<|", 2)
// 	|| compare_symbol(data, "&>", 2) || compare_symbol(data, "&<", 2)
// 	|| compare_symbol(data, ";>", 2) || compare_symbol(data, ";<", 2)
// 	|| compare_symbol(data, ";;", 2) || compare_symbol(data, "?<", 2)
// 	|| compare_symbol(data, "&?", 2) || compare_symbol(data, "?>", 2)
// 	|| compare_symbol(data, "&-", 2))
// 		return (EXIT_FAILURE);
// 	return (EXIT_SUCCESS);
// }

// int	input_error(t_data *data)
// {
// 	if (check_standalone_symbols(data))
// 	{
// 		print_error();
// 		return (EXIT_FAILURE);
// 	}
// 	return (EXIT_SUCCESS);
// }
