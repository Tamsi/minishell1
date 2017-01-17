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

char    *my_strcat(char *dest, char *src)
{
  int   len;
  int   i;

  len = my_strlen(dest);
  i = 0;
  while (src[i])
    {
      dest[len + i] = src[i];
      i = i + 1;
    }
  dest[len + i] = '\0';
  return (dest);
}

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

int main(int ac, char **av, char **env)
{
  char *s;
  char **tab2d;
  char *tab[] = {"ls", NULL};
  pid_t process;
  int i;

  tab2d = malloc (1000 * sizeof(char *));
  s = my_getenv(env);
  tab2d = my_str_to_wordtab(s);
  i = 0;
  while (tab2d[i])
  {
    my_strcat(tab2d[i], "/");
    my_strcat(tab2d[i], tab[0]);
    i++;
  }
  while (1)
    {
      i = 0;
      write (0, "$>", 3);
      get_next_line(0);
      if (my_strncmp("exit", s, 5) == 0)
        exit (0);
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
}
