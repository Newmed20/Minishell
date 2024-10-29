/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 01:08:05 by mjadid            #+#    #+#             */
/*   Updated: 2024/10/29 21:45:35 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_var(t_data *data, char *str)
{
	(void)data;
	int		i;
	int		j;
	int		start;
	char	*key;
	char	*value;

	i = 0;
	key = NULL;
	value = NULL;
	while (str[i] && str[i] != '=')
		i++;
	start = i++;
	j = i;
	while (str[j])
		j++;
	key = ft_substr(str, 0, i - 1);
	value = ft_substr(str, start + 1, j);
	printf("key %s\n", key);
	printf("value %s\n", value);
	return (0);
}

int	ft_export(t_data *data)
{
	t_env	*env;
	t_token	*token;
	char	*arg;

	arg = NULL;
	env = data->env_copy;
	token = data->lexer->tokens;
	if (token->next)
	{
		token = skip_spaces(token->next, 1);
		arg = ft_strdup(token->content);
	}
	if (!arg)
	{
		while (env)
		{
			printf("declare -x %s=\"%s\"\n", env->key, env->value);
			env = env->next;
		}
	}
	else
		check_var(data, arg);
	return (0);
}
