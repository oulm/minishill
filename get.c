#include "minishell.h"

int get_len_of_string(char **str)
{
    char *tmp;
    int i;

    tmp = *str;
    i = 0;
    while (*tmp != '"' && *tmp != '\'' && *tmp != ' ' && *tmp != '>' && *tmp != '<' && *tmp != '|' && *tmp != '\n' && *tmp != '\0' && *tmp != '$') // $ ghi zadnaha
    {
        tmp++;
        i++;
    }

    return (i + 1); // +1 for null char
}

char *get_str(char **str, int size)
{
    char *tmp;
    int   i;
    char *m_start;

    tmp = malloc(size * sizeof(char));
    i = 0;
    m_start = *str;
    size--;
    while ((*m_start != '"' && *m_start != '\'' && *m_start != ' ' && *m_start != '>' && *m_start != '<' && *m_start != '|' && *m_start != '\n' && *m_start != '$') && size)
    {
        *(tmp + i) = *(m_start);
        m_start++;
        i++;
        size--;
    }
    *(tmp + i) = 0;
    *str = m_start;
    
    return (tmp);
    
}
/*********************************************************/
/*
int get_len_q_v2(char *start, char *end)
{
    int i;
    int j;

    i = 0;
    j = 2;
    while (start < end && j)
    {   
        if (*start != '\'')
        {
            i++;
        }
        else
            j--;
        start++;
    }
    return(i + 1); // +1 null char
}
*/
// lfar9 fhadi mafihash end
int get_len_q_v4(char *start)        // NO LEAKS
{
    int i;
    int j;

    i = 0;
    j = 2;
    while (j)
    {   
        if (*start != '\'')
        {
            i++;
        }
        else
            j--;
        start++;
    }
    return(i + 1); // +1 null char
}
/******************************************************************/

/******************************************************************/
/*
char *get_string_q_v2(char **start, char *end, int size)
{
    char *tmp;
    int   i;
    int   j;
    char *m_start;

    tmp = malloc(size * sizeof(char));
    i = 0;
    j = 2;
    m_start = *start;
    while (m_start < end && j)
    {
        if (*m_start != '\'')
        {
            *(tmp + i) = *(m_start);
            i++;
        }
        else
            j--;
        m_start++;
    }
    *(tmp + i) = 0;
    *start = m_start;
    return (tmp);
    
}
*/
char *get_string_q_v4(char **start, int size)
{
    char *tmp;
    int   i;
    int   j;
    char *m_start;

    tmp = malloc(size * sizeof(char));
    i = 0;
    j = 2;
    m_start = *start;
    while (*m_start && j)
    {
        if (*m_start != '\'')
        {
            *(tmp + i) = *(m_start);
            i++;
        }
        else
            j--;
        m_start++;
    }
    *(tmp + i) = 0;
    *start = m_start;
    return (tmp);
    
}

/******************************************************************/


/******************************************************************/
int get_len_q_v1_new(char *start, char *end, char **env)
{
    int i;
    int j;
    char *var_name;
    char *tmp;
    int len_string;
    char *value_var;

    i = 0;
    j = 2;
    tmp = start;
    while (start < end && j)
    {
        if (*start == '$')
        {
            if (*(start + 1) == '?')
            {
                start += 2;
                value_var = get_value_of_exit();
                if (!value_var)
                    value_var = ft_strdup("\0");
                len_string = ft_strlen(value_var);
                free_ptr(&value_var);
            }
            else
            {
                var_name = get_name_variable(start, 0);
                len_string = ft_strlen(var_name);
                start += (len_string + 1);
                if (len_string == 0)
                {
                    len_string = 1;
                }
                else
                {
                    value_var = get_value_variable(var_name, env);
                    if (!value_var)
                        value_var = ft_strdup("\0");
                    len_string = ft_strlen(value_var);
                    free_ptr(&value_var);
                }
                free_ptr(&var_name);
            }
            i += len_string;
        }
        else if (*start != '"')
        {
            i++;
            start++;
        }
        else
        {
            start++;
            j--;
        }
    }
    return(i + 1); // +1 null char
}

