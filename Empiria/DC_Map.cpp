#include "DaiCastle.h"

dc_map g_Map;

#define DAY_MAX_TIME 7200 //7200

float dc_map::get_shadow_angle()
{
	int modul = day_time % DAY_MAX_TIME;

	return 360.f * modul / DAY_MAX_TIME;

}

void dc_map::simulate_day()
{
	static dc_clock daeclock;


	if (daeclock.GetDiff() > 100)
	{
		day_time+= daeclock.GetDiff()/100;
		daeclock.Update();
	}
}

sf::Color dc_map::get_modulation_color()
{
	static int time_stamps[] = { 0,1200,2400,3000,3600,4800,6000,6600,7200 };
	static sf::Color cols[] = { sf::Color(238,238,222,255),sf::Color(255,255,255,255),sf::Color(255,255,255,255),sf::Color(250,221,120,255),sf::Color(114,114,160,255),sf::Color(100,100,175,255),sf::Color(114,114,160,255),sf::Color(215,150,150,255),sf::Color(238,238,222,255) };
	int modul = day_time % DAY_MAX_TIME;
	int current_timestamp = 0;
	for (int i = 0; i < 8; i++)if (modul >= time_stamps[i]) { current_timestamp = i; }
	int timestamp_length = time_stamps[current_timestamp + 1] - time_stamps[current_timestamp];
	int from_start = modul - time_stamps[current_timestamp];
	int from_end = time_stamps[current_timestamp + 1] - modul;
	
	int r = (from_end*cols[current_timestamp].r + from_start*cols[current_timestamp + 1].r) / timestamp_length;
	int g = (from_end*cols[current_timestamp].g + from_start*cols[current_timestamp + 1].g) / timestamp_length;
	int b = (from_end*cols[current_timestamp].b + from_start*cols[current_timestamp + 1].b) / timestamp_length;
	int a = 255;

	//ConLog("\nTime: %d | Timestamp: %d | Color: %d %d %d %d", modul, current_timestamp, r, g, b, a);
	return sf::Color(r, g, b, a);
}

float dc_map::get_shadow_length()
{
	static int time_stamps[] = { 0,1200,2400,3000,3600,4800,6000,6600,7200 };
	static float length[] = { 1.f,0.4f,0.45f,0.7f,1.f,1.5f,2.f,1.5f,1.f };
	int modul = day_time % DAY_MAX_TIME;
	int current_timestamp = 0;
	for (int i = 0; i < 8; i++)if (modul >= time_stamps[i]) { current_timestamp = i; }
	int timestamp_length = time_stamps[current_timestamp + 1] - time_stamps[current_timestamp];
	int from_start = modul - time_stamps[current_timestamp];
	int from_end = time_stamps[current_timestamp + 1] - modul;

	return (from_end*length[current_timestamp] + from_start*length[current_timestamp + 1]) / timestamp_length;
}

void dc_map::define(int sx, int sy)
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



sf::Vector2f dc_map::screen_to_world(float mx, float my, float width,float x, float y)
{
	sf::Vector2f blocksize((float)(g_Resolution.x) / width, (float)(g_Resolution.x) / width);


	float _x = (float)(x - g_Resolution.x / 2) / blocksize.x + mx;
	float _y = (float)(y - g_Resolution.y / 2) / blocksize.x + my;
	return sf::Vector2f(_x, _y);
}
sf::Vector2f dc_map::cursor_to_world(float mx, float my, float width)
{
	sf::Vector2f blocksize((float)(g_Resolution.x) / width, (float)(g_Resolution.x) / width);
	int x = g_Mouse.Coords.x;
	int y = g_Mouse.Coords.y;

	float _x = (float)(x-g_Resolution.x/2) / blocksize.x + mx;
	float _y = (float)(y-g_Resolution.y/2) / blocksize.x + my;
	return sf::Vector2f(_x, _y);
}

sf::Vector2f dc_map::world_to_screen(float mx, float my, float width, float x ,float y)
{
	sf::Vector2f blocksize((float)(g_Resolution.x) / width, (float)(g_Resolution.x) / width);

	return sf::Vector2f((x - mx)*blocksize.x + g_Resolution.x / 2, (y - my)*blocksize.x + g_Resolution.y / 2);
}

sf::Texture shadowtext;

