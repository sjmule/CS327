void displayStats()
{
	mvprintw(0, 0, "Player's stats");

	std::vector<std::string>
	char** menu = (char**) malloc(80 * sizeof(char*));
	int line = 0;
	char* str = (char*) malloc(40);
	sprintf(str, "Health: %d", kirito->hp);
	menu[line++] = str;
	if(kirito->equip[0] != NULL)
	{
		sprintf(str, "Damage (%s): %d+%dd%d", kirito->equip[0]->name, kirito->equip[0]->damage.get_base(),
			kirito->equip[0]->damage.get_number(), kirito->equip[0]->damage.get_sides());
		menu[line++] = str;
	}
	else
	{
		menu[line++] = "Damage (Empty): 0+1d4";
	}
	for(int i = 0; i < 12; ++i)
	{
		if(kirito->equip[i] != NULL)
			menu[line++] = " +" + kirito->equip[i]->name + ": " + kirito->equip[i]->damage.get_base() +
			"+" + kirito->equip[i]->damage.get_number() + "d" + kirito->equip[i]->damage.get_sides();
	}
	menu[line++] = "Dodge: 0";
	for(int i = 0; i < 12; ++i)
	{
		if(kirito->equip[i] != NULL)
			menu[line++] = " +" + kirito->equip[i]->name + ": " + kirito->equip[i]->dodge;
	}
	menu[line++] = "Defence: 0";
	for(int i = 0; i < 12; ++i)
	{
		if(kirito->equip[i] != NULL)
			menu[line++] = " +" + kirito->equip[i]->name + ": " + kirito->equip[i]->defence;
	}
	int speed = kirito->speed;
	int weight = 0;
	for(int i = 0; i < 12; ++i)
	{
		if(kirito->equip[i] != NULL)
		{
			speed += kirito->equip[i]->speed;
			weight += kirito->equip[i]->weight;
		}
	}
	for(int i = 0; i < 10; ++i)
	{
		if(kirito->inventory[i] != NULL)
			weight += kirito->inventory[i]->weight;
	}
	if(weight < 25)
	{
		menu[line++] = "Weight (light): " + weight;
		menu[line++] = "Speed: " + speed;
	}
	else if(weight >= 25 && weight <= 40)
	{
		menu[line++] = "Weight (medium): " + weight;
		menu[line++] = "Speed (-2): " + (speed - 2);
	}
	else if(weight >= 41 && weight <= 55)
	{
		menu[line++] = "Weight (heavy): " + weight;
		menu[line++] = "Speed (-4): " + (speed - 4);
	}
	else if(weight >= 56)
	{
		menu[line++] = "Weight (over encumbered): " + weight;
		menu[line++] = "Speed (-6): " + (speed - 2);
	}

	int offset = 0;
	while(1)
	{
		for(int i = offset, int j = 1; j < 22 && i < line - 1; ++j, ++i)
		{
			mvprintw(j, 0, monList[i]);
		}
		for(; j < 22; ++j)
		{
			for(i = 0; i < X; ++i)
			{
				mvaddch(j, i, ' ');
			}
		}
		refresh();
		int ch = getch();
		if(ch == KEY_UP)
		{
			if(offset != 0)
				--offset;
		}
		if(ch == KEY_DOWN)
		{
			if(offset != (line - 1))
				++offset;
		}
		if(ch == 27)
			break;
	}

	delete[] menu;
}
