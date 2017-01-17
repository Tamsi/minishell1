/*
** main.c for  in /home/tbesson/projet_psu/PSU_2016_minishell1
** 
** Made by Tamsi Besson
** Login   <tbesson@epitech.net>
** 
** Started on  Mon Jan 16 14:03:49 2017 Tamsi Besson
** Last update Mon Jan 16 14:09:56 2017 Tamsi Besson
*/

#include "my.h"

char *my_getenv(char **env)
{
  int i;
  int j;
  int k;
  char *s;

  i = 0;
  j = 0;
  k = my_strlen("PATH=");
  s = malloc (100 * sizeof(char));
  while (env[i] != NULL)
  {
    if (my_strncmp(env[i], "PATH", 4) == 0)
      while (env[i][k] != '\0')
      {
        s[j] = env[i][k];
        j++;
        k++;
      }
    i++;
  }
  return (s);
}

char **path2d(char *s, char **env)
{
  char *str;
  int i;
  char **tab2d;

  tab2d = malloc (1000 * sizeof(char *));
  str = my_getenv(env);
  tab2d = my_str_to_wordtab(str);
  i = 0;
  while (tab2d[i])
  {
    my_strcat(tab2d[i], "/");
    my_strcat(tab2d[i], s);
    i++;
  }
  return (tab2d);
}

void cmd(char **tab2d, char **av, char **env)
{
  pid_t process;
  int i;

  i = 0;
  if (access(tab2d[i], F_OK) == 0)
  {
    process = fork();
    if (process == 0)
    {
      execve(tab2d[i], av, env);
      exit(0);
    }
    else
      wait(&process);
  }
  else
    i++;
}

int main(int ac, char **av, char **env)
{
  char *s;
  char **tab2d;
  while (1)
    {
      write (0, "$>", 3);
      s = get_next_line(0);
      if (my_strncmp("exit", s, 5) == 0)
        exit (0);
      tab2d = path2d(s, env);
      cmd(tab2d, av, env);
    }
}
