/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 12:48:18 by abmahfou          #+#    #+#             */
/*   Updated: 2024/09/08 12:59:35 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	get_word(t_lst *tokens, char *line, enum e_state state)
{
	int	i;

	i = 0;
	while (line[i] && !not_special(line[i]))
		i++;
	lst_token_add_back(tokens, create_token(line, i, WORD, state));
	return (i);
}

int	_redir_tokenize(t_lst *tokens, char *line, int pos, enum e_state *state)
{
	int	i;

	i = pos;
	if (line[pos] == '>')
	{
		if (line[pos + 1] == '>')
			lst_token_add_back(tokens, create_token(line + (pos++), 2, DREDIR_OUT, *state));
		else
			lst_token_add_back(tokens, create_token(line + (pos), 1, REDIR_OUT, *state));
		pos++;
	}
	else if (line[pos] == '<')
	{
		if (line[pos + 1] == '<')
			lst_token_add_back(tokens, create_token(line + (pos++), 2, HERE_DOC, *state));
		else
			lst_token_add_back(tokens, create_token(line + (pos), 1, REDIR_IN, *state));
		pos++;
	}
	return (pos - i);
}
