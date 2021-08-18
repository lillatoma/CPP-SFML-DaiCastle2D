#include "DaiCastle.h"

void dc_mapeditor::Do()
{
	DrawAll();

	if (!edit_label)
	{
		Control();

		if (!show_minimap)
		{
			if (mode == 0)TextureBrush();
			if (mode == 1)LineBrush();
			if (mode == 2)ChestBrush();
			if (mode == 3)LabelBrush();
			if (mode == 4)TextureBrush();
			if (mode == 5)CopyTexture();
		}
		clock.Update();
	}
	else LabelEdit();

	if (!edit_label && g_Keyboard.keys[0x4D] & 1)show_minimap = !show_minimap;
}

void dc_mapeditor::LabelEdit()
{
	if (g_Keyboard.keys[VK_ESCAPE]) {
		edit_label = false;
		return;
	}
	for (int i = 0x41; i < 0x5B; i++)
	{
		if (g_Keyboard.keys[i] & 1)
		{
			if (!label.n[63])label.n[strlen(label.n)] = 'A' - 0x41 + i;
		}
	}
	if (g_Keyboard.keys[VK_BACK] & 1 && label.n[0])
		label.n[strlen(label.n) - 1] = '\0';
	if (g_Keyboard.keys[VK_SPACE] & 1 && !label.n[63])
		label.n[strlen(label.n)] = '\n';
}

void dc_mapeditor::LabelBrush()
{
	if (!g_Mouse.hasReleased())return;
	if (!g_Mouse.IsBetween(0, 32, 1000, 720, g_Mouse.Coords.x, g_Mouse.Coords.y))return;
	if (!label.n[0])return;
	for (auto &lab : map.labels)
	{
		auto chs = max(strlen(lab.n), strlen(label.n));
		bool match = true;
		for (int i = 0; i < chs; i++)
		{
			if (label.n[i] != lab.n[i])
			{
				match = false;
				break;
			}
		}



		if (match)
		{
			map.labels.erase(std::remove(map.labels.begin(), map.labels.end(), lab), map.labels.end());
			return;
		}
	}

	auto v = map.cursor_to_world(vecCamera.x, vecCamera.y, camera_width);
	label.vPosition = v;
	map.labels.push_back(label);

}

void dc_mapeditor::__debug_draw_label_circles()
{
	static sf::CircleShape circle;
	//IWindow::RenderOverlay(g_Resolution.x*0.245, g_Resolution.y*0.5 - g_Resolution.x*0.25, g_Resolution.x*0.50, g_Resolution.x*0.50, 255, 255, 255, 255);
	for (auto lab : map.labels)
	{
		float radius = lab.size*g_Resolution.x*0.50 / 1000;
		float _x = lab.vPosition.x*g_Resolution.x*0.5 / 1000 + g_Resolution.x*0.25;
		float _y = lab.vPosition.y*g_Resolution.x*0.5 / 1000 + g_Resolution.y*0.5 - g_Resolution.x*0.25;
		circle.setPosition(_x - radius, _y - radius);
		circle.setRadius(radius);
		circle.setFillColor(sf::Color(255, 230, 64, 128));
		g_Window->draw(circle);
	}
}

void dc_mapeditor::DrawAll()
{
	map.draw(vecCamera.x, vecCamera.y, camera_width);
	DrawForSelectedMode();
	DrawUI();
	if (show_minimap) {
		map.show_minimap(vecCamera.x, vecCamera.y, camera_width, false,sf::Vector2f(500,500),2000);
		__debug_draw_label_circles();
	}
}

void dc_mapeditor::Start()
{
	map.define(1000,1000);
	printf("\nMap generated...");
	Load();

	for (int i = 0; i < map.chests.size(); i++)
	{
		auto Chest = map.chests[i];
		//printf("\n#%d | (%.1f,%.1f)", i, Chest.vPosition.x,Chest.vPosition.y);
	}
}

