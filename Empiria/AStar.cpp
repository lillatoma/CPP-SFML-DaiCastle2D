#include "AStar.h"


void tilemap_t::Setup(int x, int y)
{
	if (Tiles.size() > 0)
	{
		for (int t = Tiles.size() - 1; t >= 0; t--)
		{
			Tiles[t].clear();
			//Tiles.pop_back();
		}

		Tiles.clear();
	}
	Tiles = std::vector<std::vector<tile_t>>();
	for (int _x = 0; _x < x; _x++)
	{
		std::vector<tile_t> vy;
		for (int _y = 0; _y < y; _y++)
		{
			tile_t toil;
			toil.coord = sf::Vector2i(_x, _y);
			vy.push_back(toil);
		}
		Tiles.push_back(vy);
	}

	size.x = x;
	size.y = y;
}

void tilemap_t::Reset()
{
	for (int x = 0; x < size.x; x++)
	{
		for (int y = 0; y < size.y; y++)
		{
			if (Tiles[x][y].status != TS_UNWALKABLE)
			{
				Tiles[x][y].status = TS_UNUSED;
				Tiles[x][y].start_dist = INT_MAX / 2;
				Tiles[x][y].target_dist = INT_MAX / 2;
			}
		}
	}
}

void tilemap_t::Brush(int x, int y, int s)
{
	static int brushmode = -1;
	int brushsize = 10;

	static auto lastM = g_Mouse.Coords;

	sf::Vector2f _tilesize = sf::Vector2f((float)s / size.x, (float)s / size.y);

	if (g_Mouse.isHolding() && brushmode != -1)
	{
		int dx = abs(g_Mouse.Coords.x - lastM.x);
		int dy = abs(g_Mouse.Coords.y - lastM.y);

		float dif = sqrt(float(dx*dx + dy*dy));

		for (int i = 0; i < dif; i++)
		{
			int midx = (i*g_Mouse.Coords.x + (dif - i)*lastM.x) / dif;
			int midy = (i*g_Mouse.Coords.y + (dif - i)*lastM.y) / dif;


			for (int _x = 0; _x < brushsize; _x++)
			{
				for (int _y = 0; _y < brushsize; _y++)
				{
					int _tx = (float)((midx + _x - brushsize / 2) - x) / _tilesize.x;
					int _ty = (float)(((y + s) - midy + _y - brushsize / 2)) / _tilesize.y;

					if (_tx >= 0 && _tx < size.x && _ty >= 0 && _ty < size.y)
					{
						if (Tiles[_x][_y].status == TS_UNUSED || Tiles[_x][_y].status == TS_UNWALKABLE)Tiles[_tx][_ty].status = brushmode;
					}
				}
			}
		}
	}


	for (int _x = 0; _x < size.x; _x++)
	{
		for (int _y = 0; _y < size.y; _y++)
		{
			float _tx = x + _x*_tilesize.x;
			float _ty = (y + s) - (_y + 1)*_tilesize.y;

			if (g_Mouse.hasReleased(true) && g_Mouse.IsClickValid(true) && g_Mouse.IsBetween(_tx, _ty, _tilesize.x, _tilesize.y, g_Mouse.Coords.x, g_Mouse.Coords.y))
			{
				static bool rcmode = false;
				static int rc[] = { TS_START, TS_TARGET };

				for (int i = 0; i < size.x; i++)
				{
					for (int j = 0; j < size.x; j++)
					{
						if (Tiles[i][j].status == rc[rcmode])Tiles[i][j].status = TS_UNUSED;
					}
				}
				Tiles[_x][_y].status = rc[rcmode];
				rcmode = !rcmode;
			}

			if (g_Mouse.isHolding())
			{
				if (!g_Mouse.IsBetween(_tx - brushsize / 2, _ty - brushsize / 2, _tilesize.x + brushsize, _tilesize.y + brushsize, g_Mouse.Coords.x, g_Mouse.Coords.y))continue;
				if (brushmode == -1)
				{
					if (Tiles[_x][_y].status == TS_UNUSED)brushmode = TS_UNWALKABLE;
					else if (Tiles[_x][_y].status == TS_UNWALKABLE)brushmode = TS_UNUSED;
				}
				if (Tiles[_x][_y].status == TS_UNUSED || Tiles[_x][_y].status == TS_UNWALKABLE)Tiles[_x][_y].status = brushmode;
			}
			else brushmode = -1;


		}
	}
	lastM = g_Mouse.Coords;
}

