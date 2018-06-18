//
// ai.cpp for zappy in /home/ambroise/PSU_2016_zappy/Zappy_ai
// 
// Made by ambroise
// Login   <ambroise.damier@epitech.eu>
// 
// Started on  Sat Jul  1 22:55:57 2017 ambroise
// Last update Sun Jul  2 21:37:32 2017 ambroise
//

#include "ai.hpp"
#include "time.h"

Ai::Ai(std::string name, int fd)
{
  _fd = fd;
  _name = name;


  _lvl = 1;
  _status = 0;

  _food = 10;
  _linemate = 0;
  _deraumere = 0;
  _sibur = 0;
  _mendiane = 0;
  _phiras = 0;
  _thystame = 0;
}

Ai::~Ai()
{
}

int	Ai::run()
{
  bool	end = false;
  std::string buf;

  std::srand(time(NULL));
  while (end != true)
    {
      if (checkElevation() != true)
	{
	  if (_lvl == 1)
	    {
	      if (getobj1() == 84)
		return 84;
	    }
	  else
	    {
	      // if (_food < 7)
	      // 	if (searchFood() != true)
	      // 	  return 84;
	      if (mooveRandom() == 84)
	      	return 84;
	      if (searchObj() == 84)
	      	return 84;
	    }
	}
      else
	{

	  if (_lvl == 1)
	    {
	      if(cleanMap() == 84)
		return 84;	      
	      if (setobj1() == 84)
		return 84;
	    }
	  
	  else
	    {
	      if (sendFull() == 84)
		return 84;
	      if(cleanMap() == 84)
		return 84;
	      if (setObj() == 84)
	      	return 84;
	    }
	  // if (command("Broadcast ZZroth") == 84)
	  //   return 84;
	  std::cout << "Incantation" << std::endl;
	  dprintf(_fd, "%s\n", "Incantation");
	  bool end2 = false;

	  while (end2 != true)
	    {
	      buf = my_getline(_fd);
	      std::cout << buf << std::endl;
	      // if (buf[0] == 'm')
	      // 	{
	      // 	}
	      if (buf[0] == 'd')
		{
		  std::cout << "dead" << std::endl;
		  exit(84);
		}
	      else if (buf[0] == 'k' && buf[1] == 'o')
		{
		  // if (command("Forward") == 84)
		  //   return 84;
		  end2 = true;
		}
	      else if (buf[0] == 'E')
		{
		  std::cout << "L'incantation part sur de bonnes bases" << std::endl;
		}
	      else if (buf[0] == 'C')
		{
		  std::cout << "GG GROS LEVEL" << std::endl;
		  _lvl++;
		  end2 = true;
		}
	      else if (buf[0] != 'm')
		end2 = true;
	    }
	  // if (command("Broadcast YYroth") == 84)
	  //   return 84;
	}
    }
  return 0;
}


