#include "minishell.h"

/*
    *chof wash hadi fiha shi error khasso ithandla

*/

int ft_env(char **env)
{
    size_t  i;

    if (!env)
        return (0);
    i = 0;
    while (*(env + i))
    {
        printf("%s\n", *(env + i));
        i++;
    }
    return (0);
}