#pragma once
#include "AStar.h"
#include "DC_Demo.h"

//////////////////////////////////////////////
///Data holder of a projectile/sniper bullet object
//////////////////////////////////////////////
struct dc_projectile
{
	int ProjectileIndex; //This is for demos
	int originid; //unit who shot the projectile
	sf::Vector2f start, end; //origin, and final destination if there is nothing to catch the projectile
	float projectile_speed; 
	float timeAlive = 0.f; //used to calculate current position
	int DamageEnd, DamageStart; 
	int wpnListIndex; //to get more data if needed
};

//////////////////////////////////////////////
///Data holder of an explosive's projectile
//////////////////////////////////////////////
struct dc_explosive
{
	int ExplosiveIndex; //This is for demos
	sf::Vector2f start, end; //origin, and final destination if there is nothing to catch the projectile
	int originid; //unit who shot the projectile
	int userid;
	int stickid; //unused
	float projectile_speed;
	int projectiletype; //0 - Rocket, 1 - GL Grenade, 2 - HandGrenade, 3 - Sticky
	float explosionRange; //Radius in which the explosion affects its environment
	float timeAlive = 0.f;
	float timeMax; //Maximum amount of time the explosive is alive

	int DamageEnd, DamageStart;
	int wpnListIndex; //to get more data if needed
	//char wpnName[128];
};

//////////////////////////////////////////////
///Data holder of an item
///Notably there is two different categories: weapons and heals
///Heals heal you
///Weapons damage other units. 
///There are pistols, submachineguns, assault rifles, machineguns, rifles, sniper rifles, and explosives.
//////////////////////////////////////////////
struct dc_item
{
	int ListIndex;
	//TODO: AudibleDistance
	sf::Vector2f vPosition;
	int iType; //0 - normal, 1 - multishot, 2 - projectile, 3 - explosive, 4 - heal, 5 - shield, 6 - progressive
	bool bValidated = false;
	bool bAuto = false;
	int iDamageStart;
	int iDamageEnd;
	float fRange;
	int iBullets;
	int iMaxBullets;
	int iBulletType; //1 - small, 2 - medium, 3 - heavy, 4 -shotgun
	int iBulletConsumption = 1;
	int iPellets;
	int iReloadMethod = 1; //1 - full magazine, 2 - bullets
	float fReloadTime;

	float fProjectileSpeed;
	float fProjectileSpeedMax;
	float fExplosiveLifetime;
	float fExplosionRange;
	int iExplosiveType; //0 - Rocket, 1 - GL Grenade, 2 - HandGrenade, 3 - Sticky
	bool bReloadable = true;

	float fBloomMinSize;
	float fBloomMovingMinSize;
	float fBloomMaxSize;
	float fBloomStandingDecrease;
	float fBloomMovingDecrease;
	float fBloomShootIncrease;

	float fFirerate;
	float fPulloutTime;
	float fWeaponWeight = 0.0f;

	int iHealType; //0 - health, 1 - shield, 2- progressive
	int iHealAmount;
	int iHealMax;
	float fHealTime;
	float fHealRateProgressive;
	float fAudibleDistance;
	float fVolumeMulti = 1.f;
	int iSoundID;


	int iRarity;
	int iTexture;
	bool bOwned = false;

	char szName[128];

	int id;
	int GameIdx = -1;

	//////////////////////////////////////////////
	/// Returns a random ID based on the lootpool
	//////////////////////////////////////////////
	static int GetRandomWeaponID();

	//////////////////////////////////////////////
	/// Creates a copy of the dc_item with ListIndex 'type' on this object, and changes the position to 'pos'
	//////////////////////////////////////////////
	void create(int type, sf::Vector2f pos);

	//////////////////////////////////////////////
	/// Hardcoded. Sets up all weapons.
	//////////////////////////////////////////////
	static void define_all();
	//////////////////////////////////////////////
	/// DPS calculation
	//////////////////////////////////////////////
	float GetPrimitiveDPS(float distance);
	//////////////////////////////////////////////
	/// DPS calculation
	//////////////////////////////////////////////
	float GetRealDPS(float distance, bool fsawait);
	//////////////////////////////////////////////
	/// DPS calculation, the best approximation
	//////////////////////////////////////////////
	float CalculateDPS(float distance, bool standing);
	bool IsConsumable()
	{
		return id >= 1000;
	}
	bool IsHeal()
	{
		return iType >= 4 && iType <= 6;
	}

	bool IsSniper()
	{
		return iType == 2;
	}

	bool IsPistol()
	{
		return (ListIndex <= 4) || (ListIndex >= 19 && ListIndex <= 23);
	}

	bool IsSmg()
	{
		return (ListIndex >= 5 && ListIndex <= 12) || (ListIndex >= 88 && ListIndex <= 90);
	}

	bool IsMachinegun()
	{
		return ListIndex == 29 || ListIndex == 30 || (ListIndex >= 79 && ListIndex <= 81);
	}
	bool IsRifle()
	{
		return (ListIndex >= 24 && ListIndex <= 28) || (ListIndex >= 31 && ListIndex <= 33) || (ListIndex >= 49 && ListIndex <= 63);
	}
	bool IsShotgun()
	{
		return (ListIndex >=34 && ListIndex <= 48) ||(ListIndex >= 82 && ListIndex <= 87);
	}
	bool IsExplosive()
	{
		return (ListIndex >= 72 && ListIndex <= 78);
	}
	//////////////////////////////////////////////
	/// Unused
	//////////////////////////////////////////////
	bool is_for_bot(dc_item* It);

	dc_item() {};
	//////////////////////////////////////////////
	/// Similar to create(..)
	/// Creates a copy of the dc_item with ListIndex 'ListIndex' and places it into pos
	//////////////////////////////////////////////
	dc_item(int ListIndex, sf::Vector2f pos);

};


inline bool operator==(dc_item a, dc_item b)
{
	for (int i = 0; i < sizeof(dc_item); i++)
	{
		if(*(((char*)&a) + i) != *(((char*)&b) + i))return false;

	}
	return true;
}

extern std::vector<dc_item> g_Items;


struct dc_elimdata
{
	sf::Vector2f shooterPos;
	sf::Vector2f targetPos;
	int WeaponListindex;
};

//////////////////////////////////////////////
/// Struct that holds statistics for a player
//////////////////////////////////////////////
struct dc_stats
{
	int iEliminations = 0;
	int iPlacement = 0;
	float fDistanceWalked = 0.f;
	int iDamageDealt = 0;
	int iDamageTaken = 0;
	float fTimeAlive = 0.f;
	int iShotsTaken = 0;
	int iShotsHit = 0;
	sf::Vector2f LandingPosition = sf::Vector2f(-1.f,-1.f);
	std::vector<dc_elimdata> Elims;
	std::vector<int> Chests;
	std::vector<int> VisitedPositions;

};

#define ALL_SKINTEXTURES 10
#define ALL_GLIDERTEXTURES 5
#define ALL_WEAPONWRAPTEXTURES 8

#define CHEST_OPENTIME 0.45f
#define AIRDROP_OPENTIME 4.f
#define AIRDROP_FALLINGTIME 30.f
#define AIRDROP_VISIBLETIME 25.f

#define NEXT_AIRDROP_MINTIME 60.f
#define NEXT_AIRDROP_MAXTIME 300.f

#define UNIT_NATURAL_DESCEND 1.5f
#define UNIT_FORCE_DESCEND 6.f

#define UNIT_ACCEL_TIME 0.05f
#define UNIT_SLOWDOWN_FACTOR 0.9925f
#define UNIT_RUN_SPEED 6.f
#define UNIT_RUN_SPEED_WATER 4.f
#define UNIT_FREEFALL_SPEED 12.5f
#define UNIT_RELOAD_SPEED_MULT 0.55f

#define UNIT_FOOTSTEPSIZEGRASS 2.4f
#define UNIT_FOOTSTEPSIZEWOOD 1.8f
#define UNIT_FOOTSTEPSIZESAND 2.1f
#define UNIT_FOOTSTEPSIZESNOW 2.1f
#define UNIT_FOOTSTEPSIZETILE 1.8f
#define UNIT_FOOTSTEPSIZEMETAL 1.7f
#define UNIT_FOOTSTEPSIZEWATER 2.7f
#define FOOTSTEP_AUDIODISTANCE 50.f

#define BUS_PREWAIT
#define BUS_TRAVELSPEED 30.f
#define BUSLOOPTIME 8.7333f
#define BUS_HEIGHT 100.f

#define KILL_OWNERTIME 15.f
#define BUS_AUDIBLEDISTANCE 250.f


struct dc_slurptypeheal
{
	int healLeft = 0;
	float fHealRate;
	float fHealTimeLeft;
};

//////////////////////////////////////////////
/// Representing object for a unit of a player or AI
//////////////////////////////////////////////
struct dc_unit
{
	bool bGodMode = false; //Cheat
	bool bOnBus = false; 
	float fFreeFallHeight = 0.f; //Starting from 100, it descends to 0
	sf::Vector2f vPosition; // position in the world
	int iHealth = 100; //Ranging from 0 - 100
	int iShield = 0; //Ranging from 0 - 100
	dc_item Items[5];
	bool bMoved = false; //If the player moved in a frame
	sf::Vector2f vVelocity = sf::Vector2f(0,0); 
	float fAngle = 0; //Where the unit facing
	int iSelectedWeapon = 0; //Which item is equipped
	float fPulloutDelay = 0.f; //The weapon needs this much time to be pulled out
	float fShootDelay = 0.f; //Fire rate delay. Can shoot next bullet this much seconds later.
	float fBloomSize = 0.f; //Size of the bullet spread
	float fFSADelay = 0.f; //The spread can get smaller this much seconds later.
	bool bReloading = false;
	float fReloadDelay = 0.f; //The weapon gets reloaded this much seconds later. Either fully reloaded, or bullets added in mag
	int iSkinTexture = 0; //Texture ID for Skin
	int iGliderTexture = 0; //Texture ID for Glider
	int iWeaponWrapTexture = 0;//Texture ID for Weapon Wrap

	int iOpeningAirdrop = -1; //Airdrop index of an airdrop being opened. When not opening an airdrop, it's -1
	int iOpeningChest = -1; //Chest index of a chest being opened. When not opening a chest, it's -1
	float fOpeningTime = 0.f; //Time needed to open a chest or airdrop
	float fHealTime = 0.f; //Time needed for a heal to take effects
	
	dc_stats Stats;
	dc_clock StormClock;
	float StormSpentTime;
	float DistanceTillNextFootStep = 1.f;
	int gotHitLastPlayerID = -1;
	int gotHitLastItemID = -1;
	dc_clock gothitLastClock;
	char szName[64] = "Player";

