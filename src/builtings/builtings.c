/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtings.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivas-q <arivas-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:04:53 by arivas-q          #+#    #+#             */
/*   Updated: 2025/10/30 18:56:09 by arivas-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int strcmp(char *str1, char *str2)
{
    int len1;
    int len2;
    int i;
    
    i = 0;
    if(len1 == len2)
    {
		while(str1[i] && str2[i] && str1[i] == str2[i])
			i++;
		if(str1[i] == '\0')
			return (1);
    }
	return (0);
}

int is_builtin(t_token name)
{
    if(strcmp(name.value, "echo"))
		return(1);
	else if(strcmp(name.value, "cd"))
		return(1);
	else if(strcmp(name.value, "pwd"))
		return(1);
	else if(strcmp(name.value, "export"))
		return (1);
	else if(strcmp(name.value, "unset"))
		return (1);
	else if(strcmp(name.value, "env"))
		return (1);
	else if(strcmp(name.value, "exit"))
		return (1);
	else
		return (0);
}

void	builting_dispatcher(t_token name)
{
	if(strcmp(name.value, "echo"))
		builtin_echo(t_token name);
	else if(strcmp(name.value, "cd"))
		builtin_cd(t_token cd);
	else if(strcmp(name.value, "pwd"))
		builtin_pwd(t_token name);
	else if(strcmp(name.value, "export"))
		builtin_export(t_token name);
	else if(strcmp(name.value, "unset"))
		builtin_unset(t_token name)
	else if(strcmp(name.value, "env"))
		builtin_env(t_token name);
	else if(strcmp(name.value, "exit"))
		builtin_exit(t_token name);
	else
		return (0);
}