void dc_mapeditor::Control()
{
	auto _W = g_Keyboard.keys[0x57], _S = g_Keyboard.keys[0x53], _A = g_Keyboard.keys[0x41], _D = g_Keyboard.keys[0x44];

	bool move = true;
	float adif = 0.f;
	if (g_Keyboard.keys[VK_CONTROL] && (_S & 1)) { Save(); move = false; }
	else if (_W && _A)
		adif = -45.f;
	else if (_W && _D)
		adif = 45.f;
	else if (_S && _A)
		adif = -135.f;
	else if (_S && _D)
		adif = 135.f;
	else if (_W)
		adif = 0.f;
	else if (_A)
		adif = -90.f;
	else if (_D)
		adif = 90.f;
	else if (_S)
		adif = 180.f;
	else move = false;

	auto diff = clock.deltaTime();
	float fdif = float(diff) / 1000;
	if (move)
	{
		vecCamera += (sf::Vector2f(cos((adif - 90)*PI / 180), sin((adif - 90)*PI / 180))*fdif*(camera_width*camera_width/10)*(1.0f-(bool)(g_Keyboard.keys[VK_SHIFT])*0.66f));
	}

	camera_width *= pow(1.1, -g_Mouse.scroll);
	if (camera_width < 10)camera_width = 10;
	else if (camera_width > 50)camera_width = 50;


	for (int i = 0; i < 6; i++)
	{
		if (g_Keyboard.keys[0x31 + i])mode = i;
	}

}

