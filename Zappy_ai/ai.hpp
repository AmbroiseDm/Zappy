/*
1;4402;0c** ai.h for ai in /home/ambroise/PSU_2016_zappy/Zappy_ai
** 
** Made by ambroise
** Login   <ambroise.damier@epitech.eu>
** 
** Started on  Tue Jun 27 20:12:12 2017 ambroise
// Last update Sun Jul  2 12:31:02 2017 ambroise
*/

#ifndef		AI_H_
# define	AI_H_

# include	<sys/socket.h>
# include	<netdb.h>
# include	<netinet/in.h>
# include	<arpa/inet.h>
# include	<unistd.h>
# include	<string.h>
# include	<stdlib.h>
# include	<stdio.h>
# include	<unistd.h>
# include	<sys/types.h>
# include	<sys/stat.h>
# include	<ifaddrs.h>
# include	<fcntl.h>

# include	<cstdlib>
# include	<iostream>
# include	<string>
# include	<fstream>
# include	<sstream>

class Ai
{
 private:
  int	_fd;
  std::string _name;
  int	_status;


  int	_lvl;

  int _food;
  int _linemate;
  int _deraumere;
  int _sibur;
  int _mendiane;
  int _phiras;
  int _thystame;

  
  
 public:
  Ai(std::string name, int fd);
  ~Ai();

  int	updateInventory();
  int	getobj1();
  bool	checkElevation();
  int	takeObj(std::string str);
  int	cleanMap();
  int	run();
  int	setobj1();
  int	mooveRandom();
  int	commandFork();
  int	searchObj();
  int	putObj(std::string str);
  int	setObj();
  int	sendFull();
  int	sendDir();
  int	sendEnd();
  int	joinBro();
  int	sendP(std::string, int);
  int	command(std::string);
  int	maxLvl();
};

std::string	my_getline(int fd);

# endif		/* AI_H_ */
