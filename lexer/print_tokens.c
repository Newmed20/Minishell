# include "lexer.h"

char	*print_state(enum e_state state)
{
	switch (state)
	{
		case IN_SQUOTE: return "IN_SQUOTE";
		case IN_DQUOTE: return "IN_DQUOTE";
		case GENERAL: return "GENERAL";
	}
	return NULL;
}

char	*print_type(enum e_type type)
{
	switch (type)
	{
		case WORD: return "WORD";
		case WHITE_SPACE: return "WHITE_SPACE";
		case S_QUOTE: return "S_QUOTE";
		case D_QUOTE: return "D_QUOTE";
		case PIPE_LINE: return "PIPE_LINE";
		case ENV: return "ENV";
		case REDIR_IN: return "REDIR_IN";
		case DREDIR_OUT: return "DREDIR_OUT";
		case HERE_DOC: return "HERE_DOC";
		case NEW_LINE: return "NEW_LINE";
		case ESCAPE: return "ESCAPE";
		case REDIR_OUT: return "REDIR_OUT";
	}
	return NULL;
}

void	print_token(t_lst *lst)
{
	t_token *tmp;

	tmp = lst->head;
	while (tmp)
	{
		printf("\'%s\'	 |	%d	 |	%s	 |	%s\n", tmp->content, tmp->len, 
			print_state(tmp->state), print_type(tmp->type));
		tmp = tmp->next;
	}
}