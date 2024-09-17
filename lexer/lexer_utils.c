/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:40:39 by abmahfou          #+#    #+#             */
/*   Updated: 2024/09/10 11:15:23 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

bool	ft_isspace(char c)
{
	return (c == ' ' || c == '\v' || c == '\t' 
		|| c == '\f' || c == '\r' || c == '\n');
}

bool	not_special(char c)
{
	return (c == '|' || c == '>' || c == '<' || c == '$' 
		|| c == '\'' || c == '\"' || c == '\n' 
		|| c == '\0' || ft_isspace(c));
}

t_tkn_lst	*init_lst(t_tkn_lst *lst)
{
	lst = malloc(sizeof(t_tkn_lst));
	if (!lst)
		return (NULL);
	return (lst);
}

void	lst_token_add_back(t_tkn_lst *lst, t_token *new)
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

char	*ft_strndup(const char *s1, int n)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(ft_strlen(s1) * sizeof(char) + 1);
	if (str == NULL)
		return (NULL);
	while (*(s1 + i) && i < n)
	{
		*(str + i) = *(s1 + i);
		i++;
	}
	*(str + i) = '\0';
	return (str);
}
