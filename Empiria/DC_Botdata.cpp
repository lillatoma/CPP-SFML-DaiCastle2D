#include "DaiCastle.h"

tilemap_t TMap;
sf::Vector2i TMap_Start;
sf::Vector2i TMap_Size;



void dc_match::CreateMovementMap()
{
	TMap.Setup(map.size.x * 2+1, map.size.y * 2+1);
	//Checking for walls as they are solid and can't be walked through
	for (int _x = 0; _x < map.size.x; _x++)
	{
		for (int _y = 0; _y < map.size.y; _y++)
		{
			if (map.lines[_y].blocks[_x].walls[0].iHealth > 0)
			{
				TMap.Tiles[_x * 2][TMap.size.y-_y * 2].status = TS_UNWALKABLE;
				TMap.Tiles[_x * 2][TMap.size.y-(_y * 2+1)].status = TS_UNWALKABLE;
				TMap.Tiles[_x * 2][TMap.size.y-(_y * 2+2)].status = TS_UNWALKABLE;
			}
			if (map.lines[_y].blocks[_x].walls[1].iHealth > 0)
			{
				TMap.Tiles[_x * 2][TMap.size.y-_y * 2].status = TS_UNWALKABLE;
				TMap.Tiles[_x * 2+1][TMap.size.y - _y *2].status = TS_UNWALKABLE;
				TMap.Tiles[_x * 2+2][TMap.size.y - _y *2].status = TS_UNWALKABLE;
			}
		}
	}


}

void dc_match::CreateSmallMovementMap(sf::Vector2i vMid, sf::Vector2i siz, sf::Vector2i vTar)
{
	TMap_Start = vMid - siz / 2;
	TMap_Size = siz;
	TMap.Setup(siz.x*2+2, siz.y*2+2);

	TMap.Tiles[siz.x+1 ][siz.y+1].status = TS_START;
	
	auto tarcor = vTar - vMid + siz/2;
	auto darcor = vTar - vMid;
	if (tarcor.x >= 0 && tarcor.x < siz.x && tarcor.y >= 0 && tarcor.y < siz.y)
	{
		int tx = (siz.x / 2 + darcor.x) * 2 + 1;
		int ty = (siz.y / 2 - darcor.y) * 2 + 1;
		TMap.Tiles[tx][ty].status = TS_TARGET;

	}
	for (int _x = 1; _x < siz.x-1; _x++)
	{
		for (int _y = 1; _y < siz.y-1; _y++)
		{
			auto ex = vMid.x + _x - siz.x / 2;
			auto ey = vMid.y + _y - siz.y / 2;
			if (ex < 0 || ex >= map.size.x || ey < 0 || ey >= map.size.y)
			{
				if (ex < 0 || ex >= map.size.x)
				{
					TMap.Tiles[_x * 2][TMap.size.y - _y * 2].status = TS_UNWALKABLE;
					TMap.Tiles[_x * 2][TMap.size.y - (_y * 2 + 1)].status = TS_UNWALKABLE;
					TMap.Tiles[_x * 2][TMap.size.y - (_y * 2 + 2)].status = TS_UNWALKABLE;
					TMap.Tiles[_x * 2][TMap.size.y - (_y * 2 + 3)].status = TS_UNWALKABLE;
					TMap.Tiles[_x * 2][TMap.size.y - (_y * 2 + 4)].status = TS_UNWALKABLE;
				}
				if (ey < 0 || ey  >= map.size.y)
				{
					TMap.Tiles[_x * 2][TMap.size.y - _y * 2].status = TS_UNWALKABLE;
					TMap.Tiles[_x * 2 + 1][TMap.size.y - _y * 2].status = TS_UNWALKABLE;
					TMap.Tiles[_x * 2 + 2][TMap.size.y - _y * 2].status = TS_UNWALKABLE;
					TMap.Tiles[_x * 2 + 3][TMap.size.y - _y * 2].status = TS_UNWALKABLE;
				}
			}
			else
			{
				if (map.lines[ey].blocks[ex].walls[0].iHealth > 0)
				{
					TMap.Tiles[_x * 2][TMap.size.y - _y * 2].status = TS_UNWALKABLE;
					TMap.Tiles[_x * 2][TMap.size.y - (_y * 2 + 1)].status = TS_UNWALKABLE;
					TMap.Tiles[_x * 2][TMap.size.y - (_y * 2 + 2)].status = TS_UNWALKABLE;
					if (_y == siz.y - 1)
					{
						TMap.Tiles[_x * 2][TMap.size.y - (_y * 2 + 3)].status = TS_UNWALKABLE;
						TMap.Tiles[_x * 2][TMap.size.y - (_y * 2 + 4)].status = TS_UNWALKABLE;
					}
				}
				if (map.lines[ey].blocks[ex].walls[1].iHealth > 0)
				{
					TMap.Tiles[_x * 2][TMap.size.y - _y * 2].status = TS_UNWALKABLE;
					TMap.Tiles[_x * 2 + 1][TMap.size.y - _y * 2].status = TS_UNWALKABLE;
					TMap.Tiles[_x * 2 + 2][TMap.size.y - _y * 2].status = TS_UNWALKABLE;
					if(_x == siz.x - 1)
						TMap.Tiles[_x * 2 + 3][TMap.size.y - _y * 2].status = TS_UNWALKABLE;
				}
			}
		}
	}

	//printf("\nOriginal: %d %d\nRecalculated: %d %d", vTar.x, vTar.y, darcor + TMap_Start + TMap_Size / 2);

}





//void dc_match::BotMoveToPoint(int id)
//{
//
//	//if (BotData[id].move_path.size() <= 0)
//	//{
//	//	return;
//	//}
//	//auto next_point = BotData[id].move_path[BotData[id].move_path.size() - 1];
//	//auto diff = players[id].vPosition - next_point;
//	//auto angle = 180+vec2angle(diff.x, -diff.y);
//	//PlayerMove(id, angle);
//	//auto distance = GetDistance(diff, sf::Vector2f());
//	//if (distance < 0.3)BotData[id].move_path.pop_back();
//	//else if (distance > 5)
//	//{
//	//	BotData[id].move_path.clear();
//	//	BotData[id].chest_id = -1;
//	//	BotData[id].has_somewhere_to_move = false;
//	//}
//	//auto trace = map.trace_ray(players[id].vPosition, next_point);
//	//if (trace.hit_object)//PlayerShootWeapon(id);
//	//	BotData[id].move_path.clear();
//}



int dc_match::GetClosestChestIDToPlayer(int player)
{
	int chest_id = -1;
	float chest_distance = 0.f;
	for (int i = 0; i < map.chests.size(); i++)
	{
		auto chest = map.chests[i];
		if (chest.bOpen)continue;
		auto dist = GetDistance(players[player].vPosition, chest.vPosition);
		if (chest_id == -1)
		{
			chest_id = i;
			chest_distance = dist;
		}
		else if (dist < chest_distance)
		{
			chest_id = i;
			chest_distance = dist;
		}
	}
	return chest_id;
}

//void dc_match::BotShouldCalculatePath(int player)
//{
//	if (BotData[player].has_somewhere_to_move == 2)
//	{
//		sf::Vector2i vTar = sf::Vector2i(map.chests[BotData[player].chest_id].vPosition.x, map.chests[BotData[player].chest_id].vPosition.y);
//		sf::Vector2i vMid = sf::Vector2i(players[player].vPosition.x, players[player].vPosition.y);
//		auto dif = vTar - vMid;
//		auto dist = sqrt(dif.x*dif.x + dif.y*dif.y);
//		if (dif.x >= -4 && dif.x <= 4 && dif.y >= -4 && dif.y <= 4)
//		{
//			CreateSmallMovementMap(vMid, sf::Vector2i(18, 18), vTar);
//			std::vector<sf::Vector2f> path;
//			AStar::FindPathSTD(&TMap, path);
//			
//			for (int i = 0; i < path.size(); i++)
//			{
//				BotData[player].move_path.push_back(sf::Vector2f(path[i].x + TMap_Start.x, path[i].y + TMap_Start.y));
//			}
//		}
//		else
//		{
//			auto vPos = (5 * vTar + (int)(dist - 5) * vMid)/(int)dist;
//
//
//			CreateSmallMovementMap(vMid, sf::Vector2i(12, 12), vPos);
//			std::vector<sf::Vector2f> path;
//			AStar::FindPathSTD(&TMap, path);
//
//			for (int i = 0; i < path.size(); i++)
//			{
//				BotData[player].move_path.push_back(sf::Vector2f(path[i].x + TMap_Start.x, path[i].y + TMap_Start.y));
//			}
//			BotData[player].has_somewhere_to_move = false;
//			
//		}
//
//		if (BotData[player].move_path.size() == 0)
//			BotData[player].move_path.push_back(sf::Vector2f(vTar.x,vTar.y));
//	}
//
//
//}

//void dc_match::BotSeekChest(int id)
//{
//	int chest_id = -1;
//	float chest_distance = 0.f;
//	for (int i = 0; i < map.chests.size(); i++)
//	{
//		auto chest = map.chests[i];
//		if (chest.bOpen)continue;
//		auto dist = GetDistance(players[id].vPosition, chest.vPosition);
//		if (chest_id == -1)
//		{
//			chest_id = i;
//			chest_distance = dist;
//		}
//		else if (dist < chest_distance)
//		{
//			chest_id = i;
//			chest_distance = dist;
//		}
//	}
//	if (chest_id != -1)
//	{
//			BotData[id].has_somewhere_to_move = 2;
//			BotData[id].chest_id = chest_id;
//			BotShouldCalculatePath(id);
//
//	}
//
//}



//void dc_match::BotGetUsefulWeapon(int id)
//{
//		if (id < 0 || id > 99)return;
//		float current_effectiveness = 0;
//		auto distance = GetDistance(players[id].vPosition, players[BotData[id].target_id].vPosition);
//		if (BotData[id].target_id == -1)distance = 1;
//
//
//		if (players[id].Items[players[id].iSelectedWeapon].bValidated)
//		{
//			current_effectiveness = players[id].Items[players[id].iSelectedWeapon].GetPrimitiveDPS(distance);
//		}
//		float g_ef = current_effectiveness;
//		int g_id = 0;
//		for (int i = 0; i < 5; i++)
//		{
//			if (!players[id].Items[i].bValidated)continue;
//			float effectiveness = players[id].Items[i].GetPrimitiveDPS(distance);
//			if (effectiveness > current_effectiveness)
//			{
//				//PlayerSwapWeapon(id, i);
//				g_id = i;
//				current_effectiveness = effectiveness;
//			}
//		}
//		if (current_effectiveness > g_ef + 5.f)
//		{
//			PlayerSwapWeapon(id, g_id);
//		}
//
//
//}


/*
void dc_match::BotAttack(int id)
{
	if (id < 0 || id > 99)return;
	if (BotData[id].target_id == -1)return;
	if (players[id].Items[players[id].iSelectedWeapon].iType > 3)BotGetUsefulWeapon(id);
	auto distto = -(players[BotData[id].target_id].vPosition - players[id].vPosition);
	auto needed_angle = vec2angle(distto.x, -distto.y);

	float angle_dif = anglediff(players[id].fAngle, needed_angle);

	float good_angle_diff = max(atan(0.25 / GetDistance(distto, sf::Vector2f())) * 180 / PI,BotData[id].fAimCorrectness);

	if (abs(angle_dif) <= abs(good_angle_diff))
	{

			PlayerShootWeapon(id);
	}

}
*/
//bool dc_match::BotReload(int id)
//{
//	for (int i = 0; i < 5; i++)
//	{
//		if (players[id].Items[i].bValidated && !players[id].Items[i].iType > 3 && players[id].Items[i].iBullets < players[id].Items[i].iMaxBullets)
//		{
//			PlayerSwapWeapon(id, i);
//			PlayerReloadWeapon(id);
//			return true;
//		}
//	}
//	return false;
//}

//bool dc_match::BotHeal(int id)
//{
//	if(players[id].iHealth + players[id].iShield < 200 && players[id].fReloadDelay <= 0.f)
//	for (int i = 0; i < 5; i++)
//	{
//		if (!players[id].Items[i].bValidated)continue;
//
//		if (players[id].iHealth < 75 && players[id].Items[i].id == 1000)
//		{
//			PlayerSwapWeapon(id,i);
//			PlayerShootWeapon(id);
//			return true;
//		}
//		if (players[id].iHealth < 100 && players[id].Items[i].id == 1001)
//		{
//			PlayerSwapWeapon(id,i);
//			PlayerShootWeapon(id);
//			return true;
//		}
//		if (players[id].iShield < 50 && players[id].Items[i].id == 1004)
//		{
//			PlayerSwapWeapon(id,i);
//			PlayerShootWeapon(id);
//			return true;
//		}
//		if (players[id].iHealth + players[id].iShield < 150 && players[id].Items[i].id == 1002)
//		{
//			PlayerSwapWeapon(id,i);
//			PlayerShootWeapon(id);
//			return true;
//		}
//		if (players[id].iShield < 100 && players[id].Items[i].id == 1003)
//		{
//			PlayerSwapWeapon(id,i);
//			PlayerShootWeapon(id);
//			return true;
//		}
//		if (players[id].iHealth + players[id].iShield < 150 && players[id].Items[i].id == 1005)
//		{
//			PlayerSwapWeapon(id,i);
//			PlayerShootWeapon(id);
//			return true;
//		}
//	}
//	return false;
//
//}

//void dc_match::BotDodge(int id,int diff)
//{
//	if (id < 0 || id > 99)return;
//	if (BotData[id].dodge_time_left <= 0.f)
//	{
//		BotData[id].dodge_dir++;
//		BotData[id].dodge_time_left = 0.15f + RandFloat()*0.25f;
//	}
//	else
//	{
//		if (BotData[id].dodge_dir % 2 == 1)
//		{
//
//		}
//		else
//		{
//			int L = (BotData[id].dodge_dir / 2) % 2;
//			float nangle = players[id].fAngle - 90.f;
//			if (L == 0)
//			{
//				nangle += 180.f;
//			}
//			PlayerMove(id, nangle);
//
//		}
//		BotData[id].dodge_time_left -= (float)(diff) / 1000;
//	}
//
//	
//}
/*
void dc_match::BotThink(int id, int diff)
{
	if (BotData[id].target_id != -1)
	{
		if (players[BotData[id].target_id].iHealth <= 0 || map.trace_ray(players[id].vPosition, players[BotData[id].target_id].vPosition).hit_object)BotData[id].target_id = -1;
		else
		{
			bool pulledout = players[id].Items[players[id].iSelectedWeapon].bValidated && players[id].Items[players[id].iSelectedWeapon].iType <= 3;
			BotGetUsefulWeapon(id);
			auto distto = -(players[BotData[id].target_id].vPosition - players[id].vPosition);
			auto needed_angle = vec2angle(distto.x, -distto.y);
			BotCorrectAngle(id, needed_angle, diff);
			if (!pulledout || players[id].fPulloutDelay > 0.f)
				BotDodge(id,diff);
			else
			{
				if (players[id].Items[players[id].iSelectedWeapon].fBloomMovingMinSize > 0.f || !BotData[id].uses_fsa)
				{
					BotDodge(id, diff);
					BotAttack(id);
				}
				else
				{
					float hipfireDPS = players[id].Items[players[id].iSelectedWeapon].GetRealDPS(GetDistance(players[id].vPosition, players[BotData[id].target_id].vPosition), false);
					float fsaDPS = players[id].Items[players[id].iSelectedWeapon].GetRealDPS(GetDistance(players[id].vPosition, players[BotData[id].target_id].vPosition), true);
					//printf("\n%d - %.2f %.2f", id,hipfireDPS, fsaDPS);
					if (fsaDPS < hipfireDPS)
					{
						if (id == camera_follows)ConLog("\nHipfire%.1f > %.1f", hipfireDPS, fsaDPS);
						BotDodge(id,diff);
						BotAttack(id);
					}
					else
					{
						if (BotData[id].is_currently_waiting_for_fsa)
						{

							if (players[id].fShootDelay > 0.01f)
							{
								BotData[id].is_currently_waiting_for_fsa = false;

							}
							if (players[id].fFSADelay <= 0.f)
							{
								BotAttack(id);
								BotData[id].is_currently_waiting_for_fsa = false;
							}
						}
						else
						{

							if (BotData[id].dodge_time_left <= 0.f)BotData[id].is_currently_waiting_for_fsa = true;
							else BotDodge(id, diff);
							
						}
					}
				}
			}
		}
	}
	else


	

	//if (BotData[id].target_id != -1)
	//{
	//	if (players[BotData[id].target_id].iHealth <= 0 || map.trace_ray(players[id].vPosition,players[BotData[id].target_id].vPosition).hit_object)BotData[id].target_id = -1;
	//	else
	//	{
	//		BotCorrectAngle(id, diff);
	//		BotGetUsefulWeapon(id);
	//		BotAttack(id);
	//	}
	//}
	//else
	{
		if(players[id].hasWeapon())
			for (int i = 0; i < 100; i++)
			{
				if (i == id || players[i].iHealth <= 0)continue;
				if (GetDistance(players[id].vPosition, players[i].vPosition) > 30.f)continue;
				if (!map.trace_ray(players[id].vPosition, players[i].vPosition).hit_object)
				{
					BotData[id].target_id = i;
					break;
				}
			}
		if (BotData[id].target_id == -1)
		{
			if (players[id].fHealTime > 0.f)return;

			if (BotHeal(id))return;


			if (BotData[id].move_path.size() > 0)
			{

				auto distto = BotData[id].move_path[BotData[id].move_path.size() - 1] - players[id].vPosition;
				auto needed_angle = 180 + vec2angle(distto.x, -distto.y);
				BotCorrectAngle(id, needed_angle, diff);
				BotMoveToPoint(id);
				BotPickupNearbyLoot(id);
			}
			if (players[id].fReloadDelay > 0.f)return;
			if (BotReload(id))return;
			BotGetUsefulWeapon(id);

			if (BotData[id].move_path.size() <= 0)
			{
				if (BotData[id].chest_id == -1)
					BotSeekChest(id);
				else
				{
					if (GetDistance(players[id].vPosition, map.chests[BotData[id].chest_id].vPosition) < 1.2f)
					{
						PlayerOpenChest(id, BotData[id].chest_id);
						if (map.chests[BotData[id].chest_id].bOpen)BotData[id].chest_id = -1;
					}
					else
						BotSeekChest(id);
				}
			}



		}
	}

	
}
*/

