/*
** zappy.h for zappy in PSU_2016_zappy/Zappy_server/include/
**
** Made by Mewen Le Reste
** Login   <mewen.lereste@epitech.eu>
**
** Started on  Mon Jun 26 12:16:18 2017 Mewen Le Reste
** Last update Sun Jul  2 23:11:51 2017 Mewen Le Reste
*/

#ifndef ZAPPY_H_
# define ZAPPY_H_

# include <stdio.h>
# include <string.h>
# include <time.h>
# include "list.h"
# include "rbuffer.h"

# define NBRESSOURCE	6
# define READSIZE	4096
# define LINEMATE	0
# define DERAUMERE	1
# define SIBUR		2
# define MENDIANE	3
# define PHIRAS		4
# define THYSTAME	5
# define MAXCONNECTION	200
# define UP		0
# define LEFT		90
# define DOWN		180
# define RIGHT		270

# define TEAM1			"Team1"
# define TEAM2			"Team2"
# define TEAM3			"Team3"
# define TEAM4			"Team4"
# define BCTMSG			"bct %d %d %d %d %d %d %d %d %d"
# define CONNECTCLIENT		"[+] Client connected on fd "
# define DISCONNECTCLIENT	"[-] Client disconnected on fd "
# define DEADCLIENT		"[-] Player dead on fd "
# define TCPSUCESS		"[+] Server: TCP initialized\n"
# define SOCKETSUCESS		"[+] Server: Socket created\n"
# define BINDSUCESS		"[+] Server: Binded to "
# define LISTENSUCESS		"[+] Server: Listening to "
# define TCPERROR		"[-] Server: Cannot find TCP protocol\n"
# define SOCKETERROR		"[-] Server: Cannot create the socket\n"
# define BINDERROR		"[-] Server: Cannot bind to the port "
# define LISTENERROR		"[-] Server: Cannot listen to the port "
# define GRAPHICTEAM		"GRAPHIC"
# define HEIGHTERROR		"Error: height must be between 10 and 1000\n"
# define WIDTHERROR		"Error: width must be between 10 and 1000\n"
# define NOTENOUGHPARAM		"Error: Not enough parameter given\n"
# define NOPARAM		"Error: No parameter given"
# define SEEUSAGE		"Try -help for more information\n"
# define USAGE1			" -p port -x width -y height "
# define USAGE2			"-n name1 name2 ...  -c clientsNb -f freq\n"
# define USAGEPORT		"\tport\t\tis the port number\n"
# define USAGEWIDTH		"\twidth\t\tis the width of the world\n"
# define USAGEHEIGHT		"\theight\t\tis the height of the world\n"
# define USAGENAME		"\tnameX\t\tis the name of the team X\n"
# define USAGECLIENT1		"\tclientsNb\t"
# define USAGECLIENT2		"is the number of authorized clients per team\n"
# define USAGEFREQ1		"\tfreq\t\t"
# define USAGEFREQ2		"is the reciprocal of time unit for execution of actions\n"
# define BADPARAMSVIEWER	"sbp"
# define DEAD			"dead"
# define WELCOME		"Welcome"
# define BADCMDVIEWER		"suc"
# define KOPLAYER		"ko"
# define OKPLAYER		"ok"
# define END			"end_"
# define ENDINCANT		"end_Incantation"
# define MICHEL			"Michel qui clignote"
# define ELEVATION		"Elevation underway"

# define CURRCELLF	zappy->cells[y][x].food
# define CURRCELLR	zappy->cells[y][x].ressources
# define MAPWIDTH	zappy->options.width
# define MAPHEIGHT	zappy->options.height

typedef enum		e_type
{
  PLAYER,
  VIEWER,
  WAITER
}			t_type;

typedef struct		s_timer
{
  clock_t		timer;
  unsigned int		frequence;
  unsigned int		time_unit;
  bool			set;
}			t_timer;

typedef struct		s_team
{
  unsigned int		nb_client;
  char			*name;
}			t_team;

