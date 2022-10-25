#include "minishell.h"

void clear(NODE *first, char ***env)
{
    int id;

    char *path = "/usr/bin/clear";
    char *argv[] = {"clear", NULL};
    char *envp[] = {NULL};

    id = fork();
    if (id == 0)
    {
        if (execve(path, argv, *env) == -1)
            perror("bash :");
        return ;
    }
    
}