//NEWLY WRITTEN AI

void dc_match::BotCalculatePath(int player, sf::Vector2f Target)
{
	//For performance saving, limitations to pathfinding is applied
	//Pathfinding is only used with a 250ms delay since the last call
	if (BotData[player].Changables.PathFindClock.deltaTime() < 250)
		return;
	BotData[player].Changables.PathFindClock.Update();
	BotData[player].move_path.clear();
	sf::Vector2i vTar = sf::Vector2i(Target.x,Target.y);
	sf::Vector2i vMid = sf::Vector2i(players[player].vPosition.x, players[player].vPosition.y);
	auto dif = vTar - vMid;
	auto dist = sqrt(dif.x*dif.x + dif.y*dif.y);
	{
		int Size = 30;

		if (Size >= 32)
		{
			//BotData[player].move_path.push_back(sf::Vector2f(vTar));
		}
		//auto vPos = ((Size/2-1) * vTar + (int)(dist - (Size / 2 - 1)) * vMid) / (int)dist;
		auto vPos = vMid + (Size / 2 - 3)*(vTar - vMid) / (int)(dist+1);
		if (dif.x <= Size / 2 - 2 && dif.x >= -Size / 2 + 2 && dif.y <= Size / 2 - 2 && dif.y >= -Size / 2 + 2)
			vPos = vTar;
		if (vMid == vPos)
		{
			BotData[player].move_path.clear();
			BotData[player].move_path.push_back(Target);
			return;
		}
		//Saves it to TMap
		CreateSmallMovementMap(vMid, sf::Vector2i(Size, Size), vPos);
		std::vector<sf::Vector2f> path;
		AStar::FindPathSTD(&TMap, path);

		if (path.size() > 0)
		{
			for (int i = 0; i < path.size(); i++)
			{
				BotData[player].move_path.push_back(sf::Vector2f(path[i].x + TMap_Start.x, path[i].y + TMap_Start.y));
			}
		}
		else Size += 12;
	}
}

void dc_match::BotMoveToNextPoint(int id, float difftime)
{
	//We can't move closer
	if (BotData[id].move_path.size() <= 0)
	{
			return;
	}

	//Calculating the movement angle and moving towards it
	auto next_point = BotData[id].move_path[BotData[id].move_path.size() - 1];
	auto diff = players[id].vPosition - next_point;
	auto angle = 180 + vec2angle(diff.x, -diff.y);
	PlayerMove(id, angle);

	//Rotating the bot towards the next move point
	BotCorrectAngleNew(id, difftime, angle, BotData[id].fAimSpeedCasual, BotData[id].fAimCorrectnessCasual);

	//Removing the points of the move path that are reached
	auto distance = GetDistance(diff, sf::Vector2f());
	if (distance < 0.3)BotData[id].move_path.pop_back();
	else if (distance > 5)
	{
		BotData[id].move_path.clear();
	}
	auto trace = map.trace_ray(players[id].vPosition, next_point);
	if (trace.hit_object)//PlayerShootWeapon(id);
		BotData[id].move_path.clear();
}

bool whitehealcomp(int a, int b) {
	//printf("\nin: (%d,%d)", a, b);
	//if (a == 14)return false;
	//if (b != 14 && a == 13)return false;
	//if (b != 14 && b != 13 && g_Items[a].IsHeal())return false;

	return a == 14 || (b != 13 && a == 13) 
		|| (b != 14 && b != 13 && a == 18)
		|| (b != 14 && b != 13 && b != 18 && a == 17)
		|| (b != 14 && b != 13 && b != 18 && b != 17 && g_Items[a].IsHeal())
		|| (b!= 14 && b!= 13 && b != 18 && b != 17 &&  !g_Items[b].IsHeal() && a < b);
}

bool shieldhealcomp(int a, int b) {
	//printf("\nin: (%d,%d)", a, b);
	//if (a == 14)return false;
	//if (b != 14 && a == 13)return false;
	//if (b != 14 && b != 13 && g_Items[a].IsHeal())return false;

	return a == 16 || (b != 16 && a == 15)
		|| (b != 16 && b != 15 && a == 18)
		|| (b != 16 && b != 15 && b != 18 && a == 17)
		|| (b != 16 && b != 15 && b != 18 && b != 17 && g_Items[a].IsHeal())
		|| (b != 16 && b != 15 && b != 18 && b != 17 && !g_Items[b].IsHeal() && a < b);
}


bool powerhealcomp(int a, int b) {
	//printf("\nin: (%d,%d)", a, b);
	//if (a == 14)return false;
	//if (b != 14 && a == 13)return false;
	//if (b != 14 && b != 13 && g_Items[a].IsHeal())return false;

	return a == 18 || (b != 18 && a == 17)
		|| (b != 18 && b != 17 && a == 16)
		|| (b != 18 && b != 16 && b != 17 && a == 15)
		|| (b != 18 && b != 16 && b != 17 && b != 15 && g_Items[a].IsHeal())
		|| (b != 16 && b != 15 && b != 18 && b != 17 && !g_Items[b].IsHeal() && a < b);
}



struct intfloatpair
{
	int i;
	float f;
	intfloatpair() {};
	intfloatpair(int I, float F) { i = I; f = F; }
};

bool dmgcomp(intfloatpair a, intfloatpair b)
{
	//printf("\nC: (%d,%d)", a.i, b.i);
	return a.f >= b.f;
}

float dc_match::GetBotModifiedDistance(sf::Vector2f a, sf::Vector2f b)
{
	auto DiffVec = b - a;
	auto diffX = abs(DiffVec.x);
	auto diffY = abs(DiffVec.y);
	float VerticalMultiplicator = (1.f*g_Resolution.x) / g_Resolution.y;
	diffY *= VerticalMultiplicator;
	return 1.f * max(diffX, diffY);

	DiffVec.y *= VerticalMultiplicator;
	return GetLength(DiffVec);
}

