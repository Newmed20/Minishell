/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 23:48:46 by abmahfou          #+#    #+#             */
/*   Updated: 2024/10/06 11:24:27 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redir *init_list(void)
{
	t_redir *lst;

	lst = malloc(sizeof(t_redir));
	if (!lst)
		return (NULL);
	lst->content = NULL;
	lst->next = NULL;
	lst->type = 0;
	lst->state = 0;
	return (lst);
}

void	append_to_list(t_redir **lst, t_redir *new)
{
	t_redir	*tmp;

	if (*lst == NULL)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_command	*last_cmd(t_command *last)
{
	t_command	*l;

	l = last;
	if (!l)
		return (NULL);
	while (l->next)
		l = l->next;
	return (l);
}

void	lst_add_back(t_command **cmds, t_command *cmd)
{
	t_command	*last;

	if (*cmds == NULL)
		*cmds = cmd;
	else
	{
		last = last_cmd(*cmds);
		last->next = cmd;
	}
}
