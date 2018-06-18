/*
** flags.h for zappy in PSU_2016_zappy/Zappy_server/include/
**
** Made by Mewen Le Reste
** Login   <mewen.lereste@epitech.eu>
**
** Started on  Mon Jun 26 15:33:28 2017 Mewen Le Reste
** Last update Tue Jun 27 17:24:32 2017 Mewen Le Reste
*/

#ifndef FLAGS_H_
# define FLAGS_H_

# include "zappy.h"

# define NBFLAG	8

typedef	struct	s_flag
{
  char		*command;
  int		(*fct)(const char **, int, int *, t_options *);
}		t_flag;

int		help(const char **, int, int *, t_options *);
int		set_debug(__attribute__((unused))const char **,
			  __attribute__((unused))int,
			  __attribute__((unused))int *, t_options *);
int		set_frequence(const char **, int, int *, t_options *);
int		set_height(const char **, int, int *, t_options *);
int		set_names(const char **, int, int *, t_options *);
int		set_nbclient(const char **, int, int *, t_options *);
int		set_port(const char **, int, int *, t_options *);
int		set_width(const char **, int, int *, t_options *);

#endif /* !FLAGS_H_ */