void dc_match::BotBegin(int easyCase, int normalCase, int hardCase, int expertCase)
{
	int totalCases = easyCase + normalCase + hardCase + expertCase;

	//Generating Difficulties

	for (int id = 1; id < 100; id++)
	{
		for (int i = 0; i < map.chests.size(); i++)
		{ if(!map.chests[i].bOpen)
			{ 
				BotData[id].Changables.RestOfChests.push_back(i);
			}
		}
	}

	for (int id = 1; id < 100; id++)
	{
		auto r = Random(1, totalCases);
		if (r <= easyCase)BotData[id].botDifficulty = 0;
		else if (r <= easyCase + normalCase)BotData[id].botDifficulty = 1;
		else if (r <= easyCase + normalCase + hardCase)BotData[id].botDifficulty = 2;
		else BotData[id].botDifficulty = 3;
	}
	//Generating BusData
	for (int id = 1; id < 100; id++)
	{

		float BusTime = GetDistance(BusEndPosition, BusStartPosition) / BUS_TRAVELSPEED;
		//Non-linear distrbution, bots tend to jump more early than late
		float ModifTime = pow(BusTime, 0.75f);
		BotData[id].JumpoffTime = pow(g_RandomDevice.RandomFloat(0, ModifTime),1.f/0.75f);
		//Non-linear distrbution, bots tend to jump close than far
		float ModifRadius = pow(1000, 0.5f);
		BotData[id].JumpoffDist = pow(g_RandomDevice.RandomFloat(18, ModifRadius), 1.f / 0.5f);

		//Finding suitable chest to land to
		auto GoodChests = GetAvailableChests(BusStartPosition + BotData[id].JumpoffTime*BUS_TRAVELSPEED*ToUnitVector(BusEndPosition - BusStartPosition), BotData[id].JumpoffDist);
		GoodChests.push_back(GetClosestChestToPosition(BusStartPosition + BotData[id].JumpoffTime*BUS_TRAVELSPEED*ToUnitVector(BusEndPosition - BusStartPosition)));
		float jumpprecisities[] = { 20.f,12.f,6.f,3.f };
		float precRadius = pow((g_RandomDevice.RandomFloat(0,pow(jumpprecisities[BotData[id].botDifficulty],3))),0.333f);
		float precAngle = g_RandomDevice.RandomFloat(0, 360.f);
		auto ChestID = GoodChests[Random(0, GoodChests.size() - 1)];
		BotData[id].JumpToPosition = map.chests[ChestID].vPosition + angle2vec(precAngle)*precRadius;

		float descendprecisities[] = { 2.f,0.8f,0.3f,0.1f };

		BotData[id].DescendSpeedInMind = g_RandomDevice.RandomFloat(6.f - descendprecisities[BotData[id].botDifficulty], 6.f + descendprecisities[BotData[id].botDifficulty]);
	}
	//Improving BusData
	//This one is a result of calculation from Maple for the best possible jump time for landing as fast as possible
	for (int id = 1; id < 100; id++)
	{
		auto A = BusStartPosition;
		auto U = ToUnitVector(BusEndPosition - BusStartPosition)*BUS_TRAVELSPEED;
		auto L = BotData[id].JumpToPosition;
		double s = UNIT_FREEFALL_SPEED;
		auto D = A - L;


		double Disc = s*s*(U.x*U.x + U.y*U.y - s*s)*(D.x*U.y - D.y*U.x)*(D.x*U.y-D.y*U.x);
		double m1Szam = (D.x*U.x*U.x*U.x) + (D.x*U.x*U.y*U.y) + (D.y*U.x*U.x*U.y) + (D.y*U.y*U.y*U.y) - (D.x*U.x*s*s) - (D.y*U.y*s*s) - sqrt(Disc);
		double m2Szam = (D.x*U.x*U.x*U.x) + (D.x*U.x*U.y*U.y) + (D.y*U.x*U.x*U.y) + (D.y*U.y*U.y*U.y) - (D.x*U.x*s*s) - (D.y*U.y*s*s) + sqrt(Disc);
		double mNev = (U.x*U.x*U.x*U.x) + 2 * (U.x*U.x*U.y*U.y) + (U.y*U.y*U.y*U.y) - (U.x*U.x) - (U.y*U.y);
		
		float CorrectedJumpTime = BotData[id].JumpoffTime;
		float minimalFloatTime = BUS_HEIGHT / (UNIT_NATURAL_DESCEND + UNIT_FORCE_DESCEND);
		float minimalFloatTimeFloatDistance = minimalFloatTime * UNIT_FREEFALL_SPEED;

		float OrtoY = (-U.y*A.x + U.x*A.y + U.y*(U.x*L.x + U.y*L.y) / U.x) / (U.y*U.y / U.x + U.x);
		float OrtoX = (U.x*L.x + U.y*L.y - U.y*OrtoY) / U.x;
		sf::Vector2f OrtoPoint(OrtoX, OrtoY);
		float OrtoJumpTime;
		if (U.x != 0)
			OrtoJumpTime = (OrtoX - A.x) / U.x;
		else
			OrtoJumpTime = (OrtoY - A.y) / U.y;


		if (GetDistance(OrtoPoint, L) < minimalFloatTimeFloatDistance)
		{
			float mL = minimalFloatTimeFloatDistance;
			float oL = GetDistance(OrtoPoint, L);
			float cL = sqrt(mL*mL - oL*oL);

			CorrectedJumpTime = OrtoJumpTime - cL / BUS_TRAVELSPEED;

			//ConLog("\n%d |  %.3f ", id, CorrectedJumpTime);

		}
		else
		{

			auto F = [=](float t)
			{
				return t + sqrt(U.x*U.x*t*t + U.y*U.y*t*t + 2 * D.x*U.x*t + 2 * D.y*U.y*t + A.x*A.x - 2 * A.x*L.x + A.y*A.y - 2 * A.y*L.y + L.x*L.x + L.y*L.y) / s;
			};

			if (mNev != 0.f && Disc >= 0.f)
			{
				if (F(-m1Szam / mNev) < F(-m2Szam / mNev))CorrectedJumpTime = -m1Szam / mNev;
				else CorrectedJumpTime = -m2Szam / mNev;
			}
		}

		if (CorrectedJumpTime < 0.f)CorrectedJumpTime = 0.f;
		float BotCorrMins[] = { 0.f,0.33f,0.7f,0.95f };
		float BotCorrMaxs[] = { 0.1f,0.5f,0.95f,1.f };
		float BotCorrection = 0.001f*Random(BotCorrMins[BotData[id].botDifficulty] * 1000, BotCorrMaxs[BotData[id].botDifficulty] * 1000);

		BotData[id].JumpoffTime = (1.f - BotCorrection)*BotData[id].JumpoffTime + (BotCorrection)*CorrectedJumpTime;
	}
	//GeneratingStormFearLevels
	for(int id = 1; id<100; id++)
	{
		if (BotData[id].botDifficulty == 0)
		{
			int r = Random(1, 10000);
			if (r < 5000)BotData[id].BotZoneFearLevel = 0;
			else if (r < 6750)BotData[id].BotZoneFearLevel = 1;
			else if (r < 8000)BotData[id].BotZoneFearLevel = 2;
			else if (r < 9250)BotData[id].BotZoneFearLevel = 3;
			else BotData[id].BotZoneFearLevel = 4;
		}
		else if (BotData[id].botDifficulty == 1)
		{
			int r = Random(1, 10000);
			if (r < 2500)BotData[id].BotZoneFearLevel = 0;
			else if (r < 5000)BotData[id].BotZoneFearLevel = 1;
			else if (r < 7500)BotData[id].BotZoneFearLevel = 2;
			else if (r < 8750)BotData[id].BotZoneFearLevel = 3;
			else BotData[id].BotZoneFearLevel = 4;
		}
		else if (BotData[id].botDifficulty == 2)
		{
			int r = Random(1, 10000);
			if (r < 2000)BotData[id].BotZoneFearLevel = 1;
			else if (r < 6500)BotData[id].BotZoneFearLevel = 2;
			else if (r < 8250)BotData[id].BotZoneFearLevel = 3;
			else BotData[id].BotZoneFearLevel = 4;
		}
		else
		{
			int r = Random(1, 10000);
			if (r < 5000)BotData[id].BotZoneFearLevel = 2;
			else if (r < 8000)BotData[id].BotZoneFearLevel = 3;
			else BotData[id].BotZoneFearLevel = 4;
		}
	}



	//Generating BotReactiontime
	for (int id = 1; id < 100; id++)
	{
		float reacMins[] = { 0.7f,0.5f,0.35f,0.2f };
		float reacMaxs[] = { 1.f,0.75f,0.5f,0.33f };
		BotData[id].fReactionTime = 0.001f*Random(reacMins[BotData[id].botDifficulty]*1000, reacMaxs[BotData[id].botDifficulty]*1000);
		float thinkMins[] = { 0.5f,0.4f,0.35f,0.2f };
		float thinkMaxs[] = { 1.5f,1.0f,0.8f,0.325f };
		BotData[id].fBotThinkDelay = 0.001f*Random(thinkMins[BotData[id].botDifficulty] * 1000,thinkMaxs[BotData[id].botDifficulty] * 1000);
		float noticeMins[] = { 0.8f,0.7f,0.5f,0.3f };
		float noticeMaxs[] = { 1.6f,1.1f,1.f,0.6f };
		BotData[id].fEnemyNoticeTime= 0.001f*Random(noticeMins[BotData[id].botDifficulty] * 1000, noticeMaxs[BotData[id].botDifficulty] * 1000);
	}

	//Generating WeaponPreferences
	{
		for (int id = 1; id < 100; id++)
		{
			//Weapon 1 Data
			{
				float Weapon1Percs[] = { 62.f,82.f,97.f,100.f };
				float Weapon1RangeMins[] = { 0.5f,1.f,2.5f,25.f };
				float Weapon1RangeMaxs[] = { 2.5f,3.f,5.f,40.f };

				int Weapon1Index = 0;
				float r = 0.01f*Random(1, 10000);
				if (r <= Weapon1Percs[0])Weapon1Index = 0;
				else if (r <= Weapon1Percs[1])Weapon1Index = 1;
				else if (r <= Weapon1Percs[2])Weapon1Index = 2;
				else Weapon1Index = 3;

				float Weapon1Range = 0.0001f*Random(10000 * Weapon1RangeMins[Weapon1Index], 10000 * Weapon1RangeMaxs[Weapon1Index]);

				std::vector<intfloatpair> WeaponData;

				bool Standing = true;
				if (Random(1, 10000) < 9500)Standing = false;
				

				for (int j = 0; j < g_Items.size(); j++)
				{
					WeaponData.push_back(intfloatpair(j, g_Items[j].CalculateDPS(Weapon1Range, Standing)));
				}
				std::sort(WeaponData.begin(), WeaponData.end(), dmgcomp);
				for (int j = 0; j < WeaponData.size(); j++)BotData[id].WeaponPreferences[0].push_back(WeaponData[j].i);
				BotData[id].FightType[0] = Standing;

				float Weapon1SpeedMins[] = {500.f,400.f,350.f,280.f};
				float Weapon1SpeedMaxs[] = { 600.f,500.f,450.f,350.f };
				float DiffMultMins[] = { 0.05f,0.15f,0.3f,0.65f };
				float DiffMultMaxs[] = { 0.15f,0.25f,0.55f,1.f };
				
				float CorrDiffMins[] = { 5.5f,3.5f,2.f,1.f };
				float CorrDiffMaxs[] = { 10.f,6.f,4.f,2.5f };

				BotData[id].fAimSpeed[0] = g_RandomDevice.RandomFloat(Weapon1SpeedMins[Weapon1Index], Weapon1SpeedMaxs[Weapon1Index])*g_RandomDevice.RandomFloat(DiffMultMins[BotData[id].botDifficulty], DiffMultMaxs[BotData[id].botDifficulty]);
				BotData[id].fAimCorrectness[0] = g_RandomDevice.RandomFloat(CorrDiffMins[BotData[id].botDifficulty], CorrDiffMaxs[BotData[id].botDifficulty]);
				
				float Weapon1PrecMins[] = { 0.f,0.1f,0.15f,0.4f };
				float Weapon1PrecMaxs[] = { 0.5f,0.6f,0.65f,1.f };
				float DuffMultMins[] = { 0.0f,0.0f,0.05f,0.1f };
				float DuffMultMaxs[] = { 0.25f,0.35f,0.65f,1.f };

				BotData[id].fAimPrecision[0] = g_RandomDevice.RandomFloat(Weapon1PrecMins[Weapon1Index], Weapon1PrecMaxs[Weapon1Index])*g_RandomDevice.RandomFloat(DuffMultMins[BotData[id].botDifficulty], DuffMultMaxs[BotData[id].botDifficulty]);

			}

			//Weapon 2 Data
			{
				float Weapon2Percs[] = { 62.f,82.f,97.f,100.f };
				float Weapon2RangeMins[] = { 2.5f,3.f,5.f,25.f };
				float Weapon2RangeMaxs[] = { 5.f,7.f,10.f,40.f };

				int Weapon2Index = 0;
				float r = 0.01f*Random(1, 10000);
				if (r <= Weapon2Percs[0])Weapon2Index = 0;
				else if (r <= Weapon2Percs[1])Weapon2Index = 1;
				else if (r <= Weapon2Percs[2])Weapon2Index = 2;
				else Weapon2Index = 3;

				float Weapon2Range = 0.0001f*Random(10000 * Weapon2RangeMins[Weapon2Index], 10000 * Weapon2RangeMaxs[Weapon2Index]);

				std::vector<intfloatpair> WeaponData;

				bool Standing = true;
				if (Random(1, 10000) < 7500)Standing = false;


				for (int j = 0; j < g_Items.size(); j++)
				{
					WeaponData.push_back(intfloatpair(j, g_Items[j].CalculateDPS(Weapon2Range, Standing)));
				}
				std::sort(WeaponData.begin(), WeaponData.end(), dmgcomp);
				for (int j = 0; j < WeaponData.size(); j++)BotData[id].WeaponPreferences[1].push_back(WeaponData[j].i);
				BotData[id].FightType[1] = Standing;
				float Weapon2SpeedMins[] = { 360.f,330.f,300.f,260.f };
				float Weapon2SpeedMaxs[] = { 450.f,425.f,400.f,350.f };
				float DiffMultMins[] = { 0.05f,0.15f,0.3f,0.65f };
				float DiffMultMaxs[] = { 0.15f,0.25f,0.55f,1.f };

				float CorrDiffMins[] = { 5.5f,3.5f,2.f,1.f };
				float CorrDiffMaxs[] = { 10.f,6.f,4.f,2.5f };

				BotData[id].fAimSpeed[1] = g_RandomDevice.RandomFloat(Weapon2SpeedMins[Weapon2Index], Weapon2SpeedMaxs[Weapon2Index])*g_RandomDevice.RandomFloat(DiffMultMins[BotData[id].botDifficulty], DiffMultMaxs[BotData[id].botDifficulty]);
				BotData[id].fAimCorrectness[1] = g_RandomDevice.RandomFloat(CorrDiffMins[BotData[id].botDifficulty], CorrDiffMaxs[BotData[id].botDifficulty]);
			
				float Weapon2PrecMins[] = { 0.1f,0.15f,0.2f,0.5f };
				float Weapon2PrecMaxs[] = { 0.6f,0.7f,0.75f,1.f };
				float DuffMultMins[] = { 0.0f,0.0f,0.05f,0.1f };
				float DuffMultMaxs[] = { 0.25f,0.35f,0.65f,1.f };

				BotData[id].fAimPrecision[1] = g_RandomDevice.RandomFloat(Weapon2PrecMins[Weapon2Index], Weapon2PrecMaxs[Weapon2Index])*g_RandomDevice.RandomFloat(DuffMultMins[BotData[id].botDifficulty], DuffMultMaxs[BotData[id].botDifficulty]);

			}

			//Weapon 3 Data
			{
				if (Random(1, 10000) < 9500)
				{
					float Weapon3Percs[] = { 62.f,90.f,97.f,100.f };
					float Weapon3RangeMins[] = { 20.f,30.f,45.f,10.f };
					float Weapon3RangeMaxs[] = { 40.f,50.f,60.f,20.f };

					int Weapon3Index = 0;
					float r = 0.01f*Random(1, 10000);
					if (r <= Weapon3Percs[0])Weapon3Index = 0;
					else if (r <= Weapon3Percs[1])Weapon3Index = 1;
					else if (r <= Weapon3Percs[2])Weapon3Index = 2;
					else Weapon3Index = 3;

					float Weapon3Range = 0.0001f*Random(10000 * Weapon3RangeMins[Weapon3Index], 10000 * Weapon3RangeMaxs[Weapon3Index]);

					std::vector<intfloatpair> WeaponData;

					bool Standing = true;
					if (Random(1, 10000) < 2000)Standing = false;


					for (int j = 0; j < g_Items.size(); j++)
					{
						WeaponData.push_back(intfloatpair(j, g_Items[j].CalculateDPS(Weapon3Range, Standing)));
					}
					std::sort(WeaponData.begin(), WeaponData.end(), dmgcomp);
					for (int j = 0; j < WeaponData.size(); j++)BotData[id].WeaponPreferences[2].push_back(WeaponData[j].i);
					BotData[id].FightType[2] = Standing;
					float Weapon3SpeedMins[] = { 280.f,250.f,175.f,325.f };
					float Weapon3SpeedMaxs[] = { 350.f,325.f,250.f,450.f };
					float DiffMultMins[] = { 0.05f,0.15f,0.3f,0.65f };
					float DiffMultMaxs[] = { 0.15f,0.25f,0.55f,1.f };

					float CorrDiffMins[] = { 5.5f,3.5f,2.f,1.f };
					float CorrDiffMaxs[] = { 10.f,6.f,4.f,2.5f };

					BotData[id].fAimSpeed[2] = g_RandomDevice.RandomFloat(Weapon3SpeedMins[Weapon3Index], Weapon3SpeedMaxs[Weapon3Index])*g_RandomDevice.RandomFloat(DiffMultMins[BotData[id].botDifficulty], DiffMultMaxs[BotData[id].botDifficulty]);
					BotData[id].fAimCorrectness[2] = g_RandomDevice.RandomFloat(CorrDiffMins[BotData[id].botDifficulty], CorrDiffMaxs[BotData[id].botDifficulty]);


					float Weapon3PrecMins[] = { 0.3f,0.5f,0.7f,0.8f };
					float Weapon3PrecMaxs[] = { 0.8f,1.f,1.f,1.f };
					float DuffMultMins[] = { 0.0f,0.0f,0.05f,0.1f };
					float DuffMultMaxs[] = { 0.25f,0.35f,0.65f,1.f };

					BotData[id].fAimPrecision[2] = g_RandomDevice.RandomFloat(Weapon3PrecMins[Weapon3Index], Weapon3PrecMaxs[Weapon3Index])*g_RandomDevice.RandomFloat(DuffMultMins[BotData[id].botDifficulty], DuffMultMaxs[BotData[id].botDifficulty]);

				}
				else
				{
					float HealPercentages[] = { 50.f,60.f,100.f };
					int Weapon3Index = 0;
					float r = 0.01f*Random(1, 10000);
					if (r <= HealPercentages[0])Weapon3Index = 0;
					else if (r <= HealPercentages[1])Weapon3Index = 1;
					else Weapon3Index = 2;

					std::vector<int> IndexList;
					for (int j = 0; j < g_Items.size(); j++)
					{
						IndexList.push_back(j);
					}
					if (Weapon3Index == 0)std::sort(IndexList.begin(), IndexList.end(), whitehealcomp);
					if (Weapon3Index == 1)std::sort(IndexList.begin(), IndexList.end(), shieldhealcomp);
					if (Weapon3Index == 2)std::sort(IndexList.begin(), IndexList.end(), powerhealcomp);
					for (int j = 0; j < IndexList.size(); j++)BotData[id].WeaponPreferences[2].push_back(IndexList[j]);
					BotData[id].FightType[2] = 2;
				}
			}
			//Weapon 4 Data
			{
			if (Random(1, 10000) < 2000) //Sniper Type
			{


				float Weapon4Range = 0.0001f*Random(10000 * 50.f, 10000 * 70.f);

				std::vector<intfloatpair> WeaponData;

				bool Standing = true;
				if (Random(1, 10000) < 500)Standing = false;


				for (int j = 0; j < g_Items.size(); j++)
				{
					WeaponData.push_back(intfloatpair(j, g_Items[j].CalculateDPS(Weapon4Range, Standing)));
				}
				std::sort(WeaponData.begin(), WeaponData.end(), dmgcomp);
				for (int j = 0; j < WeaponData.size(); j++)BotData[id].WeaponPreferences[3].push_back(WeaponData[j].i);
				BotData[id].FightType[3] = Standing;

				float Weapon4SpeedMin = 225.f;
				float Weapon4SpeedMax = 450.f;
				float DiffMultMins[] = { 0.05f,0.15f,0.3f,0.65f };
				float DiffMultMaxs[] = { 0.15f,0.25f,0.55f,1.f };

				float CorrDiffMins[] = { 5.5f,3.5f,2.f,1.f };
				float CorrDiffMaxs[] = { 10.f,6.f,4.f,2.5f };

				BotData[id].fAimSpeed[3] = g_RandomDevice.RandomFloat(Weapon4SpeedMin, Weapon4SpeedMax)*g_RandomDevice.RandomFloat(DiffMultMins[BotData[id].botDifficulty], DiffMultMaxs[BotData[id].botDifficulty]);
				BotData[id].fAimCorrectness[3] = g_RandomDevice.RandomFloat(CorrDiffMins[BotData[id].botDifficulty], CorrDiffMaxs[BotData[id].botDifficulty]);

				float Weapon4PrecMin = 0.8f;
				float Weapon4PrecMax = 1.f;
				float DuffMultMins[] = { 0.4f,0.6f,0.7f,0.8f };
				float DuffMultMaxs[] = { 1.f,1.f,1.f,1.f };

				BotData[id].fAimPrecision[3] = g_RandomDevice.RandomFloat(Weapon4PrecMin, Weapon4PrecMax)*g_RandomDevice.RandomFloat(DuffMultMins[BotData[id].botDifficulty], DuffMultMaxs[BotData[id].botDifficulty]);

			}
			else
			{
				float HealPercentages[] = { 30.f,60.f,100.f };
				int Weapon4Index = 0;
				float r = 0.01f*Random(1, 10000);
				if (r <= HealPercentages[0])Weapon4Index = 0;
				else if (r <= HealPercentages[1])Weapon4Index = 1;
				else Weapon4Index = 2;

				std::vector<int> IndexList;
				for (int j = 0; j < g_Items.size(); j++)
				{
					IndexList.push_back(j);
				}
				if (Weapon4Index == 0)std::sort(IndexList.begin(), IndexList.end(), whitehealcomp);
				if (Weapon4Index == 1)std::sort(IndexList.begin(), IndexList.end(), shieldhealcomp);
				if (Weapon4Index == 2)std::sort(IndexList.begin(), IndexList.end(), powerhealcomp);
				for (int j = 0; j < IndexList.size(); j++)BotData[id].WeaponPreferences[3].push_back(IndexList[j]);
				BotData[id].FightType[3] = 2;
			}
			}
			//Weapon 5 Data
			{
				float HealPercentages[] = { 10.f,80.f,100.f };
				int Weapon5Index = 0;
				float r = 0.01f*Random(1, 10000);
				if (r <= HealPercentages[0])Weapon5Index = 0;
				else if (r <= HealPercentages[1])Weapon5Index = 1;
				else Weapon5Index = 2;

				std::vector<int> IndexList;
				for (int j = 0; j < g_Items.size(); j++)
				{
					IndexList.push_back(j);
				}
				if (Weapon5Index == 0)std::sort(IndexList.begin(), IndexList.end(), whitehealcomp);
				if (Weapon5Index == 1)std::sort(IndexList.begin(), IndexList.end(), shieldhealcomp);
				if (Weapon5Index == 2)std::sort(IndexList.begin(), IndexList.end(), powerhealcomp);
				for (int j = 0; j < IndexList.size(); j++)BotData[id].WeaponPreferences[4].push_back(IndexList[j]);
				BotData[id].FightType[4] = 2;
			}

		}
	}
	//Bot How Good Weapon Ranking
	{
		for (int i = 1; i < 100; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				//Non-linear distribution, preferring better ranked items
				//3 is so they don't ever chase the best item of a type, top 4 is enough for them
				int Ranking = pow(g_RandomDevice.RandomFloat( pow(3,0.667f), pow(g_Items.size(), 0.667f) ),1.5f);
				BotData[i].GoodEnoughRanking[j] = Ranking;
			}
			BotData[i].SuckerForExtraHeals = Random(1, 10000) > 8000;
		}
	}



	//Bot HealUsages
	for(int i = 1; i < 100; i++)
	{
		//BANDAGES
		BotData[i].HealUseMinimums[0] = 0;
		int r = Random(1, 10000); 
		if (r <= 8500)BotData[i].HealUseMaximums[0] = 74;
		else 		BotData[i].HealUseMaximums[0] = 61;
		
		//MEDKIT

		r = Random(1, 10000);
		if (r <= 9500)BotData[i].HealUseMinimums[1] = 0;
		else BotData[i].HealUseMinimums[1] = 30;
		BotData[i].HealUseMaximums[1] = 100;

		//SMALL SHIELD
		BotData[i].HealUseMinimums[2] = 0;
		BotData[i].HealUseMaximums[2] = 50;

		//BIG SHIELD
		r = Random(1, 10000);
		if (r <= 5000)BotData[i].HealUseMinimums[3] = 50;
		else if (r <= 9000)BotData[i].HealUseMinimums[3] = 0;
		else BotData[i].HealUseMinimums[3] = 25;
		r = Random(1, 10000);
		if (r <= 7500)BotData[i].HealUseMaximums[3] = 100;
		else BotData[i].HealUseMaximums[3] = 75;

		//SLURP
		r = Random(1, 10000);
		if (r <= 6000)BotData[i].HealUseMinimums[4] = 0;
		else BotData[i].HealUseMinimums[4] = 75;
		r = Random(1, 10000);
		if (r <= 7500)BotData[i].HealUseMaximums[4] = 150;
		else BotData[i].HealUseMaximums[4] = 200;

		//CHUGJUG
		r = Random(1, 10000);
		BotData[i].HealUseMinimums[5] = 0;
		if (r <= 7500)BotData[i].HealUseMaximums[5] = 150;
		else if ( r <= 9500)BotData[i].HealUseMaximums[5] = 100;
		else BotData[i].HealUseMaximums[5] = 200;
	}


	//Bot Minimum Health To Raid
	for (int i = 1; i < 100; i++)
	{
		int r = Random(1, 10000);
		if (r < 5000)BotData[i].MinimumHealthToRaid = 200;
		else if (r < 7000)BotData[i].MinimumHealthToRaid = 150;
		else if (r < 9000)BotData[i].MinimumHealthToRaid = 125;
		else BotData[i].MinimumHealthToRaid = 100;
	}

	//Bot Chest And Player Ranges
	for (int i = 1; i < 100; i++)
	{
		float chestMins[] = { 3.f,5.f,8.f,15.f };
		float chestMaxs[] = { 10.5f,13.f,15.f,20.f };
		BotData[i].fChestRange = 0.001f*Random(chestMins[BotData[i].botDifficulty] * 1000, chestMaxs[BotData[i].botDifficulty] * 1000);
		float playerMins[] = { 40.f,42.5f,45.f,48.f };
		float playerMaxs[] = { 48.f,49.f,50.f,51.f };
		BotData[i].fPlayerRange = 0.001f*Random(playerMins[BotData[i].botDifficulty] * 1000, playerMaxs[BotData[i].botDifficulty] * 1000);
		float itemMins[] = { 8.f,10.f,12.f,15.f };
		float itemMaxs[] = { 12.5f,14.f,17.f,20.f };
		BotData[i].fItemRange = 0.001f*Random(chestMins[BotData[i].botDifficulty] * 1000, chestMaxs[BotData[i].botDifficulty] * 1000);
	}

	//Just In Case WeaponDistance
	for(int i = 1; i < 100; i++)
	{
		BotData[i].JustInCaseWeaponDistance = pow(g_RandomDevice.RandomFloat(pow(BotData[i].fPlayerRange*0.5f,2),pow(BotData[i].fPlayerRange,2)),0.5f );
	}

	//Casual aimspeed && aimpenalty && correctness
	for (int i = 1; i < 100; i++)
	{
		float aimMins[] = { 115.f,150.f,180.f,300.f };
		float aimMaxs[] = { 150.f,210.f,300.f,450.f };
		BotData[i].fAimSpeedCasual = 0.001f*Random(aimMins[BotData[i].botDifficulty] * 1000, aimMaxs[BotData[i].botDifficulty] * 1000);
		float penaMins[] = { 0.05f,0.15f,0.25f,0.55f };
		float penaMaxs[] = { 0.25f,0.3f,0.5f,0.7f };
		BotData[i].fAimCorrectSpeedPenalty = 0.001f*Random(penaMins[BotData[i].botDifficulty] * 1000, penaMaxs[BotData[i].botDifficulty] * 1000);
		float corMins[] = { 3.f,2.f,1.5f,1.f };
		float corMaxs[] = { 10.f,5.f,3.f,2.f };
		BotData[i].fAimCorrectnessCasual = 0.001f*Random(corMins[BotData[i].botDifficulty] * 1000, corMaxs[BotData[i].botDifficulty] * 1000);
	}

	//Bot Fightstyle
	for (int i = 1; i < 100; i++)
	{
		if (BotData[i].botDifficulty == 0)
		{
			float percs[] = { 60.f,70.f };
			float r = g_RandomDevice.RandomFloat(0.f, 100.f);
			if (r < percs[0])BotData[i].FightStyleInFight = 0;
			else if (r < percs[1])BotData[i].FightStyleInFight = 1;
			else BotData[i].FightStyleInFight = 2;
		}
		else if (BotData[i].botDifficulty == 1)
		{
			float percs[] = { 50.f,75.f };
			float r = g_RandomDevice.RandomFloat(0.f, 100.f);
			if (r < percs[0])BotData[i].FightStyleInFight = 0;
			else if (r < percs[1])BotData[i].FightStyleInFight = 1;
			else BotData[i].FightStyleInFight = 2;
		}
		else if (BotData[i].botDifficulty == 2)
		{
			float percs[] = { 40.f,75.f };
			float r = g_RandomDevice.RandomFloat(0.f, 100.f);
			if (r < percs[0])BotData[i].FightStyleInFight = 0;
			else if (r < percs[1])BotData[i].FightStyleInFight = 1;
			else BotData[i].FightStyleInFight = 2;
		}
		else
		{
			float percs[] = { 25.f,90.f };
			float r = g_RandomDevice.RandomFloat(0.f, 100.f);
			if (r < percs[0])BotData[i].FightStyleInFight = 0;
			else if (r < percs[1])BotData[i].FightStyleInFight = 1;
			else BotData[i].FightStyleInFight = 2;
		}
	}
	//In and off-Fight Healths
	for(int i = 1; i < 100; i++)
	{
		if (BotData[i].botDifficulty == 0)
		{
			int bailHealthMin = 60;
			int bailHealthMax = 300;
			int bailHealthMinIF = 50;
			int bailHealthMaxIF = 150;
			int rushHealthMin = 150;
			int rushHealthMax = 200;
			BotData[i].BailHealthMaxOF = Random(bailHealthMin, bailHealthMax);
			BotData[i].BailHealthMaxIF = Random(bailHealthMinIF, bailHealthMaxIF);
			BotData[i].RushHealthMinOF = Random(rushHealthMin, rushHealthMax);
		}
		else if (BotData[i].botDifficulty == 1)
		{
			int bailHealthMin = 60;
			int bailHealthMax = 275;
			int bailHealthMinIF = 40;
			int bailHealthMaxIF = 130;
			int rushHealthMin = 110;
			int rushHealthMax = 190;
			BotData[i].BailHealthMaxOF = Random(bailHealthMin, bailHealthMax);
			BotData[i].BailHealthMaxIF = Random(bailHealthMinIF, bailHealthMaxIF);
			BotData[i].RushHealthMinOF = Random(rushHealthMin, rushHealthMax);
		}
		else if (BotData[i].botDifficulty == 2)
		{
			int bailHealthMin = 50;
			int bailHealthMax = 200;
			int bailHealthMinIF = 35;
			int bailHealthMaxIF = 100;
			int rushHealthMin = 90;
			int rushHealthMax = 175;
			BotData[i].BailHealthMaxOF = Random(bailHealthMin, bailHealthMax);
			BotData[i].BailHealthMaxIF = Random(bailHealthMinIF, bailHealthMaxIF);
			BotData[i].RushHealthMinOF = Random(rushHealthMin, rushHealthMax);
		}
		else
		{
			int bailHealthMin = 30;
			int bailHealthMax = 125;
			int bailHealthMinIF = 35;
			int bailHealthMaxIF = 75;
			int rushHealthMin = 75;
			int rushHealthMax = 150;
			BotData[i].BailHealthMaxOF = Random(bailHealthMin, bailHealthMax);
			BotData[i].BailHealthMaxIF = Random(bailHealthMinIF, bailHealthMaxIF);
			BotData[i].RushHealthMinOF = Random(rushHealthMin, rushHealthMax);
		}

	}

	//SideStepTimes + StillstayTimes
	for(int i = 1; i < 100; i++)
	{
		float ssmin = g_RandomDevice.RandomFloat(0.3f, 0.7f);
		float ssmax = ssmin + g_RandomDevice.RandomFloat(0.5f, 1.f);
		float sssmin = g_RandomDevice.RandomFloat(0.6f, 1.2f);
		float sssmax = sssmin + g_RandomDevice.RandomFloat(0.5f, 1.f);

		BotData[i].SideStepMinTime = ssmin;
		BotData[i].SideStepMaxTime = ssmax;
		BotData[i].StillStayMinTime = sssmin;
		BotData[i].StillStayMaxTime = sssmax;
	}

	//BotInaccuracy
	for(int i = 1; i < 100; i++)
	{
		float inaMins[] = { 6.f,3.f,1.5f,0.25f };
		float inaMaxs[] = { 8.f,5.f,2.5f,0.75f };
		BotData[i].InaccuracyMax = 0.001f*Random(inaMins[BotData[i].botDifficulty] * 1000, inaMaxs[BotData[i].botDifficulty] * 1000);
	}

	//BotMemoryKill
	for (int i = 1; i < 100; i++)
	{
		float memkMins[] = { 0.45f,0.4f,0.35f,0.2f };
		float memkMaxs[] = { 0.75f,0.5f,0.45f,0.3f };
		BotData[i].BotMemoryAfterDie = 0.001f*Random(memkMins[BotData[i].botDifficulty] * 1000, memkMaxs[BotData[i].botDifficulty] * 1000);

		float memvMins[] = { 0.2f,0.25f,0.3f,0.4f };
		float memvMaxs[] = { 0.35f,0.4f,0.5f,0.65f };
		BotData[i].BotMemoryAfterVanish = 0.001f*Random(memvMins[BotData[i].botDifficulty] * 1000, memvMaxs[BotData[i].botDifficulty] * 1000);
	}


	//BotAirdrop Stuff
	for(int i = 1; i < 100; i++)
	{
		if (BotData[i].botDifficulty == 0)
		{
			BotData[i].fAirDropInterestDistance = g_RandomDevice.RandomFloat(5.f, 45.f);
			BotData[i].fAirDropGuardMaxRange = g_RandomDevice.RandomFloat(5.f, BotData[i].fAirDropInterestDistance);
			BotData[i].fAirDropGuardMinModifier = g_RandomDevice.RandomFloat(0.f, 0.6f);
		}
		else if (BotData[i].botDifficulty == 1)
		{
			BotData[i].fAirDropInterestDistance = g_RandomDevice.RandomFloat(8.f, 80.f);
			BotData[i].fAirDropGuardMaxRange = g_RandomDevice.RandomFloat(7.f, BotData[i].fAirDropInterestDistance);
			BotData[i].fAirDropGuardMinModifier = g_RandomDevice.RandomFloat(0.1f, 0.5f);
		}
		else if (BotData[i].botDifficulty == 2)
		{
			BotData[i].fAirDropInterestDistance = g_RandomDevice.RandomFloat(50.f, 100.f);
			BotData[i].fAirDropGuardMaxRange = g_RandomDevice.RandomFloat(35.f, 50.f);
			BotData[i].fAirDropGuardMinModifier = g_RandomDevice.RandomFloat(0.2f, 0.5f);
		}
		else if (BotData[i].botDifficulty == 3)
		{
			BotData[i].fAirDropInterestDistance = g_RandomDevice.RandomFloat(75.f, 200.f);
			BotData[i].fAirDropGuardMaxRange = g_RandomDevice.RandomFloat(30.f,60.f);
			BotData[i].fAirDropGuardMinModifier = g_RandomDevice.RandomFloat(0.3f, 0.4f);
		}
	}


	//Generating Skins
	//Idea:
	//Low and medium difficulty bots are more likely to wear the default skins
	//Hard difficulty bots are randomly wearing skins
	//Expert bots are more likely to wear default skins to get the user offguards
	for (int i = 1; i < 100; i++)
	{
		if (BotData[i].botDifficulty == 0)
		{
			if (Random(0, 10000) < 6000)
				players[i].iSkinTexture = 0;
			else
				players[i].iSkinTexture = Random(0, ALL_SKINTEXTURES - 1);

			if (Random(0, 10000) < 6000)
				players[i].iGliderTexture = 0;
			else
				players[i].iGliderTexture= Random(0, ALL_GLIDERTEXTURES - 1);

			if (Random(0, 10000) < 6000)
				players[i].iWeaponWrapTexture = 0;
			else
				players[i].iWeaponWrapTexture = Random(0, ALL_WEAPONWRAPTEXTURES - 1);

		}
		if (BotData[i].botDifficulty == 1)
		{
			if (Random(0, 10000) < 3000)
				players[i].iSkinTexture = 0;
			else
				players[i].iSkinTexture = Random(0, ALL_SKINTEXTURES - 1);

			if (Random(0, 10000) < 3000)
				players[i].iGliderTexture = 0;
			else
				players[i].iGliderTexture = Random(0, ALL_GLIDERTEXTURES - 1);

			if (Random(0, 10000) < 3000)
				players[i].iWeaponWrapTexture = 0;
			else
				players[i].iWeaponWrapTexture = Random(0, ALL_WEAPONWRAPTEXTURES - 1);

		}
		if (BotData[i].botDifficulty >= 3)
		{
			if (Random(0, 10000) < 3000)
				players[i].iSkinTexture = 0;
			else
				players[i].iSkinTexture = Random(0, ALL_SKINTEXTURES - 1);

			players[i].iGliderTexture = Random(0, ALL_GLIDERTEXTURES - 1);

			players[i].iWeaponWrapTexture = Random(0, ALL_WEAPONWRAPTEXTURES - 1);

		}
		if (BotData[i].botDifficulty == 2)
		{
			players[i].iSkinTexture = Random(0, ALL_SKINTEXTURES - 1);

			players[i].iGliderTexture = Random(0, ALL_GLIDERTEXTURES - 1);

			players[i].iWeaponWrapTexture = Random(0, ALL_WEAPONWRAPTEXTURES - 1);
		}
	}

	//BotBegin() Bottom
	//TODO: Generateotherstuff

	//Bot Names
	BotGiveNames();

	return;

	for (int i = 1; i < 10; i++)
	{
		//ConLog("\n#%d | %.2f | %.2f %.2f", i, BotData[i].JumpoffTime, BotData[i].JumpToPosition.x, BotData[i].JumpToPosition.y);
		ConLog("\n%d | %s | %s | %s | %s | %s", i,
			g_Items[BotData[i].WeaponPreferences[0][0]].szName,
			g_Items[BotData[i].WeaponPreferences[1][0]].szName,
			g_Items[BotData[i].WeaponPreferences[2][0]].szName,
			g_Items[BotData[i].WeaponPreferences[3][0]].szName,
			g_Items[BotData[i].WeaponPreferences[4][0]].szName);

	}

	for (int i = 1; i < 10; i++)
	{
		ConLog("\n%d Mini: %d-%d | Big: %d-%d | Slurp: %d-%d | Chug: %d-%d | Bandage: %d-%d | Medkit: %d-%d",
			i, BotData[i].HealUseMinimums[2], BotData[i].HealUseMaximums[2],
			BotData[i].HealUseMinimums[3], BotData[i].HealUseMaximums[3],
			BotData[i].HealUseMinimums[4], BotData[i].HealUseMaximums[4],
			BotData[i].HealUseMinimums[5], BotData[i].HealUseMaximums[5],
			BotData[i].HealUseMinimums[0], BotData[i].HealUseMaximums[0],
			BotData[i].HealUseMinimums[1], BotData[i].HealUseMaximums[1]
		
		);
	}
	ConLog("\nEasy: ");
	for (int i = 1; i < 100; i++)
	{
		if (BotData[i].botDifficulty == 0)printf(" %d", i);
	}
	ConLog("\nMedium: ");
	for (int i = 1; i < 100; i++)
	{
		if (BotData[i].botDifficulty == 1)printf(" %d", i);
	}
	ConLog("\nHard: ");
	for (int i = 1; i < 100; i++)
	{
		if (BotData[i].botDifficulty == 2)printf(" %d", i);
	}
	ConLog("\nPro: ");
	for (int i = 1; i < 100; i++)
	{
		if (BotData[i].botDifficulty == 3)printf(" %d", i);
	}



}
//////////////////////////////////////////////
/// Returns an array of indexes of the elements of 'V' sorted in an ascending order
/// TODO: Optimize
//////////////////////////////////////////////
std::vector<int> id_list(std::vector<int> V)
{
	std::vector<int> Indexes;

	while (V.size() != 0)
	{
		int smallestidx = 0;
		for (int i = 0; i < V.size(); i++)
		{
			if (V[i] < V[smallestidx])smallestidx = i;
		}
		Indexes.push_back(smallestidx);
		V.erase(V.begin() + smallestidx);
	}


return Indexes;
}

