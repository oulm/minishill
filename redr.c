#include "minishell.h"

void    print_error(char *str, char c)
{
    ft_putstr_fd(str, 2);
    ft_putchar_fd(c, 2);
    ft_putstr_fd("'\n", 2);
}

int    checkone(char **str)
{
    if (peek(*str) == '|' || peek(*str) == '<' || peek(*str) == '>') //check < again
    {
        print_error("bash: syntax error near unexpected token `", peek(*str));
        // hna no free ghadi traj3 null o function li 9bl hya li ghadi dir free
        return (1);
    }
    return (0);
}

NODE *create_redr_node(char **ptr_2, char type_redr)
{
    REDR_CMD    *tmp;
    t_value     *ptr;
    NODE        *exc_cmd;

    if (!ptr_2)
    {
         //ptr_2 = ft_realloc(ptr_2, 1);
        //*(ptr_2 + 0) = ft_strdup("\0");
        ft_putendl_fd("bash: syntax error near unexpected token `newline'", 2);
        return (NULL);
    }
    tmp = malloc(sizeof(REDR_CMD));
    tmp->list_file_name = ptr_2;
    tmp->type_redr = type_redr;
    ptr = malloc(sizeof(t_value));
    ptr->redr_cmd = tmp;
    exc_cmd = malloc(sizeof(NODE));
    exc_cmd->type = REDR;
    exc_cmd->value = ptr;
    return (exc_cmd);
}

/*********************************************************************/

NODE    *create_redr_3(char **str, char **env)
{
    NODE        *exc_cmd;
    char        *tmp_str;
    int         c;
    char        **ptr_2;

    tmp_str = *str;
    ptr_2 = NULL;
    if (*tmp_str == '>')
        tmp_str++;
    *str = tmp_str;
    if (*tmp_str == '>')
    {
        ft_putendl_fd("bash: syntax error near unexpected token `>'", 2);
        return (NULL);
    }
    if (peek(*str) == '|' || peek(*str) == '<' || peek(*str) == '>') //check < again
    {
        print_error("bash: syntax error near unexpected token `", peek(*str));
        return (NULL);
    }
    c = peek(*str);
    ptr_2 = get_files(str, c, env);
    exc_cmd = create_redr_node(ptr_2, '+');
    return (exc_cmd);
}

/*********************************************************************/

NODE    *create_redr_2(char **str, char **env)
{
    NODE        *exc_cmd;
    char        *tmp_str;
    int         c;
    char        **ptr_2;

    tmp_str = *str;
    ptr_2 = NULL;
    while ((*tmp_str == ' ' || *tmp_str == '\t') && *tmp_str)
        tmp_str++;
    if (*tmp_str == '>')
        tmp_str++;
    *str = tmp_str;
    if (*tmp_str == '>')
    {
        exc_cmd = create_redr_3(str, env);
        return (exc_cmd);
    }
    if (checkone(str))
        return (NULL);
    c = peek(*str);
    ptr_2 = get_files(str, c, env);
    exc_cmd = create_redr_node(ptr_2, '>');
    return (exc_cmd);
}

/*********************************************************************/

NODE    *create_redr(char **str, char **env)
{
    NODE        *exc_cmd;
    char        *tmp_str;
    int         c;
    char        **ptr_2;

    tmp_str = *str;
    ptr_2 = NULL;
    while ((*tmp_str == ' ' || *tmp_str == '\t') && *tmp_str)
        tmp_str++;
    if (*tmp_str == '<')
        tmp_str++;
    *str = tmp_str;
    if (*tmp_str == '<')
    {
        exc_cmd = create_redr_4(str, env);
        return (exc_cmd);
    }
    if (checkone(str))
        return (NULL);
    c = peek(*str);
    ptr_2 = get_files(str, c, env);
    exc_cmd = create_redr_node(ptr_2, '<');
    return (exc_cmd);
}


/*********************************************************************/

// NO LEAKS
int check_errors_rd4(char **str)
{
    //tmp_str = *str;
    if (**str == '<')
    {
        ft_putendl_fd("bash: syntax error near unexpected token `<'", 2);
        // hna no free ghadi traj3 null o function li 9bl hya li ghadi dir free
        return (1);
    }
    if (peek(*str) == '|' || peek(*str) == '<' || peek(*str) == '>') //check < again
    {
        ft_putstr_fd("bash: syntax error near unexpected token `", 2);
        ft_putchar_fd(peek(*str), 2);
        ft_putstr_fd("'\n", 2);
        // hna no free ghadi traj3 null o function li 9bl hya li ghadi dir free
        return (1);
    }
    return (0);
}

