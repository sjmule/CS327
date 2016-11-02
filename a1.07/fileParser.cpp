#include "fileParser.h"

void loadMonsters(char* path)
{
	char str[80];
	strcat(str, path);
	strcat(str, "monster_desc.txt");
	iostream  file open(str);

	if(!file.is_open())
	{
		printf("Unable to open monster list for reading.\n");
		exit(-1);
	}

	string line;
	getline(file, line);

	if(line.compare("RLG327 MONSTER DESCRIPTION 1") != 0)
	{
		printf("File incorrect version, quitting\n");
		exit(-1);
	}
	
	while(1)
	{
		bool begin = false;
		bool name = false;
		bool sym = false;
		bool color = false;
		bool desc = false;
		bool speed = false;
		bool dam = false;
		bool hp = false;
		bool abil = false;
		bool end = false;

		Monster* mon = new Monster();

		while(getline(file, line))
		{
			if(line.compare("BEGIN MONSTER") == 0)
				begin = true;

			if(line.find("NAME") == 0)
			{

			}

			if(line.find("SYMB") == 0)
			{

			}

			if(line.find("COLOR") == 0)
			{

			}

			if(line.find("DESC") == 0)
			{

			}

			if(line.find("SPEED") == 0)
			{

			}

			if(line.find("DAM") == 0)
			{

			}

			if(line.find("HP") == 0)
			{

			}

			if(line.find("ABIL") == 0)
			{

			}

			if(line.compare("END") == 0)
			{
				end = true;
				break;
			}
		}

		if(begin && name && sym && color && desc && speed && dam && hp && abil && end)
			aincrad->monsters.push_back(mon);

		if(file.eof())
			break;
	}

	file.close();
}