void dc_match::BotSortInventory(int id)
{
	BotData[id].Changables.SortInventoryClock.Update();

	int takenSlots = 0;
	for (int j = 0; j < 5; j++)if (players[id].Items[j].bValidated)takenSlots++;

	for (int i = 0; i < takenSlots; i++)
	{
		if (!players[id].Items[i].bValidated)continue;
		std::vector<int> Ranks;

		for (int It = 0; It < takenSlots; It++)Ranks.push_back(GetIndex(BotData[id].WeaponPreferences[It], players[id].Items[i].ListIndex));
		//Sorting the indexes in an ascending order
		auto IndexList = id_list(Ranks);

		for (int j = 0; j < IndexList.size(); j++)
		{
			if (IndexList[j] == i) break;
			//Sorting prefers items in the first few slots
			if (!players[id].Items[IndexList[j]].bValidated)
			{
				PlayerSwapWeaponInventory(id, i, IndexList[j]);
				i = -1;
				break;
			}
			else
			{
				if (players[id].Items[i].ListIndex == players[id].Items[IndexList[j]].ListIndex
					&& players[id].Items[IndexList[j]].IsConsumable() && players[id].Items[IndexList[j]].iBullets < players[id].Items[IndexList[j]].iMaxBullets)
				{
					PlayerSwapWeaponInventory(id, i, IndexList[j]);
					i = -1;
					break;
				}
				if (GetIndex(BotData[id].WeaponPreferences[IndexList[j]], players[id].Items[i].ListIndex) < GetIndex(BotData[id].WeaponPreferences[IndexList[j]], players[id].Items[IndexList[j]].ListIndex))
				{
					PlayerSwapWeaponInventory(id, i, IndexList[j]);
					i = -1;
					break;
				}
			}
		}


	}
}

