#include "DaiCastle.h"


std::vector<sf::Vector2i> dc_demo_playerdata::GetPreviousChanges(int tick)
{
	std::vector<sf::Vector2i> Return;

	Return.push_back(bBusJumpTick);
	int i = 0;
	for (i = PositionChanges.size() - 1; i >= 0; i--)
	{
		if (PositionChanges[i].x < tick)
		{
			Return.push_back(PositionChanges[i]);
			i = -1;
			break;
		}
	}
	if (i != -1)Return.push_back(PositionChanges[0]);
	for (i = HealthChanges.size() - 1; i >= 0; i--)
	{
		if (HealthChanges[i].x < tick)
		{
			Return.push_back(HealthChanges[i]);
			i = -1;
			break;
		}
	}
	if (i != -1)Return.push_back(HealthChanges[0]);

	for (i = RotChanges.size() - 1; i >= 0; i--)
	{
		if (RotChanges[i].x < tick)
		{
			Return.push_back(RotChanges[i]);
			i = -1;
			break;
		}
	}
	if (i != -1)Return.push_back(RotChanges[0]);

	for (i = WeapChanges.size() - 1; i >= 0; i--)
	{
		if (WeapChanges[i].x < tick)
		{
			Return.push_back(WeapChanges[i]);
			i = -1;
			break;
		}
	}
	if (i != -1)Return.push_back(WeapChanges[0]);

	return Return;
	/*
	
	std::vector<sf::Vector2i> Return;

	if (tick >= bBusJumpTick.x)Return.push_back(bBusJumpTick);
	else Return.push_back(sf::Vector2i(30 * 60 * 64, 0));
	int i = 0;
	for (i = PositionChanges.size()-1; i >= 0; i--)
	{
	if (PositionChanges[i].x < tick)
	{
	Return.push_back(PositionChanges[i]);
	i = -1;
	break;
	}
	}
	if (i != -1)Return.push_back(PositionChanges[0]);
	for (i = HealthChanges.size()-1; i >= 0;i--)
	{
	if (HealthChanges[i].x < tick)
	{
	Return.push_back(HealthChanges[i]);
	i = -1;
	break;
	}
	}
	if (i != -1)Return.push_back(HealthChanges[0]);

	for (i = RotChanges.size()-1; i >= 0;i--)
	{
	if (RotChanges[i].x < tick)
	{
	Return.push_back(RotChanges[i]);
	i = -1;
	break;
	}
	}
	if (i != -1)Return.push_back(RotChanges[0]);

	for (i = WeapChanges.size()-1; i >= 0; i--)
	{
	if (WeapChanges[i].x < tick)
	{
	Return.push_back(WeapChanges[i]);
	i = -1;
	break;
	}
	}
	if (i != -1)Return.push_back(WeapChanges[0]);

	return Return;

	*/
}

sf::Vector2i dc_demo_itemdata::is_alive(int tick)
{
	int closestSpawn = -1;
	for (int i = spawns.size() - 1; i >= 0; i--) //Finds the spawn right before the tick
		if (spawns[i].x < tick) {
			closestSpawn = i; break;
		}
	if (closestSpawn == -1)return sf::Vector2i(-1,0); //Couldn't find an earlier spawn, meaning the item hasn't spawned yet

	int closestDespawn = -1;
	for (int i = 0; i < despawns.size(); i++) //Finds the despawn right after the first spawn
		if (despawns[i] > spawns[closestSpawn].x) {
			closestDespawn = i; break;
		}
	if (closestDespawn == -1)return spawns[closestSpawn]; //Couldn't find the despawn, meaning the item hasn't despawned

	if (despawns[closestDespawn] < tick)return sf::Vector2i(-1, 0); //Spawned - Despawned - Tick
	else return spawns[closestSpawn];
}