void dc_mapeditor::DrawUI()
{


	_Window::RenderOverlay(0, 0, 1280, 32, 192, 192, 192, 255);
	_Window::RenderOverlay(1000, 32, 280, 688, 192, 192, 192, 255);

	static sf::Sprite spr;
	
	spr.setTexture(*g_Textures.get(texture_selected));

	char buffer[256];
	static char* ModeNames[] = { "Texture mode","Wall mode","Chest mode","Label mode","Texture mode + Paint","Copy texture" };
	sprintf(buffer, "%.2f %.2f  - %.1f - %d chests - %d time - %s", vecCamera.x, vecCamera.y, camera_width,map.chests.size(),map.day_time % 7200,ModeNames[mode]);
	auto vekt = map.cursor_to_world(vecCamera.x, vecCamera.y, camera_width);
	for (auto l : map.labels)
	{
		
		if (GetDistance(l.vPosition, vekt) < l.size)sprintf(buffer, "%s \n%s", buffer, l.n);
	}
	
	_Window::RenderTextB(0, 0, buffer, 24, 255, 255, 0, 255);


	spr.setPosition(1076, 100);
	g_Window->draw(spr);
	_Window::RenderOverlay(1050, 100, 20, 128, 220, 220, 220, 255);
	_Window::RenderOverlay(1210, 100, 20, 128, 220, 220, 220, 255);
	_Window::RenderOverlay(1050, 300, 20, 40, 220, 220, 220, 255);
	_Window::RenderOverlay(1210, 300, 20, 40, 220, 220, 220, 255);
	if (g_Mouse.hasReleased())
	{
		if(g_Mouse.IsBetween(1050, 100, 20, 128, g_Mouse.Coords.x, g_Mouse.Coords.y))MoveTexture(-1);
		else if (g_Mouse.IsBetween(1210, 100, 20, 128, g_Mouse.Coords.x, g_Mouse.Coords.y))MoveTexture(1);
		else if (g_Mouse.IsBetween(1050, 300, 20, 40, g_Mouse.Coords.x, g_Mouse.Coords.y))MoveHealth(-25);
		else if (g_Mouse.IsBetween(1210, 300, 20, 40, g_Mouse.Coords.x, g_Mouse.Coords.y))MoveHealth(25);
		else if (g_Mouse.IsBetween(1050, 650, 180, 35, g_Mouse.Coords.x, g_Mouse.Coords.y))Save();
		else if (g_Mouse.IsBetween(1050, 600, 180, 35, g_Mouse.Coords.x, g_Mouse.Coords.y))Load();
		else if (g_Mouse.IsBetween(1050, 550, 180, 35, g_Mouse.Coords.x, g_Mouse.Coords.y))map.define(1000, 1000);
	}
	if (!edit_label)
	{
		if (g_Keyboard.keys[0x45] & 1)MoveTexture(1);
		else if (g_Keyboard.keys[0x51] & 1)MoveTexture(-1);
	}

	if (g_Mouse.left_click)
	{
		if (g_Mouse.IsBetween(1050, 50, 180, 35, g_Mouse.Coords.x, g_Mouse.Coords.y))map.day_time += 25;
	}

	_Window::RenderOverlay(1050, 50, 180, 35, 225, 225, 225, 255);
	_Window::RenderTextBMiddle(1050, 50, 180, 35, "Forward", 24, 0, 0, 0, 255);
	

	_Window::RenderOverlay(1050, 550, 180, 35, 225, 225, 225, 255);
	_Window::RenderTextBMiddle(1050, 550, 180, 35, "Reset", 24, 0, 0, 0, 255);

	_Window::RenderOverlay(1050, 600, 180, 35, 225, 225, 225, 255);
	_Window::RenderTextBMiddle(1050, 600, 180, 35, "Load", 24, 0, 0, 0, 255);

	_Window::RenderOverlay(1050, 650, 180, 35, 225, 225, 225, 255);
	_Window::RenderTextBMiddle(1050, 650, 180, 35, "Save", 24, 0, 0, 0, 255);
	
	_Window::RenderOverlay(1050, 250, 180, 40, 255, 255, 255, 255);
	int textsize = 24;
	for (textsize = 24; textsize > 1; textsize--)
	{
		if (_Window::GetTextSize(g_Textures.getname(texture_selected), textsize).x < 180)break;
	}
	_Window::RenderTextBMiddle(1050, 250, 180, 40, g_Textures.getname(texture_selected), textsize, 0, 0, 0, 255);
	{
		int _r = 128 + edit_label*(-64);
		int _g = 128 + edit_label*(100);
		int _b = 128 + edit_label*(-64);
		_Window::RenderOverlay(1050, 350, 180, 100, _r, _g, _b, 255);
		if(label.n[0])
			_Window::RenderTextBMiddle(1050, 350, 180, 100, label.n, 24, 0, 0, 0, 255);
		else
			_Window::RenderTextBMiddle(1050, 350, 180, 100, "No label", 24, 0, 0, 0, 255);
		_Window::RenderOverlay(1050, 460, 180, 40, 255,255,255, 255);
		char hbuf[16];
		sprintf(hbuf, "%.1f", label.size);
		_Window::RenderTextBMiddle(1050, 460, 180, 40, hbuf, 25, 0, 0, 0, 255);
		if (g_Mouse.IsBetween(1050, 460, 90, 40, g_Mouse.Coords.x, g_Mouse.Coords.y) && g_Mouse.left_click)
		{
			label.size -= 0.1f;
			if (label.size < 10.f)label.size = 10.f;
		}
		else if (g_Mouse.IsBetween(1140, 460, 90, 40, g_Mouse.Coords.x, g_Mouse.Coords.y) && g_Mouse.left_click)
			label.size += 0.1f;
		if (g_Mouse.hasReleased() && g_Mouse.IsClickValid())
		{
			if (g_Mouse.IsBetween(1050, 350, 180, 100, g_Mouse.Coords.x, g_Mouse.Coords.y))
				edit_label = true;
			else edit_label = false;
		}
	}
	_Window::RenderOverlay(1076, 300, 128, 40, 255, 255, 255, 255);
	char wall_hp_buf[16];
	sprintf(wall_hp_buf, "%d HP", wall_health);
	_Window::RenderTextBMiddle(1076, 300, 128, 40, wall_hp_buf, 24, 0, 0, 0, 255);

}

