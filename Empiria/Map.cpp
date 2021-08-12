#include "Structs.h"


sf::Vector2f orient;

sf::Vector2f GetPixelVector(sf::Vector2i c)
{
	int my = orient.y;
	int mx = orient.x;



	return sf::Vector2f(c.x * 64 - mx, 720-c.y * 64 + my);
}
sf::Vector2f GetPixelVectorDef(sf::Vector2i c)
{



	return sf::Vector2f(c.x * 64, 720 - c.y * 64-18);
}


void trixel_t::Set(int ax, int ay, int bx, int by, int cx, int cy)
{
	points[0].x = ax;
	points[0].y = ay;
	points[1].x = bx;
	points[1].y = by;
	points[2].x = cx;
	points[2].y = cy;
}


void trixel_t::Draw()
{
	static bool bLoaded = false;
	static file_t f = g_Files.GetFileByName("tex_default.png");
	static sf::Texture t;

	if (!bLoaded)
	{
		bLoaded = true;
		t.loadFromMemory(f.loc_in_mem, f.size);
	}


	sf::Vertex tri[] =
	{
		sf::Vertex(GetPixelVector(points[0]),sf::Color::White,GetPixelVectorDef(points[0])),
		sf::Vertex(GetPixelVector(points[1]),sf::Color::White,GetPixelVectorDef(points[1])),
		sf::Vertex(GetPixelVector(points[2]),sf::Color::White,GetPixelVectorDef(points[2])),
	};



	sf::RenderStates states;
	states.texture = &t;
	g_Window->draw(tri, 3, sf::PrimitiveType::Triangles, states);
	//g_Window->draw(vera, states);

}





void map_t::AddTrixel(int ax, int ay, int bx, int by, int cx, int cy)
{
	trixel_t add;
	add.Set(ax, ay, bx, by, cx, cy);
	Trixels.push_back(add);
}

void map_t::Draw()
{
	for (auto it : Trixels)
	{
		it.Draw();
	}
}
