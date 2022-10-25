#include "minishell.h"

void echo(NODE *first, char ***env)
{
    size_t i;
    size_t v;

    i = 1;
    v = 0;
    if (*(first->value->exec_cmd->argv + 1) == NULL)
    {
        write(1, "\n", 1);
        return ;
    }
    if (!ft_strncmp(*(first->value->exec_cmd->argv + i), "-n", 3))
    {
        i++;
        v = 1;
    }
    while (*(first->value->exec_cmd->argv + i))
    {
        ft_putstr_fd(*(first->value->exec_cmd->argv + i), 1);
        i++;
        if (*(first->value->exec_cmd->argv + i))
            ft_putstr_fd(" ", 1);
    }
    if (!v)
        write(1, "\n", 1);
}