#include "fileParser.h"

void loadMonsters(char* path)
{
	string str(path);
	str += "/monster_desc.txt";
	ifstream file(str.c_str(), ifstream::in);

	if(!file)
	{
		printf("Unable to open monster list for reading.\n");
		exit(-1);
	}

	string line;
	getline(file, line);

	if(line.compare("RLG327 MONSTER DESCRIPTION 1"))
	{
		printf("File incorrect version, quitting\n");
		exit(-1);
	}

	while(1)
	{
		int name = 0;
		int sym = 0;
		int color = 0;
		int desc = 0;
		int speed = 0;
		int dam = 0;
		int hp = 0;
		int abil = 0;
		int end = 0;

		Monster mon;

		// getline(file, line);
		// while(line.compare("BEGIN MONSTER") && !file.eof())
		// {
		// 	cout << "Finding monster" << endl;
		// 	cout << line << endl;
		// 	getline(file, line);
		// }

		while(getline(file, line))
		{
			if(line.find("NAME") == 0)
			{
				mon.name = line.substr(5);
				++name;
			}

			if(line.find("SYMB") == 0)
			{
				if(line.length() > 6)
				{
					sym = -1;
					break;
				}
				mon.symbol = line.at(5);
				++sym;
			}

			if(line.find("COLOR") == 0)
			{
				//There's no good explination for the multiple colors if we don't care to do the extension in part 1.08
				//Since it was suggested in the discussion board, and no one said not to, we're going to only take the
				//first color and ignore the rest.
				string l = line.substr(6);
				char* co = new char[l.length() + 1];
				strcpy(co, l.c_str());
				string col(strtok(co, " "));
				if(col.compare("RED"))
				{
					mon.color = 1;
					++color;
				}
				else if(col.compare("GREEN"))
				{
					mon.color = 2;
					++color;
				}
				else if(col.compare("BLUE"))
				{
					mon.color = 4;
					++color;
				}
				else if(col.compare("CYAN"))
				{
					mon.color = 6;
					++color;
				}
				else if(col.compare("YELLOW"))
				{
					mon.color = 3;
					++color;
				}
				else if(col.compare("MAGENTA"))
				{
					mon.color = 5;
					++color;
				}
				else if(col.compare("WHITE"))
				{
					mon.color = 7;
					++color;
				}
				else if(col.compare("BLACK"))
				{
					mon.color = 0;
					++color;
				}
				else
				{
					color = -1;
					break;
				}
			}

			if(line.find("DESC") == 0)
			{
				string description;
				getline(file, line);
				while(line.compare(".") != 0)
				{
					description += line;
					if(description.length() > 77)
					{
						desc = -1;
						break;
					}
					getline(file, line);
				}
				if(desc == -1)
					break;
				else
				{
					mon.description = description;
					++desc;
				}
			}

			if(line.find("SPEED") == 0)
			{
				/*regex e("SPEED [0-9]+\\+[0-9]+d[0-9]+");
				if(regex_match(line, e))
				{
					speed = -1;
					break;
				}
				else
				{*/
					string part;
					for(unsigned int i = 6; i < line.length(); ++i)
					{
						if(line.at(i) == '+')
						{
							mon.speedDice.base = atoi(part.c_str());
							part = "";
						}
						else if(line.at(i) == 'd')
						{
							mon.speedDice.die = atoi(part.c_str());
							part = "";
						}
						else
							part += line.at(i);
					}
					mon.speedDice.sides = atoi(part.c_str());
					++speed;
				//}
			}

			if(line.find("DAM") == 0)
			{
				/*regex e("DAM [0-9]+\\+[0-9]+d[0-9]+");
				if(regex_match(line, e))
				{
					dam = -1;
					break;
				}
				else
				{*/
					string part;
					for(unsigned int i = 6; i < line.length(); ++i)
					{
						if(line.at(i) == '+')
						{
							mon.damageDice.base = atoi(part.c_str());
							part = "";
						}
						else if(line.at(i) == 'd')
						{
							mon.damageDice.die = atoi(part.c_str());
							part = "";
						}
						else
							part += line.at(i);
					}
					mon.damageDice.sides = atoi(part.c_str());
					++dam;
				//}
			}

			if(line.find("HP") == 0)
			{
				/*regex e("HP [0-9]+\\+[0-9]+d[0-9]+");
				if(regex_match(line, e))
				{
					hp = -1;
					break;
				}
				else
				{*/
					string part;
					for(unsigned int i = 6; i < line.length(); ++i)
					{
						if(line.at(i) == '+')
						{
							mon.hpDice.base = atoi(part.c_str());
							part = "";
						}
						else if(line.at(i) == 'd')
						{
							mon.hpDice.die = atoi(part.c_str());
							part = "";
						}
						else
							part += line.at(i);
					}
					mon.hpDice.sides = atoi(part.c_str());
					++hp;
				//}
			}

			if(line.find("ABIL") == 0)
			{
				if(line.length() > 4)
				{
					string l = line.substr(5);
					char* ab = new char[l.length() + 1];
					strcpy(ab, l.c_str());
					char* abilities = strtok(ab, " ");
					while(abilities != NULL)
					{
						string a(abilities);
						if(a.compare("SMART") == 0)
						{
							mon.attributes = mon.attributes | INTELLIGENT;
						}
						else if(a.compare("TELE") == 0)
						{
							mon.attributes = mon.attributes | TELEPATHIC;
						}
						else if(a.compare("TUNNEL") == 0)
						{
							mon.attributes = mon.attributes | TUNNELING;
						}
						else if(a.compare("ERRATIC") == 0)
						{
							mon.attributes = mon.attributes | ERRATIC;
						}
						else if(a.compare("PASS") == 0)
						{
							mon.attributes = mon.attributes | PASS;
						}
						else
						{
							abil = -1;
							break;
						}
						abilities = strtok(NULL, " ");
					}
					if(abil == -1)
						break;
				}
				++abil;
			}

			if(line.compare("END") == 0)
			{
				++end;
				break;
			}
		}

		if((name == 1) && (sym == 1) && (color == 1) && (desc == 1) && (speed == 1) && (dam == 1) && (hp == 1) && (abil == 1) && (end == 1))
			aincrad->monsters.push_back(mon);

		if(file.eof())
			break;
	}

	aincrad->numMonsters = aincrad->monsters.size();

	file.close();
}
