#include "minishell.h"
t_cmd *init_cmd_node(void)
{
    t_cmd *cmd;

    cmd = (t_cmd *)malloc(sizeof(t_cmd *));
    cmd->cmd_index = -1;
    cmd->cmd = NULL;
    cmd->args = NULL;
    cmd->stdin_file = 0;
    cmd->stdout_file = 0;
    cmd->is_echo = 0;
    cmd->next = NULL;
    return cmd;
}
//$*************************************************

t_cmd   *convert_data_parser(NODE *head_parser)
{
    t_cmd   *cmds;
    t_cmd   *cmd;
    int         i = 0;

    cmds = NULL;
    if (head_parser != NULL)
    {
        // cmd = init_cmd_node();
        // push_back_cmd(&cmds, cmd);
        while (head_parser)
        {
            i++;
            printf ("[%p]{%d}\n", head_parser, i);
            // if (head_parser->type == PIPE)
            // {
            //     printf("PIPE\n");
            //     // cmd = init_cmd_node();
            //     // cmd->cmd_index = i;
            //     // push_back_cmd(&cmds, cmd);
            // }
            // else if (head_parser->type == EXEC)
            // {
            //     printf("EXEC\n");
            //     // cmd->args = NULL;
            // }
            // else if (head_parser->type == REDR)
            // {
            //     printf("REDR\n");
            // }
            // if (head_parser->next == NULL)
            //     break ;
            head_parser = head_parser->next;
        }
    }
    printf ("hello\n");
    while (cmds)
    {
        // printf ("CMD [%d]\n", cmds->cmd_index);
        cmds = cmds->next;
    }
    return (cmds);
}