/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:07:14 by abmahfou          #+#    #+#             */
/*   Updated: 2024/09/26 18:16:09 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tkn_lst(t_tkn_lst *lst)
{
	t_token	*tmp;
	t_token	*next;

	if (!lst)
		return ;
	tmp = lst->tokens;
	while (tmp)
	{
		free(tmp->content);
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	free(lst);
}
