#include "CEntity.h"


int loaded_anims = 0;
animdata_t g_Animations[10000];

void IAnim::SetupAnim(char* filename, int FullSizeX, int FullSizeY, int tilesizex, int tilesizey, float length)
{

	g_Animations[loaded_anims].m_iFrames = FullSizeX / tilesizex;
	g_Animations[loaded_anims].m_iStages = FullSizeY / tilesizey;
	g_Animations[loaded_anims].m_flLength = length;
	g_Animations[loaded_anims].m_iWidth = FullSizeX;
	g_Animations[loaded_anims].m_iHeight = FullSizeY;
	//g_Animations[loaded_anims].m_Animation.m_pImg = new sf::Sprite;



	auto file = g_Files.GetFileByName(filename);






	sprintf(g_Animations[loaded_anims].name, "%s", filename);

	sf::Sprite spr;

	g_Animations[loaded_anims].m_Animation.m_Texture.loadFromMemory(file.loc_in_mem, file.size);
	spr.setTexture(g_Animations[loaded_anims].m_Animation.m_Texture);
	//spr.setTextureRect(sf::IntRect(0,0,tilesizex,tilesizey));
	

	g_Animations[loaded_anims].m_Animation.m_pImg.setTexture(g_Animations[loaded_anims].m_Animation.m_Texture);
	//g_Window->draw(*g_Animations[0].m_Animation.m_pImg);
	loaded_anims++;

}


void animstate_t::UpdateFrame(int stage, int frame)
{
	//g_Window->draw(*g_Animations[0].m_Animation.m_pImg);


	int ID = 0;
	switch (m_iCurrentAct)
	{
	case ATTACK: ID = m_idAttack; break;
	case INACTIVE: ID = m_idInactive; break;
	case MINING: ID = m_idMining; break;
	case BUILDING: ID = m_idBuilding; break;
	case MOVING: ID = m_idMoving; break;
	}
	int tilesizex, tilesizey;
	tilesizex = g_Animations[ID].m_iWidth / g_Animations[ID].m_iFrames;
	tilesizey = g_Animations[ID].m_iHeight / g_Animations[ID].m_iStages;


	static auto time = std::chrono::high_resolution_clock::now();
	auto now = std::chrono::high_resolution_clock::now();
	auto count = std::chrono::duration_cast<std::chrono::milliseconds>(now - time).count();
	time = now;




	m_flStateTime += (float)(count) / 1000;
	if (m_flStateTime >= g_Animations[ID].m_flLength)m_flStateTime -= g_Animations[ID].m_flLength;
	auto f = (int)(m_flStateTime * g_Animations[ID].m_iFrames / g_Animations[ID].m_flLength);
	printf("Frame: %d\n", f);


	g_Animations[ID].m_Animation.m_pImg.setTextureRect(sf::IntRect(f*tilesizex,0*tilesizey,tilesizex,tilesizey));
}

void CEntity::Render()
{
	m_AnimState.UpdateFrame(0, 0);
	int ID = 0;
	switch (m_AnimState.m_iCurrentAct)
	{
	case ATTACK: ID = m_AnimState.m_idAttack; break;
	case INACTIVE: ID = m_AnimState.m_idInactive; break;
	case MINING: ID = m_AnimState.m_idMining; break;
	case BUILDING: ID = m_AnimState.m_idBuilding; break;
	case MOVING: ID = m_AnimState.m_idMoving; break;
	}

	//g_Animations[ID].m_Animation.m_pImg.setOrigin(m_vecAbsPosition.x, m_vecAbsPosition.y);
	g_Animations[ID].m_Animation.m_pImg.setPosition(m_vecAbsPosition.x, m_vecAbsPosition.y);



	g_Animations[ID].m_Animation.m_pImg.setRotation(m_flDirection);
	g_Animations[ID].m_Animation.m_pImg.setOrigin(g_Animations[ID].m_iWidth / g_Animations[ID].m_iFrames / 2,
	g_Animations[ID].m_iHeight / g_Animations[ID].m_iStages / 2);
	//g_Animations[ID].m_Animation.m_pImg.setOrigin(m_vecAbsPosition.x, m_vecAbsPosition.y);
	g_Window->draw(g_Animations[ID].m_Animation.m_pImg);
	//IWindow::AddToRenderList(*g_Animations[ID].m_Animation.m_pImg);
}