void dc_mapeditor::DrawForSelectedMode()
{
	if (mode == 0 || mode == 4)
	{
		auto floatvec = map.cursor_to_world(vecCamera.x, vecCamera.y, camera_width);
		sf::Vector2f nvec;
		nvec.x = (int)(floatvec.x);
		nvec.y = (int)(floatvec.y);
		auto width = camera_width;
		sf::Vector2f blocksize((float)(g_Resolution.x) / width, (float)(g_Resolution.x) / width);

		auto screenvec = map.world_to_screen(vecCamera.x, vecCamera.y, camera_width, nvec.x, nvec.y);

		_Window::RenderOverlay(screenvec.x, screenvec.y, blocksize.x, blocksize.y, 255, 255, 255, 128);
	}
	else if (mode == 1)
	{
		auto floatvec = map.cursor_to_world(vecCamera.x, vecCamera.y, camera_width);
		sf::Vector2f nvec;
		nvec.x = (int)(floatvec.x);
		nvec.y = (int)(floatvec.y);
		auto width = camera_width;
		sf::Vector2f blocksize((float)(g_Resolution.x) / width, (float)(g_Resolution.x) / width);



		bool left = true;

		auto difference = floatvec - nvec;
		
		if (difference.y < difference.x)left = false;

		if (wall_type != -1)left = true - wall_type;

		auto screenvec = map.world_to_screen(vecCamera.x, vecCamera.y, camera_width, nvec.x, nvec.y);

		if(left)_Window::RenderOverlay(screenvec.x, screenvec.y, 2, blocksize.y, 255, 255, 255, 128);
		else _Window::RenderOverlay(screenvec.x, screenvec.y, blocksize.x, 2, 255, 255, 255, 128);


		//printf("\nFloatVec: %.1f %.1f | ScrVec: %.1f %.1f -> Diff: %.1f %.1f", floatvec.x, floatvec.y, screenvec.x, screenvec.y, difference.x, difference.y);
	}
	else if (mode == 2)
	{

		bool found_chest = false;
		auto floatvec = map.cursor_to_world(vecCamera.x, vecCamera.y, camera_width);
		for (auto _ch : map.chests)
		{
			if (GetDistance(floatvec, _ch.vPosition) < 0.7)
			{
				found_chest = true;
				break;
			}
		}

		static sf::Sprite chestsprite;
		chestsprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
		chestsprite.setTexture(*g_Textures.get(4));
		sf::Vector2f blocksize((float)(g_Resolution.x) / camera_width, (float)(g_Resolution.x) / camera_width);
		float scale = (float)(blocksize.x) / 128;
		chestsprite.setScale(scale, scale);
		chestsprite.setPosition(g_Mouse.Coords.x, g_Mouse.Coords.y);

		if (found_chest)chestsprite.setColor(sf::Color(255, 64, 64, 255));
		else chestsprite.setColor(sf::Color(255, 255,255, 255));

		g_Window->draw(chestsprite);
	}








}

void dc_mapeditor::MoveHealth(int n)
{
	wall_health += n;
	
	if (wall_health < 0)wall_health = 0;
}

void dc_mapeditor::MoveTexture(int m)
{
	static bool run = false;
	static std::vector<int> nontextures;
	if (!run)
	{
		nontextures.push_back(3);
		nontextures.push_back(4);
		nontextures.push_back(5);
		nontextures.push_back(50);
		nontextures.push_back(51);
		nontextures.push_back(52);
		nontextures.push_back(53);
		nontextures.push_back(54);
		nontextures.push_back(55);
		nontextures.push_back(56);
		nontextures.push_back(57);
		nontextures.push_back(58);
		nontextures.push_back(67);
		nontextures.push_back(68);

		run = true;
	}
	while (true)
	{
		texture_selected += m;
		if (texture_selected > (int)(g_Textures.t.size()) - 1)texture_selected = 0;
		if (texture_selected < 0)texture_selected = g_Textures.t.size()-1;
		
		//texture_selected %= g_Textures.t.size();
		bool good = true;
		for (auto n : nontextures)
		{
			if (texture_selected == n) { good = false; break; }
		}
		if (good)
		{
			break;
		}
	}


}

