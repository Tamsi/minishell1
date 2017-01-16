/*
** my_putstr.c for  in /home/Tamsi/CPool_Day04/tests
** 
** Made by Tamsi Besson
** Login   <Tamsi@epitech.net>
** 
** Started on  Thu Oct  6 13:43:17 2016 Tamsi Besson
** Last update Mon Jan 16 14:13:18 2017 Tamsi Besson
*/

#include "my.h"

int     my_putstr(char *str)
{
  int   i;

  i = 0;
  while (str[i] != '\0')
  {
  	write (1, str[i], 1);
  	i = i + 1;
  }
  return (0);
}
