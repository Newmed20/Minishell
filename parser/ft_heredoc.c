/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 19:52:33 by abmahfou          #+#    #+#             */
/*   Updated: 2024/10/06 19:57:10 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_heredoc(t_token *token, t_command *cmd, t_data *data)
{
	append_to_list(&cmd->heredoc_delimiters, create_redir(token, data));
}
