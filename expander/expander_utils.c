/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:24:34 by abmahfou          #+#    #+#             */
/*   Updated: 2024/10/09 21:54:16 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_digit(char c, int pos, t_var_name *name, char *env_var)
{
	char	*res;
	char	*str;
	int		len;
	int		j;

	res = malloc(2 * sizeof(char));
	if (!res)
		return (NULL);
	res[0] = c;
	res[1] = '\0';
	name->name = res;
	free(res);
	j = pos++;
	len = 0;
	while (env_var[j] && env_var[j] != ' ')
	{
		len++;
		j++;
	}
	str = ft_substr(env_var, pos, len);
	return (str);
}

char	*get_full(char *prompt, t_var_name *var)
{
	int		i;
	int		j;
	int		start;
	char	*full;

	i = 0;
	start = var->pos;
	j = var->pos;
	while (prompt[j] && prompt[j] != ' ')
	{
		i++;
		j++;
	}
	full = ft_substr(prompt, start, i);
	return (full);
}
