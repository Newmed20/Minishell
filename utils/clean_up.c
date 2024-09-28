/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:07:14 by abmahfou          #+#    #+#             */
/*   Updated: 2024/09/27 20:10:45 by abmahfou         ###   ########.fr       */
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

void	free_command(t_command **cmd)
{
	t_command	*tmp;

	if (!*cmd)
		return ;
	while (*cmd)
	{
		tmp = (*cmd)->next;
		free((*cmd)->command);
		free((*cmd)->full_path);
		free_split((*cmd)->args);
		free(*cmd);
		*cmd = tmp;
	}
}