void dc_map::beginshadows(float mx, float my, float width)
{
	sf::Vector2f blocksize((float)(g_Resolution.x) / width, (float)(g_Resolution.x) / width);
	float scale = (float)(blocksize.x) / 128;


	static sf::Vector2i lastRes(0, 0);

	if (lastRes != g_Resolution)
	{
		shadowtext.create(g_Resolution.x, g_Resolution.y);
		lastRes = g_Resolution;
	}






	float height = width*g_Resolution.y / g_Resolution.x;



	float dx = mx - (int)mx;
	float dy = my - (int)my;

	int _mx = (int)mx;
	int _my = (int)my;

	std::vector<sf::Vertex> shadowverts;

	float shadow_angle = get_shadow_angle();
	float shadow_length = get_shadow_length();
	//sf::Color day_color = get_modulation_color();


	for (int x = -width / 2 - 2; x < width / 2 + 3; x++)
	{
		for (int y = -height / 2 - 2; y < height / 2 + 3; y++)
		{
			float bx = _mx + x;
			float by = _my + y;


			if (bx < 0 || bx >= size.x || by < 0 || by >= size.y)continue;



			sf::Vector2f p(g_Resolution.x / 2 + x*blocksize.x - dx*blocksize.x, g_Resolution.y / 2 + y*blocksize.y - dy*blocksize.y);

#define shadow_color sf::Color(0, 0,0, 255)
			if (lines[by].blocks[bx].walls[0].iHealth > 0)
			{
				shadowverts.push_back(sf::Vertex(sf::Vector2f(p.x, p.y), shadow_color, sf::Vector2f()));
				shadowverts.push_back(sf::Vertex(sf::Vector2f(p.x, p.y + blocksize.y), shadow_color, sf::Vector2f()));
				shadowverts.push_back(sf::Vertex(sf::Vector2f(p.x, p.y + blocksize.y) + sf::Vector2f(cos(shadow_angle*PI / 180), sin(shadow_angle*PI / 180))*blocksize.x*shadow_length, shadow_color, sf::Vector2f()));
				shadowverts.push_back(sf::Vertex(sf::Vector2f(p.x, p.y) + sf::Vector2f(cos(shadow_angle*PI / 180), sin(shadow_angle*PI / 180))*blocksize.x*shadow_length, shadow_color, sf::Vector2f()));
			}
			if (lines[by].blocks[bx].walls[1].iHealth > 0)
			{


				shadowverts.push_back(sf::Vertex(sf::Vector2f(p.x, p.y), shadow_color, sf::Vector2f()));
				shadowverts.push_back(sf::Vertex(sf::Vector2f(p.x + blocksize.x, p.y), shadow_color, sf::Vector2f()));
				shadowverts.push_back(sf::Vertex(sf::Vector2f(p.x + blocksize.x, p.y) + sf::Vector2f(cos(shadow_angle*PI / 180), sin(shadow_angle*PI / 180))*blocksize.x*shadow_length, shadow_color, sf::Vector2f()));
				shadowverts.push_back(sf::Vertex(sf::Vector2f(p.x, p.y) + sf::Vector2f(cos(shadow_angle*PI / 180), sin(shadow_angle*PI / 180))*blocksize.x*shadow_length, shadow_color, sf::Vector2f()));
			}

		}
	}
	g_Window->draw(&shadowverts[0], shadowverts.size(), sf::PrimitiveType::Quads);
	shadowtext.update(*g_Window);

	return;
}


void dc_map::beginshadows(sf::RenderTexture* T,float mx, float my, float width)
{
	static sf::RenderTexture RT;
	static sf::Vector2i lastRes(0, 0);

	if (lastRes != g_Resolution)
	{
		shadowtext.create(g_Resolution.x, g_Resolution.y);
		lastRes = g_Resolution;
	}

	sf::Vector2f blocksize((float)(g_Resolution.x) / width, (float)(g_Resolution.x) / width);
	float scale = (float)(blocksize.x) / 128;

	float height = width*g_Resolution.y / g_Resolution.x;

	float dx = mx - (int)mx;
	float dy = my - (int)my;

	int _mx = (int)mx;
	int _my = (int)my;

	std::vector<sf::Vertex> shadowverts;

	float shadow_angle = get_shadow_angle();
	float shadow_length = get_shadow_length();
	//sf::Color day_color = get_modulation_color();


	for (int x = -width / 2 - 2; x < width / 2 + 3; x++)
	{
		for (int y = -height / 2 - 2; y < height / 2 + 3; y++)
		{
			float bx = _mx + x;
			float by = _my + y;


			if (bx < 0 || bx >= size.x || by < 0 || by >= size.y)continue;



			sf::Vector2f p(g_Resolution.x / 2 + x*blocksize.x - dx*blocksize.x, g_Resolution.y / 2 + y*blocksize.y - dy*blocksize.y);

#define shadow_color sf::Color(0, 0,0, 255)
			if (lines[by].blocks[bx].walls[0].iHealth > 0)
			{
				shadowverts.push_back(sf::Vertex(sf::Vector2f(p.x, p.y), shadow_color, sf::Vector2f()));
				shadowverts.push_back(sf::Vertex(sf::Vector2f(p.x, p.y + blocksize.y), shadow_color, sf::Vector2f()));
				shadowverts.push_back(sf::Vertex(sf::Vector2f(p.x, p.y + blocksize.y) + sf::Vector2f(cos(shadow_angle*PI / 180), sin(shadow_angle*PI / 180))*blocksize.x*shadow_length, shadow_color, sf::Vector2f()));
				shadowverts.push_back(sf::Vertex(sf::Vector2f(p.x, p.y) + sf::Vector2f(cos(shadow_angle*PI / 180), sin(shadow_angle*PI / 180))*blocksize.x*shadow_length, shadow_color, sf::Vector2f()));
			}
			if (lines[by].blocks[bx].walls[1].iHealth > 0)
			{


				shadowverts.push_back(sf::Vertex(sf::Vector2f(p.x, p.y), shadow_color, sf::Vector2f()));
				shadowverts.push_back(sf::Vertex(sf::Vector2f(p.x + blocksize.x, p.y), shadow_color, sf::Vector2f()));
				shadowverts.push_back(sf::Vertex(sf::Vector2f(p.x + blocksize.x, p.y) + sf::Vector2f(cos(shadow_angle*PI / 180), sin(shadow_angle*PI / 180))*blocksize.x*shadow_length, shadow_color, sf::Vector2f()));
				shadowverts.push_back(sf::Vertex(sf::Vector2f(p.x, p.y) + sf::Vector2f(cos(shadow_angle*PI / 180), sin(shadow_angle*PI / 180))*blocksize.x*shadow_length, shadow_color, sf::Vector2f()));
			}

		}
	}
	T->draw(&shadowverts[0], shadowverts.size(), sf::PrimitiveType::Quads);

	T->display();

	shadowtext = T->getTexture();

	return;
}