int	Ai::setObj()
{
  if (_lvl == 2)
    {
      if (putObj("linemate") == 84)
	return 84;
      if (putObj("deraumere") == 84)
	return 84;
      if (putObj("sibur") == 84)
	return 84;
    }
  if (_lvl == 3)
    {
      if (putObj("linemate") == 84)
	return 84;
      if (putObj("linemate") == 84)
	return 84;
      if (putObj("sibur") == 84)
	return 84;
      if (putObj("phiras") == 84)
	return 84;
      if (putObj("phiras") == 84)
	return 84;
    }
  if (_lvl == 4)
    {
      if (putObj("linemate") == 84)
	return 84;
      if (putObj("deraumere") == 84)
	return 84;
      if (putObj("sibur") == 84)
	return 84;
      if (putObj("sibur") == 84)
	return 84;
      if (putObj("phiras") == 84)
	return 84;
    }
  if (_lvl == 5)
    {
      if (putObj("linemate") == 84)
	return 84;
      if (putObj("deraumere") == 84)
	return 84;
      if (putObj("deraumere") == 84)
	return 84;
      if (putObj("sibur") == 84)
	return 84;
      if (putObj("mendiane") == 84)
	return 84;
      if (putObj("mendiane") == 84)
	return 84;
      if (putObj("mendiane") == 84)
	return 84;

    }
  if (_lvl == 6)
    {
      if (putObj("linemate") == 84)
	return 84;
      if (putObj("deraumere") == 84)
	return 84;
      if (putObj("deraumere") == 84)
	return 84;
      if (putObj("sibur") == 84)
	return 84;
      if (putObj("sibur") == 84)
	return 84;
      if (putObj("sibur") == 84)
	return 84;
      if (putObj("phiras") == 84)
	return 84;
    }
  if (_lvl == 7)
    {
      if (putObj("linemate") == 84)
	return 84;
      if (putObj("linemate") == 84)
	return 84;
      if (putObj("deraumere") == 84)
	return 84;
      if (putObj("deraumere") == 84)
	return 84;
      if (putObj("sibur") == 84)
	return 84;
      if (putObj("sibur") == 84)
	return 84;
      if (putObj("mendiane") == 84)
	return 84;
      if (putObj("mendiane") == 84)
	return 84;
      if (putObj("phiras") == 84)
	return 84;
      if (putObj("phiras") == 84)
	return 84;
      if (putObj("thystame") == 84)
	return 84;
    }
  return 0;
}

int	Ai::joinBro()
{
  std::string buf;
  bool end2 = false;
  int	tmp = 1;

  while (end2 != true)
    {
      buf = my_getline(_fd);
      std::cout << buf << std::endl;
      if (buf[0] == 'd')
	{
	  std::cout << "dead" << std::endl;
	  exit(84);

	}
      else if (buf[0] == 'm')
	{
	  // if (buf[11] == 'Z')
	  //   _status = 1;
	  // if (buf[11] == 'Y')
	  //   _status = 0;
	  if (buf[11] == 'P' && (buf[12] - '0') == _lvl)
	    tmp++;
	  if (tmp >= maxLvl())
	    {
	      if (command("Left") == 84)
		return 84;
	      if (command("Left") == 84)
		return 84;
	      if (command("Forward") == 84)
		return 84;
	      return 0;
	    }
	  if ((buf[11] - '0') == _lvl)
	    {
	      if (buf[8] == '0')
		{
		  if (sendP("Broadcast P", tmp) == 84)
		    return 84;
		  return 0;
		}
	      if (buf[8] == '1')
		{
		  if (command("Forward") == 84)
		    return 84;
		}
	      if (buf[8] == '2')
		{
		  if (command("Forward") == 84)
		    return 84;
		}
	      if (buf[8] == '3')
		{
		  if (command("Left") == 84)
		    return 84;
		}
	      if (buf[8] == '4')
		{
		  if (command("Left") == 84)
		    return 84;
		}
	      if (buf[8] == '5')
		{
		  if (command("Left") == 84)
		    return 84;
		  if (command("Left") == 84)
		    return 84;
		}
	      if (buf[8] == '6')
		{
		  if (command("Right") == 84)
		    return 84;
		}
	      if (buf[8] == '7')
		{
		  if (command("Right") == 84)
		    return 84;
		}
	      if (buf[8] == '8')
		{
		  if (command("Forward") == 84)
		    return 84;
		}
	    }
	}
    }
  return 0;
}

int	Ai::sendP(std::string str, int tmp)
{
  std::string buf;
  bool end2 = false;

  std::cout << str << std::endl;
  dprintf(_fd, "%s%d\n", str.c_str(), _lvl);
  while (end2 != true)
    {
      buf = my_getline(_fd);
      std::cout << buf << std::endl;
      if (buf[0] == 'd')
	{
	  std::cout << "dead" << std::endl;
	  exit(84);

	}
      else if (buf[0] == 'o' && buf[1] == 'k')
	{
	  bool end = false;
	  while (end != true)
	    {
	      buf = my_getline(_fd);
	      std::cout << buf << std::endl;
	      if (buf[0] == 'd')
		{
		  std::cout << "dead" << std::endl;
		  exit(84);
		}
	      if (buf[0] == 'C')
		{
	          std::cout << "GG GROS LEVEL" << std::endl;
		  _lvl++;
		  end = true;
		  return 0;
		}
	      else if (buf[0] == 'k' && buf[1] == 'o')
		{
		  return 0;
		}
	    }
	  return 0;
	}
      else if (buf[0] == 'm')
	{
	  if (buf[11] == 'P' && (buf[12] - '0') == _lvl)
	    tmp++;
	  // if (buf[11] == 'Z')
	  //   _status = 1;
	  // if (buf[11] == 'Y')
	  //   _status = 0;
	  if (tmp >= maxLvl())
	    return 0;
	}
    }
  return 0;
}

