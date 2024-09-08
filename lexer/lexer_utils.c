/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:40:39 by abmahfou          #+#    #+#             */
/*   Updated: 2024/09/08 14:13:24 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

bool	ft_isspace(char c)
{
	if (c == ' ' || c == '\v' || c == '\t' 
		|| c == '\f' || c == '\r' || c == '\n')
		return (true);
	return (false);
}

bool	not_special(char c)
{
	return (c == '|' || c == '>' || c == '<' || c == '$' 
		|| c == '\'' || c == '\"' || c == '\n' 
		|| c == '\0' || ft_isspace(c));
}

t_lst	*init_lst(t_lst *lst)
{
	lst = malloc(sizeof(t_lst));
	if (!lst)
		return (NULL);
	return (lst);
}

void	lst_token_add_back(t_lst *lst, t_token *new)
{
	if (lst->head == NULL)
		lst->head = new;
	else
	{
		lst->tail->next = new;
		new->prev = lst->tail;
	}
	lst->tail = new;
}