void tilemap_t::Draw(int x, int y, int s)
{
	static sf::Color col[] = { sf::Color(225,225,225,255), sf::Color(48,96,192,255), sf::Color(48,192,96,255),sf::Color(128,0,0,255),sf::Color(48,60,160,255),sf::Color(160,160,48,255),sf::Color(32,32,32,255) };
	sf::Vector2f _tilesize = sf::Vector2f((float)s / size.x, (float)s / size.y);


	std::vector<sf::Vertex> Vertices;

	IWindow::RenderOverlay(x, y, (_tilesize.x*size.x), _tilesize.y*size.y, 0, 0, 0, 255);
	for (int _x = 0; _x < size.x; _x++)
	{
		for (int _y = 0; _y < size.y; _y++)
		{
			float _tx = x + _x*_tilesize.x;
			float _ty = (y + s) - (_y + 1)*_tilesize.y;
			//IWindow::RenderOverlay(_tx, _ty, _tilesize.x - (_tilesize.x > 5), _tilesize.y - (_tilesize.y > 5), col[Tiles[_x][_y].status].r, col[Tiles[_x][_y].status].g, col[Tiles[_x][_y].status].b, col[Tiles[_x][_y].status].a);

			sf::Vertex v1(sf::Vector2f(_tx, _ty));
			sf::Vertex v2(sf::Vector2f(_tx + _tilesize.x - (_tilesize.x > 5), _ty));
			sf::Vertex v3(sf::Vector2f(_tx + _tilesize.x - (_tilesize.x > 5), _ty + _tilesize.y - (_tilesize.y > 5)));
			sf::Vertex v4(sf::Vector2f(_tx, _ty + _tilesize.y - (_tilesize.y > 5)));

			v1.color = col[Tiles[_x][_y].status];
			v2.color = col[Tiles[_x][_y].status];
			v3.color = col[Tiles[_x][_y].status];
			v4.color = col[Tiles[_x][_y].status];

			Vertices.push_back(v1);
			Vertices.push_back(v2);
			Vertices.push_back(v3);
			Vertices.push_back(v4);


			if (Tiles[_x][_y].status == TS_USED || Tiles[_x][_y].status == TS_READY)
			{
				if (_tilesize.x < 40)continue;
				char buf[16];
				sprintf(buf, "%d", Tiles[_x][_y].start_dist + Tiles[_x][_y].target_dist);
				IWindow::RenderTextB(_tx, _ty, buf, 16);
			}

		}
	}

	sf::Vertex* n = &Vertices[0];

	g_Window->draw(n, Vertices.size(), sf::PrimitiveType::Quads);
}

inline tile_t** tilemap_t::GetNeighbors(int x, int y)
{
	tile_t** retTiles = new tile_t*[8];

	for (int i = 0; i < 8; i++)retTiles[i] = nullptr;

	int tiles_f = 0;
	for (int _x = x - 1; _x <= x + 1; _x++)
	{
		if (_x < 0 || _x >= size.x)continue;
		for (int _y = y - 1; _y <= y + 1; _y++)
		{
			if (_y < 0 || _y >= size.y)continue;
			if (_x == x && _y == y)continue;
			if (Tiles[_x][_y].status == TS_UNWALKABLE)continue;

			retTiles[tiles_f] = &Tiles[_x][_y];
			tiles_f++;
		}
	}

	for (int i = 0; i < 8; i++)
	{
		if (retTiles[i] == nullptr)continue;
	}



	return retTiles;
}

inline int AStar::GetDist(int ax, int ay, int bx, int by)
{
	int x = abs(ax - bx);
	int y = abs(ay - by);

	if (x > y)
		return 14 * y + 10 * (x - y);
	else return 14 * x + 10 * (y - x);


	if (x < 0)x = -x;
	if (y < 0) y = -y;

	int l = x - y;
	if (l < 0)l = -l;
	int d = min(x, y);


	int val = l * 10 + d * 14;

	if (x > y)
		return 14 * y + 10 * (x - y);
	else return 14 * x + 10 * (y - x);



	return val;
}

inline int AStar::GetDistFromStart(tilemap_t* T, int x, int y)
{
	auto neigh = T->GetNeighbors(x, y);

	tile_t* ch = nullptr;

	for (int i = 0; i < 8; i++)
	{
		if (neigh[i] == nullptr)continue;
		if (neigh[i]->status == TS_UNUSED)continue;
		if (ch == nullptr)ch = neigh[i];
		if (neigh[i]->start_dist < ch->start_dist)ch = neigh[i];
	}


	delete[] neigh;
	return ch->start_dist + GetDist(ch->coord.x, ch->coord.y, x, y);
}

