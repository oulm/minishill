#include "../minishell.h"

// NOLEAKS
char    *get_value_of_env(char ***env, char *str)
{
    int     exist;
    char    **ptr;
    char    *tmp;
    char    *tmp1;

    exist = check_if_exist_v1(str, env);
    if (exist == -1)
        return (NULL);
    ptr = ft_split(*(*(env) + exist), '=');
    if (!ptr) 
        return (NULL);
    else if (number_of_var(ptr) < 2)
    {
        free_double_ptr(ptr);
        return (ft_strdup("\0"));
    }
    tmp = ft_strchr(*(*(env) + exist), '=');
    tmp1 = ft_strdup(tmp + 1);
    free_double_ptr(ptr);
    return (tmp1);
}
// NOLEAKS
void    exec_chdir(char ***env, char *path, char *old_pwd, int v)
{
    char    *tmp;
    char    *cur_pwd;

    if (chdir(path) != 0)
    {
        ft_putstr_fd("bash: cd: ", 2);
        perror(path);
        return ;
    }
    tmp = ft_strjoin("OLDPWD=", old_pwd);
    add("OLDPWD", env, number_of_var(*env), tmp);
    cur_pwd = getcwd(NULL, 0);
    free_ptr(&tmp);
    tmp = ft_strjoin("PWD=", cur_pwd);
    add("PWD", env, number_of_var(*env), tmp);
    if (v)
        ft_putendl_fd(cur_pwd, 1);
    free_ptr(&tmp);
    free_ptr(&cur_pwd);
}

// NOLEAKS
void exec_home(char ***env, char *old_pwd)
{
    char *home;

    home = get_value_of_env(env, "HOME");
    if (!home)
        ft_putstr_fd("bash: cd: HOME not set\n", 2);
    else if (*home != '\0')
        exec_chdir(env, home, old_pwd, 0);
    free(home);
}

// NOLEAKS
void exec_one(char ***env, char *old_pwd)
{
    char *old_pwd_1;

    old_pwd_1 = get_value_of_env(env, "OLDPWD");
    if (!old_pwd_1)
        ft_putstr_fd("bash: cd: OLDPWD not set\n", 2);
    else
        exec_chdir(env, old_pwd_1, old_pwd, 1);
    free(old_pwd_1);
}

// NOLEAKS
int check_errors(NODE *first)
{
    int size;

    size = number_of_var(first->value->exec_cmd->argv);
    if (size == 2)
    {
        if (*(*(first->value->exec_cmd->argv + 1)) == '-' && *(*(first->value->exec_cmd->argv + 1) + 1) != '\0')
        {
            ft_putstr_fd("bash: cd: invalid option\n", 2);
            ft_putendl_fd("cd: usage: cd [-L|[-P [-e]] [-@]] [dir]", 2);
            return (1);
        }
    }
    else if (size > 2)
    {
        ft_putendl_fd("bash: cd: too many arguments", 2);
        return 1;
    }
    return (0);
}

void ft_cd(NODE *first, char ***env)
{
    char    *old_pwd;
    char    *tmp;
    char    *home;
    char    *tmp2;

    if (check_errors(first))  // NO LEAKS
        return ;
    old_pwd = getcwd(NULL, 0);
    if (*(first->value->exec_cmd->argv + 1) == NULL) 
        exec_home(env, old_pwd);
    else if (ft_strncmp(*((first->value->exec_cmd->argv + 1)), "-", 2) == 0)
        exec_one(env, old_pwd);
    else if (ft_strncmp(*((first->value->exec_cmd->argv + 1)), "~", 2) == 0)
    {
        home = get_value_of_env(env, "HOME");
        if (!home)
        {
            tmp = get_value_of_env(env, "USER");
            tmp2 = ft_strjoin("/Users/", tmp);
            exec_chdir(env, tmp2, old_pwd, 0);
            free(tmp);
            free(tmp2);
        }
        else if (*home == '\0' || ft_strncmp("/home/", home, 6))
        {
            tmp = get_value_of_env(env, "USER");
            tmp2 = ft_strjoin("/Users/", tmp);
            exec_chdir(env, tmp2, old_pwd, 0);
            free(tmp);
            free(tmp2);
        }
        else
            exec_chdir(env, home, old_pwd, 0);
        free(home);
    }
    else 
        exec_chdir(env, *(first->value->exec_cmd->argv + 1), old_pwd, 0);
    free(old_pwd);
}