// NO LEAKS -P
NODE    *create_redr_4(char **str, char **env)
{
    NODE        *exc_cmd;
    char        *tmp_str;
    int         c;
    char        **ptr_2;

    tmp_str = *str;
    ptr_2 = NULL;
    if (*tmp_str == '<')
        tmp_str++;
    *str = tmp_str;
    if (check_errors_rd4(str))   
        return (NULL);
    c = peek(*str);
    ptr_2 = get_files(str, c, env);
    exc_cmd = create_redr_node(ptr_2, '-');
    if (ptr_2)
    {
        ft_heredoc(*(ptr_2 + 0), env, c);
    }
    return (exc_cmd);
}

void    free_ptr(char **ptr)
{
    if (!ptr)
        return ;
    if (*ptr)
        free(*ptr);
    *ptr = NULL;
}

int func3(char *str, char type, char **env, char **all_str)
{
    char *input;
    char *tmp;
    char *line;
    char *t;

    tmp = NULL;
    input = NULL;
    line = NULL;
    input = readline("> ");
    tmp = ft_strjoin(input, "\n");
    free_ptr(&input);
    if ((!ft_strncmp(tmp, str, ft_strlen(str))) && (*(tmp + ft_strlen(str)) == '\n'))
    {
        free_ptr(&tmp);
        return (0);
    }
    if (type != '"')
    {
        line = get_line(tmp, env);
        t = *all_str;
        *all_str = ft_strjoin(*all_str, line);
        free_ptr(&t);
        free_ptr(&line);
    }
    else
    {
        t = *all_str;
        *all_str = ft_strjoin(*all_str, tmp);
        free_ptr(&t);
    }
    free_ptr(&tmp);
    return (1);
}

void    ft_heredoc(char *str, char **env, char type)
{
    int     fd;
    char    *all_str;

    fd = open("tmp1.txt", O_WRONLY | O_CREAT);
    if (fd == -1)
    {
        perror("bash: open: ");
        return ;
    }
    all_str = ft_strdup("\0");
    while (1)
    {
        if (!func3(str, type, env, &all_str))
            break ;
    }
    //all_str = ft_strjoin(all_str, "\0");
    write(fd, all_str, ft_strlen(all_str));
    free_ptr(&all_str);
    close(fd);
}

void func1(char *tmp, int *i, int *size, char **env)
{
    char    *var_name;
    char    *value_var;
    int     len_string;

    var_name = get_name_variable(tmp + *i, 0);
    if (*var_name == '\0')
    {
        *size += 1;
        *i+= 1;
    }
    else 
    {
        len_string = ft_strlen(var_name);
        *i += len_string + 1;
        value_var = get_value_variable(var_name, env);
        if (value_var)
            *size = *size + ft_strlen(value_var);
        free_ptr(&value_var);
    }
    free_ptr(&var_name);
}

//NO LEAKS -P (IN)
int get_size_of_line(char *tmp, char **env)
{
    int     i;
    int     size;

    i = 0;
    size = 0;
    while (*(tmp + i))
    {
        if (*(tmp + i) == '$')
            func1(tmp, &i, &size, env);
        else
        {
            size++;
            i++;
        }
    }
    return (size);
}

void func2(char *tmp, int *i, char *return_value, int *j, char **env)
{
    char    *var_name;
    char    *value_var;
    int     len_string;
    int     k;

    var_name = get_name_variable(tmp + *i, 0);
    if (*var_name == '\0')
    {
        *(return_value + (*j)++) = '$';
        (*i)++;
    }
    else
    {
        len_string = ft_strlen(var_name);
        *i += len_string + 1;
        value_var = get_value_variable(var_name, env);
        if (value_var)
        {
            k = 0;
            while (*(value_var + k))
                *(return_value + (*j)++) = *(value_var + k++);
        }
        //free_ptr(&value_var);
    }
    //free_ptr(&var_name);
}

//NO LEAKS -P (IN)
char *get_line(char *tmp, char **env)
{
    int     i;
    int     j;
    int     size;
    char    *return_value;

    size = 0;
    return_value = NULL;
    size = get_size_of_line(tmp, env);
    return_value = malloc(size * sizeof(char) + 1);
    if (!return_value)
    {
        perror("bash: ");
        return (NULL);
    }
    i = 0;
    j = 0;
    while (*(tmp + i))
    {
        if (*(tmp + i) == '$')
            func2(tmp, &i, return_value, &j, env);
        else
            *(return_value + j++) = *(tmp + i++);
    }
    *(return_value + j) = '\0';
    return (return_value);
}