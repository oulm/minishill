#include "minishell.h"

// NO LEAKS
char peek(char *str)
{
    while ((*str == ' ' || *str == '\t' ) && *str)
        str++;
    return *str;
}
/****************************************************************************************/
// had 2 t9dar tjma3hom
void Scanner_qoutes(char **es) // NO LEAKS
{
    char *str;

    str = *es;
    str++;
    while (*str != '"')
        str++;
    str++;
    *es = str;
}

void Scanner_single(char **es) // NO LEAKS
{
    char *str;

    str = *es;
    str++;
    while (*str != '\'')
        str++;
    str++;
    *es = str;
}
/******************************************************************************************/
void get_end(char **es)  // NO LEAKS
{
    char *tmp;
    int j;

    tmp = *es;
    j = 2;

    while (*tmp != ' ' && *tmp != '\t' && *tmp != '|' && *tmp != '>'
        && *tmp != '<' && *tmp != '\n' && *tmp) // makantsh *tmp
    {
        if (*tmp == '\'')
        {
            j = 2;
            while (j)
            {
                if (*tmp == '\'')
                {
                    j--;
                }
                tmp++;
            }            
        }
        else if (*tmp == '"')
        {
                j = 2;
                while (j)
                {
                    if (*tmp == '"')
                    {
                        j--;
                    }
                    tmp++;
                }
        }
        else
            tmp++;
    }
    *es = tmp;
    //return (tmp);
    
}

int Scanner(char **string, char **s, char **e)
{
    
    char *tmp;
    int return_value;

    return_value = 0;
    tmp = *string;
    while ((*tmp == ' ' || *tmp == '\t') && *tmp)
        tmp++;
    if (s)
        *s = tmp;
    while ((*tmp != '$' && *tmp != ' ' && *tmp != '\t' && *tmp != '>' && *tmp != '|' && *tmp != '<') && *tmp && *tmp != '\n')
    {
        //printf("[%c]", *tmp);
        if (*tmp == '"')
        {
            Scanner_qoutes(&tmp);
            //get_end
            
            get_end(&tmp);
            
            *e = tmp;
            
            return_value = 1;
            return (return_value);
        }
        else if (*tmp == '\'')
        {
            Scanner_single(&tmp);
            return_value = 2;
            //*s = tmp;
            get_end(&tmp);
            
            *e = tmp;
            return (return_value);
        }
        
        else
            tmp++;
    }
    if (e)
        *e = tmp;
    *string = tmp;
    return (return_value);
}

char	**ft_realloc(char **ptr, int size)
{
	char	**tmp;

	tmp = ft_calloc((sizeof(char *)), size + 1);
	if (!tmp)
	{
		return (NULL);
	}
	if (ptr)
	{
		memcpy(tmp, ptr, size * sizeof(char *));
		free(ptr);
	}
	return (tmp);
}
