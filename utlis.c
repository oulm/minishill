#include "minishell.h"

char *name_and_value(char **str, char **env)
{
    char *start;
    int k;
    int len_string;
    char *var_name;
    char *value_var;

    k = 0;
    start = *str;
    var_name = get_name_variable(start, k);
    len_string = ft_strlen(var_name);
    k += len_string + 1;
    value_var = get_value_variable(var_name, env);
    if (!value_var)
        value_var = ft_strdup("\0");
    start = start + k;
    *str = start;
    free_ptr(&var_name);
    return (value_var);
}

char *get_new_str(char **str, char **env)
{
    char *start;
    char *new_str;

    if (**str == '$' && *(*str + 1) == '?')
    {
        start = *str;
        start = start + 2;
        new_str = get_value_of_exit();
        *str = start;
    }
    else if (**str == '$' && (*(*str + 1) == '\0' || *(*str + 1) == ' ' || *(*str + 1) == '\t'))
    {
        start = *str;
        start = start + 1;
        new_str = ft_strdup("$");
        *str = start;
    }
    else
        new_str = name_and_value(str, env);
    return (new_str);
}

char *function_three(char **str, char **env, char c)
{
    char *full_str;
    char *new_str;
    int len;
    char *t;

    full_str = ft_strdup("\0");
    if (c == '"')
        new_str = handle_qoutes_string(str, '"', env);
    else
        new_str = handle_single_string(str, '\'', env);  // had kadir return new str ot9dar dir return 7ta l null so khasseha thandla
    t = full_str;
    full_str = ft_strjoin(full_str, new_str);
    free_ptr(&t);
    free_ptr(&new_str);
    while ((**str == '\'' || **str == '"') || (**str != ' ' && **str != '\t' && **str != '<' && **str != '>' && **str != '|' && **str != '\n'&& **str != '\0'))
    {
        if (**str == '"')
        {
            new_str = handle_qoutes_string(str, '"', env);
            t = full_str;
            full_str = ft_strjoin(full_str, new_str);
            free_ptr(&t);
            free_ptr(&new_str);
        }
        else if (**str == '\'')
        {
            new_str = handle_single_string(str, '\'', env);
            t = full_str;
            full_str = ft_strjoin(full_str, new_str);
            free_ptr(&t);
            free_ptr(&new_str);
        }
        else if (**str == '$')
        {
            new_str = get_new_str(str, env);
            t = full_str;
            full_str = ft_strjoin(full_str, new_str);
            free_ptr(&t);
            free_ptr(&new_str);
        }
        else
        {
            len = get_len_of_string(str); // NO LEAKS
            new_str = get_str(str, len);    // khassk thandlil l7ala fash kadir return null
            t = full_str;
            full_str = ft_strjoin(full_str, new_str);
            free_ptr(&t);
            free_ptr(&new_str);
        }
    }
    return (full_str);
}

/***************************************************************************************************/

/*-------------------------------------------------------------------------------------------------*/

char *name_and_value_v(char **str, char **env, char **start)
{
    int k;
    int len_string;
    char *var_name;
    char *new_str;
    char *value_var;

    k = 0; // hadi makantsh
    var_name = NULL;
    value_var = NULL;
    var_name = get_name_variable(*start, k);
    len_string = ft_strlen(var_name);
    k += len_string + 1;
    if (len_string == 0)
        new_str = ft_strdup("$");
    else
    {
        value_var = get_value_variable(var_name, env);
        if (!value_var)
            new_str = ft_strdup("\0");
        else
            new_str = value_var;
    }
    free_ptr(&var_name);
    *start = *start + k;
    return (new_str);
}

char *get_value_of_exit()
{
    char *tmp;

    tmp = ft_itoa(exit_st);
    return (tmp);
}

char *get_new_str_v(char **str, char **env, char **start)
{
    char    *new_str;
    int     k;
    char    *var_name;
    char    *value_var;
    int     len_string;
    // hna n9adro nzidr 7ta == $
    if (**start == '$' && (*(*start + 1) == '\0' || *(*start + 1) == ' ' || *(*start + 1) == '\t'))
    {
        *start = *start + 1;
        new_str = ft_strdup("$");
    }
    else if (**start == '$' && *(*start + 1) == '?')
    {
        *start = *start + 2;
        new_str = get_value_of_exit();
    }
    else
        new_str = name_and_value_v(str, env, start);
    return (new_str);
}