void dc_demo_viewer::ProcessDemoData()
{
	for (int i = 0; i < 100; i++)
	{

	}

	float tickTime = 1.f / Demo.MetaData.DemoTickBase;

	for (int i = 0; i < Demo.Ticks.size(); i++)
	{
		for (int j = 0; j < Demo.Ticks[i].Data.size(); j++)
		{
			auto data = Demo.Ticks[i].Data[j];
			switch (*data.getType())
			{
			case DC_DEMO_PLPOSITION: PlayerData[data.toPlayerPosition()->pl].PositionChanges.push_back(sf::Vector2i(i, j));
				break;
			case DC_DEMO_PLHEALTH: PlayerData[data.toPlayerHealth()->pl].HealthChanges.push_back(sf::Vector2i(i, j));
				break;
			case DC_DEMO_BUS_JUMPOUT: PlayerData[data.toPlayerJumpout()->pl].bBusJumpTick = sf::Vector2i(i, j);
				break;
			case DC_DEMO_PLROTATE:
				//ConLog("\n%d,%d    pl: %d", i, j, data.toPlayerRotate()->pl);
				if(data.toPlayerRotate()->pl >= 0 && data.toPlayerRotate()->pl < 100)
					PlayerData[data.toPlayerRotate()->pl].RotChanges.push_back(sf::Vector2i(i, j));
				else ConLog("\n%d,%d    pl: %d", i, j, data.toPlayerRotate()->pl);
				break;
			case DC_DEMO_PLWEAPONCHANGE: PlayerData[data.toPlayerWeaponChange()->pl].WeapChanges.push_back(sf::Vector2i(i, j));
				break;
			case DC_DEMO_CHOPEN: MapData.ChestOpens.push_back(sf::Vector2i(i, j));
				break;
			case DC_DEMO_WEAPONSPAWN: 
				MapData.Items.push_back(dc_demo_itemdata(data.toWeaponSpawn()->listidx));
				Match.map.items.push_back(dc_item(data.toWeaponSpawn()->listidx, data.toWeaponSpawn()->coord));
				break;
			case DC_DEMO_WEAPONDROP:
				MapData.Items[data.toWeaponDrop()->itemidx].spawns.push_back(sf::Vector2i(i, j));
				break;
			case DC_DEMO_WEAPONPICKUP:
				MapData.Items[data.toWeaponPickup()->itemidx].despawns.push_back(i);
				break;
			case DC_DEMO_SHOTEFFECT:
				//dc_shoteffect SE; 
				//SE.start = data.toShotEffect()->start;
				//SE.end = data.toShotEffect()->end;
				//SE.clockBegin = data.toShotEffect()->BeginTime + tickTime*(i-1);
				//ConLog("\nSE: %.f (%d)", SE.clockBegin, i);
				Match.effects.sht_effects.push_back(dc_shoteffect(data.toShotEffect()->start, data.toShotEffect()->end, data.toShotEffect()->BeginTime + tickTime*(i - 1)));
				break;
			case DC_DEMO_TIMEUPDATE:
				MapData.TimeChanges.push_back(sf::Vector2i(i, j));
				break;
			case DC_DEMO_AIRDROPSPAWN:
				MapData.AirDropSpawns.push_back(sf::Vector2i(i, j));
				MapData.AirDropOpens.push_back(sf::Vector2i(12345678, 0));
				break;
			case DC_DEMO_AIRDROPEND:
				MapData.AirDropOpens[data.toAirdropRemove()->airdropindex] = sf::Vector2i(i, j);
				break;
			case DC_DEMO_SERVERTIMEUPDATE:
				Servertime_Updates.push_back(sf::Vector2i(i, j));
				break;
			case DC_DEMO_BREAKWALL:
				MapData.WallBreaks.push_back(sf::Vector2i(i, j));
				break;
			case DC_DEMO_PROJECTILEADD:
				Match.Projectiles.push_back(dc_projectile());
				MapData.ProjectileSpawns.push_back(sf::Vector2i(i, j));
				MapData.ProjectileEnds.push_back(sf::Vector2i(i, j));
				break;
			case DC_DEMO_PROJECTILEDESTRUCT:
				MapData.ProjectileEnds[data.toProjectileEnd()->projectileIndex] = sf::Vector2i(i, j);
				break;
			case DC_DEMO_EXPLOSIVEADD:
				MapData.ExplosiveData.push_back(dc_demo_explosivedata(sf::Vector2i(i,j)));
				Match.Explosives.push_back(dc_explosive());
				Match.Explosives[Match.Explosives.size() - 1].projectiletype = data.toExplosiveAdd()->projectileType;
				break;
			case DC_DEMO_EXPLOSIVEUPDATE:
				MapData.ExplosiveData[data.toExplosiveUpdate()->projectileIndex].updates.push_back(sf::Vector2i(i, j));
				break;
			case DC_DEMO_EXPLOSIVEDESTRUCT:
				MapData.ExplosiveData[data.toExplosiveDestruct()->projectileIndex].end = sf::Vector2i(i, j);
				break;
			case DC_DEMO_ELIMINATION:
				EliminationData.push_back(sf::Vector2i(i, j));
				Match.effects.kilnot_effects.push_back(dc_killnoticeeffect(data.toElimination()->killer, data.toElimination()->target, tickTime*i));
				break;
			}

		}
	}

	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < PlayerData[i].HealthChanges.size()-1; j++)
		{
			auto prevD = PlayerData[i].HealthChanges[j];
			auto nextD = PlayerData[i].HealthChanges[j + 1];

			if (Demo.Ticks[prevD.x].Data[prevD.y].toPlayerHealth()->HP > 0 && Demo.Ticks[nextD.x].Data[nextD.y].toPlayerHealth()->HP <= 0)
			{
				//ConLog("\n%d dies: Tick: %d | %d",i, Demo.Ticks[prevD.x].Data[0].toStartTick()->tick, prevD.x);
				dc_deatheffect DE;
				DE.clockBegin = tickTime*nextD.x;
				auto Changes = PlayerData[i].GetPreviousChanges(nextD.x);
				auto c = Changes[DMPD_ROTCHANGE];
				DE.fRotation = Demo.Ticks[c.x].Data[c.y].toPlayerRotate()->angle;
				DE.iTexture = Demo.MetaData.playerSkins[i];
				
				
				c = Changes[DMPD_POSCHANGE];
				DE.position = Demo.Ticks[c.x].Data[c.y].toPlayerPosition()->vPos;
				Match.effects.dth_effects.push_back(DE);
				ConLog("\n%d dies at %.2f|%.2f (time: %.1f) rot: %.f", i, DE.position.x, DE.position.y, DE.clockBegin,DE.fRotation);
			}
			else if (Demo.Ticks[prevD.x].Data[prevD.y].toPlayerHealth()->Shield > 0 && Demo.Ticks[nextD.x].Data[nextD.y].toPlayerHealth()->Shield <= 0)
			{
				//ConLog("\n%d breaks shield: Tick: %d | %d",i, Demo.Ticks[prevD.x].Data[0].toStartTick()->tick, prevD.x);
				dc_shieldbreakeffect SB;
				SB.clockBegin = tickTime*nextD.x;
				auto Changes = PlayerData[i].GetPreviousChanges(nextD.x);
				auto c = Changes[DMPD_POSCHANGE];
				SB.position = Demo.Ticks[c.x].Data[c.y].toPlayerPosition()->vPos;
				Match.effects.shb_effects.push_back(SB);
			}
		}
	}
}




void dc_demo_viewer::Setup()
{
	//Begin Match Like Normally
	Match.DemoRecord = false;
	Match.Start(100);
	
	//Player Stuff
	ProcessDemoData();
	//Metadata
	for (int i = 0; i < 100; i++)
	{
		sprintf(Match.players[i].szName, Demo.MetaData.playerNames[i]);

		Match.players[i].iSkinTexture = Demo.MetaData.playerSkins[i];
		Match.players[i].iGliderTexture = Demo.MetaData.playerGliders[i];
		Match.players[i].iWeaponWrapTexture = Demo.MetaData.playerWraps[i];
	}
	Match.BusStartPosition = Demo.MetaData.BusStart;
	Match.BusEndPosition = Demo.MetaData.BusEnd;
	Match.BusCurrentPosition = Demo.MetaData.BusBegin;

	for (int i = 0; i < Demo.MetaData.StormPhases; i++)
	{
		Match.StormMids[i] = Demo.MetaData.StormMids[i];
		Match.s_size[i] = Demo.MetaData.StormSizes[i];
		Match.s_times[i] = Demo.MetaData.StormTimes[i];
	}

	float tickTime = 1.f / Demo.MetaData.DemoTickBase;
	DemoTotalTime = tickTime*Demo.Ticks.size();

	RenderingLayers.push_back(dc_demo_renderlayer());
}

