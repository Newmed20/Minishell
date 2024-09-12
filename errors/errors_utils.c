/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 10:53:24 by abmahfou          #+#    #+#             */
/*   Updated: 2024/09/12 10:54:43 by abmahfou         ###   ########.fr       */
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

int	print_error(void)
{
	write(2, "syntax error !\n", 15);
	return (EXIT_FAILURE);
}