void dc_map::draw(float mx, float my, float width)
{
	beginshadows(mx, my, width);
	sf::Vector2f blocksize((float)(g_Resolution.x) / width, (float)(g_Resolution.x) / width);
	float scale = (float)(blocksize.x) / 128;
	
	
	
	


	

	static sf::Sprite spr;
	float height = width*g_Resolution.y / g_Resolution.x;

	spr.setScale(scale, scale);

	float dx = mx - (int)mx;
	float dy = my - (int)my;

	int _mx = (int)mx;
	int _my = (int)my;

	std::vector<sf::Vertex> verts;

	float shadow_angle = get_shadow_angle();
	float shadow_length = get_shadow_length();
	sf::Color day_color = get_modulation_color();

	int r = (32 * day_color.r) / 255;
	int g = (80 * day_color.g) / 255;
	int b = (225 * day_color.b) / 255;


	//Absolute bg color
	IWindow::RenderOverlay(0, 0, g_Resolution.x, g_Resolution.y, r,g,b, 255);

	for (int x = -width/2-1; x < width/2+ 1; x++)
	{
		for (int y = -height/2-1; y < height/2 + 1; y++)
		{
			float bx = _mx + x;
			float by = _my+y;


			if (bx < 0 || bx >= size.x || by < 0 || by >= size.y)continue;
			spr.setTexture(*g_Textures.get(lines[by].blocks[bx].iTexture));
			

			sf::Vector2f p(g_Resolution.x/2+x*blocksize.x - dx*blocksize.x,g_Resolution.y/2+y*blocksize.y-dy*blocksize.y);
			spr.setPosition(p);
			spr.setColor(day_color);
			g_Window->draw(spr);


			
			if (lines[by].blocks[bx].walls[0].iHealth > 0)
			{
				verts.push_back(sf::Vertex(sf::Vector2f(p.x - 5*scale, p.y),sf::Color::Black,sf::Vector2f()));
				verts.push_back(sf::Vertex(sf::Vector2f(p.x + 5*scale, p.y), sf::Color::Black, sf::Vector2f()));
				verts.push_back(sf::Vertex(sf::Vector2f(p.x + 5*scale, p.y+blocksize.y), sf::Color::Black, sf::Vector2f()));
				verts.push_back(sf::Vertex(sf::Vector2f(p.x - 5*scale, p.y + blocksize.y), sf::Color::Black, sf::Vector2f()));
			}
			if (lines[by].blocks[bx].walls[1].iHealth > 0)
			{
				verts.push_back(sf::Vertex(sf::Vector2f(p.x, p.y-5*scale), sf::Color::Black, sf::Vector2f()));
				verts.push_back(sf::Vertex(sf::Vector2f(p.x, p.y + 5*scale), sf::Color::Black, sf::Vector2f()));

				verts.push_back(sf::Vertex(sf::Vector2f(p.x+blocksize.x, p.y + 5*scale), sf::Color::Black, sf::Vector2f()));
				verts.push_back(sf::Vertex(sf::Vector2f(p.x + blocksize.x, p.y - 5*scale), sf::Color::Black, sf::Vector2f()));

			}
			
		}
	}
	g_Window->draw(&verts[0], verts.size(), sf::PrimitiveType::Quads);
	static sf::Sprite chspr;
	chspr.setTexture(*g_Textures.get(4));
	chspr.setScale(scale, scale);
	
	//if(scale >=0.5f)
	for (auto ch : chests)
	{
		if (ch.vPosition.x > mx - width / 2 - 1 && ch.vPosition.x < mx + width / 2 + 1 && ch.vPosition.y > my - height / 2 - 1 && ch.vPosition.y < my + height / 2 + 1)
		{
			float _x = mx - ch.vPosition.x;
			float _y = my - ch.vPosition.y;
			chspr.setPosition(g_Resolution.x / 2 - _x*blocksize.x , g_Resolution.y / 2 - _y*blocksize.y );
			chspr.setTextureRect(sf::IntRect(ch.bOpen * 64, 0, 64, 64));
			g_Window->draw(chspr);
		}
	}

	static sf::Sprite shadsprite;
	shadsprite.setTextureRect(sf::IntRect(0, 0, g_Resolution.x, g_Resolution.y));
	shadsprite.setTexture(shadowtext);
	shadsprite.setColor(sf::Color(255,255,255, 64));

	g_Window->draw(shadsprite);



	return;
}