int dc_demo_viewer::GetPreviousTick(float time)
{
	float tickTime = 1.f / Demo.MetaData.DemoTickBase;
	int tick = (time+0.001f*tickTime) / tickTime;
	return tick;
}

int dc_demo_viewer::GetNextTick(float time)
{
	return GetPreviousTick(time) + 1;
}

void dc_demo_viewer::JumpToTime(float time)
{
	//Match.ServerTime = time;
	int prev_tick = GetPreviousTick(time);
	int next_tick = prev_tick + 1;
	float tickTime = 1.f / Demo.MetaData.DemoTickBase;
	float timeToTick = time / tickTime;
	float diffFromPrev = time - tickTime*prev_tick;
	
	auto DiffVec = ToUnitVector(Match.BusEndPosition - Match.BusStartPosition)*BUS_TRAVELSPEED;

	Match.BusCurrentPosition = Demo.MetaData.BusBegin + time * DiffVec;

	float TimeCorrection = 0.f;

	for (int i = 0; i < Servertime_Updates.size(); i++)
	{
		if (Servertime_Updates[i].x > prev_tick)
		{
			auto data = Demo.Ticks[Servertime_Updates[i].x].Data[Servertime_Updates[i].y].toServerTime();
			TimeCorrection = data->sv_time - tickTime*Servertime_Updates[i].x;
			break;
		}
	}
	Match.ServerTime = time+TimeCorrection;

	for (int i = 0; i < 100; i++)
	{
		auto prevChanges = PlayerData[i].GetPreviousChanges(prev_tick);
		auto nextChanges = PlayerData[i].GetPreviousChanges(next_tick);

		//Bus Jump;
		if (prevChanges[DMPD_BUSJUMP].x > prev_tick)
		{
			Match.players[i].bOnBus = true;
			Match.players[i].vPosition = Match.BusCurrentPosition;
		}
		else
		{
			//Position;
			Match.players[i].bOnBus = false;
			auto ppCh = prevChanges[DMPD_POSCHANGE];
			auto pnCh = nextChanges[DMPD_POSCHANGE];
			
			if (ppCh.x >= 30 * 60 * 64 || pnCh.x >= 30 * 60 * 64 || ppCh.x < 0 || pnCh.x < 0)
			{

			}
			else
			{

				sf::Vector2f prevPosition = Demo.Ticks[ppCh.x].Data[ppCh.y].toPlayerPosition()->vPos;
				sf::Vector2f nextPosition = Demo.Ticks[pnCh.x].Data[pnCh.y].toPlayerPosition()->vPos;
				sf::Vector2f Position = ((tickTime - diffFromPrev)*prevPosition + diffFromPrev*nextPosition) / tickTime;
				float prevHeight = Demo.Ticks[ppCh.x].Data[ppCh.y].toPlayerPosition()->height;
				float nextHeight = Demo.Ticks[pnCh.x].Data[pnCh.y].toPlayerPosition()->height;
				float Height = ((tickTime - diffFromPrev)*prevHeight + diffFromPrev*nextHeight) / tickTime;
				Match.players[i].vPosition = Position;
				Match.players[i].fFreeFallHeight = Height;
			}

			//Rotation
			auto rpCh = prevChanges[DMPD_ROTCHANGE];
			auto rnCh = nextChanges[DMPD_ROTCHANGE];

			if (rpCh.x >= 30 * 60 * 64 || rnCh.x >= 30 * 60 * 64 || rpCh.x <0 || rnCh.x < 0)
			{

			}
			else
			{


				float prevAngle = Demo.Ticks[rpCh.x].Data[rpCh.y].toPlayerRotate()->angle;
				float nextAngle = Demo.Ticks[rnCh.x].Data[rnCh.y].toPlayerRotate()->angle;
				float aDiff = nextAngle - prevAngle;
				while (aDiff > 180.f)aDiff -= 360.f;
				while (aDiff < -180.f)aDiff += 360.f;

				float Angle = ((tickTime - diffFromPrev)*prevAngle + diffFromPrev*(prevAngle+aDiff)) / tickTime;
				Match.players[i].fAngle = Angle;
			}

			//HP
			auto hpCh = prevChanges[DMPD_HPCHANGE];

			if (hpCh.x >= 30 * 60 * 64 ||hpCh.x < 0)
			{
				Match.players[i].iHealth = 100;
				Match.players[i].iShield = 0;
			}
			else
			{
				auto hData = Demo.Ticks[hpCh.x].Data[hpCh.y].toPlayerHealth();
				Match.players[i].iHealth = hData->HP;
				Match.players[i].iShield = hData->Shield;
			}

			//Weapon

			auto wpCh = prevChanges[DMPD_WPCHANGE];

			if (wpCh.x >= 30 * 60 * 64 || wpCh.x <= 0)
			{
				Match.players[i].GetCurrentWeapon().bValidated = false;
				Match.players[i].Items[0].ListIndex = 0;
				Match.players[i].iSelectedWeapon = 0;
			}
			else
			{
				auto wData = Demo.Ticks[wpCh.x].Data[wpCh.y].toPlayerWeaponChange();
				Match.players[i].iSelectedWeapon = 0;
				Match.players[i].Items[0].bValidated = wData->validated;
				Match.players[i].Items[0].ListIndex = wData->listidx;
				if(Match.players[i].Items[0].bValidated && Match.players[i].Items[0].ListIndex >= 0 && Match.players[i].Items[0].ListIndex < g_Items.size())
					Match.players[i].Items[0].iTexture = g_Items[Match.players[i].Items[0].ListIndex].iTexture;
			}
		}
	}
	for (int i = 0; i < Match.map.chests.size(); i++)
	{
		Match.map.chests[i].bOpen = false;
	}
	for (int j = 0; j < MapData.ChestOpens.size(); j++)
	{
		if (prev_tick > MapData.ChestOpens[j].x)
			Match.map.chests[Demo.Ticks[MapData.ChestOpens[j].x].Data[MapData.ChestOpens[j].y].toChestOpen()->chest].bOpen = true;
	}	
	for (int i = 0; i < MapData.WallBreaks.size(); i++)
	{
		auto da = MapData.WallBreaks[i];
		if (prev_tick < da.x)
		{
			auto data = Demo.Ticks[da.x].Data[da.y].toBreakWall();
			Match.map.lines[data->coord.y].blocks[data->coord.x].walls[data->type].iHealth = 100;
		}
		else
		{
			auto data = Demo.Ticks[da.x].Data[da.y].toBreakWall();
			Match.map.lines[data->coord.y].blocks[data->coord.x].walls[data->type].iHealth = 0;
		}
	}
	for (int i = 0; i < MapData.Items.size(); i++)
	{
		auto alive = MapData.Items[i].is_alive(prev_tick);
		if (alive.x < 0)
		{
			Match.map.items[i].bOwned = true;
		}
		else
		{
			auto data = Demo.Ticks[alive.x].Data[alive.y];
			Match.map.items[i].vPosition = data.toWeaponDrop()->coord;
			Match.map.items[i].bOwned = false;
		}
	}
	//Time
	for (int i = MapData.TimeChanges.size()-1; i>=0;i--)
	{
		if (tickTime * MapData.TimeChanges[i].x < time)
		{
			auto prevD = MapData.TimeChanges[i];
			auto nextD = MapData.TimeChanges[i];

			int CorrigTime = 0;

			if (i == MapData.TimeChanges.size() - 1)
				Match.map.day_time = Demo.Ticks[prevD.x].Data[prevD.y].toTimeUpdate()->daytime;
			else {
				nextD = MapData.TimeChanges[i+1];
				int nextDayTime = Demo.Ticks[nextD.x].Data[nextD.y].toTimeUpdate()->daytime;
				int prevDayTime = Demo.Ticks[prevD.x].Data[prevD.y].toTimeUpdate()->daytime;

				int DayTimeDiff = nextDayTime - prevDayTime;
				while (DayTimeDiff < 0)DayTimeDiff += 7200;

				float totalTime = tickTime*(nextD.x - prevD.x);
				float timeSince = time - (tickTime*prevD.x);

				int DayTime = prevDayTime + (timeSince / totalTime*DayTimeDiff);
				//ConLog("\n%d, %d (diff: %d) -> %d", prevDayTime, nextDayTime, DayTimeDiff, DayTime);
				Match.map.day_time = DayTime;
				
			}

			break;
		}
	}


	//Airdrops
	Match.AirDrops.clear();
	for (int i = 0; i < MapData.AirDropSpawns.size(); i++)
	{
		auto sp = MapData.AirDropSpawns[i];
		auto ep = MapData.AirDropOpens[i];
		if (sp.x < prev_tick && prev_tick <= ep.x)
		{

			dc_airdrop Drop;
			Drop.ClockBegin = tickTime *sp.x;
			Drop.airdropid = i;
			Drop.vPosition = Demo.Ticks[sp.x].Data[sp.y].toAirdropSpawn()->Pos;
			Match.AirDrops.push_back(Drop);
			
		}
	}

	//Projectiles
	for(int i = 0; i < MapData.ProjectileSpawns.size();i++)
	{
		if (MapData.ProjectileSpawns[i].x < timeToTick && timeToTick < MapData.ProjectileEnds[i].x)
		{
			auto data = Demo.Ticks[MapData.ProjectileSpawns[i].x].Data[MapData.ProjectileSpawns[i].y].toProjectileAdd();
			Match.Projectiles[i].projectile_speed = data->projSpeed;
			Match.Projectiles[i].start = data->startPos;
			Match.Projectiles[i].end = data->startPos + sf::Vector2f(cos(data->Angle*PI / 180), -sin(data->Angle*PI / 180));
			Match.Projectiles[i].timeAlive = time - tickTime*MapData.ProjectileSpawns[i].x;
		}
		else
		{
			Match.Projectiles[i].start = sf::Vector2f(-60000, -60000);
			Match.Projectiles[i].projectile_speed = 0;
			Match.Projectiles[i].end =sf::Vector2f(-90000,-90000);
		}

	}

	//Explosives
	{
		for (int i = 0; i < MapData.ExplosiveData.size();i++)
		{
			auto ex = MapData.ExplosiveData[i];
			if (ex.spawn.x < timeToTick && timeToTick < ex.end.x)
			{
				auto prevDD = ex.GetPositionDemoData(prev_tick);
				auto nextDD = ex.GetPositionDemoData(next_tick);

				if (nextDD.x == -1)nextDD = prevDD;
				if (prevDD.x != -1)
				{
					auto prevPosition = Demo.Ticks[prevDD.x].Data[prevDD.y].toExplosiveUpdate()->position;
					auto nextPosition = Demo.Ticks[nextDD.x].Data[nextDD.y].toExplosiveUpdate()->position;

					sf::Vector2f Position = ((tickTime - diffFromPrev)*prevPosition + diffFromPrev*nextPosition) / tickTime;
					Match.Explosives[i].start = Position;
					float angle = 0.f;
					if (nextPosition != prevPosition)angle = vec2angle(nextPosition.x - prevPosition.x, nextPosition.y - prevPosition.y);
					Match.Explosives[i].end = Position + angle2vec(angle);

				}
			}
			else
			{
				Match.Explosives[i].start = sf::Vector2f(-6000, -6000);
			}
		}
	}

	for (int i = 0; i < 100; i++)
		Match.players[i].Stats.iEliminations = 0;

	for (auto e : EliminationData)
		if(e.x < prev_tick)
			Match.players[Demo.Ticks[e.x].Data[e.y].toElimination()->killer].Stats.iEliminations++;
}


