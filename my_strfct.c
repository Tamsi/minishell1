/*
** my_strfct.c for  in /home/tbesson/projet_psu/PSU_2016_minishell1
** 
** Made by Tamsi Besson
** Login   <tbesson@epitech.net>
** 
** Started on  Tue Jan 17 14:40:58 2017 Tamsi Besson
** Last update Tue Jan 17 14:40:59 2017 Tamsi Besson
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

int     my_strlen(char *str)
{
  int   length;

  length = 0;
  while (str[length] != '\0')
    {
      length = length + 1;
    }
  return (length);
}