float dc_match::BotFindBestBailAngle(int id)
{
	std::vector<float> BadAngles;
	//Adding players
	for (int i = 0; i < BotData[id].Changables.NoticedPlayerIDs.size(); i++)
	{
		int ID = BotData[id].Changables.NoticedPlayerIDs[i];
		auto DiffVec = players[ID].vPosition - players[id].vPosition;
		float Angle = vec2angle(DiffVec.x, -DiffVec.y);
		BadAngles.push_back(Angle);
	}
	//Adding the storm if it's close to the bot
	if (GetDistance(players[id].vPosition, GetCurrentStormMiddle()) > (0.5f*GetCurrentStormDiameter() - 50.f))
	{
		auto DiffVec = players[id].vPosition - GetCurrentStormMiddle();
		float Angle = vec2angle(DiffVec.x, -DiffVec.y);
		BadAngles.push_back(Angle);
	}

	std::vector<float> TestingAngles;
	for (int i = 0; i < BadAngles.size(); i++)
	{
		int j = (i + 1) % (BadAngles.size());
		//Pushing back the halfpoint angle of two angles occupied by opponents (or storm)
		TestingAngles.push_back(0.5f*(BadAngles[i] + BadAngles[j]));
	}
	//Sorting the testingangles in an ascending order of Manhattan distance from the bad angles
	int bestIndex = 0;
	float bestDiff = 0.f;
	for (int i = 0; i < TestingAngles.size(); i++)
	{
		float diff = 0;
		for (int j = 0; j < BadAngles.size(); j++)
		{
			float AngDiff = TestingAngles[i] - BadAngles[j];
			//This is for normalizing angle differences
			while (AngDiff > 180.f)AngDiff -= 360.f;
			while (AngDiff < -180.f)AngDiff += 360.f;
			AngDiff = abs(AngDiff);
			diff += AngDiff;
		}
		if (diff > bestDiff)
		{
			bestDiff = diff;
			bestIndex = i;
		}
	}

	return TestingAngles[bestIndex];


}




bool dc_match::BotShouldRushOpponent(int id)
{
	if (!BotHasRealNoticed(id))return false;
	if (players[id].iHealth + players[id].iShield > BotData[id].RushHealthMinOF)
	{
		if (players[id].Items[0].bValidated && GetIndex(BotData[id].WeaponPreferences[0], players[id].Items[0].ListIndex) < BotData[id].GoodEnoughRanking[0])return true;
		if (players[id].Items[1].bValidated && GetIndex(BotData[id].WeaponPreferences[1], players[id].Items[1].ListIndex) < BotData[id].GoodEnoughRanking[1])return true;
	}
	return false;
}

void dc_match::BotRushOpponent(int id)
{
	if (BotData[id].Changables.DistantTargetType == 6)return;
	int closest_id = id;

	for (auto I : BotData[id].Changables.NoticedPlayers)
	{
		if (I.NoticeTime.deltaTime() <= 1000.f* BotData[id].fEnemyNoticeTime)continue;
		if (closest_id == id || (GetDistance(players[id].vPosition, players[closest_id].vPosition) > GetDistance(players[id].vPosition, players[I.playerid].vPosition)))
			closest_id = I.playerid;
	}

	BotData[id].Changables.DistantTargetType = 6;
	BotData[id].Changables.DistantTargetPoint = players[closest_id].vPosition;
	BotData[id].move_path.clear();
	//ConLog("\n%d is rushing %d", id,closest_id);

}

void dc_match::BotSwapToJustInCaseWeapon(int id)
{
	if (BotData[id].Changables.WeaponSwapCheckClock.deltaTime() > 600)
	{
		float fCurrentDamage = 0;
		if (players[id].GetCurrentWeapon().bValidated)fCurrentDamage = players[id].GetCurrentWeapon().CalculateDPS(BotData[id].JustInCaseWeaponDistance, BotData[id].FightType[players[id].iSelectedWeapon]);

		int SwapSlot = players[id].iSelectedWeapon;
		for (int i = 0; i < 5; i++)
		{
			if (players[id].Items[i].bValidated && players[id].Items[i].CalculateDPS(BotData[id].JustInCaseWeaponDistance, BotData[id].FightType[i]) > fCurrentDamage)
			{
				SwapSlot = i;
				fCurrentDamage = players[id].Items[i].CalculateDPS(BotData[id].JustInCaseWeaponDistance, BotData[id].FightType[i]);
			}
		}
		if (SwapSlot != players[id].iSelectedWeapon)PlayerSwapWeapon(id, SwapSlot);
		BotData[id].Changables.WeaponSwapCheckClock.Update();
	}
}

void dc_match::BotSwapWeaponInFight(int id)
{
	if (BotData[id].Changables.WeaponSwapCheckClock.deltaTime() > 300)
	{
		float shortest_distance = 999.f;
		for (int i = 0; i < BotData[id].Changables.TargetedPlayerIDs.size(); i++)
		{
			if (GetDistance(players[id].vPosition, players[BotData[id].Changables.TargetedPlayerIDs[i]].vPosition) < shortest_distance)
				shortest_distance = GetDistance(players[id].vPosition, players[BotData[id].Changables.TargetedPlayerIDs[i]].vPosition);
		}

		float fCurrentDamage = 0;
		if (players[id].GetCurrentWeapon().bValidated)fCurrentDamage = players[id].GetCurrentWeapon().CalculateDPS(shortest_distance, BotData[id].FightType[players[id].iSelectedWeapon]);
		float fOriginalDamage = fCurrentDamage;
		int SwapSlot = players[id].iSelectedWeapon;
		for (int i = 0; i < 5; i++)
		{
			if (players[id].Items[i].bValidated && players[id].Items[i].CalculateDPS(shortest_distance, BotData[id].FightType[i]) > fOriginalDamage*1.25f
				&& players[id].Items[i].CalculateDPS(shortest_distance, BotData[id].FightType[i]) > fCurrentDamage)
			{
				fCurrentDamage = players[id].Items[i].CalculateDPS(shortest_distance, BotData[id].FightType[i]);
				SwapSlot = i;
			}
		
		}

		if (SwapSlot != players[id].iSelectedWeapon)PlayerSwapWeapon(id, SwapSlot);
		BotData[id].Changables.WeaponSwapCheckClock.Update();
	}
}

void dc_match::BotSwapToEmergencyWeapon(int id)
{
	if (BotData[id].Changables.WeaponSwapCheckClock.deltaTime() > 350)
	{
		float shortest_distance = 30.f;
		for (int i = 0; i < BotData[id].Changables.TargetedPlayerIDs.size(); i++)
		{
			if (GetDistance(players[id].vPosition, players[BotData[id].Changables.TargetedPlayerIDs[i]].vPosition) < shortest_distance)
				shortest_distance = GetDistance(players[id].vPosition, players[BotData[id].Changables.TargetedPlayerIDs[i]].vPosition);
		}

		float fCurrentDamage = 0;
		if (players[id].GetCurrentWeapon().bValidated)fCurrentDamage = players[id].GetCurrentWeapon().CalculateDPS(shortest_distance, BotData[id].FightType[players[id].iSelectedWeapon]);
		float fOriginalDamage = fCurrentDamage;
		int SwapSlot = players[id].iSelectedWeapon;
		for (int i = 0; i < 5; i++)
		{
			if (players[id].Items[i].bValidated && players[id].Items[i].CalculateDPS(shortest_distance, BotData[id].FightType[i]) > fCurrentDamage)
			{
				fCurrentDamage = players[id].Items[i].CalculateDPS(shortest_distance, BotData[id].FightType[i]);
				SwapSlot = i;
			}

		}

		if (SwapSlot != players[id].iSelectedWeapon)PlayerSwapWeapon(id, SwapSlot);
		BotData[id].Changables.WeaponSwapCheckClock.Update();
	}
}

void dc_match::BotCorrectAngleNew(int id, float diff, float neededang, float speed, float corr)
{
	float currentangle = players[id].fAngle;

	float angleDifference = neededang - currentangle;
	//Angle difference normalization
	while (angleDifference > 180.f)angleDifference -= 360.f;
	while (angleDifference <= -180.f)angleDifference += 360.f;

	float AngleCorrection = speed*diff;

	if (angleDifference > 0)
	{
		if (angleDifference < corr)AngleCorrection *= BotData[id].fAimCorrectSpeedPenalty;
		if (angleDifference < AngleCorrection)AngleCorrection = angleDifference;

		players[id].fAngle += AngleCorrection;
	}
	else if (angleDifference < 0)
	{
		if (angleDifference > -corr)AngleCorrection *= BotData[id].fAimCorrectSpeedPenalty;
		if (angleDifference > -AngleCorrection)AngleCorrection = -angleDifference;

		players[id].fAngle -= AngleCorrection;
	}

}

int dc_match::BotShouldHeal(int id)
{
	bool has_opponent = BotHasRealNoticed(id);
	int health = players[id].iHealth;
	int shield = players[id].iShield;

	//InStorm
	float distfromcurrentstorm = GetDistance(GetCurrentStormMiddle(), players[id].vPosition);
	//float distfromnextstorm = GetDistance(GetNextStormMiddle(), players[id].vPosition);

	if (IsPointInStorm(players[id].vPosition))
	{

		for (int i = 0; i < 6; i++)
		{
			if (i == 2 || i == 3)continue;
			auto response = players[id].hasSpecificItem(13 + i);
			if (response != -1)
			{
				//Only returning 2 in the very last moment if in storm
				if (players[id].iHealth < (GetNextStormDamage() * (1 + ceil(g_Items[13 + i].fHealTime))))return 2;
			}

		}
	}

	else
	{
		if (BotData[id].Changables.forceHeal && players[id].Items[0].IsHeal() &&players[id].Items[0].bValidated)
		{
			return 2;
		}
		for (int i = 0; i < 6; i++)
		{
			auto response = players[id].hasSpecificItem(13 + i);
			if (response != -1)
			{
				//Checking if the healing item is between the boundaries
				if (players[id].Items[response].iType == 4)
				{
					if ((BotData[id].HealUseMinimums[i] <= health && BotData[id].HealUseMaximums[i] > health)
						|| (has_opponent && g_Items[13+i].iHealMax > health))return 2;
				}
				else if (players[id].Items[response].iType == 5)
				{
					if ((BotData[id].HealUseMinimums[i] <= shield && BotData[id].HealUseMaximums[i] > shield)
						|| (has_opponent && g_Items[13 + i].iHealMax > shield))return 2;
				}
				else if (players[id].Items[response].iType == 6)
				{
					if ((BotData[id].HealUseMinimums[i] <= (health+shield) && BotData[id].HealUseMaximums[i] > (health + shield))
						|| (has_opponent && (health+shield) < 195 ))return 2;
				}
			}

		}
	}
	if (health != 100 || shield != 100)return 1;
	return 0;
}

bool dc_match::BotHasUsableWeapon(int id, float range)
{
	float dmg = 0.f;
	for (int i = 0; i < 5; i++)
	{
		if (players[id].Items[i].bValidated)
		{
			if (players[id].Items[i].CalculateDPS(range, BotData[i].FightType) > 0)return true;
		}
	}
	return false;
}

void dc_match::BotCheckStuff(int id, float diff)
{
	//If the healing item has been used up
	if (players[id].fHealTime <= 0.f)BotData[id].Changables.bHealing = false;

	//If the last zone point has been reached
	if (BotData[id].Changables.DistantTargetType == 3)
	{
		if(GetDistance(BotData[id].Changables.DistantTargetPoint,players[id].vPosition) < 0.5f)
		BotData[id].Changables.DistantTargetType = 0;


	}

	//Checking for noticable players if they die or too far
	for (int i = BotData[id].Changables.NoticedPlayers.size() - 1; i >= 0; i--)
	{
		auto pid = BotData[id].Changables.NoticedPlayers[i].playerid;

		if (players[pid].iHealth <= 0
			|| GetBotModifiedDistance(players[id].vPosition, players[pid].vPosition) > BotData[id].fPlayerRange + 5.f)
		{
			BotData[id].Changables.NoticedPlayerIDs.erase(BotData[id].Changables.NoticedPlayerIDs.begin() + i);
			BotData[id].Changables.NoticedPlayers.erase(BotData[id].Changables.NoticedPlayers.begin() + i);
		}
	}
	//Checking for noticed/targetabl players if they aren't visible or too far
	for (int i = BotData[id].Changables.TargetedPlayerIDs.size() - 1; i >= 0; i--)
	{
		auto pid = BotData[id].Changables.TargetedPlayers[i].playerid;

		bool hit0 = false, hit1 = false, hit2 = false, hit3 = false, hit4 = false;

		hit0 = !(map.trace_ray(players[id].vPosition, players[pid].vPosition).hit_object);
		//TODO: Do these relative to the bot with index 'id'
		hit1 = !(map.trace_ray(players[id].vPosition, players[pid].vPosition + sf::Vector2f(0.25f, 0.f)).hit_object);
		hit2 = !(map.trace_ray(players[id].vPosition, players[pid].vPosition + sf::Vector2f(0.f, 0.25f)).hit_object);
		hit3 = !(map.trace_ray(players[id].vPosition, players[pid].vPosition - sf::Vector2f(0.25f, 0.f)).hit_object);
		hit4 = !(map.trace_ray(players[id].vPosition, players[pid].vPosition - sf::Vector2f(0.f, 0.25f)).hit_object);


		if (players[pid].iHealth > 0 && (GetBotModifiedDistance(players[id].vPosition, players[pid].vPosition) <= (BotData[id].fPlayerRange))
			&& (hit1 || hit2 || hit3 || hit4 || hit0))BotData[id].Changables.TargetedPlayers[i].DeleteTime.Update();

		if(players[pid].iHealth <= 0 && BotData[id].Changables.TargetedPlayers[i].DeleteTime.deltaTime() > 1000.f*BotData[id].BotMemoryAfterDie)
		{
			BotData[id].Changables.TargetedPlayerIDs.erase(BotData[id].Changables.TargetedPlayerIDs.begin() + i);
			BotData[id].Changables.TargetedPlayers.erase(BotData[id].Changables.TargetedPlayers.begin() + i);
		}
		else if ((GetBotModifiedDistance(players[id].vPosition, players[pid].vPosition) > BotData[id].fPlayerRange)
			|| (!hit0 && !hit1 && !hit2 && !hit3 && !hit4) && BotData[id].Changables.TargetedPlayers[i].DeleteTime.deltaTime() > 1000.f*BotData[id].BotMemoryAfterVanish)
		{
			BotData[id].Changables.TargetedPlayerIDs.erase(BotData[id].Changables.TargetedPlayerIDs.begin() + i);
			BotData[id].Changables.TargetedPlayers.erase(BotData[id].Changables.TargetedPlayers.begin() + i);
		}

	}
	//Resetting bail distance if the last bail happened 30s or more ago
	if (BotData[id].Changables.LastBailClock.deltaTime() > 30000)
		BotData[id].Changables.BailDistance = 40;

	BotData[id].Changables.SideStepTimeLeft -= diff;

	//If a bail target dies, it gets erased
	for (int i = BotData[id].Changables.BailTarget.size() - 1; i >= 0; i--)
	{
		if (players[BotData[id].Changables.BailTarget[i]].iHealth <= 0) BotData[id].Changables.BailTarget.erase(BotData[id].Changables.BailTarget.begin() + i);
	}
	//In case of successful bailing
	if (BotData[id].Changables.DistantTargetType == 5 && BotData[id].Changables.BailTarget.size() == 0)
	{
		BotData[id].Changables.DistantTargetType = 0;
		BotData[id].move_path.clear();
	}

	if (BotData[id].Changables.DistantTargetType == 0)
	{
		BotData[id].Changables.DistantTargetPoint = players[id].vPosition;
	}

	if ((BotData[id].Changables.DistantTargetType != 9 && players[id].fHealTime <= 0.f) 
		|| !players[id].Items[0].IsHeal()
		|| (players[id].iHealth >= 100 && players[id].iShield >= 100)){
		BotData[id].Changables.forceHeal = false;
		BotData[id].Changables.forceHealHealID = 0;
	}
	
}