void dc_demo_viewer::DrawUI()
{
	DrawKillLeaders();
	DrawTimebar();
	DrawInformation();

	if (vCameraMode == 1)
		DrawPlayerInfo();
}

void dc_demo_viewer::DrawInformation()
{
	char Buffer[64];
	auto vCam = GetCameraPosition();
	if (vCameraMode == 0)
	{
		sprintf(Buffer, "Free camera\n%.1f %.1f", vCam.x, vCam.y);
	}
	else
		sprintf(Buffer, "Following %d\n%.1f %.1f", vCameraPlayerLock, vCam.x, vCam.y);

	_Window::RenderTextB(g_Resolution.x*0.005f, g_Resolution.y*0.2f, Buffer, g_Resolution.y*0.015f, 225, 190, 32, 255);
}

void dc_demo_viewer::DoTimebar()
{
	if (LockInput)return;

	if (g_Mouse.IsBetween(g_Resolution.x*0.05f, g_Resolution.y*0.94f, g_Resolution.x*0.9f, g_Resolution.y*0.02f, g_Mouse.Coords.x, g_Mouse.Coords.y)
		&& g_Mouse.hasJustClicked())
	{
		float percent = ((float)g_Mouse.Coords.x - g_Resolution.x*0.05f) / ((float)g_Resolution.x*0.9f);
		if (percent < 0)percent = 0;
		if (percent > 1)percent = 1;

		ServerTime = percent*DemoTotalTime;
	}
}