void dc_mapeditor::CopyTexture()
{
	if (!g_Mouse.left_click)return;
	if (!g_Mouse.IsBetween(0, 32, 1000, 720, g_Mouse.Coords.x, g_Mouse.Coords.y))return;


	auto vector = map.cursor_to_world(vecCamera.x, vecCamera.y, camera_width);

	auto intvector = sf::Vector2i(int(vector.x), int(vector.y));

	if (intvector.x >= 0 && intvector.x < 1000 && intvector.y >= 0 && intvector.y < 1000)
	{
		texture_selected = map.lines[intvector.y].blocks[intvector.x].iTexture;
	}
}

void dc_mapeditor::TextureBrush()
{

	static dc_clock last_click_clock;

	if (mode == 4 && g_Mouse.hasReleased())
	{
		if (last_click_clock.deltaTime() < 250)
		{
			auto vec = map.cursor_to_world(vecCamera.x, vecCamera.y, camera_width);
			PaintBrushPart(vec.x, vec.y, true);
		}
		last_click_clock.Update();
	}

	if (!g_Mouse.left_click)return;
	if (!g_Mouse.IsBetween(0, 32, 1000, 720, g_Mouse.Coords.x, g_Mouse.Coords.y))return;




	auto vector = map.cursor_to_world(vecCamera.x, vecCamera.y, camera_width);

	auto intvector = sf::Vector2i(int(vector.x), int(vector.y));

	if (intvector.x >= 0 && intvector.x < 1000 && intvector.y >= 0 && intvector.y < 1000)
	{
		map.lines[intvector.y].blocks[intvector.x].iTexture = texture_selected;
	}

	static sf::Vector2f old_coords = vector;
	static dc_clock clokito;

	if (old_coords != vector && clokito.deltaTime() < 50)
	{
		auto dif = GetDistance(old_coords, vector);
		for (float i = 0; i < dif; i += 0.5f)
		{
			auto viktor = (old_coords*i + (vector*(dif - i))) / dif;
			intvector = sf::Vector2i(int(viktor.x), int(viktor.y));

			if (intvector.x >= 0 && intvector.x < 1000 && intvector.y >= 0 && intvector.y < 1000)
			{
				map.lines[intvector.y].blocks[intvector.x].iTexture = texture_selected;
			}
		}
	}

	old_coords = vector;
	clokito.Update();
}

void dc_mapeditor::LineBrush()
{
	static int adding = -1;
	if (!g_Mouse.left_click)
	{
		adding = -1;
		wall_type = -1;
		return;
	}
	if (!g_Mouse.IsBetween(0, 32, 1000, 720, g_Mouse.Coords.x, g_Mouse.Coords.y))return;

	auto vector = map.cursor_to_world(vecCamera.x, vecCamera.y, camera_width);
	auto intvector = sf::Vector2i(int(vector.x), int(vector.y));


	auto floatvec = map.cursor_to_world(vecCamera.x, vecCamera.y, camera_width);
	sf::Vector2f nvec;
	nvec.x = (int)(floatvec.x);
	nvec.y = (int)(floatvec.y);
	auto width = camera_width;
	sf::Vector2f blocksize((float)(g_Resolution.x) / width, (float)(g_Resolution.x) / width);



	bool left = true;

	auto difference = floatvec - nvec;

	if (difference.y < difference.x)left = false;
	if (intvector.x >= 0 && intvector.x < 1000 && intvector.y >= 0 && intvector.x < 1000)
	{
		if (adding == -1)
		{
			if (map.lines[intvector.y].blocks[intvector.x].walls[true - left].iHealth == 0)adding = 1;
			else adding = 0;
			wall_type = true - left;
		}

		if (adding == 1)map.lines[intvector.y].blocks[intvector.x].walls[wall_type].iHealth = wall_health;
		else if (adding == 0)map.lines[intvector.y].blocks[intvector.x].walls[wall_type].iHealth = 0;

	}
}