bool AStar::FindPath(tilemap_t* T)
{
	tile_t* SP = nullptr;
	tile_t* TP = nullptr;
	bool is_started = false;
	bool hasready = false;
	bool haspath = false;

	for (int i = 0; i < T->size.x; i++)
	{
		for (int j = 0; j < T->size.y; j++)
		{
			if (T->Tiles[i][j].status == TS_START)SP = &T->Tiles[i][j];
			else if (T->Tiles[i][j].status == TS_TARGET)TP = &T->Tiles[i][j];
			else if (T->Tiles[i][j].status == TS_READY || T->Tiles[i][j].status == TS_USED)is_started = true;
			if (T->Tiles[i][j].status == TS_READY)hasready = true;
			if (T->Tiles[i][j].status == TS_PATH)haspath = true;
		}
	}
	if (SP == nullptr || TP == nullptr)
	{
		//printf("\nNo start or target point found");
		return true;
	}

	if (TP->start_dist != INT_MAX / 2 || haspath)
	{
		if (!haspath)
		{
			tile_t* closest_point = nullptr;
			while (true)
			{
				if (GetAsyncKeyState(VK_F6) & 1)
				{
					g_Window->clear();
					T->Draw(50, 50, 640);
					g_Window->display();
				}
				auto neighs = T->GetNeighbors(SP->coord.x, SP->coord.y);
				auto neight = T->GetNeighbors(TP->coord.x, TP->coord.y);
				bool hps = false, hpt = false;


				for (int i = 0; i < 8; i++)
				{
					if (neighs[i] != nullptr && neighs[i]->status == TS_PATH)hps = true;
					if (neight[i] != nullptr && neight[i]->status == TS_PATH)hpt = true;
				}
				if (hps && hpt)break;


				if (closest_point == nullptr)
				{
					for (int i = 0; i < 8; i++)
					{
						if (neight[i] == nullptr || neight[i]->status != TS_USED)continue;
						if (closest_point == nullptr)closest_point = neight[i];
						if (closest_point->start_dist + closest_point->target_dist >= neight[i]->start_dist + neight[i]->target_dist)
						{
							if (closest_point->start_dist + closest_point->target_dist > neight[i]->start_dist + neight[i]->target_dist)closest_point = neight[i];
							else if (neight[i]->target_dist < closest_point->target_dist)closest_point = neight[i];
						}
					}
					closest_point->status = TS_PATH;
				}
				else
				{
					auto old_cl = closest_point;
					auto neighC = T->GetNeighbors(closest_point->coord.x, closest_point->coord.y);
					closest_point = nullptr;
					for (int i = 0; i < 8; i++)
					{
						if (neighC[i] == nullptr || neighC[i]->status != TS_USED)continue;
						if (closest_point == nullptr)closest_point = neighC[i];
						if (closest_point->start_dist + closest_point->target_dist >= neighC[i]->start_dist + neighC[i]->target_dist)
						{
							//if (closest_point->start_dist + closest_point->target_dist > neighC[i]->start_dist + neighC[i]->target_dist)closest_point = neighC[i];
							//else
							if (neighC[i]->start_dist < closest_point->start_dist)closest_point = neighC[i];
						}
					}
					if (closest_point == nullptr)
						closest_point = old_cl;
					closest_point->status = TS_PATH;

					delete[] neighC;
				}
				delete[] neighs;
				delete[] neight;








			}
			haspath = true;
		}
		//printf("\nPath already found");
		return true;

	}
	if (!is_started)
	{
		auto neigh = T->GetNeighbors(SP->coord.x, SP->coord.y);

		SP->start_dist = 0;
		SP->target_dist = GetDist(SP->coord.x, SP->coord.y, TP->coord.x, TP->coord.y);
		for (int i = 0; i < 8; i++)
		{
			if (neigh[i] == nullptr)continue;
			neigh[i]->status = TS_READY;
			neigh[i]->start_dist = GetDistFromStart(T, neigh[i]->coord.x, neigh[i]->coord.y);
			neigh[i]->target_dist = GetDist(neigh[i]->coord.x, neigh[i]->coord.y, TP->coord.x, TP->coord.y);
		}


		delete[] neigh;
	}





	if (!hasready)

	{
		//printf("\nThere is no path between the start and the target");
		return true;

	}
	tile_t* lowest_value = nullptr;
	for (int i = 0; i < T->size.x; i++)
	{
		for (int j = 0; j < T->size.y; j++)
		{
			if (T->Tiles[i][j].status == TS_UNWALKABLE || T->Tiles[i][j].status == TS_USED || T->Tiles[i][j].status == TS_START)continue;
			if (T->Tiles[i][j].status == TS_UNUSED)continue;
			if (lowest_value == nullptr)lowest_value = &T->Tiles[i][j];
			if (T->Tiles[i][j].start_dist + T->Tiles[i][j].target_dist <= lowest_value->start_dist + lowest_value->target_dist)
			{
				if (T->Tiles[i][j].start_dist + T->Tiles[i][j].target_dist < lowest_value->start_dist + lowest_value->target_dist)
					lowest_value = &T->Tiles[i][j];
				if (T->Tiles[i][j].target_dist < lowest_value->target_dist)
					lowest_value = &T->Tiles[i][j];
			}
		}
	}

	//printf("\n%d | %d is the lowest value with %d");

	if (lowest_value != nullptr)
	{
		lowest_value->status = TS_USED;

		auto neigh = T->GetNeighbors(lowest_value->coord.x, lowest_value->coord.y);

		for (int i = 0; i < 8; i++)
		{
			if (neigh[i] == nullptr)continue;
			if (neigh[i]->status == TS_START)continue;
			if (neigh[i]->status == TS_USED)
			{
				if (neigh[i]->start_dist > lowest_value->start_dist)
				{
					neigh[i]->start_dist = GetDistFromStart(T, neigh[i]->coord.x, neigh[i]->coord.y);
					neigh[i]->target_dist = GetDist(neigh[i]->coord.x, neigh[i]->coord.y, TP->coord.x, TP->coord.y);
				}
				continue;
			}
			if (neigh[i]->status == TS_TARGET)
			{
				neigh[i]->start_dist = GetDistFromStart(T, neigh[i]->coord.x, neigh[i]->coord.y);
				continue;
			}
			neigh[i]->status = TS_READY;
			neigh[i]->start_dist = GetDistFromStart(T, neigh[i]->coord.x, neigh[i]->coord.y);
			neigh[i]->target_dist = GetDist(neigh[i]->coord.x, neigh[i]->coord.y, TP->coord.x, TP->coord.y);
		}
		delete[] neigh;
	}



	return false;
}