int	Ai::command(std::string str)
{
  std::string buf;
  bool end2 = false;

  std::cout << str << std::endl;
  dprintf(_fd, "%s\n", str.c_str());
  while (end2 != true)
    {
      buf = my_getline(_fd);
      std::cout << buf << std::endl;
      if (buf[0] == 'd')
	{
	  std::cout << "dead" << std::endl;
	  exit(84);
	}
      else if (buf[0] == 'o' && buf[1] == 'k')
	return 0;
      // else if (buf[0] == 'm')
      // 	{
	  
	  // if (buf[11] == 'Z')
	  //   _status = 1;
	  // if (buf[11] == 'Y')
	  //   _status = 0;
      // }
    }
  return 0;
}

int	Ai::sendFull()
{
  std::string buf;
  bool end2 = false;

  std::cout << "Broadcast " << _lvl << " FULL" << std::endl;
  dprintf(_fd, "Broadcast %d FULL\n", _lvl);
  while (end2 != true)
    {
      buf = my_getline(_fd);
      std::cout << buf << std::endl;
      if (buf[0] == 'd')
	{
	  std::cout << "dead" << std::endl;
	  exit(84);
	}
      else if (buf[0] == 'o' && buf[1] == 'k')
	{
	  if (sendDir() == 84)
	    return 84;
	  return 0;
	}
      else if (buf[0] == 'm')
	{
	  if ((buf[11] - '0') == _lvl)
	    {
	      if (joinBro() == 84)
	      	return 84;
	      return 0;
	    }
	  // if (buf[11] == 'Z')
	  //   _status = 1;
	  // if (buf[11] == 'Y')
	  //   _status = 0;
	}
    }
  return 0;
}

int	Ai::sendDir()
{
  std::string buf;
  bool end2 = false;
  int	n = 1;

  std::cout << "Broadcast " << _lvl << " FULL" << std::endl;
  dprintf(_fd, "Broadcast %d FULL\n", _lvl);
  while (end2 != true)
    {
      buf = my_getline(_fd);
      std::cout << buf << std::endl;
      if (buf[0] == 'd')
	{
	  std::cout << "dead" << std::endl;
	  exit(84);
	}
      else if (buf[0] == 'm')
	{
	  // if (buf[11] == 'Z')
	  //   _status = 1;
	  // if (buf[11] == 'Y')
	  //   _status = 0;
	  if (buf[8] == '0')
	    n++;
	  if (n >= maxLvl())
	    {
	      std::cout << "LETS GOOO" << std::endl;
	      if (sendEnd() == 84)
		return 84;
	      return 0;
	    }
	}
      else if (buf[0] == 'o' && buf[1] == 'k')
	{
	  std::cout << "Broadcast " << _lvl << " FULL" << std::endl;
	  dprintf(_fd, "Broadcast %d FULL\n", _lvl);
	}
    }
  return 0;
}

int	Ai::maxLvl()
{
  if (_lvl == 2 || _lvl == 3)
    return 2;
  if (_lvl == 4 || _lvl == 5)
    return 4;
  if (_lvl == 6 || _lvl == 7)
    return 6;
  return 0;
}
 