void dc_mapeditor::ChestBrush()
{
	if (!g_Mouse.IsBetween(0, 32, 1000, 720, g_Mouse.Coords.x, g_Mouse.Coords.y))return;
	auto floatvec = map.cursor_to_world(vecCamera.x, vecCamera.y, camera_width);
	if (g_Mouse.hasReleased())
	{
		bool found_chest = false;

		for (auto _ch : map.chests)
		{
			if (GetDistance(floatvec, _ch.vPosition) < 0.7)
			{
				found_chest = true;
				map.chests.erase(std::remove(map.chests.begin(), map.chests.end(), _ch), map.chests.end());
				break;
			}
		}

		if (!found_chest)
		{
			dc_chest ch;
			ch.bOpen = false;
			ch.vPosition = floatvec;

			map.chests.push_back(ch);
		}
	}
}

void dc_mapeditor::Save()
{
	printf("\nStarting...");
	char* map_buffer = new char[1000000 * sizeof(dc_block)];
	printf("\nBufferCreated...");
	for (int y = 0; y < 1000; y++)
	{
		for (int x = 0; x < 1000; x++)
		{
			for (int i = 0; i < sizeof(dc_block); i++)
			{
				map_buffer[(y * 1000 + x) * sizeof(dc_block) + i] = *(((char*)(&map.lines[y].blocks[x]))+i);
			}
		}
		//printf("\n%.1f", (float)y / 10);
	}
	printf("\nBufferCopied");
	file_t F;
	F.size = 1000000 * sizeof(dc_block);
	F.loc_in_mem = map_buffer;
	F.Dump("BigSize.map",true);
	F.Dump("BizMent.map", true);
	printf("\nMap Saved");
	delete[] map_buffer;
	if (map.chests.size() > 0)
	{
		char* chest_buffer = new char[map.chests.size() * sizeof(dc_chest)];

		for (int c = 0; c < map.chests.size(); c++)
		{
			for (int i = 0; i < sizeof(dc_chest); i++)
			{
				chest_buffer[c * sizeof(dc_chest) + i] = *(((char*)(&map.chests[c])) + i);

			}
		}
		file_t F;
		F.size = map.chests.size() * sizeof(dc_chest);
		F.loc_in_mem = chest_buffer;
		F.Dump("BigSize.chest", true);
		delete[] chest_buffer;
	}
	if (map.labels.size() > 0)
	{
		char* label_buffer = new char[map.labels.size() * sizeof(dc_label)];
		for (int c = 0; c < map.labels.size(); c++)
		{
			for (int i = 0; i < sizeof(dc_label); i++)
			{
				label_buffer[c * sizeof(dc_label) + i] = *(((char*)(&map.labels[c])) + i);

			}
		}
		F.size = map.labels.size() * sizeof(dc_label);
		F.loc_in_mem = label_buffer;
		F.Dump("BigSize.label", true);
		delete[] label_buffer;
	}
}