void dc_map::draw(sf::RenderTexture* T,float mx, float my, float width,bool map, bool chestdraw, bool shadow)
{
	beginshadows(mx, my, width);
	sf::Vector2f blocksize((float)(g_Resolution.x) / width, (float)(g_Resolution.x) / width);
	float scale = (float)(blocksize.x) / 128;








	static sf::Sprite spr;
	float height = width*g_Resolution.y / g_Resolution.x;

	spr.setScale(scale, scale);

	float dx = mx - (int)mx;
	float dy = my - (int)my;

	int _mx = (int)mx;
	int _my = (int)my;

	std::vector<sf::Vertex> verts;

	float shadow_angle = get_shadow_angle();
	float shadow_length = get_shadow_length();
	sf::Color day_color = get_modulation_color();

	int r = (32 * day_color.r) / 255;
	int g = (80 * day_color.g) / 255;
	int b = (225 * day_color.b) / 255;



	//IWindow::RenderOverlay(0, 0, g_Resolution.x, g_Resolution.y, r, g, b, 255);


	if (map)
	{

		//Absolute bg color
		sf::RectangleShape Rect;
		Rect.setPosition(0, 0);
		Rect.setSize(sf::Vector2f(g_Resolution.x, g_Resolution.y));
		Rect.setFillColor(sf::Color(r, g, b));
		T->draw(Rect);

		for (int x = -width / 2 - 1; x < width / 2 + 1; x++)
		{
			for (int y = -height / 2 - 1; y < height / 2 + 1; y++)
			{
				float bx = _mx + x;
				float by = _my + y;


				if (bx < 0 || bx >= size.x || by < 0 || by >= size.y)continue;
				spr.setTexture(*g_Textures.get(lines[by].blocks[bx].iTexture));


				sf::Vector2f p(g_Resolution.x / 2 + x*blocksize.x - dx*blocksize.x, g_Resolution.y / 2 + y*blocksize.y - dy*blocksize.y);
				spr.setPosition(p);
				spr.setColor(day_color);
				T->draw(spr);



				if (lines[by].blocks[bx].walls[0].iHealth > 0)
				{
					verts.push_back(sf::Vertex(sf::Vector2f(p.x - 5 * scale, p.y), sf::Color::Black, sf::Vector2f()));
					verts.push_back(sf::Vertex(sf::Vector2f(p.x + 5 * scale, p.y), sf::Color::Black, sf::Vector2f()));
					verts.push_back(sf::Vertex(sf::Vector2f(p.x + 5 * scale, p.y + blocksize.y), sf::Color::Black, sf::Vector2f()));
					verts.push_back(sf::Vertex(sf::Vector2f(p.x - 5 * scale, p.y + blocksize.y), sf::Color::Black, sf::Vector2f()));
				}
				if (lines[by].blocks[bx].walls[1].iHealth > 0)
				{
					verts.push_back(sf::Vertex(sf::Vector2f(p.x, p.y - 5 * scale), sf::Color::Black, sf::Vector2f()));
					verts.push_back(sf::Vertex(sf::Vector2f(p.x, p.y + 5 * scale), sf::Color::Black, sf::Vector2f()));

					verts.push_back(sf::Vertex(sf::Vector2f(p.x + blocksize.x, p.y + 5 * scale), sf::Color::Black, sf::Vector2f()));
					verts.push_back(sf::Vertex(sf::Vector2f(p.x + blocksize.x, p.y - 5 * scale), sf::Color::Black, sf::Vector2f()));

				}

			}
		}
		T->draw(&verts[0], verts.size(), sf::PrimitiveType::Quads);
	}
	static sf::Sprite chspr;
	chspr.setTexture(*g_Textures.get(4));
	chspr.setScale(scale, scale);

	//if(scale >=0.5f)
	if (chestdraw)
	{
		for (auto ch : chests)
		{
			if (ch.vPosition.x > mx - width / 2 - 1 && ch.vPosition.x < mx + width / 2 + 1 && ch.vPosition.y > my - height / 2 - 1 && ch.vPosition.y < my + height / 2 + 1)
			{
				float _x = mx - ch.vPosition.x;
				float _y = my - ch.vPosition.y;
				chspr.setPosition(g_Resolution.x / 2 - _x*blocksize.x, g_Resolution.y / 2 - _y*blocksize.y);
				chspr.setTextureRect(sf::IntRect(ch.bOpen * 64, 0, 64, 64));
				T->draw(chspr);
			}
		}
	}

	static sf::Sprite shadsprite;
	shadsprite.setTextureRect(sf::IntRect(0, 0, g_Resolution.x, g_Resolution.y));
	shadsprite.setTexture(shadowtext);
	shadsprite.setColor(sf::Color(255, 255, 255, 64));
	if(shadow)
	T->draw(shadsprite);



	return;
}