void dc_demo_viewer::DoKillLeaders()
{
	auto Leaders = Match.GetKillLeaders();

	for (int i = 0; i < 5; i++)
	{
		if (g_Mouse.IsBetween(g_Resolution.x*0.675f, g_Resolution.y*0.025f + i*g_Resolution.y*0.035f, g_Resolution.x*0.3f, g_Resolution.y*0.03f, g_Mouse.Coords.x, g_Mouse.Coords.y)
			&& g_Mouse.IsClickValid() && g_Mouse.hasReleased() && Match.players[Leaders[i]].iHealth > 0)
		{
			vCameraMode = 1;
			vCameraPlayerLock = Leaders[i];
		}

	}
}

void dc_demo_viewer::DrawKillLeaders()
{
	static sf::Sprite logosSprite;
	static bool bRun = false;
	if (!bRun)
	{
		logosSprite.setTexture(*g_Textures.get(51));
		bRun = true;
	}
	float scale = (0.025f*g_Resolution.y) / 64.f;
	logosSprite.setOrigin(0, 0);
	logosSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));

	auto Leaders = Match.GetKillLeaders();

	for (int i = 0; i < 5; i++)
	{
		logosSprite.setScale(scale, scale);
		
		sf::RectangleShape Rect;
		Rect.setSize(sf::Vector2f(g_Resolution.x*0.3f, g_Resolution.y*0.03f));
		Rect.setPosition(g_Resolution.x*0.675f, g_Resolution.y*0.025f + i*g_Resolution.y*0.035f);
		Rect.setFillColor(sf::Color(36, 64, 255, 96));
		if (Match.players[Leaders[i]].iHealth <= 0)
			Rect.setFillColor(sf::Color(192, 32, 32, 96));
		Rect.setOutlineColor(sf::Color(0, 0, 0, 96));
		Rect.setOutlineThickness(1.f);
		g_Window->draw(Rect);

		auto textLen = _Window::GetTextSize(Match.players[Leaders[i]].szName, g_Resolution.y*0.025f);
		_Window::RenderTextBMiddleC(g_Resolution.x*0.675f, g_Resolution.y*0.025f + i*g_Resolution.y*0.035f, textLen.x, g_Resolution.y*0.03f, Match.players[Leaders[i]].szName, g_Resolution.y*0.025f, 192, 192, 192, 128);
		char Buffer[16]; sprintf(Buffer, "%d", Match.players[Leaders[i]].Stats.iEliminations);

		logosSprite.setPosition(g_Resolution.x*0.975f - scale * 64, g_Resolution.y*0.0275f + i*g_Resolution.y*0.035f);
		g_Window->draw(logosSprite);
		textLen = _Window::GetTextSize(Buffer, g_Resolution.y*0.025f);
		_Window::RenderTextBMiddleC(g_Resolution.x*0.975f-scale*64-textLen.x-g_Resolution.x*0.005f, g_Resolution.y*0.025f + i*g_Resolution.y*0.035f, textLen.x, g_Resolution.y*0.03f, Buffer, g_Resolution.y*0.025f, 192, 192, 192, 128);

	}


	DoKillLeaders();
}

void dc_demo_viewer::DrawTimebar()
{
	float sliderSize = g_Resolution.x*0.005f;

	//Bar
	sf::RectangleShape r;
	r.setSize(sf::Vector2f(g_Resolution.x*0.9f, g_Resolution.y*0.01f));
	r.setPosition(g_Resolution.x*0.5f, g_Resolution.y*0.95f);
	r.setOrigin(0.5f*r.getSize());
	r.setFillColor(sf::Color(192, 192, 192, 64));
	r.setOutlineThickness(1.f);
	r.setOutlineColor(sf::Color(0, 0, 0, 64));
	g_Window->draw(r);

	//Slider
	r.setSize(sf::Vector2f(sliderSize, g_Resolution.y*0.02f));
	r.setOrigin(0.5f*r.getSize());
	float x = g_Resolution.x*0.05f + ((ServerTime / DemoTotalTime)*g_Resolution.x*0.9f);
	r.setPosition(x, g_Resolution.y*0.95f);
	r.setFillColor(sf::Color(255,255,255,192));
	r.setOutlineThickness(1.f);
	r.setOutlineColor(sf::Color(0, 0, 0, 128));
	g_Window->draw(r);

	DoTimebar();


	int S_Time = ServerTime;
	int F_Time = DemoTotalTime;

	int S_Seconds = 0, S_Minutes = 0, F_Seconds = 0, F_Minutes = 0;

	while (S_Time > 60)
	{
		S_Time -= 60;
		S_Minutes++;
	}
	S_Seconds = S_Time;

	while (F_Time > 60)
	{
		F_Time -= 60;
		F_Minutes++;
	}
	F_Seconds = F_Time;

	char TimeBuffer[32];
	sprintf(TimeBuffer, "%d:%s%d / %d:%s%d", S_Minutes, ((S_Seconds > 9) ? "" : "0"), S_Seconds, F_Minutes, ((F_Seconds > 9) ? "" : "0"), F_Seconds);
	_Window::RenderTextBMiddleC(g_Resolution.x*0.5f, g_Resolution.y*0.95f, 0, 0, TimeBuffer, g_Resolution.y*0.02f, 0, 0, 0);


	static sf::Sprite logosSprite;
	static bool bRun = false;
	if (!bRun)
	{
		logosSprite.setTexture(*g_Textures.get(51));
		bRun = true;
	}
	float scale = (0.03f*g_Resolution.y) / 64.f;
	logosSprite.setOrigin(32, 32);

	if (vCameraMode == 1)
	{
		if (vCameraPlayerLock >= 0 && vCameraPlayerLock < 100)
		{
			float tickTime = 1.f / Demo.MetaData.DemoTickBase;
			for (auto e : EliminationData)
			{
				if (Demo.Ticks[e.x].Data[e.y].toElimination()->killer == vCameraPlayerLock)
				{
					logosSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
					logosSprite.setScale(scale, scale);
					float pX = g_Resolution.x*0.05f + (((tickTime*e.x) / DemoTotalTime)*g_Resolution.x*0.9f);
					logosSprite.setPosition(pX, g_Resolution.y*0.95f);
					g_Window->draw(logosSprite);
				}
				else if (Demo.Ticks[e.x].Data[e.y].toElimination()->target == vCameraPlayerLock)
				{
					r.setSize(sf::Vector2f(g_Resolution.x*0.0025f, g_Resolution.y*0.02f));
					r.setOrigin(0.5f*r.getSize());
					float pX = g_Resolution.x*0.05f + (((tickTime*e.x) / DemoTotalTime)*g_Resolution.x*0.9f);
					r.setPosition(pX, g_Resolution.y*0.95f);
					r.setFillColor(sf::Color(192,32,32, 255));
					r.setOutlineThickness(0.f);
					g_Window->draw(r);
				}
			}
		}
	}
}

