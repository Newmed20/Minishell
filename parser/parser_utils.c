/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 23:48:46 by abmahfou          #+#    #+#             */
/*   Updated: 2024/09/23 23:48:46 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list_ *init_list(void)
{
	t_list_ *lst;

	lst = malloc(sizeof(t_list_));
	if (!lst)
		return (NULL);
	lst->content = NULL;
	lst->next = NULL;
	lst->type = 0;
}
