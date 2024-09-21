/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 10:53:24 by abmahfou          #+#    #+#             */
/*   Updated: 2024/09/20 11:24:45 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*skip_spaces(t_token *el, int flg)
{
	while (el && el->type == WHITE_SPACE)
	{
		if (flg)
			el = el->next;
		else
			el = el->prev;
	}
	return (el);
}

int	print_error(int error)
{
	if (error == 1)
		write(2, "syntax error: redirection\n", 26);
	else if (error == 2)
		write(2, "syntax error near unexpected token `|'\n", 39);
	return (EXIT_FAILURE);
}