void dc_demo_viewer::DoPlayerInfo()
{
	int movement = 0;
	float scale = g_Resolution.y*0.06f / 64.f;
	if (g_Mouse.IsBetween(g_Resolution.x*0.25f, g_Resolution.y*0.87f, scale * 32, g_Resolution.y*0.06f, g_Mouse.Coords.x, g_Mouse.Coords.y)
		&& g_Mouse.IsClickValid() && g_Mouse.hasReleased())
		movement = -1;
	else 	if (g_Mouse.IsBetween(g_Resolution.x*0.75f - scale * 32, g_Resolution.y*0.87f, scale * 32, g_Resolution.y*0.06f, g_Mouse.Coords.x, g_Mouse.Coords.y)
		&& g_Mouse.IsClickValid() && g_Mouse.hasReleased())
		movement = 1;

	if (movement != 0)
	{
		do
		{
			vCameraPlayerLock += movement;
			if (vCameraPlayerLock < 0)vCameraPlayerLock = 99;
			if (vCameraPlayerLock > 99)vCameraPlayerLock = 0;
		} while (Match.players[vCameraPlayerLock].iHealth <= 0);

	}
}

void dc_demo_viewer::DrawPlayerInfo()
{
	if (vCameraPlayerLock < 0 || vCameraPlayerLock > 99)return;

	sf::RectangleShape r;
	r.setSize(sf::Vector2f(g_Resolution.x*0.5f, g_Resolution.y*0.06f));
	r.setPosition(g_Resolution.x*0.5f, g_Resolution.y*0.9f);
	r.setOrigin(0.5f*r.getSize());
	r.setFillColor(sf::Color(192, 192, 192, 128));
	g_Window->draw(r);

	for(int i = -1; i <= 1;i++)
		for(int j = -1; j<=1;j++)
			_Window::RenderTextBMiddleC(g_Resolution.x*0.5f+i, g_Resolution.y*0.9f+j, 0, 0, Demo.MetaData.playerNames[vCameraPlayerLock], g_Resolution.y*0.03f, 0,0,0, 255);


	_Window::RenderTextBMiddleC(g_Resolution.x*0.5f, g_Resolution.y*0.9f, 0, 0, Demo.MetaData.playerNames[vCameraPlayerLock], g_Resolution.y*0.03f, 255, 255, 255, 255);


	static sf::Sprite logosSprite;
	static bool bRun = false;
	if (!bRun)
	{
		logosSprite.setTexture(*g_Textures.get(51));
		bRun = true;
	}

	float scale = g_Resolution.y*0.06f / 64.f;

	logosSprite.setScale(scale, scale);
	logosSprite.setOrigin(32, 32);
	logosSprite.setTextureRect(sf::IntRect(64 * 6, 0, 64, 64));
		
	logosSprite.setPosition(g_Resolution.x*0.25f+scale*32, g_Resolution.y*0.9f);

	if (g_Mouse.IsBetween(g_Resolution.x*0.25f, g_Resolution.y*0.87f, scale * 32, g_Resolution.y*0.06f, g_Mouse.Coords.x, g_Mouse.Coords.y)
		&& g_Mouse.IsClickValid() && g_Mouse.isHolding())
		logosSprite.setColor(sf::Color(128,128,128));
	else if (g_Mouse.IsBetween(g_Resolution.x*0.25f, g_Resolution.y*0.87f, scale * 32, g_Resolution.y*0.06f, g_Mouse.Coords.x, g_Mouse.Coords.y))
		logosSprite.setColor(sf::Color(255, 225, 96));
	else logosSprite.setColor(sf::Color(192, 192, 192));

	g_Window->draw(logosSprite);

	logosSprite.setTextureRect(sf::IntRect(64 * 7, 0, 64, 64));
	logosSprite.setPosition(g_Resolution.x*0.75f - scale * 32, g_Resolution.y*0.9f);
	
	if (g_Mouse.IsBetween(g_Resolution.x*0.75f-scale*32, g_Resolution.y*0.87f, scale * 32, g_Resolution.y*0.06f, g_Mouse.Coords.x, g_Mouse.Coords.y)
		&& g_Mouse.IsClickValid() && g_Mouse.isHolding())
		logosSprite.setColor(sf::Color(128, 128, 128));
	else if (g_Mouse.IsBetween(g_Resolution.x*0.75f-scale*32, g_Resolution.y*0.87f, scale * 32, g_Resolution.y*0.06f, g_Mouse.Coords.x, g_Mouse.Coords.y))
		logosSprite.setColor(sf::Color(255, 225, 96));
	else logosSprite.setColor(sf::Color(192, 192, 192));

	g_Window->draw(logosSprite);


	r.setSize(sf::Vector2f(g_Resolution.x*0.5f, g_Resolution.y*0.09f));
	r.setPosition(g_Resolution.x*0.5f, g_Resolution.y*0.8f);
	r.setOrigin(0.5f*r.getSize());
	r.setFillColor(sf::Color(192, 192, 192, 128));
	g_Window->draw(r);
	

	r.setPosition(g_Resolution.x*0.5f, g_Resolution.y*0.78f);
	r.setSize(sf::Vector2f(g_Resolution.x*0.48f, g_Resolution.y*0.03f));
	r.setOrigin(0.5f*r.getSize());
	r.setFillColor(sf::Color(0,0,0, 255));
	g_Window->draw(r);

	r.setPosition(g_Resolution.x*0.5f, g_Resolution.y*0.82f);
	r.setSize(sf::Vector2f(g_Resolution.x*0.48f, g_Resolution.y*0.03f));
	r.setOrigin(0.5f*r.getSize());
	r.setFillColor(sf::Color(0, 0, 0, 255));
	g_Window->draw(r);

	float hplen = (0.01f*g_Resolution.x*0.48f)*Match.players[vCameraPlayerLock].iHealth;
	float shlen = (0.01f*g_Resolution.x*0.48f)*Match.players[vCameraPlayerLock].iShield;

	r.setPosition(g_Resolution.x*0.26f, g_Resolution.y*0.78f);
	r.setSize(sf::Vector2f(hplen, g_Resolution.y*0.03f));
	r.setOrigin(0,0.5f*r.getSize().y);
	r.setFillColor(sf::Color(98, 219, 66, 255));
	g_Window->draw(r);

	r.setPosition(g_Resolution.x*0.26f, g_Resolution.y*0.82f);
	r.setSize(sf::Vector2f(shlen, g_Resolution.y*0.03f));
	r.setOrigin(0, 0.5f*r.getSize().y);
	r.setFillColor(sf::Color(72, 141, 226, 255));
	g_Window->draw(r);

	DoPlayerInfo();
}

