#include "minishell.h"

void    print_node(NODE *tmp)
{
    int i;

    i = 0;
    while (tmp)
    {
        if (tmp->type == EXEC)
        {
            i = 0;
            printf("EXEC {\n");
            while (*(tmp->value->exec_cmd->argv + i))
            {
                if (i == 0)
                {
                    printf("\tcommand : %s\n", *(tmp->value->exec_cmd->argv + i));
                }
                else
                    printf("\targs [%d]: %s\n", i, *(tmp->value->exec_cmd->argv + i));
                i++;
            }
            printf("}\n");
        }
        else if (tmp->type == PIPE)
        {
            printf("PIPE {\n");
            printf("\t%s\n", tmp->value->pipe_cmd->arg);
            //printf("|\n");
            printf("}\n");
        }
        else if (tmp->type == REDR)
        {
            printf("REDR {\n");
            printf("\ttype of rederaction: %c\n", tmp->value->redr_cmd->type_redr);
            int i = 0;
            while (*(tmp->value->redr_cmd->list_file_name + i))
            {
                printf("\tfile_name[%d]:[%s]\n", i + 1, *(tmp->value->redr_cmd->list_file_name + i));
                i++;
            }
            //printf("|\n");
            printf("}\n");
        }
        tmp = tmp->next;
    }
    
    
    
}