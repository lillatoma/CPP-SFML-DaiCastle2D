#include "DaiCastle.h"

void dc_match::Demo_CreateSnapshotPointers()
{
	for (int i = 0; i < 128; i++)Demo_Snapshots.push_back(nullptr);
}

void dc_match::Demo_LoopSnapshots()
{
	if (Demo_Snapshots[0] == nullptr)
	{
		for (int i = 0; i < 127; i++)
		{
			Demo_Snapshots[i] = Demo_Snapshots[i + 1];
		}
		Demo_Snapshots[127] = nullptr;
	}

}

void dc_match::Demo_SnapshotUpdateProjectileAdd(sf::Vector2f spawn, float angle, float projspeed)
{
	if (DemoRecord != 1)return;
	dc_demo_data Data;
	*Data.getType() = DC_DEMO_PROJECTILEADD;
	Data.toProjectileAdd()->Angle = angle;
	Data.toProjectileAdd()->startPos = spawn;
	Data.toProjectileAdd()->projSpeed = projspeed;

	Demo_NewestSnapshot.DataCont.push_back(Data);
}

void dc_match::Demo_SnapshotProjectileEnd(int index)
{
	if (DemoRecord != 1)return;
	dc_demo_data Data;
	*Data.getType() = DC_DEMO_PROJECTILEDESTRUCT;
	Data.toProjectileEnd()->projectileIndex = index;


	Demo_NewestSnapshot.DataCont.push_back(Data);
}

void dc_match::Demo_SnapshotUpdateExplosiveAdd(int projtype)
{
	if (DemoRecord != 1)return;
	dc_demo_data Data;
	*Data.getType() = DC_DEMO_EXPLOSIVEADD;
	Data.toExplosiveAdd()->projectileType = projtype;


	Demo_NewestSnapshot.DataCont.push_back(Data);
}

void dc_match::Demo_SnapshotUpdateExplosives()
{
	if (DemoRecord != 1)return;
	for (int i = 0; i < Explosives.size(); i++)
	{
		dc_demo_data Data;
		*Data.getType() = DC_DEMO_EXPLOSIVEUPDATE;
		Data.toExplosiveUpdate()->projectileIndex = Explosives[i].ExplosiveIndex;
		Data.toExplosiveUpdate()->position = Explosives[i].start;

		Demo_NewestSnapshot.DataCont.push_back(Data);
	}
}

void dc_match::Demo_SnapshotUpdateExplosiveRemove(int projindex)
{
	if (DemoRecord != 1)return;
	dc_demo_data Data;
	*Data.getType() = DC_DEMO_EXPLOSIVEDESTRUCT;
	Data.toExplosiveDestruct()->projectileIndex = projindex;


	Demo_NewestSnapshot.DataCont.push_back(Data);
}



void dc_match::Demo_SnapshotUpdateWallbreak(sf::Vector2i coord, int wall)
{
	if (DemoRecord != 1)return;
	dc_demo_data Data;
	*Data.getType() = DC_DEMO_BREAKWALL;
	Data.toBreakWall()->coord = coord;
	Data.toBreakWall()->type = wall;
	Demo_NewestSnapshot.DataCont.push_back(Data);
}

void dc_match::Demo_SnapshotUpdateElimination(int killer, int target)
{
	if (DemoRecord != 1)return;
	dc_demo_data Data;
	*Data.getType() = DC_DEMO_ELIMINATION;
	Data.toElimination()->killer = killer;
	Data.toElimination()->target = target;
	Demo_NewestSnapshot.DataCont.push_back(Data);
}

void dc_match::Demo_SnapshotUpdateAirdropSpawn(sf::Vector2f spawn, int ADindex)
{
	if (DemoRecord != 1)return;
	dc_demo_data Data;
	*Data.getType() = DC_DEMO_AIRDROPSPAWN;
	Data.toAirdropSpawn()->Pos = spawn;
	Data.toAirdropSpawn()->airdropindex = ADindex;
	Demo_NewestSnapshot.DataCont.push_back(Data);
}