int get_len_q_v1_new_2(char *start, char **env)
{
    int i;
    int j;
    char *var_name;
    char *tmp;
    int len_string;
    char *value_var;

    i = 0;
    j = 2;
    tmp = start;
    var_name = NULL;
    value_var = NULL;
    while (*start && j)
    {
        if (*start == '$')
        {
            if (*(start + 1) == '?')
            {
                start += 2;
                value_var = get_value_of_exit();
                if (!value_var)
                    value_var = ft_strdup("\0");
                len_string = ft_strlen(value_var);
                free_ptr(&value_var);
            }
            else
            {
                var_name = get_name_variable(start, 0);
                len_string = ft_strlen(var_name);
                start += (len_string + 1);
                if (len_string == 0)
                {
                    len_string = 1;
                }
                else
                {
                    value_var = get_value_variable(var_name, env);
                    if (!value_var)
                        value_var = ft_strdup("\0");
                    len_string = ft_strlen(value_var);
                    free_ptr(&value_var);
                }
                free_ptr(&var_name);
            }
            i += len_string;
        }
        else if (*start != '"')
        {
            i++;
            start++;
        }
        else
        {
            start++;
            j--;
        }
    }
    return(i + 1); // +1 null char
}

/*******************************************************************/

int get_len_q_v1(char *start, char *end, char **env)
{
    int i;
    char *var_name;
    char *tmp;
    int len_string;
    char *value_var;

    i = 0;
    tmp = start;
    while (start < end)
    { 
        if (*start == '$')
        {
            var_name = get_name_variable(start, 0);
            len_string = ft_strlen(var_name);
            start += (len_string + 1);

            value_var = get_value_variable(var_name, env);
            len_string = ft_strlen(value_var);
            i += len_string;
            if (var_name && value_var)
            {
                free(var_name);
                free(value_var);
            }
        }
        else if (*start != '"')
        {
            i++;
            start++;
        }
        else
            start++;
    }
    return(i + 1); // +1 null char
}

/****************************************************/
char *get_string_q_v1_and_move_2(char **start, int size, char **env)
{
    char *tmp;
    int   i;
    char*     var_name;
    int     len_string;
    char    *value_var;
    int d;
    char *m_start;
    int j;

    tmp = malloc(size * sizeof(char));
    i = 0;
    m_start = *start;
    j = 2;
    var_name = NULL;
    value_var = NULL;
    while (*m_start && j)
    {
        if (*m_start == '$')
        {
            if (*(m_start + 1) == '?')
            {
                m_start += 2;
                value_var = get_value_of_exit();
                if (!value_var)
                    value_var = ft_strdup("\0");
                len_string = ft_strlen(value_var);
            }
            else
            {
                var_name = get_name_variable(m_start, 0);
                len_string = ft_strlen(var_name);
                if (len_string == 0)
                {
                    m_start += (len_string + 1);
                    len_string = 1;
                    value_var = ft_strdup("$");
                }
                else
                {
                    m_start += (len_string + 1);
                    value_var = get_value_variable(var_name, env);
                    if (!value_var)
                        value_var = ft_strdup("\0");
                }
                len_string = ft_strlen(value_var);
                free_ptr(&var_name);
            }
            d = 0;
            while (d < len_string)
            {
                *(tmp + i) = *(value_var + d);
                d++;
                i++;
            }
            free_ptr(&value_var);
        }
        else if (*m_start != '"')
        {
            *(tmp + i) = *(m_start);
            i++;
            m_start++;
        }
        else
        {
            m_start++;
            j--;
        }
    }
    *(tmp + i) = 0;
    *start = m_start;
    return (tmp);
}

