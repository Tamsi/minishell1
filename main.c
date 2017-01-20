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

char *getpath(char **env)
{
  int i;
  int j;
  int k;
  char *s;

  i = 0;
  j = 0;
  k = my_strlen("PATH=");
  while (env[i] != NULL)
  {
    if (my_strncmp(env[i], "PATH", 4) == 0)
    {
      s = malloc (my_strlen(env[i]) * sizeof(char) + 1);
      while (env[i][k] != '\0')
      {
        s[j] = env[i][k];
        j++;
        k++;
      }
    }
    i++;
  }
  return (s);
}

int get_exec_path(char *str, char **path, char **command)
{
  pid_t process;
  int i;

  i = 0;
  while (path[i] != NULL)
  {
    //METTRE LE PATH[I] DANS UNE STR TEMPORAIRE
    my_strcat(path[i], "/");
    if (command[0] == NULL)
      return (0);
    my_strcat(path[i], command[0]);
    if (access(path[i], F_OK) == 0)
    {
      my_strcpy(str, path[i]);
      path[i][my_strlen(path[i]) - (1 + my_strlen(command[0]))] = '\0';
      return (0);
    }
    path[i][my_strlen(path[i]) - (1 + my_strlen(command[0]))] = '\0';
    i++;
  }
  return (1);
}

void cmd(char **path, char **command, char **env)
{
  pid_t process;
  char *path_command;

  path_command = malloc (1000 * sizeof(char));
  get_exec_path(path_command, path, command);
  process = fork();
  if (process == 0)
  {
    execve(path_command, command, env);
    write (2, my_strcat(command[0], ": Command not found.\n"), my_strlen(command[0]) + 21);
    exit(1);
  }
  else
    wait(&process);
}


char **get_path2d(char **env)
{
  char *str;
  char **path2d;

  str = getpath(env);
  path2d = my_str_to_wordtab(str, ':');
  return (path2d);
}

int main(int ac, char **av, char **env)
{
  char *s;
  char **path;
  char **command;

  path = get_path2d(env);
  while (1)
    {
      //write (0, "$>", 3);
      s = get_next_line(0);
      command = my_str_to_wordtab(s, ' ');
      if (!my_builtins(s, env, command))
        cmd(path, command, env);
    }
}