int	Ai::sendEnd()
{
  std::string buf;
  bool end2 = false;

  std::cout << "Broadcast END" << std::endl;
  dprintf(_fd, "Broadcast END\n");
  while (end2 != true)
    {
      buf = my_getline(_fd);
      std::cout << buf << std::endl;
      if (buf[0] == 'd')
	{
	  std::cout << "dead" << std::endl;
	  exit(84);
	}
      else if (buf[0] == 'o' && buf[1] == 'k')
	{
	  return 0;
	}
      // else if (buf[0] == 'm')
      // 	{
      // 	  if (buf[11] == 'Z')
      // 	    _status = 1;
      // 	  if (buf[11] == 'Y')
      // 	    _status = 0;
      // 	}
    }
  return 0;
}

int	Ai::putObj(std::string str)
{
  std::string buf;
  bool end2 = false;

  std::cout << "Set " << str << std::endl;
  dprintf(_fd, "Set %s\n", str.c_str());
  while (end2 != true)
    {
      buf = my_getline(_fd);
      std::cout << buf << std::endl;
      if (buf[0] == 'd')
	{
	  std::cout << "dead" << std::endl;
	  exit(84);
	}
      // else if (buf[0] == 'm')
      // 	{
      // 	  if (buf[11] == 'Z')
      // 	    _status = 1;
      // 	  if (buf[11] == 'Y')
      // 	    _status = 0;
      // 	}
      else if (buf[0] == 'o' && buf[1] == 'k')
	return 0;
      else if (buf[0] == 'k' && buf[1] == 'o')
	return 0;
    }
  return 0;

}

int	Ai::setobj1()
{
  bool end2 = false;
  std::string buf;
  std::cout << "Set linemate" << std::endl;
  dprintf(_fd, "%s\n", "Set linemate");
  while (end2 != true)
    {
      buf = my_getline(_fd);
      std::cout << buf << std::endl;
      if (buf[0] == 'd')
	{
	  std::cout << "dead" << std::endl;
	  exit(84);
	}
      else if (buf[0] == 'o' && buf[1] == 'k')
	return 0;
      else if (buf[0] == 'k' && buf[1] == 'o')
	return 0;
      // else if (buf[0] == 'm')
      // 	{
      // 	  if (buf[11] == 'Z')
      // 	    _status = 1;
      // 	  if (buf[11] == 'Y')
      // 	    _status = 0;
      // 	}
    }
  return 0;
}

int	Ai::cleanMap()
{
  if (takeObj("food") == 84)
    return 84;
  if (takeObj("linemate") == 84)
    return 84;
  if (takeObj("deraumere") == 84)
    return 84;
  if (takeObj("sibur") == 84)
    return 84;
  if (takeObj("mendiane") == 84)
    return 84;
  if (takeObj("phiras") == 84)
    return 84;
  if (takeObj("thystame") == 84)
    return 84;
  if (updateInventory() == 84)
    return 84;

  bool end2 = false;
  std::string buf;
  std::cout << "Look" << std::endl;
  dprintf(_fd, "%s\n", "Look");
  while (end2 != true)
    {
      buf = my_getline(_fd);
      std::cout << buf << std::endl;
      if (buf[0] == 'd')
	{
	  std::cout << "dead" << std::endl;
	  exit(84);
	}
      else
	{
	  if (buf[0] == '[')
	    return 0;
	  // else if (buf[0] == 'm')
	  //   {
	  //     if (buf[11] == 'Z')
	  // 	_status = 1;
	  //     if (buf[11] == 'Y')
	  // 	_status = 0;
	  //   }
	}
      
    }
  return 0;
}

int	Ai::takeObj(std::string str)
{
  std::string buf;
  bool end2 = false;

  std::cout << str << std::endl;
  dprintf(_fd, "Take %s\n", str.c_str());
  while (end2 != true)
    {
      buf = my_getline(_fd);
      std::cout << buf << std::endl;
      if (buf[0] == 'd')
	{
	  std::cout << "dead" << std::endl;
	  exit(84);
	}
      else if (buf[0] == 'o' && buf[1] == 'k')
	return 0;
      else if (buf[0] == 'k' && buf[1] == 'o')
	return 0;
      else if (buf[0] == 'm')
	{
	  if ((buf[11] - '0') == _lvl)
	    {
	      if (joinBro() == 84)
	      	return 84;
	      return 0;
	    }
	  // if (buf[11] == 'Z')
	  //   _status = 1;
	  // if (buf[11] == 'Y')
	  //   _status = 0;
	}

    }
  return 0;
}