typedef struct		s_options
{
  unsigned int		port;
  unsigned int		width;
  unsigned int		height;
  unsigned int		nb_client;
  t_team		*team;
  unsigned int		frequence;
  bool			debug;
}			t_options;

typedef struct		s_cell
{
  int			x;
  int			y;
  unsigned int		food;
  unsigned int		ressources[NBRESSOURCE];
  unsigned int		nb_player;
  struct s_cell		*left;
  struct s_cell		*right;
  struct s_cell		*up;
  struct s_cell		*down;
}			t_cell;

typedef	struct		s_egg
{
  t_cell		*cell;
  t_timer		hatching;
  t_timer		alive;
  unsigned int		food;
  char			*team;
  int			idx;
  int			by;
  bool			hatch;
}			t_egg;

typedef	struct		s_client
{
  t_timer		timer;
  t_type		type;
  t_cell		*cell;
  t_timer		alive;
  bool			from_egg;
  unsigned int		food;
  unsigned int		level;
  int			angle;
  char			*team;
  unsigned int		inventory[NBRESSOURCE];
  char			**command;
  int			fd;
  char			*buffer;
  t_rbuffer		*ring_buffer;
  bool			treat;
  bool			read_more;
  t_list		*message;
}			t_client;

typedef struct		s_zappy
{
  int			socket;
  int			fd_max;
  fd_set		fd_read;
  fd_set		fd_write;
  t_client		*current;
  t_type		current_type;
  t_options		options;
  t_cell		**cells;
  t_list		*eggs;
  t_list		*players;
  t_list		*viewer;
  t_list		*waiter;
}			t_zappy;

/*******************
 * Timer functions *
 *******************/
bool			is_over(t_timer *);
void			start(t_zappy *, t_timer *, unsigned int);

/***********************************
 * Function for the client request *
 ***********************************/
bool			find_command_player(t_zappy *, const char *);
bool			find_command_viewer(t_zappy *, const char *);
bool			find_command_waiter(t_zappy *, const char *);
int			find_flag(const char	**av, int ac, t_options *op);
int			nb_len(unsigned int);

/*****************
 * Map functions *
 *****************/
bool			generate_map(t_zappy *, bool, bool, bool);
bool			init_map(t_zappy *);
void			delete_map(t_zappy *);
bool			send_bct(t_zappy *, unsigned int, unsigned int, bool);
char			*send_cell(t_zappy *, char *, t_cell *, unsigned int);
void			connect_map(t_zappy *);

/*******************
 * Zappy functions *
 *******************/
bool			check_player(t_zappy *);
bool			check_egg(t_zappy *);
bool			init_zappy(t_zappy *);
void			delete_zappy(t_zappy *);
bool			read_client(t_zappy *, bool);
void			debug(t_zappy *);
bool			select_zappy(t_zappy *);

/****************
 * Egg function *
 ****************/
bool			add_egg(t_zappy *);
bool			hatch_egg(t_zappy *, t_egg *);
void		 	remove_egg(t_zappy *, int);
int			connect_egg(t_zappy *, int);

/*******************
 * Client function *
 *******************/
bool			init_client(t_zappy *, int, const char *, t_type);
void			delete_client(t_client *);
void			remove_client(t_zappy *, int, t_type);
bool			switch_list(t_zappy *, int, t_type);
bool			send_pdi(t_zappy *, const t_client *);
bool			send_to(t_client *, const char *);
bool			send_to_viewer(t_zappy *, const char *);
bool			send_client_to_viewer(t_zappy *, const t_client *);
bool			send_egg_to_viewer(t_zappy *, const t_egg *);

/******************
 * Misc functions *
 ******************/
bool			sort_cmd(t_zappy *);
void			free_team(t_team *);
bool			is_num(const char *);
void			usage(const char *);
bool			_strcmp(const char *, const char *);
void			free_double(char **);
char			**split(const char *, char);
char			*trim(const char *);
void			win(t_zappy *);

#endif /* !ZAPPY_H_ */
