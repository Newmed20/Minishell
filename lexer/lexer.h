/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:46:46 by abmahfou          #+#    #+#             */
/*   Updated: 2024/09/12 17:37:47 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../minishell.h"

bool	not_special(char c);
t_lst	*init_lst(t_lst *lst); 
void	lst_token_add_back(t_lst *lst, t_token *new);
int		get_word(t_lst *tokens, char *line, enum e_state state);
t_token	*create_token(char *content, int len, enum e_type type, 
			enum e_state state);
int		_redir_tokenize(t_lst *tokens, char *line, int pos, 
			enum e_state *state);
bool	ft_isspace(char c);
void	_quote_tokenize(t_lst *tokens, char *line, enum e_type type, 
			enum e_state *state);
char	*ft_strndup(const char *s1, int n);
void	print_token(t_lst *lst); // ~~!!!!!!!!~~
int		_env_tokenize(t_lst *tokens, char *line, 
			enum e_type type, enum e_state state);
t_lst	*lexer(char *line);

#endif