/*
char *get_line(char *tmp, char **env)
{
    int     i;
    int     j;
    int     k;
    int     size;
    int     len_malloc;
    char    *var_name;
    int     len_string;
    char    *value_var;
    char    *return_value;

    i = 0;
    size = 0;
    while (*(tmp + i))
    {
        if (*(tmp + i) == '$')
        {
            var_name = get_name_variable(tmp + i, 0);
            len_string = ft_strlen(var_name);
            if (len_string == 0)
                len_string == 1;
            i += len_string + 1;
            value_var = get_value_variable(var_name, env);
            //printf("[%s]\n", value_var);
            if (!value_var)
            {
                size += 1;
            }
            else
                size = size + ft_strlen(value_var);
        }
        else
        {
            size++;
            i++;
        }

    }
    return_value = malloc(size * sizeof(char) + 1);

    i = 0;
    j = 0;
    while (*(tmp + i))
    {
        if (*(tmp + i) == '$')
        {
            var_name = get_name_variable(tmp + i, 0);
            len_string = ft_strlen(var_name);
            if (len_string == 0)
                len_string == 1;
            i += len_string + 1;
            value_var = get_value_variable(var_name, env);
            if (!value_var)
            {
                value_var = ft_strdup("\0"); // hadi t9dar t7aydha
            }
            else
            {
                k = 0;
                while (*(value_var + k))
                {
                    *(return_value + j) = *(value_var + k);
                    k++;
                    j++;
                }
            }
        }
        else
        {
            *(return_value + j) = *(tmp + i);
            i++;
            j++;
        }

    }
    return (return_value);
}
*/