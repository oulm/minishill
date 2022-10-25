#include "minishell.h"

void print_declare_x(char **str)
{
    size_t  i;
    char    **split;
    char    *tmp;

    i = 0;
    while (*(str + i))
    {
        ft_putstr_fd("declare -x ", 1);
        split = ft_split(*(str + i), '=');
        if (!split)
        {
            ft_putendl_fd("Error\n with malloc()\n", 1);
            exit_st = 1;
        }
        tmp = ft_strrchr(*(str + i), '=');
        ft_putstr_fd(*(split + 0), 1);
        ft_putstr_fd("=\"", 1);
        ft_putstr_fd(tmp + 1 , 1);
        ft_putendl_fd("\"", 1);
        i++;
        if (split)
            free_double_ptr(split);
    }
}

// NOLEAKS
size_t number_of_var(char **env)
{
    size_t i;

    i = 0;
    while (*(env + i))
        i++;
    return (i);
}

// NOLEAKS
int check_valid_name(char *str)
{
    size_t i;

    if ((*str < 'A' || *str > 'Z') && (*str < 'a' || *str > 'z') && *str != '_')
    {
        write(2, "bash: export: `", 16);
        write(2, str, ft_strlen(str));
        write(2, "': not a valid identifier\n", 27);
        exit_st = 1;
        return (0);
    }
    i = 1;
    while (*(str + i))
    {
        if ((*(str + i) < 'A' || *(str + i) > 'Z') && (*(str + i) < 'a' || *(str + i) > 'z') && (*(str + i) < '0' || *(str + i) > '9') && *(str + i) != '_')
        {
            write(2, "bash: export: `", 16);
            write(2, str, ft_strlen(str));
            write(2, "': not a valid identifier\n", 27);
            exit_st = 1;
            return (0);
        }
        i++;
    }
    return (1);
}

// NOLEAKS
int check_valid_name_v1(char *str)
{
    size_t i;

    if ((*str < 'A' || *str > 'Z') && (*str < 'a' || *str > 'z') && *str != '_')
    {
        write(2, "bash: export: `", 16);
        write(2, str, ft_strlen(str));
        write(2, "': not a valid identifier\n", 27);
        exit_st = 1;
        return (0);
    }
    i = 1;
    while (*(str + i) && *(str + i) != '=')
    {
        if ((*(str + i) < 'A' || *(str + i) > 'Z') && (*(str + i) < 'a' || *(str + i) > 'z') && (*(str + i) < '0' || *(str + i) > '9') && *(str + i) != '_')
        {
            write(2, "bash: export: `", 16);
            write(2, str, ft_strlen(str));
            write(2, "': not a valid identifier\n", 27);
            exit_st = 1;
            return (0);
        }
        i++;
    }
    return (1);
}

// NOLEAKS
int check_if_exist(char *str, char ***env)
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
            {
                free(*(*env + i));
                *(*env + i) = NULL;
                return (i);
            }
        }
        i++;
    }
    return (-1);
}

int    check_and_print(NODE *first, char ***env, size_t *argv_size)
{
    if (!first || !env)
    {
        exit_st = 1;
        return (0);
    }
    else if (*(first->value->exec_cmd->argv + 1) == NULL)  // NOLEAKS
    {
        exit_st = 0;
        print_declare_x(*env);
        return (0);
    }
    *argv_size = number_of_var(first->value->exec_cmd->argv + 1);
    return (1);
}

// NOLEAKS
void    export(NODE *first, char ***env)
{
    char    **tmp;
    size_t  j;
    size_t  argv_size;

    exit_st = 0;
    if (!check_and_print(first, env, &argv_size))
        return ;
    j = 1;
    while (j <= argv_size)
    {
        if (check_valid_name_v1(*(first->value->exec_cmd->argv + j)))
        {
            tmp = ft_split(*(first->value->exec_cmd->argv + j), '=');
            if (tmp == NULL)
            {
                perror("bash: export:");
                exit_st = 1;
                return;
            }
            else
                add(*(tmp + 0), env, number_of_var(*env), *(first->value->exec_cmd->argv + j)); 
            free_double_ptr(tmp);
        }
        j++;
    }
}

// NOLEAKS
void    add(char *tmp, char ***env, int env_size, char *str)
{
    char    **ptr;
    size_t  len;
    int     exist;

    if (check_valid_name(tmp))
    {
        len = ft_strlen(tmp);
        if (*(str + len) == '=')
        {
            exist = check_if_exist(tmp, env);
            if (exist == -1)
            {
                ptr = ft_realloc(*env, env_size + 1);
                *(ptr + env_size) = ft_strdup(str);
                *env = ptr;
            }
            else
            {
                free(*(*env + exist));
                *(*env + exist) = ft_strdup(str);
            }
        }
    }
}