	//////////////////////////////////////////////
	/// Returns if the unit has a free item slot
	//////////////////////////////////////////////
	int hasFreeSlot();
	//////////////////////////////////////////////
	/// Returns the index of the first weapon
	//////////////////////////////////////////////
	int getFirstNonHealSlot();





	//////////////////////////////////////////////
	/// Reduces the health of the unit by 'dmg'
	/// If 'ignore_shield' is false, the shield will absorb the damage first
	/// Otherwise the unit's health is affected direcly
	/// The unit can't be damaged if it is still on the bus, or has god mode.
	//////////////////////////////////////////////
	void Damage(int dmg, bool ignore_shield = false)
	{
		if (bOnBus || bGodMode)return;
		if (!ignore_shield)
		{

			if (iShield > dmg)iShield -= dmg;
			else
			{
				dmg -= iShield;
				iShield = 0;
				iHealth -= dmg;
			}
			if (iHealth < 0)iHealth = 0;
		}
		else
		{
			iHealth -= dmg;
			if (iHealth < 0)iHealth = 0;
		}
	}
	//////////////////////////////////////////////
	/// Calculates the linear euclidean velocity
	//////////////////////////////////////////////
	float CalculateVelocity()
	{
		return sqrt(vVelocity.x*vVelocity.x + vVelocity.y*vVelocity.y);
	}
	//////////////////////////////////////////////
	/// Returns true if one of the unit's valid items is a weapon
	/// Returns false if none of the unit's valid items is a weapon
	//////////////////////////////////////////////
	bool hasWeapon();

	dc_item& GetCurrentWeapon()
	{
		return Items[iSelectedWeapon];
	}
	//////////////////////////////////////////////
	/// Returns how heavy the current selected item is
	/// Used to 'drag' the unit
	//////////////////////////////////////////////
	float GetCurrentWeaponWeight()
	{
		if (Items[iSelectedWeapon].bValidated)
		{
			return Items[iSelectedWeapon].fWeaponWeight;
		}
		else return 0.f;
	}

	//////////////////////////////////////////////
	/// Returns true if one of the unit's valid items has ListIndex of 'listid'
	/// Returns false if none of the unit's valid items has ListIndex of 'listid'
	//////////////////////////////////////////////
	int hasSpecificItem(int listid);
	//////////////////////////////////////////////
	/// Returns true if one of the unit's valid heals can heal health
	/// Returns false if none of the unit's valid heals can heal health
	//////////////////////////////////////////////
	int hasWhiteheal();
	//////////////////////////////////////////////
	/// Returns true if one of the unit's valid heals can heal shield
	/// Returns false if none of the unit's valid heals can heal shield
	//////////////////////////////////////////////
	int hasShieldheal();

	std::vector<dc_slurptypeheal> SlurpContainer; //This is a holder for slurp type heals

	//////////////////////////////////////////////
	/// Simulates slurp effect for each active slurp-type-heal if 'diffTime' seconds have passed
	//////////////////////////////////////////////
	void SimulateSlurp(float diffTime)
	{
		for (int i = SlurpContainer.size() - 1; i >= 0; i--)
		{
			auto& s = SlurpContainer[i];
			s.fHealTimeLeft -= diffTime;
			while (s.fHealTimeLeft < 0 && s.healLeft > 0)
			{
				s.fHealTimeLeft += 1.f / s.fHealRate;
				s.healLeft--;
				if (iHealth < 100)iHealth++;
				else if (iShield < 100)iShield++;
			}
			if (s.healLeft <= 0)SlurpContainer.erase(SlurpContainer.begin() + i);
		}
	}
};

//////////////////////////////////////////////
/// Data of a chest on the map
/// DONT CHANGE ANYTHING, IT CAUSES THE MAP TO LOAD IN AN UNHANDLED WAY
//////////////////////////////////////////////
struct dc_chest 
{
	sf::Vector2f vPosition;
	bool bOpen;
	char fill[3];
};



inline bool operator==(dc_chest a, dc_chest b) { return a.vPosition == b.vPosition &&a.bOpen == b.bOpen; }

//////////////////////////////////////////////
/// Data of a wall of a block
//////////////////////////////////////////////
struct dc_wall
{
	int iHealth = 0; //If health is > 0, wall is active, else its not
	int iTexture = 0; //Unused
};

//////////////////////////////////////////////
/// Data of a block on the map
//////////////////////////////////////////////
struct dc_block
{
	int iTexture = 0; //Texture of ground
	dc_wall walls[2]; //Right and bottom walls
};

struct dc_blockline //Because multi-dimensional arrays work in a weird way.
{
	std::vector<dc_block> blocks;
};

//////////////////////////////////////////////
/// Holds the data of a raytrace.
//////////////////////////////////////////////
struct dc_tracedata
{
	sf::Vector2f start;
	sf::Vector2f end;
	bool hit_object = false;
	sf::Vector2i object;
	int type = 0;
	bool hit_target = false;
	int targetid = -1;
};

//////////////////////////////////////////////
/// Holds the data of a named POI on the map
/// POI : Point of Interest
//////////////////////////////////////////////
struct dc_label
{
	sf::Vector2f vPosition;
	char n[64] = "\0";
	float size = 0.f;
};

inline bool operator==(dc_label a, dc_label b)
{
	return a.size = b.size && a.vPosition == b.vPosition && !strncmp(a.n, b.n, 64);
}

//////////////////////////////////////////////
/// Object for the map
/// It is built up by blocklines, and the blocklines are built up by blocks
/// It holds all the data of chests, labels, and dropped items
//////////////////////////////////////////////
struct dc_map
{
	std::vector<dc_blockline> lines;
	//char AccidentPadding[1024];
	std::vector<dc_chest> chests;
	std::vector<dc_item> items; //onground;
	std::vector<dc_label> labels;


	sf::Vector2i size;


	int day_time = 0;

	//////////////////////////////////////////////
	/// Simulates the day/night cycle of the map
	/// It only updates if 100ms have passed after the last update
	//////////////////////////////////////////////
	void simulate_day();

	//////////////////////////////////////////////
	/// Returns the modifier color for the current daytime
	//////////////////////////////////////////////
	sf::Color get_modulation_color();

	//////////////////////////////////////////////
	/// Returns the angle of shadow for the current daytime
	//////////////////////////////////////////////
	float get_shadow_angle();
	//////////////////////////////////////////////
	/// Returns the length of shadows for the current daytime
	//////////////////////////////////////////////
	float get_shadow_length();

	//////////////////////////////////////////////
	/// Generates a blank map with size sx*sy
	/// It deletes the previous map from memory
	//////////////////////////////////////////////
	void define(int sx, int sy);
	//////////////////////////////////////////////
	/// Draws the map if the middle of the screen is (mx,my)
	/// The width represents how many blocks are drawn in a line horizontally
	//////////////////////////////////////////////
	void draw(float mx, float my, float width);
	//////////////////////////////////////////////
	/// Draws the map if the middle of the screen is (mx,my)
	/// The width represents how many blocks are drawn in a line horizontally
	/// This function is used for demo layer rendering
	/// It renders the map if 'map' is true
	/// It renders chests if 'chests' is true
	/// It draws shadows if 'shadow' is true
	//////////////////////////////////////////////
	void draw(sf::RenderTexture* T, float mx, float my, float width, bool map,bool chests, bool shadow);
	
	//////////////////////////////////////////////
	/// Draws the shadows on a new white texture
	/// This function was needed because shadows tended to overlap each other
	/// This function is used for demo layer rendering
	//////////////////////////////////////////////
	void beginshadows(sf::RenderTexture* R, float mx, float my, float width);
	//////////////////////////////////////////////
	/// Draws the shadows on a new white texture
	/// This function was needed because shadows tended to overlap each other
	//////////////////////////////////////////////
	void beginshadows(float mx, float my, float width);


	//////////////////////////////////////////////
	/// Draws the items if the middle of the screen is (mx,my)
	/// the width represents how many blocks are drawn in a line horizontally
	//////////////////////////////////////////////
	void drawitems(float mx, float my, float width);
	//////////////////////////////////////////////
	/// Draws the items if the middle of the screen is (mx,my)
	/// the width represents how many blocks are drawn in a line horizontally
	/// This function is used for demo layer rendering
	//////////////////////////////////////////////
	void drawitems(sf::RenderTexture* T,float mx, float my, float width);

	//////////////////////////////////////////////
	/// Deletes the items from the vector that are picked up to save memory
	//////////////////////////////////////////////
	void delete_items();

	//////////////////////////////////////////////
	/// Deletes the items from the vector that are picked up to save memory
	//////////////////////////////////////////////


	//////////////////////////////////////////////
	/// Creates all small lines for every wall and puts them to chunks
	//////////////////////////////////////////////
	void begin_lines();
	//////////////////////////////////////////////
	/// Deletes a line with startpoint s, endpoint e, and type typ
	//////////////////////////////////////////////
	void delete_line(sf::Vector2f s, sf::Vector2f e, int typ);

	//////////////////////////////////////////////
	/// Loads the map with name 'n'
	/// TODO: Multi-map support
	//////////////////////////////////////////////
	void load(char* n);

	//////////////////////////////////////////////
	/// Draws the entire map on a small screen in the middle
	/// It shows the current location of the player's unit
	/// It has an option to show all alive units (if show_only_player is false)
	/// Draws the Storm on top of it
	//////////////////////////////////////////////
	void show_minimap(float &mx, float &my, float width, bool show_only_player,sf::Vector2f StormMid, float StormRadius);

	//////////////////////////////////////////////
	/// Draws the close surroundings on a small screen in the top right
	/// Draws the Storm on top of it
	//////////////////////////////////////////////
	void show_minimapui(float &mx, float &my, float width, float busx, float busy, float busr, sf::Vector2f StormMid, float StormRadius);

	//////////////////////////////////////////////
	/// Converts the point (x,y) on screen to (rx,ry) on map if the middle of the screen is (mx,my) on map and 'width' amount of blocks are drawn horizontally
	/// Returns the point (rx,ry)
	//////////////////////////////////////////////
	static sf::Vector2f screen_to_world(float mx, float my, float width, float x, float y);
	//////////////////////////////////////////////
	/// Converts the point the mouse is at on screen to (rx,ry) on map if the middle of the screen is (mx,my) on map and 'width' amount of blocks are drawn horizontally
	/// Returns the point (rx,ry)
	//////////////////////////////////////////////
	static sf::Vector2f cursor_to_world(float mx, float my, float width);
	//////////////////////////////////////////////
	/// Converts the point (x,y) on map to (rx,ry) on screen if the middle of the screen is (mx,my) on map and 'width' amount of blocks are drawn horizontally
	/// Returns the point (rx,ry)
	//////////////////////////////////////////////
	static sf::Vector2f world_to_screen(float mx, float my, float width,float x, float y);

