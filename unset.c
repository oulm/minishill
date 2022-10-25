#include "minishell.h"

// NOLEAKS
int check_if_exist_v1(char *str, char ***env)
{
    size_t  i;
    size_t  len_str;

    i = 0;
    len_str = ft_strlen(str);
    while (*(*env + i))
    {
        if (!ft_strncmp(*(*env + i), str, len_str))
        {
            if (*(*(*env + i) + len_str) == '=')
                return (i);
        }
        i++;
    }
    return (-1);
}

void check_and_delete(NODE *first, char ***env, size_t argv_size)
{
    size_t  j;
    int     exist;
    size_t  env_size;

    j = 1;
    while (j <= argv_size)
    {
        if (check_valid_name(*(first->value->exec_cmd->argv + j)))
        {
            exist = check_if_exist_v1(*(first->value->exec_cmd->argv + j), env);
            env_size = number_of_var(*env);
            if (exist != -1)
            {
                free(*(*env + exist));
                while (exist < env_size - 1)
                {
                    *(*env + exist) = *(*env + exist + 1);
                    exist++;
                }
                *(*env + exist) = NULL;
            }
        }
        j++;
    }
}

// NOLEAKS
void unset(NODE *first, char ***env)
{
    size_t  j;
    size_t  argv_size;

    exit_st = 0;
    if (*(first->value->exec_cmd->argv + 1) == NULL || !first || ! env)
        return ;
    argv_size = number_of_var(first->value->exec_cmd->argv + 1);
    check_and_delete(first, env, argv_size);
}