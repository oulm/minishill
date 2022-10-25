#include "../minishell.h"

// NOLEAKS
void ft_pwd()
{
    char    *tmp;

    tmp = getcwd(NULL, 0);
    if (tmp == NULL)
        perror(NULL);
    else
        ft_putendl_fd(tmp, 1);
    free_ptr(&tmp);
    exit_st = errno;
}