bool AStar::FindPathOneIter(tilemap_t* T)
{
	tile_t* SP = nullptr;
	tile_t* TP = nullptr;
	bool is_started = false;

	for (int i = 0; i < T->size.x; i++)
	{
		for (int j = 0; j < T->size.y; j++)
		{
			if (T->Tiles[i][j].status == TS_START)SP = &T->Tiles[i][j];
			else if (T->Tiles[i][j].status == TS_TARGET)TP = &T->Tiles[i][j];
			else if (T->Tiles[i][j].status == TS_READY || T->Tiles[i][j].status == TS_USED)is_started = true;
		}
	}

	if (SP == nullptr || TP == nullptr)
	{
		//printf("\nNo start or target point found");
		return true;
	}
	if (!is_started)
	{
		auto neigh = T->GetNeighbors(SP->coord.x, SP->coord.y);

		SP->start_dist = 0;
		SP->target_dist = GetDist(SP->coord.x, SP->coord.y, TP->coord.x, TP->coord.y);
		for (int i = 0; i < 8; i++)
		{
			if (neigh[i] == nullptr)continue;
			neigh[i]->status = TS_READY;
			neigh[i]->start_dist = GetDistFromStart(T, neigh[i]->coord.x, neigh[i]->coord.y);
			neigh[i]->target_dist = GetDist(neigh[i]->coord.x, neigh[i]->coord.y, TP->coord.x, TP->coord.y);
		}


		delete[] neigh;
	}


	while (true)
	{

		bool hasready = false;

		for (int i = 0; i < T->size.x; i++)
		{
			for (int j = 0; j < T->size.y; j++)
			{
				if (T->Tiles[i][j].status == TS_READY)hasready = true;
			}
			if (hasready)break;
		}


		if (!hasready)

		{
			//printf("\nThere is no path between the start and the target");
			return true;

		}

		tile_t* lowest_value = nullptr;

		for (int i = 0; i < T->size.x; i++)
		{
			for (int j = 0; j < T->size.y; j++)
			{
				if (T->Tiles[i][j].status == TS_UNWALKABLE || T->Tiles[i][j].status == TS_USED || T->Tiles[i][j].status == TS_START)continue;
				if (T->Tiles[i][j].status == TS_UNUSED)continue;
				if (lowest_value == nullptr)lowest_value = &T->Tiles[i][j];
				if (T->Tiles[i][j].start_dist + T->Tiles[i][j].target_dist <= lowest_value->start_dist + lowest_value->target_dist)
				{
					if (T->Tiles[i][j].start_dist + T->Tiles[i][j].target_dist < lowest_value->start_dist + lowest_value->target_dist)
						lowest_value = &T->Tiles[i][j];
					if (T->Tiles[i][j].target_dist < lowest_value->target_dist)
						lowest_value = &T->Tiles[i][j];
				}
			}
		}

		//printf("\n%d | %d is the lowest value with %d");

		if (lowest_value != nullptr)
		{
			lowest_value->status = TS_USED;

			auto neigh = T->GetNeighbors(lowest_value->coord.x, lowest_value->coord.y);

			for (int i = 0; i < 8; i++)
			{
				if (neigh[i] == nullptr)continue;
				if (neigh[i]->status == TS_START)continue;
				if (neigh[i]->status == TS_USED)
				{
					if (neigh[i]->start_dist > lowest_value->start_dist)
					{
						neigh[i]->start_dist = GetDistFromStart(T, neigh[i]->coord.x, neigh[i]->coord.y);
						neigh[i]->target_dist = GetDist(neigh[i]->coord.x, neigh[i]->coord.y, TP->coord.x, TP->coord.y);
					}
					continue;
				}
				if (neigh[i]->status == TS_TARGET)
				{
					neigh[i]->start_dist = GetDistFromStart(T, neigh[i]->coord.x, neigh[i]->coord.y);
					continue;
				}
				neigh[i]->status = TS_READY;
				neigh[i]->start_dist = GetDistFromStart(T, neigh[i]->coord.x, neigh[i]->coord.y);
				neigh[i]->target_dist = GetDist(neigh[i]->coord.x, neigh[i]->coord.y, TP->coord.x, TP->coord.y);
			}
			delete[] neigh;
		}

		if (TP->start_dist != INT_MAX / 2)
		{
			{
				tile_t* closest_point = nullptr;
				while (true)
				{
					if (GetAsyncKeyState(VK_F6) & 1)
					{
						g_Window->clear();
						T->Draw(50, 50, 640);
						g_Window->display();
					}
					auto neighs = T->GetNeighbors(SP->coord.x, SP->coord.y);
					auto neight = T->GetNeighbors(TP->coord.x, TP->coord.y);
					bool hps = false, hpt = false;


					for (int i = 0; i < 8; i++)
					{
						if (neighs[i] != nullptr && neighs[i]->status == TS_PATH)hps = true;
						if (neight[i] != nullptr && neight[i]->status == TS_PATH)hpt = true;
					}
					if (hps && hpt)break;


					if (closest_point == nullptr)
					{
						for (int i = 0; i < 8; i++)
						{
							if (neight[i] == nullptr || neight[i]->status != TS_USED)continue;
							if (closest_point == nullptr)closest_point = neight[i];
							if (closest_point->start_dist + closest_point->target_dist >= neight[i]->start_dist + neight[i]->target_dist)
							{
								if (closest_point->start_dist + closest_point->target_dist > neight[i]->start_dist + neight[i]->target_dist)closest_point = neight[i];
								else if (neight[i]->target_dist < closest_point->target_dist)closest_point = neight[i];
							}
						}
						closest_point->status = TS_PATH;
					}
					else
					{
						auto old_cl = closest_point;
						auto neighC = T->GetNeighbors(closest_point->coord.x, closest_point->coord.y);
						closest_point = nullptr;
						for (int i = 0; i < 8; i++)
						{
							if (neighC[i] == nullptr || neighC[i]->status != TS_USED)continue;
							if (closest_point == nullptr)closest_point = neighC[i];
							if (closest_point->start_dist + closest_point->target_dist >= neighC[i]->start_dist + neighC[i]->target_dist)
							{
								//if (closest_point->start_dist + closest_point->target_dist > neighC[i]->start_dist + neighC[i]->target_dist)closest_point = neighC[i];
								//else
								if (neighC[i]->start_dist < closest_point->start_dist)closest_point = neighC[i];
							}
						}
						if (closest_point == nullptr)
							closest_point = old_cl;
						closest_point->status = TS_PATH;

						delete[] neighC;
					}
					delete[] neighs;
					delete[] neight;








				}
			}
			//printf("\nPath already found");
			return true;

		}



	}
	return false;
}


