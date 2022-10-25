#include "minishell.h"

void    free_double_ptr(char **ptr)
{
    size_t i;

    i = 0;
    if (!ptr)
        return ;
    
    while (*(ptr + i))
    {
        free(*(ptr + i));
        i++;
    }
    free(ptr);
    return ;
}

void free_node(NODE *top)
{
    NODE *tmp;

    if (!top)
        return ;
    
    while (top)
    {
        tmp = top->next;
        if (top->type == EXEC)
        {
            free_double_ptr(top->value->exec_cmd->argv);
            free(top->value->exec_cmd);
            free(top->value);
            free(top);
        }
        else if (top->type == PIPE)
        {
            /* code */
        }
        else if (top->value == REDR)
        {
            /* code */
        }
        top = tmp;
    }
     
}