char *get_string_q_v1_and_move(char **start, char *end, int size, char **env)
{
    char *tmp;
    int   i;
    char*     var_name;
    int     len_string;
    char    *value_var;
    int d;
    char *m_start;
    int j;

    tmp = malloc(size * sizeof(char));
    i = 0;
    m_start = *start;
    j = 2;
    value_var = NULL;
    var_name = NULL;
    while (m_start < end && j)
    {
        if (*m_start == '$')
        {
            if (*(m_start + 1) == '?')
            {
                m_start += 2;
                value_var = get_value_of_exit();
                if (!value_var)
                    value_var = ft_strdup("\0");
                len_string = ft_strlen(value_var);
                
            }
            else
            {
                var_name = get_name_variable(m_start, 0);
                len_string = ft_strlen(var_name);
                if (len_string == 0)
                {
                    m_start += (len_string + 1);
                    len_string = 1;
                    value_var = ft_strdup("$");
                }
                else
                {
                    m_start += (len_string + 1);
                    value_var = get_value_variable(var_name, env);
                    if (!value_var)
                        value_var = ft_strdup("\0");
                }
                len_string = ft_strlen(value_var);
                free_ptr(&var_name);
            }
            d = 0;
            while (d < len_string)
            {
                *(tmp + i) = *(value_var + d);
                d++;
                i++;
            }
            free_ptr(&value_var);
        }
        else if (*m_start != '"')
        {
            *(tmp + i) = *(m_start);
            i++;
            m_start++;
        }
        else
        {
            m_start++;
            j--;
        }
    }
    *(tmp + i) = 0;
    *start = m_start;
    return (tmp);
    
}
/**************************************************************/
int get_len_q_v3(char *start, char *end)
{
    int i;
    int j;

    i = 0;
    j = 2;
    while (start < end && j)
    {   
        if (*start != '"')
        {
            i++;
        }
        else
            j--;
        start++;
    }
    return(i + 1); // +1 null char
}


int get_len_q(char *start, char *end)
{
    int i;

    i = 0;
    while (start < end)
    {   
        if (*start != '"')
        {
            i++;
        }
        start++;
    }
    return(i + 1); // +1 null char
}

char *get_string_q(char *start, char *end, int size)
{
    char *tmp;
    int   i;

    tmp = malloc(size * sizeof(char));
    i = 0;
    while (start < end)
    {
        if (*start != '"')
        {
            *(tmp + i) = *(start);
            i++;
        }
        start++;
    }
    *(tmp + i) = 0;
    return (tmp);
    
}

/**************************************************************/
/*
int get_len_v(char *start, char *end)
{
    int i;

    i = 0;
    while (start < end)
    {
        start++;
        i++;
        if (*start == '\'' || *start == '"')
            break;
    }
    return(i + 1); // +1 null char
}
*/
// get_len_v_2 zadna fiha *start == '$' 3la get_len_v


int get_len_v_2(char *start, char *end)  // NO LEAKS
{
    int i;

    i = 0;
    while (start < end)
    {
        start++;
        i++;
        if (*start == '\'' || *start == '"' || *start == '$')
            break;
    }
    return(i + 1); // +1 null char
}

/**************************************************************/

int get_len(char *start, char *end)
{
    int i;

    i = 0;
    // ' and ""
    while (start < end)
    {
        start++;
        i++;
    }
    return(i + 1); // +1 null char
}

/**************************************************************/
/*
char *get_string_move_start(char **start, char *end, int size)
{
    char *tmp;
    char *m_start;
    int   i;

    m_start = *start;
    tmp = malloc(size * sizeof(char));
    i = 0;
    size--;
    while (m_start < end && size)
    {
        *(tmp + i) = *(m_start);
        m_start++;
        i++;
        size--;
    }
    *(tmp + i) = 0;
    *start = m_start;
    return (tmp);
    
}
*/
// get_string_move_start_2 and get_string_move_start nafss l7aja wa9ila

char *get_string_move_start_2(char **start, char *end, int size)
{
    char *tmp;
    char *m_start;
    int   i;

    m_start = *start;
    tmp = malloc(size * sizeof(char));
    i = 0;
    size--;
    while (m_start < end && size)
    {
        *(tmp + i) = *(m_start);
        m_start++;
        i++;
        size--;
    }
    *(tmp + i) = 0;
    *start = m_start;
    return (tmp);
    
}

/**************************************************************/

char *get_string(char *start, char *end, int size)
{
    char *tmp;
    int   i;

    tmp = malloc(size * sizeof(char));
    i = 0;
    while (start < end)
    {
        *(tmp + i) = *(start);
        start++;
        i++;
    }
    *(tmp + i) = 0;
    return (tmp);
    
}