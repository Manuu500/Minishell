/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivas-q <arivas-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:05:28 by arivas-q          #+#    #+#             */
/*   Updated: 2025/10/30 19:00:38 by arivas-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../"
#include "../minishell.h"
#include "exe.h"
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

/* ------------------------ helpers locales ------------------------ */

static char *get_env_value(char **envp, const char *key)
{
    size_t klen;
    int i;

    if (!envp || !key)
        return NULL;
    klen = strlen(key);
    i = 0;
    while (envp[i])
    {
        if (strncmp(envp[i], key, klen) == 0 && envp[i][klen] == '=')
            return envp[i] + klen + 1;
        i++;
    }
    return NULL;
}

static char *join_path_cmd(const char *dir, const char *cmd)
{
    size_t len;
    char *p;

    if (!dir || !cmd)
        return NULL;
    len = strlen(dir) + 1 + strlen(cmd) + 1;
    p = (char *)malloc(len);
    if (!p)
        return NULL;
    snprintf(p, len, "%s/%s", dir, cmd);
    return p;
}


/* Construye argv desde una secuencia de TOKEN_WORD empezando en token.
   No atraviesa pipes ni redirecciones. Devuelve NULL en error. */
static char **make_argv_view_from_tokens(t_token *token)
{
    size_t count = 0;
    t_token *cur = token;
    char **argv;
    size_t i;

    while (cur && cur->type == TOKEN_WORD)
    {
        count++;
        cur = cur->next;
    }
    if (count == 0)
        return NULL;
    argv = (char **)malloc(sizeof(char *) * (count + 1));
    if (!argv)
        return NULL;
    i = 0;
    cur = token;
    while (cur && cur->type == TOKEN_WORD)
    {
        argv[i++] = cur->value; // sin duplicar, solo apuntamos
        cur = cur->next;
    }
    argv[i] = NULL;
    return argv;
}

/* ------------------------ API ------------------------ */

int execute_external_command(char **argv, char **envp)
{
    pid_t pid;
    int status;

    if (!argv || !argv[0])
        return 1;

    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return 1;
    }
    if (pid == 0)
    {
        /* child */
        if (strchr(argv[0], '/'))
        {
            execve(argv[0], argv, envp);
            perror("execve");
            _exit(127);
        }
        /* Buscar en PATH */
        {
            char *path = get_env_value(envp, "PATH");
            if (!path)
            {
                fprintf(stderr, "minishell: PATH not set\n");
                _exit(127);
            }
            char **parts = ft_split(path, ':');
            if (!parts)
                _exit(127);
            for (int i = 0; parts[i]; i++)
            {
                char *try_path = join_path_cmd(parts[i], argv[0]);
                if (!try_path)
                    continue;
                execve(try_path, argv, envp);
                free(try_path);
            }
            /* no se encontró */
            fprintf(stderr, "%s: command not found\n", argv[0]);
            for (int i = 0; parts[i]; i++)
                free(parts[i]);
            free(parts);
            _exit(127);
        }
    }
    /* parent */
    if (waitpid(pid, &status, 0) < 0)
    {
        perror("waitpid");
        return 1;
    }
    if (WIFEXITED(status))
        return WEXITSTATUS(status);
    if (WIFSIGNALED(status))
        return 128 + WTERMSIG(status);
    return 1;
}

int command_dispatcher(t_token *token, t_minishell *ms)
{
    char **argv;

    if (!token || !ms)
        return 1;

    if (token->type != TOKEN_WORD)
        return 0; /* nada que ejecutar */

    if (is_builtin(token->value))
		builtin_dispatcher(t_token	token);

    argv = make_argv_view_from_tokens(token);
    if (!argv)
        return 1;

    int status = execute_external_command(argv, ms->envp);
    free(argv); // liberamos solo el contenedor, no las cadenas
    return status;
}