void dc_match::BotDoHeal(int id)
{
	//if (BotData[id].Changables.bHealing)return;
	int health = players[id].iHealth;
	int shield = players[id].iShield;

	bool has_opponent = BotHasRealNoticed(id);

	if (IsPointInStorm(players[id].vPosition))
	{
		for (int i = 0; i < 6; i++)
		{
			//Not healing shields in storm
			if (i == 2 || i == 3)continue;
			auto response = players[id].hasSpecificItem(13 + i);
			if (response != -1)
			{
				if (players[id].iHealth < (GetNextStormDamage() * (1 + ceil(g_Items[13 + i].fHealTime))))
				{
					PlayerSwapWeapon(id, response);
					PlayerShootWeapon(id);
					BotData[id].Changables.bHealing = true;
					//BotData[id].Changables.DistantTargetType = 0;
					return;
				}
			}

		}
	}
	else
	{
		if (BotData[id].Changables.forceHeal && players[id].Items[0].IsHeal())
		{
			PlayerSwapWeapon(id, 0);
			PlayerShootWeapon(id);
			BotData[id].Changables.bHealing = true;
			
			return;
		}

		for (int j = 0; j < 5; j++)
		{
			if (!players[id].Items[j].bValidated)continue;
			auto i = players[id].Items[j].ListIndex;
			if (i >= 13 && i <= 18)
			{
				i = i - 13;
				if (players[id].Items[j].iType == 4)
				{

					if ((BotData[id].HealUseMinimums[i] <= health && BotData[id].HealUseMaximums[i] > health)
						|| (has_opponent && g_Items[i+13].iHealMax > health))
					{

						PlayerSwapWeapon(id, j);
						PlayerShootWeapon(id);
						BotData[id].Changables.bHealing = true;
						//BotData[id].Changables.DistantTargetType = 0;
						return;
					}
				}
				else if (players[id].Items[j].iType == 5)
				{
					if ((BotData[id].HealUseMinimums[i] <= shield && BotData[id].HealUseMaximums[i] > shield)
						|| (has_opponent && g_Items[i + 13].iHealMax > shield))
					{
						PlayerSwapWeapon(id, j);
						PlayerShootWeapon(id);
						BotData[id].Changables.bHealing = true;
						//BotData[id].Changables.DistantTargetType = 0;
						return;
					}
				}
				else if (players[id].Items[j].iType == 6)
				{
					if ((BotData[id].HealUseMinimums[i] <= (health + shield) && BotData[id].HealUseMaximums[i] > (health + shield))
						|| (195 > (health+shield)))
					{
						PlayerSwapWeapon(id, j);
						PlayerShootWeapon(id);
						BotData[id].Changables.bHealing = true;
						//BotData[id].Changables.DistantTargetType = 0;
						return;
					}
				}
			}
		}
	}
}
bool dc_match::BotShouldGoToZone(int id)
{
	if (IsPointInStorm(players[id].vPosition))return true;
	if (BotData[id].BotZoneFearLevel == 0); //Only in storm
	else if (BotData[id].BotZoneFearLevel == 1) //Only if storm is close
	{
		auto Mid = GetCurrentStormMiddle();
		auto Size = GetCurrentStormDiameter();

		return GetDistance(Mid, players[id].vPosition) > (Size/2-10);
	}
	else if (BotData[id].BotZoneFearLevel == 2) // On time
	{
		auto Mid = GetNextStormMiddle();
		auto Size = GetNextStormDiameter();
		float time_to_get_in_there = max(0.f, GetDistance(Mid, players[id].vPosition) - Size / 2) / (UNIT_RUN_SPEED*0.8f);
		float time_till_close = max(0.00f,GetTimeTillNextStormPhase()-0.25f-BotData[id].fBotThinkDelay);

		auto cuMid = GetCurrentStormMiddle();
		auto cuSize = GetCurrentStormDiameter();

		if (GetDistance(cuMid, players[id].vPosition) >= (cuSize / 2 - 0.5f))return true;

		return time_to_get_in_there >= time_till_close && time_to_get_in_there > 0.f;
	}
	else if (BotData[id].BotZoneFearLevel == 3) // Early
	{
		auto Mid = GetNextStormMiddle();
		auto Size = GetNextStormDiameter();
		float time_to_get_in_there = max(0.f, GetDistance(Mid, players[id].vPosition) - Size / 2) / (UNIT_RUN_SPEED*0.8f);
		float time_till_close = max(0.00f, GetTimeTillNextStormPhase() - 0.25f - BotData[id].fBotThinkDelay)-20.f;

		auto cuMid = GetCurrentStormMiddle();
		auto cuSize = GetCurrentStormDiameter();

		if (GetDistance(cuMid, players[id].vPosition) >= (cuSize / 2 - 0.5f))return true;

		return time_to_get_in_there >= time_till_close && time_to_get_in_there > 0.f;
	}
	else if (BotData[id].BotZoneFearLevel == 4) // Very early
	{
		auto Mid = GetNextStormMiddle();
		auto Size = GetNextStormDiameter();
		float time_to_get_in_there = max(0.f, GetDistance(Mid, players[id].vPosition) - Size / 2) / (UNIT_RUN_SPEED*0.8f);
		float time_till_close = max(0.00f, GetTimeTillNextStormPhase() - 0.25f - BotData[id].fBotThinkDelay) - 60.f;

		auto cuMid = GetCurrentStormMiddle();
		auto cuSize = GetCurrentStormDiameter();

		if (GetDistance(cuMid, players[id].vPosition) >= (cuSize / 2 - 0.5f))return true;

		return time_to_get_in_there >= time_till_close && time_to_get_in_there > 0.f;
	}

	return false;
}

void dc_match::BotGoToZone(int id)
{
	//if (BotData[id].Changables.DistantTargetType == 3)return;
	auto Mid = GetNextStormMiddle();
	auto Size = GetNextStormDiameter();
	float distance = max(0.f, GetDistance(Mid, players[id].vPosition) - Size / 2);

	if (distance > 0.f)
	{

		BotData[id].Changables.DistantTargetType = 3;
		//BotData[id].Changables.DistantTargetPoint = Mid + GetUnit(players[id].vPosition - Mid)*(Size / 2);
		BotData[id].Changables.DistantTargetPoint = players[id].vPosition + ToUnitVector(Mid - players[id].vPosition)*max(2.f,min(10.f, distance));
		if (BotData[id].Changables.DistantTargetType != 3 && BotData[id].Changables.DistantTargetType != 0)
		BotData[id].move_path.clear();
	}
}

bool dc_match::BotNeedsToLoot(int id)
{
	if (BotData[id].Changables.DistantTargetType == 3 || BotData[id].Changables.RestOfChests.size() <= 0)return false;
	if (players[id].iHealth + players[id].iShield < BotData[id].MinimumHealthToRaid)return true;
	for (int i = 0; i < 5; i++)
	{
		if (!players[id].Items[i].bValidated)return true;
		if (GetIndex(BotData[id].WeaponPreferences[i],players[id].Items[i].ListIndex) > BotData[id].GoodEnoughRanking[i] && (BotData[id].FightType[i] != 2 || BotData[id].SuckerForExtraHeals))return true;
	}
	return false;
}

int dc_match::BotIsNeededItem(int id, int listid)
{
	if (BotData[id].Changables.forceHeal) return -1;
	for (int i = 0; i < 5; i++)if (!players[id].Items[i].bValidated)return i;


	if (GetIndex(BotData[id].WeaponPreferences[0], listid) < GetIndex(BotData[id].WeaponPreferences[0], players[id].Items[0].ListIndex))return 0;
	if (GetIndex(BotData[id].WeaponPreferences[1], listid) < GetIndex(BotData[id].WeaponPreferences[1], players[id].Items[1].ListIndex))return 1;
	if (GetIndex(BotData[id].WeaponPreferences[2], listid) < GetIndex(BotData[id].WeaponPreferences[2], players[id].Items[2].ListIndex)
		|| (listid == players[id].Items[2].ListIndex && players[id].Items[2].IsHeal() && players[id].Items[2].iBullets < players[id].Items[2].iMaxBullets)
		)return 2;
	if (GetIndex(BotData[id].WeaponPreferences[3], listid) < GetIndex(BotData[id].WeaponPreferences[3], players[id].Items[3].ListIndex)
		|| (listid == players[id].Items[3].ListIndex && players[id].Items[3].IsHeal() && players[id].Items[3].iBullets < players[id].Items[3].iMaxBullets)
		)return 3;
	if (GetIndex(BotData[id].WeaponPreferences[4], listid) < GetIndex(BotData[id].WeaponPreferences[4], players[id].Items[4].ListIndex)
		|| (listid == players[id].Items[4].ListIndex && players[id].Items[4].IsHeal() && players[id].Items[4].iBullets < players[id].Items[4].iMaxBullets)
		)return 4;
	
	return -1;
};

void dc_match::BotClearUnnecesaryMovepathInFight(int id)
{
	if (BotData[id].Changables.DistantTargetType != 5)
	{
		BotData[id].move_path.clear();
		BotData[id].Changables.DistantTargetType = 0;
	}
}

void dc_match::BotDoTheMoveInFight(int id, float diff)
{
	if (BotData[id].Changables.DistantTargetType == 5) //Bailing
	{
		if (BotData[id].move_path.size() == 0)
		{
			BotCalculatePath(id, BotData[id].Changables.DistantTargetPoint);
			float currentangle = players[id].fAngle;
			BotMoveToNextPoint(id, diff);
			players[id].fAngle = currentangle;
		}
		else if (GetDistance(BotData[id].Changables.DistantTargetPoint, players[id].vPosition) > 1.f) {
			float currentangle = players[id].fAngle;
			BotMoveToNextPoint(id, diff);
			players[id].fAngle = currentangle;
		}
		if (GetDistance(BotData[id].Changables.DistantTargetPoint, players[id].vPosition) <= 1.f)BotData[id].Changables.DistantTargetType = 0;
	}
}

void dc_match::BotDoTheMove(int id,float diff)
{
	if (BotData[id].move_path.size() == 0) //No movepath, generating new move path
	{
		BotCalculatePath(id, BotData[id].Changables.DistantTargetPoint);
		if (BotData[id].move_path.size() == 0)BotData[id].Changables.movepathBugged = true;
		else BotData[id].Changables.movepathBugged = false;
		BotMoveToNextPoint(id,diff);

	} //Moving towards the distanttargetpoint if it's far
	else if  (GetDistance(BotData[id].Changables.DistantTargetPoint, players[id].vPosition) > 0.5f) BotMoveToNextPoint(id,diff);



	if (BotData[id].Changables.DistantTargetType == 1) //Chests
	{
		if (!IsIn(BotData[id].Changables.RestOfChests, BotData[id].Changables.DistantTargetChestID) || IsPointInStorm(BotData[id].Changables.DistantTargetPoint))
		{
			BotData[id].Changables.DistantTargetType = 0;
			BotCheckOpenChests(id, true);
			BotData[id].Changables.fTimeTillThink = BotData[id].fBotThinkDelay;
		}
		else if (GetDistance(map.chests[BotData[id].Changables.DistantTargetChestID].vPosition, players[id].vPosition) > 1.5f)
		{
		}
		else
		{
			PlayerOpenChest(id, BotData[id].Changables.DistantTargetChestID);
			BotData[id].Changables.fTimeTillThink = BotData[id].fBotThinkDelay;
		}
	}
	else if (BotData[id].Changables.DistantTargetType == 2) //Items
	{
		if (GetDistance(BotData[id].Changables.DistantTargetPoint, players[id].vPosition) > 1.4f)
		{
		}
		else
		{
			std::vector<int> ItemList;
			for (int i = 0; i < map.items.size(); i++)
			{
				auto& item = map.items[i];
				if (item.bOwned)continue;
				if (GetDistance(item.vPosition, players[id].vPosition) > 1.5f)continue;

				if (BotIsNeededItem(id, item.ListIndex) != -1)ItemList.push_back(i);
			}
			auto itemlistcomp = [=](int a, int b)
			{
				return GetDistance(players[id].vPosition, map.items[a].vPosition) <= GetDistance(players[id].vPosition, map.items[b].vPosition);
			};
			std::sort(ItemList.begin(), ItemList.end(), itemlistcomp);
			if (ItemList.size() > 0)
			{
				int wantedslot = BotIsNeededItem(id, map.items[ItemList[0]].ListIndex);
				if (players[id].Items[wantedslot].bValidated && map.items[ItemList[0]].ListIndex != players[id].Items[wantedslot].ListIndex)
					PlayerDropWeapon(id, wantedslot);
				PlayerPickupItem(id, 0, ItemList[0]);
				BotSortInventory(id);
			}
			else
			{
				BotData[id].Changables.DistantTargetType = 0;
				BotData[id].Changables.forceHeal = false;
			}
			BotData[id].Changables.fTimeTillThink = BotData[id].fBotThinkDelay;
			BotData[id].Changables.DistantTargetType = 0;
		}
	}
	else if (BotData[id].Changables.DistantTargetType == 9) //Force heal pickup
	{
		if (GetDistance(BotData[id].Changables.DistantTargetPoint, players[id].vPosition) > 1.4f)
		{
		}
		else
		{
			std::vector<int> ItemList;
			for (int i = 0; i < map.items.size(); i++)
			{
				auto& item = map.items[i];
				if (item.bOwned)continue;
				if (GetDistance(item.vPosition, players[id].vPosition) > 1.5f)continue;

				auto listid = item.ListIndex;
				if (players[id].iHealth < 75 && (listid == 13 || listid == 14 || listid == 17 || listid == 18)) {

					if (IsPointInStorm(players[id].vPosition) && players[id].hasWhiteheal() == -1)
					{
						ItemList.push_back(i);
					}
					else if (IsPointInStorm(players[id].vPosition) && players[id].hasWhiteheal() != -1)
					{
						int sl = players[id].hasSpecificItem(listid);
						if (players[id].Items[sl].iBullets < players[id].Items[sl].iMaxBullets)
						{
							ItemList.push_back(i);
						}
					}
					else if (!IsPointInStorm(players[id].vPosition))
					{
						ItemList.push_back(i);
					}
				}
				else if (players[id].iHealth < 100 && (listid == 14 || listid == 17 || listid == 18)) {
					if (IsPointInStorm(players[id].vPosition) && players[id].hasWhiteheal() == -1)
					{
						ItemList.push_back(i);
					}
					else if (!IsPointInStorm(players[id].vPosition))
					{
						ItemList.push_back(i);
					}
				}
				else if (players[id].iShield < 50 && (listid == 15 || listid == 16 || listid == 17 || listid == 18)) { ItemList.push_back(i); }
				else if (players[id].iShield < 100 && (listid == 16 || listid == 17 || listid == 18)) { ItemList.push_back(i); }
			}
			auto itemlistcomp = [=](int a, int b)
			{
				return GetDistance(players[id].vPosition, map.items[a].vPosition) <= GetDistance(players[id].vPosition, map.items[b].vPosition);
			};
			std::sort(ItemList.begin(), ItemList.end(), itemlistcomp);
			if (ItemList.size() > 0)
			{
				if (players[id].Items[4].bValidated)
					PlayerDropWeapon(id, 0);

				BotData[id].Changables.forceHeal = true;
				BotData[id].Changables.forceHealHealID = map.items[ItemList[0]].ListIndex;

				PlayerPickupItem(id, 0, ItemList[0]);
				PlayerSwapWeapon(id, 0);
				
				if(players[id].GetCurrentWeapon().IsHeal())
					PlayerShootWeapon(id);


				//ConLog("\n%d is force healing", id);
				//camera_follows = id;
			}
			else
			{
				BotData[id].Changables.DistantTargetType = 0;
				BotData[id].Changables.forceHeal = false;
			}
			BotData[id].Changables.fTimeTillThink = BotData[id].fBotThinkDelay;
			BotData[id].Changables.DistantTargetType = 0;
		}
	}

	else if (BotData[id].Changables.DistantTargetType == 4 || BotData[id].Changables.DistantTargetType == 5 || BotData[id].Changables.DistantTargetType == 6 || BotData[id].Changables.DistantTargetType == 7)
	{
		if (GetDistance(players[id].vPosition, BotData[id].Changables.DistantTargetPoint) < 1.f)
		{
			BotData[id].Changables.fTimeTillThink = BotData[id].fBotThinkDelay;
			BotData[id].Changables.DistantTargetType = 0;
		}
	}
	else if (BotData[id].Changables.DistantTargetType == 8) //opening airdrop
	{
		int AID = -1;
		for (int i = 0; i < AirDrops.size(); i++)
			if (AirDrops[i].airdropid == BotData[id].Changables.DistantTargetAirdropID)AID = i;

		if (AID == -1)
		{
			BotData[id].Changables.DistantTargetType = 0;
			BotData[id].Changables.fTimeTillThink = BotData[id].fBotThinkDelay;
		}
		if (GetDistance(AirDrops[AID].vPosition, players[id].vPosition) > 1.5f)
		{
		}
		else
		{
			PlayerOpenAirdrop(id, BotData[id].Changables.DistantTargetAirdropID);
			BotData[id].Changables.fTimeTillThink = BotData[id].fBotThinkDelay;
			if (players[id].fOpeningTime <= 0.f)
			{
				BotData[id].Changables.DistantTargetType = 0;
				BotData[id].Changables.fTimeTillThink = BotData[id].fBotThinkDelay;
			}
		}
	}
}

