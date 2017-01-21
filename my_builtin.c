/*
** my_builtin.c for  in /home/tbesson/projet_psu/PSU_2016_minishell1
** 
** Made by Tamsi Besson
** Login   <tbesson@epitech.net>
** 
** Started on  Fri Jan 20 16:21:59 2017 Tamsi Besson
** Last update Sat Jan 21 15:27:55 2017 Tamsi Besson
*/

#include "my.h"

int my_builtins(char *s, char **env, char **command)
{
        if (my_exit(s) == 0)
                exit (0);
        if (my_env(s, env) == 0)
                return (0);
        if (my_cd(command, env) == 0)
                return (0);
        if (my_unsetenv(env, command) == 0)
                                        return (0);
        return (1);
}

int my_env(char *s, char **env)
{
  int i;

  i = 0;
  if (my_strcmp("env", s) == 0)
  {
    while (env[i] != NULL)
    {
      write (0, env[i], my_strlen(env[i]));
      write(0, "\n", 1);
      i++;
    }
    return (0);
  }
  return (1);
}

int my_exit(char *s)
{
        if (my_strcmp("exit", s) == 0)
  {
    write (0, my_strcat(s, "\n"), 6);
    return (0);
  }
  return (1);
}

int my_cd(char **command, char **env)
{
  if (my_strcmp("cd", command[0]) == 0)
    {
      if (command[1] == NULL || my_strcmp("-", command[1]) == 0
          || my_strcmp("~", command[1]) == 0)
        chdir (getpath(env, "HOME"));
      else
        chdir (command[1]);
      return (0);
    }
  return (1);
}

int my_unsetenv(char **env, char **command)
{
  int i;

  i = 0;
  if (my_strcmp ("unsetenv", command[0]) == 0)
    {
      while (env[i] != NULL)
        {
          if (command[1] == NULL)
            {
              write (2, "unsetenv: Too few arguments.\n", 30);
              return (0);
            }
          if (my_strncmp(env[i], command[1], my_strlen(command[1])) == 0)
            {
              while (env[i] != NULL)
                {
                  env[i] = env[i + 1];
                  i++;
                }
              return (0);
            }
          i++;
        }
    }
  return (1);
}
