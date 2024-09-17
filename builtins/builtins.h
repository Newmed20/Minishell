/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjadid <mjadid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 05:34:29 by mjadid            #+#    #+#             */
/*   Updated: 2024/09/17 08:16:46 by mjadid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
# include "../libft/libft.h"


extern int g_exit_status;


typedef struct s_command
{
    char    *command; // The command name (e.g., "echo", "ls")
    char    *full_path; // The full path to the command (e.g., "/bin/echo", "/bin
    char    **args; // Array of arguments including the command
    int     arg_count; // Number of arguments
    t_list  *input_files; // For input redirection (<)
    t_list  *oa_files; // For output redirection (>)
    t_list  *heredoc_delimiters; // For heredoc (<<)
    t_list  *heredoc_content; // Content of heredoc
    int     pipe_out; // 1 if this command pipes to next, 0 otherwise
    struct s_command *next; // Pointer to next command in pipeline
}   t_command;


typedef struct s_exit
{
	int						exit_status;
}							t_check;

// t_check						g_check;

typedef struct s_environment
{
	char					*name;
	char					*data;
	struct s_environment	*next;
	struct s_environment	*prev;
	char					**environment_array;
	int						count;
}							t_environment;



#endif