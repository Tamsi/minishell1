/*
** my.h for  in /home/tbesson/CPE_2016_getnextline
** 
** Made by Tamsi Besson
** Login   <tbesson@epitech.net>
** 
** Started on  Sun Jan 15 12:27:22 2017 Tamsi Besson
** Last update Mon Jan 16 14:10:35 2017 Tamsi Besson
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int my_putstr(char *);
int my_strlen(char *);
int	my_strncmp(char *, char *, int);
int	my_strcmp(char *, char *);
int my_builtins(char *, char **, char **);
int my_exit(char *);
int my_cd(char **);
int my_env(char *, char **);
char *my_strcat(char *, char *);
char *my_realloc(char *);
char *my_strcpy(char *, char *);
char *my_strcat(char *, char *);
char *stock_line(char *);
char *get_next_line(const int);
char **my_str_to_wordtab(char *, char);
void sig_handler(int);