void dc_map::drawitems(float mx, float my, float width)
{
	sf::Vector2f blocksize((float)(g_Resolution.x) / width, (float)(g_Resolution.x) / width);
	float height = width*g_Resolution.y / g_Resolution.x;
	float scale = (float)(blocksize.x) / 128;

	static sf::Sprite itspr;
	itspr.setTexture(*g_Textures.get(5));
	itspr.setScale(scale / 2, scale / 2);

	for (auto it : items)
	{
		if (it.bOwned)continue;
		if (it.vPosition.x > mx - width / 2 - 1 && it.vPosition.x < mx + width / 2 + 1 && it.vPosition.y > my - height / 2 - 1 && it.vPosition.y < my + height / 2 + 1)
		{

			float _x = mx - it.vPosition.x;
			float _y = my - it.vPosition.y;


			static sf::Color rarities[] = { sf::Color(255,255,255,128),sf::Color(90, 180, 0, 170),sf::Color(60, 190, 250, 200),sf::Color(200, 105, 235, 255),sf::Color(240, 150, 40, 255),sf::Color(255,32,32,255) };
			itspr.setTextureRect(sf::IntRect(it.iTexture * 64, 64, 64, 64));
			itspr.setColor(rarities[it.iRarity]);
			for (int i = -2; i <= 2; i += 2)
			{
				for (int j = -2; j <= 2; j += 2)
				{
					itspr.setPosition(g_Resolution.x / 2 - _x*blocksize.x + i, g_Resolution.y / 2 - _y*blocksize.y + j);

					g_Window->draw(itspr);
				}
			}
			itspr.setTextureRect(sf::IntRect(it.iTexture * 64, 0, 64, 64));
			itspr.setPosition(g_Resolution.x / 2 - _x*blocksize.x, g_Resolution.y / 2 - _y*blocksize.y);
			
			itspr.setColor(sf::Color::White);
			g_Window->draw(itspr);

		}
	}
}

void dc_map::drawitems(sf::RenderTexture* T,float mx, float my, float width)
{
	sf::Vector2f blocksize((float)(g_Resolution.x) / width, (float)(g_Resolution.x) / width);
	float height = width*g_Resolution.y / g_Resolution.x;
	float scale = (float)(blocksize.x) / 128;

	static sf::Sprite itspr;
	itspr.setTexture(*g_Textures.get(5));
	itspr.setScale(scale / 2, scale / 2);

	for (auto it : items)
	{
		if (it.bOwned)continue;
		if (it.vPosition.x > mx - width / 2 - 1 && it.vPosition.x < mx + width / 2 + 1 && it.vPosition.y > my - height / 2 - 1 && it.vPosition.y < my + height / 2 + 1)
		{

			float _x = mx - it.vPosition.x;
			float _y = my - it.vPosition.y;


			static sf::Color rarities[] = { sf::Color(255,255,255,128),sf::Color(90, 180, 0, 170),sf::Color(60, 190, 250, 200),sf::Color(200, 105, 235, 255),sf::Color(240, 150, 40, 255),sf::Color(255,32,32,255) };
			itspr.setTextureRect(sf::IntRect(it.iTexture * 64, 64, 64, 64));
			itspr.setColor(rarities[it.iRarity]);
			for (int i = -2; i <= 2; i += 2)
			{
				for (int j = -2; j <= 2; j += 2)
				{
					itspr.setPosition(g_Resolution.x / 2 - _x*blocksize.x + i, g_Resolution.y / 2 - _y*blocksize.y + j);

					T->draw(itspr);
				}
			}
			itspr.setTextureRect(sf::IntRect(it.iTexture * 64, 0, 64, 64));
			itspr.setPosition(g_Resolution.x / 2 - _x*blocksize.x, g_Resolution.y / 2 - _y*blocksize.y);

			itspr.setColor(sf::Color::White);
			T->draw(itspr);

		}
	}
}

bool it_comp(dc_item a, dc_item b) { return a.bOwned < b.bOwned; }

//void dc_map::mark_for_delete(dc_item it)
//{
//	for (int i = 0; i < items.size(); i++)
//		if (it == items[i])
//		{
//			items[i].bOwned = true;
//			delete_items();
//			break;
//		}
//	
//}

//int dc_map::get_item_id(dc_item it)
//{
//	for (int i = 0; i < items.size(); i++)
//		if (it == items[i])
//		{
//			return i;
//		}
//}

void dc_map::delete_items()
{
	for (int i = items.size() - 1; i >= 0; i--)
	{
		if (items[i].bOwned)
		{
			items.erase(items.begin() + i);
		}
	}
	return;


	std::sort(items.begin(), items.end(), it_comp);
	while (items.size() > 0 && items[items.size() - 1].bOwned)
	{
		items.pop_back();
	}
}


struct l_t
{
	sf::Vector2f start, end;
	int type;
	l_t()
	{}

	l_t(sf::Vector2f s, sf::Vector2f e, int t)
	{
		start = s;
		end = e;
		type = t;
	}
};

struct chunk_t
{
	std::vector<l_t> lines;
};

chunk_t Chunks[625];
std::vector<l_t> all_lines;

inline bool operator==(l_t a, l_t b)
{
	return a.end == b.end && a.start == b.start && a.type == b.type;
}

