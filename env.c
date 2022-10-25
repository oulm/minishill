#include "minishell.h"

char **duplicate_env(char **env)
{
    char    **return_value;
    char    *dup_str;
    size_t    i;

    if (!env)
        return (NULL);
    i = 0;
    while (*(env + i))
        i++;
    return_value = malloc(((i + 1)* sizeof(char *)));
    if (!return_value)
        return (NULL);
    i = 0;
    while (*(env + i))
    {
        dup_str = ft_strdup(*(env + i));
        if (!dup_str)
        {
            *(return_value + i) = dup_str;
            free_double_ptr(return_value);
            return (NULL);
        }
        *(return_value + i) = dup_str;
        i++;
    }
    *(return_value + i) = 0;
    return (return_value);
}