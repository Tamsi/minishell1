/*
** main.c for  in /home/tbesson/projet_psu/PSU_2016_minishell1
** 
** Made by Tamsi Besson
** Login   <tbesson@epitech.net>
** 
** Started on  Mon Jan 16 14:03:49 2017 Tamsi Besson
** Last update Fri Apr  7 09:54:10 2017 Tamsi Besson
*/

#include "my.h"

char *getpath(char **env, char *path)
{
  int i;
  int j;
  int k;
  char *s;

  i = 0;
  j = 0;
  k = my_strlen(path) + 1;
  while (env[i] != NULL)
    {
      if (my_strncmp(env[i], path, 4) == 0)
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

int get_exec_path(char *str, s_command *command)
{
  int i;

  i = 0;
  while (command[0].path[i] != NULL)
    {
      my_strcat(command[0].path[i], "/");
      if (command[0].command[0] == NULL)
        return (0);
      my_strcat(command[0].path[i], command[0].command[0]);
      if (access(command[0].path[i], F_OK) == 0)
        {
          my_strcpy(str, command[0].path[i]);
          command[0].path[i][my_strlen(command[0].path[i])
            - (1 + my_strlen(command[0].command[0]))] = '\0';
          return (0);
        }
      command[0].path[i][my_strlen(command[0].path[i])
        - (1 + my_strlen(command[0].command[0]))] = '\0';
      i++;
    }
  return (1);
}

void cmd(s_command *command, char **env)
{
  pid_t process;
  int   pipefd[2];
  int   error;
  char *path_command;

  path_command = malloc (1000 * sizeof(char));
  get_exec_path(path_command, command);
  error = pipe(pipefd);
  process = fork();
  if (process == -1 || error == -1)
    exit (1);
  if (process == 0)
    {
      close(pipefd[0]);
      execve(path_command, command[0].command, env);
      write (2, my_strcat(command[0].command[0], ": Command not found.\n"),
             my_strlen(command[0].command[0]) + 21);
      exit(1);
    }
  else
  {
    close(pipefd[1]);
    wait(&process);
  }
}

char **get_path2d(char **env, char *path)
{
  char *str;
  char **path2d;

  str = getpath(env, path);
  path2d = my_str_to_wordtab(str, ':');
  return (path2d);
}

s_command *check_pipe(char *s, s_command *command)
{
  char *tmp;
  int i;
  int j;
  int k;

  i = 0;
  j = 0;
  tmp = malloc(my_strlen(s) * sizeof(char));
  while (s[i])
  {
    if (s[i] == '|' || s[i] == ';')
    {
      command[j].command = my_str_to_wordtab(tmp, ' ');
      printf("tmp = %s\n", command[j].command[0]);
      k = 0;
      j++;
      i++;
    }
    tmp[k] = s[i];
    k++;
    i++;
  }
  if (j == 0)
    command[j].command = my_str_to_wordtab(s, ' ');
  else
    command[j].command = my_str_to_wordtab(tmp, ' ');
  printf("tmp = %s\n", command[j].command[0]);
  return (command);
}

int main(int ac, char **av, char **env)
{
  char *s;
  s_command *command;

  command = malloc(5 * sizeof(s_command *));
  command->path = get_path2d(env, "PATH");
  while (1)
    { 
      s = get_next_line(0);
      command = check_pipe(s, command);
      if (command[0].command != NULL)
        if (my_builtins(s, env, command[0].command) != 0)
          cmd(command, env);
    }
  free(command);
}
