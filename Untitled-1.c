while (c && (c != ' ' && c != '\t') && c != '\n' && c != '|' && c!= '<' && c != '>')
    {
        if (c == '"')
        {
            full_str = ft_strdup("\0");
            new_str = handle_qoutes_string(str, c, env);
            full_str = ft_strjoin(full_str, new_str);
            while ((**str == '\'' || **str == '"') || (**str != ' ' && **str != '\t' && **str != '<' && **str != '>' && **str != '|' && **str != '\n' && **str != '\0'))
            {
                if (**str == '"')
                {
                    new_str = handle_qoutes_string(str, '"', env);
                    full_str = ft_strjoin(full_str, new_str);
                }
                else if (**str == '\'')
                {
                    new_str = handle_single_string(str, '\'', env);
                    full_str = ft_strjoin(full_str, new_str);
                }
                else if (**str == '$')
                {
                    if (**str == '$' && *(*str + 1) == '\0')
                    {
                        start = *str;
                        start = start + 1;
                        new_str = ft_strdup("$");
                    }else
                    {
                        k = 0;
                        start = *str;
                        var_name = get_name_variable(start, k);
                        len_string = ft_strlen(var_name);
                        k += len_string + 1;
                        value_var = get_value_variable(var_name, env);
                        if (!value_var)
                            new_str = ft_strdup("\0");
                        else
                            new_str = value_var;
                        start = start + k;
                    }
                    
                    
                    full_str = ft_strjoin(full_str, new_str);
                    *str = start;
                }
                else
                {
                    len = get_len_of_string(str);
                    new_str = get_str(str, len);
                    full_str = ft_strjoin(full_str, new_str);
                }
                
            }
            
        }
        else if (c == '\'')
        {
            full_str = ft_strdup("\0");
            new_str = handle_single_string(str, '\'', env);
            full_str = ft_strjoin(full_str, new_str);
            while ((**str == '\'' || **str == '"') || (**str != ' ' && **str != '\t' && **str != '<' && **str != '>' && **str != '|' && **str != '\n'&& **str != '\0'))
            {
                if (**str == '"')
                {
                    new_str = handle_qoutes_string(str, '"', env);
                    full_str = ft_strjoin(full_str, new_str);
                }
                else if (**str == '\'')
                {
                    new_str = handle_single_string(str, c, env);
                    full_str = ft_strjoin(full_str, new_str);
                }
                else if (**str == '$')
                {
                    if (**str == '$' && *(*str + 1) == '\0')
                    {
                        start = *str;
                        start = start + 1;
                        new_str = ft_strdup("$");
                    }
                    else
                    {
                        k = 0;
                        start = *str;
                        var_name = get_name_variable(start, k);
                        len_string = ft_strlen(var_name);
                        k += len_string + 1;
                        value_var = get_value_variable(var_name, env);
                        if (!value_var)
                            new_str = ft_strdup("\0");
                        else
                            new_str = value_var;
                        start = start + k;
                    }
                    full_str = ft_strjoin(full_str, new_str);
                    *str = start;
                }
                else
                {
                    len = get_len_of_string(str);
                    //printf("len[%d]\n", len);
                    new_str = get_str(str, len);
                    full_str = ft_strjoin(full_str, new_str);
                    //printf("**str[%s]\n", *str);
                }
            }
        }
        else if (c == '$')
        {
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
                k = 0;
                if (!v)
                {
                    //printf("test\n");
                    //len = get_len_v(start, end);
                    //new_str = get_string_move_start(&start, end, len);
                    len = get_len_v_2(start, end);
                    //printf("len[%d]\n", len);
                    new_str = get_string_move_start_2(&start, end, len);
                    /*
                    printf("len[%d]", len);
                    printf("newstr[%s]", new_str);
                    printf("start[%c]\n", *start);
                    exit(1);
                    */
                   //printf("000000[%s]\n", start);
                }
                else if (v == 1)
                {
                    len = get_len_q_v1_new(start, end, env); // hadi rah tbadl fiha shuf wash ba9a khdama
                    new_str = get_string_q_v1_and_move(&start, end, len, env);
                    //printf("1111111[%s]\n", start);
                }
                else if (v == 2)
                {
                    //printf("notok\n");
                    len = get_len_q_v4(start);
                    //printf("len[%d]", len);
                    new_str = get_string_q_v4(&start, len);
                    //len = get_len_q_v2(start, end);
                    //new_str = get_string_q_v2(&start, end, len);
                    //printf("len[%d]", len);
                    //printf("newstr[%s]", new_str);
                    //printf("start[%c]\n", *start);
                    //exit(1);
                    //printf("2222222[%s]\n", start);
                }
                else if (v == 4)
                {
                    if (*start == '$' && *(start + 1) == '\0')
                    {
                        start = start + 1;
                        new_str = ft_strdup("$");
                    }
                    else
                    {
                        //k = 0;
                        //k khasseha tkun 0 hna
                        var_name = get_name_variable(start, k);
                        len_string = ft_strlen(var_name);
                        k += len_string + 1;
                        value_var = get_value_variable(var_name, env);
                        //printf("test");
                        if (!value_var)
                            new_str = ft_strdup("\0");
                        else
                            new_str = value_var;
                        start = start + k;
                        //printf("444444[%s]\n", start);
                        //exit(1);
                    }
                    
                    
                    //printf("start[%s]\n", start);
                }
                //printf("*start[%c]\n", *start);
                full_str = ft_strjoin(full_str, new_str);
                if (*start == '\'')
                    v = 2;
                else if (*start == '"')
                    v = 1;
                else if (*start == ' ' || *start == '\t' || *start == '\n' || *start == '\0')
                    break;
                else if (*start == '$')
                    v = 4;
                else
                    v = 0;
            }
            *str = start;
        }
        else
        {
            v = Scanner(str, &start, &end);
            full_str = ft_strdup("\0");
            k = 0;
            //hadi hya li kant flele !!!!!! 
            //while (start < end && *start != ' ' && *start != '\t')
            while (*start != '\0' && *start != ' ' && *start != '\t')
            {

                if (!v)
                {
                    //len = get_len_v(start, end);
                    //new_str = get_string_move_start(&start, end, len);
                    len = get_len_v_2(start, end);
                    new_str = get_string_move_start_2(&start, end, len);
                }
                else if (v == 1)
                {
                    //len = get_len_q_v1_new(start, end, env);
                    //new_str = get_string_q_v1_and_move(&start, end, len, env);
                    len = get_len_q_v1_new_2(start, env);
                    new_str = get_string_q_v1_and_move_2(&start, len, env);
                }
                else if (v == 2)
                {
                    //printf("ok2\n");
                    
                    //printf("end[%c]", *end);
                    //len = get_len_q_v2(start, end);
                    len = get_len_q_v4(start);
                     //printf("len[%d]", len);
                     new_str = get_string_q_v4(&start, len);
                     //printf("new str[%c]\n", *start);
                     //printf("full str[%s]", full_str);
                    //exit(1);
                    //exit(1);
                    //new_str = get_string_q_v2(&start, end, len);
                    //new_str = get_string_q_v4(&start, len);
                }
                else if (v == 4)
                {
                    //printf("test\n");
                    if (*start == '$' && *(start + 1) == '\0')
                    {
                        start = start + 1;
                        new_str = ft_strdup("$");
                    }
                    else
                    {
                        k = 0;
                        var_name = get_name_variable(start, k);
                        len_string = ft_strlen(var_name);
                        k += len_string + 1;
                        value_var = get_value_variable(var_name, env);
                        if (!value_var)
                            new_str = ft_strdup("\0");
                        else
                            new_str = value_var;
                        start = start + k;
                    }
                }
                full_str = ft_strjoin(full_str, new_str);
                //printf("full_str[%s and v[%d]]\n", full_str, v);
                if (*start == '\'')
                    v = 2;
                else if (*start == '"')
                    v = 1;
                else if (*start == ' ' || *start == '\t' || *start == '\n' || *start == '\0')
                    break;
                else if (*start == '$')
                    v = 4;
                else
                    v = 0;
                //printf("->[%d]", v);
            }
            *str = start;
        }
        //if (*full_str != '\0')
        //{
            ptr = ft_realloc(ptr, i + 1);
            *(ptr + i - 1) = full_str;
            i++;
        //}
        c = peek(*str);
    }