void dc_mapeditor::Load()
{
	bool should_presave = false;
	file_t fMap;
	fMap.ReadInMemory("BigSize.map");

	if (fMap.size < 20000000)
	{
		delete[]fMap.loc_in_mem;
		fMap.ReadInMemory("BizMent.map");
		should_presave = true;
	}
	if (fMap.size <= 10000)
	{
		printf("\nNo map found, default loaded");
		return;
	}
	printf("\n%d\n", fMap.size);
	for (int y = 0; y < 1000; y++)
	{
		for (int x = 0; x < 1000; x++)
		{
			for (int i = 0; i < sizeof(dc_block); i++)
			{
				*(((char*)(&map.lines[y].blocks[x])) + i) = *(fMap.loc_in_mem + (y*1000+x)*sizeof(dc_block)+i);
			}
		}
		//printf("\n%.1f", (float)y / 10);
	}
	printf("\nMap successfully loaded");
	delete[]fMap.loc_in_mem;
	printf("\nMap file deleted from memory");
	

	file_t fChest;
	fChest.ReadInMemory("BigSize.chest");
	//for (int i = 0; i < fChest.size; i++)printf("%c", fChest.loc_in_mem[i]);

	printf("\nChest file loaded in");
	map.chests.clear();
	printf("\n%d chests should be present\n", fChest.size / sizeof(dc_chest));
	dc_chest ch;
	for (int c = 0; c < fChest.size / sizeof(dc_chest); c++)
	{
		dc_chest* pch = (dc_chest*)(fChest.loc_in_mem + c * sizeof(dc_chest));
		map.chests.push_back(*pch);

	}
	printf("\nChests successfully loaded");
	//delete[]fChest.loc_in_mem;
	printf("\nChests file successfully deleted from memory");
	printf("\n%d chests are present.", map.chests.size());
	delete[]fChest.loc_in_mem;

	file_t fLabel;
	fLabel.ReadInMemory("BigSize.label");
	map.labels.clear();
	printf("\n%d labels should be present\n", fLabel.size / sizeof(dc_label));
	for (int c = 0; c < fLabel.size / sizeof(dc_label); c++)
	{
		dc_label* pch = (dc_label*)(fLabel.loc_in_mem + c * sizeof(dc_label));
		map.labels.push_back(*pch);

	}
	delete[]fLabel.loc_in_mem;

	printf("\nLoaded Data:\n");
	for (auto l : map.labels)
	{
		int count = 0;
		for (auto c : map.chests)
		{
			if (GetDistance(l.vPosition, c.vPosition) < l.size)count++;
		}
		printf("\n%s : %d chests", l.n, count);
	}

	for (int _X = 0; _X < map.size.x; _X++)
	{
		for (int _Y = 0; _Y < map.size.y; _Y++)
		{
			if (map.lines[_Y].blocks[_X].iTexture == 30 || map.lines[_Y].blocks[_X].iTexture == 8 || map.lines[_Y].blocks[_X].iTexture == 64)
			{
				if (map.lines[_Y].blocks[_X].walls[0].iHealth == 0)map.lines[_Y].blocks[_X].walls[0].iHealth = 100;
				if (map.lines[_Y].blocks[_X].walls[1].iHealth == 0)map.lines[_Y].blocks[_X].walls[1].iHealth = 100;
				if (map.is_on_map(sf::Vector2i(_X + 1, _Y)) && map.lines[_Y].blocks[_X + 1].walls[0].iHealth == 0)map.lines[_Y].blocks[_X + 1].walls[0].iHealth = 100;
				if (map.is_on_map(sf::Vector2i(_X, _Y+1)) && map.lines[_Y+1].blocks[_X].walls[1].iHealth == 0)map.lines[_Y+1].blocks[_X].walls[1].iHealth = 100;

			}
		}
	}


	if (should_presave)Save();


}

void dc_mapeditor::DrawSaveScreen(char* name, float percent)
{
	static char buf[64]; sprintf(buf, "DaiCastle - Saving %s", name);
	g_Window->setTitle(buf);

	g_Mouse.Update(50, 50, 0);

	_Window::RenderOverlay(320, 315, 640, 90, 64, 64, 64, 255);
	_Window::RenderTextB(320, 315, name, 24);

	_Window::RenderOverlay(330, 365, 620 * percent, 30, 255, 64, 64, 255);
	g_Window->display();
}

void dc_mapeditor::PaintBrushPart(int x, int y,bool initiator)
{
	if (x < 0 || y < 0 || x > 999 || y > 999)return;
	if (!initiator && map.lines[y].blocks[x].iTexture == texture_selected)return;


	map.lines[y].blocks[x].iTexture = texture_selected;

	
	PaintBrushPart(x - 1, y, false);
	PaintBrushPart(x + 1, y, false);
	PaintBrushPart(x, y-1, false);
	PaintBrushPart(x, y+1, false);
}