void dc_match::BotLoot(int id)
{
	if (BotData[id].Changables.DistantTargetType == 1)return;
			int close_id = BotGetClosestChest(id);
			//int close_id = GetClosestChestWithExceptions(players[id].vPosition, BotData[id].Changables.KnownOpenChest);
			//int close_id = GetClosestChestToPosition(players[id].vPosition);
			if (close_id != -1)
			{
				BotData[id].Changables.DistantTargetType = 1;
				BotData[id].Changables.DistantTargetChestID = close_id;
				BotData[id].Changables.DistantTargetPoint = map.chests[close_id].vPosition;
				BotData[id].move_path.clear();
			}
			else BotData[id].Changables.AreChestsAvailable = false;
}

bool dc_match::BotShouldCoverAirDrop(int id)
{
	if (players[id].hasFreeSlot() != -1)return false;


	for (int i = 0; i < AirDrops.size(); i++)
	{
		if (GetDistance(AirDrops[i].vPosition, players[id].vPosition) > BotData[id].fAirDropInterestDistance)continue;
		return true;
	}

	return false;
}

bool dc_match::BotShouldGetAirDrop(int id)
{
	if (players[id].hasFreeSlot() != -1)return false;

	for (int i = 0; i < AirDrops.size(); i++)
	{
		if (GetDistance(AirDrops[i].vPosition, players[id].vPosition) > BotData[id].fAirDropInterestDistance)continue;
		if (ServerTime - AirDrops[i].ClockBegin < AIRDROP_FALLINGTIME)continue;
		return true;
	}

	return false;
}

void dc_match::BotCoverAirDrop(int id)
{
	if (BotData[id].Changables.DistantTargetType == 7)return;
	int AID = -1;
	for (int i = 0; i < AirDrops.size(); i++)
	{
		if (GetDistance(AirDrops[i].vPosition, players[id].vPosition) > BotData[id].fAirDropInterestDistance)continue;
		if (AID == -1 || GetDistance(AirDrops[AID].vPosition, players[id].vPosition) > GetDistance(AirDrops[i].vPosition, players[id].vPosition))AID = i;
	}
	if (AID == -1)return;


	float Range = g_RandomDevice.RandomFloat(BotData[id].fAirDropGuardMaxRange*BotData[id].fAirDropGuardMinModifier, BotData[id].fAirDropGuardMaxRange);
	sf::Vector2f npos(-10000, -10000);
	while (GetDistance(AirDrops[AID].vPosition, npos) > Range)
	{
		npos.x = g_RandomDevice.RandomFloat(AirDrops[AID].vPosition.x - Range / 2, AirDrops[AID].vPosition.x + Range / 2);
		npos.y = g_RandomDevice.RandomFloat(AirDrops[AID].vPosition.y - Range / 2, AirDrops[AID].vPosition.y + Range / 2);
	}
	BotData[id].Changables.DistantTargetType = 7;
	BotData[id].Changables.DistantTargetPoint = npos;
	BotData[id].move_path.clear();
}

void dc_match::BotGetAirDrop(int id)
{
	if (BotData[id].Changables.DistantTargetType == 8)return;
	int AID = -1;
	for (int i = 0; i < AirDrops.size(); i++)
	{
		if (GetDistance(AirDrops[i].vPosition, players[id].vPosition) > BotData[id].fAirDropInterestDistance)continue;
		if (AID == -1 || GetDistance(AirDrops[AID].vPosition, players[id].vPosition) > GetDistance(AirDrops[i].vPosition, players[id].vPosition))AID = i;
	}
	if (AID == -1)return;
	float Range = g_RandomDevice.RandomFloat(BotData[id].fAirDropGuardMaxRange*BotData[id].fAirDropGuardMinModifier, BotData[id].fAirDropGuardMaxRange);
	BotData[id].Changables.DistantTargetType = 8;
	BotData[id].Changables.DistantTargetPoint = AirDrops[AID].vPosition;
	BotData[id].Changables.DistantTargetAirdropID = AirDrops[AID].airdropid;
	BotData[id].move_path.clear();
}



void dc_match::BotRaid(int id)
{
	if (BotData[id].Changables.DistantTargetType == 4)return;
	auto nextStormMid = GetNextStormMiddle();
	auto nextStormRadius = GetNextStormDiameter() / 2;
	nextStormRadius = min(nextStormRadius, 300.f);
	sf::Vector2f nPoint(6000, 6000);
	auto distanceFromNextStorm = max(0,GetDistance(players[id].vPosition, nextStormMid) - nextStormRadius);
	float rad = distanceFromNextStorm + 100;
	sf::Vector2f p = players[id].vPosition;
	while (GetDistance(nPoint,nextStormMid) > nextStormRadius) //Generating a Random point in the zone
	{
		int X = Random(p.x - rad, p.x + rad);
		int Y = Random(p.y - rad, p.y + rad);
		nPoint = sf::Vector2f(X, Y);
	}
	BotData[id].Changables.DistantTargetType = 4;
	BotData[id].move_path.clear();
	BotData[id].Changables.DistantTargetPoint = nPoint;
}

int dc_match::BotGetClosestChest(int id)
{
	int returnid = -1;
	for (int i =  0; i < BotData[id].Changables.RestOfChests.size(); i++)
	{
		if (returnid == -1
			|| GetDistance(map.chests[BotData[id].Changables.RestOfChests[i]].vPosition, players[id].vPosition) < GetDistance(map.chests[BotData[id].Changables.RestOfChests[returnid]].vPosition, players[id].vPosition))
			returnid = i;
	}
	if (returnid == -1)return -1;
	else
		return BotData[id].Changables.RestOfChests[returnid];
}

void dc_match::BotCheckOpenChests(int id, bool force_it)
{
	if (BotData[id].Changables.ChestCheckClock.deltaTime() < 1000 && !force_it)return;
	for (int i = BotData[id].Changables.RestOfChests.size()-1; i >= 0; i--)
	{

		//If the chest in the chestrange is visibly open
		if(GetDistance(map.chests[BotData[id].Changables.RestOfChests[i]].vPosition, players[id].vPosition) <= BotData[id].fChestRange && map.chests[BotData[id].Changables.RestOfChests[i]].bOpen)
			BotData[id].Changables.RestOfChests.erase(BotData[id].Changables.RestOfChests.begin() + i);
		else if (IsPointInStorm(map.chests[BotData[id].Changables.RestOfChests[i]].vPosition)) //If the chest is in the storm
			BotData[id].Changables.RestOfChests.erase(BotData[id].Changables.RestOfChests.begin() + i);

	}
	BotData[id].Changables.ChestCheckClock.Update();
}

void dc_match::BotJumpoffBus(int id)
{
	float CurrentBusTime = GetDistance(BusCurrentPosition, BusStartPosition)/BUS_TRAVELSPEED;
	if (CurrentBusTime > BotData[id].JumpoffTime)PlayerJumpOffBus(id);
	//if (id == 1)printf("\nCBT: %.2f", CurrentBusTime);
}

void dc_match::BotDescend(int id, float diff)
{
	float TimeToDescend = players[id].fFreeFallHeight / (BotData[id].DescendSpeedInMind + 1.5f);
	float TimeToReachThere = GetDistance(players[id].vPosition, BotData[id].JumpToPosition) / UNIT_FREEFALL_SPEED;

	if (TimeToReachThere <= TimeToDescend)PlayerDescent(id, diff, 6.f);
}

void dc_match::BotFreefallMove(int id,float diff)
{
	if (!BotData[id].hasJumpedoffTotally)
	{
		auto V = BotData[id].JumpToPosition - players[id].vPosition;
		float angle = vec2angle(V.x, -V.y);
		
		if(GetDistance(players[id].vPosition,BotData[id].JumpToPosition) > 0.25f)
		PlayerMove(id, angle);
		BotCorrectAngleNew(id, diff, angle, BotData[id].fAimSpeedCasual, BotData[id].fAimCorrectnessCasual);
	}
	else
	{

	}
}

void dc_match::BotLowFreefallMove(int id, float diff)
{
	if (!BotData[id].hasJumpedoffTotally)
	{
		if (BotData[id].move_path.size() == 0)
		{
			if (GetDistance(players[id].vPosition, BotData[id].JumpToPosition) > 0.25f) {
				BotCalculatePath(id, BotData[id].JumpToPosition);
				BotMoveToNextPoint(id,diff);
			}
		}
		else BotMoveToNextPoint(id,diff);
		//auto V = BotData[id].JumpToPosition - players[id].vPosition;
		//float angle = vec2angle(V.x, -V.y);
		//PlayerMove(id, angle);
	}
	else //In case for an item that can bounce a player in the air
	{

	}
}

bool dc_match::BotCheckHeal(int id, int listid)
{
	if (listid < 13 || listid >18)return false;
	int health = players[id].iHealth;
	int shield = players[id].iShield;

	if (listid == 13 && BotData[id].HealUseMinimums[0] <= health && BotData[id].HealUseMaximums[0] > health)return true;
	if (listid == 14 && BotData[id].HealUseMinimums[1] <= health && BotData[id].HealUseMaximums[1] > health)return true;
	if (listid == 15 && BotData[id].HealUseMinimums[2] <= shield && BotData[id].HealUseMaximums[2] > shield)return true;
	if (listid == 16 && BotData[id].HealUseMinimums[3] <= shield && BotData[id].HealUseMaximums[3] > shield)return true;
	if (listid == 17 && BotData[id].HealUseMinimums[4] <= (health+shield) && BotData[id].HealUseMaximums[4] > (health+shield))return true;
	if (listid == 18 && BotData[id].HealUseMinimums[5] <= (health + shield) && BotData[id].HealUseMaximums[5] > (health + shield))return true;
	return false;
}

int dc_match::BotHasForceHealNearby(int id)
{
	if (players[id].hasFreeSlot() != -1)return -1;
	std::vector<int> ItemList;
	for (int i = 0; i < map.items.size(); i++)
	{
		auto& item = map.items[i];
		if (item.bOwned)continue;
		if (GetDistance(item.vPosition, players[id].vPosition) > BotData[id].fItemRange)continue;
		auto listid = item.ListIndex;
		if (players[id].iHealth < 75 && (listid == 13 || listid == 14 || listid == 17 || listid == 18)) {

			if (IsPointInStorm(players[id].vPosition) && players[id].hasWhiteheal() == -1)
			{
				ItemList.push_back(i);
			}
			else if (IsPointInStorm(players[id].vPosition) && players[id].hasSpecificItem(listid))
			{
				int sl = players[id].hasSpecificItem(listid);
				if ((players[id].Items[sl].iBullets < players[id].Items[sl].iMaxBullets))
				{
					ItemList.push_back(i);
				}
			}
			else if (!IsPointInStorm(players[id].vPosition))
			{
				ItemList.push_back(i);
			}
		}
		else if (players[id].iHealth < 100 && (listid == 14 || listid == 17 || listid == 18)) {
			if (IsPointInStorm(players[id].vPosition) && players[id].hasWhiteheal() == -1)
			{
				ItemList.push_back(i);
			}
			else if (IsPointInStorm(players[id].vPosition) && players[id].hasSpecificItem(listid))
			{
				int sl = players[id].hasSpecificItem(listid);
				if ((players[id].Items[sl].iBullets < players[id].Items[sl].iMaxBullets))
				{
					ItemList.push_back(i);
				}
			}
			else if (!IsPointInStorm(players[id].vPosition))
			{
				ItemList.push_back(i);
			}
		}
		else if (players[id].iShield < 50 && (listid == 15 || listid == 16 || listid == 17 || listid == 18)) { ItemList.push_back(i); }
		else if (players[id].iShield < 100 && (listid == 16 || listid == 17 || listid == 18)) { ItemList.push_back(i); }


	}
	if (ItemList.size() > 0)
	{
		auto itemlistcomp = [=](int a, int b)
		{
			return GetDistance(players[id].vPosition, map.items[a].vPosition) <= GetDistance(players[id].vPosition, map.items[b].vPosition);
		};
		std::sort(ItemList.begin(), ItemList.end(), itemlistcomp);

		//BotData[id].Changables.forceHeal = true;
		//BotData[id].Changables.forceHealHealID = map.items[ItemList[0]].ListIndex;

		return ItemList[0];
		//BotData[id].Changables.DistantTargetType = 2;
		//BotData[id].Changables.DistantTargetPoint = map.items[ItemList[0]].vPosition;

	}
	else return -1;
}

int dc_match::BotHasItemNearby(int id)
{
	std::vector<int> ItemList;
	for (int i = 0; i < map.items.size(); i++)
	{
		auto& item = map.items[i];
		if (item.bOwned)continue;
		if (GetDistance(item.vPosition, players[id].vPosition) > BotData[id].fItemRange)continue;
		if (!players[id].hasWeapon() && GetDistance(item.vPosition, players[id].vPosition) > 1.5f)continue;
		//if (IsPointInStorm(map.items[i].vPosition))continue;
		if (BotIsNeededItem(id, item.ListIndex) != -1)ItemList.push_back(i);

	}
	if (ItemList.size() > 0)
	{
		auto itemlistcomp = [=](int a, int b)
		{
			return GetDistance(players[id].vPosition, map.items[a].vPosition) <= GetDistance(players[id].vPosition, map.items[b].vPosition);
		};
		std::sort(ItemList.begin(), ItemList.end(), itemlistcomp);
		return ItemList[0];
		//BotData[id].Changables.DistantTargetType = 2;
		//BotData[id].Changables.DistantTargetPoint = map.items[ItemList[0]].vPosition;

	}
	else return -1;
}