bool tile_comp(tile_t* i, tile_t* j) { return (i->start_dist + i->target_dist<j->start_dist + j->target_dist); }

bool AStar::FindPathSTD(tilemap_t* T, std::vector<sf::Vector2f>& printvec)
{
	printvec.clear();
	std::vector<tile_t*> Used;
	std::vector<tile_t*> Ready;


	int nodes = 0;

	tile_t* SP = nullptr;
	tile_t* TP = nullptr;
	bool is_started = false;

	for (int i = 0; i < T->size.x; i++)
	{
		for (int j = 0; j < T->size.y; j++)
		{
			if (T->Tiles[i][j].status == TS_START)SP = &T->Tiles[i][j];
			else if (T->Tiles[i][j].status == TS_TARGET)TP = &T->Tiles[i][j];
			else if (T->Tiles[i][j].status == TS_READY || T->Tiles[i][j].status == TS_USED)is_started = true;
		}
	}

	if (SP == nullptr || TP == nullptr)
	{
		//printf("\nNo start or target point found");
		return true;
	}
	if (!is_started)
	{
		auto neigh = T->GetNeighbors(SP->coord.x, SP->coord.y);

		SP->start_dist = 0;
		SP->target_dist = GetDist(SP->coord.x, SP->coord.y, TP->coord.x, TP->coord.y);
		for (int i = 0; i < 8; i++)
		{
			if (neigh[i] == nullptr)continue;
			neigh[i]->status = TS_READY;
			neigh[i]->start_dist = GetDist(SP->coord.x, SP->coord.y, neigh[i]->coord.x, neigh[i]->coord.y);
			neigh[i]->target_dist = GetDist(neigh[i]->coord.x, neigh[i]->coord.y, TP->coord.x, TP->coord.y);
			Ready.push_back(neigh[i]);
		}


		delete[] neigh;
	}


	while (true)
	{

		bool hasready = false;


		for (auto it : Ready)
		{
			hasready = true;
			break;
		}

		if (!hasready)

		{
			//printf("\nThere is no path between the start and the target");
			return true;

		}

		tile_t* lowest_value = nullptr;

		for (auto it : Ready)
		{
			if (lowest_value == nullptr)lowest_value = it;
			if (it->start_dist + it->target_dist <= lowest_value->start_dist + lowest_value->target_dist)
			{
				if (it->start_dist + it->target_dist < lowest_value->start_dist + lowest_value->target_dist)
					lowest_value = it;
				if (it->target_dist < lowest_value->target_dist)
					lowest_value = it;
			}
		}

		//printf("\n%d | %d is the lowest value with %d");

		if (lowest_value != nullptr)
		{
			lowest_value->status = TS_USED;
			Used.push_back(lowest_value);
			nodes++;
			if(Ready.size() > 0)
			Ready.erase(std::remove(Ready.begin(), Ready.end(), lowest_value), Ready.end());


			auto neigh = T->GetNeighbors(lowest_value->coord.x, lowest_value->coord.y);

			for (int i = 0; i < 8; i++)
			{
				if (neigh[i] == nullptr)continue;
				if (neigh[i]->status == TS_START)continue;
				if (neigh[i]->status == TS_USED)
				{
					if (neigh[i]->start_dist > lowest_value->start_dist)
					{
						neigh[i]->start_dist = min(neigh[i]->start_dist, lowest_value->start_dist + GetDist(lowest_value->coord.x, lowest_value->coord.y, neigh[i]->coord.x, neigh[i]->coord.y));
						neigh[i]->target_dist = GetDist(neigh[i]->coord.x, neigh[i]->coord.y, TP->coord.x, TP->coord.y);
					}
					continue;
				}
				if (neigh[i]->status == TS_TARGET)
				{
					neigh[i]->start_dist = min(neigh[i]->start_dist, lowest_value->start_dist + GetDist(lowest_value->coord.x, lowest_value->coord.y, neigh[i]->coord.x, neigh[i]->coord.y));
					continue;
				}

				neigh[i]->start_dist = min(neigh[i]->start_dist, lowest_value->start_dist + GetDist(lowest_value->coord.x, lowest_value->coord.y, neigh[i]->coord.x, neigh[i]->coord.y));
				neigh[i]->target_dist = GetDist(neigh[i]->coord.x, neigh[i]->coord.y, TP->coord.x, TP->coord.y);

				if (neigh[i]->status != TS_READY)
					Ready.push_back(neigh[i]);
				neigh[i]->status = TS_READY;
			}
			delete[] neigh;
		}

		if (TP->start_dist != INT_MAX / 2)
		{
			{
				tile_t* closest_point = nullptr;
				while (true)
				{
					if (GetAsyncKeyState(VK_F6) & 1)
					{
						g_Window->clear();
						T->Draw(50, 50, 640);
						g_Window->display();
					}
					auto neighs = T->GetNeighbors(SP->coord.x, SP->coord.y);
					auto neight = T->GetNeighbors(TP->coord.x, TP->coord.y);
					bool hps = false, hpt = false;


					for (int i = 0; i < 8; i++)
					{
						if (neighs[i] != nullptr && neighs[i]->status == TS_PATH)hps = true;
						if (neight[i] != nullptr && neight[i]->status == TS_PATH)hpt = true;
					}
					if (hps && hpt)break;


					if (closest_point == nullptr)
					{
						for (int i = 0; i < 8; i++)
						{
							if (neight[i] == nullptr || neight[i]->status != TS_USED)continue;
							if (closest_point == nullptr)closest_point = neight[i];
							if (closest_point->start_dist + closest_point->target_dist >= neight[i]->start_dist + neight[i]->target_dist)
							{
								if (closest_point->start_dist + closest_point->target_dist > neight[i]->start_dist + neight[i]->target_dist)closest_point = neight[i];
								else if (neight[i]->target_dist < closest_point->target_dist)closest_point = neight[i];
							}
						}
						closest_point->status = TS_PATH;
						printvec.push_back(sf::Vector2f((float)(closest_point->coord.x) / 2, (float)(T->size.y - closest_point->coord.y) / 2));
					}
					else
					{
						auto old_cl = closest_point;
						auto neighC = T->GetNeighbors(closest_point->coord.x, closest_point->coord.y);
						closest_point = nullptr;
						for (int i = 0; i < 8; i++)
						{
							if (neighC[i] == nullptr || neighC[i]->status != TS_USED)continue;
							if (closest_point == nullptr)closest_point = neighC[i];
							if (closest_point->start_dist + closest_point->target_dist >= neighC[i]->start_dist + neighC[i]->target_dist)
							{
								//if (closest_point->start_dist + closest_point->target_dist > neighC[i]->start_dist + neighC[i]->target_dist)closest_point = neighC[i];
								//else
								if (neighC[i]->start_dist < closest_point->start_dist)closest_point = neighC[i];
							}
						}
						if (closest_point == nullptr)
							closest_point = old_cl;
						closest_point->status = TS_PATH;
						printvec.push_back(sf::Vector2f((float)(closest_point->coord.x)/2, (float)(T->size.y-closest_point->coord.y)/2));

						delete[] neighC;
					}
					delete[] neighs;
					delete[] neight;








				}
			}
			//printf("\nPath already found");
			//printf("\nNodes: %d", nodes);
			return true;

		}



	}





	return false;
}


