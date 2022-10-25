#include "minishell.h"
typedef struct t_cmd{
    int     cmd_index;
    char    *cmd;
    char    **args;
    int     stdin_file;
    int     stdout_file;
    int     is_echo;
    struct s_shell *next;
} s_cmd;

s_cmd *init_cmd_node(void)
{
    s_cmd *cmd;

    cmd = (s_cmd *)malloc(sizeof(s_cmd *));
    cmd->cmd_index = -1;
    cmd->cmd = NULL;
    cmd->args = NULL;
    cmd->stdin_file = 0;
    cmd->stdout_file = 0;
    cmd->is_echo = 0;
    cmd->next = NULL;
    return cmd;
}
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

s_cmd *fill_created_node(NODE *cmd,s_cmd *tmp)
{
    tmp = (s_cmd *)malloc(sizeof(s_cmd *));
    tmp->cmd = cmd->type ;
    tmp->args = cmd->value;
    return(tmp);
}

void	push_back_cmd(s_cmd **lstcmd, s_cmd *new)
{
	t_list	*head;

	head = *lstcmd;
	if (*lstcmd == NULL)
		*lstcmd = new;
	else
	{
		while (head->next != NULL)
			head = head->next;
		head->next = new;
	}
}

void test(NODE *tmp)
{
    s_cmd *lstcmd;
    s_cmd *cmd;

    if(tmp->type == PIPE_CMD)
        tmp = tmp->next;
    else
    {
        push_back_cmd(lstcmd,fill_created_node(tmp,init_cmd_node()));
        tmp = tmp->next;
    }
}


//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

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