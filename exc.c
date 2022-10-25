#include "minishell.h"

void execution(NODE* first, char **env)
{
    int     fd;
    char    *cmd;

    
    fd = fork();
    
    if (fd == 0)
    {
        cmd = *(first->value->exec_cmd->argv);
        if (execve(cmd, first->value->exec_cmd->argv, env) == -1)
        {
            perror ("bash: ");
            //exit_s = 127; // hadi khasseha tbadl
        }
        
    }
    
}