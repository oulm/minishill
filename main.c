#include "minishell.h"

void    free_double_ptr(char **ptr)
{
    size_t i;

    if (!ptr)
        return ;
    i = 0;
    while (*(ptr + i))
    {
        free(*(ptr + i));
        i++;
    }
    free(ptr);
}

char *read_line()
{
    char    *buffer;

    buffer = NULL;
    buffer = readline("[+]");
    add_history(buffer);
    return (buffer);
    
}

void    add_node(NODE *cmd, NODE **top)
{
    cmd->prev = *top;
    cmd->next = NULL;
    if (*top)
        (*top)->next = cmd;
    *top = cmd;
}

// NO ALLOCATION IN THIS FUNCTION
NODE *parsing(char **string, char **env)
{
    char    c;
    NODE    *cmd;
    NODE    *top;

    top = NULL;
    c = peek(*string);
    while (c != '\n' && c != '\0')
    {
        if (c == '|')
        {
            if (top == NULL) // ya3ni pipe ma9bl mnnha ta7aja
            {
                print_error("bash: syntax error near unexpected token `", '|');
                return (NULL);
            }
            cmd = create_pipe(string);
            c = peek(*string);
            if (c == '|')
            {
                print_error("bash: syntax error near unexpected token `", c);
                return (NULL);
            }
            cmd->type = PIPE;
        }
        else if (c == '<')
        {
            cmd = create_redr(string, env);
        }
        else if (c == '>')
        {
            cmd = create_redr_2(string, env);
        }
        else
        {
            cmd = create_exec(string, c, env);
        }
        if (cmd == NULL)
        {
            // code
            return (NULL);
        }
        add_node(cmd, &top);
        //print_node(top);
        c = peek(*string);
    }
    if (!top)
        return (NULL);
    if (top->type == PIPE)
    {
        print_error("Error\nCommand not found after `", '|');
        /* hna khass free */
        return (NULL);
    }
    //print_node(top);
    return (top);
}

void    print_prompt(char **env)
{
    int i;
    char **tmp;
    i = 0;

    printf("[+]");
    /*
    while (*(env + i))
    {
        //printf("[%s]\n", *(env + i));
        if (!ft_strncmp(*(env + i), "USER", 4))
        {
            //printf("ok");
            tmp = ft_split(*(env + i), '=');
            printf("\033[0;31m");
            printf("%s$", *(tmp + 1));
            printf("\033[0;37m");
            break;
        }
        i++;
    }
    */
}

void free_node(NODE *first)
{
    NODE *tmp;

    tmp = first;
    while (first)
    {
        tmp = first->next;
        if (first->type == EXEC)
        {
            free_double_ptr(first->value->exec_cmd->argv);
            free((first->value->exec_cmd));
            free((first->value));
            free(first);
        }
        else if (first->type == PIPE)
        {
            free_ptr(&(first->value->pipe_cmd->arg));
            free((first->value->pipe_cmd));
            free((first->value));
            free(first);
        }
        else if (first->type == REDR)
        {
            free_double_ptr(first->value->redr_cmd->list_file_name);
            free((first->value->redr_cmd));
            free((first->value));
            free(first);
        }
        //free(first->value);
        //free(first);
        first = tmp;
    }
}

void print(NODE *top)
{
    NODE *first;

    if (!top)
        return ;
    first = first_node(top);
    if (!first)
        return ;
    print_node(first);
}

void update(NODE* node, size_t number)
{
    NODE*   tmp;
    size_t  size;
    char    **ptr;
    size_t  i;
    char*   str;
    char    **ptr_2;

    tmp = node->prev;
    size = number_of_var(tmp->value->exec_cmd->argv);
    number -= 1;
    //ptr_2 = ft_realloc(tmp->value->exec_cmd->argv, size + number);
    //ptr_2[size + number] = NULL;
    ptr_2 = ft_calloc(sizeof(char *), (size + number + 1));
    memcpy(ptr_2, tmp->value->exec_cmd->argv, size * sizeof(char *));
    free(tmp->value->exec_cmd->argv);
    tmp->value->exec_cmd->argv = ptr_2;

    i = 0;
    while (i < number)
    {
        str = ft_strdup(*(node->value->redr_cmd->list_file_name + i + 1));
        *(tmp->value->exec_cmd->argv + size + i) = str;
        i++;
    }
    *(tmp->value->exec_cmd->argv + size + i) = 0;
    i = 1;
    while (*(node->value->redr_cmd->list_file_name + i))
    {
        free(*(node->value->redr_cmd->list_file_name + i));
        *(node->value->redr_cmd->list_file_name + i) = NULL;
        i++;
    }
}

void update_and_create(NODE* node, size_t number)
{
    NODE*   tmp;
    size_t  size;
    char    **ptr;
    size_t  i;
    char*   str;
    NODE    *exc_cmd;

    ptr = malloc((sizeof(char *)) * (number + 1));
    if (!ptr)
        return ;
    i = 0;
    while (*(node->value->redr_cmd->list_file_name + i + 1))
    {
        str = ft_strdup(*(node->value->redr_cmd->list_file_name + i + 1));
        *(ptr + i) = str;
        i++;
    }
    *(ptr + i) = 0;
    exc_cmd = malloc(sizeof(NODE));
    if (!exc_cmd)
    {
        printf("ERROR\n");
        exit(1);
    }
    exc_cmd->type = EXEC;
    exc_cmd->value = initialize_node_exec(ptr);
    if (node->prev == NULL)
    {
        node->prev = exc_cmd;
        exc_cmd->next = node;
        exc_cmd->prev = NULL;
    }
    else
    {
        tmp = node->prev;
        (node->prev)->next = exc_cmd;
        exc_cmd->next = node;
        exc_cmd->prev = tmp;
    } 
    i = 1;
    while (*(node->value->redr_cmd->list_file_name + i))
    {
        free(*(node->value->redr_cmd->list_file_name + i));
        *(node->value->redr_cmd->list_file_name + i) = NULL;
        i++;
    }
}

void check_redr(NODE* first)
{
    NODE* tmp;
    size_t  number;

    if (!first)
        return ;
    while (first)
    {
        if (first->type == REDR)
        {
            number = number_of_var(first->value->redr_cmd->list_file_name);
            if (first->prev)
            {
                //printf("1\n");
                
                tmp = first->prev;
                if (number > 1 && tmp->type == EXEC)
                    update(first, number);
                else if (tmp->type == PIPE && number > 1)
                    update_and_create(first, number);

            }
            else if (!first->prev && number > 1)
            {
                update_and_create(first, number);
            }
            
        }
        first = first->next;
    }
}



int main(int argc, char const *argv[], char **env)
{
    char    *input;
    char    **parsed;
    char    **dup_env;
    int     i;
    NODE    *top;
    top = NULL;
    NODE *tmp;
    char    *t;

    dup_env = NULL;
    dup_env = duplicate_env(env);
    if (!dup_env)
    {
        write(2, "Error\n with env!\n", 18);
        return(1);
    }
    exit_st = 0;
    while (true)
    {
        //print_prompt(dup_env);
        input = read_line();
        t = input;
        top = parsing(&input, dup_env);
        tmp = first_node(top);
        check_redr(tmp);
        print(top);
        free(t);
        check_built_in(top, &dup_env);
        free_node(tmp);
        //execution(tmp, env);
        //free maktsda9sh hit kan7arko ptr
        //free(t);
    }
    return 0;
}