char *fn_check_exec(char **str, char **env, int *v, char *end, char **start)
{
    char    *new_str;
    //int     k;
    int     len;
    char    *var_name;
    char    *value_var;
    int     len_string;

    //k = 0;
    if (!(*v))
    {
        //len = get_len_v(start, end);                          // hadi 7aydnaha
        //new_str = get_string_move_start(&start, end, len);    // hadi 7aydnaha
        len = get_len_v_2(*start, end);
        new_str = get_string_move_start_2(start, end, len);
    }
    else if (*v == 1)
    {
        len = get_len_q_v1_new(*start, end, env); // hado rah bdalna fihom
        new_str = get_string_q_v1_and_move(start, end, len, env); // hado rah bdalna fihom
    }
    else if (*v == 2)
    {
        len = get_len_q_v4(*start);
        new_str = get_string_q_v4(start, len);
        //len = get_len_q_v2(start, end);               // hadi 7aydnaha
        //new_str = get_string_q_v2(&start, end, len);  // hadi 7aydnaha
    }
    else if (*v == 4)
        new_str = get_new_str_v(str, env, start);       // for now 7aydna leaks
    return (new_str);
}

void    set_v(char *start, int *v)
{
    if (*start == '\'')
        *v = 2;
    else if (*start == '"')
        *v = 1;
    else if (*start == ' ' || *start == '\t' || *start == '\n' || *start == '\0')
        *v = 5;
    else if (*start == '$')
        *v = 4;
    else
        *v = 0;
}

char *function_four(char **str, char **env)
{
    int     k;
    char    *start;
    char    *end;
    int     v;
    char    *full_str;
    char    *new_str;
    char    *tmp;

    k = 0;
    start = *str;
    while (*(start + k) == ' ' || *(start + k) == '\t')
        k++;
    start = start + k;
    end = start;
    get_end(&end);
    v = 4;
    full_str = ft_strdup("\0");
    while (*start != ' ' && *start != '\t' && *start != '\0' && *start != '>' && *start != '<' && *start != '|')
    {
        tmp = full_str;
        new_str = fn_check_exec(str, env, &v, end, &start);
        full_str = ft_strjoin(full_str, new_str);
        set_v(start, &v);
        free_ptr(&new_str);
        free_ptr(&tmp);
        if (v == 5)
            break ;
    }
    *str = start;
    return (full_str);
}

/*-------------------------------------------------------------------------------------------------*/

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

char *fn_check_exec_v(char **str, char **env, int *v, char *end, char **start)
{
    int len;
    char *new_str;

    if (!(*v))
    {
        //len = get_len_v(start, end);
        //new_str = get_string_move_start(&start, end, len);
        len = get_len_v_2(*start, end);                             // NO LEAKS
        new_str = get_string_move_start_2(start, end, len);         // kain allocation l new_str
    }
    else if (*v == 1)
    {
        //len = get_len_q_v1_new(start, end, env);
        //new_str = get_string_q_v1_and_move(&start, end, len, env);
        len = get_len_q_v1_new_2(*start, env);                      // fiha leaks dyl var_name o value_name
        new_str = get_string_q_v1_and_move_2(start, len, env);      // kaina allocation dyl new_str
    }
    else if (*v == 2)
    {
        //len = get_len_q_v2(start, end);
        len = get_len_q_v4(*start);                                 // NO LEAKS
        new_str = get_string_q_v4(start, len);                      // kain allocation l new_str
        //new_str = get_string_q_v2(&start, end, len);
        //new_str = get_string_q_v4(&start, len);
    }
    else if (*v == 4)
        new_str = get_new_str_v(str, env, start);
    return (new_str);
}


/*
    > kain allocaition l full_str
    > Scanner no leaks
*/
char *function_five(char **str, char **env)
{
    char *full_str;
    char *new_str;
    char *tmp;
    int v;
    char *start;
    char *end;

    v = Scanner(str, &start, &end); // NO LEAKS
    full_str = ft_strdup("\0"); 
    //hadi hya li kant fwlele !!!!!! 
    //while (start < end && *start != ' ' && *start != '\t')
    //while (*start != '\0' && *start != ' ' && *start != '\t')
    while (*start != ' ' && *start != '\t' && *start != '\0' && *start != '>' && *start != '<' && *start != '|')
    {
        tmp = full_str;
        new_str = fn_check_exec_v(str, env, &v, end, &start);
        full_str = ft_strjoin(full_str, new_str);
        free_ptr(&new_str);
        free_ptr(&tmp);
        set_v(start, &v);
        if (v == 5)
            break ;
    }
    *str = start;
    return (full_str);
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

char    **get_files(char **str, char c, char **env)
{
    char    **ptr;
    int     i;
    char    *full_str;

    i = 1;
    ptr = NULL;
    full_str = NULL;
    //full_str = ft_strdup("\0"); // hadi khasseha t7ayd wa9ila
    while (c && (c != ' ' && c != '\t') && c != '\n' && c != '|' && c!= '<' && c != '>')
    {
        if (c == '"')
            full_str = function_three(str, env, c);
        else if (c == '\'')
            full_str = function_three(str, env, c);
        else if (c == '$')
            full_str = function_four(str, env);
        else
            full_str = function_five(str, env);
        ptr = ft_realloc(ptr, i + 1);
        *(ptr + i - 1) = full_str;
        i++;
        c = peek(*str);
    }
    return (ptr);
}