bool	Ai::checkElevation()
{
  if (updateInventory() == 84)
    exit(84);
  if (_lvl == 1)
    {
      if (_linemate >= 1)
	return true;
    }
  else if (_lvl == 2)
    {
      if (_linemate >= 1 && _deraumere >= 1 && _sibur >= 1)
	return true;
    }
  else if (_lvl == 3)
    {
      if (_linemate >= 2 && _sibur >= 1 && _phiras >= 2)
	return true;
    }
  else if (_lvl == 4)
    {
      if (_linemate >= 1 && _deraumere >= 1 && _sibur >= 2 && _phiras >= 1)
	return true;
    }
  else if (_lvl == 5)
    {
      if (_linemate >= 1 && _deraumere >= 2 && _sibur >= 1 && _mendiane >= 3)
	return true;
    }
  else if (_lvl == 6)
    {
      if (_linemate >= 1 && _deraumere >= 2 && _sibur >= 3 && _phiras >= 1)
	return true;
    }
  else if (_lvl == 6)
    {
      if (_linemate >= 2 && _deraumere >= 2 && _sibur >= 2 && _mendiane >= 2 && _phiras >= 2 && _thystame >= 1)
	return true;
    }  
  else
    std::cout << "trop high level" << std::endl;
  return false;
}

int	Ai::searchObj()
{
  if (takeObj("food") == 84)
    return 84;
  // if (_status == 1)
  //   return 0;
  if (_lvl == 2)
    {
      if (takeObj("linemate") == 84)
	return 84;
      if (takeObj("deraumere") == 84)
	return 84;
      if (takeObj("sibur") == 84)
	return 84;
    }
  if (_lvl == 3)
    {
      if (takeObj("linemate") == 84)
	return 84;
      if (takeObj("linemate") == 84)
	return 84;
      if (takeObj("sibur") == 84)
	return 84;
      if (takeObj("phiras") == 84)
	return 84;
      if (takeObj("phiras") == 84)
	return 84;
    }
  if (_lvl == 4)
    {
      if (takeObj("linemate") == 84)
	return 84;
      if (takeObj("deraumere") == 84)
	return 84;
      if (takeObj("sibur") == 84)
	return 84;
      if (takeObj("sibur") == 84)
	return 84;
      if (takeObj("phiras") == 84)
	return 84;
    }
  if (_lvl == 5)
    {
      if (takeObj("linemate") == 84)
	return 84;
      if (takeObj("deraumere") == 84)
	return 84;
      if (takeObj("deraumere") == 84)
	return 84;
      if (takeObj("sibur") == 84)
	return 84;
      if (takeObj("mendiane") == 84)
	return 84;
      if (takeObj("mendiane") == 84)
	return 84;
      if (takeObj("mendiane") == 84)
	return 84;

    }
  if (_lvl == 6)
    {
      if (takeObj("linemate") == 84)
	return 84;
      if (takeObj("deraumere") == 84)
	return 84;
      if (takeObj("deraumere") == 84)
	return 84;
      if (takeObj("sibur") == 84)
	return 84;
      if (takeObj("sibur") == 84)
	return 84;
      if (takeObj("sibur") == 84)
	return 84;
      if (takeObj("phiras") == 84)
	return 84;
    }
  if (_lvl == 7)
    {
      if (takeObj("linemate") == 84)
	return 84;
      if (takeObj("linemate") == 84)
	return 84;
      if (takeObj("deraumere") == 84)
	return 84;
      if (takeObj("deraumere") == 84)
	return 84;
      if (takeObj("sibur") == 84)
	return 84;
      if (takeObj("sibur") == 84)
	return 84;
      if (takeObj("mendiane") == 84)
	return 84;
      if (takeObj("mendiane") == 84)
	return 84;
      if (takeObj("phiras") == 84)
	return 84;
      if (takeObj("phiras") == 84)
	return 84;
      if (takeObj("thystame") == 84)
	return 84;
    }
  return 0;
}

