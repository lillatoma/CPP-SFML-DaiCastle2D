#include "DaiCastle.h"

std::vector<dc_item> g_Items;

std::vector<int> lootpool;

void add_to_lootpool(int what, int howmany)
{
	for (int i = 0; i < howmany; i++)lootpool.push_back(what);
}


int dc_item::GetRandom()
{
	return lootpool[Random(0, lootpool.size() - 1)];
}

void dc_item::create(int type, sf::Vector2f pos)
{
	for (int i = 0; i < sizeof(dc_item); i++)
	{
		*(((char*)this) + i) = *(((char*)&g_Items[type]) + i);
		
	}
	vPosition = pos;
}


//common: ~50;
//uncommon: ~ 25;
//rare: ~15
//epic: ~7
//legendary: ~3

#define PISTOL_START 11
#define PISTOL_END 100
#define SMG_START 101
#define SMG_END 200
#define AR_START 201
#define AR_END 300
#define SHOTGUN_START 401
#define SHOTGUN_END 500
#define HEAL_START 1000

bool dc_item::is_for_bot(dc_item* It)
{
	if (iDamageStart == It->iDamageStart && iDamageEnd == It->iDamageEnd && id == It->id)return true;
	return false;
}

float dc_item::GetPrimitiveDPS(float distance)
{
	if (iType > 3)return 0;

	auto dmg = iDamageEnd - (iDamageEnd - iDamageStart)*(fRange - distance) / fRange;

	if (distance > fRange)return 0;
	else return dmg*fFirerate;
}

float dc_item::CalculateDPS(float distance, bool standing)
{
	if (IsHeal())return 0;
	if (distance > fRange)return 0;
	float totalDamage = 0.f;
	float timeElapsed = 0.f;
	int dmg_per_shot = iDamageEnd - (iDamageEnd - iDamageStart)*(fRange - distance) / fRange;
	float target_total_angle = 2*(atan(0.25f / distance) * 180 / PI);

	float bloomSize = fBloomMovingMinSize;
	if (standing)bloomSize = fBloomMinSize;

	float bloomDecrease = fBloomMovingDecrease;
	if (standing)bloomDecrease = fBloomStandingDecrease;

	float timeBetweenShots = 1.f / fFirerate;

	if (iType == 0 || iType == 2)
	{
		for (int i = 0; i < iMaxBullets; i+=iBulletConsumption)
		{
			float shot_percentage = min(1.f, target_total_angle/bloomSize);
			totalDamage += dmg_per_shot*shot_percentage;
			if (i == 0)			totalDamage += dmg_per_shot*shot_percentage;
			timeElapsed += timeBetweenShots;
			bloomSize += fBloomShootIncrease;
			if (bloomSize > fBloomMaxSize)bloomSize = fBloomMaxSize;
			bloomSize -= bloomDecrease*timeBetweenShots;
			if (bloomSize < 0)bloomSize = 0;

		}
	}

	if (iType == 1)
	{
		for (int i = 0; i < iMaxBullets; i += iBulletConsumption)
		{
			float shot_percentage = min(1.f, target_total_angle / bloomSize);
			totalDamage += dmg_per_shot*shot_percentage*iPellets;
			if (i == 0)totalDamage += dmg_per_shot*shot_percentage*iPellets;

			timeElapsed += timeBetweenShots;
			bloomSize += fBloomShootIncrease;
			if (bloomSize > fBloomMaxSize)bloomSize = fBloomMaxSize;
			bloomSize -= bloomDecrease*timeBetweenShots;
			if (bloomSize < 0)bloomSize = 0;

		}
	}
	if (iType == 3)
	{
		return 0.1f;
		for (int i = 0; i < iMaxBullets; i += iBulletConsumption)
		{
			totalDamage += iDamageEnd;
			if (i == 0 && standing)totalDamage += iDamageEnd;
			if (!standing)totalDamage -= iDamageEnd*0.75f;
			timeElapsed += timeBetweenShots;
		}
	}

	if (IsConsumable());
	else if (iReloadMethod == 1)
	{
		timeElapsed += fReloadTime;
	}
	else if (iReloadMethod == 2)
	{
		timeElapsed += fReloadTime;
	}

	return totalDamage / timeElapsed;

}

float dc_item::GetRealDPS(float distance, bool waitforfsa)
{
	if (iType > 3)return 0;

	auto dmg = iDamageEnd - (iDamageEnd - iDamageStart)*(fRange - distance) / fRange;

	float perc = min(1, (atan(1 / distance) * 180 / PI)/(0.5*fBloomMinSize+0.5*fBloomMaxSize));

	float activetime = (float)iMaxBullets / fFirerate;

	float timepercent = activetime/(activetime + fReloadTime);
	if (distance > fRange)return 0;


	if (waitforfsa && fBloomMinSize == 0.f)
	{
		float frate = fFirerate;
		float ftime = 1.0 / frate;
		frate = 1 / ftime;
		return dmg*frate*timepercent;
	}

	 return dmg*fFirerate*perc*timepercent;

}