void dc_match::Demo_SnapshotUpdateAirdropRemove(int ADindex)
{
	if (DemoRecord != 1)return;
	dc_demo_data Data;
	*Data.getType() = DC_DEMO_AIRDROPEND;
	Data.toAirdropRemove()->airdropindex = ADindex;
	Demo_NewestSnapshot.DataCont.push_back(Data);
}


void dc_match::Demo_SnapshotUpdateItemSpawn(int demoitemidx, int listix, sf::Vector2f p)
{
	if (DemoRecord != 1)return;
	dc_demo_data Data;
	*Data.getType() = DC_DEMO_WEAPONSPAWN;
	Data.toWeaponSpawn()->coord = p;
	Data.toWeaponSpawn()->itemidx = demoitemidx;
	Data.toWeaponSpawn()->listidx = listix;
	Demo_NewestSnapshot.DataCont.push_back(Data);
}

void dc_match::Demo_SnapshotUpdateWeaponShot(sf::Vector2f start, sf::Vector2f end, float time)
{
	if (DemoRecord != 1)return;
	dc_demo_data Data;
	*Data.getType() = DC_DEMO_SHOTEFFECT;
	Data.toShotEffect()->start = start;
	Data.toShotEffect()->end = end;
	Data.toShotEffect()->BeginTime = time - lastTickTime;
	Demo_NewestSnapshot.DataCont.push_back(Data);
}

void dc_match::Demo_SnapshotUpdateItemPickup(int demoitemidx)
{
	if (DemoRecord != 1)return;
	dc_demo_data Data;
	*Data.getType() = DC_DEMO_WEAPONPICKUP;
	Data.toWeaponPickup()->itemidx= demoitemidx;
	Demo_NewestSnapshot.DataCont.push_back(Data);
}
void dc_match::Demo_SnapshotUpdateItemDrop(int demoitemidx, sf::Vector2f p)
{
	if (DemoRecord != 1)return;
	dc_demo_data Data;
	*Data.getType() = DC_DEMO_WEAPONDROP;
	Data.toWeaponDrop()->itemidx = demoitemidx;
	Data.toWeaponDrop()->coord = p;
	Demo_NewestSnapshot.DataCont.push_back(Data);
}

void dc_match::Demo_SnapshotUpdateChest(int i)
{
	if (DemoRecord != 1)return;
	Demo_NewestSnapshot.ChestOpens.push_back(i);
}

void dc_match::Demo_SnapshotUpdatePlayers()
{
	for (int i = 0; i < 100; i++)
		Demo_NewestSnapshot.players[i] = players[i];
}

void dc_match::Demo_CreateSnapshot()
{
	Demo_SnapshotUpdatePlayers(); //Saves player information into snapshot
	Demo_NewestSnapshot.DAYTIME = map.day_time;
	if (TicksTotal % (2 * DemoTickBase) == 0)Demo_NewestSnapshot.KeyFrame = true;
	Demo_NewestSnapshot.Tick = TicksTotal;
	Demo_NewestSnapshot.ServerTime = ServerTime;
	int SmallIndex = 0;
	//for (int i = 0; i < 127;i++)
	//	if (Demo_Snapshots[i] == nullptr) { SmallIndex = i; break; }

	for (int i = 127; i >= 0; i--)
	{
		if (Demo_Snapshots[i] != nullptr) //Saving to the first available slot
		{
			SmallIndex = (i + 1); break;
		}
	}

	auto new_Snap = new dc_ticksnapshot;




	*new_Snap = Demo_NewestSnapshot;

	Demo_NewestSnapshot = dc_ticksnapshot();
	Demo_Snapshots[SmallIndex] = new_Snap;
	TicksTotal++;
}

int dc_demo_metadata::GetSizeOf()
{
	int Size = sizeof(int); //First 4 bytes: Size of Metadata ~ the metadata of the metadata
	Size += sizeof(int); //TickBase
	Size += 3 * sizeof(sf::Vector2f); //Bus Stuff;
	Size += sizeof(int); //How Many Storm Phases
	Size += sizeof(sf::Vector2f)*StormMids.size(); //Variable of Storm
	Size += sizeof(float)*StormSizes.size(); //Variable of Storm
	Size += sizeof(float)*StormTimes.size();
	Size += sizeof(char) * 64 * 100; //Playernames
	Size += sizeof(int) * 3 * 100; //Player skin data

	return Size;
}

