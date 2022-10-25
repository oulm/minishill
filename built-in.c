#include "minishell.h"

NODE    *first_node(NODE *top)
{
    if (!top)
        return (NULL);
    while (top->prev)
        top = top->prev;
    return (top);
}

void    check_built_in(NODE *top, char ***env)
{
    NODE    *first;
    size_t  i;
    char    *buf;

    if (!top)
        return ;
    
    first = first_node(top);
    if (!first)
        return ;
        
    if (first->type == EXEC)
    {
        if ((!ft_strncmp(*(first->value->exec_cmd->argv), "exit", 5)))
        {
            if ((first->next == NULL) && *(first->value->exec_cmd->argv + 1) == NULL)
            {
                free_node(first);
                free_double_ptr(*env);
                ft_putendl_fd("exit", 1);
                exit(0);
            }
            else
            {
                // Do nothing
            }
        }
        else if ((!ft_strncmp(*(first->value->exec_cmd->argv), "env", 4)))
        {
            if (*(first->value->exec_cmd->argv + 1) == NULL)
            {
                i = 0;
                while (*(*env + i))
                {
                    printf("%s\n", *(*env + i));
                    i++;
                }
            }
            else
            {
                // Do nothing
            }
        }
        else if ((!ft_strncmp(*(first->value->exec_cmd->argv), "pwd", 4)))
        {
            ft_pwd();
        }
        else if ((!ft_strncmp(*(first->value->exec_cmd->argv), "export", 7)))
        {
            export(first, env);
        }
        else if ((!ft_strncmp(*(first->value->exec_cmd->argv), "unset", 6)))
        {
            unset(first, env);
        }
        else if ((!ft_strncmp(*(first->value->exec_cmd->argv), "clear", 6)))
        {
            clear(first, env);
        }
        else if ((!ft_strncmp(*(first->value->exec_cmd->argv), "echo", 5)))
        {
            echo(first, env);
        }
        else if ((!ft_strncmp(*(first->value->exec_cmd->argv), "cd", 3)))
        {
            ft_cd(first, env);
        }
    }
    
}