void dc_map::delete_line(sf::Vector2f s, sf::Vector2f e, int typ)
{
	auto l = l_t(s, e, typ);
	int cy = s.y / 40;
	int cx = s.x / 40;

	auto original_size = Chunks[cy * 25 + cx].lines.size();

	if(Chunks[cy*25+cx].lines.size() > 0)
		Chunks[cy*25+cx].lines.erase(std::remove(Chunks[cy * 25 + cx].lines.begin(), Chunks[cy * 25 + cx].lines.end(), l), Chunks[cy * 25 + cx].lines.end());

	int als = 0;
	for (int i = 0; i < 625; i++)als += Chunks[i].lines.size();

	if(false)all_lines.erase(std::remove(all_lines.begin(), all_lines.end(), l), all_lines.end());


	//ConLog("\nall Lines Size: %d", als);
	//ConLog("\nChunks Line Size: %d", Chunks[cy * 25 + cx].lines.size());
}


void dc_map::begin_lines()
{
	all_lines.clear();

	for (int x = 0; x < size.x; x++)
	{
		for (int y = 0; y < size.y; y++)
		{
			if (lines[y].blocks[x].walls[0].iHealth > 0)
			{
				Chunks[(y/40)*25+x/40].lines.push_back(l_t(sf::Vector2f(x, y), sf::Vector2f(x, y + 1), 0));
			}
			if (lines[y].blocks[x].walls[1].iHealth > 0)
			{
				Chunks[(y / 40) * 25 + x / 40].lines.push_back(l_t(sf::Vector2f(x, y), sf::Vector2f(x + 1, y), 1));
			}
		}
	}




}

//void dc_map::update_lines()
//{
//	//return;
//	all_lines.clear();
//	for (int x = 0; x < size.x; x++)
//	{
//		for (int y = 0; y < size.y; y++)
//		{
//			if (lines[y].blocks[x].walls[0].iHealth > 0)
//			{
//				all_lines.push_back(l_t(sf::Vector2f(x, y), sf::Vector2f(x, y + 1), 0));
//			}
//			if (lines[y].blocks[x].walls[1].iHealth > 0)
//			{
//				all_lines.push_back(l_t(sf::Vector2f(x, y), sf::Vector2f(x + 1, y), 1));
//			}
//		}
//	}
//	ConLog("\nall Lines Size: %d", all_lines.size());
//}

inline float GetT1(sf::Vector2f rs, sf::Vector2f rd, sf::Vector2f ws, sf::Vector2f wd)
{
	if ((wd.y*rd.x - wd.x*rd.y) == 0)return -1;
	return (wd.x*(rs.y - ws.y) - wd.y*(rs.x - ws.x)) / (wd.y*rd.x - wd.x*rd.y);
}

inline float GetT2(sf::Vector2f rs, sf::Vector2f rd, sf::Vector2f ws, sf::Vector2f wd)
{
	if ((rd.y*wd.x - rd.x*wd.y) == 0)return -1;
	return (rd.x*(ws.y - rs.y) - rd.y*(ws.x - rs.x)) / (rd.y*wd.x - rd.x*wd.y);
}

dc_tracedata dc_map::trace_ray(sf::Vector2f a, sf::Vector2f b)
{
	if (isnan(a.x) || isnan(a.y) || isnan(b.x) || isnan(b.y))return dc_tracedata();

	dc_tracedata ret;
	ret.start = a;
	auto radius = GetDistance(a, b);
	auto rad = radius;

	sf::Vector2i Sch = sf::Vector2i((int)(a.x) / 40, (int)(a.y) / 40);
	sf::Vector2i Ech = sf::Vector2i((int)(b.x) / 40, (int)(b.y) / 40);

	int la = 0, lb = 0;
	for (int x = min(Sch.x, Ech.x); x <= max(Sch.x, Ech.x); x++)
	{
		for (int y = min(Sch.y, Ech.y); y <= max(Sch.y, Ech.y); y++)
		{
			if(x >= 0 && x <= 24 && y >= 0 && y<=24)
				for (auto l : Chunks[y*25+x].lines)
				{
					la++;
					auto t1 = GetT1(a, b - a, l.start, l.end - l.start);
					auto t2 = GetT2(a, b - a, l.start, l.end - l.start);
					if (t1 > 0 && t2 > 0 && t1 <= 1 && t2 <= 1)
					{
						if (rad > t1*radius)
						{
							rad = t1*radius;
							ret.hit_object = true;
							ret.object.x = l.start.x;
							ret.object.y = l.start.y;
							ret.type = l.type;

						}
					}
				}
		}
	}

	if(false)for (auto l : all_lines)
	{
		lb++;
		auto t1 = GetT1(a, b - a, l.start, l.end - l.start);
		auto t2 = GetT2(a, b - a, l.start, l.end - l.start);
		if (t1 > 0 && t2 > 0 && t1 <= 1 && t2 <= 1)
		{

			if (rad > t1*radius)
			{
				rad = t1*radius;
				ret.hit_object = true;
				ret.object.x = l.start.x;
				ret.object.y = l.start.y;
				ret.type = l.type;

			}
		}
	}
	ret.end = a + rad / radius*(b - a);

	return ret;
}