	//////////////////////////////////////////////
	/// Traces a ray from point 'a' to point 'b'
	/// Returns all effective data
	//////////////////////////////////////////////
	dc_tracedata trace_ray(sf::Vector2f a, sf::Vector2f b);

	//////////////////////////////////////////////
	/// Returns true if the point I is on the map
	//////////////////////////////////////////////
	bool is_on_map(sf::Vector2i I)
	{
		return (I.x >= 0 && I.x < size.x && I.y >= 0 && I.y < size.y);
	}
	//////////////////////////////////////////////
	/// Returns true if the point I is on the map
	//////////////////////////////////////////////
	bool is_on_map(sf::Vector2f I)
	{
		return (I.x >= 0 && I.x < size.x && I.y >= 0 && I.y < size.y);
	}
};

///Globally loaded for a faster copy at match-start
extern dc_map g_Map;

//////////////////////////////////////////////
/// Data of a line of a bullet
//////////////////////////////////////////////
struct dc_shoteffect
{
	sf::Vector2f start;
	sf::Vector2f end;
	float clockBegin;

	void draw(float mx, float my, float width, float ServerTime);
	void draw(sf::RenderTexture*T,float mx, float my, float width, float ServerTime);
	dc_shoteffect() {};
	dc_shoteffect(sf::Vector2f s, sf::Vector2f e, float begin) { start = s; end = e; clockBegin = begin; }
};
//////////////////////////////////////////////
/// Data of how much damage was dealt
//////////////////////////////////////////////
struct dc_damageeffect
{
	sf::Vector2f position;
	int damage;
	sf::Color color = sf::Color(0,0,0,255);
	float clockBegin;

	void draw(float mx, float my, float width, float ServerTime);
};
//////////////////////////////////////////////
/// Data of a player being eliminated by the spectated player
//////////////////////////////////////////////
struct dc_killnoticeeffect
{
	int Killer = -1, Target=-1;
	char message[128];
	float clockBegin;

	dc_killnoticeeffect() {};
	dc_killnoticeeffect(int killer, int target, float clockbegin)
	{
		Killer = killer; Target = target; clockBegin = clockbegin;
	}

	void draw(float y, int cfollows, float y2, float ServerTime);
};
//////////////////////////////////////////////
/// Data of a player's unit dying
//////////////////////////////////////////////
struct dc_deatheffect
{
	int iTexture = 0;
	float fRotation = 0.f;
	float clockBegin;
	sf::Vector2f position;
	void draw(sf::RenderTexture* T,float mx, float my, float width, float ServerTime);
	void draw(float mx, float my, float width, float ServerTime);
};

//////////////////////////////////////////////
/// Data of a player's unit's shieldbreak
//////////////////////////////////////////////
struct dc_shieldbreakeffect
{
	float clockBegin;
	sf::Vector2f position;
	void draw(sf::RenderTexture* T,float mx, float my, float width, float ServerTime);
	void draw(float mx, float my, float width, float ServerTime);
};

//////////////////////////////////////////////
/// Data of a recent airdrop
//////////////////////////////////////////////
struct dc_airdropeffect
{
	float clockBegin;

	void draw(float ServerTime);
};

//////////////////////////////////////////////
/// Data of a recent change in storm behaviour
//////////////////////////////////////////////
struct dc_stormclosingeffect
{
	float clockBegin;
	float lifetime;
	void draw(float ServerTime);
};

//////////////////////////////////////////////
/// Container object for all effects
//////////////////////////////////////////////
struct dc_effects
{
	std::vector<dc_damageeffect> dmg_effects;
	std::vector<dc_shoteffect> sht_effects;
	std::vector<dc_killnoticeeffect> kilnot_effects;
	std::vector<dc_deatheffect> dth_effects;
	std::vector<dc_shieldbreakeffect> shb_effects;
	std::vector<dc_airdropeffect> ade_effects;
	std::vector<dc_stormclosingeffect> sce_effects;
};

//////////////////////////////////////////////
/// Data for a computer controlled player if they can notice another player
//////////////////////////////////////////////
struct dc_bottarget
{
	int playerid;
	dc_clock NoticeTime;
	dc_clock DeleteTime;
	dc_bottarget() {};
	dc_bottarget(int i) { playerid = i; NoticeTime.Update(); DeleteTime.Update(); }
};

//////////////////////////////////////////////
/// All the data of a computer-controlled player that could change
//////////////////////////////////////////////
struct dc_botchangable
{
	std::vector<int> RestOfChests; //The bot remembers which chests they see open, the rest of the chests can be okay
	float fTimeTillReact = 0.f; //Time needed for the bot to shoot at an opponent
	float fTimeTillThink = 0.f; //Time needed for the bot till its next action
	sf::Vector2f DistantTargetPoint; //Next point to go
	int DistantTargetType = 0; // 1 - Chest, 2 - Item, 3 - Zone, 4 - Raid, 5 - Bail, 6 - Rush, 7 - Airdrop Cover, 8 - Airdrop Open, 9 - Forceheal
	int DistantTargetChestID = -1; //If DistantTargetType == 1
	int DistantTargetAirdropID = -1; //If DistantTargetType == 7 or 8
	int DistantTargetItemID = -1; //If DistantTargetType == 2
	//These clocks are not resource effective, but easy to work with
	dc_clock ChestCheckClock;
	dc_clock PathFindClock;
	dc_clock WeaponSwapCheckClock;
	dc_clock LastBailClock;
	dc_clock NoBailOFClock;
	dc_clock SortInventoryClock;
	std::vector<int> BailTarget;
	float BailDistance = 40; //The distance how far the bot goes if the situation is not good
	bool bHealing = false; //If the bot starte healing
	bool AreChestsAvailable = true; //Possibly the same as RestOfChests.size() == 0
	bool forceHeal = false; //These force heals are due to a glitch in the thinking process of the bots
	int forceHealHealID = 0; //These force heals are due to a glitch in the thinking process of the bots
	std::vector<int> NoticedPlayerIDs; //IDs of other players that were noticed by the bot
	std::vector<int> TargetedPlayerIDs; //IDs of other players that are attackable by the bot
	std::vector<dc_bottarget> NoticedPlayers; //Target data of other players that were noticed by the bot
	std::vector<dc_bottarget> TargetedPlayers; //Target data of other players that are attackable by the bot

	int SideStepType = 0; //0, 2 Stay; 1 MoveLeft; 3 MoveRight
	float SideStepTimeLeft; //How much time is left until sidestep behaviour changes

	bool movepathBugged = false;

};

struct dc_botdata
{
	dc_botchangable Changables;
	int botDifficulty; // 0 - Easy, 1 - Normal, 2 - Hard, 3 - Expert
	float JumpoffTime; //How much time after being able to jump out of the bus will the bot actually jump out
	float JumpoffDist; //How far the bot is willing to jump from the bus
	float DescendSpeedInMind; //How fast the bot thinks it can descend - causes intended calculation error with lower difficulty bots
	bool hasJumpedoffTotally = false; //This is not changed often
	sf::Vector2f JumpToPosition; //Where the bot will land
	float fBotThinkDelay; //Time when not doing anything, except targeting/shooting
	float fReactionTime; //80-120% of reactiontime (when they noticed and can attack player);
	float fEnemyNoticeTime; //How long the bot takes to notice another player if they are in their range
	float fChestRange = 10.f; //How far the bot can see the chests
	float fItemRange = 10.f; //How far the bot can see the items
	float fPlayerRange = 20.f; //How far the bo can see the players
	float fAirDropInterestDistance; //How far the bot is willing to go for an airdrop
	float fAirDropGuardMaxRange; //How closely the bot is guarding a falling airdrop - max limit
	float fAirDropGuardMinModifier; //How closely the bot is guarding a falling airdrop - must be between 0 and 1

	std::vector<int> WeaponPreferences[5]; //Order of items that the bot likes for each slot
	bool SuckerForExtraHeals; //If the bot wants to get full heals in their inventory before raiding
	int GoodEnoughRanking[5]; //How good the inventory of the bot should be to 'feel' good about it
	int FightType[5]; //0 - moving, 1 - standing, 2 - heal
	int HealUseMinimums[6]; //When the bot uses heal - min amount
	int HealUseMaximums[6]; //When the bot uses heal - max amount
	int BotZoneFearLevel = 2; //0 - only in storm, 1 - when storm is close, 2 - on time, 3 - early, 4 - very early
	int MinimumHealthToRaid; //Minimum health needed to randomly walk on the map for eliminations
	float JustInCaseWeaponDistance; //What distance the bot thinks is useful if they can't directly see another player
	float fAimCorrectSpeedPenalty; 
	float fAimCorrectness[5] = { 10.f,10.f,10.f,10.f,10.f }; //How accurate the bot needs to be to shoot
	float fAimSpeed[5] = { 70.f,70.f,70.f,70.f,70.f }; //How fast the bot turns to their target
	bool PrecisionWait; //If the bot likes to wait until their spread is small
	float fAimPrecision[5] = { 20.f,30.f,50.f,90.f,100.f }; //If the target is in the correct radius, how fast they continue to aim
	float fAimSpeedCasual; //How fast the bot turns to their non-player target
	float fAimCorrectnessCasual;  //How accurately the bot turns to their non-player target

	int FightStyleInFight = 0; //0 - Rusher, 1 - Placeholder, 2 - Bailer
	//int FightStyleOffFight = 0; //0 - Rusher, 1 - Placeholder, 2 - Bailer
	int RushHealthMinOF = 0; //How much health the bot needs to rush other players - OF is for off-fight
	int BailHealthMaxOF = 0; //How much health is the maximum for the bot to not bail - OF is for off-fight
	int BailHealthMaxIF = 0; //How much health is the maximum for the bot to not bail - IF is for in-fight
	float SideStepMinTime; //Minimum time for side-step behaviour change
	float SideStepMaxTime; //Maximum time for side-step behaviour change
	float StillStayMinTime; //Minimum time for side-step behaviour change when it stays still
	float StillStayMaxTime; //Maximum time for side-step behaviour change when it stays still
	float InaccuracyMax; //Maximum amount of random inaccuracy
	float BotMemoryAfterDie; //How long the bot remembers another player after it kills another player - so the bot keeps shooting for a while
	float BotMemoryAfterVanish; //How long the bot remembers another player after it loses another player out of sight - so the bot keeps shooting for a while
	
	std::vector<sf::Vector2f> move_path;
};

