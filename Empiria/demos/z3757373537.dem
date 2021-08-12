#pragma once
#include "includes.h"


struct trixel_t
{
	sf::Vector2i points[3];
	int textureID = 0;

	void Set(int ax, int ay, int bx, int by, int cx, int cy);
	void Draw();

	trixel_t()
	{
		Set(0, 0, 1, 0, 0, 1);
	}
};

struct map_t
{
	bool init = false;
	std::vector<trixel_t> Trixels;

	void AddTrixel(int ax, int ay, int bx, int by, int cx, int cy);
	void Draw();


	map_t()
	{
		//Trixels.push_back(trixel_t());
	}


};


struct shootball_t
{
	sf::Vector2f vecCoord;

	int hp = 100;
	int armor = 0;


};


struct player_t
{
	shootball_t* unit;
	int kills = 0;
	int deaths = 0;

};

struct game_t
{

};


extern sf::Vector2f orient;