sf::Vector2f dc_demo_viewer::GetCameraPosition()
{
	if (vCameraMode == 0)
		return vCameraPosition;
	else return Match.players[vCameraPlayerLock].vPosition;
}

bool dc_demo_viewer::GetKeyStatus(int KEY, bool Continuous)
{
	if (LockInput)return false;
	if (Continuous)
	{
		if (KeyBinds->KeysPrimary[KEY] && g_Keyboard.keys[KeyBinds->KeysPrimary[KEY]])return true;
		if (KeyBinds->KeysSecondary[KEY] && g_Keyboard.keys[KeyBinds->KeysSecondary[KEY]])return true;
	}
	else
	{
		if (KeyBinds->KeysPrimary[KEY] && g_Keyboard.hasJustPressed(KeyBinds->KeysPrimary[KEY]))return true;
		if (KeyBinds->KeysSecondary[KEY] && g_Keyboard.hasJustPressed(KeyBinds->KeysSecondary[KEY]))return true;
	}
	return false;
}

void dc_demo_viewer::DoMove()
{
	if (vCameraMode == 1)
		vCameraPosition = GetCameraPosition();
	else if (!LockInput)
	{
		bool _W = GetKeyStatus(DCK_UP, true), _S = GetKeyStatus(DCK_DOWN, true), _A = GetKeyStatus(DCK_LEFT, true), _D = GetKeyStatus(DCK_RIGHT, true);

		bool move = true;
		float adif = 0.f;


		if (_W && _A)
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

		if (move)
		{
			auto dVec = angle2vec(90 - adif)*(CameraSpeed*timeDiffSinceLastFrame);
			vCameraPosition += sf::Vector2f(dVec.x, -dVec.y);
		}
	}

	if (!LockInput)
	{
		DoScroll();
		DoSpeedUp();
	}

	if (GetKeyStatus(DCK_JUMPOFFBUS, false))
		vCameraMode = !vCameraMode;

}

void dc_demo_viewer::DoSpeedUp()
{
	if (g_Keyboard.keys[VK_ADD] & 1)CameraSpeed += 10;
	if (g_Keyboard.keys[VK_SUBTRACT]& 1)CameraSpeed -= 10;
	if (CameraSpeed < 5)CameraSpeed = 5;
	if (CameraSpeed > 200)CameraSpeed = 200;
}

void dc_demo_viewer::DoScroll()
{
	
	CameraWidth *= pow(1.1, -g_Mouse.scroll);
	if (CameraWidth < 5)CameraWidth = 5;
	else if (CameraWidth > 200)CameraWidth = 200;
}

void dc_demo_viewer::DrawEffectsModified(sf::Vector2f V)
{
	float checkTime = ServerTime;
	for (auto e : Match.effects.sht_effects)
	{
		if(e.clockBegin <= checkTime && checkTime < e.clockBegin + 0.5f)
		e.draw(V.x, V.y, CameraWidth, checkTime);
	}
	for (auto e : Match.effects.dth_effects)
	{
		if (e.clockBegin <= checkTime && checkTime < e.clockBegin + 1.f)
		{
			//ConLog("\n%.1f %.1f", e.position.x, e.position.y);
			e.draw(V.x, V.y, CameraWidth, checkTime);
		}
	}
	for (auto e : Match.effects.shb_effects)
	{
		if (e.clockBegin <= checkTime && checkTime < e.clockBegin + 0.5f)
			e.draw(V.x, V.y, CameraWidth, checkTime);
	}
}

void dc_demo_viewer::DrawKillNoticeEffect()
{
	int KillPose = 0;
	for (auto it : Match.effects.kilnot_effects)
	{
		if (vCameraMode == 0 || it.clockBegin > ServerTime || it.clockBegin + 5.f < ServerTime)continue;

		if (vCameraPlayerLock == it.Killer)KillPose++;

		if (vCameraPlayerLock == it.Killer)
		{
			auto y2 = 0.03f*KillPose*g_Resolution.y;
			float diff = ServerTime - it.clockBegin;
			int alpha = 255;
			if (diff >= 4.f)
			{
				alpha = 255 - (diff - 4.f) * 255 / 1.f;
			}
			else if (diff <= 0.2f)
			{
				alpha = 255 - (0.2f - diff) * 255 / 0.2f;
			}
			char BufferA[64] = "Eliminated ", BufferB[64];
			char BufferC[64];
			sprintf(BufferB, "%s", Match.players[it.Target].szName);
			sprintf(BufferC, "Eliminated %s", Match.players[it.Target].szName);

			auto Dims = _Window::GetTextSize(BufferC, g_Resolution.y * 0.03f);
			auto Dims2 = _Window::GetTextSize(BufferA, g_Resolution.y * 0.03f);
			_Window::RenderTextB(g_Resolution.x*0.5f - Dims.x*0.5f, g_Resolution.y*0.65f + y2, BufferA, g_Resolution.y*0.03f, 222, 222, 222, alpha);

			for (int i = -1; i <= 1; i++)
				for (int j = -1; j <= 1; j++)
					_Window::RenderTextB(g_Resolution.x*0.5f - Dims.x* 0.5f + Dims2.x + i, g_Resolution.y*0.65f + y2 + i, BufferB, g_Resolution.y*0.03f, 0, 0, 0, 0.00392156862*(alpha*alpha));


			_Window::RenderTextB(g_Resolution.x*0.5f - Dims.x* 0.5f + Dims2.x, g_Resolution.y*0.65f + y2, BufferB, g_Resolution.y*0.03f, 225, 180, 32, alpha);


		}
	}
}