void dc_demo_metadata::Setup(void* N)
{
	auto M = (dc_match*)N;
	DemoTickBase = M->DemoTickBase;
	BusStart = M->BusStartPosition;
	BusBegin = M->BusCurrentPosition;
	BusEnd = M->BusEndPosition;
	StormPhases = 18;
	for (int i = 0; i < StormPhases; i++)
	{
		ConLog("%d", i);
		StormMids.push_back(M->StormMids[i]);
		StormSizes.push_back(M->s_size[i]);
		StormTimes.push_back(M->s_times[i]);
	}
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 64; j++)
			playerNames[i][j] = '\0';

		sprintf(playerNames[i], M->players[i].szName);
		playerSkins[i] = M->players[i].iSkinTexture;
		playerGliders[i] = M->players[i].iGliderTexture;
		playerWraps[i] = M->players[i].iWeaponWrapTexture;
	}
}

char* dc_demo_metadata::GetPrinted(int* Size)
{
	*Size = GetSizeOf();

	char* buffer = new char[*Size];
	
	int xPos = 0;
	*(int*)(buffer + xPos) = *Size; xPos += sizeof(int);
	*(int*)(buffer + xPos) = DemoTickBase; xPos += sizeof(int);
	*(sf::Vector2f*)(buffer + xPos) = BusStart; xPos += sizeof(sf::Vector2f);
	*(sf::Vector2f*)(buffer + xPos) = BusEnd; xPos += sizeof(sf::Vector2f);
	*(sf::Vector2f*)(buffer + xPos) = BusBegin; xPos += sizeof(sf::Vector2f);
	*(int*)(buffer + xPos) = StormPhases; xPos += sizeof(int);
	for (int i = 0; i < StormPhases; i++)
	{
		*(sf::Vector2f*)(buffer + xPos) = StormMids[i]; xPos += sizeof(sf::Vector2f);
		*(float*)(buffer + xPos) = StormSizes[i]; xPos += sizeof(float);
		*(float*)(buffer + xPos) = StormTimes[i]; xPos += sizeof(float);
	}
	for (int i = 0; i < 100; i++)
	{
		sprintf(buffer + xPos, playerNames[i]); xPos += 64;
		*(int*)(buffer + xPos) = playerSkins[i]; xPos += sizeof(int);
		*(int*)(buffer + xPos) = playerGliders[i]; xPos += sizeof(int);
		*(int*)(buffer + xPos) = playerWraps[i]; xPos += sizeof(int);
	}

	return buffer;
}

int dc_demo_metadata::ReadFrom(char* p)
{
	int xPos = 0;
	int Size = 0;
	Size = *(int*)(p + xPos); xPos += sizeof(int);
	DemoTickBase = *(int*)(p + xPos); xPos += sizeof(int);
	BusStart = *(sf::Vector2f*)(p + xPos); xPos += sizeof(sf::Vector2f);
	BusEnd = *(sf::Vector2f*)(p + xPos); xPos += sizeof(sf::Vector2f);
	BusBegin = *(sf::Vector2f*)(p + xPos); xPos += sizeof(sf::Vector2f);
	StormPhases = *(int*)(p + xPos); xPos += sizeof(int);
	for (int i = 0; i < StormPhases; i++)
	{
		StormMids.push_back(*(sf::Vector2f*)(p + xPos)); xPos += sizeof(sf::Vector2f);
		StormSizes.push_back( *(float*)(p + xPos)); xPos += sizeof(float);
		StormTimes.push_back(*(float*)(p + xPos)); xPos += sizeof(float);
	}
	for (int i = 0; i < 100; i++)
	{
		sprintf(playerNames[i], "%.*s", 64, p + xPos); xPos += 64;
		playerSkins[i] = *(int*)(p + xPos); xPos += sizeof(int);
		playerGliders[i] = *(int*)(p + xPos); xPos += sizeof(int);
		playerWraps[i] = *(int*)(p + xPos); xPos += sizeof(int);
	}

	return Size;
}

