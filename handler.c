#include "minishell.h"

char    *handle_single_string(char **str, char c, char **env)
{
    char *tmp;
    char *new_str;
    int i;
    int j;

    tmp = *str;
    while ((*tmp == ' ' || *tmp == '\t') && *tmp)
        tmp++;
    tmp++;
    i = 0;
    while (*(tmp + i) != c) //hadi khassha tbadle l ' ' and '\t'
    {
        i++;
    }
    if (i == 0)
    {
        *str = tmp + i + 1;
        return (ft_strdup("\0"));
    }
    
    *str = tmp + i + 1;
    new_str = malloc(sizeof(char) * i + 1);
    j = 0;
    while (j < i)
    {
        *(new_str + j) = *(tmp + j);
        j++;
    }
    
    *(new_str + j) = 0;
    return (new_str);
}

char    *get_name_variable(char *tmp, int i)
{
    int j;
    char *str;
    int c;
    int d;

    j = 0;
    i++;
    while (*(tmp + i + j) != '\n' && *(tmp + i + j) != ' ' && *(tmp + i + j) != '\''
        && *(tmp + i + j) != '\t' && *(tmp + i + j) != '\\' && *(tmp + i + j) != '"'
        && *(tmp + i + j) != '\0' && *(tmp + i + j) != '$') // dyl \0 ghi zdnaha
    {
        j++;
    }
    str = malloc(sizeof(char) * j + 1);
    d = 0;
    while(d < j)
    {
        *(str + d) = *(tmp + i + d);
        d++;
    }
    *(str + d) = 0;
    return (str);
}

int get_lenght_variable(char *tmp)
{
    int j;

    j = 0;
    while (*(tmp + j) != '\n' && *(tmp + j) != ' ' && *(tmp + j) != '\''
        && *(tmp + j) != '\t' && *(tmp + j) != '\\' && *(tmp + j) != '"'
        && *(tmp + j) != '\0' && *(tmp + j) != '$') // dyl \0 ghi zdnaha
    {
        j++;
    }
    return (j);
}

char *get_value_variable(char *var_name, char **env)
{
    size_t len;
    size_t i;
    char    *tmp;
    char    **ptr;
    char    *tmp2;

    len = ft_strlen(var_name);
    i = 0;
    while (*(env + i))
    {
        if (!ft_strncmp(*(env + i), var_name, len) && *(*(env + i) + len) == '=')
        {
            //ptr = ft_split(*(env + i), '=');
            tmp2 = ft_strchr(*(env + i), '=');
            tmp = ft_strdup(tmp2 + 1);
            //tmp = *(ptr + 1);
            return (tmp);
        }
        i++;
    }
    return (NULL);
}

char    *handle_qoutes_string(char **str, char c, char **env)
{
    char *tmp;
    char *new_str;
    int  i;
    int  j;
    int  d;
    int t;
    int len;
    int len_string;
    int len_malloc;
    char *var_name;
    char *value_var;
    char **variables;
    int     f;
    int size;
    int number;

    tmp = *str;
    while ((*tmp == ' ' || *tmp == '\t') && *tmp)
        tmp++;
    tmp++;

    if (*tmp == '"')
    {
        *str = tmp + 1;
        return (ft_strdup("\0"));
    }
    else if (*tmp == '$' && *(tmp + 1) == '"')
    {
        *str = tmp + 2;
        return (ft_strdup("$"));
    }
    i = 0;
    len_malloc = 0;
    size = 1;
    variables = NULL;
    while (*(tmp + i) != c)
    {
        /*
            (*(tmp + i) == '$') kant ghi hadi flawle lokhrin zdnahom 3la 7alat b7al hado
            "test $" "Test $'hello'" "test $ "
        */
        if ((*(tmp + i) == '$') && (*(tmp + i + 1) == '?'))
        {
            //var_name = get_name_variable(tmp, i);
            len_string = 1;
            i += len_string + 1;
            value_var = get_value_of_exit();
            if (!value_var)
                value_var = ft_strdup("\0");
            len_string = ft_strlen(value_var);
            len_malloc += len_string;
            variables = ft_realloc(variables, size);
            *(variables + size - 1) = value_var;
            size++;
        }
        else if ((*(tmp + i) == '$') && *(tmp + i + 1) != ' '&& *(tmp + i + 1) != '\t' && *(tmp + i + 1) != '\'' && *(tmp + i + 1) != '"' && *(tmp + i + 1) != '$')
        {
            var_name = get_name_variable(tmp, i);
            len_string = ft_strlen(var_name);
            i += len_string + 1;
            value_var = get_value_variable(var_name, env);
            if (!value_var)
                value_var = ft_strdup("\0");
            len_string = ft_strlen(value_var);
            len_malloc += len_string;
            variables = ft_realloc(variables, size);
            *(variables + size - 1) = value_var;
            size++;
            free_ptr(&var_name);
        }
        else
        {
            i++;
            len_malloc++;
        }
    }
    number = 0;
    *str = tmp + i + 1;
    new_str = malloc(sizeof(char) * len_malloc + 1);
    j = 0;
    f = 0;
    while (f < len_malloc)
    {
        /*
            (*(tmp + i) != '$') kant ghi hadi flawle lokhrin zdnahom 3la 7alat b7al hado
            "test $" "Test $'hello'" "test $ "
        */
        if ((*(tmp + j) == '$') && *(tmp + j + 1) != ' ' && *(tmp + j + 1) != '\t' && *(tmp + j + 1) != '\'' && *(tmp + j + 1) != '"' && *(tmp + j + 1) != '$')
        {
            t = 0;
            //f++;
            len_string = ft_strlen(*(variables + number));
            value_var = *(variables + number);
            while (t < len_string)
            {
                *(new_str + f) = *(value_var + t);
                t++;
                f++;
            }
            j = j + get_lenght_variable(tmp + j + 1) + 1; //hadi zadtha ms knt haydtha 9bal wa9ila
            number++;
        }
        else
        {
            *(new_str + f) = *(tmp + j);
            j++;
            f++;
        }
        
    }
    free_double_ptr(variables);
    *(new_str + f) = '\0';
    return (new_str);
}