void dc_match::BotGoToTheItem(int id, int itemid, int force)
{
	if (BotData[id].Changables.DistantTargetType == 2 || BotData[id].Changables.DistantTargetType == 9)return;
	if (force == 0)
	{
		BotData[id].Changables.DistantTargetType = 2;
		BotData[id].Changables.DistantTargetPoint = map.items[itemid].vPosition;
		BotData[id].move_path.clear();
	}
	else
	{
		BotData[id].Changables.DistantTargetType = 9;
		BotData[id].Changables.DistantTargetPoint = map.items[itemid].vPosition;
		BotData[id].move_path.clear();
	}
}

void dc_match::BotNoticePlayers(int id)
{
	for (int i = 0; i <= 100; i++)
	{
		if (players[i].iHealth < 0 || i == id)continue;
		if (GetBotModifiedDistance(players[id].vPosition, players[i].vPosition) > BotData[i].fPlayerRange)continue;
		if (IsIn(BotData[id].Changables.NoticedPlayerIDs, i))continue;
		BotData[id].Changables.NoticedPlayerIDs.push_back(i);
		BotData[id].Changables.NoticedPlayers.push_back(dc_bottarget(i));
	}
	if(!BotData[id].hasJumpedoffTotally)return;
	for (int i = 0; i < BotData[id].Changables.NoticedPlayers.size(); i++)
	{
		int pid = BotData[id].Changables.NoticedPlayers[i].playerid;
		if (BotData[id].Changables.NoticedPlayers[i].NoticeTime.deltaTime() > 1000.f*BotData[id].fEnemyNoticeTime && !IsIn(BotData[id].Changables.TargetedPlayerIDs,pid))
		{

			bool hit0 = false, hit1 = false, hit2 = false, hit3 = false, hit4 = false;
			hit0 = !(map.trace_ray(players[id].vPosition, players[pid].vPosition).hit_object);
			hit1 = !(map.trace_ray(players[id].vPosition, players[pid].vPosition + sf::Vector2f(0.25f, 0.f)).hit_object);
			hit2 = !(map.trace_ray(players[id].vPosition, players[pid].vPosition + sf::Vector2f(0.f, 0.25f)).hit_object);
			hit3 = !(map.trace_ray(players[id].vPosition, players[pid].vPosition - sf::Vector2f(0.25f, 0.f)).hit_object);
			hit4 = !(map.trace_ray(players[id].vPosition, players[pid].vPosition - sf::Vector2f(0.f, 0.25f)).hit_object);

			if (hit0 || hit1 || hit2 || hit3 || hit4)
			{
				BotData[id].Changables.TargetedPlayers.push_back(dc_bottarget(pid));
				BotData[id].Changables.TargetedPlayerIDs.push_back(pid);
			}
		}
	}
}

bool dc_match::BotHasRealTarget(int id)
{
	for (int i = 0; i < BotData[id].Changables.TargetedPlayers.size(); i++)
	{
		if (BotData[id].Changables.TargetedPlayers[i].NoticeTime.deltaTime() > 1000.f*BotData[id].fReactionTime)return true;
	}
	return false;
}

bool dc_match::BotShouldBailOffFight(int id)
{
	if (BotData[id].Changables.NoBailOFClock.deltaTime() <= 30000)return false;
	if (BotData[id].Changables.DistantTargetType == 5)return true;
	if (BotHasRealNoticed(id) && (players[id].iHealth + players[id].iShield) < BotData[id].BailHealthMaxOF)return true;
	return false;
}

bool dc_match::BotShouldBailInFight(int id)
{
	if (BotData[id].Changables.DistantTargetType == 5)return true;
	if (BotHasRealNoticed(id) && (players[id].iHealth + players[id].iShield) < BotData[id].BailHealthMaxIF)return true;
	return false;
}

void dc_match::BotBailOffFight(int id)
{

	if (BotData[id].Changables.DistantTargetType == 5)return;
	float BestBailAngle = BotFindBestBailAngle(id);
	BotData[id].Changables.DistantTargetPoint = players[id].vPosition + BotData[id].Changables.BailDistance * angle2vec(BestBailAngle);
	BotData[id].Changables.DistantTargetType = 5;
	BotData[id].Changables.LastBailClock.Update();
	BotData[id].Changables.BailDistance += 20;
	BotData[id].Changables.fTimeTillThink = BotData[id].fBotThinkDelay;
	for (int i = 0; i < BotData[id].Changables.NoticedPlayers.size(); i++)
		if (BotData[id].Changables.NoticedPlayers[i].NoticeTime.deltaTime() > 1000.f*BotData[id].fEnemyNoticeTime)
			BotData[id].Changables.BailTarget.push_back(BotData[id].Changables.NoticedPlayers[i].playerid);
	BotData[id].move_path.clear();
}

void dc_match::BotBailInFight(int id)
{
	if (BotData[id].Changables.DistantTargetType == 5)return;
	float BestBailAngle = BotFindBestBailAngle(id);
	BotData[id].Changables.DistantTargetPoint = players[id].vPosition + BotData[id].Changables.BailDistance * angle2vec(BestBailAngle);
	BotData[id].Changables.DistantTargetType = 5;
	BotData[id].Changables.LastBailClock.Update();
	BotData[id].Changables.BailDistance += 20;

	for (int i = 0; i < BotData[id].Changables.NoticedPlayers.size(); i++)
		if (BotData[id].Changables.NoticedPlayers[i].NoticeTime.deltaTime() > 1000.f*BotData[id].fEnemyNoticeTime)
			BotData[id].Changables.BailTarget.push_back(BotData[id].Changables.NoticedPlayers[i].playerid);
	BotData[id].move_path.clear();
}

void dc_match::BotAimOnTarget(int id, float diff)
{
	if (players[id].GetCurrentWeapon().iType != 2)
	{
		auto DiffVec = players[BotData[id].Changables.TargetedPlayerIDs[0]].vPosition - players[id].vPosition;
		float Angle = vec2angle(DiffVec.x, -DiffVec.y);
		float Speed = BotData[id].fAimSpeed[players[id].iSelectedWeapon];
		float Correct = BotData[id].fAimCorrectness[players[id].iSelectedWeapon];
		BotCorrectAngleNew(id, diff, Angle, Speed, Correct);
	}
	else
	{
		//With a sniper, projectile travel should also be calculated
		float Distance = GetDistance(players[id].vPosition, players[BotData[id].Changables.TargetedPlayerIDs[0]].vPosition);
		float ProjectileSpeed = players[id].GetCurrentWeapon().fProjectileSpeed;
		float projectileTime = Distance / ProjectileSpeed;
		auto OpponentPosition = players[BotData[id].Changables.TargetedPlayerIDs[0]].vPosition + players[BotData[id].Changables.TargetedPlayerIDs[0]].vVelocity * projectileTime;

		auto DiffVec = OpponentPosition - players[id].vPosition;
		float Angle = vec2angle(DiffVec.x, -DiffVec.y);
		float Speed = BotData[id].fAimSpeed[players[id].iSelectedWeapon];
		float Correct = BotData[id].fAimCorrectness[players[id].iSelectedWeapon];
		BotCorrectAngleNew(id, diff, Angle, Speed, Correct);
	}
}

void dc_match::BotDoDodge(int id)
{

		auto DiffVec = players[BotData[id].Changables.TargetedPlayerIDs[0]].vPosition - players[id].vPosition;
		if (GetDistance(DiffVec, sf::Vector2f()) < 1.5f)return;

		float TargetAngle = vec2angle(DiffVec.x, -DiffVec.y);
		float LeftAngle = TargetAngle - 30.f - 60.f * BotData[id].FightStyleInFight;
		float RightAngle = TargetAngle + 30.f + 60.f * BotData[id].FightStyleInFight;



		if (BotData[id].Changables.SideStepTimeLeft < 0.f)
		{
			BotData[id].Changables.SideStepType++;
			BotData[id].Changables.SideStepType %= 4;
			if (BotData[id].Changables.SideStepType % 2 == 0)
				BotData[id].Changables.SideStepTimeLeft = g_RandomDevice.RandomFloat(BotData[id].StillStayMinTime, BotData[id].StillStayMaxTime);
			else
				BotData[id].Changables.SideStepTimeLeft = g_RandomDevice.RandomFloat(BotData[id].SideStepMinTime, BotData[id].SideStepMaxTime);
		}
		
		
		if (!BotData[id].FightType[players[id].iSelectedWeapon] && BotData[id].Changables.SideStepType % 2 == 0)
		{
			BotData[id].Changables.SideStepTimeLeft = -0.1f;
		}
		if (players[id].GetCurrentWeapon().iBullets <= 0 && BotData[id].Changables.SideStepType % 2 == 0)
		{
			BotData[id].Changables.SideStepTimeLeft = -0.1f;
		}
		if (BotData[id].Changables.SideStepType == 1)
		{
			PlayerMove(id, LeftAngle);
		}
		else if (BotData[id].Changables.SideStepType == 3)
		{
			PlayerMove(id, RightAngle);
		}

	
}

bool dc_match::BotShouldShootWeapon(int id)
{
	auto DiffVec = players[BotData[id].Changables.TargetedPlayerIDs[0]].vPosition - players[id].vPosition;
	float TargetAngle = vec2angle(DiffVec.x, -DiffVec.y);

	float AngDiff = TargetAngle - players[id].fAngle;
	while (AngDiff > 180.f)AngDiff -= 360.f;
	while (AngDiff <= -180.f)AngDiff += 360.f;

	float distance = GetLength(DiffVec);
	float target_total_angle = 2 * (atan(0.25f / distance) * 180 / PI);
	float precision = target_total_angle / players[id].fBloomSize;
	float smallestanglepossible = players[id].GetCurrentWeapon().fBloomMinSize;


	float requiredangle = BotData[id].fAimPrecision[players[id].iSelectedWeapon] * players[id].fBloomSize;

	if ((AngDiff < BotData[id].fAimCorrectness[players[id].iSelectedWeapon] && AngDiff > -BotData[id].fAimCorrectness[players[id].iSelectedWeapon])
		|| (AngDiff < target_total_angle && AngDiff > -target_total_angle))
	{
		if(!BotData[id].FightType[players[id].iSelectedWeapon]
			|| (precision > BotData[id].fAimPrecision[players[id].iSelectedWeapon]) 
			|| requiredangle <= smallestanglepossible 
			|| (BotData[id].Changables.DistantTargetType == 5)
			|| (distance < 2.f)
			|| (BotData[id].Changables.SideStepType % 2 == 0))
		return true;
	}

	return false;
}

void dc_match::BotShoot(int id)
{
	float Inaccuracy = g_RandomDevice.RandomFloat(-BotData[id].InaccuracyMax, BotData[id].InaccuracyMax);

	if (!players[id].GetCurrentWeapon().IsSniper())
	{
		players[id].fAngle += Inaccuracy;
		PlayerShootWeapon(id);
		players[id].fAngle -= Inaccuracy;
	}
	else
	{
		PlayerShootWeapon(id);
	}
}


void dc_match::BotRemoveObstacle(int id, float diff)
{
	auto DiffVec = BotData[id].Changables.DistantTargetPoint - players[id].vPosition;
	float Angle = vec2angle(DiffVec.x, -DiffVec.y);
	float Speed = BotData[id].fAimSpeed[players[id].iSelectedWeapon];
	float Correct = BotData[id].fAimCorrectness[players[id].iSelectedWeapon];
	BotCorrectAngleNew(id, diff, Angle, Speed, Correct);

	float AngDiff = Angle - players[id].fAngle;
	while (AngDiff > 180.f)AngDiff -= 360.f;
	while (AngDiff <= -180.f)AngDiff += 360.f;
	if (AngDiff < BotData[id].fAimCorrectness[players[id].iSelectedWeapon] && AngDiff > -BotData[id].fAimCorrectness[players[id].iSelectedWeapon])PlayerShootWeapon(id);

	//REMOVE
	//camera_follows = id;;
}

bool dc_match::BotReloadWeapons(int id)
{
	if (BotData[id].Changables.movepathBugged)return false;
	for (int i = 0; i < 5; i++)
	{
		if (!players[id].Items[i].bValidated || players[id].Items[i].IsConsumable())continue;
		if (players[id].Items[i].iBullets < players[id].Items[i].iMaxBullets)
		{
			PlayerSwapWeapon(id, i);
			PlayerReloadWeapon(id);
			return true;
		}
	}
	return false;
}

void dc_match::BotThink(int id, float diff)
{
	if (players[id].bOnBus)
		BotJumpoffBus(id); //We check for jump in every BotThink call on the bus
	else
	{
		if (!BotData[id].hasJumpedoffTotally && players[id].fFreeFallHeight > 0.f)BotDescend(id, diff); //Checking for descend every BotThink Call (in the air)
		if (players[id].fFreeFallHeight <= 0.f) {
		
			if (!BotData[id].hasJumpedoffTotally)BotData[id].Changables.NoBailOFClock.Update();
			BotData[id].hasJumpedoffTotally = true;
		}
		if (players[id].fFreeFallHeight > 5.f)BotFreefallMove(id,diff); //If high enough to fly over walls
		else if (players[id].fFreeFallHeight > 0.f)BotLowFreefallMove(id,diff); //If low in the air

		BotNoticePlayers(id); //Checking for players
		BotCheckStuff(id,diff); //Doing a checkup
	
		if (BotData[id].hasJumpedoffTotally)
		{
			if (BotData[id].Changables.fTimeTillThink > 0.f) //To create a thinking delay
			{
				BotData[id].Changables.fTimeTillThink -= diff; 
				return;
			}

			BotCheckOpenChests(id, false); //Checking surrounding chests
			//////////////////////////////////////////////
			/// IN FIGHT
			//////////////////////////////////////////////
			if (BotHasRealTarget(id) && BotHasUsableWeapon(id,GetDistance(players[id].vPosition,players[BotData[id].Changables.TargetedPlayerIDs[0]].vPosition)))
			{
				BotClearUnnecesaryMovepathInFight(id); //No moving to weird positions
				BotAimOnTarget(id, diff); //Aiming
				BotSwapWeaponInFight(id); //Swapping to the most efficient DPS weapon
				
				if (BotShouldBailInFight(id)) //Checking if the situation is bad
				{
					BotBailInFight(id); //If bad, run
					BotDoTheMoveInFight(id, diff);
				}
				else BotDoDodge(id);

				if (BotShouldShootWeapon(id))BotShoot(id);
			}
			//////////////////////////////////////////////
			/// NOT IN FIGHT
			//////////////////////////////////////////////
			else
			{
				//Not interrupting the consumption of a healing item
				if (BotData[id].Changables.bHealing || players[id].fHealTime > 0.f)
				{
					BotDoHeal(id);
					return;
				}


				int bothealresponse = BotShouldHeal(id);
				int force_item_id = BotHasForceHealNearby(id);
				int item_id = (force_item_id == -1)?(BotHasItemNearby(id)):(-1);

				if (BotData[id].Changables.forceHeal);

				else if (BotHasRealNoticed(id) || BotData[id].Changables.DistantTargetType == 6) //Swapping to the most effective weapon
					BotSwapToEmergencyWeapon(id);
				else if (!BotReloadWeapons(id)) //If there is no target, reload the weapons
					BotSwapToJustInCaseWeapon(id); //If weapons are reloaded, swap to the just in case weapon




				if (bothealresponse == 2)BotDoHeal(id); //If the bot has a healing item in the inventory, it uses it up
				else if (BotShouldGoToZone(id) && item_id == -1 && force_item_id == -1)BotGoToZone(id); //If the bot should go to zone and there is no needed item, it goes to zone
				else if (BotShouldBailOffFight(id))BotBailOffFight(id); 
				else if (BotShouldGetAirDrop(id))BotGetAirDrop(id);
				else if (BotShouldCoverAirDrop(id))BotCoverAirDrop(id);
				else if (BotShouldRushOpponent(id))BotRushOpponent(id);
				else if (force_item_id != -1) //If there is a forceheal, the bot should pick it up
					BotGoToTheItem(id, force_item_id, 1);
				else if (item_id != -1) //If there is a needed item, the bot should pick it up
					BotGoToTheItem(id, item_id);
				else if (BotNeedsToLoot(id))BotLoot(id);
				else if (BotCanRaid(id))BotRaid(id);
				BotDoTheMove(id, diff); //Move to the next movepath point

				if (BotData[id].Changables.movepathBugged)
				{
					BotRemoveObstacle(id, diff);
				}
			}
		}


	}

}


//TODO: Wallbreak effect
//TODO: Unreachable point finder