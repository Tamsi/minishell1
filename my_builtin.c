/*
** my_builtin.c for  in /home/tbesson/projet_psu/PSU_2016_minishell1
** 
** Made by Tamsi Besson
** Login   <tbesson@epitech.net>
** 
** Started on  Fri Jan 20 16:21:59 2017 Tamsi Besson
** Last update Fri Jan 20 16:22:00 2017 Tamsi Besson
*/

#include "my.h"

int my_builtins(char *s, char **env, char **command)
{
	if (my_exit(s) == 0)
		exit (0);
	if (my_env(s, env) == 0)
		return (0);
	if (my_cd(command) == 0)
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
    return (1);
  }
  return (0);
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

int my_cd(char **command)
{
	if (my_strcmp("cd", command[0]) == 0)
	{
		chdir (command[1]);
		return (0);
	}
	return (1);
}