inline bool heap_smaller(tile_t* a, tile_t* b)
{
	return a->start_dist + a->target_dist < b->start_dist + b->target_dist || (a->start_dist + a->target_dist == b->start_dist + b->target_dist && a->target_dist < b->target_dist);
}

inline void heap_swap(std::vector<tile_t*> &v, int a, int b)
{
	auto A = v[a];
	auto B = v[b];
	v[a] = B;
	v[b] = A;
}

inline void heap_comp_from_high(std::vector<tile_t*> &v, int ind);

inline void heap_comp_from_low(std::vector<tile_t*> &v, int ind)
{
	if (ind == 0)
	{
		heap_comp_from_high(v, 0);
		return;
	}
	if (heap_smaller(v[ind], v[(ind - 1) / 2]))
	{
		heap_swap(v, ind, (ind - 1) / 2);
		heap_comp_from_low(v, (ind - 1) / 2);
	}
}

inline void heap_add(std::vector<tile_t*> &v, tile_t* e)
{
	int size = v.size();
	v.push_back(e);
	heap_comp_from_low(v, size);
}

inline void heap_comp_from_high(std::vector<tile_t*> &v, int ind)
{
	if (ind >= v.size())return;
	bool good = true;
	for (int i = ind * 2 + 1; i <= ind * 2 + 2; i++)
	{
		if (i >= v.size())break;
		if (heap_smaller(v[i], v[ind]))
		{
			good = false;
		}
	}
	if (!good)
	{
		if (heap_smaller(v[ind * 2 + 1], v[ind * 2 + 2]))
		{
			heap_swap(v, ind * 2 + 1, ind);
			heap_comp_from_high(v, ind * 2 + 1);
		}
		else
		{
			heap_swap(v, ind * 2 + 2, ind);
			heap_comp_from_high(v, ind * 2 + 2);
		}
	}

	return;
	for (int i = ind * 2 + 1; i <= ind * 2 + 2; i++)
	{
		if (i >= v.size())break;
		if (v[ind]->start_dist + v[ind]->target_dist > v[i]->target_dist + v[i]->start_dist)
		{
			heap_swap(v, ind, i);
			heap_comp_from_high(v, i);
		}
	}

	return;




}

