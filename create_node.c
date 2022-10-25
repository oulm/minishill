#include "minishell.h"

NODE    *create_pipe(char **str)
{
    NODE        *exc_cmd;
    PIPE_CMD    *tmp;
    t_value     *ptr;
    char        *tmp2;

    tmp2 = *str;
    while ((*tmp2 == ' ' || *tmp2 == '\t') && *tmp2)
        tmp2++;
    
    if (*tmp2 == '|')
        tmp2++;
    *str = tmp2;
    tmp = malloc(sizeof(PIPE_CMD));
    tmp->arg = strdup("|");
    ptr = malloc(sizeof(t_value));
    ptr->pipe_cmd = tmp;
    exc_cmd = malloc(sizeof(NODE));
    exc_cmd->value = ptr;
    return (exc_cmd);
}

/*
    > hna 3ndna allocation l EXEC_CMD
    > o 3ndna allocation l value li fiha EXEC_CMD
*/

t_value    *initialize_node_exec(char **ptr)
{
    EXEC_CMD *tmp;
    t_value  *data_cmd;

    tmp = malloc(sizeof(EXEC_CMD));
    tmp->argv = ptr;
    data_cmd = malloc(sizeof(t_value));
    data_cmd->exec_cmd = tmp;
    return (data_cmd);
}

/*
    > hna 3ndna allocation l double pointer ptr
    > 3nd allocation l NODE
*/
NODE    *create_exec(char **str, char c, char **env)
{
    char    **ptr;
    NODE    *exc_cmd;

    ptr = NULL;
    ptr = get_files(str, c, env);
    exc_cmd = malloc(sizeof(NODE));
    if (!exc_cmd)
    {
        printf("ERROR\n");
        exit(1);
    }
    exc_cmd->type = EXEC;
    exc_cmd->value = initialize_node_exec(ptr);
    return (exc_cmd);
}