//////////////////////////////////////////////
/// Info of weapon damage dealt by one bullet/pellet
/// Introduced for multishot weapons, like shotguns to reduce damage effects
//////////////////////////////////////////////
struct damageinfo_t
{
	bool is_null = false;
	int iType = -1; //0 - Player, 1 - Wall
	int iDamage = 0;
	int iShooter = 0;

	int iVictim = 0;
	sf::Vector2i vWallCoords;
	int iWalltype = 0;
	sf::Vector2f mapCoord;
	int mapCoordWeight = 1;
};

//////////////////////////////////////////////
/// Holder for weapon damage info
//////////////////////////////////////////////
struct damagelist_t
{
	std::vector<damageinfo_t> totalDamages;


	//////////////////////////////////////////////
	/// Sometimes shooting with a multishot weapon results in hitting the same object multiple times
	/// This function sums the damages on each object, and reduces the element count of the damagelist
	//////////////////////////////////////////////
	void compress()
	{
		for (int i = 0; i < totalDamages.size(); i++)
		{
			if (totalDamages[i].is_null)
			{
				totalDamages.erase(totalDamages.begin() + i);
				i--;
				continue;
			}

			for (int j = i + 1; j < totalDamages.size(); j++)
			{

				if (totalDamages[i].iType != totalDamages[j].iType)continue;
				if (totalDamages[i].iShooter != totalDamages[j].iShooter)continue;
				if (totalDamages[i].iType == 0)
				{
					if (totalDamages[i].iVictim != totalDamages[j].iVictim)continue;
					totalDamages[i].iDamage += totalDamages[j].iDamage;

					totalDamages[i].mapCoord += totalDamages[j].mapCoord;
					totalDamages[i].mapCoordWeight++;

					totalDamages.erase(totalDamages.begin() + j);
					j--;
				}
				else if (totalDamages[i].iType == 1)
				{
					if (totalDamages[i].vWallCoords != totalDamages[j].vWallCoords)continue;
					if (totalDamages[i].iWalltype != totalDamages[j].iWalltype)continue;

					totalDamages[i].iDamage += totalDamages[j].iDamage;

					totalDamages[i].mapCoord += totalDamages[j].mapCoord;
					totalDamages[i].mapCoordWeight++;

					totalDamages.erase(totalDamages.begin() + j);
					j--;
				}
			}
		}
	}
};

//TODO: wall break effect

struct dc_keybinds;

//////////////////////////////////////////////
/// It's a UI data holder used to shw information
//////////////////////////////////////////////
struct dc_buttoninfo
{
	int TYPE = 0; //0- Map, 1 - Inv, 2-6 Slots, 7 - Chest, 8 - Weapon, 9 - Airdrop
	int chest_id = -1;
	int WeaponListIndex = -1;
	int WeaponBullets = -1;
};

//////////////////////////////////////////////
/// Same as chest, but an airdrop
/// It spawns randomly during a match, takes time to get to the ground
/// Legendary or Mythic loot
//////////////////////////////////////////////
struct dc_airdrop
{
	int airdropid;
	float ClockBegin;
	sf::Vector2f vPosition;
};

//////////////////////////////////////////////
/// Holds all relevant server data from the last tick update
/// Used to save demo files
//////////////////////////////////////////////
struct dc_ticksnapshot
{
	int Tick;
	bool KeyFrame = false;
	dc_unit players[100];
	std::vector<int> ChestOpens;
	std::vector<dc_demo_data> DataCont;
	int DAYTIME;
	float ServerTime;
	dc_ticksnapshot() {};
};

struct dc_match
{
	dc_clock ServerStartClock;
	float ServerTimeLastFrame = 0.f;
	float ServerTime = 0.f;
	bool padding[4096];
	std::vector<dc_buttoninfo> DrawButs;
	int bMatchEnded = 0;
	dc_clock MatchEndClock;
	bool LockInput = false;
	bool ALLOW_CHEATS = true;
	dc_keybinds* KeyBinds;
	dc_map map;
	dc_unit players[100];
	std::vector<dc_airdrop> AirDrops;
	float fTimeTillNextAirdrop;
	int TotalAirdrops = 0;
	int TotalItems = 0;
	int TotalProjectiles = 0;
	int TotalExplosives = 0;
	int MatchType = 0; //0 - Solo Casual, 1 - Solo Competitive
	int PlayerHealReward = 0;
	int weapon_selected_to_swap = -1;
	int camera_follows = 1;
	float camera_width = 10; //min = 10, max = 50

	sf::Vector2f PlayerMarker[4] = { sf::Vector2f(-1,-1),sf::Vector2f(-1,-1),sf::Vector2f(-1,-1),sf::Vector2f(-1,-1) };
	std::vector<dc_projectile> Projectiles;
	std::vector<dc_explosive> Explosives;

	int EasyCases = 450, NormalCases = 370, HardCases = 150, ExpertCases = 30;
	std::vector<float> s_times = { 0.f,45.f,75.f, 150.f,240.f , 330.f,420.f , 480.f,525.f , 570.f,600.0f , 630.f,660.f ,690.0f,705.f,720.0f,730.0f,2500.f };
	std::vector<int> s_damage = { 1,1,1,1,1,1,1,2,2,5,5,7,10,10,10,10,10,10,10,10,10,10 };
	std::vector<float> s_size = { 2000.f,2000.f,2000.f, 2000.f,750.f , 750.f,350.f , 350.f,180.f , 180.f,90.f , 90.f,50.f ,30.f,15.f,5.f,0.f,0.f };

	bool Demo_ShouldEnd = false;
	int DemoRecord = 1;
	int DemoTickBase = 16;
	int TicksTotal = 0;
	dc_demo* pDemo;
	float lastTickTime = 0.f;
	std::vector<dc_ticksnapshot*> Demo_Snapshots;
	dc_ticksnapshot Demo_NewestSnapshot;

	bool show_minimap = false;
	bool show_inventory = false;
	bool canDelete = false;

	sf::Vector2f StormMids[18];
	dc_clock t_clock;
	float timeDiffSinceLastFrame = 0.f;

	bool bBusMoving = true;
	bool bBusJumpable = false;
	sf::Vector2f BusStartPosition;
	sf::Vector2f BusCurrentPosition;
	sf::Vector2f BusEndPosition;
	float MusicLoopSinceLast = 0.05f;

	sf::Vector2f vCameraPosition;
	int vCameraMode = 1; //0 - Free, 1 - Locked
	int vCameraPlayerLock = 0;

	dc_effects effects;
	dc_botdata BotData[100]; //0 is empty as the player is not controlled by the computer


	void Demo_SnapshotUpdateProjectileAdd(sf::Vector2f spawn, float angle, float projspeed);
	void Demo_SnapshotProjectileEnd(int index);
	void Demo_SnapshotUpdateExplosiveAdd(int projectiletype);
	void Demo_SnapshotUpdateExplosives();
	void Demo_SnapshotUpdateExplosiveRemove(int projindex);
	void Demo_SnapshotUpdateWallbreak(sf::Vector2i coord, int wall);
	void Demo_SnapshotUpdateElimination(int killer, int target);
	void Demo_SnapshotUpdateAirdropSpawn(sf::Vector2f spawn, int ADindex);
	void Demo_SnapshotUpdateAirdropRemove(int ADindex);
	void Demo_SnapshotUpdateWeaponShot(sf::Vector2f start, sf::Vector2f end, float time);
	void Demo_SnapshotUpdateItemPickup(int demoitemidx);
	void Demo_SnapshotUpdateItemDrop(int demoitemidx, sf::Vector2f p);
	void Demo_SnapshotUpdateItemSpawn(int demoitemidx, int listix, sf::Vector2f p);
	void Demo_SnapshotUpdateChest(int i);
	void Demo_SnapshotUpdatePlayers();
	void Demo_CreateSnapshotPointers();
	void Demo_CreateSnapshot();
	void Demo_LoopSnapshots();

	//////////////////////////////////////////////
	/// !!! This function should run in a different thread
	/// Until the match finishes, the function keeps converting the demo snapshots
	/// m needs to be a valid pointer for an active match
	/// Metadata should be setup first with a pointer of the same match
	/// When the match is finished, it saves a complete .dem file in the replays/ folder
	//////////////////////////////////////////////
	static void Demo_Convert(dc_match* m, dc_demo_metadata Metadata);


	//////////////////////////////////////////////
	/// Returns the current storm phase ID
	//////////////////////////////////////////////
	int GetCurrentStormPhase();
	//////////////////////////////////////////////
	/// Returns the current damage tick
	//////////////////////////////////////////////
	int GetCurrentStormDamage();
	//////////////////////////////////////////////
	/// Returns the next damage tick
	//////////////////////////////////////////////
	int GetNextStormDamage();
	//////////////////////////////////////////////
	/// Returns the coordinates of the center of the storm
	//////////////////////////////////////////////
	sf::Vector2f GetCurrentStormMiddle();
	//////////////////////////////////////////////
	/// Returns the DIAMETER of the center of the storm
	//////////////////////////////////////////////
	float GetCurrentStormDiameter();
	//////////////////////////////////////////////
	/// Returns the coordinates of the center of the next stormm
	//////////////////////////////////////////////
	sf::Vector2f GetNextStormMiddle();
	//////////////////////////////////////////////
	/// Returns the DIAMETER of the center of the next storm
	//////////////////////////////////////////////
	float GetNextStormDiameter();
	//////////////////////////////////////////////
	/// Hard-coded
	/// Generates the storm information for the entire match
	/// TODO: Read it from a file to make it more customizable
	//////////////////////////////////////////////
	void GenerateStorms();
	//////////////////////////////////////////////
	/// Returns the time till the next storm phase
	//////////////////////////////////////////////
	float GetTimeTillNextStormPhase();
	//////////////////////////////////////////////
	/// Returns the index for the logo of the current storm phase
	//////////////////////////////////////////////
	int GetCurrentStormPhaseLogo();


	//////////////////////////////////////////////
	/// Generates the bus route, including the startpoint, and endpoint of the bus
	//////////////////////////////////////////////
	void GenerateBusRoute();
	//////////////////////////////////////////////
	/// While the bus is moving, it updates its position depending on how much time has passed
	/// while the bus is moving, it iterates the bus music
	//////////////////////////////////////////////
	void SimulateBus();
	
	//////////////////////////////////////////////
	/// Loops the bus music with a dynamic sound that follows the bus
	//////////////////////////////////////////////
	void DoBusMusic();
	//////////////////////////////////////////////
	/// If there is only one player left, it finishes the match
	//////////////////////////////////////////////
	void FinishMatch();

