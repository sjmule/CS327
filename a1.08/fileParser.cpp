#include "fileParser.h"

static inline void eat_whitespace(ifstream &file)
{
  while (isspace(file.peek())) {
    file.get();
  }
}

static inline void eat_blankspace(ifstream &file)
{
  while (isblank(file.peek())) {
    file.get();
  }
}

void parseMonseters(ifstream &file, string *line)
{
  bool name, sym, color, desc, speed, dam, hp, abil, end;
  name = sym = color = desc = speed = dam = hp = abil = end = false;

  Monster mon;

  if(*line != "BEGIN")
  {
    file >> *line;
    while(*line != "BEGIN" && file.peek() != EOF)
      file >> *line;
  }
  if(file.peek() == EOF)
    return;
  file >> *line;
  if(*line != "MONSTER")
    return;

  int count;
  for(file >> *line, count = 0; count < 8; count++)
  {
    if(*line == "NAME")
    {
      if(!name)
      {
        eat_blankspace(file);

        if(file.peek() == '\n')
          return;

        getline(file, mon.name);
        name = true;
      }
      else
        return;
    }
    else if(*line == "DESC")
    {
      if(!desc)
      {
        eat_blankspace(file);

        if(file.peek() == '\n')
          return;

        file.get();

        while(file.peek() != EOF)
        {
          getline(file, *line);
          if(line->length() > 77)
            return;
          line->push_back('\n');

          if(*line == ".\n")
            break;

          mon.description += *line;
        }

        mon.description.erase(mon.description.length() -1);

        if(*line != ".\n")
          return;

        file >> *line;

        desc = true;
      }
      else
        return;
    }
    else if(*line == "SYMB")
    {
      if(!sym)
      {
        eat_blankspace(file);
        if(file.peek() == '\n')
          return;

        mon.symbol = file.get();

        eat_blankspace(file);
        if(file.peek() != '\n')
          return;

        file >> *line;

        sym = true;
      }
      else
        return;
    }
    else if(*line == "COLOR")
    {
      if(!color)
      {
        eat_blankspace(file);
        if(file.peek() != '\n')
          return;

        file >> *line;
        if(*line == "RED")
				{
				  mon.color = 1;
          color = true;
        }
        else if(*line == "GREEN")
				{
				  mon.color = 2;
				  color = true;
				}
				else if(*line == "BLUE")
			  {
				  mon.color = 4;
				  color = true;
				}
				else if(*line == "CYAN")
				{
				  mon.color = 6;
				  color = true;
				}
				else if(*line == "YELLOW")
			  {
				  mon.color = 3;
				  color = true;
				}
				else if(*line == "MAGENTA")
			  {
				  mon.color = 5;
				  color = true;
				}
				else if(*line == "WHITE")
				{
				  mon.color = 7;
				  color = true;
				}
				else if(*line == "BLACK")
				{
				  mon.color = 0;
				  color = true;
				}
        else
          return;

        while(file.peek() != '\n')
        {
          file.get();
        }
        file >> *line;
      }
      else
        return;
    }
    else if(*line == "SPEED")
    {
      if(!speed)
      {
        int base;
        unsigned int die, sides;
        eat_blankspace(file);
        if(file.peek() != '\n')
          return;

        file >> *line;

        if(sscanf(line->c_str(), "%d+%dd%d", &base, &die, &sides) != 3)
          return;

        mon.speedDice.set(base, die, sides);

        file >> *line;

        speed = true;
      }
      else
        return;
    }
    else if(*line == "HP")
    {
      if(!hp)
      {
        int base;
        unsigned int die, sides;
        eat_blankspace(file);
        if(file.peek() != '\n')
          return;

        file >> *line;

        if(sscanf(line->c_str(), "%d+%dd%d", &base, &die, &sides) != 3)
          return;

        mon.hpDice.set(base, die, sides);

        file >> *line;

        hp = true;
      }
      else
        return;
    }
    else if(*line == "DAM")
    {
      if(!dam)
      {
        int base;
        unsigned int die, sides;
        eat_blankspace(file);
        if(file.peek() != '\n')
          return;

        file >> *line;

        if(sscanf(line->c_str(), "%d+%dd%d", &base, &die, &sides) != 3)
          return;

        mon.damageDice.set(base, die, sides);

        file >> *line;

        dam = true;
      }
      else
        return;
    }
    else if(*line == "ABIL")
    {
      if(!abil)
      {
        eat_blankspace(file);
        if(file.peek() != '\n')
          return;

        while(file.peek() != '\n')
        {
          file >> *line;

          if(*line == "SMART")
						mon.attributes = mon.attributes | INTELLIGENT;
					else if(*line == "TELE")
						mon.attributes = mon.attributes | TELEPATHIC;
					else if(*line == "TUNNEL")
						mon.attributes = mon.attributes | TUNNELING;
					else if(*line == "ERRATIC")
						mon.attributes = mon.attributes | ERRATIC;
					else if(*line == "PASS")
						mon.attributes = mon.attributes | PASS;
					else
					  return;

          eat_blankspace(file);
        }
        file >> *line;
      }
      else
        return;
    }
    else
      return;
  }

  if(*line != "END")
    return;

  eat_blankspace(file);
  if(file.peek() != '\n' && file.peek() != EOF)
    return;
  file >> *line;

  aincrad->monsters.push_back(mon);
}

void loadMonsters(char* path)
{
	ifstream file;
	string str(path);
	str += "/monster_desc.txt";

	file.open(str.c_str());

	if(!file)
	{
		printf("Unable to open monster list for reading.\n");
		exit(-1);
	}

	string line;

  eat_whitespace(file);

	getline(file, line);

	if(line != "RLG327 MONSTER DESCRIPTION 1")
	{
		printf("File incorrect version, quitting\n");
		exit(-1);
	}

  file >> line;
	while(file.peek() != EOF)
    parseMonseters(file, &line);

	file.close();
}
