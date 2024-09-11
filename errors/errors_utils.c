/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:07:16 by abmahfou          #+#    #+#             */
/*   Updated: 2024/09/11 17:07:16 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token *skip_spaces(t_token *el, int flg)
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
