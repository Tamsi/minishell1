/*
** my_strcat.c for  in /home/Tamsi/CPool_Day07
** 
** Made by Tamsi Besson
** Login   <Tamsi@epitech.net>
** 
** Started on  Wed Oct 12 11:17:37 2016 Tamsi Besson
** Last update Mon Oct 17 23:27:27 2016 Tamsi Besson
*/

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