void dc_match::Demo_Convert(dc_match* m, dc_demo_metadata Metadata)
{
	dc_demo Demo;
	//ConLog("\nDemo Converting started");

	dc_ticksnapshot LastSnapShot; //For comparing two snapshots
	while (!m->Demo_ShouldEnd)
	{
		while (m->Demo_Snapshots[0] == nullptr)
		{
			if (m->Demo_ShouldEnd)break;
			Sleep(1); //Without this Sleep, the loop got stuck, it also reduces CPU load on this thread
		}
		if (m->Demo_ShouldEnd)break;
		auto &pointer = m->Demo_Snapshots[0];
		auto previouspointer = &LastSnapShot;
		if (pointer->Tick == 0)previouspointer = pointer;
		//ConLog("\nDemo Converting tick %d/%d",pointer->Tick,m->TicksTotal);
		dc_demo_tick Tick(pointer->Tick);
		
		if (pointer->KeyFrame) //In a keyframe, every information is updated for the players, and servertime and daytime is updated
		{
			dc_demo_data KF;
			KF.toKeyframe()->tick = pointer->Tick;
			Tick.Data.push_back(KF);

			for (int i = 0; i < 100; i++)
			{

				dc_demo_data Pos_Info;
				*Pos_Info.getType() = DC_DEMO_PLPOSITION;
				Pos_Info.toPlayerPosition()->vPos = pointer->players[i].vPosition;
				Pos_Info.toPlayerPosition()->height = pointer->players[i].fFreeFallHeight;
				Pos_Info.toPlayerPosition()->pl = i;
				Tick.Data.push_back(Pos_Info);

				dc_demo_data HP_Info;
				*HP_Info.getType() = DC_DEMO_PLHEALTH;
				HP_Info.toPlayerHealth()->HP = pointer->players[i].iHealth;
				HP_Info.toPlayerHealth()->Shield = pointer->players[i].iShield;
				HP_Info.toPlayerHealth()->pl = i;

				Tick.Data.push_back(HP_Info);

				dc_demo_data Rot_Info;
				*Rot_Info.getType() = DC_DEMO_PLROTATE;
				Rot_Info.toPlayerRotate()->pl = i;
				Rot_Info.toPlayerRotate()->angle = pointer->players[i].fAngle;

				Tick.Data.push_back(Rot_Info);

				dc_demo_data Swap_Info;
				*Swap_Info.getType() = DC_DEMO_PLWEAPONCHANGE;
				Swap_Info.toPlayerWeaponChange()->pl = i;
				Swap_Info.toPlayerWeaponChange()->listidx = pointer->players[i].GetCurrentWeapon().ListIndex;
				Swap_Info.toPlayerWeaponChange()->validated = pointer->players[i].GetCurrentWeapon().bValidated;
				Tick.Data.push_back(Swap_Info);

				if (previouspointer->players[i].bOnBus && !pointer->players[i].bOnBus)
				{
					dc_demo_data JumpInfo;
					JumpInfo.toPlayerJumpout()->pl = i;
					*JumpInfo.getType() = DC_DEMO_BUS_JUMPOUT;
					Tick.Data.push_back(JumpInfo);
				}

			}
			dc_demo_data Sun_Data;
			*Sun_Data.getType() = DC_DEMO_TIMEUPDATE;
			Sun_Data.toTimeUpdate()->daytime = pointer->DAYTIME;
			Tick.Data.push_back(Sun_Data);

			dc_demo_data Server_Data;
			*Server_Data.getType() = DC_DEMO_SERVERTIMEUPDATE;
			Server_Data.toServerTime()->sv_time = pointer->ServerTime;
			Tick.Data.push_back(Server_Data);


		}
		else
		{
			for (int i = 0; i < 100; i++)
			{
				dc_demo_data HP_Info;
				dc_demo_data Pos_Info;
				if (!previouspointer->players[i].bOnBus)
				{
					if (pointer->players[i].vPosition != previouspointer->players[i].vPosition || pointer->players[i].fFreeFallHeight != previouspointer->players[i].fFreeFallHeight)
					{
						Pos_Info.toPlayerPosition()->vPos = pointer->players[i].vPosition;
						Pos_Info.toPlayerPosition()->pl = i;
						Pos_Info.toPlayerPosition()->height = pointer->players[i].fFreeFallHeight;
						*Pos_Info.getType() = DC_DEMO_PLPOSITION;
						Tick.Data.push_back(Pos_Info);
					}
					if (pointer->players[i].iHealth != previouspointer->players[i].iHealth
						|| pointer->players[i].iShield != previouspointer->players[i].iShield)
					{
						dc_demo_data HP_Info;
						HP_Info.toPlayerHealth()->HP = pointer->players[i].iHealth;
						HP_Info.toPlayerHealth()->Shield = pointer->players[i].iShield;
						HP_Info.toPlayerHealth()->pl = i;
						*HP_Info.getType() = DC_DEMO_PLHEALTH;
						Tick.Data.push_back(HP_Info);

					}
					if (pointer->players[i].fAngle != previouspointer->players[i].fAngle)
					{
						dc_demo_data Rot_Info;
						*Rot_Info.getType() = DC_DEMO_PLROTATE;
						Rot_Info.toPlayerRotate()->pl = i;
						Rot_Info.toPlayerRotate()->angle = pointer->players[i].fAngle;

						Tick.Data.push_back(Rot_Info);
					}
					if (pointer->players[i].GetCurrentWeapon().bValidated != previouspointer->players[i].GetCurrentWeapon().bValidated ||
						pointer->players[i].GetCurrentWeapon().ListIndex != previouspointer->players[i].GetCurrentWeapon().ListIndex)
					{
						dc_demo_data Swap_Info;
						*Swap_Info.getType() = DC_DEMO_PLWEAPONCHANGE;
						Swap_Info.toPlayerWeaponChange()->pl = i;
						Swap_Info.toPlayerWeaponChange()->listidx = pointer->players[i].GetCurrentWeapon().ListIndex;
						Swap_Info.toPlayerWeaponChange()->validated = pointer->players[i].GetCurrentWeapon().bValidated;
						Tick.Data.push_back(Swap_Info);
					}
				}
				else if (previouspointer->players[i].bOnBus && !pointer->players[i].bOnBus)
				{
					dc_demo_data JumpInfo;
					JumpInfo.toPlayerJumpout()->pl = i;
					*JumpInfo.getType() = DC_DEMO_BUS_JUMPOUT;
					Tick.Data.push_back(JumpInfo);

					dc_demo_data Pos_Info;
					Pos_Info.toPlayerPosition()->vPos = pointer->players[i].vPosition;
					Pos_Info.toPlayerPosition()->pl = i;
					*Pos_Info.getType() = DC_DEMO_PLPOSITION;
					Tick.Data.push_back(Pos_Info);
				}
			}

		}
		//Chest Opens
		for (auto ind : pointer->ChestOpens)
		{
			dc_demo_data ChInfo;
			*ChInfo.getType() = DC_DEMO_CHOPEN;
			ChInfo.toChestOpen()->chest = ind;
			Tick.Data.push_back(ChInfo);
		}
		//Weapon Spawns
		for (auto d : pointer->DataCont)
			Tick.Data.push_back(d);



		Demo.Ticks.push_back(Tick);
		LastSnapShot = *pointer;
		delete pointer;
		pointer = nullptr;
	}

	for (int i = 0; i < 128; i++)
	{
		if (m->Demo_Snapshots[i] != nullptr)delete m->Demo_Snapshots[i];
	}
	//From this point, the match pointer will not be used, so it can be flagged for deletion
	m->canDelete = true;

	int mDataSize;
	auto metadataPrint = Metadata.GetPrinted(&mDataSize);

	int TotalData = 4 + mDataSize;
	for (auto tick : Demo.Ticks)
	{
		for (auto data : tick.Data)
		{
			TotalData += data.size();
		}
	}
	char* DemoFile = new char[TotalData];

	int WriterPosition = 0;

	for (unsigned int t = 0; t < mDataSize; t++)
	{
		DemoFile[WriterPosition] = metadataPrint[t];
		WriterPosition++;
	}

	for (int t = 0; t < Demo.Ticks.size(); t++)
	{
		auto &tick = Demo.Ticks[t];
		for (int d = 0; d < tick.Data.size(); d++)
		{
			auto &data = tick.Data[d];
			for (int c = 0; c < data.size(); c++)
			{
				DemoFile[WriterPosition] = data.info[c];
				WriterPosition++;
			}
		}
	}

	file_t F;
	F.loc_in_mem = DemoFile;
	F.size = TotalData;

	char FolderBuffer[260];
	sprintf(FolderBuffer, "%sdemos", appLocation.c_str());
	_mkdir(FolderBuffer);

	std::time_t t = std::time(0);   // get time now
	std::tm* now = std::localtime(&t);



	char NameBuffer[260];
	//sprintf(NameBuffer, "%sdemos\\demo_%d%d%d%d-%d%d%d%d-%d%d%d%d-%d%d%d%d.dem", appLocation.c_str(), Random(0, 9), Random(0, 9), Random(0, 9), Random(0, 9), Random(0, 9), Random(0, 9), Random(0, 9), Random(0, 9), Random(0, 9), Random(0, 9), Random(0, 9), Random(0, 9), Random(0, 9), Random(0, 9), Random(0, 9), Random(0, 9));
	//Saving the current time as demoname
	sprintf(NameBuffer, "%sdemos\\demo_%d-%s%d-%s%d-%s%d-%s%d-%s%d.dem",
		appLocation.c_str(), now->tm_year + 1900, (now->tm_mon < 9 ? "0" : ""), now->tm_mon+1, (now->tm_mday < 10 ? "0" : ""), now->tm_mday, (now->tm_hour < 10 ? "0" : ""), now->tm_hour, (now->tm_min < 10 ? "0" : ""), now->tm_min, (now->tm_sec < 10 ? "0" : ""), now->tm_sec);
	F.Dump(NameBuffer);
	//Freeing memory
	delete[] F.loc_in_mem;
	delete[] metadataPrint;
}

