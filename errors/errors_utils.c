/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 10:53:24 by abmahfou          #+#    #+#             */
/*   Updated: 2024/11/07 10:12:22 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_error(int error)
{
	if (error == 1)
		write(2, "minishell: syntax error: redirection\n", 37);
	else if (error == 2)
		write(2, "minishell: syntax error near unexpected token `|'\n", 50);
	return (EXIT_FAILURE);
}