	//////////////////////////////////////////////
	/// Returns a constantly changing color with lightning effects
	/// TODO: Timescale support, and accurate demo representation
	//////////////////////////////////////////////
	sf::Color GetCurrentStormColor();

	//////////////////////////////////////////////
	/// Returns the position of the camera
	//////////////////////////////////////////////
	sf::Vector2f GetCameraPosition();

	//////////////////////////////////////////////
	/// When the player is a spectator, it draws different information on the screen
	/// Including the player's placement and the spectated player's name
	//////////////////////////////////////////////
	void DrawSpectatorInfo();

	//////////////////////////////////////////////
	/// Draws the user marker on the map or shows which direction the marker is at
	//////////////////////////////////////////////
	void DrawMark(sf::Vector2f Coords, sf::Color color, bool ignore_onscreen, sf::Vector2f V);
	//////////////////////////////////////////////
	/// Draws the bus on the map
	//////////////////////////////////////////////
	void DrawBus(sf::Vector2f V);
	//////////////////////////////////////////////
	/// Draws the bus on the map
	/// Used for demo layer rendering
	//////////////////////////////////////////////
	void DrawBus(sf::RenderTexture* T, sf::Vector2f V);
	//////////////////////////////////////////////
	/// Draws everything in the right order
	//////////////////////////////////////////////
	void DrawAll();
	//////////////////////////////////////////////
	/// Draws the storm on teh map
	//////////////////////////////////////////////
	void DrawStorm(sf::Vector2f V);
	//////////////////////////////////////////////
	/// Draws the storm on teh map
	/// Used for demo layer rendering
	//////////////////////////////////////////////
	void DrawStorm(sf::RenderTexture* T,sf::Vector2f V);
	//////////////////////////////////////////////
	/// Draws the storm on the map with V (on map coordinate) being the center of the screen
	//////////////////////////////////////////////
	void DrawMap(sf::Vector2f V);
	//////////////////////////////////////////////
	/// Draws airdrops on the map with V (on map coordinate) being the center of the screen
	//////////////////////////////////////////////
	void DrawAirDrop(sf::Vector2f V);
	//////////////////////////////////////////////
	/// Draws airdrops on the map with V (on map coordinate) being the center of the screen
	/// Used for demo layer rendering
	//////////////////////////////////////////////
	void DrawAirDrop(sf::RenderTexture* T,sf::Vector2f V);
	//////////////////////////////////////////////
	/// When the camera width is too large, it draws a circular indicator on the spectated player
	//////////////////////////////////////////////
	void DrawPlayerIndicator(sf::Vector2f V);
	//////////////////////////////////////////////
	/// Draws all the players on the map with V (on map coordinate) being the center of the screen
	//////////////////////////////////////////////
	void DrawPlayers(sf::Vector2f V); 
	//////////////////////////////////////////////
	/// Draws all the players on the map with V (on map coordinate) being the center of the screen
	/// Used for demo layer rendering
	//////////////////////////////////////////////
	void DrawPlayers(sf::RenderTexture* T,sf::Vector2f V);
	//////////////////////////////////////////////
	/// Draws the small map on the map, if it's open
	/// Otherwise it draws the minimap UI element in the top right corner
	//////////////////////////////////////////////
	void DrawMinimap();
	//////////////////////////////////////////////
	/// Draws players on the small map, if it's open
	//////////////////////////////////////////////
	void DrawPlayersOnMinimapCheat();
	//////////////////////////////////////////////
	/// Draws the current and next storm on the minimap
	//////////////////////////////////////////////
	void DrawStormOnMiniMap();
	//////////////////////////////////////////////
	/// Draws all unopened airdrops on the minimap
	//////////////////////////////////////////////
	void DrawAirDropOnMinimap();
	//////////////////////////////////////////////
	/// Draws every storm on the minimap
	//////////////////////////////////////////////
	void DrawAllStormOnMiniMap();
	//////////////////////////////////////////////
	/// Draws the health, shield bar, inventory, time indicators, markers, and information
	//////////////////////////////////////////////
	void DrawUI(sf::Vector2f V);
	//////////////////////////////////////////////
	/// Draws the inventory page showing information about the item's in the inventory
	//////////////////////////////////////////////
	void DrawInventoryPage();
	//////////////////////////////////////////////
	/// Draws information about which buttons can be pressed to do actions
	//////////////////////////////////////////////
	void DrawHelpButtons();
	//////////////////////////////////////////////
	/// Removes effects that are over
	//////////////////////////////////////////////
	void RemoveExpiredEffects();
	//////////////////////////////////////////////
	/// Draws currently active effects
	//////////////////////////////////////////////
	void DrawEffects(sf::Vector2f V);
	//////////////////////////////////////////////
	/// Draws the crosshair at the position of the mouse
	/// If there is no straight line between the player's unit and the crosshair
	/// A big X is drawn to indicate there is an object between
	//////////////////////////////////////////////
	void DrawCrosshair(sf::Vector2f V);
	//////////////////////////////////////////////
	/// Draws the victory effect
	/// Should only be called when the match is over
	//////////////////////////////////////////////
	void DrawVictoryEffect();
	//////////////////////////////////////////////
	/// Makes projectiles go forward
	/// If a projectile has an object in its way, it damages it, and gets destroyed
	//////////////////////////////////////////////
	void SimulateProjectiles(float timediff, sf::Vector2f V);
	//////////////////////////////////////////////
	/// Draws currently active projectiles
	//////////////////////////////////////////////
	void DrawProjectiles(sf::Vector2f V);
	//////////////////////////////////////////////
	/// Draws currently active projectiles
	/// Used for demo layer rendering
	//////////////////////////////////////////////
	void DrawProjectiles(sf::RenderTexture* T, sf::Vector2f V);
	//////////////////////////////////////////////
	/// Traces rays in a circle with radius ExpRange to simulate an explosion
	//////////////////////////////////////////////
	damagelist_t SimulateExplosion(sf::Vector2f Position, float ExpRange, int DmgMax, int DmgMin);
	//////////////////////////////////////////////
	/// Makes explosive projectiles go forward
	/// If a projectile has an object in its way, it either damages it, and gets destroyed
	/// Or gets bounced in a direction
	//////////////////////////////////////////////
	void SimulateExplosives(float timediff, sf::Vector2f V);
	//////////////////////////////////////////////
	/// Draws currently active explosive projectiles
	//////////////////////////////////////////////
	void DrawExplosives(sf::Vector2f V);
	//////////////////////////////////////////////
	/// Draws currently active explosive projectiles
	/// Used for demo layer rendering
	//////////////////////////////////////////////
	void DrawExplosives(sf::RenderTexture* T, sf::Vector2f V);
	//////////////////////////////////////////////
	/// Plays a gun sound with index listid at world position OriPos
	//////////////////////////////////////////////
	void AddGunShotSound(int listid, sf::Vector2f OriPos);


	//////////////////////////////////////////////
	/// When airdrops should spawn, it spawns 2 airdrops, at random locations in the next circle
	/// In final circles, it purposefully doesn't function
	//////////////////////////////////////////////
	void SimulateAirdrops();
	//////////////////////////////////////////////
	/// Starts a match with 'bs' botcount
	/// Loads the map, generates storms and bus routes
	/// Launches demo recording if it's active in the settings
	//////////////////////////////////////////////
	void Start(int bs);

