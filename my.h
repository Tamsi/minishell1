/*
** my.h for  in /home/tbesson/CPE_2016_getnextline
** 
** Made by Tamsi Besson
** Login   <tbesson@epitech.net>
** 
** Started on  Sun Jan 15 12:27:22 2017 Tamsi Besson
** Last update Wed Apr  5 17:43:04 2017 Tamsi Besson
*/
#ifndef MINISHELL2_H_
# define MINISHELL2_H_
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

typedef struct t_command
{
	char **command;
	char **path;
} s_command;

int my_putstr(char *);
int my_strlen(char *);
int my_strncmp(char *, char *, int);
int my_strcmp(char *, char *);
int my_builtins(char *, char **, char **);
int my_exit(char *);
int my_cd(char **, char **);
int my_env(char *, char **);
int my_unsetenv(char **, char **);
char *my_strcat(char *, char *);
char *my_realloc(char *);
char *my_strcpy(char *, char *);
char *my_strcat(char *, char *);
char *getpath(char **, char *);
char *my_putnbr_base(int, char*);
char *get_next_line(const int);
char **my_str_to_wordtab(char *, char);

extern char map[2][8][9];
#endif //MINISHELL2_H_