dc_tracedata dc_match::TracePlayers(sf::Vector2f a, sf::Vector2f b, int skip)
{
	dc_tracedata ret;
	ret.start = a;
	auto radius = GetDistance(a, b);
	auto rad = radius;
	for (int i = 0; i < 100; i++)
	{
		if (players[i].iHealth <= 0)continue;
		if (i == skip)continue;

		l_t l;
		auto angle = vec2angle((a - b).x, (a - b).y);
		auto vector = angle2vec(angle + 90);
		l.start = players[i].vPosition + vector*0.25f;
		l.end = players[i].vPosition - vector*0.25f;


		auto t1 = GetT1(a, b - a, l.start, l.end - l.start);
		auto t2 = GetT2(a, b - a, l.start, l.end - l.start);
		if (t1 > 0 && t2 > 0 && t1 <= 1 && t2 <= 1)
		{
			if (rad > t1*radius)
			{
				ret.hit_target = true;
				rad = t1*radius;
				ret.targetid = i;
			}
		}
	}
	ret.end = a + rad / radius*(b - a);
	return ret;
}

void dc_map::show_minimapui(float& mx, float &my, float width, float busx, float busy, float busr, sf::Vector2f StormMid, float StormRadius)
{
	static sf::Image img;
	static sf::Texture tex;
	static sf::Sprite spr;
	static dc_clock clock;
	static bool run_first = false;

	if (clock.GetDiff() > 1000 || !run_first)
	{
		img.create(1000, 1000, sf::Color(255, 255, 255, 255));
		auto modulate_color = get_modulation_color();
		for (int x = 0; x < 1000; x++)
		{
			for (int y = 0; y < 1000; y++)
			{




				auto color = g_Textures.getavgcolor(lines[y].blocks[x].iTexture);

				auto r = color.r*modulate_color.r / 255;
				auto g = color.g*modulate_color.g / 255;
				auto b = color.b*modulate_color.b / 255;
				if (GetDistance(sf::Vector2f(x, y), StormMid) > StormRadius)
				{
					r = 165.f*r / 255.f;
					g = 35.f*g / 255.f;
					b = 220.f*b / 255.f;
				}
				img.setPixel(x, y, sf::Color(r, g, b, 255));

			}
		}

		tex.loadFromImage(img);
		tex.setSmooth(true);
		spr.setTexture(tex);

		run_first = true;
		clock.Update();
	}


	float revarea = 50.f + width;
	float scale = g_Resolution.x*0.15 / revarea;

	spr.setPosition(g_Resolution.x*0.8, g_Resolution.y*0.05);
	spr.setScale(scale, scale);
	spr.setTextureRect(sf::IntRect(mx - 0.5*revarea, my - 0.5*revarea, revarea, revarea));
	spr.setColor(sf::Color(255, 255, 255, 128));


	g_Window->draw(spr);

	static sf::Sprite sprb;
	float bscale = 0.025f*scale;
	sprb.setOrigin(400, 300);
	sprb.setScale(bscale, bscale);
	sprb.setTexture(*g_Textures.get(50));




	sprb.setRotation(busr);

	float _X = (busx - mx)*scale + 0.875f*g_Resolution.x;
	float _Y = (busy - my)*scale + 0.05f*g_Resolution.y+0.075f*g_Resolution.x;

	//So that the bus doesn't go off of the minimap
	if (0.8f*g_Resolution.x > _X-500.f*bscale || 0.95f*g_Resolution.x < _X+ 500.f*bscale || 0.05f*g_Resolution.y > _Y- 500.f*bscale || (0.05f*g_Resolution.y + 0.15*g_Resolution.x) < _Y+ 500.f*bscale)return;

	sprb.setPosition(_X,_Y);
	sprb.setColor(sf::Color(255, 255, 255, 128));
	g_Window->draw(sprb);


}

