/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:43:59 by abmahfou          #+#    #+#             */
/*   Updated: 2024/10/31 21:38:00 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*skip_spaces(t_token *el, int flg)
{
	while (el && el->type == WHITE_SPACE)
	{
		if (flg && el->next)
			el = el->next;
		else if (!flg && el->prev)
			el = el->prev;
		else
			break ;
	}
	return (el);
}

int	is_special(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '#' || s[i] == '@' || s[i] == '%' || s[i] == '!'
			|| s[i] == '^' || s[i] == '&' || s[i] == '*' || s[i] == '~'
			|| s[i] == '-' || s[i] == '+' || s[i] == '.' || s[i] == ';'
			|| s[i] == '}' || s[i] == '{' || s[i] == '?' || s[i] == '$' || s[i] == '=')
			return (1);
		i++;
	}
	return (0);
}