	//////////////////////////////////////////////
	/// Deletes items that are far out in the storm, with no player nearby
	//////////////////////////////////////////////
	void ClearUnreachableItems();
	//////////////////////////////////////////////
	/// Checks if a player is about to hit a wall
	/// TODO: Player collisions
	//////////////////////////////////////////////
	void CheckCollisions(int i, float t);
	//////////////////////////////////////////////
	/// Long loop of action checks
	/// Better see the definition
	//////////////////////////////////////////////
	void LoopPlayers();
	//////////////////////////////////////////////
	/// User action function to check if the cursor is over a chest
	/// If the cursor is on a chest, and it's close to their unit
	/// An indicator shows which button the user has to press
	/// If they press that button, the opening process starts
	/// This function is also used with airdrops
	//////////////////////////////////////////////
	bool OverChest();
	//////////////////////////////////////////////
	/// User action function to check if the cursor is over an item
	/// If the cursor is on an item, and it's close to their unit
	/// An indicator shows which button the user has to press
	/// If they press that button, and there is space in their inventory, the item gets picked up
	/// This function is also used with airdrops
	//////////////////////////////////////////////
	bool OverItem();
	//////////////////////////////////////////////
	/// All user action functions in a function
	/// timediff is used for Descend action
	//////////////////////////////////////////////
	void Control(float timediff);
	//////////////////////////////////////////////
	/// All user action functions in a function
	/// Used when the inventory is open
	//////////////////////////////////////////////
	void ControlInventory();
	//////////////////////////////////////////////
	/// All user action functions in a function
	/// Used when the minimap is open
	/// timediff is used for Descend action
	//////////////////////////////////////////////
	void ControlMinimap(float diff);
	//////////////////////////////////////////////
	/// User action function for moving on the map
	/// Alternative movement is moving the unit as it was facing the cursor
	/// Non-alternative movement is moving the unit as it was facing up
	//////////////////////////////////////////////
	void ControlMove();
	//////////////////////////////////////////////
	/// Non-user action for unit with ID 'player'
	/// Checks if the current location of the unit is in a named POI
	/// If it is a named POI, it marks it as a visited POI for the match
	//////////////////////////////////////////////
	void PlayerCheckCurrentLocationForData(int player);
	//////////////////////////////////////////////
	/// Player's call to jump off the bus
	//////////////////////////////////////////////
	void PlayerJumpOffBus(int player);
	//////////////////////////////////////////////
	/// Player's call to descend for unit with ID 'player'
	/// There is also a non-player descend call
	//////////////////////////////////////////////
	void PlayerDescent(int player, float diff, float speed);
	//////////////////////////////////////////////
	/// Player's call to open the airdrop with ID 'airdrop_id' for unit with ID 'player'
	//////////////////////////////////////////////
	void PlayerOpenAirdrop(int player, int airdrop_id);
	//////////////////////////////////////////////
	/// Player's call to open the airdrop with ID 'unit_id' for unit with ID 'player'
	//////////////////////////////////////////////
	void PlayerOpenChest(int player, int chest_id);
	//////////////////////////////////////////////
	/// Player's call to pick up the item with ID 'itemid' for unit with ID 'player'
	/// TODO: remove slot, or add a function that sorts consumables to the right on pickup
	//////////////////////////////////////////////
	void PlayerPickupItem(int player, int slot, int itemid);
	//////////////////////////////////////////////
	/// Player's call to use the selected healing item
	/// Should be only called in PlayerShootWeapon()
	//////////////////////////////////////////////
	void PlayerUseHeal(int player);
	//////////////////////////////////////////////
	/// Player's call to drop the item from the 'weaponslot'th weapon-slot for unit with ID 'player'
	/// When used, the item gets destroyed
	/// A new item is spawned on the map
	//////////////////////////////////////////////
	void PlayerDropWeapon(int player, int weaponslot);
	//////////////////////////////////////////////
	/// Player's call to swap to the item from the 'weaponslot'th weapon-slot for unit with ID 'player'
	//////////////////////////////////////////////
	void PlayerSwapWeapon(int player, int weaponslot);
	//////////////////////////////////////////////
	/// Player's call to swap the item from 'slotFrom' to 'slotTo'
	/// These items are exchanged entirely
	/// If the unit has iSelectedWeapon == slotFrom || iSelectedWeapon == slotTo, the iSelectedWeapon also changes
	/// This is to avoid abusing fancy glitches
	//////////////////////////////////////////////
	void PlayerSwapWeaponInventory(int player, int slotFrom, int slotTo);
	//////////////////////////////////////////////
	/// Casts a ray from the player's position ignoring the player
	/// Checks if there is any wall or player in the way of the bullet
	/// Returns the result of the cast
	/// Note: This adds a bulletshot-effect to the vector
	//////////////////////////////////////////////
	damageinfo_t SimulateBullet(int player);
	//////////////////////////////////////////////
	/// Player's call to use its selected item for unit with ID 'player'
	/// It calls PlayerShootWeapon0 for single-shot weapons
	/// It calls PlayerShootWeapon1 for multi-shot weapons
	/// It calls PlayerShootWeapon2 for projectile weapons
	/// It calls PlayerShootWeapon1 for explosive weapons
	/// It calls PlayerUseHeal for healing items
	//////////////////////////////////////////////
	void PlayerShootWeapon(int player);
	//////////////////////////////////////////////
	/// Fires a single bullet, applies the damage if anything is hit
	/// If the bullet hit's another unit, and it dies, it applies elimination effects and recognition
	//////////////////////////////////////////////
	void PlayerShootWeapon0(int player);
	//////////////////////////////////////////////
	/// Fires multiple bullets, applies the damage if anything is hit (for all hit objects)
	/// If the bullet hit's another unit, and it dies, it applies elimination effects and recognition
	//////////////////////////////////////////////
	void PlayerShootWeapon1(int player);
	//////////////////////////////////////////////
	/// Fires a projectile, adds it to the projectile list
	//////////////////////////////////////////////
	void PlayerShootWeapon2(int player);
	//////////////////////////////////////////////
	/// Fires an explosive projectile, adds it to the explosive list
	//////////////////////////////////////////////
	void PlayerShootWeapon3(int player);
	//////////////////////////////////////////////
	/// Player's call to reload the weapon for unit with ID 'player'
	//////////////////////////////////////////////
	void PlayerReloadWeapon(int player);
	//////////////////////////////////////////////
	/// This is used to completely eliminate the unit with ID 'player'
	/// It updates placement, and drops all the items
	/// It also adds a kill-effect
	//////////////////////////////////////////////
	void PlayerKill(int player);
	//////////////////////////////////////////////
	/// Progressively heals the unit with ID 'player' in arena game-mode
	/// Does nothing otherwise
	//////////////////////////////////////////////
	void PlayerRewardForKill(int player);
	//////////////////////////////////////////////
	/// Player's call to move the unit with ID 'player' to the direction of 'angle'
	//////////////////////////////////////////////
	void PlayerMove(int player, float angle);
	//////////////////////////////////////////////
	/// This function makes footstep sounds for all units if they travelled enough
	//////////////////////////////////////////////
	void SimulateFootsteps();
	//////////////////////////////////////////////
	/// This function makes all the draw, loop, and simulation calls
	//////////////////////////////////////////////
	void Do();
	//////////////////////////////////////////////
	/// This function does not exist ;)
	//////////////////////////////////////////////
	void DoCheatStuff();
	//////////////////////////////////////////////
	/// User's call to change the horizontal amount of blocks rendered
	/// It changes the camera_width on scrollup, and scrolldown
	//////////////////////////////////////////////
	void ScrollMap();


	dc_tracedata TracePlayers(sf::Vector2f a, sf::Vector2f b, int skip);


	void BotGiveNames();
	void BotBegin(int easyCase, int normalCase, int hardCase, int expertCase);
	void BotJumpoffBus(int id);
	void BotDescend(int id, float diff); //Only descends when should
	void BotFreefallMove(int id, float diff);
	void BotLowFreefallMove(int id,float diff);
	void BotCalculatePath(int id, sf::Vector2f Target);
	void BotMoveToNextPoint(int id, float diff);
	bool BotNeedsToLoot(int id);
	void BotCheckOpenChests(int id, bool force_it);
	int BotGetClosestChest(int id);
	void BotLoot(int id);
	int BotIsNeededItem(int id, int itemlistid);
	void BotSortInventory(int id);
	int BotShouldHeal(int id);
	void BotDoHeal(int id);
	void BotCheckStuff(int id, float diff);
	bool BotShouldGoToZone(int id);
	void BotGoToZone(int id);
	void BotDoTheMove(int id, float diff);
	void BotDoTheMoveInFight(int id, float diff);
	int BotHasItemNearby(int id);
	int BotHasForceHealNearby(int id);


	void BotGoToTheItem(int id, int itemid, int force = 0);
	bool BotCheckHeal(int id, int listid);
	bool BotCanRaid(int id) { return BotData[id].Changables.DistantTargetType == 0; }
	void BotRaid(int id);
	void BotSwapToJustInCaseWeapon(int id);
	void BotSwapWeaponInFight(int id);
	void BotSwapToEmergencyWeapon(int id);
	void BotCorrectAngleNew(int id, float diff, float neededang, float speed, float corr);
	void BotNoticePlayers(int id);
	bool BotHasUsableWeapon(int id, float range);
	bool BotHasRealNoticed(int id) { return BotData[id].Changables.NoticedPlayerIDs.size() > 0 && BotData[id].Changables.NoticedPlayers[0].NoticeTime.GetDiff() > 1000.f*BotData[id].fEnemyNoticeTime; }
	bool BotHasRealTarget(int id);
	bool BotShouldBailOffFight(int id);
	float BotFindBestBailAngle(int id);
	void BotBailOffFight(int id);
	bool BotShouldRushOpponent(int id);
	void BotRushOpponent(int id);
	void BotAimOnTarget(int id, float diff);
	void BotDoDodge(int id);
	bool BotShouldBailInFight(int id);
	void BotBailInFight(int id);
	void BotClearUnnecesaryMovepathInFight(int id);
	bool BotShouldShootWeapon(int id);
	void BotShoot(int id);
	void BotRemoveObstacle(int id, float diff);
	bool BotReloadWeapons(int id);
	float GetBotModifiedDistance(sf::Vector2f a, sf::Vector2f b);
	bool BotShouldCoverAirDrop(int id);
	bool BotShouldGetAirDrop(int id);
	void BotCoverAirDrop(int id);
	void BotGetAirDrop(int id);

	//TODO: Bot More Memory


	void BotDodge(int id, int diff);
	void BotPickupNearbyLoot(int id);
	void BotSeekChest(int id);
	void BotAttack(int id);
	void BotCorrectAngle(int id, int diff);
	void BotGetUsefulWeapon(int id);
	void BotThink(int id, float diff);
	void BotMoveToPoint(int id);
	void BotShouldCalculatePath(int id);
	bool BotHeal(int id);
	bool BotReload(int id);
	void BotCorrectAngle(int id, float angle, int diff);

	std::vector<int> GetKillLeaders();
	void PrintAllWeaponDPS();
	int GetLowestPlayerID();
	int GetAlivePlayers();
	int GetClosestChestIDToPlayer(int pl);
	int GetClosestChestToPosition(sf::Vector2f pos);
	int GetAvailableChestNumber();
	std::vector<int> GetAvailableChests(sf::Vector2f Mid, float radius);
	int GetClosestChestWithExceptions(sf::Vector2f Mid, std::vector<int> Exceptions);
	float IsPointInStorm(sf::Vector2f p);

	void CreateMovementMap();
	void CreateSmallMovementMap(sf::Vector2i vMid, sf::Vector2i siz, sf::Vector2i vTar);

	bool GetKeyStatus(int KEY, bool Continuous);


	sf::Vector2f Bounce(sf::Vector2f inDirVector, sf::Vector2f wallA, sf::Vector2f wallB);

private:
	bool p_bShouldUpdatelines = true;
};


struct dc_mapeditor
{
	dc_clock clock;
	dc_map map;
	sf::Vector2f vecCamera;
	float camera_width = 10.f;
	int texture_selected = 0;

	int mode = 1;
	int wall_health = 100;
	int wall_type = -1;
	bool show_minimap = false;
	bool edit_label = false;

	dc_label label;


	void TextureBrush();
	void LineBrush();
	void ChestBrush();
	void LabelBrush();
	void CopyTexture();
	void LabelEdit();
	


	void DrawSelectedBox();
	void DrawUI();
	void DrawAll();
	void Do();
	void Control();
	void Start();
	void MoveTexture(int m);
	void MoveHealth(int n);
	void PaintBrush();
	void PaintBrushPart(int x, int y, bool initiator);
	void __debug_draw_label_circles();

	static void DrawSaveScreen(char* name, float percent);
	void Save();
	void Load();

};


















struct dc_textures
{
	std::vector<sf::Texture> t;
	std::vector<sf::Color> ac;
	std::vector<char*> nam;

	void add(char* n);
	//void add(sf::Texture tex);
	sf::Texture* get(int id);
	char* getname(int id);
	sf::Color getavgcolor(int id);
	static void define_all();
};


struct dc_convar
{
	bool Cheat = false;
	float Value;
	char CommandName[64];
	void(*Execute)();

	dc_convar() {};
	dc_convar(float iValue, char* iName) { sprintf(CommandName, iName); Value = iValue; }
	dc_convar(float iValue, char* iName, bool cheat) {
		sprintf(CommandName, iName); Value = iValue; Cheat = cheat;
	}
};

#define ConVar(a,b,c) dc_convar a = dc_convar(c,b)
#define ConVarCheat(a,b,c) dc_convar a = dc_convar(c,b,true)

struct dc_consolelog
{
	char* msg = nullptr;
	sf::Color Color;

	dc_consolelog() {};
	
	dc_consolelog(char* Msg, sf::Color mColor) { Color = mColor; msg = new char[strlen(Msg) + 1]; sprintf(msg, Msg); }

