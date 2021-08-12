#pragma once
#include "DaiCastle.h"

enum dc_demo_structs
{
	DC_DEMO_STARTDEMO,
	DC_DEMO_ENDDEMO,
	DC_DEMO_STARTTICK,
	DC_DEMO_KEYFRAME,
	DC_DEMO_BUS_JUMPOUT,
	DC_DEMO_PLPOSITION,
	DC_DEMO_PLHEALTH,
	DC_DEMO_PLROTATE,
	DC_DEMO_PLWEAPONCHANGE,
	DC_DEMO_WEAPONSPAWN,
	DC_DEMO_WEAPONPICKUP,
	DC_DEMO_WEAPONDROP,
	DC_DEMO_CHOPEN,
	DC_DEMO_SHOTEFFECT,
	DC_DEMO_AIRDROPSPAWN,
	DC_DEMO_AIRDROPEND,
	DC_DEMO_TIMEUPDATE,
	DC_DEMO_SERVERTIMEUPDATE,
	DC_DEMO_BREAKWALL,
	DC_DEMO_PROJECTILEADD,
	DC_DEMO_PROJECTILEDESTRUCT,
	DC_DEMO_EXPLOSIVEADD,
	DC_DEMO_EXPLOSIVEUPDATE,
	DC_DEMO_EXPLOSIVEDESTRUCT,
	DC_DEMO_ELIMINATION
};

#define TICK_INFO_SIZE 32

class dc_demo_starttick
{
	int ID = DC_DEMO_STARTTICK;
public:
	int tick;
};

class dc_demo_playerposition
{
	int ID = DC_DEMO_PLPOSITION;
public:
	int pl;
	sf::Vector2f vPos;
	float height;
};

class dc_demo_playerhealth
{
	int ID = DC_DEMO_PLHEALTH;
public:
	int pl;
	int HP;
	int Shield;
};

class dc_demo_playerjumpout
{
	int ID = DC_DEMO_PLHEALTH;
public:
	int pl;
};

class dc_demo_keyframe
{
	int ID = DC_DEMO_KEYFRAME;
public:
	int tick;
};

class dc_demo_end
{
	int ID = DC_DEMO_ENDDEMO;
};

class dc_demo_playerrotate
{
	int ID = DC_DEMO_PLROTATE;
public:
	int pl;
	float angle;
};

class dc_demo_chestopen
{
	int ID = DC_DEMO_CHOPEN;
public:
	int chest;
};

class dc_demo_weaponspawn
{
	int ID = DC_DEMO_WEAPONSPAWN;
public:
	int itemidx;
	sf::Vector2f coord;
	int listidx;
};

class dc_demo_weaponpickup
{
	int ID = DC_DEMO_WEAPONPICKUP;
public:
	int itemidx;
};

class dc_demo_weapondrop
{
	int ID = DC_DEMO_WEAPONDROP;
public:
	int itemidx;
	sf::Vector2f coord;
};

class dc_demo_playerweaponchange
{
	int ID = DC_DEMO_PLWEAPONCHANGE;
public:
	int pl;
	int listidx;
	bool validated;
};

class dc_demo_shoteffect
{
	int ID = DC_DEMO_SHOTEFFECT;
public:
	sf::Vector2f start;
	sf::Vector2f end;
	float BeginTime;
};

class dc_demo_airdropspawn
{
	int ID = DC_DEMO_AIRDROPSPAWN;
public:
	int airdropindex;
	sf::Vector2f Pos;
};

class dc_demo_airdropremove
{
	int ID = DC_DEMO_AIRDROPEND;
public:
	int airdropindex;
};

class dc_demo_timeupdate
{
	int ID = DC_DEMO_TIMEUPDATE;
public:
	int daytime;
};

class dc_demo_servertime
{
	int ID = DC_DEMO_SERVERTIMEUPDATE;
public:
	float sv_time;
};

class dc_demo_breakwall
{
	int ID = DC_DEMO_BREAKWALL;
public:
	sf::Vector2i coord;
	int type;
};

class dc_demo_projectileadd
{
	int ID = DC_DEMO_PROJECTILEADD;
public:
	sf::Vector2f startPos;
	float Angle;
	float projSpeed;
};

class dc_demo_projectileend
{
	int ID = DC_DEMO_PROJECTILEDESTRUCT;
public:
	int projectileIndex;
};

class dc_demo_explosiveadd
{
	int ID = DC_DEMO_EXPLOSIVEADD;
public:
	int projectileType;
};

class dc_demo_explosiveupdate
{
	int ID = DC_DEMO_EXPLOSIVEUPDATE;
public:
	int projectileIndex;
	sf::Vector2f position;
};

class dc_demo_explosivedestruct
{
	int ID = DC_DEMO_EXPLOSIVEDESTRUCT;
public:
	int projectileIndex;
};

class dc_demo_elimination
{
	int ID = DC_DEMO_ELIMINATION;
public:
	int killer;
	int target;
};

struct dc_wallbreakdata
{
	sf::Vector2i coord;
	int type;
};

struct dc_airdropdata
{
	int type = 0; //0 - spawn, 
};

struct dc_demo_data
{
	char info[TICK_INFO_SIZE];

	int* getType() { return (int*)this; }

	dc_demo_starttick* toStartTick() { return (dc_demo_starttick*)this; }
	dc_demo_playerhealth* toPlayerHealth() { return (dc_demo_playerhealth*)this; }
	dc_demo_playerposition* toPlayerPosition() { return (dc_demo_playerposition*)this; }
	dc_demo_playerjumpout* toPlayerJumpout() { return (dc_demo_playerjumpout*)this; }
	dc_demo_playerrotate* toPlayerRotate() { return (dc_demo_playerrotate*)this; }
	dc_demo_playerweaponchange* toPlayerWeaponChange() { return (dc_demo_playerweaponchange*)this; }

