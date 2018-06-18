/*
1;4402;0c** main.c for main in /home/ambroise/PSU_2016_zappy/Zappy_ai
1;4402;0c** 
** Made by ambroise
** Login   <ambroise.damier@epitech.eu>
** 
** Started on  Wed Jun 21 12:49:38 2017 ambroise
// Last update Sun Jul  2 07:55:21 2017 ambroise
*/

#include "ai.hpp"

int	usage()
{
  std::cout << "USAGE:  ./zappy_ai -p port -n name -h machine" << std::endl;
  std::cout << "       port     is the port number" << std::endl;
  std::cout << "       name     is thie name of the team" << std::endl;
  std::cout << "       machine  is the name of the machine; localhost by default" << std::endl;
  return 84;
}

std::string	my_getline(int fd)
{
  std::string	buf;
  char		tmp[1];

  while (read(fd, tmp, 1) != -1)
    {
      if (tmp[0] == '\n')
	return buf;
      buf = buf + tmp[0];
    }
  return buf;
}

int	init(int fd, char *name)
{
  Ai	ai(std::string(name), fd);
  std::string buf;
  
  buf = my_getline(fd);
  std::cout << buf << std::endl;
  if (buf[0] == 'k' && buf[1] == 'o')
    return 84;
  dprintf(fd, "%s\n", name);
  buf = my_getline(fd);
  std::cout << buf << std::endl;
  if (buf[0] == 'k' && buf[1] == 'o')
    return 84;
  buf = my_getline(fd);
  if (buf[0] == 'k' && buf[1] == 'o')
    return 84;
  std::cout << buf << std::endl;
  if (buf[0] < '8')
    ai.commandFork();
  return ai.run();
}

int	join_server(int port, char *name, char *machine)
{
  struct protoent	*pe;
  struct sockaddr_in	s_in;
  int			fd;

  if (!(pe = getprotobyname("TCP")))
    return 84;
  if ((fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    return 84;
  s_in.sin_family = AF_INET;
  s_in.sin_port = htons(port);
  s_in.sin_addr.s_addr = inet_addr(machine);
  if (connect(fd, (struct sockaddr *)&s_in, sizeof(s_in)) == -1)
    {
      close(fd);
      return 84;
    }
  return init(fd, name);
}

int	check_args(int ac, char **av)
{
  if (ac != 7)
    return usage();
  else
    {
      if (av[1][0] != '-' || av[3][0] != '-' || av[5][0] != '-')
	return usage();
      else if (av[1][1] != 'p' || av[3][1] != 'n' || av[5][1] != 'h')
	return usage();
    }
  return 0;
}

int	main(int ac, char **av)
{
  if (check_args(ac, av) == 84)
    return 84;
  else
    return join_server(atoi(av[2]), av[4], av[6]);
  return 0;
}
