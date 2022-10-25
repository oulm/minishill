#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>

#include "libft/libft.h"
//----------

typedef struct s_cmd{
    int     cmd_index;
    char    *cmd;
    char    **args;
    int     stdin_file;
    int     stdout_file;
    int     is_echo;
    struct s_shell *next;
} t_cmd;

//---------------
//typedef struct NODE;

int exit_st;

typedef enum e_type
{
    EXEC = 0,
    PIPE = 1,
    REDR = 2
}   t_type;

typedef struct s_exec
{
    char        **argv;
}   EXEC_CMD;

typedef struct s_pipe
{
    char *arg;
}   PIPE_CMD;

typedef struct s_redr
{
    char    **list_file_name;
    char    type_redr;
    int     mode;
    int     fd;
}   REDR_CMD;



typedef union value
{
    EXEC_CMD  *exec_cmd;
    PIPE_CMD  *pipe_cmd;
    REDR_CMD  *redr_cmd;
} t_value;


typedef struct NODE
{
    t_type  type;
    t_value *value;
    struct NODE    *prev;
    struct NODE    *next;
} NODE;


void        print_node(NODE *tmp);
int         get_len(char *start, char *end);
char        *get_string(char *start, char *end, int size);
NODE        *create_redr(char **str, char **env);
NODE        *create_pipe(char **str);
t_value     *initialize_node_exec(char **ptr);
NODE        *create_exec(char **str, char c, char **env);
char	    **ft_realloc(char **ptr, int size);
int        Scanner(char **string, char **s, char **e);
char        peek(char *str);
NODE        *create_redr_2(char **str, char **env);
NODE        *create_redr_3(char **str, char **env);
NODE        *create_redr_4(char **str, char **env);
char        *handle_qoutes_string(char **str, char c, char **env);
char        *handle_single_string(char **str, char c, char **env);
int         get_len_q(char *start, char *end);
char        *get_string_q(char *start, char *end, int size);
int         get_len_q_v1(char *start, char *end, char **env);
char        *get_string_q_v1(char *start, char *end, int size, char **env);
char        *get_value_variable(char *var_name, char **env);
char        *get_name_variable(char *tmp, int i);
int         get_len_q_v2(char *start, char *end);
char        *get_string_q_v2(char **start, char *end, int size);
char        *get_string_move_start(char **start, char *end, int size);
int         get_len_q_v3(char *start, char *end);
char        *get_string_q_v1_and_move(char **start, char *end, int size, char **env);
int         get_len_q_v1_new(char *start, char *end, char **env);
int         get_len_v(char *start, char *end);
int         get_len_of_string(char **str);
char        *get_str(char **str, int size);
void        check_built_in(NODE *top, char ***dup_env);
int         get_len_q_v4(char *start);
char        *get_string_q_v4(char **start, int size);
void        get_end(char **es);
int         get_len_q_v1_new_2(char *start,char ** env);
char        *get_string_q_v1_and_move_2(char **start, int len,char ** env);
void        free_double_ptr(char **ptr);
int         get_len_v_2(char *start, char *end);
char        *get_string_move_start_2(char **start, char *end, int size);
char        **get_files(char **str, char c, char **env);
NODE        *create_redr(char **str, char **env);
NODE        *create_redr_2(char **str, char **env);
NODE        *create_redr_node(char **ptr_2, char type_redr);
void        ft_heredoc(char *str, char **env, char type);
char        *get_line(char *str,char **env);
NODE    *first_node(NODE *top);
void    print_error(char *str, char c);
char *get_value_of_exit();
void    free_ptr(char **ptr);
void free_node(NODE *first);
//env.c
char        **duplicate_env(char **env);
void    free_double_ptr(char **ptr);

//exoprt.c
void        export(NODE *first, char ***env);
int         check_if_exist(char *str, char ***env);
size_t      number_of_var(char **env);
int         check_valid_name(char *str);
void        add(char *tmp, char ***env, int env_size, char *str);

//unset.c
void unset(NODE *first, char ***env);
int  check_if_exist_v1(char *str, char ***env);

//echo.c
void echo(NODE *first, char ***env);

//clear.c
void clear(NODE *first, char ***env);

//ft_cd.c
void ft_cd(NODE *first, char ***env);

//ft_pwd
void ft_pwd();

//signal.c
void init_signal();


void execution(NODE* first, char **env);


/*
void    add(char *tmp, char ***env, int env_size, char *str)
{
    char    **ptr;
    size_t  len;
    int     exist;

    if (check_valid_name(tmp))
    {
        len = ft_strlen(tmp);
        if (*(str + len) == '=')
        {
            exist = check_if_exist(tmp, env);
            if (exist == -1)
            {
                ptr = ft_realloc(*env, env_size + 1);
                *(ptr + env_size) = str;
                *env = ptr;
            }
            else
                *(*env + exist) = str;
        }
    }
}
*/

#endif