inline void heap_remove(std::vector<tile_t*> &v)
{
	int size = v.size();
	auto B = v[size - 1];
	v[0] = B;
	v.pop_back();

	heap_comp_from_high(v, 0);
	//printf("\n%d", size);
}


bool AStar::FindPathSTDS(tilemap_t* T)
{
	//std::vector<tile_t*> Used;
	std::vector<tile_t*> Ready;


	int nodes = 0;

	tile_t* SP = nullptr;
	tile_t* TP = nullptr;
	bool is_started = false;

	for (int i = 0; i < T->size.x; i++)
	{
		for (int j = 0; j < T->size.y; j++)
		{
			if (T->Tiles[i][j].status == TS_START)SP = &T->Tiles[i][j];
			else if (T->Tiles[i][j].status == TS_TARGET)TP = &T->Tiles[i][j];
			else if (T->Tiles[i][j].status == TS_READY || T->Tiles[i][j].status == TS_USED)is_started = true;
		}
	}

	if (SP == nullptr || TP == nullptr)
	{
		printf("\nNo start or target point found");
		return true;
	}
	if (!is_started)
	{
		auto neigh = T->GetNeighbors(SP->coord.x, SP->coord.y);

		SP->start_dist = 0;
		SP->target_dist = GetDist(SP->coord.x, SP->coord.y, TP->coord.x, TP->coord.y);
		for (int i = 0; i < 8; i++)
		{
			if (neigh[i] == nullptr)continue;
			neigh[i]->status = TS_READY;
			neigh[i]->start_dist = GetDist(SP->coord.x, SP->coord.y, neigh[i]->coord.x, neigh[i]->coord.y);
			neigh[i]->target_dist = GetDist(neigh[i]->coord.x, neigh[i]->coord.y, TP->coord.x, TP->coord.y);

			heap_add(Ready, neigh[i]);
		}


		delete[] neigh;
	}


	while (true)
	{
		if (GetAsyncKeyState(VK_F6) & 1)
		{
			g_Window->clear();
			T->Draw(50, 50, 640);
			g_Window->display();
		}
		bool hasready = false;


		for (auto it : Ready)
		{
			hasready = true;
			break;
		}

		if (!hasready)

		{
			printf("\nThere is no path between the start and the target");
			return true;

		}
		//std::sort(Ready.begin(), Ready.end(), tile_comp);
		tile_t* lowest_value = Ready[0];

		//printf("\n%d | %d is the lowest value with %d");

		if (lowest_value != nullptr)
		{
			lowest_value->status = TS_USED;
			//Used.push_back(lowest_value);
			nodes++;
			heap_remove(Ready);

			auto neigh = T->GetNeighbors(lowest_value->coord.x, lowest_value->coord.y);

			for (int i = 0; i < 8; i++)
			{
				if (neigh[i] == nullptr)continue;
				if (neigh[i]->status == TS_START)continue;
				if (neigh[i]->status == TS_USED)
				{
					if (neigh[i]->start_dist > lowest_value->start_dist)
					{
						neigh[i]->start_dist = min(neigh[i]->start_dist, lowest_value->start_dist + GetDist(lowest_value->coord.x, lowest_value->coord.y, neigh[i]->coord.x, neigh[i]->coord.y));
						neigh[i]->target_dist = GetDist(neigh[i]->coord.x, neigh[i]->coord.y, TP->coord.x, TP->coord.y);
					}
					continue;
				}
				if (neigh[i]->status == TS_TARGET)
				{
					neigh[i]->start_dist = min(neigh[i]->start_dist, lowest_value->start_dist + GetDist(lowest_value->coord.x, lowest_value->coord.y, neigh[i]->coord.x, neigh[i]->coord.y));
					continue;
				}
				neigh[i]->start_dist = min(neigh[i]->start_dist, lowest_value->start_dist + GetDist(lowest_value->coord.x, lowest_value->coord.y, neigh[i]->coord.x, neigh[i]->coord.y));
				neigh[i]->target_dist = GetDist(neigh[i]->coord.x, neigh[i]->coord.y, TP->coord.x, TP->coord.y);
				if (neigh[i]->status != TS_READY)
				{
					neigh[i]->status = TS_READY;

					heap_add(Ready, neigh[i]);
				}
				//Ready.push_back(neigh[i]);
			}
			delete[] neigh;
		}

		if (TP->start_dist != INT_MAX / 2)
		{
			{
				tile_t* closest_point = nullptr;
				while (true)
				{
					if (GetAsyncKeyState(VK_F6) & 1)
					{
						g_Window->clear();
						T->Draw(50, 50, 640);
						g_Window->display();
					}
					auto neighs = T->GetNeighbors(SP->coord.x, SP->coord.y);
					auto neight = T->GetNeighbors(TP->coord.x, TP->coord.y);
					bool hps = false, hpt = false;


					for (int i = 0; i < 8; i++)
					{
						if (neighs[i] != nullptr && neighs[i]->status == TS_PATH)hps = true;
						if (neight[i] != nullptr && neight[i]->status == TS_PATH)hpt = true;
					}
					if (hps && hpt)break;


					if (closest_point == nullptr)
					{
						for (int i = 0; i < 8; i++)
						{
							if (neight[i] == nullptr || neight[i]->status != TS_USED)continue;
							if (closest_point == nullptr)closest_point = neight[i];
							if (closest_point->start_dist + closest_point->target_dist >= neight[i]->start_dist + neight[i]->target_dist)
							{
								if (closest_point->start_dist + closest_point->target_dist > neight[i]->start_dist + neight[i]->target_dist)closest_point = neight[i];
								else if (neight[i]->target_dist < closest_point->target_dist)closest_point = neight[i];
							}
						}
						closest_point->status = TS_PATH;
					}
					else
					{
						auto old_cl = closest_point;
						auto neighC = T->GetNeighbors(closest_point->coord.x, closest_point->coord.y);
						closest_point = nullptr;
						for (int i = 0; i < 8; i++)
						{
							if (neighC[i] == nullptr || neighC[i]->status != TS_USED)continue;
							if (closest_point == nullptr)closest_point = neighC[i];
							if (closest_point->start_dist + closest_point->target_dist >= neighC[i]->start_dist + neighC[i]->target_dist)
							{
								//if (closest_point->start_dist + closest_point->target_dist > neighC[i]->start_dist + neighC[i]->target_dist)closest_point = neighC[i];
								//else
								if (neighC[i]->start_dist < closest_point->start_dist)closest_point = neighC[i];
							}
						}
						if (closest_point == nullptr)
							closest_point = old_cl;
						closest_point->status = TS_PATH;

						delete[] neighC;
					}
					delete[] neighs;
					delete[] neight;








				}
			}
			printf("\nPath already found");
			//printf("\nNodes: %d\nUsed: %d\nReady: %d", nodes,Used.size(),Ready.size());
			return true;

		}



	}





	return false;
}