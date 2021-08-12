#include "Interfaces.h"

int map_t::RandomPlotType()
{
	int percent = Random(1, 1000);

	if (percent < 300)return PLOT_4446;
	else if (percent < 610)
	{
		switch (Random(1, 9))
		{
		case 1: return PLOT_3456; break;
		case 2: return PLOT_5436; break;
		case 3: return PLOT_4356; break;
		case 4: return PLOT_4536; break;
		case 5: return PLOT_5346; break;
		case 6: return PLOT_3546; break;
		case 7: return PLOT_4437; break;
		case 8: return PLOT_4347; break;
		case 9: return PLOT_3447; break;
		}
	}
	else if (percent < 617) return PLOT_3339;
	else if (percent < 620) return PLOT_11115;
	else if (percent < 820)
	{
		switch (Random(1, 4))
		{
		case 1: return PLOT_WOOD; break;
		case 2: return PLOT_CLAY; break;
		case 3: return PLOT_IRON; break;
		case 4: return PLOT_CROP; break;
		case 5: return PLOT_CROPEXTRA; break;
		}
	}
	else if (percent < 838) return PLOT_CROPEXTRA;
	else return PLOT_RAW;
}

void map_t::GenerateMap()
{
	for (int i = 0; i < 801; i++)
	{
		for (int j = 0; j < 801; j++)
		{
			auto t = RandomPlotType();

			fields[i][j].x = i - 400;
			fields[i][j].y = j - 400;
			fields[i][j].type = t;
			if (t > PLOT_RAW)fields[i][j].is_oasis = true;
		}
	}
}

void map_t::DrawAField(int x, int y, int cx, int cy, int s)
{
	if (cx < -400) cx = 801 + cx;
	if (cx > 400) cx = -801 + cx;
	
	if (cy < -400) cy = 801 + cy;
	if (cy > 400) cy = -801 + cy;
	static bool bLoaded = false;
	static file_t f = g_Files.GetFileByName("fields.png");
	static sf::Texture t;
	static sf::Sprite a;

	if (!bLoaded)
	{
		bLoaded = true;
		t.loadFromMemory(f.loc_in_mem, f.size);
		a.setTexture(t);
	}
	int ty = 0;
	switch (fields[cx+400][cy+400].type)
	{
	case PLOT_RAW:
	case PLOT_WOOD:
	case PLOT_CLAY:
	case PLOT_IRON:
	case PLOT_CROP:
	case PLOT_CROPEXTRA:
		ty = fields[cx + 400][cy + 400].type - 488;
		break;
	default:
		ty = fields[cx + 400][cy + 400].type - 1;
			break;
	}




	a.setPosition(x, y);
	a.setTextureRect(sf::IntRect(ty*70,0, 70,70));


	if (fields[cx + 400][cy + 400].village)a.setColor(sf::Color(225, 225, 225));
	else a.setColor(sf::Color(255, 255, 255));
	float fs = s;
	a.setScale(fs / 70, fs / 70);

	IWindow::AddToRenderList(a);

	if (fields[cx + 400][cy + 400].village)DrawAVillage(x, y, cx, cy, s);
}

void map_t::DrawAVillage(int x, int y, int cx, int cy, int s)
{
	if (cx < -400) cx = 801 + cx;
	if (cx > 400) cx = -801 + cx;

	if (cy < -400) cy = 801 + cy;
	if (cy > 400) cy = -801 + cy;
	static bool bLoaded = false;
	static file_t f = g_Files.GetFileByName("villages.png");
	static sf::Texture t;
	static sf::Sprite a;

	if (!bLoaded)
	{
		bLoaded = true;
		t.loadFromMemory(f.loc_in_mem, f.size);
		a.setTexture(t);
	}
	int ty = 0;
	


	int tribe = fields[cx + 400][cy + 400].village->owner->tribe;

	a.setPosition(x, y);
	a.setTextureRect(sf::IntRect(0, tribe*70, 70, 70));
	float fs = s;
	a.setScale(fs / 70, fs / 70);

	IWindow::AddToRenderList(a);
}

int map_t::DrawFieldInfo(int x, int y)
{
	if (x < -400) x = 801 + x;
	if (y < -400) y = 801 + y;
	if (x > 400) x = -801 + x;
	if (y > 400) y = -801 + y;
	auto f = fields[x + 400][y + 400];

	IWindow::RenderOverlay(900, 300, 300, 400, 255, 255, 255, 255);
	bool occupied = f.village != nullptr;

	if (occupied)
	{
		static char* types[] = { nullptr,"4-4-4-6","4-3-5-6","4-5-3-6","3-4-5-6","5-4-3-6","3-5-4-6","5-3-4-6","3-4-4-7","4-3-4-7","4-4-3-7","3-3-3-9","1-1-1-15" };
		char buf[46];
		sprintf(buf, "%s\n(%d|%d)\n%s",f.village->name, f.x, f.y, types[f.type]);
	
		
		IWindow::RenderTextB(905, 305, buf, 24, 0, 0, 0, 255);

		if (g_Mouse.IsBetween(905, 400, 390, 30, g_Mouse.Coords.x, g_Mouse.Coords.y))
			IWindow::RenderTextB(905, 400, "Center the map", 24, 0, 255, 0, 255);
		else
			IWindow::RenderTextB(905, 400, "Center the map", 24, 0, 128, 0, 255);

		if (g_Mouse.hasReleased() && g_Mouse.IsClickValid() && g_Mouse.IsBetween(905, 400, 390, 30, g_Mouse.leftclickCoords.x, g_Mouse.leftclickCoords.y))return 1;

	}
	else
	{
		static char* types[] = { nullptr,"4-4-4-6","4-3-5-6","4-5-3-6","3-4-5-6","5-4-3-6","3-5-4-6","5-3-4-6","3-4-4-7","4-3-4-7","4-4-3-7","3-3-3-9","1-1-1-15" };
		char buf[40];
		if (f.type < PLOT_RAW)
			sprintf(buf, "Unoccuppied plot\n(%d|%d)\n%s", f.x, f.y,types[f.type]);
		else if (f.type == PLOT_RAW)sprintf(buf, "Raw oasis\n(%d|%d)", f.x, f.y);
		else if (f.type == PLOT_RAW + 1)sprintf(buf, "Oasis (+25%% Wood)\n(%d|%d)", f.x, f.y);
		else if (f.type == PLOT_RAW + 2)sprintf(buf, "Oasis (+25%% Clay)\n(%d|%d)", f.x, f.y);
		else if (f.type == PLOT_RAW + 3)sprintf(buf, "Oasis (+25%% Iron)\n(%d|%d)", f.x, f.y);
		else if (f.type == PLOT_RAW + 4)sprintf(buf, "Oasis (+25%% Wheat)\n(%d|%d)", f.x, f.y);
		else if (f.type == PLOT_RAW + 5)sprintf(buf, "Oasis (+50%% Wheat)\n(%d|%d)", f.x, f.y);

		IWindow::RenderTextB(905, 305, buf, 24, 0, 0, 0, 255);

		if(g_Mouse.IsBetween(905,400,390,30,g_Mouse.Coords.x,g_Mouse.Coords.y))
			IWindow::RenderTextB(905, 400, "Center the map", 24, 0, 255, 0, 255);
		else
			IWindow::RenderTextB(905, 400, "Center the map", 24, 0, 128, 0, 255);

		if (g_Mouse.hasReleased() && g_Mouse.IsClickValid() && g_Mouse.IsBetween(905, 400, 390, 30, g_Mouse.leftclickCoords.x, g_Mouse.leftclickCoords.y))return 1;


	}


	return 0;
}

