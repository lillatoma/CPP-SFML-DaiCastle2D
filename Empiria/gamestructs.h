/*
#pragma once
#include "includes.h"
#include "Menu.h"
#include "Vector.h"

class unit_t;

class item_t
{
public:

	int iRarity;
	char* szName;
	bool doesExist = false;
	int iDamage1;
	int iDamage2;
	int iDamage3;
	float fHeadshotMultiplier;

	int iDropoffRange1;
	int iDropoffRange2;
	int iRange;
	
	int iBullets;
	int iMagazineSize;
	int iFireRate;
	int iWeaponType;  //1 - Shotgun, 2 - Secondary, 3 - AR, 4 - Sniper
	int iAimType; 
	bool b_isHeal = false;
	bool b_isShield = false;
	int iHealAmount;
	int iAmount;

	int iID;

	bool isShotgun() { return iWeaponType == 1; }
	bool isSecondary() { return iWeaponType == 2; }
	bool isAR() { return iWeaponType == 3; }
	bool isSniper() { return iWeaponType == 4; }
	bool isEmpty() {
		if (doesExist)
		{
			if (iBullets > 0)return false;
		}
		return true;
	}

	void Setup(int id, int dmg1, int dmg2, int dmg3, float hsmult, int range1, int range2, int range3, int magsize, int firerate, int type, int atype, char* name)
	{
		iID = id;
		doesExist = true;
		iDamage1 = dmg1;
		iDamage2 = dmg2;
		iDamage3 = dmg3;
		fHeadshotMultiplier = hsmult;
		iDropoffRange1 = range1;
		iDropoffRange2 = range2;
		iRange = range3;
		iMagazineSize = magsize;
		iBullets = magsize;
		iFireRate = firerate;
		iWeaponType = type;
		iAimType = atype;
		szName = name;

		if (strstr(szName, "Common"))iRarity = 0;
		else if (strstr(szName, "Uncommon"))iRarity = 1;
		else if (strstr(szName, "Rare"))iRarity = 2;
		else if (strstr(szName, "Epic"))iRarity = 3;
		else iRarity = 4;


	}

	void Setup(int id,bool isheal, bool isshield, int healamount, int amount, char* name)
	{
		iID = id;
		b_isHeal = isheal;
		b_isShield = isshield;
		iHealAmount = healamount;
		doesExist = true;
		iAmount = amount;
		szName = name;
	}

	void Setup(item_t it)
	{
		iRarity = it.iRarity;
		iID = it.iID;
		doesExist = it.doesExist;
		iDamage1 = it.iDamage1;
		iDamage2 = it.iDamage2;
		iDamage3 = it.iDamage3;
		fHeadshotMultiplier = it.fHeadshotMultiplier;
		iDropoffRange1 = it.iDropoffRange1;
		iDropoffRange2 = it.iDropoffRange2;
		iRange = it.iRange;
		iMagazineSize = it.iMagazineSize;
		iBullets = it.iBullets;
		iFireRate = it.iFireRate;
		iWeaponType = it.iWeaponType;
		iAimType = it.iAimType;
		b_isHeal = it.b_isHeal;
		b_isShield = it.b_isShield;
		iHealAmount = it.iHealAmount;
		iAmount = it.iAmount;
		szName = it.szName;
	}

	void Reload()
	{
		if (iWeaponType != 1)iBullets = iMagazineSize;
		else iBullets += iFireRate;

		if (iBullets > iMagazineSize)iBullets = iMagazineSize;
	}

	void SetUpAllWeapons();

	void Copy(int a);

	static int GetRandomItem();


	void Shoot(unit_t* shooter, unit_t* target);


};

extern item_t g_ItemList[1000];




enum AimType
{
	AIMTYPE_FLICK,
	AIMTYPE_TRACK,
	AIMTYPE_PREDICT
};

class skill_t
{
public:
	int atk_flick = 5;
	int atk_track = 5;
	int atk_predict = 5;
	int defending = 5;
	//int pushing = 10;
	//int denying = 10;
	int looting = 5;
};


enum GameStyles
{
	GS_VERY_OFFENSIVE, 
	GS_OFFENSIVE,
	GS_AVERAGE,
	GS_DEFENSIVE,
	GS_VERY_DEFENSIVE
};

class gamestyle_t
{
public:
	skill_t skill;
	int style;
	int shotgun_preference; // 0 - tactical, 1 - pump, 2 - heavy
	int secondary_preference; //0 - smg, 1 - compact smg, 2 - dual pistol
	int ar_preference; //0 - ar, 1 - heavy ar, 2 - deagle
	

};


class match_t;

class unit_t
{
public:
	int iID;
	int iTeam = 0;
	bool bAlive;
	int iHealth;
	int iArmor;
	item_t itShotgun;
	item_t itSecondary_weapon;
	item_t itMid_range;
	item_t itSniper;
	item_t itHeal;

	Vector vecPosition;

	gamestyle_t* gsGamestyle;

	int s_Position = 1;
	int s_iEliminations = 0;
	int s_iSecondsSurvived = 0;
	int s_iShotsFlicked = 0;
	int s_iShotsTracked = 0;
	int s_iShotsPredicted = 0;
	int s_iShotsDodged = 0;
	int s_iPushesDone = 0;
	int s_iPushesDenied = 0;
	int s_iItemsFound = 0;

	match_t* pMatch;

	int iTargetID = -1;

	bool hasShotgun();
	bool hasSecondary();
	bool hasAR();
	bool hasSniper();

	bool NeedsToLoot();

	bool NeedsWeapons();
	bool NeedsHealth();
	bool NeedsShield();




	int GetAimSkill(int type)
	{
		if (type == 1)return gsGamestyle->skill.atk_flick;
		if (type == 2)return gsGamestyle->skill.atk_track;
		return gsGamestyle->skill.atk_predict;
	}

	int GetTotalElims();

	int GetTotalSkill()
	{
		return gsGamestyle->skill.atk_flick + gsGamestyle->skill.atk_track + gsGamestyle->skill.atk_predict + gsGamestyle->skill.defending + gsGamestyle->skill.looting;
	}

	void RunToCircle();
	void Loot(bool should_generate = true, item_t* fixed = nullptr);
	void Explore();
	void Spot();
	void Think();

	void GetDamage(int damage, bool is_storm = false);


	void Attack();
	void Push();

};

class inmatchinfo_t
{
public:
	inmatchinfo_t* next = nullptr;
	
	int killer = 0;
	int target = 0;
	int weapon = 0;


	void Add(int k, int t, int w)
	{
		if (next == nullptr)
		{
			killer = k, target = t, weapon = w;
			next = new inmatchinfo_t;
		}
		else next->Add(k,t,w);
	}

	void Clear(bool starter = true)
	{
		if (next == nullptr)return;
		while (next->next)
		{
			auto p = this;
			while (p->next->next)
			{
				p = p->next;
			}
			delete[]p->next;
			p->next = nullptr;
		}
		delete[]next;
		next = nullptr;
	}
};

class match_t
{
public:
	unit_t* players[100];
	
	
	
	int current_circle = 1;
	int ticks_from_circle_change = 200;
	float circle_size = 2500.f;
	float next_circle_size = 2500.f;
	Vector vecCircleMiddle = Vector(0.f,0.f,0.f);
	Vector vecNextMiddle = Vector(0.f, 0.f, 0.f);
	Vector hotspot = Vector(0.f, 0.f, 0.f);

	void SetupMatch(gamestyle_t* gsLocal, int gametype, int matches_played, int hotdroplevel); //game types: 1 - Solo, 2 - Duo, 3 - Squad, 4 - Solo Duo, 5 - Solo Squads
	gamestyle_t* GenerateGameStyle(int matches_played);



	void SimulateCircle();
	void SimulatePlayers();
	void SimulateTick();
	
	void DrawOneCircleOnMap(Vector cord, float size, sf::Color c);
	void DrawCircle();
	void DrawViewRange();
	void DrawPlayers();
	void DrawLoadout();
	void DrawIngameInformation();
	void DrawEndgameInformation();



	bool IsInCircle(Vector v);
	bool IsInNextCircle(Vector v);


	int GetStormDamage();
	float GetStormSize(int w);
	int GetStormTime(int w);
	int GetAliveTeams();

	int GetAlivePlayers();

	void Delete();


	inmatchinfo_t inInfo;
};


struct plstats_t
{
	int iMatches = 0;
	int iWins = 0;
	int iKills = 0;
	int iTopSmalls = 0;
	int iTopBigs = 0;
	int iMostKills = 0;
	int iWinstreak = 0;
	int iLongestWinstreak = 0;

	void Reset()
	{
		iMatches = 0;
		iWins = 0;
		iKills = 0;
		iTopSmalls = 0;
		iTopBigs = 0;
		iMostKills = 0;
		iWinstreak = 0;
		iLongestWinstreak = 0;
	}
};

struct recentmatch_t
{
	bool valid = false;
	int gametype = 0;
	int placement = 0;
	int eliminations = 0;
	int match_length = 0;
};

struct game_t
{
	int experience = 0;
	bool bInMatch = false;
	gamestyle_t gsGameStyle;
	int iGameModeSelected = 0;
	int iCurrentTab = 0;
	int iHotdropLevel = 0;

	bool bShowOverallStats = true;
	plstats_t psSolos;
	plstats_t psDuos;
	plstats_t psSquads;

	plstats_t psSeasonSolos;
	plstats_t psSeasonDuos;
	plstats_t psSeasonSquads;

	match_t* pMatch;

	void Do();
	void StartGame();

	void DrawARecord(int id, int y);

	void DrawStatistics();
	void DrawPlay();
	void DrawSkill();
	void DrawSave();
	void DrawHistory();


	void Load(char* savename);
	void Save(char* savename);

	void DrawUI();
	void DrawUIBar();

	int iRecentMatch = 0;
	recentmatch_t previousMatches[10];
	bool bAutoplay = false;
};



*/