int	Ai::getobj1()
{
  std::string buf;
  bool end = false;

  std::cout << "Take linemate" << std::endl;
  dprintf(_fd, "%s\n", "Take linemate");

  while (end != true)
    {
      buf = my_getline(_fd);
      std::cout << buf << std::endl;
      if (buf[0] == 'd')
	{
	  std::cout << "dead" << std::endl;
	  exit(84);
	}
      else if (buf[0] == 'o' && buf[1] == 'k')
	{
	  if (updateInventory() == 84)
	    return 84;
	  return 0;
	}
      // else if (buf[0] == 'm')
      // 	{
      // 	  if (buf[11] == 'Z')
      // 	    _status = 1;
      // 	  if (buf[11] == 'Y')
      // 	    _status = 0;
      // 	}
      else if (buf[0] == 'k' && buf[1] == 'o')
	{
	  bool end2 = false;
	  int	rand;

	  rand = (std::rand() % 10);
	  if (rand == 1)
	    {
	      std::cout << "Left" << std::endl;
	      dprintf(_fd, "%s\n", "Left");
	    }
	  else if (rand == 2)
	    {
	      std::cout << "Right" << std::endl;
	      dprintf(_fd, "%s\n", "Right");
	    }
	  else
	    {
	      std::cout << "Forward" << std::endl;
	      dprintf(_fd, "%s\n", "Forward");
	    }
	  while (end2 != true)
	    {
	      buf = my_getline(_fd);
	      std::cout << buf << std::endl;
	      if (buf[0] == 'd')
		{
		  std::cout << "dead" << std::endl;
		  exit(84);
		}
	      else if (buf[0] == 'o' && buf[1] == 'k')
	      	{
	      	  std::cout <<  "Take linemate" << std::endl;
	      	  dprintf(_fd, "%s\n", "Take linemate");
		  end2 = true;
	        }
	      else
		{
		  end2 = true;
		}
	    }
	}
      else
	{
	  end = true;
	}
    }
  return 0;
}

int	Ai::updateInventory()
{
  std::cout << "Inventory" << std::endl;
  dprintf(_fd, "%s\n", "Inventory");
  bool end2 = false;
  std::string buf;

  while (end2 != true)
    {
      buf = my_getline(_fd);
      std::cout << buf << std::endl;
      
      if (buf[0] == 'd')
	{
	  std::cout << "dead" << std::endl;
	  exit(84);
	}
      
      // else if (buf[0] == 'm')
      // 	{

      // 	  if ((buf[11] - '0') == _lvl)
      // 	    {
      // 	      if (joinBro() == 84)
      // 	      	return 84;
      // 	      return 0;
      // 	    }
      // 	  // if (buf[11] == 'Z')
      // 	  //   _status = 1;
      // 	  // if (buf[11] == 'Y')
      // 	  //   _status = 0;

      // 	}

      else if (buf[0] == '[')
	{
	  int n = 0;
	  while ((buf[n] < '0' || buf[n] > '9') && buf[n])
	    n++;
	  _food = buf[n] - '0';
	  n++;
	  if (buf[n] >= '0' && buf[n] <= '9')
	    {
	      _food = (_food * 10) + buf[n] - '0';
	      n++;
	    }
	  while ((buf[n] < '0' || buf[n] > '9') && buf[n])
	    n++;
	  _linemate = buf[n] - '0';
	  n++;
	  if (buf[n] >= '0' && buf[n] <= '9')
	    {
	      _linemate = (_linemate * 10) + buf[n] - '0';
	      n++;
	    }
	  while ((buf[n] < '0' || buf[n] > '9') && buf[n])
	    n++;
	  _deraumere = buf[n] - '0';
	  n++;	
	  if (buf[n] >= '0' && buf[n] <= '9')
	    {
	      _deraumere = (_deraumere * 10) + buf[n] - '0';
	      n++;
	    }
	  while ((buf[n] < '0' || buf[n] > '9') && buf[n])
	    n++;
	  _sibur = buf[n] - '0';
	  n++;
	  if (buf[n] >= '0' && buf[n] <= '9')
	    {
	      _sibur = (_sibur * 10) + buf[n] - '0';
	      n++;
	    }
	  while ((buf[n] < '0' || buf[n] > '9') && buf[n])
	    n++;
	  _mendiane = buf[n] - '0';
	  n++;
	  if (buf[n] >= '0' && buf[n] <= '9')
	    {
	      _mendiane = (_mendiane * 10) + buf[n] - '0';
	      n++;
	    }
	  while ((buf[n] < '0' || buf[n] > '9') && buf[n])
	    n++;
	  _phiras = buf[n] - '0';
	  n++;
	  if (buf[n] >= '0' && buf[n] <= '9')
	    {
	      _phiras = (_phiras * 10) + buf[n] - '0';
	      n++;
	    }
	  while ((buf[n] < '0' || buf[n] > '9') && buf[n])
	    n++;
	  _thystame = buf[n] - '0';
	  if (buf[n] >= '0' && buf[n] <= '9')
	    {
	      _thystame = (_thystame * 10) + buf[n] - '0';
	      n++;
	    }
	  end2 = true;
	}
      else
	end2 = true;
    }
  return 0;
}

