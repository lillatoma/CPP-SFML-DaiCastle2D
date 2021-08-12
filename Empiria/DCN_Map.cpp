#include "DCN_Map.h"

#define DAY_MAX_TIME 7200

void dcn_map::define(int sx, int sy)
{
	for (int i = 0; i < size.y; i++)
	{
		lines[i].blocks.clear();
	}
	lines.clear();
	chests.clear();
	items.clear();

	size.x = sx; size.y = sy;




	for (int i = 0; i < sy; i++)
	{
		dc_blockline line;
		for (int j = 0; j < sx; j++)
		{
			dc_block block;
			line.blocks.push_back(block);
		}
		lines.push_back(line);
	}

}