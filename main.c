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

int		my_strncmp(char *s1, char *s2, int len)
{
  int	i;

  i = 0;
  while (s1[i] != '\0' && s2[i] != '\0' && i < len)
    {
      if (s1[i] == s2[i])
				i++;
      else
				return (s1[i] - s2[i]);
    }
  return (0);
}

char *my_getenv(char **env)
{
  int i;
  char *s;

  i = 0;
  s = malloc (100 * sizeof(char));
  while (env[i] != NULL)
  {
    if (my_strncmp(env[i], "PATH", 4) == 0)
      s = env[i];
    i++;
  }
  return (s);
}

int main(int ac, char **av, char **env)
{
  char *s;
  pid_t process;

  while (1)
    {
      write (0, "$>", 3);
      s = get_next_line(0);
      if (my_strncmp("exit", s, 5) == 0)
        exit (0);
      s = my_getenv(env);
      my_str_to_wordtab(s);
      /*process = fork();
        if (process == 0)
        {
          int retour = execve(tab[0], tab);
          exit(0);
        }
        else
        {
            wait(&process);
        }*/
    }
}