void dc_map::show_minimap(float& mx, float &my, float width, bool show_only_player, sf::Vector2f StormMid, float StormRadius)
{
	static sf::Image img;
	static sf::Texture tex;
	static sf::Sprite spr;
	static dc_clock clock;
	static bool run_first = false;
	
	if (clock.GetDiff() > 1000 || !run_first)
	{
		img.create(1000, 1000, sf::Color(255, 255, 255, 255));
		auto modulate_color = get_modulation_color();
		for (int x = 0; x < 1000; x++)
		{
			for (int y = 0; y < 1000; y++)
			{




				auto color = g_Textures.getavgcolor(lines[y].blocks[x].iTexture);

				auto r = color.r*modulate_color.r / 255;
				auto g = color.g*modulate_color.g / 255;
				auto b = color.b*modulate_color.b / 255;
				if (GetDistance(sf::Vector2f(x, y), StormMid) > StormRadius)
				{
					r = 165.f*r/255.f;
					g = 35.f*g/255.f;
					b = 220.f*b / 255.f;
				}
				img.setPixel(x, y, sf::Color(r,g,b,255));
				
			}
		}

		tex.loadFromImage(img);
		tex.setSmooth(true);
		spr.setTexture(tex);

		run_first = true;
		clock.Update();
	}

	spr.setPosition(g_Resolution.x*0.25, g_Resolution.y*0.5 - g_Resolution.x*0.25);
	float scale = (float)g_Resolution.x / 2000;
	spr.setScale(scale, scale);
	IWindow::RenderOverlay(g_Resolution.x*0.2475, g_Resolution.y*0.5 - g_Resolution.x*0.2525, g_Resolution.x*0.505, g_Resolution.x*0.505, 255, 255, 255, 255);
	g_Window->draw(spr);


	for (auto lab : labels)
	{
		float radius = lab.size*g_Resolution.x*0.50 / 1000;
		float _x = lab.vPosition.x*g_Resolution.x*0.5 / 1000 + g_Resolution.x*0.25;
		float _y = lab.vPosition.y*g_Resolution.x*0.5 / 1000 + g_Resolution.y*0.5 - g_Resolution.x*0.25;
		//continue;
		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
					IWindow::RenderTextBMiddle(_x+i, _y+j, 0, 0, lab.n, 16 * g_Resolution.x / 1280, 0,0,0);
			}
		}
		IWindow::RenderTextBMiddle(_x, _y, 0, 0, lab.n, 16 * g_Resolution.x / 1280, 255, 255, 255);

	}



	if(show_only_player)
	{
		float cradius = 5.f*g_Resolution.y / 720;
		sf::CircleShape c;
		
		auto topleft = screen_to_world(mx, my, width, g_Resolution.x/2,g_Resolution.y/2);


		c.setRadius(cradius);

		float top = g_Resolution.y*0.5 - g_Resolution.x*0.25 + g_Resolution.x*0.5*(topleft.y) / 1000;
		float left = g_Resolution.x*0.25 + g_Resolution.x*0.5*(topleft.x) / 1000;
		c.setPosition(left-cradius, top-cradius);
		c.setFillColor(sf::Color::White);
		c.setOutlineColor(sf::Color::Black);
		c.setOutlineThickness(2);

		g_Window->draw(c);
	}
	else
	{

		if (g_Mouse.IsBetween(g_Resolution.x*0.2475, g_Resolution.y*0.5 - g_Resolution.x*0.2525, g_Resolution.x*0.505, g_Resolution.x*0.505, g_Mouse.Coords.x, g_Mouse.Coords.y) && g_Mouse.left_click)
		{
			mx = (g_Mouse.Coords.x - g_Resolution.x*0.2475) * 1000 / (g_Resolution.x*0.505);
			my = (g_Mouse.Coords.y - (g_Resolution.y*0.5 - g_Resolution.x*0.2525)) * 1000 / (g_Resolution.x*0.505);
		}

		auto topleft = screen_to_world(mx, my, width, 0, 0);
		auto botright = screen_to_world(mx, my, width, g_Resolution.x, g_Resolution.y);


		float top = g_Resolution.y*0.5-g_Resolution.x*0.25 + g_Resolution.x*0.5*(topleft.y) / 1000;
		float bottom = g_Resolution.y*0.5 - g_Resolution.x*0.25 + g_Resolution.x*0.5*(botright.y) / 1000;
		float left = g_Resolution.x*0.25 + g_Resolution.x*0.5*(topleft.x) / 1000;
		float right = g_Resolution.x*0.25 + g_Resolution.x*0.5*(botright.x) / 1000;

		sf::Vertex vert[] =
		{
			sf::Vertex(sf::Vector2f(left,top),sf::Color(255,255,255,255),sf::Vector2f()),
			sf::Vertex(sf::Vector2f(right,top),sf::Color(255,255,255,255),sf::Vector2f()),
			sf::Vertex(sf::Vector2f(right,bottom),sf::Color(255,255,255,255),sf::Vector2f()),
			sf::Vertex(sf::Vector2f(left,bottom),sf::Color(255,255,255,255),sf::Vector2f()),
			sf::Vertex(sf::Vector2f(left,top),sf::Color(255,255,255,255),sf::Vector2f()),
		};

		g_Window->draw(vert, 5, sf::LineStrip);

	}

}

void dc_map::load(char* n)
{
	this->define(1000, 1000);
	file_t fMap;
	char name[64]; sprintf(name, "%s.map", n);
	fMap.ReadInMemory(name);
	for (int y = 0; y < 1000; y++)
	{
		for (int x = 0; x < 1000; x++)
		{
			//memcpy(&lines[y].blocks[x], fMap.loc_in_mem + (y * 1000 + x) * sizeof(dc_block), sizeof(dc_block));
			for (int i = 0; i < sizeof(dc_block); i++)
			{
				*(((char*)(&lines[y].blocks[x])) + i) = *(fMap.loc_in_mem + (y * 1000 + x) * sizeof(dc_block) + i);
			}
		}
		//ConLog("\n%.1f", (float)y / 10);
	}
	delete[] fMap.loc_in_mem;

	chests.clear();
	sprintf(name, "%s.chest", n);
	file_t fChest;
	fChest.ReadInMemory(name);
	for (int c = 0; c < fChest.size / sizeof(dc_chest); c++)
	{
		dc_chest* pch = (dc_chest*)(fChest.loc_in_mem + c * sizeof(dc_chest));
		chests.push_back(*pch);

	}
	printf("Total number of chests: %d (%d)", fChest.size / sizeof(dc_chest),chests.size());
	delete[]fChest.loc_in_mem;
	labels.clear();
	sprintf(name, "%s.label", n);
	file_t fLabel;
	fLabel.ReadInMemory(name);
	for (int c = 0; c < fLabel.size / sizeof(dc_label); c++)
	{
		dc_label* pch = (dc_label*)(fLabel.loc_in_mem + c * sizeof(dc_label));
		labels.push_back(*pch);

	}
	delete[]fLabel.loc_in_mem;
}