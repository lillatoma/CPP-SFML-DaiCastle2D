#pragma once
#include "includes.h"
#include "Vector.h"

struct IAnim
{
	void SetupAnim(char* filename, int FullSizeX, int FullSizeY, int tilesizex, int tilesizey, float length);
};



struct entityinfo_t
{
	int m_iMaxHealth;
	int m_iDamage;
	int m_iRange;
	int m_iSpeed;
	int m_iArmor;
	float m_flRatioToStoneBuildings;
	float m_flRatioToWoodenBuildings;
	float m_flRatioToHumans;
	float m_flArmorPierce;
};

struct animation_t
{
	sf::Texture m_Texture;
	sf::Sprite m_pImg;
};

struct animdata_t
{
	char name[32] = "(invalid name)";
	animation_t m_Animation;
	int m_iWidth;
	int m_iHeight;
	int m_iFrames;
	int m_iStages;
	float m_flLength;
};



enum AnimStates
{
	INACTIVE,
	MOVING,
	ATTACK,
	MINING,
	BUILDING
};
struct animstate_t
{


	int m_idInactive;
	int m_idMoving;
	int m_idAttack;
	int m_idMining;
	int m_idBuilding;
	float m_flStateTime;
	int m_iCurrentAct;

	void UpdateFrame(int stage, int frame);



};


class CEntity
{
public:
	Vector m_vecAbsPosition;
	entityinfo_t m_EntInfo;
	animstate_t m_AnimState;
	int m_iHealth;
	float m_flCurrentSpeed = 0.f;
	float m_flDirection = 0.f;
	char m_bActiveResourceType;
	float m_flResource;












	void Render();


};

extern animdata_t g_Animations[10000];
