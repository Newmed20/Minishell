/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 10:09:31 by abmahfou          #+#    #+#             */
/*   Updated: 2024/09/08 13:50:01 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*create_token(char *content, int len, enum e_type type, enum e_state state)
{
	t_token	*token;
	char	*str;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	str = ft_strdup(content);
	if (!str)
		return (NULL);
	token->content = str;
	token->len = len;
	token->state = state;
	token->type = type;
	return (token);
}

int	_tokenize(char *line, t_lst *tokens, int pos, enum e_state *state)
{
	if (!not_special(line[pos]))
		pos += get_word(tokens, line + pos, *state);
	else if (line[pos] == '>' || line[pos] == '<')
		_redir_tokenize(tokens, line, pos, state);
	else if (line[pos] == '|')
		lst_token_add_back(tokens, create_token(line + (pos++), 1, PIPE_LINE, *state));
	else if (isspace(line[pos]))
		lst_token_add_back(tokens, create_token(line + (pos++), 1, WHITE_SPACE, *state));
	return (pos);
}

t_lst	*lexer(char *line)
{
	t_lst			*tokens;
	enum e_state	state;
	int				i;

	i = 0;
	tokens = NULL;
	state = GENERAL;
	tokens = init_lst(tokens);
	if (!tokens)
		return(NULL);
	while (line[i])
	{
		i = _tokenize(line, tokens, i, &state);
	}
	return (tokens);
}

int main()
{
	char *line = "echo \"hello  $USER \" > file | grep h | cat << eof | cat >> file | echo 'done'";
	t_lst *token;

	token = lexer(line);
	printf("content => %s\n", token->head->content);
}