	template <typename... Args> dc_consolelog(char* Msg, sf::Color mColor, Args... args)
	{
		size_t bufsz = snprintf(NULL, 0, Msg, args...);
		msg = new char[bufsz+4];
		sprintf(msg, Msg, args...);
		Color = mColor;
	}
	
	~dc_consolelog()
	{
		if (msg != nullptr)delete[]msg;
	}
};

enum DEMO_PLAYERDATA_IND
{
	DMPD_BUSJUMP,
	DMPD_POSCHANGE,
	DMPD_HPCHANGE,
	DMPD_ROTCHANGE,
	DMPD_WPCHANGE,
};

struct dc_demo_playerdata
{
	sf::Vector2i bBusJumpTick = sf::Vector2i(100000,0);
	std::vector<sf::Vector2i> PositionChanges;
	std::vector<sf::Vector2i> HealthChanges;
	std::vector<sf::Vector2i> RotChanges;
	std::vector<sf::Vector2i> WeapChanges;
	std::vector<sf::Vector2i> GetPreviousChanges(int tick);
};

struct dc_demo_itemdata
{
	std::vector<sf::Vector2i> spawns;
	std::vector<int> despawns;
	int listidx;

	sf::Vector2i is_alive(int tick); // If !Alive returns (-1,0), if Alive returns demodata indexes (tick,data)
	
	dc_demo_itemdata() {};
	dc_demo_itemdata(int lidx) { listidx = lidx; }
};

struct dc_demo_explosivedata
{
	sf::Vector2i spawn;
	sf::Vector2i end = sf::Vector2i(100000,0);
	std::vector<sf::Vector2i> updates;



	dc_demo_explosivedata() {}
	dc_demo_explosivedata(sf::Vector2i sp) { spawn = sp; }

	sf::Vector2i GetPositionDemoData(int tick)
	{
		for (auto u : updates)
		{
			if (u.x == tick)return u;
		}
		return { -1,0 };
	}
};

struct dc_demo_mapdata
{
	std::vector<sf::Vector2i> ChestOpens;
	std::vector<sf::Vector2i> WallBreaks;

	std::vector<dc_demo_itemdata> Items;
	std::vector<sf::Vector2i> TimeChanges;
	std::vector<sf::Vector2i> AirDropSpawns;
	std::vector<sf::Vector2i> AirDropOpens;
	std::vector<sf::Vector2i> ProjectileSpawns;
	std::vector<sf::Vector2i> ProjectileEnds;

	std::vector<dc_demo_explosivedata> ExplosiveData;

	//std::vector<sf::Vector2i> GetPreviousChanges(int tick);
};


struct dc_demo_renderlayer
{
	char Name[32] = "Default";
	sf::RenderTexture* T = nullptr;
	int Type = 0; //0 - RealWorld, 1 - DOF
	sf::Color BackgroundColor = sf::Color(255,255,255);
	bool AllowMap = true;
	bool AllowChests = true;
	bool AllowShadows = true;
	bool AllowItems = true;
	bool AllowPlayers = true;
	bool AllowShootEffects = true;
	bool AllowExplosives = true;
	bool AllowDamageEffects = true;
	bool AllowStorm = true;

	bool Should_Render = true;
	bool Should_Export = false;

	dc_demo_renderlayer(){}
};


//TODO: Match - memory leak fix
struct dc_demo_viewer
{
	int Takes = 0;
	int Frame = 0;
	bool Recording = false;
	bool LockInput = false;
	float timeDiffSinceLastFrame = 0.f;

	float ServerTime = 0.5f;
	float DemoTotalTime;

	dc_keybinds* KeyBinds;

	std::vector<dc_demo_renderlayer> RenderingLayers;

	std::vector<sf::Vector2i> Servertime_Updates;
	dc_demo_playerdata PlayerData[100];
	dc_demo_mapdata MapData;
	std::vector<sf::Vector2i> EliminationData;
	
	static void DrawOnRenderLayer(dc_demo_viewer* DV, int layer);
	
	dc_demo Demo;
	dc_match Match;
	sf::Vector2f vCameraPosition = sf::Vector2f(500.f,500.f);
	int vCameraMode = 0; //0 - Free, 1 - Locked
	int vCameraPlayerLock = 0;
	sf::Vector2f GetCameraPosition();

	void ProcessDemoData();
	void Setup();
	int GetPreviousTick(float time);
	int GetNextTick(float time);

	void JumpToTime(float time);

	void Do();

	void DrawKillNoticeEffect();
	void DrawEffectsModified(sf::Vector2f V);
	void DrawEffectsModified(dc_demo_renderlayer* R,sf::Vector2f V);
	void DrawUI();
	void DrawInformation();
	void DrawTimebar();
	void DoTimebar();
	void DrawPlayerInfo();
	void DoPlayerInfo();
	void DrawKillLeaders();
	void DoKillLeaders();


	float CameraSpeed = 75.f;
	float CameraWidth = 10.f;
	
	void DoSpeedUp();
	void DoMove();
	void DoScroll();
	
	void Record();

	bool GetKeyStatus(int KEY, bool Continuous);
};


struct dc_config
{
	ConVar(mastervolume, "mastervolume", 0.5f);
	ConVar(gm_cheats, "gm_cheats", 0.f);
	ConVar(fps_enable, "fps_enable", 0.f);
	ConVar(fps_max, "fps_max", 60.f);
	//ConVar(g_antialias_level, "g_antialias_level", 0);
	ConVar(p_movement_type, "p_movement_type", 0); //0 doesn't depend on angle, 1 Depends on angle
	ConVar(con_silent, "con_silent", 0);
	ConVar(g_res_x,"g_res_x", 1024);
	ConVar(g_res_y, "g_res_y", 768);
	ConVar(g_brightness, "g_brightness", 1.f);
	ConVar(g_fullscreen, "g_fullscreen", 0.f);

	ConVar(m_record_replay, "m_record_replay", 1.f);
	ConVar(demo_framerate, "demo_framerate", 0.f);
	ConVar(demo_timescale, "demo_timescale", 1.f);

	ConVarCheat(ch_bot_stop, "ch_bot_stop", 0.f);
	ConVarCheat(ch_show_players_on_map, "ch_show_players_on_map", 0.f);
	ConVarCheat(ch_debug_info, "ch_debug_info", 0.f);
	ConVarCheat(ch_teleportmarker, "ch_teleportmarker", 0.f);
	ConVarCheat(ch_debug_mode, "ch_debug_mode", 0.f);

	void LoadConfig(char* name);
	void SaveConfig(char* name);

	dc_convar* GetConVar(int index);
	sf::Vector2i EditCVar(char* inputtext);
};
extern dc_config g_Config;

enum dc_keyactions
{
	DCK_SHOOT,
	DCK_UP,
	DCK_DOWN,
	DCK_RIGHT,
	DCK_LEFT,
	DCK_RELOAD,
	DCK_SLOT1,
	DCK_SLOT2,
	DCK_SLOT3,
	DCK_SLOT4,
	DCK_SLOT5,
	DCK_DROPITEM,
	DCK_OPENINVENTORY,
	DCK_OPENMINIMAP,
	DCK_MARKERPLACE,
	DCK_MARKERREMOVE,
	DCK_OPENCONSOLE,
	DCK_JUMPOFFBUS,
	DCK_DESCEND,
	DCK_ALTERNATIVE,
	DCK_CLOSEMENU,
	DCK_SWAP_TO_OTHER_PLAYER,
	DCK_CONSOLE_ENTER
};

struct dc_keybinds
{

	unsigned char KeysPrimary[32];
	unsigned char KeysSecondary[32];

	int find(char ACT)
	{
		if (KeysPrimary[ACT])return KeysPrimary[ACT];
		else  if (KeysSecondary[ACT])return KeysSecondary[ACT];
		return -1;
		for (int i = 0; i < 32; i++)if (ACT == KeysPrimary[i])return KeysPrimary[i];
		for (int i = 0; i < 32; i++)if (ACT == KeysSecondary[i])return KeysSecondary[i];
		return -1;
	}
};

struct dc_quest
{
	bool Finished = false;
	int tierReward;
	int type; //0 - kill, 1 - killatplace, 2 - chest, 3 - chestatplace, 4 - land at, 5- visit 3 places, 6- place top10, 7- placetop25
	int killweapontype; //0 - all, 1 - pistol, 2 - smg, 3- shotgun, 4- rifle, 5 - sniper, 6- explosive, 7 - mg
	int location1 = -1, location2 = -1, location3 = -1;
	int needed;
	int totalNeeded;
	bool oneMatch = false;

	void Init();
};

struct dc_questdoneeffect
{
	dc_quest Quest;
	dc_clock Clock;

	void draw();
};

struct dc_lockergoteffect
{
	void* lockerUnlockable;
	dc_clock Clock;

	void draw();
};


struct dc_gameeffect
{
	std::vector<dc_questdoneeffect> QD_Effects;
	std::vector<dc_lockergoteffect> LG_Effects;
};

struct dc_playerprofile
{
	int lastGamemode = 0; //0 - Regular Solo, 1 - Arena Solo
	int Level = 0;
	int Xp = 0;
	int Tier = 0;
	int TierStars = 0;
	char szName[64] = "PlayerDefault";

	int TotalDamage = 0;
	int TotalMatches = 0;
	int TotalKills = 0;
	int TotalPistolKills = 0;
	int TotalSubmachinegunKills = 0;
	int TotalShotgunKills = 0;
	int TotalRifleKills = 0;
	int TotalSniperKills = 0;
	int TotalExplosiveKills = 0;
	int TotalMachinegunKills = 0;


	int TotalWins = 0;
	int TotalPlacement = 0;
	int TotalTop25s = 0;
	int TotalTop10s = 0;


	dc_stats LastMatchStats;

	int LastMatchKills = 0;
	int LastMatchPlacement = 0;

	int DistanceTravelledHigh = 0;
	float DistanceTravelledLow = 0.f;
	int TotalTimeAlive = 0;

	int QuestsFinished = 0;

	bool SkinUnlocked[32];
	bool GliderUnlocked[16];
	bool WrapUnlocked[8];

	char SelectedSkin = 0, SelectedGlider = 0, SelectedWrap = 0;
	dc_quest Quests[2];

	int ArenaPoints = 0;
	char padding[32];

