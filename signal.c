#include "minishell.h"

void handler_two_2(int signum)
{
    // DO nothing
}

void init_signal()
{
    //signal(SIGINT, handler());
    signal(SIGQUIT, handler_two_2);
}