/*
** main.c for  in /home/tbesson/maps
** 
** Made by Tamsi Besson
** Login   <tbesson@epitech.net>
** 
** Started on  Thu Feb  2 16:20:32 2017 Tamsi Besson
** Last update Fri Feb  3 12:44:55 2017 Tamsi Besson
*/

#include "my.h"

char map[2][8][9] = {
  {
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'}
  },
  {
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'}
  }
};

void decoder(int nb_msg, int nb_data, int pid)
{
  if (nb_msg == 100)
    hello(nb_data, pid);
  if (nb_msg == 101)
    attack(nb_data, pid);
  if (nb_msg == 102)
    hit(nb_data);
  if (nb_msg == 103)
    missed(nb_data);
  if (nb_msg == 104)
    sunk(nb_data);
  if (nb_msg == 105)
    win(nb_data);
}

int coo_to_nb(char *s)
{
  int nb;

  nb = (s[0] - 65) * 8;
  nb += s[1] - 49;
  return (nb);
}

int check_coo(char *s)
{
  if (s[0] < 'A' || s[0] > 'H')
    return (0);
  if (s[1] < '1' || s[1] > '8')
    return (0);
  if (map[1][s[1] - 49][s[0] - 65] != '.')
    return (0);
  return (1);
}

void play(int pid)
{
  char *s;
  my_putstr("attack\n");
  s = get_next_line(0);
  if (s != NULL)
  {
    if (check_coo(s) == 0)
    {
      my_putstr("wrong positions\n");
      play(pid);
    }
    else
      send_msg(pid, ATTACK, coo_to_nb(s));
  }
}

void game()
{
  my_putstr("my pid : ");
  my_putnbr(getpid());
  my_putstr("waiting for enemy connexion...\n");
  while (1)
  {
    pause ();
  }
}

char *get_bytestr(int nb)
{
  char *bit;
  char *octet;
  int k;
  int j;
  int i;

  j = 8;
  i = 0;
  k = 0;
  octet = malloc (8);
  bit = my_putnbr_base(nb, "01");
  while (j > my_strlen(bit))
  {
    octet[i] = '0';
    i++;
    j--;
  }
  while (bit[k] != '\0')
  {
    octet[i] = bit[k];
    k++;
    i++;
  }
  return (octet);
}

void send_msg(int pid, int msg, int data)
{
  int i;
  char *bit_msg;
  char *bit_data;
  int signum;

  i = 0;
  bit_msg = get_bytestr(msg);
  usleep(8000);
  while (bit_msg[i] != '\0')
  {
    signum = (bit_msg[i] == '1') ? SIGUSR1 : SIGUSR2;
    send_kill(pid, signum);
    i++;
  }
  i = 0;
  bit_data = get_bytestr(data);
  while (bit_data[i] != '\0')
  {
    signum = (bit_data[i] == '1') ? SIGUSR1 : SIGUSR2;
    send_kill(pid, signum);
    i++;
  }
}

void send_kill(int pid, int signum)
{
  kill(pid, signum);
  usleep(8000);
}

void receiver(int signum, siginfo_t *info, void *ptr)
{
  static int i;
  static int nb_msg;
  static int nb_data;
  char *bit_msg;
  char *bit_data;

  bit_msg = malloc (8);
  bit_data = malloc (8);
  if (i < 8)
  {
    bit_msg[i] = (signum == SIGUSR1) ? '1' : '0';
    nb_msg += ((bit_msg[i] - 48) << (7 - i));
  }
  if (i >= 8 && i < 16)
  {
    bit_data[i] = (signum == SIGUSR1) ? '1' : '0';
    nb_data += ((bit_data[i] - 48) << (15 - i));
  }
  if (i == 15)
  {
    usleep(8000);
    decoder(nb_msg, nb_data, (int)info->si_pid);
    nb_msg = 0;
    nb_data = 0;
    i = 0;
  }
  else
    i++;
}

void handler(int signum)
{
  struct sigaction action;
  action.sa_sigaction = receiver;
  action.sa_flags = SA_SIGINFO;
  if (sigaction(signum, &action, NULL))
    exit (-1);
}

int check_error(char **pos_tab, int posA[], int posB[])
{
  if (pos_tab[0][0] < '2' || pos_tab[0][0] > '5')
    return (84);
  if ((pos_tab[1][0] < 'A' || pos_tab[1][0] > 'H')
   || (pos_tab[2][0] < 'A' || pos_tab[2][0] > 'H'))
    return (84);
  if ((pos_tab[1][1] < '1' || pos_tab[1][1] > '8')
   || (pos_tab[2][1] < '1' || pos_tab[2][1] > '8'))
    return (84);
  if ((pos_tab[1][0] != pos_tab[2][0]) && (pos_tab[1][1] != pos_tab[2][1]))
    return (84);
  if ((posB[0] - posA[0] != pos_tab[0][0] - 49)
   && (posB[1] - posA[1] != pos_tab[0][0] - 49))
    return (84);
  return (0);
}

int init_map(char *str)
{
  char *s;
  char **pos_tab;
  int fd;
  int posA[2];
  int posB[2];

  fd = open (str, O_RDONLY);
  if (fd == -1)
    return (84);
  while (s = get_next_line (fd))
  {
    pos_tab = my_str_to_wordtab (s, ':');
    posA[0] = pos_tab[1][0] - 65;
    posA[1] = pos_tab[1][1] - 49;
    posB[0] = pos_tab[2][0] - 65;
    posB[1] = pos_tab[2][1] - 49;
    if (check_error(pos_tab, posA, posB) != 0)
      return (84);
    if (posA[0] == posB[0])
      for (int i = posA[1]; i <= posB[1]; i++)
        map[0][i][posA[0]] = pos_tab[0][0];
    if (posA[1] == posB[1])
      for (int i = posA[0]; i <= posB[0]; i++)
        map[0][posA[1]][i] = pos_tab[0][0];
  }
  return (0);
}

void disp_map(int id)
{
  int i;
  int j;
  int y;
  if (id == 0)
    write (0, "my positions:\n", 14);
  else
    write(0, "enemy's positions:\n", 19);
  write(0, " |A B C D E F G H\n", 18);
  write(0, "-+---------------\n", 18);
  i = 0;
  y = 1;
  while (i < 8)
  {
    j = 0;
    my_putnbr(y);
    write(0, "|", 1);
    while (map[id][i][j])
    {
      write(0, my_strcat(map[id][i][j], " "), 2);
      j++;
    }
    write(0, "\n", 1);
    y++;
    i++;
  }
}

int disp_usage()
{
  write(1, "USAGE\n", 6);
  write(1, "\t./navy [first_player_pid] navy_positions\n", 42);
  write(1, "\nDESCRIPTION\n", 13);
  write(1, "\tfirst_player_pid\tonly for the 2nd player.  pid of the first player.\n", 69);
  write(1, "\tnavy_positions\t\tfile representing the positions of the ships.\n", 63);
  return (0);
}

int main(int ac, char **av)
{
  char *s;

  if (ac <= 1 || init_map(av[1]) != 0)
    return (84);
  if (my_strcmp(av[1], "-h") == 0)
    return (disp_usage());
  handler(SIGUSR1);
  handler(SIGUSR2);
  if (av[2] != NULL)
  {
    send_msg(my_getnbr(av[2]), HELLO, 0);
  }
  game ();
  return (0);
}