	dc_playerprofile() {};
	dc_playerprofile(const dc_playerprofile& right)
	{

		ArenaPoints = right.ArenaPoints;
		DistanceTravelledHigh = right.DistanceTravelledHigh;
		DistanceTravelledLow = right.DistanceTravelledLow;
		for (int i = 0; i < 16; i++)
			GliderUnlocked[i] = right.GliderUnlocked[i];
		LastMatchKills = right.LastMatchKills;
		LastMatchPlacement = right.LastMatchPlacement;
		//LastMatchStats = right.LastMatchStats;
		Level = right.Level;
		Quests[0] = right.Quests[0];
		Quests[1] = right.Quests[1];
		QuestsFinished = right.QuestsFinished;
		SelectedGlider = right.SelectedGlider;
		SelectedSkin = right.SelectedSkin;
		SelectedWrap = right.SelectedWrap;
		for (int i = 0; i < 32; i++)
			SkinUnlocked[i] = right.SkinUnlocked[i];
		sprintf(szName, right.szName);
		Tier = right.Tier;
		TierStars = right.TierStars;
		TotalDamage = right.TotalDamage;
		TotalExplosiveKills = right.TotalExplosiveKills;
		TotalKills = right.TotalKills;
		TotalMachinegunKills = right.TotalMachinegunKills;
		TotalMatches = right.TotalMatches;
		TotalPistolKills = right.TotalPistolKills;
		TotalPlacement = right.TotalPlacement;
		TotalRifleKills = right.TotalRifleKills;
		TotalShotgunKills = right.TotalShotgunKills;
		TotalSniperKills = right.TotalSniperKills;
		TotalSubmachinegunKills = right.TotalTimeAlive;
		TotalTimeAlive = right.TotalTimeAlive;
		TotalTop10s = right.TotalTop10s;
		TotalTop25s = right.TotalTop25s;
		TotalWins = right.TotalWins;
		for (int i = 0; i < 8; i++)
			WrapUnlocked[i] = right.WrapUnlocked[i];
		Xp = right.Xp;
	}

	dc_playerprofile operator=(const dc_playerprofile& right)
	{

		ArenaPoints = right.ArenaPoints;
		DistanceTravelledHigh = right.DistanceTravelledHigh;
		DistanceTravelledLow = right.DistanceTravelledLow;
		for (int i = 0; i < 16; i++)
			GliderUnlocked[i] = right.GliderUnlocked[i];
		LastMatchKills = right.LastMatchKills;
		LastMatchPlacement = right.LastMatchPlacement;
		//LastMatchStats = right.LastMatchStats;
		Level = right.Level;
		Quests[0] = right.Quests[0];
		Quests[1] = right.Quests[1];
		QuestsFinished = right.QuestsFinished;
		SelectedGlider = right.SelectedGlider;
		SelectedSkin = right.SelectedSkin;
		SelectedWrap = right.SelectedWrap;
		for (int i = 0; i < 32; i++)
			SkinUnlocked[i] = right.SkinUnlocked[i];
		sprintf(szName, right.szName);
		Tier = right.Tier;
		TierStars = right.TierStars;
		TotalDamage = right.TotalDamage;
		TotalExplosiveKills = right.TotalExplosiveKills;
		TotalKills = right.TotalKills;
		TotalMachinegunKills = right.TotalMachinegunKills;
		TotalMatches = right.TotalMatches;
		TotalPistolKills = right.TotalPistolKills;
		TotalPlacement = right.TotalPlacement;
		TotalRifleKills = right.TotalRifleKills;
		TotalShotgunKills = right.TotalShotgunKills;
		TotalSniperKills = right.TotalSniperKills;
		TotalSubmachinegunKills = right.TotalTimeAlive;
		TotalTimeAlive = right.TotalTimeAlive;
		TotalTop10s = right.TotalTop10s;
		TotalTop25s = right.TotalTop25s;
		TotalWins = right.TotalWins;
		for (int i = 0; i < 8; i++)
			WrapUnlocked[i] = right.WrapUnlocked[i];
		Xp = right.Xp;

		return *this;
	}
};

struct dc_lockerunlockable
{
	int Type = 0; //0 = Skin, 1 = Glider, 2 = Wrap
	int Index = 0;
	int Tier = 0;
	int iRarity = 0;
	char szName[64];
	dc_lockerunlockable() {};
	dc_lockerunlockable(int typ, int ind, int tie, int Rar, char* nam) {
		Type = typ, Index = ind, Tier = tie; iRarity = Rar; sprintf(szName, nam);
	};
};



struct dc_game
{
	char PrePadding[128];
	dc_playerprofile ThePlayer;
	char Padding[128];
	bool LockInput = false;

	int console_pos = 0;
	std::vector<dc_consolelog*> ConsoleLogs;
	int GM_STATE = 0; // 0- Lobby, 1 - InGame, 2 - Player Statistics, 3 - Settings, 4 - Demo Menu, 5 - Locker, 6 - Credits, 7 - In Demo
	int MatchType = 0; //0- Solo, 1 - Arena Solo
	dc_match* Match = nullptr;
	dc_demo_viewer* DViewer = nullptr;
	int OW_STATUS = 0; //0-Nothing, 1 - Console, 2 - Esc Menu, 3 - Settings Menu, 4 - ShowstatsMenu, 5 - Quitprompt, 6 - Press Key, 7 - IngamePressKey
	dc_keybinds Binds;
	bool bNameEditSelected = false;

	int Cloud1Index=-1;
	int Cloud2Index=-1;
	std::vector<dc_lockerunlockable> Unlockables;
	std::vector<char*> cfgNames;
	std::vector<dc_consolelog*> OldConsoleMessages;
	char ConsoleMessage[128] = "\0";
	int ConsoleMessageIndex = 0;

	dc_gameeffect Effects;


	void DrawEffects();
	void RemoveExpiredEffects();
	int TotalEffectCount();

	void SetupUnlockables();
	void SetupDefaultBinds();
	void Setup();
	bool HasMatch();
	void StartNewMatch();
	void StartNewDemoViewer(char* buffer);
	void OpenConsole() { OW_STATUS = 1; }
	void CloseConsole() { OW_STATUS = 0; }
	void LogMessage(char* msg, sf::Color color);
	int CalcExpForMatch();
	void EvaluateMatch();
	void EvaluateMatchForQuests();
	int GetEvaluateMatchForQuests(int i);

	int GetXpNeededForLevel(int level);
	void CheckLevels();
	void CheckTiers();
	int GetArenaLevel();
	int GetArenaNeededForNextLevel();
	void EvaluateMatchForArenaPoints();
	std::vector<int> GetBotDifficultiesForArenaLevel(int i);

	void LogConsoleMessage();
	template <typename... Args> void LogMessage(char* msg, sf::Color color, Args... args)
	{
		if (g_Config.con_silent.Value >= 1.f)return;
		dc_consolelog* m = new dc_consolelog(msg, color,args...);
		ConsoleLogs.push_back(m);
		ConsoleMessageIndex = 0;
	}
	void LogError(char* msg)
	{
		auto orval = g_Config.con_silent.Value;
		g_Config.con_silent.Value = 0.f;
		LogMessage(msg, sf::Color(192, 0, 0));
		g_Config.con_silent.Value = orval;
	}
	template <typename... Args> void LogError(char* msg, Args... args)
	{
		auto orval = g_Config.con_silent.Value;
		g_Config.con_silent.Value = 0.f;
		LogMessage(msg, sf::Color(192, 0, 0), args...); 
		g_Config.con_silent.Value = orval;
	}

	void DrawIngameSettingsMenu();
	void DoIngameSettingsMenu();
	void DrawShowStatsMenu();
	void DoShowStatsMenu();

	void DrawBackButton();
	void DoBackButton();

	void DrawQuitButton();
	void DrawQuitPrompt();
	void DoQuitButton();
	void DoQuitPrompt();

	int CharacterVisionStatus = 0; //0 - only character, 1 - glider, 2 - weapon wrap + player
	void DoMainMenuCharacterVision();
	void DrawMainMenuCharacterVision();




	void Quit();

	void DrawIngameEscapeMenu();
	void DoIngameEscapeMenu();

	void DrawInDemoEscapeMenu();
	void DoInDemoEscapeMenu();

	void DrawMainMenu();
	void DoMainMenu();
	void DrawMainMenuBg();
	void DrawMainMenuPlayButton();
	void DrawMainMenuPlayerProfile();
	void DrawMainMenuMap();
	void DrawLeftSideMenubar();
	void DoLeftSideMenubar();

	int DrawChallenge(int i,int x, int y, int w, int h);
	int DrawChallengeWithProgress(int i, int x, int y, int w, int h);

	void Do();

	void DrawStatisticsMenu();
	void DoStatisticsMenu();


	int SettingKeySelected = -1;
	int SettingPrimerity = -1; // 0 - Primary, 1 - Secondary
	int PressKeyWaitFrames = 2;
	int SettingFullscreen = 0;
	int SelectedVideoSetting = 0;
	int SettingsState = 0;
	void DrawSettingsMenu();
	void DoSettingsMenu();
	void DrawPressKeyOL();
	void DoPressKeyOL();

	int LockerPush = 0;
	void DrawLockerItemShowCase(int lu_index);
	void DrawLockerMenuNextUnlockables();
	void DrawLockerMenu();
	void DoLockerMenu();

	void DrawCreditsMenu();
	void DoCreditsMenu();
	
	int DemoCoordinate = 0;
	int DemoSelected = -1;
	std::vector<std::string> GetAllDemoNames(bool Update = false);
	void DrawDemoMenu();
	void DoDemoMenu();


	std::vector<int> GetUnlockedIndexes(int type);
	void DrawLockerInventory();
	void DoLockerInventory();

	void DrawConsole();
	void DoConsole();
	void ConsoleExecuteCommand(char* cm);
	void ScrollConsole();
	void MoveConsoleMessages();


	std::vector<char*> GetAllNonCvarCommands();
	std::vector<char*> GetAllConvars();



	bool cmdSpawn(char* cm);
	bool cmdEcho(char* cm,sf::Vector2i trim);
	bool cmdClear(char* cm);
	bool cmdPlayer(char* cm);
	bool cmdCamera(char* cm);
	bool cmdTime(char* cm);
	bool cmdDPS(char* cm);
	bool cmdCommands(char* cm);
	bool cmdConvars(char* cm);
	bool cmdFind(char* cm);
	bool cmdPlaysound(char* cm);
	bool cmdPlaysoundrel(char* cm);
	bool cmdBind(char* cm);
	bool cmdUnbind(char* cm);
	bool cmdExec(char* cm);
	bool cmdLayer(char* cm);
	bool cmdBot(char* cm);

	bool GetKeyStatus(int KEY, bool Continuous);

	bool LoadConfig(char* name);
	void SaveConfig(char* name);
	bool LoadProfile();
	void SaveProfile();

	std::vector<char*> GetAllKeyNames();
	std::vector<char*> GetAllActNames();

	void show_fps();
};


extern dc_textures g_Textures;