void dc_demo::convert_back(file_t F)
{
	auto p = F.loc_in_mem;
	auto s = F.size;

	ConLog("\n File: %d %d", p, s);


	int mDataSize = MetaData.ReadFrom(p);

	for (auto i = p+mDataSize; i < (p + s); )
	{
		//ConLog("\n %d~%d~%d", p, i, p + s);
		auto cp = (dc_demo_data*)i;
		int type = *(cp->getType());
		if (type == DC_DEMO_STARTTICK)
		{
			int t = cp->toStartTick()->tick;
			dc_demo_tick T(t);
			Ticks.push_back(T);
		}
		else
			Ticks[Ticks.size() - 1].Data.push_back(*cp);
		i += cp->size();
	}


	/*
	for (int i = 0; i < Ticks.size();i++)
	{
		auto& t = Ticks[i];
		//ConLog("\nTick Started (%d/%d)",i,Ticks.size());
		for (int j = 0; j < t.Data.size(); j++)
		{
			auto d = t.Data[j];
			int type = *d.getType();
			if (type == DC_DEMO_WEAPONSPAWN)
			{
				int idx = d.toWeaponSpawn()->itemidx;
				int listidx = d.toWeaponSpawn()->listidx;
				sf::Vector2f pos = d.toWeaponSpawn()->coord;
				//ConLog("\n%d ~ (%d) %s spawned (%.1f|%.1f)", i, idx, g_Items[listidx].szName, pos.x, pos.y);
			}
			else if (type == DC_DEMO_WEAPONPICKUP)
			{
				int idx = d.toWeaponPickup()->itemidx;
				//ConLog("\n%d ~ (%d) picked up", i, idx);
			}
			else if (type == DC_DEMO_WEAPONDROP)
			{
				int idx = d.toWeaponDrop()->itemidx;
				sf::Vector2f pos = d.toWeaponDrop()->coord;
				//ConLog("\n%d ~ (%d) dropped (%.1f|%.1f)", i, idx, pos.x, pos.y);
			}
		}
	}
	*/

	for (int i = 0; i < 100; i++)
	{
		ConLog("\nPlayer Name: %s | Skins: (%d %d %d)", MetaData.playerNames[i], MetaData.playerSkins[i], MetaData.playerGliders[i], MetaData.playerWraps[i]);
	}

	delete[] F.loc_in_mem;
}