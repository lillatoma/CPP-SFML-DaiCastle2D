#pragma once
#include "includes.h"

enum TileStatus
{
	TS_UNUSED,
	TS_START,
	TS_TARGET,
	TS_USED,
	TS_PATH,
	TS_READY,
	TS_UNWALKABLE
};

struct tile_t
{
	sf::Vector2i coord;
	int target_dist = INT_MAX / 2;
	int start_dist = INT_MAX / 2;
	int status = TS_UNUSED;
};

struct tilemap_t
{
	std::vector<std::vector<tile_t>> Tiles;
	//tile_t** Tiles;
	sf::Vector2i size;

	void Setup(int x, int y);
	void Draw(int x, int y, int s);
	void Brush(int x, int y, int s);
	void Reset();



	tile_t** GetNeighbors(int x, int y);

};

struct AStar
{
	static bool FindPath(tilemap_t* T);
	static bool FindPathSTD(tilemap_t* T, std::vector<sf::Vector2f>& printvec);
	static bool FindPathSTDS(tilemap_t* T);
	static bool FindPathOneIter(tilemap_t* T);
	static int GetDist(int ax, int ay, int bx, int by);
	static int GetDistFromStart(tilemap_t* T, int x, int y);
};


