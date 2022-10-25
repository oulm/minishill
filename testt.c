#include<unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
int main()
{
    char *buffer;
    while (1)
    {
      buffer = readline("+");
      add_history(buffer);
    }
    return 0;
}