int	Ai::mooveRandom()
{

  bool end2 = false;
  int	rand;
  std::string buf;

  rand = (std::rand() % 10);
  if (rand == 1)
    {
      std::cout << "Left" << std::endl;
      dprintf(_fd, "%s\n", "Left");
    }
  else if (rand == 2)
    {
      std::cout << "Right" << std::endl;
      dprintf(_fd, "%s\n", "Right");
    }
  else
    {
      std::cout << "Forward" << std::endl;
      dprintf(_fd, "%s\n", "Forward");
    }
  while (end2 != true)
    {
      buf = my_getline(_fd);
      std::cout << buf << std::endl;
      if (buf[0] == 'd')
	{
	  std::cout << "dead" << std::endl;
	  exit(84);
	}
      else if (buf[0] == 'm')
	{
	  // if (buf[11] == 'Z')
	  //   _status = 1;
	  // if (buf[11] == 'Y')
	  //   _status = 0;
	  if ((buf[11] - '0') == _lvl)
	    {
	      if (joinBro() == 84)
	      	return 84;
	      return 0;
	    }
	}

      else if (buf[0] == 'o' && buf[1] == 'k')
	end2 = true;
      else
	end2 = true;
    }
  return 0;
}

int	Ai::commandFork()
{
  bool end2 = false;
  std::string buf;

  std::cout << "Fork" << std::endl;
  dprintf(_fd, "%s\n", "Fork");
  while (end2 != true)
    {
      buf = my_getline(_fd);
      std::cout << buf << std::endl;
      if (buf[0] == 'd')
	{
	  std::cout << "dead" << std::endl;
	  exit(84);
	}
      else if (buf[0] == 'o' && buf[1] == 'k')
	end2 = true;
      // else if (buf[0] == 'm')
      // 	{
      // 	  if (buf[11] == 'Z')
      // 	    _status = 1;
      // 	  if (buf[11] == 'Y')
      // 	    _status = 0;
      // 	}
    }
  return 0;  
}

// bool	Ai::searchFood()
// {
//   std::string buf;
//   bool	end = false;

//   dprintf(fd, "%s\n", "Look");
//   while (end != true)
//     {
//       buf = my_getline(fd);
//       if (buf[0] == '[' && buf[1] != 'l')
// 	{
// 	  string arr[_range];
// 	  int	i = 0;

// 	  stringstream ssin(buf);
// 	  while (ssin.good() && i < _range)
// 	    {
// 	      ssin >> arr[i];
// 	      ++i;
// 	    }
	  
// 	}
      
//     }
// }