void dc_demo_viewer::DrawEffectsModified(dc_demo_renderlayer* R,sf::Vector2f V)
{
	float checkTime = ServerTime;
	if (R->AllowShootEffects)
		for (auto e : Match.effects.sht_effects)
		{
			if (e.clockBegin <= checkTime && checkTime < e.clockBegin + 0.5f)
				e.draw(R->T,V.x, V.y, CameraWidth, checkTime);
		}

	if (R->AllowDamageEffects)
	{
		for (auto e : Match.effects.dth_effects)
		{
			if (e.clockBegin <= checkTime && checkTime < e.clockBegin + 1.f)
			{
				//ConLog("\n%.1f %.1f", e.position.x, e.position.y);
				e.draw(R->T, V.x, V.y, CameraWidth, checkTime);
			}
		}
		for (auto e : Match.effects.shb_effects)
		{
			if (e.clockBegin <= checkTime && checkTime < e.clockBegin + 0.5f)
				e.draw(R->T, V.x, V.y, CameraWidth, checkTime);
		}
	}
}

void dc_demo_viewer::DrawOnRenderLayer(dc_demo_viewer* DV, int layer)
{

	auto cam = DV->GetCameraPosition();
	auto V = DV->Match.map.screen_to_world(cam.x, cam.y, DV->CameraWidth, g_Resolution.x*0.5f, g_Resolution.y*0.5f);

	auto& r = DV->RenderingLayers[layer];

	if (r.T == nullptr) {
		r.T = new sf::RenderTexture;
		r.T->create(g_Resolution.x, g_Resolution.y);
	}
	r.T->clear(r.BackgroundColor);
	DV->Match.map.draw(r.T, V.x, V.y, DV->CameraWidth, r.AllowMap, r.AllowChests, r.AllowShadows);
	if (r.AllowChests)DV->Match.DrawAirDrop(r.T, V);
	if (r.AllowItems)DV->Match.map.drawitems(r.T, V.x, V.y, DV->CameraWidth);
	if (r.AllowPlayers)DV->Match.DrawPlayers(r.T, V);
	if (r.AllowExplosives)DV->Match.DrawExplosives(r.T, V);
	if (r.AllowShootEffects)DV->Match.DrawProjectiles(r.T, V);
	DV->DrawEffectsModified(&r, V);
	if (r.AllowStorm)DV->Match.DrawStorm(r.T, V);
	if (r.AllowPlayers)DV->Match.DrawBus(r.T, V);
	r.T->display();
}
#include <thread>



void dc_demo_viewer::Record()
{


	//ConLog("\nRecording");
	for (int i = 0; i < RenderingLayers.size(); i++)
	{
		if (!RenderingLayers[i].Should_Export)continue;

		char Buf[260];
		sprintf(Buf, "%sRecord", appLocation.c_str());
		_mkdir(Buf);
		sprintf(Buf, "%s\\take%d", Buf, Takes);
		_mkdir(Buf);
		sprintf(Buf, "%s\\%s", Buf, RenderingLayers[i].Name);
		_mkdir(Buf);

		char FileName[260];
		sprintf(FileName, "%sRecord\\take%d\\%s\\%s%s%s%s%d.png", appLocation.c_str(), Takes, RenderingLayers[i].Name, (Frame < 10000 ? "0" : ""), (Frame < 1000 ? "0" : ""), (Frame < 100 ? "0" : ""), (Frame < 10 ? "0" : ""), Frame);
		RenderingLayers[i].T->getTexture().copyToImage().saveToFile(FileName);
		ConLog("\nexporting %s", FileName);
	}
	Frame++;
}

void dc_demo_viewer::Do()
{
	//MoveTime
	static dc_clock Clock;
	if (Clock.deltaTime() > 500)Clock.Update();

	timeDiffSinceLastFrame = 0.001f*Clock.deltaTime();
	Clock.Update();


	//Locking to have a perfect framerate for the demo
	//The actual framerate might differ
	if (g_Config.demo_framerate.Value > 0.5f)
	{
		ServerTime += 1.f / g_Config.demo_framerate.Value;
	}
	else if (g_Config.demo_timescale.Value > 0.f) //Locking to have a perfect timescale
		ServerTime += timeDiffSinceLastFrame * g_Config.demo_timescale.Value;

	//ServerTime += timeDiffSinceLastFrame;
	//If the demo is over, it goes back to its beginning
	if (ServerTime > DemoTotalTime)ServerTime = 0.f;




	JumpToTime(ServerTime);
	auto cam = GetCameraPosition();
	auto V = Match.map.screen_to_world(cam.x, cam.y, CameraWidth, g_Resolution.x*0.5f, g_Resolution.y*0.5f);
	Match.camera_width = CameraWidth;
	/*
	Match.DrawMap(V);
	Match.map.drawitems(V.x, V.y, CameraWidth);
	Match.DrawPlayers(V);
	Match.DrawBus(V);
	Match.DrawProjectiles(V);
	Match.DrawExplosives(V);
	DrawEffectsModified(V);
	Match.DrawStorm(V);
	*/

	for (int i = 0; i < RenderingLayers.size(); i++)
	{
		DrawOnRenderLayer(this, i);
		if (!RenderingLayers[i].Should_Render)continue;
		sf::Sprite Sprite;
		Sprite.setTexture(RenderingLayers[i].T->getTexture());
		g_Window->draw(Sprite);
	}
	DrawKillNoticeEffect();
	/*std::thread* F = new std::thread[RenderingLayers.size()];

	for (int i = 0; i < RenderingLayers.size(); i++)
	{
		std::thread A(DrawOnRenderLayer, this,i);
		F[i].swap(A);
	}

	for (int i = 0; i < RenderingLayers.size(); i++)
		if(F[i].joinable())F[i].join();
	delete[]F;
	*/

	if (Recording)
		Record();

	DrawUI();

	DoMove();
	//printf("\nServerTime: %.1f/%.1f (tb: %d)", ServerTime,DemoTotalTime,Demo.MetaData.DemoTickBase);

}