void dc_item::define_all()
{
	dc_item it;
	dc_item heal;

	it.bValidated = true;
	heal.bValidated = true;
	////////////////////////////////////////////////////////////////
	//                        REVOLVER
	////////////////////////////////////////////////////////////////
	it.fWeaponWeight = 0.01f;

	it.fAudibleDistance = 40.f;
	it.iSoundID = 20;
	it.fVolumeMulti = 1.f;

	//Common
	it.ListIndex = 0;
	it.iType = 0;

	it.bAuto = false;
	it.iRarity = 0;
	it.iDamageStart = 44;
	it.iDamageEnd = 18;
	it.fRange = 60;
	it.fFirerate = 3;
	it.iBullets = 6;
	it.iBulletConsumption = 1;
	it.iMaxBullets = 6;
	it.iBulletType = 2;
	it.fBloomMinSize = 0;
	it.fBloomMaxSize = 5.f;
	it.fBloomMovingMinSize = 4.f;
	it.fBloomShootIncrease = 3.f;
	it.fBloomStandingDecrease = 7.5f;
	it.fBloomMovingDecrease = 6.5f;
	it.fReloadTime = 2.4f;
	it.fPulloutTime = 0.5f;
	sprintf(it.szName, "SR - Revolver (Common)");
	it.iTexture = 0;
	it.id = 11;
	
	g_Items.push_back(it);


	//Uncommon
	it.ListIndex = 1;
	it.iType = 0;
	it.bAuto = false;
	it.iRarity = 1;
	it.iDamageStart = 46;
	it.iDamageEnd = 18;
	it.fRange = 60;
	it.fFirerate = 3;
	it.iBullets = 6;
	it.iBulletConsumption = 1;
	it.iMaxBullets = 6;
	it.iBulletType = 2;
	it.fBloomMinSize = 0;
	it.fBloomMaxSize = 4.8f;
	it.fBloomMovingMinSize = 3.9f;
	it.fBloomShootIncrease = 3.0f;
	it.fBloomStandingDecrease = 7.7f;
	it.fBloomMovingDecrease = 6.6f;
	it.fReloadTime = 2.3f;
	it.fPulloutTime = 0.49f;
	sprintf(it.szName, "SR - Revolver (Uncommon)");
	it.iTexture = 0;
	it.id = 11;

	g_Items.push_back(it);

	//Rare
	it.ListIndex = 2;
	it.iType = 0;
	it.bAuto = false;
	it.iRarity = 2;
	it.iDamageStart = 48;
	it.iDamageEnd = 19;
	it.fRange = 60;
	it.fFirerate = 3;
	it.iBullets = 6;
	it.iBulletConsumption = 1;
	it.iMaxBullets = 6;
	it.iBulletType = 2;
	it.fBloomMinSize = 0;
	it.fBloomMaxSize = 4.6f;
	it.fBloomMovingMinSize = 3.75f;
	it.fBloomShootIncrease = 3.0f;
	it.fBloomStandingDecrease = 8.0f;
	it.fBloomMovingDecrease = 6.7f;
	it.fReloadTime = 2.2f;
	it.fPulloutTime = 0.48f;
	sprintf(it.szName, "SR - Revolver (Rare)");
	it.iTexture = 0;
	it.id = 11;

	g_Items.push_back(it);

	//Epic
	it.ListIndex = 3;
	it.iType = 0;
	it.bAuto = false;
	it.iRarity = 3;
	it.iDamageStart = 51;
	it.iDamageEnd = 19;
	it.fRange = 60;
	it.fFirerate = 3;
	it.iBullets = 7;
	it.iBulletConsumption = 1;
	it.iMaxBullets = 7;
	it.iBulletType = 2;
	it.fBloomMinSize = 0;
	it.fBloomMaxSize = 4.5f;
	it.fBloomMovingMinSize = 3.675f;
	it.fBloomShootIncrease = 3.0f;
	it.fBloomStandingDecrease = 8.25f;
	it.fBloomMovingDecrease = 6.75f;
	it.fReloadTime = 2.1f;
	it.fPulloutTime = 0.46f;
	sprintf(it.szName, "SR - Revolver (Epic)");
	it.iTexture = 0;
	it.id = 11;

	g_Items.push_back(it);

	//Legendary
	it.ListIndex = 4;
	it.iType = 0;
	it.bAuto = false;
	it.iRarity = 4;
	it.iDamageStart = 53;
	it.iDamageEnd = 20;
	it.fRange = 60;
	it.fFirerate = 3;
	it.iBullets = 7;
	it.iBulletConsumption = 1;
	it.iMaxBullets = 7;
	it.iBulletType = 2;
	it.fBloomMinSize = 0;
	it.fBloomMaxSize = 4.4f;
	it.fBloomMovingMinSize = 3.55f;
	it.fBloomShootIncrease = 3.0f;
	it.fBloomStandingDecrease = 8.5f;
	it.fBloomMovingDecrease = 6.8f;
	it.fReloadTime = 2.f;
	it.fPulloutTime = 0.45f;
	sprintf(it.szName, "SR - Revolver (Legendary)");
	it.iTexture = 0;
	it.id = 11;

	g_Items.push_back(it);
	add_to_lootpool(0, 70);
	add_to_lootpool(1, 40);
	add_to_lootpool(2, 17);
	add_to_lootpool(3, 6);
	add_to_lootpool(4, 3);
	//

	////////////////////////////////////////////////////////////////
	//                        MP8
	////////////////////////////////////////////////////////////////

	it.fAudibleDistance = 40.f;
	it.iSoundID = 25;
	it.fVolumeMulti = 1.f;


	it.fWeaponWeight = 0.01f;
	//Common
	it.ListIndex = 5;
	it.iType = 0;
	it.bAuto = true;
	it.iRarity = 0;
	it.iDamageStart = 20;
	it.iDamageEnd = 10;
	it.fRange = 45;
	it.fFirerate = 12;
	it.iBullets = 35;
	it.iMaxBullets = 35;
	it.iBulletConsumption = 1;
	it.iBulletType = 1;
	it.fBloomMinSize = 2.5f;
	it.fBloomMaxSize = 9.f;
	it.fBloomMovingMinSize = 3.f;
	it.fBloomShootIncrease = 0.75f;
	it.fBloomStandingDecrease = 7.f;
	it.fBloomMovingDecrease = 6.5f;
	it.fReloadTime = 2.4f;
	it.fPulloutTime = 0.6f;
	sprintf(it.szName, "MP8 (Common)");
	it.iTexture = 1;
	it.id = 101;
	g_Items.push_back(it);

	//Uncommon
	it.ListIndex = 6;
	it.iType = 0;
	it.bAuto = true;
	it.iRarity = 1;
	it.iDamageStart = 21;
	it.iDamageEnd = 10;
	it.fRange = 46;
	it.fFirerate = 12;
	it.iBullets = 35;
	it.iMaxBullets = 35;
	it.iBulletConsumption = 1;
	it.iBulletType = 1;
	it.fBloomMinSize = 2.42f;
	it.fBloomMaxSize = 8.8f;
	it.fBloomMovingMinSize = 2.925f;
	it.fBloomShootIncrease = 0.74f;
	it.fBloomStandingDecrease = 7.05f;
	it.fBloomMovingDecrease = 6.55f;
	it.fReloadTime = 2.3f;
	it.fPulloutTime = 0.58f;
	sprintf(it.szName, "MP8 (Uncommon)");
	it.iTexture = 1;
	it.id = 101;
	g_Items.push_back(it);

	//Rare
	it.ListIndex = 7;
	it.iType = 0;
	it.bAuto = true;
	it.iRarity = 2;
	it.iDamageStart = 22;
	it.iDamageEnd = 11;
	it.fRange = 47;
	it.fFirerate = 12;
	it.iBullets = 35;
	it.iMaxBullets = 35;
	it.iBulletConsumption = 1;
	it.iBulletType = 1;
	it.fBloomMinSize = 2.35f;
	it.fBloomMaxSize = 8.6f;
	it.fBloomMovingMinSize = 2.85f;
	it.fBloomShootIncrease = 0.73f;
	it.fBloomStandingDecrease = 7.15f;
	it.fBloomMovingDecrease = 6.6f;
	it.fReloadTime = 2.2f;
	it.fPulloutTime = 0.56f;
	sprintf(it.szName, "MP8 (Rare)");
	it.iTexture = 1;
	it.id = 101;
	g_Items.push_back(it);

	//Epic
	it.ListIndex = 8;
	it.iType = 0;
	it.bAuto = true;
	it.iRarity = 3;
	it.iDamageStart = 23;
	it.iDamageEnd = 11;
	it.fRange = 48;
	it.fFirerate = 12;
	it.iBullets = 35;
	it.iMaxBullets = 35;
	it.iBulletConsumption = 1;
	it.iBulletType = 1;
	it.fBloomMinSize = 2.3f;
	it.fBloomMaxSize = 8.4f;
	it.fBloomMovingMinSize = 2.75f;
	it.fBloomShootIncrease = 0.72f;
	it.fBloomStandingDecrease = 7.25f;
	it.fBloomMovingDecrease = 6.675f;
	it.fReloadTime = 2.1f;
	it.fPulloutTime = 0.53f;
	sprintf(it.szName, "MP8 (Epic)");
	it.iTexture = 1;
	it.id = 101;
	g_Items.push_back(it);

	//Legendary
	it.ListIndex = 9;
	it.iType = 0;
	it.bAuto = true;
	it.iRarity = 4;
	it.iDamageStart = 24;
	it.iDamageEnd = 12;
	it.fRange = 49;
	it.fFirerate = 12;
	it.iBullets = 35;
	it.iMaxBullets = 35;
	it.iBulletConsumption = 1;
	it.iBulletType = 1;
	it.fBloomMinSize = 2.25f;
	it.fBloomMaxSize = 8.2f;
	it.fBloomMovingMinSize = 2.65f;
	it.fBloomShootIncrease = 0.71f;
	it.fBloomStandingDecrease = 7.35f;
	it.fBloomMovingDecrease = 6.725f;
	it.fReloadTime = 2.f;
	it.fPulloutTime = 0.5f;
	sprintf(it.szName, "MP8 (Legendary)");
	it.iTexture = 1;
	it.id = 101;
	g_Items.push_back(it);


	add_to_lootpool(5, 73);
	add_to_lootpool(6, 44);
	add_to_lootpool(7, 17);
	add_to_lootpool(8, 7);
	add_to_lootpool(9, 3);

	////////////////////////////////////////////////////////////////
	//                       Silenced MP5
	////////////////////////////////////////////////////////////////

	it.fAudibleDistance = 15.f;
	it.iSoundID = 17;
	it.fVolumeMulti = 1.f;

	it.fWeaponWeight = 0.01f;
	//Common
	it.ListIndex = 10;
	it.iType = 0;
	it.bAuto = true;
	it.iRarity = 0;
	it.iDamageStart = 22;
	it.iDamageEnd = 11;
	it.fRange = 50;
	it.fFirerate = 8.5;
	it.iBullets = 30;
	it.iMaxBullets = 30;
	it.iBulletConsumption = 1;
	it.iBulletType = 1;
	it.fBloomMinSize = 0.f;
	it.fBloomMaxSize = 6.f;
	it.fBloomMovingMinSize = 3.5f;
	it.fBloomShootIncrease = 1.f;
	it.fBloomStandingDecrease = 4.5f;
	it.fBloomMovingDecrease = 1.f;
	it.fReloadTime = 2.8f;
	it.fPulloutTime = 0.6f;
	sprintf(it.szName, "Silenced MP5 (Common)");
	it.iTexture = 2;
	it.id = 111;
	g_Items.push_back(it);

	//Uncommon
	it.ListIndex = 11;
	it.iType = 0;
	it.bAuto = true;
	it.iRarity = 1;
	it.iDamageStart = 23;
	it.iDamageEnd = 11;
	it.fRange = 50;
	it.fFirerate = 8.5;
	it.iBullets = 30;
	it.iMaxBullets = 30;
	it.iBulletConsumption = 1;
	it.iBulletType = 1;
	it.fBloomMinSize = 0.f;
	it.fBloomMaxSize = 5.8f;
	it.fBloomMovingMinSize = 3.45f;
	it.fBloomShootIncrease = 0.99f;
	it.fBloomStandingDecrease = 4.55f;
	it.fBloomMovingDecrease = 1.03f;
	it.fReloadTime = 2.6f;
	it.fPulloutTime = 0.58f;
	sprintf(it.szName, "Silenced MP5 (Uncommon)");
	it.iTexture = 2;
	it.id = 111;
	g_Items.push_back(it);

	//Rare
	it.ListIndex = 12;
	it.iType = 0;
	it.bAuto = true;
	it.iRarity = 2;
	it.iDamageStart = 24;
	it.iDamageEnd = 12;
	it.fRange = 50;
	it.fFirerate = 8.5;
	it.iBullets = 30;
	it.iMaxBullets = 30;
	it.iBulletConsumption = 1;
	it.iBulletType = 1;
	it.fBloomMinSize = 0.f;
	it.fBloomMaxSize = 5.6f;
	it.fBloomMovingMinSize = 3.4f;
	it.fBloomShootIncrease = 0.98f;
	it.fBloomStandingDecrease = 4.6f;
	it.fBloomMovingDecrease = 1.05f;
	it.fReloadTime = 2.5f;
	it.fPulloutTime = 0.56f;
	sprintf(it.szName, "Silenced MP5 (Rare)");
	it.iTexture = 2;
	it.id = 111;
	g_Items.push_back(it);


	add_to_lootpool(10, 96);
	add_to_lootpool(11, 55);
	add_to_lootpool(12, 8);


	////////////////////////////////////////////////////////////////
	//                       HEALING ITEMS
	////////////////////////////////////////////////////////////////

	heal.fAudibleDistance = 25.f;
	heal.iSoundID = 31;
	heal.fVolumeMulti = 0.6f;

	it.fWeaponWeight = 0.0f;
	//Bandages
	it.ListIndex = 13;
	it.fBloomMinSize = 0.f;
	it.fBloomMaxSize = 0.f;
	heal.iType = 4;
	heal.iRarity = 0;
	heal.iBullets = 5;
	heal.iMaxBullets = 15;
	heal.iHealAmount = 15;
	heal.iHealMax = 75;
	heal.fHealTime = 1.5f;
	heal.iTexture = 3;
	sprintf(heal.szName, "Bandages");
	heal.id = 1000;
	g_Items.push_back(heal);

	//Med-Kit
	it.ListIndex = 14;
	heal.iType = 4;
	heal.iRarity = 1;
	heal.iBullets = 1;
	heal.iMaxBullets = 3;
	heal.iHealAmount = 100;
	heal.iHealMax = 100;
	heal.fHealTime = 4.5f;
	heal.iTexture = 4;
	sprintf(heal.szName, "Med-Kit");
	heal.id = 1001;
	g_Items.push_back(heal);


	heal.fAudibleDistance = 25.f;
	heal.iSoundID = 32;
	heal.fVolumeMulti = 0.3f;

	//Small shield
	it.ListIndex = 15;
	heal.iType = 5;
	heal.iRarity = 1;
	heal.iBullets = 3;
	heal.iMaxBullets = 6;
	heal.iHealAmount = 25;
	heal.iHealMax = 50;
	heal.fHealTime = 1.0f;
	heal.iTexture = 5;
	sprintf(heal.szName, "Small Shield Potion");
	heal.id = 1004;
	g_Items.push_back(heal);

	//Big shield
	it.ListIndex = 16;
	heal.iType = 5;
	heal.iRarity = 2;
	heal.iBullets = 1;
	heal.iMaxBullets = 3;
	heal.iHealAmount = 50;
	heal.iHealMax = 100;
	heal.fHealTime = 3.0f;
	heal.iTexture = 6;
	sprintf(heal.szName, "Shield Potion");
	heal.id = 1003;
	g_Items.push_back(heal);

	//Slurp Juice
	it.ListIndex = 17;
	heal.iType = 6;
	heal.iRarity = 3;
	heal.iBullets = 1;
	heal.iMaxBullets = 2;
	heal.iHealAmount = 75;
	heal.iHealMax = 100;
	heal.fHealTime = 2.0f;
	heal.fHealRateProgressive = 4.f;
	heal.iTexture = 7;
	sprintf(heal.szName, "Slurp Juice");
	heal.id = 1002;
	g_Items.push_back(heal);

	//Chug Jug
	it.ListIndex = 18;
	heal.iType = 6;
	heal.iRarity = 4;
	heal.iBullets = 1;
	heal.iMaxBullets = 1;
	heal.iHealAmount = 200;
	heal.iHealMax = 100;
	heal.fHealTime = 6.0f;
	heal.fHealRateProgressive = 200.f;
	heal.iTexture = 8;
	sprintf(heal.szName, "Chug Jug");
	heal.id = 1005;
	g_Items.push_back(heal);

	add_to_lootpool(13, 60);
	add_to_lootpool(14, 33);
	add_to_lootpool(15, 50);
	add_to_lootpool(16, 24);
	add_to_lootpool(17, 15);
	add_to_lootpool(18, 8);


	////////////////////////////////////////////////////////////////
	//                   GLOCK-11 & Silenced USP
	////////////////////////////////////////////////////////////////

	it.fAudibleDistance = 40.f;
	it.iSoundID = 14;
	it.fVolumeMulti = 1.f;

	it.fWeaponWeight = 0.01f;
	//Common
	it.ListIndex = 19;
	it.iType = 0;
	it.bAuto = false;
	it.iRarity = 0;
	it.iDamageStart = 25;
	it.iDamageEnd = 15;
	it.fRange = 80;
	it.fFirerate = 7;
	it.iBullets = 16;
	it.iBulletConsumption = 1;
	it.iMaxBullets = 16;
	it.iBulletType = 1;
	it.fBloomMinSize = 2.f;
	it.fBloomMaxSize = 5.f;
	it.fBloomMovingMinSize = 4.f;
	it.fBloomShootIncrease = 2.5f;
	it.fBloomStandingDecrease = 6.f;
	it.fBloomMovingDecrease = 3.f;
	it.fReloadTime = 1.9f;
	it.fPulloutTime = 0.45f;
	sprintf(it.szName, "Glock-11 (Common)");
	it.iTexture = 9;
	it.id = 21;

	g_Items.push_back(it);

	//Uncommon
	it.ListIndex = 20;
	it.iType = 0;
	it.bAuto = false;
	it.iRarity = 1;
	it.iDamageStart = 26;
	it.iDamageEnd = 15;
	it.fRange = 80;
	it.fFirerate = 7;
	it.iBullets = 16;
	it.iBulletConsumption = 1;
	it.iMaxBullets = 16;
	it.iBulletType = 1;
	it.fBloomMinSize = 1.75f;
	it.fBloomMaxSize = 4.9f;
	it.fBloomMovingMinSize = 3.75f;
	it.fBloomShootIncrease = 2.4f;
	it.fBloomStandingDecrease = 6.5f;
	it.fBloomMovingDecrease = 3.25f;
	it.fReloadTime = 1.85f;
	it.fPulloutTime = 0.44f;
	sprintf(it.szName, "Glock-11 (Uncommon)");
	it.iTexture = 9;
	it.id = 21;

	g_Items.push_back(it);

	//Rare
	it.ListIndex = 21;
	it.iType = 0;
	it.bAuto = false;
	it.iRarity = 2;
	it.iDamageStart = 27;
	it.iDamageEnd = 16;
	it.fRange = 80;
	it.fFirerate = 7;
	it.iBullets = 16;
	it.iBulletConsumption = 1;
	it.iMaxBullets = 16;
	it.iBulletType = 1;
	it.fBloomMinSize = 1.5f;
	it.fBloomMaxSize = 4.8f;
	it.fBloomMovingMinSize = 3.5f;
	it.fBloomShootIncrease = 2.3f;
	it.fBloomStandingDecrease = 6.75f;
	it.fBloomMovingDecrease = 3.4f;
	it.fReloadTime = 1.8f;
	it.fPulloutTime = 0.43f;
	sprintf(it.szName, "Glock-11 (Rare)");
	it.iTexture = 9;
	it.id = 21;
	g_Items.push_back(it);


	it.fAudibleDistance = 20.f;
	it.iSoundID = 18;
	it.fVolumeMulti = 1.f;

	//Epic
	it.ListIndex = 22;
	it.iType = 0;
	it.bAuto = false;
	it.iRarity = 3;
	it.iDamageStart = 29;
	it.iDamageEnd = 17;
	it.fRange = 80;
	it.fFirerate = 7;
	it.iBullets = 16;
	it.iBulletConsumption = 1;
	it.iMaxBullets = 16;
	it.iBulletType = 1;
	it.fBloomMinSize = 0.f;
	it.fBloomMaxSize = 4.7f;
	it.fBloomMovingMinSize = 3.25f;
	it.fBloomShootIncrease = 2.25f;
	it.fBloomStandingDecrease = 7.f;
	it.fBloomMovingDecrease = 3.5f;
	it.fReloadTime = 1.7f;
	it.fPulloutTime = 0.41f;
	sprintf(it.szName, "Silenced USP (Epic)");
	it.iTexture = 10;
	it.id = 22;
	g_Items.push_back(it);

	//Epic
	it.ListIndex = 23;
	it.iType = 0;
	it.bAuto = false;
	it.iRarity = 4;
	it.iDamageStart = 31;
	it.iDamageEnd = 18;
	it.fRange = 80;
	it.fFirerate = 7;
	it.iBullets = 16;
	it.iBulletConsumption = 1;
	it.iMaxBullets = 16;
	it.iBulletType = 1;
	it.fBloomMinSize = 0.f;
	it.fBloomMaxSize = 4.5f;
	it.fBloomMovingMinSize = 3.1f;
	it.fBloomShootIncrease = 2.1f;
	it.fBloomStandingDecrease = 7.25f;
	it.fBloomMovingDecrease = 3.6f;
	it.fReloadTime = 1.6f;
	it.fPulloutTime = 0.4f;
	sprintf(it.szName, "Silenced USP (Legendary)");
	it.iTexture = 10;
	it.id = 22;
	g_Items.push_back(it);

	add_to_lootpool(19, 140);
	add_to_lootpool(20, 80);
	add_to_lootpool(21, 55);
	add_to_lootpool(22, 18);
	add_to_lootpool(23, 7);

	////////////////////////////////////////////////////////////////
	//                         ARA1 & SFR-12
	////////////////////////////////////////////////////////////////


	it.fAudibleDistance = 50.f;
	it.iSoundID = 24;
	it.fVolumeMulti = 1.f;

	it.fWeaponWeight = 0.025f;
	//Common
	it.ListIndex = 24;
	it.iType = 0;
	it.bAuto = true;
	it.iRarity = 0;
	it.iDamageStart = 30;
	it.iDamageEnd = 20;
	it.fRange = 100;
	it.fFirerate = 5.5;
	it.iBullets = 30;
	it.iBulletConsumption = 1;
	it.iMaxBullets = 30;
	it.iBulletType = 2;
	it.fBloomMinSize = 0.f;
	it.fBloomMaxSize = 7.5f;
	it.fBloomMovingMinSize = 6.65f;
	it.fBloomShootIncrease = 1.25f;
	it.fBloomStandingDecrease = 6.05f;
	it.fBloomMovingDecrease = 2.f;
	it.fReloadTime = 2.4f;
	it.fPulloutTime = 0.65f;
	sprintf(it.szName, "AR-A1 (Common)");
	it.iTexture = 11;
	it.id = 201;

	g_Items.push_back(it);

	//Uncommon
	it.ListIndex = 25;
	it.iType = 0;
	it.bAuto = true;
	it.iRarity = 1;
	it.iDamageStart = 31;
	it.iDamageEnd = 21;
	it.fRange = 100;
	it.fFirerate = 5.5;
	it.iBullets = 30;
	it.iBulletConsumption = 1;
	it.iMaxBullets = 30;
	it.iBulletType = 2;
	it.fBloomMinSize = 0.f;
	it.fBloomMaxSize = 7.3f;
	it.fBloomMovingMinSize = 6.5f;
	it.fBloomShootIncrease = 1.24f;
	it.fBloomStandingDecrease = 6.1f;
	it.fBloomMovingDecrease = 2.05f;
	it.fReloadTime = 2.3f;
	it.fPulloutTime = 0.63f;
	sprintf(it.szName, "AR-A1 (Uncommon)");
	it.iTexture = 11;
	it.id = 201;

	g_Items.push_back(it);

	//Rare
	it.ListIndex = 26;
	it.iType = 0;
	it.bAuto = true;
	it.iRarity = 2;
	it.iDamageStart = 33;
	it.iDamageEnd = 22;
	it.fRange = 100;
	it.fFirerate = 5.5;
	it.iBullets = 30;
	it.iBulletConsumption = 1;
	it.iMaxBullets = 30;
	it.iBulletType = 2;
	it.fBloomMinSize = 0.f;
	it.fBloomMaxSize = 7.2f;
	it.fBloomMovingMinSize = 6.4f;
	it.fBloomShootIncrease = 1.235f;
	it.fBloomStandingDecrease = 6.15f;
	it.fBloomMovingDecrease = 2.1f;
	it.fReloadTime = 2.2f;
	it.fPulloutTime = 0.61f;
	sprintf(it.szName, "AR-A1 (Rare)");
	it.iTexture = 11;
	it.id = 201;

	g_Items.push_back(it);

	//Epic
	it.ListIndex =27;
	it.iType = 0;
	it.bAuto = true;
	it.iRarity = 3;
	it.iDamageStart = 34;
	it.iDamageEnd = 23;
	it.fRange = 100;
	it.fFirerate = 5.5;
	it.iBullets = 30;
	it.iBulletConsumption = 1;
	it.iMaxBullets = 30;
	it.iBulletType = 2;
	it.fBloomMinSize = 0.f;
	it.fBloomMaxSize = 7.1f;
	it.fBloomMovingMinSize = 6.3f;
	it.fBloomShootIncrease = 1.23f;
	it.fBloomStandingDecrease = 6.2f;
	it.fBloomMovingDecrease = 2.15f;
	it.fReloadTime = 2.1f;
	it.fPulloutTime = 0.59f;
	sprintf(it.szName, "SFR-12 (Epic)");
	it.iTexture = 12;
	it.id = 201;

	g_Items.push_back(it);

	//Legendary
	it.ListIndex = 28;
	it.iType = 0;
	it.bAuto = true;
	it.iRarity = 4;
	it.iDamageStart = 36;
	it.iDamageEnd = 24;
	it.fRange = 100;
	it.fFirerate = 5.5;
	it.iBullets = 30;
	it.iBulletConsumption = 1;
	it.iMaxBullets = 30;
	it.iBulletType = 2;
	it.fBloomMinSize = 0.f;
	it.fBloomMaxSize = 7.f;
	it.fBloomMovingMinSize = 6.2f;
	it.fBloomShootIncrease = 1.225f;
	it.fBloomStandingDecrease = 6.25f;
	it.fBloomMovingDecrease = 2.2f;
	it.fReloadTime = 2.0f;
	it.fPulloutTime = 0.55f;
	sprintf(it.szName, "SFR-12 (Legendary)");
	it.iTexture = 12;
	it.id = 201;

	g_Items.push_back(it);
	add_to_lootpool(24, 80);
	add_to_lootpool(25, 55);
	add_to_lootpool(26, 19);
	add_to_lootpool(27, 7);
	add_to_lootpool(28, 3);

	////////////////////////////////////////////////////////////////
	//                         MINIGUN
	////////////////////////////////////////////////////////////////

	it.fAudibleDistance = 40.f;
	it.iSoundID = 26;
	it.fVolumeMulti = 1.f;



	it.fWeaponWeight = 0.1f;
	//Epic
	it.ListIndex = 29;
	it.iType = 0;
	it.bAuto = true;
	it.iRarity = 3;
	it.iDamageStart = 19;
	it.iDamageEnd = 4;
	it.fRange = 40;
	it.fFirerate = 15;
	it.iBullets = 50;
	it.iBulletConsumption = 1;
	it.iMaxBullets = 50;
	it.iBulletType = 1;
	it.fBloomMinSize = 3.f;
	it.fBloomMaxSize = 12.f;
	it.fBloomMovingMinSize = 8.f;
	it.fBloomShootIncrease = 0.9f;
	it.fBloomStandingDecrease = 7.f;
	it.fBloomMovingDecrease = 0.5f;
	it.fReloadTime = 1.f;
	it.fPulloutTime = 0.8f;
	sprintf(it.szName, "Minigun (Epic)");
	it.iTexture = 13;
	it.id = 151;

	g_Items.push_back(it);

	//Legendary
	it.ListIndex = 30;
	it.iType = 0;
	it.bAuto = true;
	it.iRarity = 4;
	it.iDamageStart = 20;
	it.iDamageEnd = 5;
	it.fRange = 42.5;
	it.fFirerate = 15;
	it.iBullets = 50;
	it.iBulletConsumption = 1;
	it.iMaxBullets = 50;
	it.iBulletType = 1;
	it.fBloomMinSize = 3.f;
	it.fBloomMaxSize = 11.5f;
	it.fBloomMovingMinSize = 7.75f;
	it.fBloomShootIncrease = 0.87f;
	it.fBloomStandingDecrease = 7.5f;
	it.fBloomMovingDecrease = 0.55f;
	it.fReloadTime = 0.97f;
	it.fPulloutTime = 0.77f;
	sprintf(it.szName, "Minigun (Legendary)");
	it.iTexture = 13;
	it.id = 151;

	g_Items.push_back(it);

	add_to_lootpool(29, 12);
	add_to_lootpool(30, 6);

	////////////////////////////////////////////////////////////////
	//                        SCOPED AR7
	////////////////////////////////////////////////////////////////
	it.fWeaponWeight = 0.05f;

	it.fAudibleDistance = 45.f;
	it.iSoundID = 27;
	it.fVolumeMulti = 1.f;

	//Uncommon
	it.ListIndex = 31;
	it.iType = 0;
	it.bAuto = true;
	it.iRarity = 1;
	it.iDamageStart = 28;
	it.iDamageEnd = 25;
	it.fRange = 100;
	it.fFirerate = 4.25;
	it.iBullets = 20;
	it.iMaxBullets = 20;
	it.iBulletConsumption = 1;
	it.iBulletType = 2;
	it.fBloomMinSize = 0.f;
	it.fBloomMaxSize = 8.f;
	it.fBloomMovingMinSize = 6.f;
	it.fBloomShootIncrease = 1.2f;
	it.fBloomStandingDecrease = 4.7f;
	it.fBloomMovingDecrease = 1.f;
	it.fReloadTime = 2.0f;
	it.fPulloutTime = 0.6f;
	sprintf(it.szName, "Scoped AR7 (Uncommon)");
	it.iTexture = 14;
	it.id = 211;
	g_Items.push_back(it);

	//Rare
	it.ListIndex = 32;
	it.iType = 0;
	it.bAuto = true;
	it.iRarity = 2;
	it.iDamageStart = 30;
	it.iDamageEnd = 27;
	it.fRange = 100;
	it.fFirerate = 4.25;
	it.iBullets = 20;
	it.iMaxBullets = 20;
	it.iBulletConsumption = 1;
	it.iBulletType = 2;
	it.fBloomMinSize = 0.f;
	it.fBloomMaxSize = 7.75f;
	it.fBloomMovingMinSize = 5.8f;
	it.fBloomShootIncrease = 1.19f;
	it.fBloomStandingDecrease = 4.725f;
	it.fBloomMovingDecrease = 1.f;
	it.fReloadTime = 1.8f;
	it.fPulloutTime = 0.55f;
	sprintf(it.szName, "Scoped AR7 (Rare)");
	it.iTexture = 14;
	it.id = 211;
	g_Items.push_back(it);

	//Epic
	it.ListIndex = 33;
	it.iType = 0;
	it.bAuto = true;
	it.iRarity = 3;
	it.iDamageStart = 32;
	it.iDamageEnd = 28;
	it.fRange = 100;
	it.fFirerate = 4.25;
	it.iBullets = 20;
	it.iMaxBullets = 20;
	it.iBulletConsumption = 1;
	it.iBulletType = 2;
	it.fBloomMinSize = 0.f;
	it.fBloomMaxSize = 7.5f;
	it.fBloomMovingMinSize = 5.6f;
	it.fBloomShootIncrease = 1.18f;
	it.fBloomStandingDecrease = 4.75f;
	it.fBloomMovingDecrease = 1.f;
	it.fReloadTime = 1.6f;
	it.fPulloutTime = 0.5f;
	sprintf(it.szName, "Scoped AR7 (Epic)");
	it.iTexture = 14;
	it.id = 211;
	g_Items.push_back(it);

	add_to_lootpool(31, 30);
	add_to_lootpool(32,14);
	add_to_lootpool(33, 8);

	////////////////////////////////////////////////////////////////
	//                        SPAS ShOTGUN
	////////////////////////////////////////////////////////////////

	it.fAudibleDistance = 55.f;
	it.iSoundID = 28;
	it.fVolumeMulti = 1.f;

	it.fWeaponWeight = 0.02f;
	//Common
	it.ListIndex = 34;
	it.iType = 1;
	it.bAuto = false;
	it.iRarity = 0;
	it.iDamageStart = 16;
	it.iDamageEnd = 2;
	it.fRange = 20;
	it.fFirerate = 1.1;
	it.iBullets = 5;
	it.iMaxBullets = 5;
	it.iPellets = 8;
	it.iBulletConsumption = 1;
	it.iBulletType = 2;
	it.iReloadMethod = 2;
	it.fBloomMinSize = 10.f;
	it.fBloomMaxSize = 15.f;
	it.fBloomMovingMinSize = 12.f;
	it.fBloomShootIncrease = 5.f;
	it.fBloomStandingDecrease = 6.0f;
	it.fBloomMovingDecrease = 5.f;

	it.fReloadTime = 0.65f;
	it.fPulloutTime = 0.6f;
	sprintf(it.szName, "SPAS Shotgun (Common)");
	it.iTexture = 15;
	it.id = 300;
	g_Items.push_back(it);

	//Uncommon
	it.ListIndex = 35;
	it.iType = 1;
	it.bAuto = false;
	it.iRarity = 1;
	it.iDamageStart = 18;
	it.iDamageEnd = 2;
	it.fRange = 21;
	it.fFirerate = 1.1;
	it.iBullets = 5;
	it.iMaxBullets = 5;
	it.iPellets = 8;
	it.iBulletConsumption = 1;
	it.iBulletType = 2;
	it.iReloadMethod = 2;
	it.fBloomMinSize = 9.75f;
	it.fBloomMaxSize = 14.9f;
	it.fBloomMovingMinSize = 11.75f;
	it.fBloomShootIncrease = 5.f;
	it.fBloomStandingDecrease = 6.0f;
	it.fBloomMovingDecrease = 5.f;
	it.fReloadTime = 0.63f;
	it.fPulloutTime = 0.58f;
	sprintf(it.szName, "SPAS Shotgun (Uncommon)");
	it.iTexture = 15;
	it.id = 300;
	g_Items.push_back(it);

	//Rare
	it.ListIndex = 36;
	it.iType = 1;
	it.bAuto = false;
	it.iRarity = 2;
	it.iDamageStart = 20;
	it.iDamageEnd = 3;
	it.fRange = 22;
	it.fFirerate = 1.1;
	it.iBullets = 5;
	it.iMaxBullets = 5;
	it.iPellets = 8;
	it.iBulletConsumption = 1;
	it.iBulletType = 2;
	it.iReloadMethod = 2;
	it.fBloomMinSize = 9.5f;
	it.fBloomMaxSize = 14.8f;
	it.fBloomMovingMinSize = 11.5f;
	it.fBloomShootIncrease = 5.f;
	it.fBloomStandingDecrease = 6.0f;
	it.fBloomMovingDecrease = 5.f;
	it.fReloadTime = 0.61f;
	it.fPulloutTime = 0.56f;
	sprintf(it.szName, "SPAS Shotgun (Rare)");
	it.iTexture = 15;
	it.id = 300;
	g_Items.push_back(it);

	//Epic
	it.ListIndex = 37;
	it.iType = 1;
	it.bAuto = false;
	it.iRarity = 3;
	it.iDamageStart = 22;
	it.iDamageEnd = 4;
	it.fRange = 23;
	it.fFirerate = 1.1;
	it.iBullets = 5;
	it.iMaxBullets = 5;
	it.iPellets = 8;
	it.iBulletConsumption = 1;
	it.iBulletType = 2;
	it.iReloadMethod = 2;
	it.fBloomMinSize = 9.25f;
	it.fBloomMaxSize = 14.7f;
	it.fBloomMovingMinSize = 11.25f;
	it.fBloomShootIncrease = 5.f;
	it.fBloomStandingDecrease = 6.0f;
	it.fBloomMovingDecrease = 5.f;
	it.fReloadTime = 0.59f;
	it.fPulloutTime = 0.53f;
	sprintf(it.szName, "SPAS Shotgun (Epic)");
	it.iTexture = 15;
	it.id = 300;
	g_Items.push_back(it);

	//Legendary
	it.ListIndex = 38;
	it.iType = 1;
	it.bAuto = false;
	it.iRarity = 4;
	it.iDamageStart = 24;
	it.iDamageEnd = 4;
	it.fRange = 24;
	it.fFirerate = 1.1;
	it.iBullets = 5;
	it.iMaxBullets = 5;
	it.iPellets = 8;
	it.iBulletConsumption = 1;
	it.iBulletType = 2;
	it.iReloadMethod = 2;
	it.fBloomMinSize = 9.f;
	it.fBloomMaxSize = 14.5f;
	it.fBloomMovingMinSize = 11.f;
	it.fBloomShootIncrease = 5.f;
	it.fBloomStandingDecrease = 6.0f;
	it.fBloomMovingDecrease = 5.f;
	it.fReloadTime = 0.56f;
	it.fPulloutTime = 0.5f;
	sprintf(it.szName, "SPAS Shotgun (Legendary)");
	it.iTexture = 15;
	it.id = 300;
	g_Items.push_back(it);

	add_to_lootpool(34, 80);
	add_to_lootpool(35, 66);
	add_to_lootpool(36, 20);
	add_to_lootpool(37, 13);
	add_to_lootpool(38, 5);

	////////////////////////////////////////////////////////////////
	//                        Leone ShOTGUN
	////////////////////////////////////////////////////////////////

	it.fAudibleDistance = 50.f;
	it.iSoundID = 16;
	it.fVolumeMulti = 1.f;

	it.fWeaponWeight = 0.02f;
	//Common
	it.ListIndex = 39;
	it.iType = 1;
	it.bAuto = true;
	it.iRarity = 0;
	it.iDamageStart = 10;
	it.iDamageEnd = 2;
	it.fRange = 14;
	it.fFirerate = 2.25;
	it.iBullets = 8;
	it.iMaxBullets = 8;
	it.iPellets = 8;
	it.iBulletConsumption = 1;
	it.iBulletType = 2;
	it.iReloadMethod = 2;
	it.fBloomMinSize = 10.f;
	it.fBloomMaxSize = 22.5f;
	it.fBloomMovingMinSize = 17.5f;
	it.fBloomShootIncrease = 5.f;
	it.fBloomStandingDecrease = 9.0f;
	it.fBloomMovingDecrease = 7.f;
	it.fReloadTime = 0.55f;
	it.fPulloutTime = 0.55f;
	sprintf(it.szName, "Leone Shotgun (Common)");
	it.iTexture = 16;
	it.id = 310;
	g_Items.push_back(it);

	//Uncommon
	it.ListIndex = 40;
	it.iType = 1;
	it.bAuto = true;
	it.iRarity = 1;
	it.iDamageStart = 11;
	it.iDamageEnd = 2;
	it.fRange = 14.5;
	it.fFirerate = 2.25;
	it.iBullets = 8;
	it.iMaxBullets = 8;
	it.iPellets = 8;
	it.iBulletConsumption = 1;
	it.iBulletType = 2;
	it.iReloadMethod = 2;
	it.fBloomMinSize = 9.75f;
	it.fBloomMaxSize = 22.25f;
	it.fBloomMovingMinSize = 17.3f;
	it.fBloomShootIncrease = 5.f;
	it.fBloomStandingDecrease = 9.0f;
	it.fBloomMovingDecrease = 7.f;
	it.fReloadTime = 0.54f;
	it.fPulloutTime = 0.53f;
	sprintf(it.szName, "Leone Shotgun (Uncommon)");
	it.iTexture = 16;
	it.id = 310;
	g_Items.push_back(it);

	//Rare
	it.ListIndex = 41;
	it.iType = 1;
	it.bAuto = true;
	it.iRarity = 2;
	it.iDamageStart = 12;
	it.iDamageEnd = 2;
	it.fRange = 15;
	it.fFirerate = 2.25;
	it.iBullets = 8;
	it.iMaxBullets = 8;
	it.iPellets = 8;
	it.iBulletConsumption = 1;
	it.iBulletType = 2;
	it.iReloadMethod = 2;
	it.fBloomMinSize = 9.5f;
	it.fBloomMaxSize = 22.f;
	it.fBloomMovingMinSize = 17.1f;
	it.fBloomShootIncrease = 5.f;
	it.fBloomStandingDecrease = 9.0f;
	it.fBloomMovingDecrease = 7.f;
	it.fReloadTime = 0.53f;
	it.fPulloutTime = 0.51f;
	sprintf(it.szName, "Leone Shotgun (Rare)");
	it.iTexture = 16;
	it.id = 310;
	g_Items.push_back(it);

	//Epic
	it.ListIndex = 42;
	it.iType = 1;
	it.bAuto = true;
	it.iRarity = 3;
	it.iDamageStart = 13;
	it.iDamageEnd = 3;
	it.fRange = 15.5;
	it.fFirerate = 2.25;
	it.iBullets = 8;
	it.iMaxBullets = 8;
	it.iPellets = 8;
	it.iBulletConsumption = 1;
	it.iBulletType = 2;
	it.iReloadMethod = 2;
	it.fBloomMinSize = 9.25f;
	it.fBloomMaxSize = 21.75f;
	it.fBloomMovingMinSize = 16.9f;
	it.fBloomShootIncrease = 5.f;
	it.fBloomStandingDecrease = 9.0f;
	it.fBloomMovingDecrease = 7.f;
	it.fReloadTime = 0.52f;
	it.fPulloutTime = 0.49f;
	sprintf(it.szName, "Leone Shotgun (Epic)");
	it.iTexture = 16;
	it.id = 310;
	g_Items.push_back(it);

	//Legendary
	it.iType = 1;
	it.bAuto = true;
	it.iRarity = 4;
	it.iDamageStart = 14;
	it.iDamageEnd = 3;
	it.fRange = 16;
	it.fFirerate = 2.25;
	it.iBullets = 8;
	it.iMaxBullets = 8;
	it.iPellets = 8;
	it.iBulletConsumption = 1;
	it.iBulletType = 2;
	it.iReloadMethod = 2;
	it.fBloomMinSize = 9.f;
	it.fBloomMaxSize = 21.5f;
	it.fBloomMovingMinSize = 16.7f;
	it.fBloomShootIncrease = 5.f;
	it.fBloomStandingDecrease = 9.0f;
	it.fBloomMovingDecrease = 7.f;
	it.fReloadTime = 0.5f;
	it.fPulloutTime = 0.47f;
	sprintf(it.szName, "Leone Shotgun (Legendary)");
	it.iTexture = 16;
	it.id = 310;
	g_Items.push_back(it);

	add_to_lootpool(39, 99);
	add_to_lootpool(40, 66);
	add_to_lootpool(41, 22);
	add_to_lootpool(42, 14);
	add_to_lootpool(43, 5);


	////////////////////////////////////////////////////////////////
	//                        Thomson ShOTGUN
	////////////////////////////////////////////////////////////////

	it.fAudibleDistance = 45.f;
	it.iSoundID = 30;
	it.fVolumeMulti = 0.7f;

	it.fWeaponWeight = 0.02f;
	//Common
	it.iType = 1;
	it.bAuto = true;
	it.iRarity = 0;
	it.iDamageStart = 9;
	it.iDamageEnd = 1;
	it.fRange = 8;
	it.fFirerate = 3.9;
	it.iBullets = 12;
	it.iMaxBullets = 12;
	it.iPellets = 8;
	it.iBulletConsumption = 1;
	it.iBulletType = 2;
	it.iReloadMethod = 1;
	it.fBloomMinSize = 14.f;
	it.fBloomMaxSize = 25.f;
	it.fBloomMovingMinSize = 20.f;
	it.fBloomShootIncrease = 5.f;
	it.fBloomStandingDecrease = 12.0f;
	it.fBloomMovingDecrease = 10.f;
	it.fReloadTime = 2.5f;
	it.fPulloutTime = 0.65f;
	sprintf(it.szName, "Thomson Shotgun (Common)");
	it.iTexture = 17;
	it.id = 320;
	g_Items.push_back(it);

	//Uncommon
	it.iType = 1;
	it.bAuto = true;
	it.iRarity = 1;
	it.iDamageStart = 10;
	it.iDamageEnd = 1;
	it.fRange = 9;
	it.fFirerate = 3.9;
	it.iBullets = 12;
	it.iMaxBullets = 12;
	it.iPellets = 8;
	it.iBulletConsumption = 1;
	it.iBulletType = 2;
	it.iReloadMethod = 1;
	it.fBloomMinSize = 13.75f;
	it.fBloomMaxSize = 24.75f;
	it.fBloomMovingMinSize = 19.75f;
	it.fBloomShootIncrease = 5.f;
	it.fBloomStandingDecrease = 12.0f;
	it.fBloomMovingDecrease = 10.f;
	it.fReloadTime = 2.425f;
	it.fPulloutTime = 0.63f;
	sprintf(it.szName, "Thomson Shotgun (Uncommon)");
	it.iTexture = 17;
	it.id = 320;
	g_Items.push_back(it);

	//Rare
	it.iType = 1;
	it.bAuto = true;
	it.iRarity = 2;
	it.iDamageStart = 11;
	it.iDamageEnd = 1;
	it.fRange = 9;
	it.fFirerate = 3.9;
	it.iBullets = 12;
	it.iMaxBullets = 12;
	it.iPellets = 8;
	it.iBulletConsumption = 1;
	it.iBulletType = 2;
	it.iReloadMethod = 1;
	it.fBloomMinSize = 13.5f;
	it.fBloomMaxSize = 24.5f;
	it.fBloomMovingMinSize = 19.5f;
	it.fBloomShootIncrease = 5.f;
	it.fBloomStandingDecrease = 12.0f;
	it.fBloomMovingDecrease = 10.f;
	it.fReloadTime = 2.35f;
	it.fPulloutTime = 0.61f;
	sprintf(it.szName, "Thomson Shotgun (Rare)");
	it.iTexture = 17;
	it.id = 320;
	g_Items.push_back(it);

	//Epic
	it.iType = 1;
	it.bAuto = true;
	it.iRarity = 3;
	it.iDamageStart = 12;
	it.iDamageEnd = 2;
	it.fRange = 10;
	it.fFirerate = 3.9;
	it.iBullets = 12;
	it.iMaxBullets = 12;
	it.iPellets = 8;
	it.iBulletConsumption = 1;
	it.iBulletType = 2;
	it.iReloadMethod = 1;
	it.fBloomMinSize = 13.25f;
	it.fBloomMaxSize = 24.25f;
	it.fBloomMovingMinSize = 19.25f;
	it.fBloomShootIncrease = 5.f;
	it.fBloomStandingDecrease = 12.0f;
	it.fBloomMovingDecrease = 10.f;
	it.fReloadTime = 2.276f;
	it.fPulloutTime = 0.58f;
	sprintf(it.szName, "Thomson Shotgun (Epic)");
	it.iTexture = 17;
	it.id = 320;
	g_Items.push_back(it);

	//Legendary
	it.iType = 1;
	it.bAuto = true;
	it.iRarity = 4;
	it.iDamageStart = 13;
	it.iDamageEnd = 2;
	it.fRange = 11;
	it.fFirerate = 3.9;
	it.iBullets = 12;
	it.iMaxBullets = 12;
	it.iPellets = 8;
	it.iBulletConsumption = 1;
	it.iBulletType = 2;
	it.iReloadMethod = 1;
	it.fBloomMinSize = 13.f;
	it.fBloomMaxSize = 24.f;
	it.fBloomMovingMinSize = 19.2f;
	it.fBloomShootIncrease = 5.f;
	it.fBloomStandingDecrease = 12.0f;
	it.fBloomMovingDecrease = 10.f;
	it.fReloadTime = 2.2f;
	it.fPulloutTime = 0.55f;
	sprintf(it.szName, "Thomson Shotgun (Legendary)");
	it.iTexture = 17;
	it.id = 320;
	g_Items.push_back(it);

	add_to_lootpool(44, 73);
	add_to_lootpool(45, 45);
	add_to_lootpool(46, 18);
	add_to_lootpool(47, 10);
	add_to_lootpool(48, 3);


	////////////////////////////////////////////////////////////////
	//                        Kor91k
	////////////////////////////////////////////////////////////////

	it.fAudibleDistance = 55.f;
	it.iSoundID = 19;
	it.fVolumeMulti = 1.f;

	it.fWeaponWeight = 0.075f;
	//Common
	it.iType = 0;
	it.bAuto = false;
	it.iRarity = 0;
	it.iDamageStart = 72;
	it.iDamageEnd = 54;
	it.fRange = 100;
	it.fFirerate = 1.5;
	it.iBullets = 5;
	it.iMaxBullets = 5;
	it.iPellets = 1;
	it.iBulletConsumption = 1;
	it.iBulletType = 2;
	it.iReloadMethod = 1;
	it.fBloomMinSize = 0.f;
	it.fBloomMaxSize = 10.f;
	it.fBloomMovingMinSize = 7.f;
	it.fBloomShootIncrease = 10.f;
	it.fBloomStandingDecrease = 12.0f;
	it.fBloomMovingDecrease = 2.f;
	it.fReloadTime = 2.f;
	it.fPulloutTime = 0.75f;
	sprintf(it.szName, "Kor91K (Common)");
	it.iTexture = 18;
	it.id = 400;
	g_Items.push_back(it);

	//Uncommon
	it.iType = 0;
	it.bAuto = false;
	it.iRarity = 1;
	it.iDamageStart = 79;
	it.iDamageEnd = 60;
	it.fRange = 100;
	it.fFirerate = 1.5;
	it.iBullets = 5;
	it.iMaxBullets = 5;
	it.iPellets = 1;
	it.iBulletConsumption = 1;
	it.iBulletType = 2;
	it.iReloadMethod = 1;
	it.fBloomMinSize = 0.f;
	it.fBloomMaxSize = 10.f;
	it.fBloomMovingMinSize = 7.f;
	it.fBloomShootIncrease = 10.f;
	it.fBloomStandingDecrease = 12.0f;
	it.fBloomMovingDecrease = 2.f;
	it.fReloadTime = 1.925f;
	it.fPulloutTime = 0.73f;
	sprintf(it.szName, "Kor91K (Uncommon)");
	it.iTexture = 18;
	it.id = 400;
	g_Items.push_back(it);

	//Rare
	it.iType = 0;
	it.bAuto = false;
	it.iRarity = 2;
	it.iDamageStart = 86;
	it.iDamageEnd = 63;
	it.fRange = 100;
	it.fFirerate = 1.5;
	it.iBullets = 5;
	it.iMaxBullets = 5;
	it.iPellets = 1;
	it.iBulletConsumption = 1;
	it.iBulletType = 2;
	it.iReloadMethod = 1;
	it.fBloomMinSize = 0.f;
	it.fBloomMaxSize = 10.f;
	it.fBloomMovingMinSize = 7.f;
	it.fBloomShootIncrease = 10.f;
	it.fBloomStandingDecrease = 12.0f;
	it.fBloomMovingDecrease = 2.f;
	it.fReloadTime = 1.85f;
	it.fPulloutTime = 0.71f;
	sprintf(it.szName, "Kor91K (Rare)");
	it.iTexture = 18;
	it.id = 400;
	g_Items.push_back(it);

	//Epic
	it.iType = 0;
	it.bAuto = false;
	it.iRarity = 3;
	it.iDamageStart = 94;
	it.iDamageEnd = 67;
	it.fRange = 100;
	it.fFirerate = 1.5;
	it.iBullets = 5;
	it.iMaxBullets = 5;
	it.iPellets = 1;
	it.iBulletConsumption = 1;
	it.iBulletType = 2;
	it.iReloadMethod = 1;
	it.fBloomMinSize = 0.f;
	it.fBloomMaxSize = 10.f;
	it.fBloomMovingMinSize = 7.f;
	it.fBloomShootIncrease = 10.f;
	it.fBloomStandingDecrease = 12.0f;
	it.fBloomMovingDecrease = 2.f;
	it.fReloadTime = 1.775f;
	it.fPulloutTime = 0.68f;
	sprintf(it.szName, "Kor91K (Epic)");
	it.iTexture = 18;
	it.id = 400;
	g_Items.push_back(it);

	//Legendary
	it.iType = 0;
	it.bAuto = false;
	it.iRarity = 4;
	it.iDamageStart = 101;
	it.iDamageEnd = 72;
	it.fRange = 100;
	it.fFirerate = 1.5;
	it.iBullets = 5;
	it.iMaxBullets = 5;
	it.iPellets = 1;
	it.iBulletConsumption = 1;
	it.iBulletType = 2;
	it.iReloadMethod = 1;
	it.fBloomMinSize = 0.f;
	it.fBloomMaxSize = 10.f;
	it.fBloomMovingMinSize = 7.f;
	it.fBloomShootIncrease = 10.f;
	it.fBloomStandingDecrease = 12.0f;
	it.fBloomMovingDecrease = 2.f;
	it.fReloadTime = 1.7f;
	it.fPulloutTime = 0.65f;
	sprintf(it.szName, "Kor91K (Legendary)");
	it.iTexture = 18;
	it.id = 400;
	g_Items.push_back(it);


	add_to_lootpool(49, 31);
	add_to_lootpool(50, 21);
	add_to_lootpool(51, 11);
	add_to_lootpool(52, 5);
	add_to_lootpool(53, 2);


	////////////////////////////////////////////////////////////////
	//                     FAMAS Burst Rifle
	////////////////////////////////////////////////////////////////

	it.fAudibleDistance = 50.f;
	it.iSoundID = 15;
	it.fVolumeMulti = 0.5f;

	it.fWeaponWeight = 0.025f;
	//Common
	it.iType = 1;
	it.bAuto = true;
	it.iRarity = 0;
	it.iDamageStart = 29;
	it.iDamageEnd = 25;
	it.fRange = 90;
	it.fFirerate = 2;
	it.iBullets = 30;
	it.iMaxBullets = 30;
	it.iPellets = 3;
	it.iBulletConsumption = 3;
	it.iBulletType = 2;
	it.iReloadMethod = 1;
	it.fBloomMinSize = 1.5f;
	it.fBloomMaxSize = 8.f;
	it.fBloomMovingMinSize = 6.5f;
	it.fBloomShootIncrease = 5.f;
	it.fBloomStandingDecrease = 9.7f;
	it.fBloomMovingDecrease = 2.f;
	it.fReloadTime = 2.5f;
	it.fPulloutTime = 0.65f;
	sprintf(it.szName, "FAMAS Burst (Common)");
	it.iTexture = 19;
	it.id = 221;
	g_Items.push_back(it);

	//Uncommon
	it.iType = 1;
	it.bAuto = true;
	it.iRarity = 1;
	it.iDamageStart = 30;
	it.iDamageEnd = 26;
	it.fRange = 90;
	it.fFirerate = 2;
	it.iBullets = 30;
	it.iMaxBullets = 30;
	it.iPellets = 3;
	it.iBulletConsumption = 3;
	it.iBulletType = 2;
	it.iReloadMethod = 1;
	it.fBloomMinSize = 1.45f;
	it.fBloomMaxSize = 7.8f;
	it.fBloomMovingMinSize = 6.4f;
	it.fBloomShootIncrease = 4.99f;
	it.fBloomStandingDecrease = 9.7f;
	it.fBloomMovingDecrease = 2.f;
	it.fReloadTime = 2.425f;
	it.fPulloutTime = 0.63f;
	sprintf(it.szName, "FAMAS Burst (Uncommon)");
	it.iTexture = 19;
	it.id = 221;
	g_Items.push_back(it);

	//Rare
	it.iType = 1;
	it.bAuto = true;
	it.iRarity = 2;
	it.iDamageStart = 32;
	it.iDamageEnd = 27;
	it.fRange = 90;
	it.fFirerate = 2;
	it.iBullets = 30;
	it.iMaxBullets = 30;
	it.iPellets = 3;
	it.iBulletConsumption = 3;
	it.iBulletType = 2;
	it.iReloadMethod = 1;
	it.fBloomMinSize = 1.4f;
	it.fBloomMaxSize = 7.65f;
	it.fBloomMovingMinSize = 6.3f;
	it.fBloomShootIncrease = 4.98f;
	it.fBloomStandingDecrease = 9.7f;
	it.fBloomMovingDecrease = 2.f;
	it.fReloadTime = 2.35f;
	it.fPulloutTime = 0.61f;
	sprintf(it.szName, "FAMAS Burst (Rare)");
	it.iTexture = 19;
	it.id = 221;
	g_Items.push_back(it);

	//Epic
	it.iType = 1;
	it.bAuto = true;
	it.iRarity = 3;
	it.iDamageStart = 33;
	it.iDamageEnd = 27;
	it.fRange = 90;
	it.fFirerate = 2;
	it.iBullets = 30;
	it.iMaxBullets = 30;
	it.iPellets = 3;
	it.iBulletConsumption = 3;
	it.iBulletType = 2;
	it.iReloadMethod = 1;
	it.fBloomMinSize = 1.3f;
	it.fBloomMaxSize = 7.55f;
	it.fBloomMovingMinSize = 6.2f;
	it.fBloomShootIncrease = 4.97f;
	it.fBloomStandingDecrease = 9.7f;
	it.fBloomMovingDecrease = 2.f;
	it.fReloadTime = 2.275f;
	it.fPulloutTime = 0.59f;
	sprintf(it.szName, "FAMAS Burst (Epic)");
	it.iTexture = 19;
	it.id = 221;
	g_Items.push_back(it);

	//Legendary
	it.iType = 1;
	it.bAuto = true;
	it.iRarity = 4;
	it.iDamageStart = 35;
	it.iDamageEnd = 28;
	it.fRange = 90;
	it.fFirerate = 2;
	it.iBullets = 30;
	it.iMaxBullets = 30;
	it.iPellets = 3;
	it.iBulletConsumption = 3;
	it.iBulletType = 2;
	it.iReloadMethod = 1;
	it.fBloomMinSize = 1.25f;
	it.fBloomMaxSize = 7.5f;
	it.fBloomMovingMinSize = 6.05f;
	it.fBloomShootIncrease = 4.96f;
	it.fBloomStandingDecrease = 9.7f;
	it.fBloomMovingDecrease = 2.1f;
	it.fReloadTime = 2.2f;
	it.fPulloutTime = 0.56f;
	sprintf(it.szName, "FAMAS Burst (Legendary)");
	it.iTexture = 19;
	it.id = 221;
	g_Items.push_back(it);

	add_to_lootpool(54, 64);
	add_to_lootpool(55, 45);
	add_to_lootpool(56, 33);
	add_to_lootpool(57, 20);
	add_to_lootpool(58, 8);

	////////////////////////////////////////////////////////////////
	//                     TACTICAT AR
	////////////////////////////////////////////////////////////////
	it.fWeaponWeight = 0.025f;


	it.fAudibleDistance = 45.f;
	it.iSoundID = 21;
	it.fVolumeMulti = 0.3f;

	//Common
	it.iType = 0;
	it.bAuto = true;
	it.iRarity = 0;
	it.iDamageStart = 25;
	it.iDamageEnd = 15;
	it.fRange = 80;
	it.fFirerate = 8.25;
	it.iBullets = 35;
	it.iMaxBullets = 35;
	it.iPellets = 1;
	it.iBulletConsumption = 1;
	it.iBulletType = 2;
	it.iReloadMethod = 1;
	it.fBloomMinSize = 2.f;
	it.fBloomMaxSize = 8.f;
	it.fBloomMovingMinSize = 3.2f;
	it.fBloomShootIncrease = 0.77f;
	it.fBloomStandingDecrease = 5.6f;
	it.fBloomMovingDecrease = 4.4f;
	it.fReloadTime = 2.5f;
	it.fPulloutTime = 0.65f;
	sprintf(it.szName, "TACTICAT AR (Common)");
	it.iTexture = 20;
	it.id = 231;
	g_Items.push_back(it);

	//Uncommon
	it.iType = 0;
	it.bAuto = true;
	it.iRarity = 1;
	it.iDamageStart = 26;
	it.iDamageEnd = 15;
	it.fRange = 80;
	it.fFirerate = 8.25;
	it.iBullets = 35;
	it.iMaxBullets = 35;
	it.iPellets = 1;
	it.iBulletConsumption = 1;
	it.iBulletType = 2;
	it.iReloadMethod = 1;
	it.fBloomMinSize = 1.95f;
	it.fBloomMaxSize = 7.9f;
	it.fBloomMovingMinSize = 3.12f;
	it.fBloomShootIncrease = 0.76f;
	it.fBloomStandingDecrease = 5.61f;
	it.fBloomMovingDecrease = 4.45f;
	it.fReloadTime = 2.45f;
	it.fPulloutTime = 0.63f;
	sprintf(it.szName, "TACTICAT AR (Uncommon)");
	it.iTexture = 20;
	it.id = 231;
	g_Items.push_back(it);

	//Rare
	it.iType = 0;
	it.bAuto = true;
	it.iRarity = 2;
	it.iDamageStart = 27;
	it.iDamageEnd = 16;
	it.fRange = 80;
	it.fFirerate = 8.25;
	it.iBullets = 35;
	it.iMaxBullets = 35;
	it.iPellets = 1;
	it.iBulletConsumption = 1;
	it.iBulletType = 2;
	it.iReloadMethod = 1;
	it.fBloomMinSize = 1.9f;
	it.fBloomMaxSize = 7.8f;
	it.fBloomMovingMinSize = 3.04f;
	it.fBloomShootIncrease = 0.75f;
	it.fBloomStandingDecrease = 5.62f;
	it.fBloomMovingDecrease = 4.5f;
	it.fReloadTime = 2.4f;
	it.fPulloutTime = 0.61f;
	sprintf(it.szName, "TACTICAT AR (Rare)");
	it.iTexture = 20;
	it.id = 231;
	g_Items.push_back(it);

	//Epic
	it.iType = 0;
	it.bAuto = true;
	it.iRarity = 3;
	it.iDamageStart = 28;
	it.iDamageEnd = 16;
	it.fRange = 80;
	it.fFirerate = 8.25;
	it.iBullets = 35;
	it.iMaxBullets = 35;
	it.iPellets = 1;
	it.iBulletConsumption = 1;
	it.iBulletType = 2;
	it.iReloadMethod = 1;
	it.fBloomMinSize = 1.85f;
	it.fBloomMaxSize = 7.7f;
	it.fBloomMovingMinSize = 2.96f;
	it.fBloomShootIncrease = 0.74f;
	it.fBloomStandingDecrease = 5.63f;
	it.fBloomMovingDecrease = 4.55f;
	it.fReloadTime = 2.35f;
	it.fPulloutTime = 0.59f;
	sprintf(it.szName, "TACTICAT AR (Epic)");
	it.iTexture = 20;
	it.id = 231;
	g_Items.push_back(it);

	//Legendary
	it.iType = 0;
	it.bAuto = true;
	it.iRarity = 4;
	it.iDamageStart = 29;
	it.iDamageEnd = 17;
	it.fRange = 80;
	it.fFirerate = 8.25;
	it.iBullets = 35;
	it.iMaxBullets = 35;
	it.iPellets = 1;
	it.iBulletConsumption = 1;
	it.iBulletType = 2;
	it.iReloadMethod = 1;
	it.fBloomMinSize = 1.8f;
	it.fBloomMaxSize = 7.5f;
	it.fBloomMovingMinSize = 2.88f;
	it.fBloomShootIncrease = 0.73f;
	it.fBloomStandingDecrease = 5.64f;
	it.fBloomMovingDecrease = 4.6f;
	it.fReloadTime = 2.3f;
	it.fPulloutTime = 0.56f;
	sprintf(it.szName, "TACTICAT AR (Legendary)");
	it.iTexture = 20;
	it.id = 231;
	g_Items.push_back(it);

	add_to_lootpool(59, 60);
	add_to_lootpool(60, 48);
	add_to_lootpool(61, 24);
	add_to_lootpool(62, 17);
	add_to_lootpool(63, 8);

	////////////////////////////////////////////////////////////////
	//                     MAGNUM SNIPER
	////////////////////////////////////////////////////////////////


	it.fAudibleDistance = 70.f;
	it.iSoundID = 23;
	it.fVolumeMulti = 1.f;

	it.fWeaponWeight = 0.125f;
	//Rare
	it.iType = 2;
	it.bAuto = false;
	it.iRarity = 2;
	it.iDamageStart = 100;
	it.iDamageEnd = 100;
	it.fRange = 150;
	it.fFirerate = 1;
	it.iBullets = 1;
	it.iMaxBullets = 1;
	it.iPellets = 1;
	it.iBulletConsumption = 1;
	it.iBulletType = 2;
	it.iReloadMethod = 1;
	it.fBloomMinSize = 0.f;
	it.fBloomMaxSize = 30.f;
	it.fBloomMovingMinSize = 15.f;
	it.fBloomShootIncrease = 15.f;
	it.fBloomStandingDecrease = 15.f;
	it.fBloomMovingDecrease = 3.4f;
	it.fReloadTime = 2.f;
	it.fPulloutTime = 0.65f;
	sprintf(it.szName, "MAGNUM Sniper (Rare)");
	it.iTexture = 21;
	it.id = 500;
	it.fProjectileSpeed = 110.f;
	g_Items.push_back(it);

	//Epic
	it.iType = 2;
	it.bAuto = false;
	it.iRarity = 3;
	it.iDamageStart = 110;
	it.iDamageEnd = 110;
	it.fRange = 150;
	it.fFirerate = 1;
	it.iBullets = 1;
	it.iMaxBullets = 1;
	it.iPellets = 1;
	it.iBulletConsumption = 1;
	it.iBulletType = 2;
	it.iReloadMethod = 1;
	it.fBloomMinSize = 0.f;
	it.fBloomMaxSize = 30.f;
	it.fBloomMovingMinSize = 15.f;
	it.fBloomShootIncrease = 15.f;
	it.fBloomStandingDecrease = 15.f;
	it.fBloomMovingDecrease = 3.4f;
	it.fReloadTime = 1.925f;
	it.fPulloutTime = 0.625f;
	sprintf(it.szName, "MAGNUM Sniper (Epic)");
	it.iTexture = 21;
	it.id = 500;
	g_Items.push_back(it);

	//LEGNDARY
	it.iType = 2;
	it.bAuto = false;
	it.iRarity = 4;
	it.iDamageStart = 120;
	it.iDamageEnd = 120;
	it.fRange = 150;
	it.fFirerate = 1;
	it.iBullets = 1;
	it.iMaxBullets = 1;
	it.iPellets = 1;
	it.iBulletConsumption = 1;
	it.iBulletType = 2;
	it.iReloadMethod = 1;
	it.fBloomMinSize = 0.f;
	it.fBloomMaxSize = 30.f;
	it.fBloomMovingMinSize = 15.f;
	it.fBloomShootIncrease = 15.f;
	it.fBloomStandingDecrease = 15.f;
	it.fBloomMovingDecrease = 3.4f;
	it.fReloadTime = 1.85f;
	it.fPulloutTime = 0.6f;
	sprintf(it.szName, "MAGNUM Sniper (Legendary)");
	it.iTexture = 21;
	it.id = 500;
	g_Items.push_back(it);

	add_to_lootpool(64, 18);
	add_to_lootpool(65, 11);
	add_to_lootpool(66, 6);

	////////////////////////////////////////////////////////////////
	//                     Hunting Rifle
	////////////////////////////////////////////////////////////////

	it.fAudibleDistance = 60.f;
	it.iSoundID = 22;
	it.fVolumeMulti = 1.f;

	it.fWeaponWeight = 0.05f;
	//Uncommon
	it.iType = 2;
	it.bAuto = true;
	it.iRarity = 1;
	it.iDamageStart = 80;
	it.iDamageEnd = 73;
	it.fRange = 100;
	it.fFirerate =1;
	it.iBullets = 1;
	it.iMaxBullets = 1;
	it.iPellets = 1;
	it.iBulletConsumption = 1;
	it.iBulletType = 2;
	it.iReloadMethod = 1;
	it.fBloomMinSize = 0.f;
	it.fBloomMaxSize = 20.f;
	it.fBloomMovingMinSize = 10.f;
	it.fBloomShootIncrease = 8.0f;
	it.fBloomStandingDecrease = 15.f;
	it.fBloomMovingDecrease = 3.4f;
	it.fReloadTime = 1.3f;
	it.fPulloutTime = 0.55f;
	it.fProjectileSpeed = 90.f;
	sprintf(it.szName, "Hunting Rifle (Uncommon)");
	it.iTexture = 22;
	it.id = 510;
	g_Items.push_back(it);

	//Rare
	it.iType = 2;
	it.bAuto = true;
	it.iRarity = 2;
	it.iDamageStart = 88;
	it.iDamageEnd = 79;
	it.fRange = 100;
	it.fFirerate = 1;
	it.iBullets = 1;
	it.iMaxBullets = 1;
	it.iPellets = 1;
	it.iBulletConsumption = 1;
	it.iBulletType = 2;
	it.iReloadMethod = 1;
	it.fBloomMinSize = 0.f;
	it.fBloomMaxSize = 20.f;
	it.fBloomMovingMinSize = 10.f;
	it.fBloomShootIncrease = 8.0f;
	it.fBloomStandingDecrease = 15.f;
	it.fBloomMovingDecrease = 3.4f;
	it.fReloadTime = 1.2f;
	it.fPulloutTime = 0.525f;
	it.fProjectileSpeed = 50.f;
	sprintf(it.szName, "Hunting Rifle (Rare)");
	it.iTexture = 22;
	it.id = 510;
	g_Items.push_back(it);

	add_to_lootpool(67, 66);
	add_to_lootpool(68, 28);

	////////////////////////////////////////////////////////////////
	//                     Semi Auto Sniper
	////////////////////////////////////////////////////////////////

	it.fAudibleDistance = 60.f;
	it.iSoundID = 29;
	it.fVolumeMulti = 1.f;

	it.fWeaponWeight = 0.075f;
	//Uncommon
	it.iType = 2;
	it.bAuto = true;
	it.iRarity = 1;
	it.iDamageStart = 48;
	it.iDamageEnd = 40;
	it.fRange = 100;
	it.fFirerate = 2.f;
	it.iBullets = 10;
	it.iMaxBullets = 10;
	it.iPellets = 1;
	it.iBulletConsumption = 1;
	it.iBulletType = 2;
	it.iReloadMethod = 1;
	it.fBloomMinSize = 0.f;
	it.fBloomMaxSize = 30.f;
	it.fBloomMovingMinSize = 20.f;
	it.fBloomShootIncrease = 10.f;
	it.fBloomStandingDecrease = 18.f;
	it.fBloomMovingDecrease = 3.4f;
	it.fReloadTime = 3.f;
	it.fPulloutTime = 0.65f;
	it.fProjectileSpeed = 75.f;
	sprintf(it.szName, "Semi-Auto Sniper (Uncommon)");
	it.iTexture = 23;
	it.id = 520;
	g_Items.push_back(it);

	//Rare
	it.iType = 2;
	it.bAuto = true;
	it.iRarity = 2;
	it.iDamageStart = 54;
	it.iDamageEnd = 45;
	it.fRange = 100;
	it.fFirerate = 2.f;
	it.iBullets = 10;
	it.iMaxBullets = 10;
	it.iPellets = 1;
	it.iBulletConsumption = 1;
	it.iBulletType = 2;
	it.iReloadMethod = 1;
	it.fBloomMinSize = 0.f;
	it.fBloomMaxSize = 30.f;
	it.fBloomMovingMinSize = 20.f;
	it.fBloomShootIncrease = 10.f;
	it.fBloomStandingDecrease = 18.f;
	it.fBloomMovingDecrease = 3.4f;
	it.fReloadTime = 2.9f;
	it.fPulloutTime = 0.625f;
	it.fProjectileSpeed = 45.f;
	sprintf(it.szName, "Semi-Auto Sniper (Rare)");
	it.iTexture = 23;
	it.id = 520;
	g_Items.push_back(it);

	//Epic
	it.iType = 2;
	it.bAuto = true;
	it.iRarity = 3;
	it.iDamageStart = 60;
	it.iDamageEnd = 50;
	it.fRange = 100;
	it.fFirerate = 2.f;
	it.iBullets = 10;
	it.iMaxBullets = 10;
	it.iPellets = 1;
	it.iBulletConsumption = 1;
	it.iBulletType = 2;
	it.iReloadMethod = 1;
	it.fBloomMinSize = 0.f;
	it.fBloomMaxSize = 30.f;
	it.fBloomMovingMinSize = 20.f;
	it.fBloomShootIncrease = 10.f;
	it.fBloomStandingDecrease = 18.f;
	it.fBloomMovingDecrease = 3.4f;
	it.fReloadTime = 2.75f;
	it.fPulloutTime = 0.6f;
	it.fProjectileSpeed = 45.f;
	sprintf(it.szName, "Semi-Auto Sniper (Epic)");
	it.iTexture = 23;
	it.id = 520;
	g_Items.push_back(it);

	add_to_lootpool(69, 28);
	add_to_lootpool(70, 18);
	add_to_lootpool(71, 14);





	////////////////////////////////////////////////////////////////
	//                     Rocket Launcher
	////////////////////////////////////////////////////////////////

	it.fAudibleDistance = 30.f;
	it.iSoundID = 33;
	it.fVolumeMulti = 0.6f;

	it.fWeaponWeight = 0.075f;
	//Rare
	it.iType = 3;
	it.bAuto = false;
	it.iRarity = 2;
	it.iDamageStart = 120;
	it.iDamageEnd = 60;
	it.fExplosionRange = 2.6f;
	it.fExplosiveLifetime = 2.f;
	it.iExplosiveType = 0;
	it.fRange = 100;
	it.fFirerate = 1.f;
	it.iBullets = 1;
	it.iMaxBullets = 1;
	it.iPellets = 1;
	it.iBulletConsumption = 1;
	it.iBulletType = 2;
	it.iReloadMethod = 1;
	it.fBloomMinSize = 2.f;
	it.fBloomMaxSize = 10.f;
	it.fBloomMovingMinSize = 10.f;
	it.fBloomShootIncrease = 10.f;
	it.fBloomStandingDecrease = 18.f;
	it.fBloomMovingDecrease = 3.4f;
	it.fReloadTime = 3.6f;
	it.fPulloutTime = 0.75f;
	it.fProjectileSpeed = 32.5f;
	it.fProjectileSpeedMax = 35.f;
	sprintf(it.szName, "Rocket Launcher (Rare)");
	it.iTexture = 24;
	it.id = 600;
	g_Items.push_back(it);

	//Epic
	it.iType = 3;
	it.bAuto = false;
	it.iRarity = 3;
	it.iDamageStart = 130;
	it.iDamageEnd = 65;
	it.fExplosionRange = 2.7f;
	it.fRange = 100;
	it.fFirerate = 1.f;
	it.iBullets = 1;
	it.iMaxBullets = 1;
	it.iPellets = 1;
	it.iBulletConsumption = 1;
	it.iBulletType = 2;
	it.iReloadMethod = 1;
	it.fBloomMinSize = 2.f;
	it.fBloomMaxSize = 10.f;
	it.fBloomMovingMinSize = 10.f;
	it.fBloomShootIncrease = 10.f;
	it.fBloomStandingDecrease = 18.f;
	it.fBloomMovingDecrease = 3.4f;
	it.fReloadTime = 3.25f;
	it.fPulloutTime = 0.725f;
	it.fProjectileSpeed = 32.5f;
	it.fProjectileSpeedMax = 35.f;
	sprintf(it.szName, "Rocket Launcher (Epic)");
	it.iTexture = 24;
	it.id = 600;
	g_Items.push_back(it);

	//Legendary
	it.iType = 3;
	it.bAuto = false;
	it.iRarity = 4;
	it.iDamageStart = 140;
	it.iDamageEnd = 70;
	it.fExplosionRange = 2.8f;
	it.fRange = 100;
	it.fFirerate = 1.f;
	it.iBullets = 1;
	it.iMaxBullets = 1;
	it.iPellets = 1;
	it.iBulletConsumption = 1;
	it.iBulletType = 2;
	it.iReloadMethod = 1;
	it.fBloomMinSize = 2.f;
	it.fBloomMaxSize = 10.f;
	it.fBloomMovingMinSize = 10.f;
	it.fBloomShootIncrease = 10.f;
	it.fBloomStandingDecrease = 18.f;
	it.fBloomMovingDecrease = 3.4f;
	it.fReloadTime = 2.9f;
	it.fPulloutTime = 0.725f;
	it.fProjectileSpeed = 32.5f;
	it.fProjectileSpeedMax = 35.f;
	sprintf(it.szName, "Rocket Launcher (Legendary)");
	it.iTexture = 24;
	it.id = 600;
	g_Items.push_back(it);


	add_to_lootpool(72, 17);
	add_to_lootpool(73, 9);
	add_to_lootpool(74, 5);


	////////////////////////////////////////////////////////////////
	//                     Grenade Launcher
	////////////////////////////////////////////////////////////////

	it.fAudibleDistance = 30.f;
	it.iSoundID = 34;
	it.fVolumeMulti = 0.6f;

	it.fWeaponWeight = 0.075f;
	//Rare
	it.iType = 3;
	it.bAuto = true;
	it.iRarity = 2;
	it.iDamageStart = 90;
	it.iDamageEnd = 45;
	it.fExplosionRange = 1.9f;
	it.fExplosiveLifetime = 5.f;
	it.iExplosiveType = 1;
	it.fRange = 100;
	it.fFirerate = 1.6f;
	it.iBullets = 6;
	it.iMaxBullets = 6;
	it.iPellets = 1;
	it.iBulletConsumption = 1;
	it.iBulletType = 2;
	it.iReloadMethod = 1;
	it.fBloomMinSize = 2.f;
	it.fBloomMaxSize = 10.f;
	it.fBloomMovingMinSize = 10.f;
	it.fBloomShootIncrease = 5.f;
	it.fBloomStandingDecrease = 18.f;
	it.fBloomMovingDecrease = 3.4f;
	it.fReloadTime = 3.f;
	it.fPulloutTime = 0.75f;
	it.fProjectileSpeed = 16.f;
	it.fProjectileSpeedMax = 28.f;
	sprintf(it.szName, "Grenade Launcher (Rare)");
	it.iTexture = 25;
	it.id = 610;
	g_Items.push_back(it);

	//Epic
	it.iType = 3;
	it.bAuto = true;
	it.iRarity = 3;
	it.iDamageStart = 100;
	it.iDamageEnd = 50;
	it.fExplosionRange = 1.95f;
	it.fExplosiveLifetime = 5.f;
	it.iExplosiveType = 1;
	it.fRange = 100;
	it.fFirerate = 1.6f;
	it.iBullets = 6;
	it.iMaxBullets = 6;
	it.iPellets = 1;
	it.iBulletConsumption = 1;
	it.iBulletType = 2;
	it.iReloadMethod = 1;
	it.fBloomMinSize = 2.f;
	it.fBloomMaxSize = 10.f;
	it.fBloomMovingMinSize = 10.f;
	it.fBloomShootIncrease = 5.f;
	it.fBloomStandingDecrease = 18.f;
	it.fBloomMovingDecrease = 3.4f;
	it.fReloadTime = 2.9f;
	it.fPulloutTime = 0.73f;
	it.fProjectileSpeed = 16.f;
	it.fProjectileSpeedMax = 28.f;
	sprintf(it.szName, "Grenade Launcher (Epic)");
	it.iTexture = 25;
	it.id = 610;
	g_Items.push_back(it);

	//Legendary
	it.iType = 3;
	it.bAuto = true;
	it.iRarity = 4;
	it.iDamageStart = 110;
	it.iDamageEnd = 55;
	it.fExplosionRange = 2.f;
	it.fExplosiveLifetime = 5.f;
	it.iExplosiveType = 1;
	it.fRange = 100;
	it.fFirerate = 1.6f;
	it.iBullets = 6;
	it.iMaxBullets = 6;
	it.iPellets = 1;
	it.iBulletConsumption = 1;
	it.iBulletType = 2;
	it.iReloadMethod = 1;
	it.fBloomMinSize = 2.f;
	it.fBloomMaxSize = 10.f;
	it.fBloomMovingMinSize = 10.f;
	it.fBloomShootIncrease = 5.f;
	it.fBloomStandingDecrease = 18.f;
	it.fBloomMovingDecrease = 3.4f;
	it.fReloadTime = 2.8f;
	it.fPulloutTime = 0.71f;
	it.fProjectileSpeed = 16.f;
	it.fProjectileSpeedMax = 28.f;
	sprintf(it.szName, "Grenade Launcher (Legendary)");
	it.iTexture = 25;
	it.id = 610;
	g_Items.push_back(it);

	add_to_lootpool(75, 22);
	add_to_lootpool(76, 15);
	add_to_lootpool(77, 6);


	////////////////////////////////////////////////////////////////
	//                     Hand Grenade
	////////////////////////////////////////////////////////////////

	it.fAudibleDistance = 30.f;
	it.iSoundID = 35;
	it.fVolumeMulti = 0.35f;

	it.fWeaponWeight = 0.025f;
	//Uncommon
	it.iType = 3;
	it.bAuto = false;
	it.iRarity = 1;
	it.iDamageStart = 110;
	it.iDamageEnd = 55;
	it.fExplosionRange = 2.3f;
	it.fExplosiveLifetime = 3.f;
	it.iExplosiveType = 2;
	it.fRange = 100;
	it.fFirerate = 1.f;
	it.iBullets = 3;
	it.iMaxBullets = 6;
	it.iPellets = 1;
	it.iBulletConsumption = 1;
	it.iBulletType = 2;
	it.iReloadMethod = 1;
	it.fBloomMinSize = 0.f;
	it.fBloomMaxSize = 2.f;
	it.fBloomMovingMinSize = 2.f;
	it.fBloomShootIncrease = 5.f;
	it.fBloomStandingDecrease = 18.f;
	it.fBloomMovingDecrease = 3.4f;
	it.fReloadTime = 3.f;
	it.fPulloutTime = 0.35f;
	it.fProjectileSpeed = 15.f;
	it.fProjectileSpeedMax = 25.f;
	sprintf(it.szName, "Hand Grenade");
	it.iTexture = 26;
	it.id = 1200;
	g_Items.push_back(it);

	add_to_lootpool(78, 35);



	////////////////////////////////////////////////////////////////
	//                         LMG
	////////////////////////////////////////////////////////////////

	it.fAudibleDistance = 47.f;
	it.iSoundID = 40;
	it.fVolumeMulti = 1.f;



	it.fWeaponWeight = 0.1f;
	//Rare
	it.iType = 0;
	it.bAuto = true;
	it.iRarity = 2;
	it.iDamageStart = 28;
	it.iDamageEnd = 10;
	it.fRange = 70;
	it.fFirerate = 10;
	it.iBullets = 100;
	it.iBulletConsumption = 1;
	it.iMaxBullets = 100;
	it.iBulletType = 1;
	it.fBloomMinSize = 2.f;
	it.fBloomMaxSize = 10.f;
	it.fBloomMovingMinSize = 6.f;
	it.fBloomShootIncrease = 0.9f;
	it.fBloomStandingDecrease = 8.3f;
	it.fBloomMovingDecrease = 6.5f;
	it.fReloadTime = 3.75f;
	it.fPulloutTime = 0.8f;
	sprintf(it.szName, "LMG (Rare)");
	it.iTexture = 27;
	it.id = 161;

	g_Items.push_back(it);

	//Epic
	it.iType = 0;
	it.bAuto = true;
	it.iRarity = 3;
	it.iDamageStart = 29;
	it.iDamageEnd = 11;
	it.fRange = 70;
	it.fFirerate = 10;
	it.iBullets = 100;
	it.iBulletConsumption = 1;
	it.iMaxBullets = 100;
	it.iBulletType = 1;
	it.fBloomMinSize = 1.98f;
	it.fBloomMaxSize = 9.75f;
	it.fBloomMovingMinSize = 5.8f;
	it.fBloomShootIncrease = 0.9f;
	it.fBloomStandingDecrease = 8.35f;
	it.fBloomMovingDecrease = 6.53f;
	it.fReloadTime = 3.625f;
	it.fPulloutTime = 0.76f;
	sprintf(it.szName, "LMG (Epic)");
	it.iTexture = 27;
	it.id = 161;

	g_Items.push_back(it);

	//Legendary
	it.iType = 0;
	it.bAuto = true;
	it.iRarity = 4;
	it.iDamageStart = 30;
	it.iDamageEnd = 12;
	it.fRange = 70;
	it.fFirerate = 10;
	it.iBullets = 100;
	it.iBulletConsumption = 1;
	it.iMaxBullets = 100;
	it.iBulletType = 1;
	it.fBloomMinSize = 1.96f;
	it.fBloomMaxSize = 9.5f;
	it.fBloomMovingMinSize = 5.6f;
	it.fBloomShootIncrease = 0.9f;
	it.fBloomStandingDecrease = 8.4f;
	it.fBloomMovingDecrease = 6.55f;
	it.fReloadTime = 3.5f;
	it.fPulloutTime = 0.72f;
	sprintf(it.szName, "LMG (Legendary)");
	it.iTexture = 27;
	it.id = 161;

	g_Items.push_back(it);

	add_to_lootpool(79, 26);
	add_to_lootpool(80, 12);
	add_to_lootpool(81, 4);


	////////////////////////////////////////////////////////////////
	//                        Double Barrel
	////////////////////////////////////////////////////////////////

	it.fAudibleDistance = 50.f;
	it.iSoundID = 41;
	it.fVolumeMulti = 1.f;

	it.fWeaponWeight = 0.02f;
	//Rare
	it.iType = 1;
	it.bAuto = true;
	it.iRarity = 2;
	it.iDamageStart = 11;
	it.iDamageEnd = 0;
	it.fRange = 14;
	it.fFirerate = 7;
	it.iBullets = 2;
	it.iMaxBullets = 2;
	it.iPellets = 10;
	it.iBulletConsumption = 1;
	it.iBulletType = 2;
	it.iReloadMethod = 1;
	it.fBloomMinSize = 7.f;
	it.fBloomMaxSize = 22.5f;
	it.fBloomMovingMinSize = 15.f;
	it.fBloomShootIncrease = 5.1f;
	it.fBloomStandingDecrease = 12.1f;
	it.fBloomMovingDecrease = 7.f;
	it.fReloadTime = 1.25f;
	it.fPulloutTime = 0.55f;
	sprintf(it.szName, "Double-barrel Shotgun (Rare)");
	it.iTexture = 28;
	it.id = 330;
	g_Items.push_back(it);
	//Epic
	it.iType = 1;
	it.bAuto = true;
	it.iRarity = 3;
	it.iDamageStart = 12;
	it.iDamageEnd = 1;
	it.fRange = 14.5;
	it.fFirerate = 7;
	it.iBullets = 2;
	it.iMaxBullets = 2;
	it.iPellets = 10;
	it.iBulletConsumption = 1;
	it.iBulletType = 2;
	it.iReloadMethod = 1;
	it.fBloomMinSize = 6.9f;
	it.fBloomMaxSize = 22.25f;
	it.fBloomMovingMinSize = 14.8f;
	it.fBloomShootIncrease = 5.f;
	it.fBloomStandingDecrease = 12.15f;
	it.fBloomMovingDecrease = 7.1f;
	it.fReloadTime = 1.2f;
	it.fPulloutTime = 0.525f;
	sprintf(it.szName, "Double-barrel Shotgun (Epic)");
	it.iTexture = 28;
	it.id = 330;
	g_Items.push_back(it);
	//Legendary
	it.iType = 1;
	it.bAuto = true;
	it.iRarity = 4;
	it.iDamageStart = 13;
	it.iDamageEnd = 2;
	it.fRange = 15;
	it.fFirerate = 7;
	it.iBullets = 2;
	it.iMaxBullets = 2;
	it.iPellets = 10;
	it.iBulletConsumption = 1;
	it.iBulletType = 2;
	it.iReloadMethod = 1;
	it.fBloomMinSize = 6.8f;
	it.fBloomMaxSize = 22.f;
	it.fBloomMovingMinSize = 14.6f;
	it.fBloomShootIncrease = 4.9f;
	it.fBloomStandingDecrease = 12.2f;
	it.fBloomMovingDecrease = 7.2f;
	it.fReloadTime = 1.15f;
	it.fPulloutTime = 0.5f;
	sprintf(it.szName, "Double-barrel Shotgun (Legendary)");
	it.iTexture = 28;
	it.id = 330;
	g_Items.push_back(it);


	add_to_lootpool(82, 30);
	add_to_lootpool(83, 15);
	add_to_lootpool(84, 5);

	////////////////////////////////////////////////////////////////
	//                        Combat Shotgun
	////////////////////////////////////////////////////////////////

	it.fAudibleDistance = 50.f;
	it.iSoundID = 42;
	it.fVolumeMulti = 1.f;

	it.fWeaponWeight = 0.02f;
	//Rare
	it.iType = 1;
	it.bAuto = true;
	it.iRarity = 2;
	it.iDamageStart = 9;
	it.iDamageEnd = 6;
	it.fRange = 25;
	it.fFirerate = 2.4;
	it.iBullets = 10;
	it.iMaxBullets = 10;
	it.iPellets = 8;
	it.iBulletConsumption = 1;
	it.iBulletType = 2;
	it.iReloadMethod = 2;
	it.fBloomMinSize = 3.f;
	it.fBloomMaxSize = 12.5f;
	it.fBloomMovingMinSize = 8.f;
	it.fBloomShootIncrease = 6.f;
	it.fBloomStandingDecrease = 13.5f;
	it.fBloomMovingDecrease = 10.f;
	it.fReloadTime = 0.65f;
	it.fPulloutTime = 0.55f;
	sprintf(it.szName, "Combat Shottie (Rare)");
	it.iTexture = 29;
	it.id = 340;
	g_Items.push_back(it);

	//Epic
	it.iType = 1;
	it.bAuto = true;
	it.iRarity = 3;
	it.iDamageStart = 10;
	it.iDamageEnd = 7;
	it.fRange = 26;
	it.fFirerate = 2.4;
	it.iBullets = 10;
	it.iMaxBullets = 10;
	it.iPellets = 8;
	it.iBulletConsumption = 1;
	it.iBulletType = 2;
	it.iReloadMethod = 2;
	it.fBloomMinSize = 3.f;
	it.fBloomMaxSize = 12.3f;
	it.fBloomMovingMinSize = 7.9f;
	it.fBloomShootIncrease = 6.f;
	it.fBloomStandingDecrease = 13.53f;
	it.fBloomMovingDecrease = 10.1f;
	it.fReloadTime = 0.63f;
	it.fPulloutTime = 0.525f;
	sprintf(it.szName, "Combat Shottie (Epic)");
	it.iTexture = 29;
	it.id = 340;
	g_Items.push_back(it);

	//Legendary
	it.iType = 1;
	it.bAuto = true;
	it.iRarity = 4;
	it.iDamageStart = 11;
	it.iDamageEnd = 7;
	it.fRange = 27;
	it.fFirerate = 2.4;
	it.iBullets = 10;
	it.iMaxBullets = 10;
	it.iPellets = 8;
	it.iBulletConsumption = 1;
	it.iBulletType = 2;
	it.iReloadMethod = 2;
	it.fBloomMinSize = 3.f;
	it.fBloomMaxSize = 12.1f;
	it.fBloomMovingMinSize = 7.8f;
	it.fBloomShootIncrease = 6.f;
	it.fBloomStandingDecrease = 13.55f;
	it.fBloomMovingDecrease = 10.2f;
	it.fReloadTime = 0.61f;
	it.fPulloutTime = 0.5f;
	sprintf(it.szName, "Combat Shottie (Legendary)");
	it.iTexture = 29;
	it.id = 340;
	g_Items.push_back(it);


	add_to_lootpool(85, 25);
	add_to_lootpool(86, 16);
	add_to_lootpool(87, 6);

	////////////////////////////////////////////////////////////////
	//                         Tommygun
	////////////////////////////////////////////////////////////////

	it.fAudibleDistance = 47.f;
	it.iSoundID = 43;
	it.fVolumeMulti = 1.f;



	it.fWeaponWeight = 0.05f;
	//Common
	it.iType = 0;
	it.bAuto = true;
	it.iRarity = 0;
	it.iDamageStart = 26;
	it.iDamageEnd = 10;
	it.fRange = 70;
	it.fFirerate = 9;
	it.iBullets = 50;
	it.iBulletConsumption = 1;
	it.iReloadMethod = 1;
	it.iMaxBullets = 50;
	it.iBulletType = 1;
	it.fBloomMinSize = 2.f;
	it.fBloomMaxSize = 10.f;
	it.fBloomMovingMinSize = 4.f;
	it.fBloomShootIncrease = 1.f;
	it.fBloomStandingDecrease = 8.3f;
	it.fBloomMovingDecrease = 7.8f;
	it.fReloadTime = 2.7f;
	it.fPulloutTime = 0.67f;
	sprintf(it.szName, "Tommygun (Common)");
	it.iTexture = 30;
	it.id = 161;

	g_Items.push_back(it);

	//Uncommon
	it.iType = 0;
	it.bAuto = true;
	it.iRarity = 1;
	it.iDamageStart = 27;
	it.iDamageEnd = 11;
	it.fRange = 70;
	it.fFirerate = 9;
	it.iBullets = 50;
	it.iBulletConsumption = 1;
	it.iMaxBullets = 50;
	it.iBulletType = 1;
	it.fBloomMinSize = 1.95f;
	it.fBloomMaxSize = 9.8f;
	it.fBloomMovingMinSize = 3.9f;
	it.fBloomShootIncrease = 0.99f;
	it.fBloomStandingDecrease = 8.35f;
	it.fBloomMovingDecrease = 7.9f;
	it.fReloadTime = 2.6f;
	it.fPulloutTime = 0.65f;
	sprintf(it.szName, "Tommygun (Uncommon)");
	it.iTexture = 30;
	it.id = 161;

	g_Items.push_back(it);

	//Rare
	it.iType = 0;
	it.bAuto = true;
	it.iRarity = 2;
	it.iDamageStart = 28;
	it.iDamageEnd = 12;
	it.fRange = 70;
	it.fFirerate = 9;
	it.iBullets = 50;
	it.iBulletConsumption = 1;
	it.iMaxBullets = 50;
	it.iBulletType = 1;
	it.fBloomMinSize = 1.9f;
	it.fBloomMaxSize = 9.6f;
	it.fBloomMovingMinSize = 3.8f;
	it.fBloomShootIncrease = 0.98f;
	it.fBloomStandingDecrease = 8.4f;
	it.fBloomMovingDecrease = 8.f;
	it.fReloadTime = 2.5f;
	it.fPulloutTime = 0.63f;
	sprintf(it.szName, "Tommygun (Rare)");
	it.iTexture = 30;
	it.id = 161;

	g_Items.push_back(it);

	add_to_lootpool(88, 66);
	add_to_lootpool(89, 45);
	add_to_lootpool(90, 29);

	//MYTHICS
	////////////////////////////////////////////////////////////////
	//                       Silenced MP5
	////////////////////////////////////////////////////////////////

	it.fAudibleDistance = 15.f;
	it.iSoundID = 17;
	it.fVolumeMulti = 1.f;

	it.fWeaponWeight = 0.01f;
	//Mythic
	it.ListIndex = 12;
	it.iType = 0;
	it.bAuto = true;
	it.iRarity = 5;
	it.iDamageStart = 30;
	it.iDamageEnd = 15;
	it.fRange = 60;
	it.fFirerate = 9;
	it.iBullets = 30;
	it.iMaxBullets = 30;
	it.iReloadMethod = 1;
	it.iBulletConsumption = 1;
	it.iBulletType = 1;
	it.fBloomMinSize = 0.f;
	it.fBloomMaxSize = 5.0f;
	it.fBloomMovingMinSize = 3.0f;
	it.fBloomShootIncrease = 0.95f;
	it.fBloomStandingDecrease = 7.0f;
	it.fBloomMovingDecrease = 4.1f;
	it.fReloadTime = 2.1f;
	it.fPulloutTime = 0.5f;
	sprintf(it.szName, "Silenced MP5 (Mythic)");
	it.iTexture = 2;
	it.id = 111;
	g_Items.push_back(it);

	////////////////////////////////////////////////////////////////
	//                         Tommygun
	////////////////////////////////////////////////////////////////

	it.fAudibleDistance = 47.f;
	it.iSoundID = 43;
	it.fVolumeMulti = 1.f;
	it.fWeaponWeight = 0.05f;

	//Mythic
	it.iType = 0;
	it.bAuto = true;
	it.iRarity = 5;
	it.iDamageStart = 31;
	it.iDamageEnd = 10;
	it.fRange = 70;
	it.fFirerate = 9.25;
	it.iBullets = 50;
	it.iBulletConsumption = 1;
	it.iMaxBullets = 50;
	it.iBulletType = 1;
	it.fBloomMinSize = 1.5f;
	it.fBloomMaxSize = 9.6f;
	it.fBloomMovingMinSize = 3.8f;
	it.fBloomShootIncrease = 0.95f;
	it.fBloomStandingDecrease = 8.33f;
	it.fBloomMovingDecrease = 7.9f;
	it.fReloadTime = 2.1f;
	it.fPulloutTime = 0.55f;
	sprintf(it.szName, "Tommygun (Mythic)");
	it.iTexture = 30;
	it.id = 161;

	g_Items.push_back(it);

	////////////////////////////////////////////////////////////////
	//                         MINIGUN
	////////////////////////////////////////////////////////////////

	it.fAudibleDistance = 40.f;
	it.iSoundID = 26;
	it.fVolumeMulti = 1.f;

	it.fWeaponWeight = 0.1f;
	//Legendary
	it.ListIndex = 30;
	it.iType = 0;
	it.bAuto = true;
	it.iRarity = 5;
	it.iDamageStart = 22;
	it.iDamageEnd = 6;
	it.fRange = 45;
	it.fFirerate = 15;
	it.iBullets = 50;
	it.iBulletConsumption = 1;
	it.iMaxBullets = 50;
	it.iBulletType = 1;
	it.fBloomMinSize = 2.5f;
	it.fBloomMaxSize = 11.f;
	it.fBloomMovingMinSize = 7.f;
	it.fBloomShootIncrease = 0.75f;
	it.fBloomStandingDecrease = 9.5f;
	it.fBloomMovingDecrease = 1.5f;
	it.fReloadTime = 0.95f;
	it.fPulloutTime = 0.7f;
	sprintf(it.szName, "Minigun (Mythic)");
	it.iTexture = 13;
	it.id = 151;

	g_Items.push_back(it);

	////////////////////////////////////////////////////////////////
	//                     Hunting Rifle
	////////////////////////////////////////////////////////////////

	it.fAudibleDistance = 60.f;
	it.iSoundID = 22;
	it.fVolumeMulti = 1.f;

	it.fWeaponWeight = 0.05f;


	//Rare
	it.iType = 2;
	it.bAuto = true;
	it.iRarity = 5;
	it.iDamageStart = 110;
	it.iDamageEnd = 100;
	it.fRange = 110;
	it.fFirerate = 1.5;
	it.iBullets = 1;
	it.iMaxBullets = 1;
	it.iPellets = 1;
	it.iBulletConsumption = 1;
	it.iBulletType = 2;
	it.iReloadMethod = 1;
	it.fBloomMinSize = 0.f;
	it.fBloomMaxSize = 15.f;
	it.fBloomMovingMinSize = 6.f;
	it.fBloomShootIncrease = 8.0f;
	it.fBloomStandingDecrease = 18.f;
	it.fBloomMovingDecrease = 3.4f;
	it.fReloadTime = 1.f;
	it.fPulloutTime = 0.5f;
	it.fProjectileSpeed = 100.f;
	sprintf(it.szName, "Hunting Rifle (Mythic)");
	it.iTexture = 22;
	it.id = 510;
	g_Items.push_back(it);

	////////////////////////////////////////////////////////////////
	//                         ARA1 & SFR-12
	////////////////////////////////////////////////////////////////

	it.fAudibleDistance = 50.f;
	it.iSoundID = 24;
	it.fVolumeMulti = 1.f;

	it.fWeaponWeight = 0.025f;

	//Mythic
	it.ListIndex = 28;
	it.iType = 0;
	it.bAuto = true;
	it.iRarity = 5;
	it.iDamageStart = 37;
	it.iDamageEnd = 25;
	it.fRange = 100;
	it.fFirerate = 6.75;
	it.iBullets = 30;
	it.iBulletConsumption = 1;
	it.iMaxBullets = 30;
	it.iBulletType = 2;
	it.fBloomMinSize = 0.f;
	it.fBloomMaxSize = 7.f;
	it.fBloomMovingMinSize = 6.2f;
	it.fBloomShootIncrease = 1.225f;
	it.fBloomStandingDecrease = 7.5f;
	it.fBloomMovingDecrease = 2.2f;
	it.fReloadTime = 1.925f;
	it.fPulloutTime = 0.525f;
	sprintf(it.szName, "SFR-12 (Mythic)");
	it.iTexture = 12;
	it.id = 201;

	g_Items.push_back(it);

	add_to_lootpool(91,1);
	add_to_lootpool(92, 1);
	add_to_lootpool(93, 1);
	add_to_lootpool(94, 1);
	add_to_lootpool(95, 1);

	//TODO: Upgrade toolkit
	//TODO: Impulse grenade
	//TODO: Shockwave grenade
	//TODO: Launch grenade
	//TODO: Enemy marker


	//it.Setup(4, true, 100, 100, 2500, 1000, 25000, 1, true, 25, 1, 0.1, 0.3, 14, "Bratatat", 160);
	//g_Items.push_back(it);
	//add_to_lootpool(28, 1000);
	//it.Setup(0, true, 28, 15, 100, 30, 3, 1, true, 6.f, 0.4f, 0.45f, 0.5f, 13, "DR Burst (Epic)", 151);
	//g_Items.push_back(it);
	//add_to_lootpool(28, 300);


	it.fAudibleDistance = 60.f;
	it.iSoundID = 22;
	it.fVolumeMulti = 1.f;

	/*
	Weapons:

	Rocket 
	Grenade L
	Hand Grenade

	*/

	


	//Epic
	it.iType = 1;
	it.bAuto = true;
	it.iRarity = 4;
	it.iDamageStart = 50;
	it.iDamageEnd = 20;
	it.fRange = 100;
	it.fFirerate = 55;
	it.iBullets = 50;
	it.iMaxBullets = 50;
	it.iPellets = 20;
	it.iBulletConsumption = 1;
	it.iBulletType = 2;
	it.iReloadMethod = 1;
	it.fBloomMinSize = 9.f;
	it.fBloomMaxSize = 14.5f;
	it.fBloomMovingMinSize = 11.f;
	it.fBloomShootIncrease = 5.f;
	it.fBloomStandingDecrease = 4.0f;
	it.fBloomMovingDecrease = 1.f;
	it.fReloadTime = 1.8f;
	it.fPulloutTime = 0.5f;
	sprintf(it.szName, "Fuckton");
	it.iTexture = 15;
	it.id = 200;
	//g_Items.push_back(it);


	for (int i = 0; i < g_Items.size(); i++)
	{
		g_Items[i].ListIndex = i;
	}
	ConLog("\nItemList Size: %d", lootpool.size());

}

dc_item::dc_item(int ListIndex, sf::Vector2f pos)
{
	*this = g_Items[ListIndex];
	//for (int p = 0; p < sizeof(dc_item); p++)
	//{
	//	*(((char*)this) + p) = *(((char*)&g_Items[ListIndex]) + p);
	//}
}