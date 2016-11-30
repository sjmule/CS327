#include "dungeon.h"
#include "object.h"

void loadObjects()
{
  unsigned int i;
  for(i = 0; i < aincrad->object_descriptions.size(); ++i)
  {
    object_description objDesc = aincrad->object_descriptions.at(i);
    Object obj;
    obj.name = objDesc.name;
    obj.description = objDesc.description;
    obj.symbol = object_symbol[objDesc.type];
    // unsigned int color = objDesc.color;
		// init_pair(colors_lookup[color].value, colors_lookup[color].value, COLOR_BLACK);
    obj.color = objDesc.color;
    obj.hit = objDesc.hit.roll();
    obj.dodge = objDesc.dodge.roll();
    obj.defence = objDesc.defence.roll();
    obj.weight = objDesc.weight.roll();
    obj.speed = objDesc.speed.roll();
    obj.attribute = objDesc.attribute.roll();
    obj.value = objDesc.value.roll();
    obj.damage = objDesc.damage;
    int x = 0;
    int y = 0;
    bool ok = true;
    while(ok)
    {
      x = (rand() % (X - 2)) + 1;
			y = (rand() % (Y - 2)) + 1;
			if(aincrad->hardness[y][x] == 0)
			{
        unsigned int k;
        bool stack = true;
        for(k = 0; k < aincrad->objects.size(); ++k)
        {
          if((aincrad->objects.at(k).x == x) && (aincrad->objects.at(k).y == y))
          {
            stack = false;
            break;
          }
        }
        if(stack)
          ok = false;
      }
    }
    obj.x = x;
    obj.y = y;
    aincrad->objects.push_back(obj);
  }
}