	dc_demo_chestopen* toChestOpen() { return (dc_demo_chestopen*)this; }
	dc_demo_weaponspawn* toWeaponSpawn() { return (dc_demo_weaponspawn*)this; }
	dc_demo_weaponpickup* toWeaponPickup() { return (dc_demo_weaponpickup*)this; }
	dc_demo_weapondrop* toWeaponDrop() { return (dc_demo_weapondrop*)this; }
	dc_demo_airdropspawn* toAirdropSpawn() { return (dc_demo_airdropspawn*)this; }
	dc_demo_airdropremove* toAirdropRemove() { return (dc_demo_airdropremove*)this; }
	dc_demo_timeupdate* toTimeUpdate() { return (dc_demo_timeupdate*)this; }

	dc_demo_shoteffect* toShotEffect() { return (dc_demo_shoteffect*)this; }
	dc_demo_projectileadd* toProjectileAdd() { return (dc_demo_projectileadd*)this; }
	dc_demo_projectileend* toProjectileEnd() { return (dc_demo_projectileend*)this; }
	dc_demo_explosiveadd* toExplosiveAdd() { return (dc_demo_explosiveadd*)this; }
	dc_demo_explosiveupdate* toExplosiveUpdate() { return (dc_demo_explosiveupdate*)this; }
	dc_demo_explosivedestruct* toExplosiveDestruct() { return (dc_demo_explosivedestruct*)this; }


	dc_demo_keyframe* toKeyframe() { return (dc_demo_keyframe*)this; }
	dc_demo_servertime* toServerTime() { return (dc_demo_servertime*)this; }
	dc_demo_breakwall* toBreakWall() { return (dc_demo_breakwall*)this; }
	dc_demo_elimination* toElimination() { return (dc_demo_elimination*)this; }
	
	unsigned int size()
	{
		switch (*getType())
		{
		case DC_DEMO_STARTTICK: return sizeof(dc_demo_starttick);
		case DC_DEMO_PLPOSITION: return sizeof(dc_demo_playerposition);
		case DC_DEMO_PLHEALTH: return sizeof(dc_demo_playerhealth);
		case DC_DEMO_BUS_JUMPOUT: return sizeof(dc_demo_playerjumpout);
		case DC_DEMO_KEYFRAME: return sizeof(dc_demo_keyframe);
		case DC_DEMO_ENDDEMO: return sizeof(dc_demo_end);
		case DC_DEMO_PLROTATE: return sizeof(dc_demo_playerrotate);
		case DC_DEMO_CHOPEN: return sizeof(dc_demo_chestopen);
		case DC_DEMO_WEAPONSPAWN: return sizeof(dc_demo_weaponspawn);
		case DC_DEMO_WEAPONPICKUP: return sizeof(dc_demo_weaponpickup);
		case DC_DEMO_WEAPONDROP: return sizeof(dc_demo_weapondrop);
		case DC_DEMO_PLWEAPONCHANGE: return sizeof(dc_demo_playerweaponchange);
		case DC_DEMO_SHOTEFFECT: return sizeof(dc_demo_shoteffect);
		case DC_DEMO_AIRDROPSPAWN: return sizeof(dc_demo_airdropspawn);
		case DC_DEMO_AIRDROPEND: return sizeof(dc_demo_airdropremove);
		case DC_DEMO_TIMEUPDATE: return sizeof(dc_demo_timeupdate);
		case DC_DEMO_SERVERTIMEUPDATE: return sizeof(dc_demo_servertime);
		case DC_DEMO_BREAKWALL: return sizeof(dc_demo_breakwall);
		case DC_DEMO_PROJECTILEADD: return sizeof(dc_demo_projectileadd);
		case DC_DEMO_PROJECTILEDESTRUCT: return sizeof(dc_demo_projectileend);
		case DC_DEMO_EXPLOSIVEADD: return sizeof(dc_demo_explosiveadd);
		case DC_DEMO_EXPLOSIVEUPDATE: return sizeof(dc_demo_explosiveupdate);
		case DC_DEMO_EXPLOSIVEDESTRUCT: return sizeof(dc_demo_explosivedestruct);
		case DC_DEMO_ELIMINATION: return sizeof(dc_demo_elimination);
		default: return TICK_INFO_SIZE;
		}
	}
};

struct dc_demo_tick
{
	std::vector<dc_demo_data> Data;

	dc_demo_tick() {};
	dc_demo_tick(int tick)
	{
		dc_demo_data D;
		*(int*)(&D) = DC_DEMO_STARTTICK;
		D.toStartTick()->tick = tick;
		Data.push_back(D);
	}

};

struct dc_demo_metadata
{
	int DemoTickBase;
	sf::Vector2f BusStart, BusEnd, BusBegin;
	int StormPhases;
	std::vector<sf::Vector2f> StormMids;
	std::vector<float> StormSizes;
	
	char playerNames[100][64];
	int playerSkins[100];
	int playerGliders[100];
	int playerWraps[100];
	int GetSizeOf();

	void Setup(void* M);
	char* GetPrinted(int* Size);
	int ReadFrom(char* C);
};

struct dc_demo
{
	dc_demo_metadata MetaData;
	std::vector<dc_demo_tick> Ticks;

	void convert_back(file_t F);

};

