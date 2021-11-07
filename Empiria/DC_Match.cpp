#include "DaiCastle.h"
#include "ThreadManager.h"

void dc_match::DrawSpectatorInfo()
{
	char NumBuffer[16]; sprintf(NumBuffer, "#%d", players[0].Stats.iPlacement);

	auto NumDim = _Window::GetTextSize(NumBuffer, g_Resolution.y*0.08f);

	char youplaced[16] = "You placed";
	auto youDim = _Window::GetTextSize(youplaced, g_Resolution.y*0.03f);

	_Window::RenderTextB(0.5f*(g_Resolution.x - NumDim.x-youDim.x)-g_Resolution.x*0.005, g_Resolution.y*0.01f+1.f*(NumDim.y-youDim.y), youplaced, g_Resolution.y*0.03f, 255, 255, 255, 255);
	
	for(int i = -1; i <= 1;i++)
		for(int j = -1; j <= 1;j++)
			_Window::RenderTextB(0.5f*(g_Resolution.x - NumDim.x+youDim.x)+2*i, g_Resolution.y*0.01f+2*i, NumBuffer, g_Resolution.y*0.08f, 0, 0, 0, 255);

	_Window::RenderTextB(0.5f*(g_Resolution.x - NumDim.x+youDim.x), g_Resolution.y*0.01f, NumBuffer, g_Resolution.y*0.08f, 225, 180, 32, 255);

	char spectating[16] = "Spectating ";
	char playBuf[128];
	char fullBuf[144];
	sprintf(playBuf, "%s\0", players[camera_follows].szName);
	sprintf(fullBuf, "%s%s", spectating, playBuf);
	auto specdim = _Window::GetTextSize(spectating, g_Resolution.y*0.03f);
	auto fulldim = _Window::GetTextSize(fullBuf, g_Resolution.y*0.03f);

	_Window::RenderTextB(0.5f*g_Resolution.x - 0.5f*fulldim.x, g_Resolution.y*0.80f, spectating, g_Resolution.y*0.03f, 255, 255, 255, 255);

	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
			_Window::RenderTextB(0.5f*g_Resolution.x - 0.5f*fulldim.x + specdim.x+i, g_Resolution.y*0.80f+i, playBuf, g_Resolution.y*0.03f, 0,0,0, 255);

	_Window::RenderTextB(0.5f*g_Resolution.x - 0.5f*fulldim.x+specdim.x, g_Resolution.y*0.80f, playBuf, g_Resolution.y*0.03f, 225,180,32, 255);
}




void dc_match::DrawAirDrop(sf::Vector2f V )
{
	static sf::Sprite chspr;
	static bool brun = false;
	if (!brun)
	{
		brun = true;
		chspr.setTexture(*g_Textures.get(67));
		chspr.setOrigin(32, 32);
	}
	

	sf::Vector2f blocksize((float)(g_Resolution.x) / camera_width, (float)(g_Resolution.x) / camera_width);
	float scale = (float)(blocksize.x) / 128;


	for (int i = 0; i < AirDrops.size(); i++)
	{
		auto a = AirDrops[i];

		if (ServerTime - a.ClockBegin < AIRDROP_VISIBLETIME)
		{
			chspr.setColor(sf::Color(255, 255, 255));
			chspr.setScale(scale, scale);
			chspr.setTextureRect(sf::IntRect(64, 0, 64, 64));

			float _x = V.x - a.vPosition.x;
			float _y = V.y - a.vPosition.y;
			chspr.setPosition(g_Resolution.x / 2 - _x*blocksize.x, g_Resolution.y / 2 - _y*blocksize.y);

			sf::BlendMode additiveBlending = sf::BlendAdd;
			g_Window->draw(chspr, additiveBlending);
		}
		else if (ServerTime - a.ClockBegin  < AIRDROP_FALLINGTIME)
		{
			chspr.setColor(sf::Color(255, 255, 255));
			chspr.setScale(scale, scale);
			chspr.setTextureRect(sf::IntRect(64, 0, 64, 64));

			float _x = V.x - a.vPosition.x;
			float _y = V.y - a.vPosition.y;
			chspr.setPosition(g_Resolution.x / 2 - _x*blocksize.x, g_Resolution.y / 2 - _y*blocksize.y);

			sf::BlendMode additiveBlending = sf::BlendAdd;
			g_Window->draw(chspr, additiveBlending);



			auto df = ServerTime-a.ClockBegin;
			float arriveTimeRange = AIRDROP_FALLINGTIME - AIRDROP_VISIBLETIME;
			float perc = ((AIRDROP_VISIBLETIME - df) / arriveTimeRange);
			float fScale = perc * 2 * scale + 3 * scale;

			int alpha = 0 -perc * 255;

			chspr.setScale(fScale, fScale);
			chspr.setColor(sf::Color(255, 255, 255, alpha));
			chspr.setTextureRect(sf::IntRect(0, 0, 64, 64));
			g_Window->draw(chspr);
		}
		else
		{
			chspr.setColor(sf::Color(255, 255, 255));
			chspr.setScale(scale, scale);
			chspr.setTextureRect(sf::IntRect(0, 0, 64, 64));

			float _x = V.x - a.vPosition.x;
			float _y = V.y - a.vPosition.y;
			chspr.setPosition(g_Resolution.x / 2 - _x*blocksize.x, g_Resolution.y / 2 - _y*blocksize.y);

			sf::BlendMode additiveBlending = sf::BlendAdd;
			g_Window->draw(chspr);
		}
	}
}


void dc_match::DrawAirDrop(sf::RenderTexture* T,sf::Vector2f V)
{
	static sf::Sprite chspr;
	static bool brun = false;
	if (!brun)
	{
		brun = true;
		chspr.setTexture(*g_Textures.get(67));
		chspr.setOrigin(32, 32);
	}


	sf::Vector2f blocksize((float)(g_Resolution.x) / camera_width, (float)(g_Resolution.x) / camera_width);
	float scale = (float)(blocksize.x) / 128;


	for (int i = 0; i < AirDrops.size(); i++)
	{
		auto a = AirDrops[i];

		if (ServerTime - a.ClockBegin < AIRDROP_VISIBLETIME)
		{
			chspr.setColor(sf::Color(255, 255, 255));
			chspr.setScale(scale, scale);
			chspr.setTextureRect(sf::IntRect(64, 0, 64, 64));

			float _x = V.x - a.vPosition.x;
			float _y = V.y - a.vPosition.y;
			chspr.setPosition(g_Resolution.x / 2 - _x*blocksize.x, g_Resolution.y / 2 - _y*blocksize.y);

			sf::BlendMode additiveBlending = sf::BlendAdd;
			T->draw(chspr, additiveBlending);
		}
		else if (ServerTime - a.ClockBegin  < AIRDROP_FALLINGTIME)
		{
			chspr.setColor(sf::Color(255, 255, 255));
			chspr.setScale(scale, scale);
			chspr.setTextureRect(sf::IntRect(64, 0, 64, 64));

			float _x = V.x - a.vPosition.x;
			float _y = V.y - a.vPosition.y;
			chspr.setPosition(g_Resolution.x / 2 - _x*blocksize.x, g_Resolution.y / 2 - _y*blocksize.y);

			sf::BlendMode additiveBlending = sf::BlendAdd;
			T->draw(chspr, additiveBlending);



			auto df = ServerTime - a.ClockBegin;
			float arriveTimeRange = AIRDROP_FALLINGTIME - AIRDROP_VISIBLETIME;
			float perc = ((AIRDROP_VISIBLETIME - df) / arriveTimeRange);
			float fScale = perc * 2 * scale + 3 * scale;

			int alpha = 0 - perc * 255;

			chspr.setScale(fScale, fScale);
			chspr.setColor(sf::Color(255, 255, 255, alpha));
			chspr.setTextureRect(sf::IntRect(0, 0, 64, 64));
			T->draw(chspr);
		}
		else
		{
			chspr.setColor(sf::Color(255, 255, 255));
			chspr.setScale(scale, scale);
			chspr.setTextureRect(sf::IntRect(0, 0, 64, 64));

			float _x = V.x - a.vPosition.x;
			float _y = V.y - a.vPosition.y;
			chspr.setPosition(g_Resolution.x / 2 - _x*blocksize.x, g_Resolution.y / 2 - _y*blocksize.y);

			sf::BlendMode additiveBlending = sf::BlendAdd;
			T->draw(chspr);
		}
	}
}

void dc_match::DrawMap(sf::Vector2f V)
{
	//auto V = players[camera_follows].vPosition;
	//map.draw(players[camera_follows].vPosition.x, players[camera_follows].vPosition.y, camera_width);
	map.draw(V.x, V.y, camera_width);
	DrawAirDrop(V);
}

void dc_match::DrawPlayerIndicator(sf::Vector2f V)
{
	sf::Vector2f blocksize((float)(g_Resolution.x) / camera_width, (float)(g_Resolution.x) / camera_width);

	auto vCamera = V;
	static sf::Sprite spr;
	float scale = blocksize.x / 128;
	spr.setScale(scale, scale);
	spr.setTexture(*g_Textures.get(3));
	spr.setOrigin(32, 32);


	float tx = g_Resolution.x / 2 + (players[camera_follows].vPosition.x - vCamera.x)*blocksize.x;
	//tx += blocksize.x / 4;
	float ty = g_Resolution.y / 2 + (players[camera_follows].vPosition.y - vCamera.y)*blocksize.y;

	static dc_clock Clock;
	static bool ShouldDrawCircle = false;

	auto d = Clock.deltaTime();

	float radius = blocksize.x * d / 2000;
	float outlineradius = blocksize.x *d / 10000;
	float outlinealpha = max(0,255.f - 128.f*d / 1000);




	if (d > 2000)
	{
		Clock.Update();

		if (camera_width < 25.f)ShouldDrawCircle = false;
		else ShouldDrawCircle = true;
	}
	if (ShouldDrawCircle)
	{
		sf::CircleShape C;
		C.setRadius(radius);
		C.setOutlineThickness(outlineradius);
		C.setFillColor(sf::Color::Transparent);
		C.setOutlineColor(sf::Color(0, 0, 0, outlinealpha));
		C.setPosition(sf::Vector2f(tx, ty) - sf::Vector2f(radius, radius));
		g_Window->draw(C);
	}

	if (!players[camera_follows].bOnBus && players[camera_follows].fFreeFallHeight > 0.f)
	{
		float IndicatorHeight = 0.5*blocksize.x;
		float IndicatedHeight = 0.5*blocksize.x*players[camera_follows].fFreeFallHeight * 0.01f;

		_Window::RenderOverlay(tx + IndicatorHeight, ty -IndicatorHeight, 6, IndicatorHeight*2, 0, 0, 0, 255);
		_Window::RenderOverlay(tx + IndicatorHeight, ty + IndicatorHeight-IndicatedHeight*2, 4, IndicatedHeight*2, 255, 0, 0, 255);
	}
}

void dc_match::DrawPlayers(sf::Vector2f V)
{

	sf::Vector2f blocksize((float)(g_Resolution.x) / camera_width, (float)(g_Resolution.x) / camera_width);

	//auto vCamera = players[camera_follows].vPosition;
	auto vCamera = V;
	static sf::Sprite spr;
	float scale = blocksize.x / 128;

	static sf::Sprite sprwep;
	sprwep.setTexture(*g_Textures.get(53));
	sprwep.setOrigin(48, 48);
	sprwep.setScale(scale, scale);
	spr.setScale(scale,scale);
	spr.setTexture(*g_Textures.get(3));
	spr.setOrigin(32, 32);

	if(players[camera_follows].iHealth > 0)
	DrawPlayerIndicator(V);

	for (int i = 0; i < 100; i++)
	{
		if (players[i].iHealth <= 0)continue;
		if (players[i].bOnBus)continue;
		
		float tx = g_Resolution.x/2 + (players[i].vPosition.x - vCamera.x)*blocksize.x;
		//tx += blocksize.x / 4;
		float ty = g_Resolution.y/2 + (players[i].vPosition.y - vCamera.y)*blocksize.y;
		//ty += blocksize.y / 4;
		spr.setPosition(tx+0*scale, ty+0*scale);

		spr.setRotation(-players[i].fAngle+90);
		spr.setTextureRect(sf::IntRect(64+players[i].iSkinTexture*64, 0, 64, 64));




		//Shadow
		if (!players[i].bOnBus && players[i].fFreeFallHeight > 0.f)
		{
			sf::CircleShape crc;
			crc.setRadius(32);
			crc.setOrigin(32, 32);
			float alph = 32.f + (100.f - players[i].fFreeFallHeight)*0.16f;
			float scl = scale*(1.f + players[i].fFreeFallHeight*0.02f);
			float angl = map.get_shadow_angle();
			float anglscl = map.get_shadow_length();
			float angdist = anglscl*(players[i].fFreeFallHeight * 0.02f);



			auto shadowpush = angle2vec(angl)*angdist;
			float tx2 = g_Resolution.x / 2 + (players[i].vPosition.x + shadowpush.x - vCamera.x)*blocksize.x;
			//tx += blocksize.x / 4;
			float ty2 = g_Resolution.y / 2 + (players[i].vPosition.y + shadowpush.y - vCamera.y)*blocksize.y;

			crc.setPosition(tx2, ty2);
			crc.setFillColor(sf::Color(0, 0, 0, alph));
			crc.setScale(scl, scl);

			g_Window->draw(crc);


		}

		if (players[i].GetCurrentWeapon().bValidated)
		{
			sprwep.setTextureRect(sf::IntRect(96 * players[i].GetCurrentWeapon().iTexture, 96*players[i].iWeaponWrapTexture, 64, 64));
			sprwep.setRotation(-players[i].fAngle + 90);
			sprwep.setPosition(tx + 0 * scale, ty + 0 * scale);
			_Window::AddToRenderList(sprwep);
		}

		_Window::AddToRenderList(spr);

		spr.setTextureRect(sf::IntRect(0, 0, 64, 64));
		_Window::AddToRenderList(spr);

		//Glider
		if (!players[i].bOnBus && players[i].fFreeFallHeight > 0.f)
		{

			static sf::Sprite gliderSpr;
			gliderSpr.setTexture(*g_Textures.get(68));
			gliderSpr.setOrigin(64, 64);
			gliderSpr.setPosition(tx + 0 * scale, ty + 0 * scale);
			gliderSpr.setTextureRect(sf::IntRect(players[i].iGliderTexture * 128, 0, 128, 128));
			gliderSpr.setScale(scale, scale);
			gliderSpr.setRotation(-players[i].fAngle + 90);
			g_Window->draw(gliderSpr);
		}

	}

}

void dc_match::DrawPlayers(sf::RenderTexture* T,sf::Vector2f V)
{

	sf::Vector2f blocksize((float)(g_Resolution.x) / camera_width, (float)(g_Resolution.x) / camera_width);

	//auto vCamera = players[camera_follows].vPosition;
	auto vCamera = V;
	static sf::Sprite spr;
	float scale = blocksize.x / 128;

	static sf::Sprite sprwep;
	sprwep.setTexture(*g_Textures.get(53));
	sprwep.setOrigin(48, 48);
	sprwep.setScale(scale, scale);
	spr.setScale(scale, scale);
	spr.setTexture(*g_Textures.get(3));
	spr.setOrigin(32, 32);

	for (int i = 0; i < 100; i++)
	{
		if (players[i].iHealth <= 0)continue;
		if (players[i].bOnBus)continue;

		float tx = g_Resolution.x / 2 + (players[i].vPosition.x - vCamera.x)*blocksize.x;
		//tx += blocksize.x / 4;
		float ty = g_Resolution.y / 2 + (players[i].vPosition.y - vCamera.y)*blocksize.y;
		//ty += blocksize.y / 4;
		spr.setPosition(tx + 0 * scale, ty + 0 * scale);

		spr.setRotation(-players[i].fAngle + 90);
		spr.setTextureRect(sf::IntRect(64 + players[i].iSkinTexture * 64, 0, 64, 64));




		//Shadow
		if (!players[i].bOnBus && players[i].fFreeFallHeight > 0.f)
		{
			sf::CircleShape crc;
			crc.setRadius(32);
			crc.setOrigin(32, 32);
			float alph = 32.f + (100.f - players[i].fFreeFallHeight)*0.16f;
			float scl = scale*(1.f + players[i].fFreeFallHeight*0.02f);
			float angl = map.get_shadow_angle();
			float anglscl = map.get_shadow_length();
			float angdist = anglscl*(players[i].fFreeFallHeight * 0.02f);



			auto shadowpush = angle2vec(angl)*angdist;
			float tx2 = g_Resolution.x / 2 + (players[i].vPosition.x + shadowpush.x - vCamera.x)*blocksize.x;
			//tx += blocksize.x / 4;
			float ty2 = g_Resolution.y / 2 + (players[i].vPosition.y + shadowpush.y - vCamera.y)*blocksize.y;

			crc.setPosition(tx2, ty2);
			crc.setFillColor(sf::Color(0, 0, 0, alph));
			crc.setScale(scl, scl);

			T->draw(crc);


		}

		if (players[i].GetCurrentWeapon().bValidated)
		{
			sprwep.setTextureRect(sf::IntRect(96 * players[i].GetCurrentWeapon().iTexture, 96 * players[i].iWeaponWrapTexture, 64, 64));
			sprwep.setRotation(-players[i].fAngle + 90);
			sprwep.setPosition(tx + 0 * scale, ty + 0 * scale);
			T->draw(sprwep);
		}

		T->draw(spr);

		spr.setTextureRect(sf::IntRect(0, 0, 64, 64));
		T->draw(spr);

		//Glider
		if (!players[i].bOnBus && players[i].fFreeFallHeight > 0.f)
		{

			static sf::Sprite gliderSpr;
			gliderSpr.setTexture(*g_Textures.get(68));
			gliderSpr.setOrigin(64, 64);
			gliderSpr.setPosition(tx + 0 * scale, ty + 0 * scale);
			gliderSpr.setTextureRect(sf::IntRect(players[i].iGliderTexture * 128, 0, 128, 128));
			gliderSpr.setScale(scale, scale);
			gliderSpr.setRotation(-players[i].fAngle + 90);
			T->draw(gliderSpr);
		}

	}

}

struct li_t
{
	sf::Vector2f start, end;
	li_t()
	{}

	li_t(sf::Vector2f s, sf::Vector2f e)
	{
		start = s;
		end = e;
	}
};

inline float GetT1(sf::Vector2f rs, sf::Vector2f rd, sf::Vector2f ws, sf::Vector2f wd)
{
	if ((wd.y*rd.x - wd.x*rd.y) == 0)return -1;
	return (wd.x*(rs.y - ws.y) - wd.y*(rs.x - ws.x)) / (wd.y*rd.x - wd.x*rd.y);
}

inline float GetT2(sf::Vector2f rs, sf::Vector2f rd, sf::Vector2f ws, sf::Vector2f wd)
{
	if ((rd.y*wd.x - rd.x*wd.y) == 0)return -1;
	return (rd.x*(ws.y - rs.y) - rd.y*(ws.x - rs.x)) / (rd.y*wd.x - rd.x*wd.y);
}

void dc_match::GenerateBusRoute()
{
	float Direction = 0.1f*Random(0, 3600);
	float Push = 0.1f*Random(-1000, 1000);

	auto AngleVector = angle2vec(Direction);
	auto NormalVector = angle2vec(Direction + 90.f);

	sf::Vector2f p_a = sf::Vector2f(500, 500) - AngleVector * 800.f + NormalVector*Push;
	sf::Vector2f p_b = sf::Vector2f(500, 500) + AngleVector * 800.f + NormalVector*Push;



	auto BusMid = sf::Vector2f(500, 500) + NormalVector*Push;
	float Forward = 10000.f;
	float Backward = -10000.f;

	if (AngleVector.x != 0)
	{
		float leftie = (100 - BusMid.x) / AngleVector.x;
		float rightie = (900 - BusMid.x) / AngleVector.x;

		if (leftie > 0 && Forward > leftie)Forward = leftie;
		if (leftie < 0 && Backward < leftie)Backward = leftie;

		if (rightie > 0 && Forward > rightie)Forward = rightie;
		if (rightie < 0 && Backward < rightie)Backward = rightie;
	}
	if (AngleVector.y != 0)
	{
		float upie = (100 - BusMid.y) / AngleVector.y;
		float downie = (900 - BusMid.y) / AngleVector.y;

		if (upie > 0 && Forward > upie)Forward = upie;
		if (upie < 0 && Backward < upie)Backward = upie;

		if (downie > 0 && Forward > downie)Forward = downie;
		if (downie < 0 && Backward < downie)Backward = downie;
	}

	BusStartPosition = BusMid + Backward * AngleVector;
	BusEndPosition = BusMid + Forward * AngleVector;
	BusCurrentPosition = BusStartPosition - 200.f * AngleVector;


	//ConLog("===============\nDirection: %.2f\nAngleVector: %.2f %.2f\nPush: %.2f\nPoint A: %.2f %.2f\nPoint B: %.2f %.2f\nBusStartpont: %.2f %.2f\n-JumpStartpont: %.2f %.2f\nEndpont: %.2f %.2f\n==============="
	//	, Direction, AngleVector.x, AngleVector.y, Push, p_a.x,p_a.y,p_b.x,p_b.y , BusCurrentPosition.x, BusCurrentPosition.y,BusStartPosition.x, BusStartPosition.y, BusEndPosition.x, BusEndPosition.y);



	//ConLog("===============\nDirection: %.2f\nAngleVector: %.2f %.2f\nPush: %.2f\nPoint A: %.2f %.2f\nPoint B: %.2f %.2f\nBusStartpont: %.2f %.2f\n-JumpStartpont: %.2f %.2f\nEndpont: %.2f %.2f\n==============="
	//	, Direction, AngleVector.x, AngleVector.y, Push, p_a.x,p_a.y,p_b.x,p_b.y , BusCurrentPosition.x, BusCurrentPosition.y,A.x, A.y, B.x, B.y);


	bBusJumpable = false;
}

void dc_match::DoBusMusic()
{
	MusicLoopSinceLast -= timeDiffSinceLastFrame;


	if (MusicLoopSinceLast <= 0.f)
	{
		float timepush = abs(MusicLoopSinceLast);
		if(g_Framerate > 0)
		MusicLoopSinceLast += 8.73;
		g_Sounds.AddNewDynamicSound(787772, 38, BUS_AUDIBLEDISTANCE, BusCurrentPosition, g_Config.mastervolume.Value*100.f, players[camera_follows].vPosition,timepush,0.1f);
	}
	g_Sounds.SetDynamicSound(787772, g_Config.mastervolume.Value*100.f, BusCurrentPosition, players[camera_follows].vPosition);
}

void dc_match::SimulateBus()
{
	if (!bBusMoving)return;

	DoBusMusic();
	
	float TimeDiff = timeDiffSinceLastFrame;

	if (TimeDiff > 1.f)TimeDiff = 0.f;
	auto bus_unit = ToUnitVector(BusEndPosition - BusStartPosition);

	BusCurrentPosition = BusCurrentPosition+(TimeDiff*BUS_TRAVELSPEED)*bus_unit;


	if (ServerTime > 200.f / BUS_TRAVELSPEED)bBusJumpable = true;

	
	if (GetDistance(BusStartPosition, BusCurrentPosition) >= GetDistance(BusStartPosition, BusEndPosition))
	{

		for (int i = 0; i < 100; i++)
		{
			if (players[i].bOnBus)
			{
				players[i].vPosition = BusEndPosition;
				PlayerJumpOffBus(i);
			}
		}
		if (GetDistance(BusStartPosition, BusCurrentPosition) - GetDistance(BusStartPosition, BusEndPosition) >= 200)bBusMoving = false;
		bBusJumpable = false;
	}
	else
	{
		for (int i = 0; i < 100; i++)
		{
			if (players[i].bOnBus)
			{
				players[i].vPosition = BusCurrentPosition;
			}
		}
	}


}

void dc_match::PlayerKill(int player)
{
	if (players[player].iHealth <= 0)
	{
		players[player].Stats.iPlacement = GetAlivePlayers() + 1;
		for (int i = 0; i < 5; i++)
			PlayerDropWeapon(player, i);
	}
	dc_deatheffect dF;
	dF.clockBegin = ServerTime;
	dF.position = players[player].vPosition;
	dF.fRotation = players[player].fAngle;
	dF.iTexture = players[player].iSkinTexture;
	effects.dth_effects.push_back(dF);

}

void dc_match::PlayerRewardForKill(int player)
{
	int healpossible = max(0, 100 - players[player].iHealth);
	int shieldpossible = max(0, 100 - players[player].iShield);

	int HealAmount = PlayerHealReward;

	if (healpossible >= HealAmount)players[player].iHealth += HealAmount;
	else {
		players[player].iHealth += healpossible;
		HealAmount -= healpossible;

		if (shieldpossible >= HealAmount)players[player].iShield += HealAmount;
		else players[player].iShield += shieldpossible;
	}
}


void dc_match::PlayerDropWeapon(int player, int weaponslot)
{
	if (players[player].Items[weaponslot].bValidated)
	{
		map.items.push_back(players[player].Items[weaponslot]);
		auto newpos = players[player].vPosition + sf::Vector2f(RandFloat() - 0.5f, RandFloat() - 0.5f);


		Demo_SnapshotUpdateItemDrop(players[player].Items[weaponslot].GameIdx, newpos);
		map.items[map.items.size() - 1].vPosition = newpos;

		//For removing the item
		players[player].Items[weaponslot].bValidated = false;

		if (players[player].iSelectedWeapon == weaponslot)
			players[player].fReloadDelay = 0.f;

	}
}

void dc_match::PlayerSwapWeaponInventory(int player, int slotFrom, int slotTo)
{
	if (slotFrom == slotTo)return;
	//This is for checking if two consumables are getting swapped
	//If the slot we swap to is not full with a consumable type, then we can add some from slotFrom
	else if (players[player].Items[slotFrom].bValidated 
		&& players[player].Items[slotTo].bValidated 
		&& players[player].Items[slotFrom].IsConsumable() 
		&& players[player].Items[slotTo].IsConsumable() 
		&& players[player].Items[slotTo].iBullets < players[player].Items[slotTo].iMaxBullets 
		&& players[player].Items[slotTo].id == players[player].Items[slotFrom].id)
	{
		auto addpossible = players[player].Items[slotTo].iMaxBullets - players[player].Items[slotTo].iBullets;
		//Checking if slotFrom is supposed to be empty after the swap
		if (addpossible >= players[player].Items[slotFrom].iBullets)
		{
			players[player].Items[slotTo].iBullets += players[player].Items[slotFrom].iBullets;
			players[player].Items[slotFrom].iBullets = 0;
			players[player].Items[slotFrom].bValidated = false;
			//Swapping the selected weapon
			if (players[player].iSelectedWeapon == slotFrom)players[player].iSelectedWeapon = slotTo;
		}
		else
		{
			players[player].Items[slotTo].iBullets += addpossible;
			players[player].Items[slotFrom].iBullets -= addpossible;
		}
	}
	else
	{
		//Triangle copy method
		auto A = players[player].Items[slotFrom];
		players[player].Items[slotFrom] = players[player].Items[slotTo];
		players[player].Items[slotTo] = A;
		//Swapping the selected weapon
		if (players[player].iSelectedWeapon == slotFrom)players[player].iSelectedWeapon = slotTo;
		else if (players[player].iSelectedWeapon == slotTo)players[player].iSelectedWeapon = slotFrom;
	}
}

void dc_match::PlayerSwapWeapon(int player, int weaponslot)
{
	if (weaponslot < 0 || weaponslot > 4)return;
	if (players[player].iSelectedWeapon == weaponslot || !players[player].Items[weaponslot].bValidated)return;
	players[player].iSelectedWeapon = weaponslot;

	if (players[player].Items[weaponslot].iType >= 4)players[player].fPulloutDelay = 0.f;
	else players[player].fPulloutDelay = players[player].Items[weaponslot].fPulloutTime;
	players[player].fReloadDelay = 0.f;
	players[player].fShootDelay = 0.f;
	players[player].fHealTime = 0.f;
}

void dc_match::PlayerReloadWeapon(int player)
{
	if (players[player].fFreeFallHeight > 0.f)return;
	if (players[player].Items[players[player].iSelectedWeapon].bValidated 
		&& !players[player].Items[players[player].iSelectedWeapon].IsConsumable() 
		&& players[player].Items[players[player].iSelectedWeapon].iBullets < players[player].Items[players[player].iSelectedWeapon].iMaxBullets 
		&& players[player].fReloadDelay <= 0.f)
	{
		players[player].fReloadDelay = players[player].Items[players[player].iSelectedWeapon].fReloadTime;
	}
}

void dc_match::PlayerUseHeal(int player)
{
	//players[player].Items[players[player].iSelectedWeapon].iBullets--;
	//if (players[player].Items[players[player].iSelectedWeapon].iBullets <= 0)players[player].Items[players[player].iSelectedWeapon].bValidated = false;
	int i = player;
	int healtype = players[i].Items[players[i].iSelectedWeapon].iType - 4;
	int healamount = players[i].Items[players[i].iSelectedWeapon].iHealAmount;
	int healmax = players[i].Items[players[i].iSelectedWeapon].iHealMax;

	if (healtype == 0 && players[i].iHealth >= healmax)return;
	else if (healtype == 1 && players[i].iShield >= healmax)return;
	else if (healtype == 2 && players[i].iShield >= 100 && players[i].iHealth >= 100)return;

	players[player].fHealTime = players[player].Items[players[player].iSelectedWeapon].fHealTime;
	AddGunShotSound(players[player].GetCurrentWeapon().ListIndex, players[player].vPosition);
}

damageinfo_t dc_match::SimulateBullet(int player)
{
	auto bloomangle = 0.f;
	bloomangle = (RandFloat() - 0.5f)*players[player].fBloomSize;
	auto angle = players[player].fAngle + bloomangle;
	sf::Vector2f anglevector(cos(angle*PI / 180), -sin(angle*PI / 180));
	anglevector *= players[player].Items[players[player].iSelectedWeapon].fRange;

	//Getting the ray tracing data of map objects
	auto trace = map.trace_ray(players[player].vPosition, players[player].vPosition + anglevector);

	dc_tracedata playertrace;

	dc_shoteffect sf;
	sf.clockBegin = ServerTime;
	sf.start = trace.start;

	//Here if the ray hit a wall
	//We check if there is a player inbetween
	if (trace.hit_object)
	{
		playertrace = TracePlayers(players[player].vPosition, trace.end, player);

		if (playertrace.hit_target)
		{
			damageinfo_t dmg_info;
			dmg_info.iType = 0;
			dmg_info.iShooter = player;
			auto dist = GetDistance(playertrace.start, playertrace.end);
			auto dmg = players[player].Items[players[player].iSelectedWeapon].iDamageEnd - (players[player].Items[players[player].iSelectedWeapon].iDamageEnd - players[player].Items[players[player].iSelectedWeapon].iDamageStart)*((players[player].Items[players[player].iSelectedWeapon].fRange - dist) / players[player].Items[players[player].iSelectedWeapon].fRange);

			dmg_info.iDamage = dmg;
			dmg_info.iVictim = playertrace.targetid;

			sf.end = playertrace.end;

			effects.sht_effects.push_back(sf);
			Demo_SnapshotUpdateWeaponShot(sf.start, sf.end, sf.clockBegin);
			dmg_info.mapCoord = sf.end;
			
			return dmg_info;
		}
		else
		{
			damageinfo_t dmg_info;
			dmg_info.iType = 1;
			dmg_info.iShooter = player;

			auto dist = GetDistance(trace.start, trace.end);
			auto dmg = players[player].Items[players[player].iSelectedWeapon].iDamageEnd - (players[player].Items[players[player].iSelectedWeapon].iDamageEnd - players[player].Items[players[player].iSelectedWeapon].iDamageStart)*((players[player].Items[players[player].iSelectedWeapon].fRange - dist) / players[player].Items[players[player].iSelectedWeapon].fRange);
			
			dmg_info.iDamage = dmg;
			dmg_info.vWallCoords = sf::Vector2i(trace.object.x, trace.object.y);
			dmg_info.iWalltype = trace.type;
			sf.end = trace.end;
			effects.sht_effects.push_back(sf);
			Demo_SnapshotUpdateWeaponShot(sf.start, sf.end, sf.clockBegin);
			dmg_info.mapCoord = sf.end;
			return dmg_info;
		}





	}
	else
	{
		playertrace = TracePlayers(players[player].vPosition, trace.end, player);
		if (playertrace.hit_target)
		{
			damageinfo_t dmg_info;
			dmg_info.iType = 0;
			dmg_info.iShooter = player;
			auto dist = GetDistance(playertrace.start, playertrace.end);
			auto dmg = players[player].Items[players[player].iSelectedWeapon].iDamageEnd - (players[player].Items[players[player].iSelectedWeapon].iDamageEnd - players[player].Items[players[player].iSelectedWeapon].iDamageStart)*((players[player].Items[players[player].iSelectedWeapon].fRange - dist) / players[player].Items[players[player].iSelectedWeapon].fRange);
			dmg_info.iVictim = playertrace.targetid;
			dmg_info.iDamage = dmg;
			sf.end = playertrace.end;
			effects.sht_effects.push_back(sf);
			Demo_SnapshotUpdateWeaponShot(sf.start, sf.end, sf.clockBegin);
			dmg_info.mapCoord = sf.end;
			return dmg_info;
		}
		else
		{
			sf.end = trace.end;
			effects.sht_effects.push_back(sf);
			Demo_SnapshotUpdateWeaponShot(sf.start, sf.end, sf.clockBegin);
			damageinfo_t dmg_null;
			dmg_null.is_null = true;
			return dmg_null;
		}
	

	}
}


void dc_match::SimulateProjectiles(float timediff, sf::Vector2f V)
{


	for (int i = Projectiles.size() - 1; i >= 0; i--)
	{
		auto& Pr = Projectiles[i];
		bool should_delete = false;
		sf::Vector2f DirVector = ToUnitVector(Pr.end - Pr.start);
		sf::Vector2f CurrentPosition = Pr.start + DirVector*Pr.timeAlive*Pr.projectile_speed;
		sf::Vector2f NextPosition = Pr.start + DirVector*(Pr.timeAlive + timediff)*Pr.projectile_speed;

		if (GetDistance(NextPosition, Pr.start) > GetDistance(Pr.end, Pr.start))NextPosition = Pr.end;

		Pr.timeAlive += timediff;

		//DAMAGEPART
		{
			auto trace = map.trace_ray(CurrentPosition, NextPosition);
			dc_tracedata playertrace;
			int player = Pr.originid;
			if (trace.hit_object)
			{
				should_delete = true;
				playertrace = TracePlayers(CurrentPosition, NextPosition, Pr.originid);

				if (playertrace.hit_target)
				{
					players[player].Stats.iShotsTaken++;
					auto dmg = Pr.DamageEnd*GetDistance(Pr.start, NextPosition) + (GetDistance(Pr.end, NextPosition))*Pr.DamageStart;
					dmg /= GetDistance(Pr.start, Pr.end);

					players[player].Stats.iDamageDealt += dmg;
					players[playertrace.targetid].Stats.iDamageTaken += dmg;

					players[playertrace.targetid].gothitLastClock.Update();
					players[playertrace.targetid].gotHitLastItemID = Pr.wpnListIndex;
					players[playertrace.targetid].gotHitLastPlayerID = player;

					bool has_shleld = players[playertrace.targetid].iShield > 0;
					players[playertrace.targetid].Damage(dmg);
					if (has_shleld != (players[playertrace.targetid].iShield > 0))
					{
						dc_shieldbreakeffect SBR;
						SBR.clockBegin = ServerTime;
						SBR.position = players[playertrace.targetid].vPosition;
						effects.shb_effects.push_back(SBR);
					}
					if (player == camera_follows || playertrace.targetid == camera_follows)
					{
						dc_damageeffect ef;
						ef.clockBegin = ServerTime;
						ef.damage = dmg;
						ef.position = playertrace.end;
						if (has_shleld)ef.color = sf::Color(48, 192, 255, 255);
						else ef.color = sf::Color(233, 211, 199, 255);
						effects.dmg_effects.push_back(ef);


					}
					if (players[playertrace.targetid].iHealth <= 0)
					{
						dc_elimdata Elim;
						Elim.shooterPos = players[player].vPosition;
						Elim.targetPos = players[playertrace.targetid].vPosition;
						Elim.WeaponListindex = Pr.wpnListIndex;
						players[player].Stats.Elims.push_back(Elim);

						PlayerRewardForKill(player);
						players[player].Stats.iEliminations++;
						PlayerKill(playertrace.targetid);
						Demo_SnapshotUpdateElimination(player, playertrace.targetid);
						if (camera_follows == playertrace.targetid)camera_follows = player;

						dc_killnoticeeffect kl;
						kl.clockBegin = ServerTime;
						float dst = GetDistance(players[player].vPosition, players[playertrace.targetid].vPosition);
						sprintf(kl.message, "%s eliminated %s with %s (%.1fm)", players[player].szName, players[playertrace.targetid].szName, g_Items[Pr.wpnListIndex].szName, dst);
						kl.Killer = player;
						kl.Target = playertrace.targetid;
						if (camera_follows == playertrace.targetid)camera_follows = player;
						effects.kilnot_effects.push_back(kl);
					}
				}
				else
				{
					g_Sounds.AddNewSound(37, 10.f, trace.end, g_Config.mastervolume.Value*100.f, players[camera_follows].vPosition, 0.6f);
					auto dmg = Pr.DamageEnd*GetDistance(Pr.start, NextPosition) + (GetDistance(Pr.end, NextPosition))*Pr.DamageStart;
					dmg /= GetDistance(Pr.start, Pr.end);
					map.lines[trace.object.y].blocks[trace.object.x].walls[trace.type].iHealth -= 1.f*dmg;
					if (map.lines[trace.object.y].blocks[trace.object.x].walls[trace.type].iHealth < 0)
					{
						Demo_SnapshotUpdateWallbreak(trace.object, trace.type);
						p_bShouldUpdatelines = true;
						if (trace.type == 0)
							map.delete_line(sf::Vector2f(trace.object.x, trace.object.y), sf::Vector2f(trace.object.x, trace.object.y + 1), trace.type);
						else
							map.delete_line(sf::Vector2f(trace.object.x, trace.object.y), sf::Vector2f(trace.object.x + 1, trace.object.y), trace.type);
					}

					if (player == camera_follows)
					{
						dc_damageeffect ef;
						ef.clockBegin = ServerTime;
						ef.damage = dmg;
						ef.position = trace.end;
						effects.dmg_effects.push_back(ef);
					}
				}
			}
			else
			{
				playertrace = TracePlayers(CurrentPosition, NextPosition, Pr.originid);
				if (playertrace.hit_target)
				{
					players[player].Stats.iShotsTaken++;


					should_delete = true;
					auto dist = GetDistance(playertrace.start, playertrace.end);
					auto dmg = Pr.DamageEnd*GetDistance(Pr.start, NextPosition) + (GetDistance(Pr.end, NextPosition))*Pr.DamageStart;
					dmg /= GetDistance(Pr.start, Pr.end);

					players[player].Stats.iDamageDealt += dmg;
					players[playertrace.targetid].Stats.iDamageTaken += dmg;
					players[playertrace.targetid].gothitLastClock.Update();
					players[playertrace.targetid].gotHitLastItemID = Pr.wpnListIndex;
					players[playertrace.targetid].gotHitLastPlayerID = player;


					bool has_shleld = players[playertrace.targetid].iShield > 0;
					players[playertrace.targetid].Damage(dmg);
					if (has_shleld != (players[playertrace.targetid].iShield > 0))
					{
						dc_shieldbreakeffect SBR;
						SBR.clockBegin = ServerTime;
						SBR.position = players[playertrace.targetid].vPosition;
						effects.shb_effects.push_back(SBR);
					}
					if (player == camera_follows || playertrace.targetid == camera_follows)
					{
						dc_damageeffect ef;
						ef.clockBegin = ServerTime;
						ef.damage = dmg;
						ef.position = playertrace.end;
						if (has_shleld)ef.color = sf::Color(48, 192, 255, 255);
						else ef.color = sf::Color(233, 211, 199, 255);
						effects.dmg_effects.push_back(ef);

					}
					if (players[playertrace.targetid].iHealth <= 0)
					{
						dc_elimdata Elim;
						Elim.shooterPos = players[player].vPosition;
						Elim.targetPos = players[playertrace.targetid].vPosition;
						Elim.WeaponListindex = Pr.wpnListIndex;
						players[player].Stats.Elims.push_back(Elim);

						PlayerRewardForKill(player);
						players[player].Stats.iEliminations++;
						PlayerKill(playertrace.targetid);
						Demo_SnapshotUpdateElimination(player, playertrace.targetid);
						dc_killnoticeeffect kl;
						kl.clockBegin = ServerTime;
						kl.Killer = player;
						kl.Target = playertrace.targetid;
						if (camera_follows == playertrace.targetid)camera_follows = player;

						float dst = GetDistance(players[player].vPosition, players[playertrace.targetid].vPosition);
						sprintf(kl.message, "%s eliminated %s with %s (%.1fm)", players[player].szName, players[playertrace.targetid].szName,g_Items[Pr.wpnListIndex].szName, dst);
						effects.kilnot_effects.push_back(kl);
					}
				}
			}

			if(NextPosition == Pr.end)should_delete = true;


			//DELETE
			if (should_delete) {
				Demo_SnapshotProjectileEnd(Projectiles[i].ProjectileIndex);
				Projectiles.erase(Projectiles.begin() + i);
			}
		}


	}

	DrawProjectiles(V);
}

void dc_match::DrawProjectiles(sf::Vector2f V)
{
	for (int i = Projectiles.size() - 1; i >= 0; i--)
	{
		auto& Pr = Projectiles[i];
		bool should_delete = false;
		sf::Vector2f DirVector = ToUnitVector(Pr.end - Pr.start);
		sf::Vector2f CurrentPosition = Pr.start + DirVector*Pr.timeAlive*Pr.projectile_speed;
		sf::Vector2f NextPosition = Pr.start + DirVector*(Pr.timeAlive + 1.f/60)*Pr.projectile_speed;


			//DRAW
			float projdrawlength = 0.03f*Pr.projectile_speed;

			sf::RectangleShape Rect;

			auto A = 0.5f*(CurrentPosition + NextPosition) - 0.5f*DirVector*projdrawlength;
			auto B = 0.5f*(CurrentPosition + NextPosition) + 0.5f*DirVector*projdrawlength;
			auto p = dc_map::world_to_screen(V.x, V.y, camera_width, A.x, A.y);
			auto p2 = dc_map::world_to_screen(V.x, V.y, camera_width, B.x, B.y);
			auto _X_ = GetDistance(p, p2);
			auto _Y_ = 50.f / camera_width;

			auto ScrPos = 0.5f*(p + p2);
			Rect.setFillColor(sf::Color(255, 192, 64));
			Rect.setSize(sf::Vector2f(_X_, _Y_));
			Rect.setOrigin(_X_ / 2, _Y_ / 2);
			Rect.setRotation(vec2angle(DirVector.x, DirVector.y));
			Rect.setPosition(ScrPos);

			g_Window->draw(Rect);


	}
}

void dc_match::DrawProjectiles(sf::RenderTexture* T,sf::Vector2f V)
{
	for (int i = Projectiles.size() - 1; i >= 0; i--)
	{
		auto& Pr = Projectiles[i];
		bool should_delete = false;
		sf::Vector2f DirVector = ToUnitVector(Pr.end - Pr.start);
		sf::Vector2f CurrentPosition = Pr.start + DirVector*Pr.timeAlive*Pr.projectile_speed;
		sf::Vector2f NextPosition = Pr.start + DirVector*(Pr.timeAlive + 1.f / 60)*Pr.projectile_speed;


		//DRAW
		float projdrawlength = 0.03f*Pr.projectile_speed;

		sf::RectangleShape Rect;

		auto A = 0.5f*(CurrentPosition + NextPosition) - 0.5f*DirVector*projdrawlength;
		auto B = 0.5f*(CurrentPosition + NextPosition) + 0.5f*DirVector*projdrawlength;
		auto p = dc_map::world_to_screen(V.x, V.y, camera_width, A.x, A.y);
		auto p2 = dc_map::world_to_screen(V.x, V.y, camera_width, B.x, B.y);
		auto _X_ = GetDistance(p, p2);
		auto _Y_ = 50.f / camera_width;

		auto ScrPos = 0.5f*(p + p2);
		Rect.setFillColor(sf::Color(255, 192, 64));
		Rect.setSize(sf::Vector2f(_X_, _Y_));
		Rect.setOrigin(_X_ / 2, _Y_ / 2);
		Rect.setRotation(vec2angle(DirVector.x, DirVector.y));
		Rect.setPosition(ScrPos);

		T->draw(Rect);


	}
}

sf::Vector2f dc_match::Bounce(sf::Vector2f inDirVector, sf::Vector2f wallA, sf::Vector2f wallB)
{
	float rot = vec2angle(wallB.x - wallA.x, wallB.y - wallA.y);

	float rotatedinAngle = vec2angle(inDirVector.x, inDirVector.y) + rot;
	sf::Vector2f rotatedDirVector = angle2vec(rotatedinAngle);

	if (abs(rotatedDirVector.y) <= 0.001f)return inDirVector;

	if (abs(rotatedDirVector.x) <= 0.001f)return -inDirVector;

	float len = GetDistance(inDirVector, sf::Vector2f());
	sf::Vector2f NewVec(rotatedDirVector.x, -rotatedDirVector.y);
	return angle2vec(vec2angle(NewVec.x, NewVec.y)-rot)*len;

}


damagelist_t dc_match::SimulateExplosion(sf::Vector2f Position, float ExpRange, int DmgMax, int DmgMin)
{
	damagelist_t Return;
	for (float x = 0.f; x <= 360.f; x += 1.f)
	{
		auto trace = map.trace_ray(Position, Position + angle2vec(x)*ExpRange);
		dc_tracedata playertrace;
		dc_shoteffect se;
		se.clockBegin = ServerTime;
		se.start = trace.start;
		se.end = trace.end;
		if (trace.hit_object)
		{
			playertrace = TracePlayers(Position, trace.end, -1);

			if (playertrace.hit_target)
			{
				damageinfo_t dmg_info;
				dmg_info.iType = 0;
				dmg_info.iShooter = -1;
				auto dist = GetDistance(playertrace.start, playertrace.end);
				auto dmg = DmgMin - (DmgMin - DmgMax)*((ExpRange - dist) / ExpRange);

				dmg_info.iDamage = dmg;
				dmg_info.iVictim = playertrace.targetid;
				dmg_info.mapCoord = playertrace.end;
				Return.totalDamages.push_back(dmg_info);
				se.end = playertrace.end;
			}
			else
			{
				damageinfo_t dmg_info;
				dmg_info.iType = 1;
				dmg_info.iShooter = -1;

				auto dist = GetDistance(trace.start, trace.end);
				auto dmg = DmgMin - (DmgMin - DmgMax)*((ExpRange - dist) / ExpRange);

				dmg_info.iDamage = dmg;
				dmg_info.vWallCoords = sf::Vector2i(trace.object.x, trace.object.y);
				dmg_info.iWalltype = trace.type;
				dmg_info.mapCoord = trace.end;
				Return.totalDamages.push_back(dmg_info);
				se.end = trace.end;
			}
		}
		else
		{
			playertrace = TracePlayers(Position, trace.end, -1);
			if (playertrace.hit_target)
			{
				damageinfo_t dmg_info;
				dmg_info.iType = 0;
				dmg_info.iShooter = -1;
				auto dist = GetDistance(playertrace.start, playertrace.end);
				auto dmg = DmgMin - (DmgMin - DmgMax)*((ExpRange - dist) / ExpRange);

				dmg_info.iDamage = dmg;
				dmg_info.iVictim = playertrace.targetid;
				dmg_info.mapCoord = playertrace.end;
				Return.totalDamages.push_back(dmg_info);
				se.end = playertrace.end;
			}
		}
		Demo_SnapshotUpdateWeaponShot(se.start, se.end, se.clockBegin);
		effects.sht_effects.push_back(se);


	}

	Return.compress();

	for (auto &Info : Return.totalDamages)
	{
		Info.iDamage /= Info.mapCoordWeight;
	}

	

	return Return;
}

#define BOUNCESPEEDRATIO 0.5f
#define BOUNCETIMELOSE 0.2f

void dc_match::SimulateExplosives(float timediff, sf::Vector2f V)
{
	static sf::Sprite spr;
	spr.setTexture(*g_Textures.get(52));
	spr.setOrigin(32, 32);


	for (int i = Explosives.size() - 1; i >= 0; i--)
	{
		auto& Exp = Explosives[i];
		bool hit_simulated = false;
		bool should_delete = false;
		sf::Vector2f DirVector = ToUnitVector(Exp.end - Exp.start);
		sf::Vector2f CurrentPosition = Exp.start;
		sf::Vector2f NextPosition = Exp.start + DirVector*(Exp.timeAlive + timediff)*Exp.projectile_speed;
		sf::Vector2f ExpPosition;
		if (GetDistance(NextPosition, Exp.start) > GetDistance(Exp.end, Exp.start))NextPosition = Exp.end;

		Exp.timeAlive += timediff;
		if (Exp.timeAlive >= 0.25f)Exp.originid = -1;

		if (Exp.projectiletype > 0)
		{
			Exp.projectile_speed *= exp(-timediff / 2.f);
			Exp.projectile_speed -= 0.5f*timediff;
			Exp.projectile_speed = max(0, Exp.projectile_speed);

		}
		Exp.timeMax -= Exp.timeAlive;
		Exp.timeAlive = 0.f;
		Exp.start = NextPosition;

		int player = Exp.userid;
		//TRACEPART
		{
			auto trace = map.trace_ray(CurrentPosition, NextPosition);
			dc_tracedata playertrace;

			if (trace.hit_object)
			{
				hit_simulated = true;
				if (Exp.projectiletype == 0)
					should_delete = true;
				playertrace = TracePlayers(CurrentPosition, trace.end, Exp.originid);

				if (playertrace.hit_target)
				{
					ExpPosition = playertrace.end;
					if (Exp.projectiletype > 0)
					{
						float totaldist = GetDistance(CurrentPosition, NextPosition);
						float bouncedist = GetDistance(CurrentPosition, ExpPosition);
						sf::Vector2f B;
						if (DirVector.x > DirVector.y)
							B = Bounce(DirVector, sf::Vector2f(0, 0), sf::Vector2f(0, 1));
						else
							B = Bounce(DirVector, sf::Vector2f(0, 0), sf::Vector2f(1, 0));

						sf::Vector2f New = playertrace.end + B * (totaldist - bouncedist);

						Exp.end = (GetDistance(Exp.end, CurrentPosition)-GetDistance(CurrentPosition,NextPosition))*B + playertrace.end;
						Exp.start = New;
						Exp.timeMax -= (Exp.timeAlive + timediff + BOUNCETIMELOSE);
						Exp.timeAlive = 0.f;
						Exp.projectile_speed *= BOUNCESPEEDRATIO;
					}
				}
				else
				{
					ExpPosition = trace.end;
					if (Exp.projectiletype > 0)
					{
						float totaldist = GetDistance(CurrentPosition, NextPosition);
						float bouncedist = GetDistance(CurrentPosition, ExpPosition);

						sf::Vector2f B;
						if (trace.type == 0)
							B = Bounce(DirVector, sf::Vector2f(0, 0), sf::Vector2f(0, 1));
						else
							B = Bounce(DirVector, sf::Vector2f(0, 0), sf::Vector2f(1, 0));

						sf::Vector2f New = playertrace.end + B * (totaldist - bouncedist);

						Exp.end = (GetDistance(Exp.end, CurrentPosition) - GetDistance(CurrentPosition, NextPosition))*B + playertrace.end;
						Exp.start = New;
						Exp.timeMax -= (Exp.timeAlive + timediff + BOUNCETIMELOSE);
						Exp.timeAlive = 0.f;
						Exp.projectile_speed *= BOUNCESPEEDRATIO;
					}
				}
			}
			else
			{
				playertrace = TracePlayers(CurrentPosition, NextPosition, Exp.originid);
				if (playertrace.hit_target)
				{
					hit_simulated = true;
					if (Exp.projectiletype == 0)should_delete = true;
					ExpPosition = playertrace.end;
					if (Exp.projectiletype > 0)
					{
						float totaldist = GetDistance(CurrentPosition, NextPosition);
						float bouncedist = GetDistance(CurrentPosition, ExpPosition);
						sf::Vector2f B;
						if (DirVector.x > DirVector.y)
							B = Bounce(DirVector, sf::Vector2f(0, 0), sf::Vector2f(0, 1));
						else
							B = Bounce(DirVector, sf::Vector2f(0, 0), sf::Vector2f(1, 0));

						sf::Vector2f New = playertrace.end + B * (totaldist - bouncedist);

						Exp.end = (GetDistance(Exp.end, CurrentPosition) - GetDistance(CurrentPosition, NextPosition))*B + playertrace.end;
						Exp.start = New;
						Exp.timeMax -= (Exp.timeAlive + timediff + BOUNCETIMELOSE);
						Exp.timeAlive = 0.f;
						Exp.projectile_speed *= BOUNCESPEEDRATIO;
					}

				}
				else ExpPosition = NextPosition;
			}
		}
		{
			ExpPosition -= ToUnitVector(ExpPosition - CurrentPosition)*0.05f;
			if (NextPosition == Exp.end)should_delete = true;
			if (Exp.timeAlive >= Exp.timeMax)should_delete = true;
			if (Exp.projectile_speed == 0.f)ExpPosition = Exp.start;
			//if (Exp.projectile_speed < 1.f)should_delete = true;

			if (should_delete)
			{
				auto Expsim = SimulateExplosion(ExpPosition, Exp.explosionRange, Exp.DamageStart, Exp.DamageEnd);
				g_Sounds.AddNewSound(36, 60.f, ExpPosition, g_Config.mastervolume.Value*100.f, players[camera_follows].vPosition, 0.5f);
				Expsim.compress();

				for (auto data : Expsim.totalDamages)
				{
					if (data.iType == 0)
					{
						int iVictimShield = players[data.iVictim].iShield;
						players[data.iVictim].Damage(data.iDamage);


						players[player].Stats.iDamageDealt += data.iDamage;
						players[data.iVictim].Stats.iDamageTaken += data.iDamage;
						if (player != data.iVictim)
						{
							players[data.iVictim].gothitLastClock.Update();
							players[data.iVictim].gotHitLastPlayerID = player;
							players[data.iVictim].gotHitLastItemID = Exp.wpnListIndex;
						}




						//Damage Effect
							dc_damageeffect ef;
							ef.clockBegin = ServerTime;
							ef.damage = data.iDamage;
							ef.position = data.mapCoord / (float)(data.mapCoordWeight);
							if (iVictimShield > 0)ef.color = sf::Color(48, 192, 255, 255);
							else ef.color = sf::Color(233, 211, 199, 255);
							effects.dmg_effects.push_back(ef);
						//Shield Break Effect
						if (iVictimShield > 0 && players[data.iVictim].iShield == 0)
						{
							dc_shieldbreakeffect SBR;
							SBR.clockBegin = ServerTime;
							SBR.position = players[data.iVictim].vPosition;
							effects.shb_effects.push_back(SBR);
						}

						//Kill Notice
						if (players[data.iVictim].iHealth <= 0)
						{
							dc_elimdata Elim;
							Elim.shooterPos = players[player].vPosition;
							Elim.targetPos = players[data.iVictim].vPosition;
							Elim.WeaponListindex = Exp.wpnListIndex;
							players[player].Stats.Elims.push_back(Elim);

							players[Exp.userid].Stats.iEliminations++;
							PlayerRewardForKill(Exp.userid);
							Demo_SnapshotUpdateElimination(player, data.iVictim);
							PlayerKill(data.iVictim);
							dc_killnoticeeffect kl;
							kl.clockBegin = ServerTime;
							kl.Killer = Exp.userid;
							kl.Target = data.iVictim;

							if (camera_follows == data.iVictim)camera_follows = Exp.userid;
							float dst = GetDistance(players[Exp.userid].vPosition, players[data.iVictim].vPosition);

							if (Exp.userid != data.iVictim)
								sprintf(kl.message, "%s eliminated %s with %s (%.1fm)", players[Exp.userid].szName, players[data.iVictim].szName, g_Items[Exp.wpnListIndex].szName, dst);
							else if (players[data.iVictim].gothitLastClock.deltaTime() < 1000.f*KILL_OWNERTIME && Exp.userid == data.iVictim)
							{
								sprintf(kl.message, "%s eliminated %s with %s (%.1fm)", players[players[data.iVictim].gotHitLastPlayerID].szName, players[data.iVictim].szName, g_Items[Exp.wpnListIndex].szName, dst);
								players[Exp.userid].Stats.iEliminations--;
								players[players[data.iVictim].gotHitLastPlayerID].Stats.iEliminations++;
								kl.Killer = players[data.iVictim].gotHitLastPlayerID;
								if (camera_follows == data.iVictim)camera_follows = kl.Killer;
							}
							
							else {
								sprintf(kl.message, "%s eliminated themselves", players[Exp.userid].szName, data.iVictim, dst);
								players[Exp.userid].Stats.iEliminations--;
							}
							effects.kilnot_effects.push_back(kl);

						}


					}
					else if (data.iType == 1)
					{
						map.lines[data.vWallCoords.y].blocks[data.vWallCoords.x].walls[data.iWalltype].iHealth -= 2*data.iDamage;

						if (map.lines[data.vWallCoords.y].blocks[data.vWallCoords.x].walls[data.iWalltype].iHealth < 0)
						{
							p_bShouldUpdatelines = true;
							Demo_SnapshotUpdateWallbreak(data.vWallCoords, data.iWalltype);
							if (data.iWalltype == 0)
								map.delete_line(sf::Vector2f(data.vWallCoords.x, data.vWallCoords.y), sf::Vector2f(data.vWallCoords.x, data.vWallCoords.y + 1), data.iWalltype);
							else
								map.delete_line(sf::Vector2f(data.vWallCoords.x, data.vWallCoords.y), sf::Vector2f(data.vWallCoords.x + 1, data.vWallCoords.y), data.iWalltype);
						}

						if (player == camera_follows)
						{
							dc_damageeffect ef;
							ef.clockBegin = ServerTime;
							ef.damage = data.iDamage;
							ef.position = data.mapCoord / (float)data.mapCoordWeight;
							effects.dmg_effects.push_back(ef);
						}
					}
				}

				//TODO: Explosion effect add


			}

			//DELETE
			if (should_delete)
			{
				Demo_SnapshotUpdateExplosiveRemove(Explosives[i].ExplosiveIndex);
				Explosives.erase(Explosives.begin() + i);

			}
		}


	}

	DrawExplosives(V);
	/**/
}

void dc_match::DrawExplosives(sf::Vector2f V)
{
	static sf::Sprite spr;
	spr.setTexture(*g_Textures.get(52));
	spr.setOrigin(32, 32);


	for (int i = Explosives.size() - 1; i >= 0; i--)
	{
		auto& Exp = Explosives[i];
		bool hit_simulated = false;
		bool should_delete = false;
		sf::Vector2f DirVector = ToUnitVector(Exp.end - Exp.start);
		sf::Vector2f CurrentPosition = Exp.start;
		sf::Vector2f NextPosition = Exp.start + DirVector*(Exp.timeAlive + 1.f/60.f)*Exp.projectile_speed;
		{



			//DRAW

			spr.setTextureRect(sf::IntRect(64 * Exp.projectiletype, 0, 64, 64));

			auto A1 = Exp.start + DirVector*Exp.timeAlive*Exp.projectile_speed;
			auto p1 = dc_map::world_to_screen(V.x, V.y, camera_width, A1.x, A1.y);
			spr.setPosition(p1);
			auto d = Exp.end - Exp.start;
			spr.setRotation(vec2angle(d.x, d.y));
			auto scale = 0.5f*(g_Resolution.x / 1280.f)*(10.f / camera_width);
			spr.setScale(scale, scale);



			float projdrawlength = 0.03f*Exp.projectile_speed;

			sf::RectangleShape Rect;


			auto A = 0.5f*(CurrentPosition + NextPosition) - 0.5f*DirVector*projdrawlength;
			auto B = 0.5f*(CurrentPosition + NextPosition) + 0.5f*DirVector*projdrawlength;
			auto p = dc_map::world_to_screen(V.x, V.y, camera_width, A.x, A.y);
			auto p2 = dc_map::world_to_screen(V.x, V.y, camera_width, B.x, B.y);
			auto _X_ = GetDistance(p, p2);
			auto _Y_ = 50.f / camera_width;

			auto ScrPos = 0.5f*(p + p2);
			Rect.setFillColor(sf::Color(255, 192, 64, 64));
			Rect.setSize(sf::Vector2f(_X_, _Y_));
			Rect.setOrigin(_X_ / 2, _Y_ / 2);
			Rect.setRotation(vec2angle(DirVector.x, DirVector.y));
			Rect.setPosition(ScrPos);


			g_Window->draw(Rect);
			g_Window->draw(spr);


		}


	}
	/**/
}

void dc_match::DrawExplosives(sf::RenderTexture* T,sf::Vector2f V)
{
	static sf::Sprite spr;
	spr.setTexture(*g_Textures.get(52));
	spr.setOrigin(32, 32);


	for (int i = Explosives.size() - 1; i >= 0; i--)
	{
		auto& Exp = Explosives[i];
		bool hit_simulated = false;
		bool should_delete = false;
		sf::Vector2f DirVector = ToUnitVector(Exp.end - Exp.start);
		sf::Vector2f CurrentPosition = Exp.start;
		sf::Vector2f NextPosition = Exp.start + DirVector*(Exp.timeAlive + 1.f / 60.f)*Exp.projectile_speed;
		{



			//DRAW

			spr.setTextureRect(sf::IntRect(64 * Exp.projectiletype, 0, 64, 64));

			auto A1 = Exp.start + DirVector*Exp.timeAlive*Exp.projectile_speed;
			auto p1 = dc_map::world_to_screen(V.x, V.y, camera_width, A1.x, A1.y);
			spr.setPosition(p1);
			auto d = Exp.end - Exp.start;
			spr.setRotation(vec2angle(d.x, d.y));
			auto scale = 0.5f*(g_Resolution.x / 1280.f)*(10.f / camera_width);
			spr.setScale(scale, scale);



			float projdrawlength = 0.03f*Exp.projectile_speed;

			sf::RectangleShape Rect;


			auto A = 0.5f*(CurrentPosition + NextPosition) - 0.5f*DirVector*projdrawlength;
			auto B = 0.5f*(CurrentPosition + NextPosition) + 0.5f*DirVector*projdrawlength;
			auto p = dc_map::world_to_screen(V.x, V.y, camera_width, A.x, A.y);
			auto p2 = dc_map::world_to_screen(V.x, V.y, camera_width, B.x, B.y);
			auto _X_ = GetDistance(p, p2);
			auto _Y_ = 50.f / camera_width;

			auto ScrPos = 0.5f*(p + p2);
			Rect.setFillColor(sf::Color(255, 192, 64, 64));
			Rect.setSize(sf::Vector2f(_X_, _Y_));
			Rect.setOrigin(_X_ / 2, _Y_ / 2);
			Rect.setRotation(vec2angle(DirVector.x, DirVector.y));
			Rect.setPosition(ScrPos);


			T->draw(Rect);
			T->draw(spr);


		}


	}
	/**/
}

void dc_match::PlayerShootWeapon3(int player)
{
	auto bloomangle = 0.f;
	bloomangle = (RandFloat() - 0.5f)*players[player].fBloomSize;


	auto angle = players[player].fAngle + bloomangle;
	sf::Vector2f anglevector(cos(angle*PI / 180), -sin(angle*PI / 180));
	anglevector *= players[player].Items[players[player].iSelectedWeapon].fRange;

	dc_explosive Exp;
	


	Exp.DamageStart = players[player].Items[players[player].iSelectedWeapon].iDamageStart;
	Exp.DamageEnd = players[player].Items[players[player].iSelectedWeapon].iDamageEnd;
	Exp.start = players[player].vPosition;
	Exp.end = Exp.start + anglevector;
	Exp.originid = player;
	Exp.userid = player;
	Exp.projectile_speed = 0.01f*Random(100*players[player].Items[players[player].iSelectedWeapon].fProjectileSpeed, 100 * players[player].Items[players[player].iSelectedWeapon].fProjectileSpeedMax);
	Exp.timeAlive = 0.f;
	Exp.explosionRange = players[player].Items[players[player].iSelectedWeapon].fExplosionRange;
	Exp.projectiletype = players[player].Items[players[player].iSelectedWeapon].iExplosiveType;
	Exp.timeMax = players[player].Items[players[player].iSelectedWeapon].fExplosiveLifetime;
	Exp.wpnListIndex = players[player].GetCurrentWeapon().ListIndex;
	//sprintf(Exp.wpnName, players[player].Items[players[player].iSelectedWeapon].szName);
	Exp.ExplosiveIndex = TotalExplosives;
	Demo_SnapshotUpdateExplosiveAdd(Exp.projectiletype);
	
	Explosives.push_back(Exp);
	TotalExplosives++;
	players[player].fBloomSize += players[player].GetCurrentWeapon().fBloomShootIncrease;
	players[player].GetCurrentWeapon().iBullets -= players[player].GetCurrentWeapon().iBulletConsumption;
	players[player].fShootDelay = 1.0f / players[player].Items[players[player].iSelectedWeapon].fFirerate + players[player].fShootDelay;

	AddGunShotSound(players[player].GetCurrentWeapon().ListIndex, players[player].vPosition);
}

void dc_match::PlayerShootWeapon2(int player)
{
	players[player].Stats.iShotsTaken++;
	auto bloomangle = 0.f;
	bloomangle = (RandFloat() - 0.5f)*players[player].fBloomSize;


	auto angle = players[player].fAngle + bloomangle;
	sf::Vector2f anglevector(cos(angle*PI / 180), -sin(angle*PI / 180));
	anglevector *= players[player].Items[players[player].iSelectedWeapon].fRange;

	dc_projectile Pr;
	Pr.DamageStart = players[player].Items[players[player].iSelectedWeapon].iDamageStart;
	Pr.DamageEnd = players[player].Items[players[player].iSelectedWeapon].iDamageEnd;
	Pr.start = players[player].vPosition;
	Pr.end = Pr.start + anglevector;
	Pr.originid = player;
	Pr.projectile_speed = players[player].Items[players[player].iSelectedWeapon].fProjectileSpeed;
	Pr.timeAlive = 0.f;
	Pr.wpnListIndex = players[player].GetCurrentWeapon().ListIndex;
	Pr.ProjectileIndex = TotalProjectiles;
	//sprintf(Pr.wpnName, players[player].Items[players[player].iSelectedWeapon].szName);
	Demo_SnapshotUpdateProjectileAdd(Pr.start, angle, Pr.projectile_speed);
	Projectiles.push_back(Pr);
	TotalProjectiles++;

	players[player].fBloomSize += players[player].GetCurrentWeapon().fBloomShootIncrease;
	players[player].GetCurrentWeapon().iBullets -= players[player].GetCurrentWeapon().iBulletConsumption;
	players[player].fShootDelay = 1.0f / players[player].Items[players[player].iSelectedWeapon].fFirerate + players[player].fShootDelay;

	AddGunShotSound(players[player].GetCurrentWeapon().ListIndex, players[player].vPosition);
}

void dc_match::PlayerShootWeapon0(int player)
{
	while (players[player].fShootDelay <= 0.f && players[player].Items[players[player].iSelectedWeapon].iBullets > 0)
	{
		players[player].Stats.iShotsTaken++;
		AddGunShotSound(players[player].GetCurrentWeapon().ListIndex, players[player].vPosition);
		auto bloomangle = 0.f;
		bloomangle = (RandFloat() - 0.5f)*players[player].fBloomSize;

		players[player].fBloomSize += players[player].Items[players[player].iSelectedWeapon].fBloomShootIncrease;

		auto angle = players[player].fAngle + bloomangle;
		sf::Vector2f anglevector(cos(angle*PI / 180), -sin(angle*PI / 180));
		anglevector *= players[player].Items[players[player].iSelectedWeapon].fRange;


		auto trace = map.trace_ray(players[player].vPosition, players[player].vPosition + anglevector);
		players[player].Items[players[player].iSelectedWeapon].iBullets--;

		players[player].fShootDelay = 1.0f / players[player].Items[players[player].iSelectedWeapon].fFirerate + players[player].fShootDelay;

		dc_tracedata playertrace;


		dc_shoteffect sf;
		sf.clockBegin = ServerTime;
		sf.start = trace.start;
		if (trace.hit_object) //If it hit a wall
		{
			playertrace = TracePlayers(players[player].vPosition, trace.end, player);

			if (playertrace.hit_target) // We still want to check if there is a player closer
			{
				players[player].Stats.iShotsHit++;

				auto dist = GetDistance(playertrace.start, playertrace.end);
				auto dmg = players[player].Items[players[player].iSelectedWeapon].iDamageEnd - (players[player].Items[players[player].iSelectedWeapon].iDamageEnd - players[player].Items[players[player].iSelectedWeapon].iDamageStart)*((players[player].Items[players[player].iSelectedWeapon].fRange - dist) / players[player].Items[players[player].iSelectedWeapon].fRange);


				players[player].Stats.iDamageDealt += dmg;
				players[playertrace.targetid].Stats.iDamageTaken += dmg;

				players[playertrace.targetid].gothitLastClock.Update();
				players[playertrace.targetid].gotHitLastPlayerID = player;
				players[playertrace.targetid].gotHitLastItemID = players[player].GetCurrentWeapon().ListIndex;


				bool has_shleld = players[playertrace.targetid].iShield > 0;
				players[playertrace.targetid].Damage(dmg);
				if (has_shleld != (players[playertrace.targetid].iShield > 0))
				{
					dc_shieldbreakeffect SBR;
					SBR.clockBegin = ServerTime;
					SBR.position = players[playertrace.targetid].vPosition;
					effects.shb_effects.push_back(SBR);
				}
				if (player == camera_follows || playertrace.targetid == camera_follows)
				{
					dc_damageeffect ef;
					ef.clockBegin = ServerTime;
					ef.damage = dmg;
					ef.position = playertrace.end;
					if (has_shleld)ef.color = sf::Color(48, 192, 255, 255);
					else ef.color = sf::Color(233, 211, 199, 255);
					effects.dmg_effects.push_back(ef);


				}
				sf.end = playertrace.end;
				Demo_SnapshotUpdateWeaponShot(sf.start, sf.end, sf.clockBegin);
				effects.sht_effects.push_back(sf);
				if (players[playertrace.targetid].iHealth <= 0)
				{
					players[player].Stats.iEliminations++;
					PlayerRewardForKill(player);
					dc_elimdata Elim;
					Elim.shooterPos = players[player].vPosition;
					Elim.targetPos = players[playertrace.targetid].vPosition;
					Elim.WeaponListindex = players[player].GetCurrentWeapon().ListIndex;
					players[player].Stats.Elims.push_back(Elim);

					Demo_SnapshotUpdateElimination(player, playertrace.targetid);
					PlayerKill(playertrace.targetid);

					if (camera_follows == playertrace.targetid)camera_follows = player;

					dc_killnoticeeffect kl;
					kl.clockBegin = ServerTime;
					float dst = GetDistance(players[player].vPosition, players[playertrace.targetid].vPosition);
					sprintf(kl.message, "%s eliminated %s with %s (%.1fm)", players[player].szName, players[playertrace.targetid].szName, players[player].Items[players[player].iSelectedWeapon].szName, dst);
					kl.Killer = player;
					kl.Target = playertrace.targetid;
					if (camera_follows == playertrace.targetid)camera_follows = player;
					
					effects.kilnot_effects.push_back(kl);
				}
			}
			else
			{
				auto dist = GetDistance(trace.start, trace.end);
				auto dmg = players[player].Items[players[player].iSelectedWeapon].iDamageEnd - (players[player].Items[players[player].iSelectedWeapon].iDamageEnd - players[player].Items[players[player].iSelectedWeapon].iDamageStart)*((players[player].Items[players[player].iSelectedWeapon].fRange - dist) / players[player].Items[players[player].iSelectedWeapon].fRange);
				map.lines[trace.object.y].blocks[trace.object.x].walls[trace.type].iHealth -= 0.5f*dmg;

				g_Sounds.AddNewSound(37, 10.f, trace.end, g_Config.mastervolume.Value*100.f, players[camera_follows].vPosition, 0.6f);


				if (map.lines[trace.object.y].blocks[trace.object.x].walls[trace.type].iHealth < 0)
				{
					Demo_SnapshotUpdateWallbreak(trace.object, trace.type);
					p_bShouldUpdatelines = true;
					if (trace.type == 0)
						map.delete_line(sf::Vector2f(trace.object.x, trace.object.y), sf::Vector2f(trace.object.x, trace.object.y + 1), trace.type);
					else
						map.delete_line(sf::Vector2f(trace.object.x, trace.object.y), sf::Vector2f(trace.object.x + 1, trace.object.y), trace.type);
				}

				if (player == 0)
				{
					dc_damageeffect ef;
					ef.clockBegin = ServerTime;
					ef.damage = dmg;
					ef.position = trace.end;
					effects.dmg_effects.push_back(ef);
				}
				sf.end = trace.end;
				Demo_SnapshotUpdateWeaponShot(sf.start, sf.end, sf.clockBegin);
				effects.sht_effects.push_back(sf);
			}





		}
		else
		{
			playertrace = TracePlayers(players[player].vPosition, trace.end, player);
			if (playertrace.hit_target)
			{
				players[player].Stats.iShotsHit++;
				auto dist = GetDistance(playertrace.start, playertrace.end);
				auto dmg = players[player].Items[players[player].iSelectedWeapon].iDamageEnd - (players[player].Items[players[player].iSelectedWeapon].iDamageEnd - players[player].Items[players[player].iSelectedWeapon].iDamageStart)*((players[player].Items[players[player].iSelectedWeapon].fRange - dist) / players[player].Items[players[player].iSelectedWeapon].fRange);


				players[player].Stats.iDamageDealt += dmg;
				players[playertrace.targetid].Stats.iDamageTaken += dmg;

				players[playertrace.targetid].gothitLastClock.Update();
				players[playertrace.targetid].gotHitLastPlayerID = player;
				players[playertrace.targetid].gotHitLastItemID = players[player].GetCurrentWeapon().ListIndex;

				bool has_shleld = players[playertrace.targetid].iShield > 0;
				players[playertrace.targetid].Damage(dmg);
				if (has_shleld != (players[playertrace.targetid].iShield > 0))
				{
					dc_shieldbreakeffect SBR;
					SBR.clockBegin = ServerTime;
					SBR.position = players[playertrace.targetid].vPosition;
					effects.shb_effects.push_back(SBR);
				}
				if (player == camera_follows || playertrace.targetid == camera_follows)
				{
					dc_damageeffect ef;
					ef.clockBegin = ServerTime;
					ef.damage = dmg;
					ef.position = playertrace.end;
					if (has_shleld)ef.color = sf::Color(48, 192, 255, 255);
					else ef.color = sf::Color(233, 211, 199, 255);
					effects.dmg_effects.push_back(ef);

				}
				sf.end = playertrace.end;
				Demo_SnapshotUpdateWeaponShot(sf.start, sf.end, sf.clockBegin);
				effects.sht_effects.push_back(sf);
				if (players[playertrace.targetid].iHealth <= 0)
				{
					players[player].Stats.iEliminations++;
					PlayerRewardForKill(player);
					dc_elimdata Elim;
					Elim.shooterPos = players[player].vPosition;
					Elim.targetPos = players[playertrace.targetid].vPosition;
					Elim.WeaponListindex = players[player].GetCurrentWeapon().ListIndex;
					players[player].Stats.Elims.push_back(Elim);
					Demo_SnapshotUpdateElimination(player, playertrace.targetid);
					PlayerKill(playertrace.targetid);
					dc_killnoticeeffect kl;
					kl.clockBegin = ServerTime;
					kl.Killer = player;
					kl.Target = playertrace.targetid;
					if (camera_follows == playertrace.targetid)camera_follows = player;

					float dst = GetDistance(players[player].vPosition, players[playertrace.targetid].vPosition);
					sprintf(kl.message, "%s eliminated %s with %s (%.1fm)", players[player].szName, players[playertrace.targetid].szName, players[player].Items[players[player].iSelectedWeapon].szName, dst);
					effects.kilnot_effects.push_back(kl);
				}
			}
			else
			{
				sf.end = trace.end;
				Demo_SnapshotUpdateWeaponShot(sf.start, sf.end, sf.clockBegin);
				effects.sht_effects.push_back(sf);
			}
		}

	}
}

void dc_match::PlayerShootWeapon1(int player)
{
	if (players[player].fShootDelay > 0.f)return;

	while (players[player].fShootDelay <= 0.f && players[player].Items[players[player].iSelectedWeapon].iBullets > 0)
	{
		players[player].Stats.iShotsTaken++;
		AddGunShotSound(players[player].GetCurrentWeapon().ListIndex, players[player].vPosition);
		damagelist_t List;

		for (int i = 0; i < players[player].GetCurrentWeapon().iPellets; i++)
		{
			auto dmginfo = SimulateBullet(player);
			List.totalDamages.push_back(dmginfo);
		}

		List.compress();

		for (auto data : List.totalDamages)
		{
			if (data.iType == 0)
			{
				players[player].Stats.iShotsHit++;
				int iVictimShield = players[data.iVictim].iShield;
				players[data.iVictim].Damage(data.iDamage);


				players[data.iShooter].Stats.iDamageDealt += data.iDamage;
				players[data.iVictim].Stats.iDamageTaken += data.iDamage;

				players[data.iVictim].gothitLastClock.Update();
				players[data.iVictim].gotHitLastPlayerID = data.iShooter;
				players[data.iVictim].gotHitLastItemID = players[data.iShooter].GetCurrentWeapon().ListIndex;

				//Damage Effect
				if (camera_follows == data.iShooter || data.iVictim == camera_follows)
				{
					dc_damageeffect ef;
					ef.clockBegin = ServerTime;
					ef.damage = data.iDamage;
					ef.position = data.mapCoord / (float)(data.mapCoordWeight);
					if (iVictimShield > 0)ef.color = sf::Color(48, 192, 255, 255);
					else ef.color = sf::Color(233, 211, 199, 255);
					effects.dmg_effects.push_back(ef);
				}
				//Shield Break Effect
				if (iVictimShield > 0 && players[data.iVictim].iShield == 0)
				{
					dc_shieldbreakeffect SBR;
					SBR.clockBegin = ServerTime;
					SBR.position = players[data.iVictim].vPosition;
					effects.shb_effects.push_back(SBR);
				}

				//Kill Notice
				if (players[data.iVictim].iHealth <= 0)
				{

					dc_elimdata Elim;
					Elim.shooterPos = players[data.iShooter].vPosition;
					Elim.targetPos = players[data.iVictim].vPosition;
					Elim.WeaponListindex = players[data.iShooter].GetCurrentWeapon().ListIndex;
					players[data.iShooter].Stats.Elims.push_back(Elim);

					players[data.iShooter].Stats.iEliminations++;
					PlayerRewardForKill(data.iShooter);
					PlayerKill(data.iVictim);
					Demo_SnapshotUpdateElimination(data.iShooter, data.iVictim);
					dc_killnoticeeffect kl;
					kl.clockBegin = ServerTime;
					kl.Killer = data.iShooter;
					kl.Target = data.iVictim;
					if (camera_follows == data.iVictim)camera_follows = data.iShooter;
					float dst = GetDistance(players[player].vPosition, players[data.iVictim].vPosition);
					sprintf(kl.message, "%s eliminated %s with %s (%.1fm)", players[player].szName, players[data.iVictim].szName, players[player].Items[players[player].iSelectedWeapon].szName, dst );
					effects.kilnot_effects.push_back(kl);

				}


			}
			else if (data.iType == 1)
			{
				map.lines[data.vWallCoords.y].blocks[data.vWallCoords.x].walls[data.iWalltype].iHealth -= 0.5f*data.iDamage;
				g_Sounds.AddNewSound(37, 10.f, data.mapCoord/((float)data.mapCoordWeight), g_Config.mastervolume.Value*100.f, players[camera_follows].vPosition, 0.6f);
				if (map.lines[data.vWallCoords.y].blocks[data.vWallCoords.x].walls[data.iWalltype].iHealth < 0)
				{
					Demo_SnapshotUpdateWallbreak(data.vWallCoords, data.iWalltype);
					p_bShouldUpdatelines = true;
					if (data.iWalltype == 0)
						map.delete_line(sf::Vector2f(data.vWallCoords.x, data.vWallCoords.y), sf::Vector2f(data.vWallCoords.x, data.vWallCoords.y + 1), data.iWalltype);
					else
						map.delete_line(sf::Vector2f(data.vWallCoords.x, data.vWallCoords.y), sf::Vector2f(data.vWallCoords.x + 1, data.vWallCoords.y),data.iWalltype);
				}

				if (player == camera_follows)
				{
					dc_damageeffect ef;
					ef.clockBegin = ServerTime;
					ef.damage = data.iDamage;
					ef.position = data.mapCoord / (float)data.mapCoordWeight;
					effects.dmg_effects.push_back(ef);
				}
			}
		}

		players[player].fBloomSize += players[player].GetCurrentWeapon().fBloomShootIncrease;
		players[player].GetCurrentWeapon().iBullets -= players[player].GetCurrentWeapon().iBulletConsumption;
		players[player].fShootDelay = 1.0f / players[player].Items[players[player].iSelectedWeapon].fFirerate + players[player].fShootDelay;
	
	
	
	
	}

	








}



void dc_match::PlayerShootWeapon(int player)
{
	if (player < 0 || player >99)return;
	if (players[player].fFreeFallHeight > 0.f)return;
	if (!players[player].Items[players[player].iSelectedWeapon].bValidated 
		|| players[player].Items[players[player].iSelectedWeapon].iBullets <= 0 
		|| players[player].fPulloutDelay > 0.f 
		|| (players[player].fReloadDelay > 0.f && players[player].GetCurrentWeapon().iReloadMethod == 1)//This last one allows the user to shoot a shotgun if the magazine isn't empty while reloading (the reloading cancels)
		|| players[player].fShootDelay > 0.f 
		|| players[player].fHealTime > 0.f)return;

	if (players[player].Items[players[player].iSelectedWeapon].iType > 3 && players[player].fHealTime <= 0)
	{
		if(players[player].CalculateVelocity() <= 2.f)
		PlayerUseHeal(player);
		return;
	}
	if (players[player].GetCurrentWeapon().iType == 0)PlayerShootWeapon0(player);
	if (players[player].GetCurrentWeapon().iType == 1)PlayerShootWeapon1(player);
	if (players[player].GetCurrentWeapon().iType == 2)PlayerShootWeapon2(player);
	if (players[player].GetCurrentWeapon().iType == 3)PlayerShootWeapon3(player);

	players[player].iOpeningChest = -1;
	players[player].iOpeningAirdrop = -1;

	if (players[player].GetCurrentWeapon().IsConsumable() && players[player].GetCurrentWeapon().iBullets == 0)players[player].GetCurrentWeapon().bValidated = false;

	if(players[player].GetCurrentWeapon().iBullets > 0)players[player].fReloadDelay = 0.f;
}

void dc_match::DrawCrosshair(sf::Vector2f V)
{
	if (camera_follows != 0)return;

	//Drawing a circle that represents the size of the bullet spread on a distance
	sf::Vector2i MouseC = sf::Vector2i(g_Mouse.Coords.x, g_Mouse.Coords.y);
	float centdist = GetDistance(sf::Vector2f(MouseC.x, MouseC.y), sf::Vector2f(g_Resolution.x / 2, g_Resolution.y / 2));
	float cradius = centdist * tan(players[0].fBloomSize * PI / 180.0);


	sf::CircleShape c;
	c.setRadius(cradius + 2.f);
	c.setFillColor(sf::Color::Transparent);
	c.setOutlineColor(sf::Color(0, 0, 0, 192));
	c.setOutlineThickness(2.f);
	if (players[0].Items[players[0].iSelectedWeapon].iBullets * 3 <= players[0].Items[players[0].iSelectedWeapon].iMaxBullets)
	{
		c.setOutlineColor(sf::Color(255, 0, 0, 192));
		c.setOutlineThickness(3.f);
	}
	c.setPosition(MouseC.x-cradius,MouseC.y-cradius);

	g_Window->draw(c);


	auto trace = map.trace_ray(players[camera_follows].vPosition, map.screen_to_world(V.x,V.y,camera_width,g_Mouse.Coords.x,g_Mouse.Coords.y));
	//Checking if there is an object in the way between the player and crosshair
	if (trace.hit_object)
	{
		//Drawing an X
		sf::RectangleShape R;
		float rectsize = 8.f + 2 * cradius;
		R.setPosition(MouseC.x, MouseC.y);
		R.setSize(sf::Vector2f(rectsize, 0.0028f*g_Resolution.y));
		R.setOrigin(0.5f*sf::Vector2f(rectsize, 0.0028f*g_Resolution.y));
		R.setFillColor(sf::Color(192, 0, 0, 128));
		R.setOutlineColor(sf::Color::Black);
		R.setOutlineThickness(1.f);
		R.setRotation(45.f);
		g_Window->draw(R);
		R.setRotation(135.f);
		g_Window->draw(R);

	}

}

void dc_match::DrawUI(sf::Vector2f V)
{
	int health = players[camera_follows].iHealth;
	int armor = players[camera_follows].iShield;
	static int last_health = health;
	static int visual_health = health;
	static dc_clock hclock;
	static int last_armor = armor;
	static int visual_armor = armor;
	static dc_clock aclock;
	static dc_clock lastCallClock;

	static float invAlpha = 1.f;
	static float hpAlpha = 1.f;
	///////////////////////////////////////
	/// Health and shield bars
	///////////////////////////////////////


	
	char hbuf[16], sbuf[16];
	sprintf(hbuf, "%d", health);
	sprintf(sbuf, "%d", armor);


	
	if (last_health != health)
	{
		hclock.Update();
		visual_health = last_health;
	}
	last_health = health;
	if (last_armor != armor)
	{
		aclock.Update();
		visual_armor = last_armor;
	}
	last_armor = armor;
	if (g_Mouse.IsBetween(g_Resolution.x*0.4f, g_Resolution.y*0.9f, g_Resolution.x*0.2f, g_Resolution.y*0.1f))
	{
		hpAlpha -= 0.00266f*lastCallClock.deltaTime();
		if (hpAlpha < 0.33f)
			hpAlpha = 0.33f;
	}
	else
	{
		hpAlpha += 0.00266f*lastCallClock.deltaTime();
		if (hpAlpha > 1.f)
			hpAlpha = 1.f;
	}

	_Window::RenderOverlay(g_Resolution.x*0.4f, g_Resolution.y*0.9f, g_Resolution.x*0.2f, g_Resolution.y*0.1f, 128, 128, 128, hpAlpha*128);
	_Window::RenderOverlay(g_Resolution.x*0.41f, g_Resolution.y*0.91f, g_Resolution.x*0.18f, g_Resolution.y*0.03f, 32, 32, 32, hpAlpha *255);
	_Window::RenderOverlay(g_Resolution.x*0.41f, g_Resolution.y*0.96f, g_Resolution.x*0.18f, g_Resolution.y*0.03f, 32, 32, 32, hpAlpha *255);

	_Window::RenderOverlay(g_Resolution.x*0.41f, g_Resolution.y*0.91f, g_Resolution.x*0.18f*visual_health / 100, g_Resolution.y*0.03f, 219, 88, 66, hpAlpha*max(0, 255 * (1000 - hclock.deltaTime()) / 1000));
	_Window::RenderOverlay(g_Resolution.x*0.41f, g_Resolution.y*0.91f, g_Resolution.x*0.18f*health / 100, g_Resolution.y*0.03f, 98, 219, 66, hpAlpha *255);

	_Window::RenderOverlay(g_Resolution.x*0.41f, g_Resolution.y*0.96f, g_Resolution.x*0.18f*visual_armor / 100, g_Resolution.y*0.03f, 100, 190, 255, hpAlpha*max(0, 255 * (1000 - aclock.deltaTime()) / 1000));
	_Window::RenderOverlay(g_Resolution.x*0.41f, g_Resolution.y*0.96f, g_Resolution.x*0.18f*armor / 100, g_Resolution.y*0.03f, 72, 141, 226, hpAlpha *255);

	_Window::RenderTextB(g_Resolution.x*0.42f, g_Resolution.y*0.91f, hbuf, 16 * g_Resolution.y / 720, 255, 255, 255, hpAlpha * 255);
	_Window::RenderTextB(g_Resolution.x*0.42f, g_Resolution.y*0.96f, sbuf, 16 * g_Resolution.y / 720, 255, 255, 255, hpAlpha * 255);


	///////////////////////////////////////
	/// Inventory items
	///////////////////////////////////////
	int boxsize = g_Resolution.x*0.06f;
	if (g_Mouse.IsBetween(g_Resolution.x - boxsize * 6 - g_Resolution.x*0.01f, g_Resolution.y - boxsize - g_Resolution.x*0.02f, boxsize * 6 + g_Resolution.x*0.01f, boxsize + g_Resolution.y*0.04f))
	{
		invAlpha -= 0.00266f*lastCallClock.deltaTime();
		if (invAlpha < 0.33f)
			invAlpha = 0.33f;
	}
	else
	{
		invAlpha += 0.00266f*lastCallClock.deltaTime();
		if (invAlpha > 1.f)
			invAlpha = 1.f;
	}


	_Window::RenderOverlay(g_Resolution.x-boxsize*6 - g_Resolution.x*0.01f, g_Resolution.y-boxsize-g_Resolution.x*0.02f, boxsize*6+ g_Resolution.x*0.01f, boxsize+g_Resolution.y*0.04f, 128, 128, 128, invAlpha*128);


	static sf::Sprite sprute;
	sprute.setTexture(*g_Textures.get(5));
	auto skale = (float)boxsize / 64.f;
	sprute.setScale(skale, skale);
	static sf::Color rarities[] = { sf::Color(255,255,255,128),sf::Color(90, 180, 0, 170),sf::Color(60, 190, 250, 200),sf::Color(200, 105, 235, 255),sf::Color(240, 150, 40, 255), sf::Color(255,32,32,255) };


	for (int i = 0; i < 5; i++)
	{
		
		if (players[camera_follows].iSelectedWeapon == i)
		{
			if (players[camera_follows].fPulloutDelay <= 0.f)
			{
				sf::RectangleShape rect;
				rect.setPosition(sf::Vector2f(g_Resolution.x - boxsize * 6 + i *boxsize*1.2, g_Resolution.y - boxsize - g_Resolution.x*0.01f));
				rect.setSize(sf::Vector2f(boxsize, boxsize ));
				rect.setFillColor(sf::Color::Transparent);
				rect.setOutlineThickness(2.f);
				rect.setOutlineColor(sf::Color(255,255,255,invAlpha*255));
				g_Window->draw(rect);
			}
			else
			{
				sf::RectangleShape rect;
				rect.setPosition(sf::Vector2f(g_Resolution.x - boxsize * 6 + i *boxsize*1.2, g_Resolution.y - boxsize - g_Resolution.x*0.01f));
				rect.setSize(sf::Vector2f(boxsize, boxsize));
				rect.setFillColor(sf::Color::Transparent);
				rect.setOutlineThickness(2.f);
				rect.setOutlineColor(sf::Color(192,192,192, invAlpha * 255));
				g_Window->draw(rect);
			}
		}
		_Window::RenderOverlay(g_Resolution.x - boxsize * 6 + i *boxsize*1.2, g_Resolution.y - boxsize - g_Resolution.x*0.01f, boxsize, boxsize, 32, 32, 32, invAlpha *255);
		
		if (players[camera_follows].Items[i].bValidated)
		{
			sprute.setPosition(g_Resolution.x - boxsize * 6 + i *boxsize*1.2, g_Resolution.y - boxsize - g_Resolution.x*0.01f);
			sprute.setTextureRect(sf::IntRect(players[camera_follows].Items[i].iTexture * 64, 0, 64, 64));
			auto r = rarities[players[camera_follows].Items[i].iRarity].r;
			auto g = rarities[players[camera_follows].Items[i].iRarity].g;
			auto b = rarities[players[camera_follows].Items[i].iRarity].b;
			auto a = invAlpha*rarities[players[camera_follows].Items[i].iRarity].a;
			_Window::RenderOverlay(g_Resolution.x - boxsize * 6 + i *boxsize*1.2, g_Resolution.y - boxsize - g_Resolution.x*0.01f, boxsize, boxsize, r,g,b,a);

			if(players[camera_follows].Items[i].iType > 3)
				sprute.setColor(sf::Color(255,255,255, invAlpha *255));
			else sprute.setColor(sf::Color(255,255,255, invAlpha *255));
			g_Window->draw(sprute);

			char Bifer[16];
			sprintf(Bifer, "%d/%d\0", players[camera_follows].Items[i].iBullets, players[camera_follows].Items[i].iMaxBullets);
			
			auto texts = _Window::GetTextSize(Bifer, 16);
			for(int XX = -1; XX <= 1; XX++)
				for(int YY = -1; YY <= 1; YY++)
					_Window::RenderTextB(g_Resolution.x - boxsize * 6 + i *boxsize*1.2 + boxsize - texts.x+XX, g_Resolution.y - boxsize - g_Resolution.x*0.01f + boxsize - texts.y - 4.f+YY, Bifer, 16, 0,0,0, invAlpha*invAlpha *255);

			_Window::RenderTextB(g_Resolution.x - boxsize * 6 + i *boxsize*1.2 + boxsize - texts.x, g_Resolution.y - boxsize - g_Resolution.x*0.01f + boxsize - texts.y-4.f, Bifer, 16, 255, 255, 255, invAlpha *255);

		}
	}
	
	///////////////////////////////////////
	/// Current weapon's ammo
	///////////////////////////////////////
	if (players[camera_follows].Items[players[camera_follows].iSelectedWeapon].bValidated)
	{
		char biffer[16];
		sprintf(biffer, "%d/%d", players[camera_follows].Items[players[camera_follows].iSelectedWeapon].iBullets, players[camera_follows].Items[players[camera_follows].iSelectedWeapon].iMaxBullets);
		
		for (int i = -1; i <= 1; i++)
			for (int j = -1; j <= 1; j++)
				_Window::RenderTextBMiddle(g_Resolution.x / 2 + i, g_Resolution.y*0.875f + j, 0, 0, biffer, 24 * g_Resolution.y / 720, 0, 0, 0, 255);
		_Window::RenderTextBMiddle(g_Resolution.x / 2, g_Resolution.y*0.875f, 0, 0, biffer, 24 * g_Resolution.y / 720, 255,255,255, 255);
	}
	///////////////////////////////////////
	/// Time left bars
	///////////////////////////////////////
	if (players[camera_follows].iOpeningChest != -1)
	{
		if (isnan(players[camera_follows].fOpeningTime))return;
		char buf[16];
		sprintf(buf, "%.2f", players[camera_follows].fOpeningTime);
		for (int i = -1; i <= 1; i++)
			for (int j = -1; j <= 1; j++)
				_Window::RenderTextBMiddle(g_Resolution.x / 2 + i, g_Resolution.y*0.8f + j, 0, 0, buf, 24 * g_Resolution.y / 720, 0, 0, 0, 255);
		_Window::RenderTextBMiddle(g_Resolution.x / 2, g_Resolution.y*0.8f, 0, 0, buf, 24 * g_Resolution.y / 720, 36, 98, 222, 255);

		_Window::RenderOverlay(g_Resolution.x*0.45f, g_Resolution.y*0.85f, g_Resolution.x*0.1f, 10, 0, 0, 0, 255);
		_Window::RenderOverlay(g_Resolution.x*0.45f+1, g_Resolution.y*0.85f+1, (g_Resolution.x*0.1f-2)*players[camera_follows].fOpeningTime/CHEST_OPENTIME, 8, 36,98, 222, 255);
		
	}

	if (players[camera_follows].iOpeningAirdrop != -1)
	{
		if (isnan(players[camera_follows].fOpeningTime))return;
		char buf[16];
		sprintf(buf, "%.2f", players[camera_follows].fOpeningTime);
		for (int i = -1; i <= 1; i++)
			for (int j = -1; j <= 1; j++)
				_Window::RenderTextBMiddle(g_Resolution.x / 2 + i, g_Resolution.y*0.8f + j, 0, 0, buf, 24 * g_Resolution.y / 720, 0, 0, 0, 255);
		_Window::RenderTextBMiddle(g_Resolution.x / 2, g_Resolution.y*0.8f, 0, 0, buf, 24 * g_Resolution.y / 720, 36, 98, 222, 255);

		_Window::RenderOverlay(g_Resolution.x*0.45f, g_Resolution.y*0.85f, g_Resolution.x*0.1f, 10, 0, 0, 0, 255);
		_Window::RenderOverlay(g_Resolution.x*0.45f + 1, g_Resolution.y*0.85f + 1, (g_Resolution.x*0.1f - 2)*players[camera_follows].fOpeningTime / AIRDROP_OPENTIME, 8, 36, 98, 222, 255);

	}

	else if (players[camera_follows].fPulloutDelay > 0.f)
	{
		if (isnan(players[camera_follows].fPulloutDelay))return;
		char buf[16];
		sprintf(buf, "%.2f", players[camera_follows].fPulloutDelay);
		for (int i = -1; i <= 1; i++)
			for (int j = -1; j <= 1; j++)
				_Window::RenderTextBMiddle(g_Resolution.x / 2 + i, g_Resolution.y*0.8f + j, 0, 0, buf, 24 * g_Resolution.y / 720, 0, 0, 0, 255);
		_Window::RenderTextBMiddle(g_Resolution.x / 2, g_Resolution.y*0.8f, 0, 0, buf, 24 * g_Resolution.y / 720, 222, 144, 46,255);

		_Window::RenderOverlay(g_Resolution.x*0.45f, g_Resolution.y*0.85f, g_Resolution.x*0.1f, 10, 0, 0, 0, 255);
		_Window::RenderOverlay(g_Resolution.x*0.45f + 1, g_Resolution.y*0.85f + 1, (g_Resolution.x*0.1f - 2)*players[camera_follows].fPulloutDelay / players[camera_follows].Items[players[camera_follows].iSelectedWeapon].fPulloutTime, 8, 222, 144, 46, 255);

	}
	else if (players[camera_follows].fReloadDelay > 0.f)
	{
		if (isnan(players[camera_follows].fReloadDelay))return;
		char buf[16];
		sprintf(buf, "%.2f", players[camera_follows].fReloadDelay);
		for (int i = -1; i <= 1; i++)
			for (int j = -1; j <= 1; j++)
				_Window::RenderTextBMiddle(g_Resolution.x / 2 + i, g_Resolution.y*0.8f + j, 0, 0, buf, 24 * g_Resolution.y / 720, 0, 0, 0, 255);
		_Window::RenderTextBMiddle(g_Resolution.x / 2, g_Resolution.y*0.8f, 0, 0, buf, 24 * g_Resolution.y / 720, 144, 222, 46, 255);

		_Window::RenderOverlay(g_Resolution.x*0.45f, g_Resolution.y*0.85f, g_Resolution.x*0.1f, 10, 0, 0, 0, 255);
		_Window::RenderOverlay(g_Resolution.x*0.45f + 1, g_Resolution.y*0.85f + 1, (g_Resolution.x*0.1f - 2)*players[camera_follows].fReloadDelay / players[camera_follows].Items[players[camera_follows].iSelectedWeapon].fReloadTime, 8, 144,222, 46, 255);

	}
	else if (players[camera_follows].fHealTime > 0.f)
	{
		if (isnan(players[camera_follows].fHealTime))return;
		char buf[16];
		sprintf(buf, "%.2f", players[camera_follows].fHealTime);
		for (int i = -1; i <= 1; i++)
			for (int j = -1; j <= 1; j++)
				_Window::RenderTextBMiddle(g_Resolution.x / 2 + i, g_Resolution.y*0.8f + j, 0, 0, buf, 24 * g_Resolution.y / 720, 0, 0, 0, 255);
		_Window::RenderTextBMiddle(g_Resolution.x / 2, g_Resolution.y*0.8f, 0, 0, buf, 24 * g_Resolution.y / 720, 255, 222, 46, 255);

		_Window::RenderOverlay(g_Resolution.x*0.45f, g_Resolution.y*0.85f, g_Resolution.x*0.1f, 10, 0, 0, 0, 255);
		_Window::RenderOverlay(g_Resolution.x*0.45f + 1, g_Resolution.y*0.85f + 1, (g_Resolution.x*0.1f - 2)*players[camera_follows].fHealTime / players[camera_follows].Items[players[camera_follows].iSelectedWeapon].fHealTime,8, 255, 222, 46, 255);

	}

	//Drawing Markers
	static sf::Color PlayerColors[4] = { sf::Color(20, 80, 225, 255), sf::Color(225, 192, 32, 255), sf::Color(225, 32, 160, 255), sf::Color(160, 255, 32, 255) };

	for (int i = 0; i < 4; i++)
	{
		if (PlayerMarker[i] != sf::Vector2f(-1, -1))
			DrawMark(PlayerMarker[i], PlayerColors[i], true,V);
	}

	//Drawing Text
	DrawHelpButtons();

	lastCallClock.Update();
}

void dc_match::DrawInventoryPage()
{
	_Window::RenderOverlay(0, 0, g_Resolution.x, g_Resolution.y, 0, 0, 0, 128);


	int boxsize = g_Resolution.x*0.06f;
	static sf::Sprite sprute;
	sprute.setTexture(*g_Textures.get(5));
	auto skale = (float)boxsize / 64.f;

	static sf::Color rarities[] = { sf::Color(255,255,255,128),sf::Color(90, 180, 0, 170),sf::Color(60, 190, 250, 200),sf::Color(200, 105, 235, 255),sf::Color(240, 150, 40, 255),sf::Color(255,32,32,255) };
	_Window::RenderOverlay(g_Resolution.x - boxsize * 6 - g_Resolution.x*0.02f, 0, g_Resolution.x, g_Resolution.y, 0, 0, 0, 128);

	for (int i = 0; i < 5; i++)
	{
		sprute.setScale(skale, skale);
		//Drawing box
		if (players[camera_follows].iSelectedWeapon == i)
		{
			if (players[camera_follows].fPulloutDelay <= 0.f)
				_Window::RenderOverlay(g_Resolution.x - boxsize * 6 + i *boxsize*1.2 - 2, g_Resolution.y - boxsize - g_Resolution.x*0.01f - 2, boxsize + 4, boxsize + 4, 255, 255, 255, 255);
			else
				_Window::RenderOverlay(g_Resolution.x - boxsize * 6 + i *boxsize*1.2 - 2, g_Resolution.y - boxsize - g_Resolution.x*0.01f - 2, boxsize + 4, boxsize + 4, 192, 192, 192, 255);
		}
		_Window::RenderOverlay(g_Resolution.x - boxsize * 6 + i *boxsize*1.2, g_Resolution.y - boxsize - g_Resolution.x*0.01f, boxsize, boxsize, 32, 32, 32, 255);

		//Drawing the weapon if available
		if (players[camera_follows].Items[i].bValidated)
		{
			sprute.setPosition(g_Resolution.x - boxsize * 6 + i *boxsize*1.2, g_Resolution.y - boxsize - g_Resolution.x*0.01f);
			sprute.setTextureRect(sf::IntRect(players[camera_follows].Items[i].iTexture * 64, 0, 64, 64));
			auto r = rarities[players[camera_follows].Items[i].iRarity].r;
			auto g = rarities[players[camera_follows].Items[i].iRarity].g;
			auto b = rarities[players[camera_follows].Items[i].iRarity].b;
			auto a = rarities[players[camera_follows].Items[i].iRarity].a;
			_Window::RenderOverlay(g_Resolution.x - boxsize * 6 + i *boxsize*1.2, g_Resolution.y - boxsize - g_Resolution.x*0.01f, boxsize, boxsize, r, g, b, a);

			if (players[camera_follows].Items[i].iType > 3)
				sprute.setColor(sf::Color(255, 255, 255, 255));
			else sprute.setColor(sf::Color(255, 255,255, 255));
			g_Window->draw(sprute);

			//Ammo text
			char Bifer[16];
			sprintf(Bifer, "%d/%d\0", players[camera_follows].Items[i].iBullets, players[camera_follows].Items[i].iMaxBullets);

			auto texts = _Window::GetTextSize(Bifer, 16);
			for (int XX = -1; XX <= 1; XX++)
				for (int YY = -1; YY <= 1; YY++)
					_Window::RenderTextB(g_Resolution.x - boxsize * 6 + i *boxsize*1.2 + boxsize - texts.x + XX, g_Resolution.y - boxsize - g_Resolution.x*0.01f + boxsize - texts.y - 4.f + YY, Bifer, 16, 0, 0, 0, 255);

			_Window::RenderTextB(g_Resolution.x - boxsize * 6 + i *boxsize*1.2 + boxsize - texts.x, g_Resolution.y - boxsize - g_Resolution.x*0.01f + boxsize - texts.y - 4.f, Bifer, 16, 255, 255, 255, 255);


			if (weapon_selected_to_swap != -1)
			{
				if (i == weapon_selected_to_swap)  //Only rendering once
				{
					//Drawing it as selected item
					auto Wpn = players[camera_follows].Items[weapon_selected_to_swap];
					auto r = rarities[Wpn.iRarity].r;
					auto g = rarities[Wpn.iRarity].g;
					auto b = rarities[Wpn.iRarity].b;
					auto a = rarities[Wpn.iRarity].a;
					sprute.setTextureRect(sf::IntRect(Wpn.iTexture * 64, 0, 64, 64));
					_Window::RenderOverlay(g_Resolution.x*0.99f - boxsize * 6, g_Resolution.y *0.025f, boxsize * 6, g_Resolution.y*0.2f, r, g, b, a);

					float skile = 0.013f*min(g_Resolution.y*0.2f, boxsize * 6);
					sprute.setScale(skile, skile);
					sprute.setPosition(g_Resolution.x*0.99f - boxsize * 3 - 32.f*skile, g_Resolution.y*0.125f - 32.f*skile);



					g_Window->draw(sprute);


					_Window::RenderTextB(g_Resolution.x - boxsize * 6 - g_Resolution.x*0.01f, g_Resolution.y*0.25f, Wpn.szName, g_Resolution.y*0.03f, 255, 192, 128, 255);

					_Window::RenderOverlay(g_Resolution.x*0.99f - boxsize * 6, g_Resolution.y*0.29, boxsize * 6, 0.0028f*g_Resolution.y, 255, 192, 128, 255);


					//Rendering the Droppable
					_Window::RenderOverlay(g_Mouse.Coords.x, g_Mouse.Coords.y, boxsize, boxsize, r, g, b, a*0.33f);

					sprute.setScale(skale, skale);
					sprute.setPosition(g_Mouse.Coords.x, g_Mouse.Coords.y);
					g_Window->draw(sprute);

					//Drawing information
					if (Wpn.iType >= 4)
					{
						char Buffer[64];
						sprintf(Buffer, "Healing Power: %d\0", Wpn.iHealAmount);
						_Window::RenderTextB(g_Resolution.x - boxsize * 6 - g_Resolution.x*0.01f, g_Resolution.y*0.33f, Buffer, g_Resolution.y*0.03f, 255, 192, 128, 255);

						sprintf(Buffer, "Heal Maximum: %d\0", Wpn.iHealMax);
						_Window::RenderTextB(g_Resolution.x - boxsize * 6 - g_Resolution.x*0.01f, g_Resolution.y*0.38f, Buffer, g_Resolution.y*0.03f, 255, 192, 128, 255);

						sprintf(Buffer, "Carriable Maximum: %d\0", Wpn.iMaxBullets);
						_Window::RenderTextB(g_Resolution.x - boxsize * 6 - g_Resolution.x*0.01f, g_Resolution.y*0.43f, Buffer, g_Resolution.y*0.03f, 255, 192, 128, 255);

						sprintf(Buffer, "Time to consume: %.1f\0", Wpn.fHealTime);
						_Window::RenderTextB(g_Resolution.x - boxsize * 6 - g_Resolution.x*0.01f, g_Resolution.y*0.48f, Buffer, g_Resolution.y*0.03f, 255, 192, 128, 255);

					}
					else
					{
						char Buffer[64];
						if (Wpn.iType == 0 || Wpn.iType == 2 || Wpn.iType == 3)
							sprintf(Buffer, "Damage: %d - %d\0", Wpn.iDamageEnd, Wpn.iDamageStart);
						else if (Wpn.iType == 1)
							sprintf(Buffer, "Damage: %d - %d\0", Wpn.iDamageEnd*Wpn.iPellets, Wpn.iDamageStart*Wpn.iPellets);
						_Window::RenderTextB(g_Resolution.x - boxsize * 6 - g_Resolution.x*0.01f, g_Resolution.y*0.33f, Buffer, g_Resolution.y*0.03f, 255, 192, 128, 255);

						sprintf(Buffer, "Range: %.1f\0", Wpn.fRange);
						_Window::RenderTextB(g_Resolution.x - boxsize * 6 - g_Resolution.x*0.01f, g_Resolution.y*0.38f, Buffer, g_Resolution.y*0.03f, 255, 192, 128, 255);

						sprintf(Buffer, "Magazine Size: %d\0", Wpn.iMaxBullets);
						_Window::RenderTextB(g_Resolution.x - boxsize * 6 - g_Resolution.x*0.01f, g_Resolution.y*0.43f, Buffer, g_Resolution.y*0.03f, 255, 192, 128, 255);

						sprintf(Buffer, "Firerate: %.2f\0", Wpn.fFirerate);
						_Window::RenderTextB(g_Resolution.x - boxsize * 6 - g_Resolution.x*0.01f, g_Resolution.y*0.48f, Buffer, g_Resolution.y*0.03f, 255, 192, 128, 255);

						if (Wpn.iReloadMethod == 1)
							sprintf(Buffer, "Reload Time: %.2f\0", Wpn.fReloadTime);
						else if (!Wpn.IsConsumable())
							sprintf(Buffer, "Reload Time: %.2f\0", Wpn.fReloadTime*Wpn.iMaxBullets);
						_Window::RenderTextB(g_Resolution.x - boxsize * 6 - g_Resolution.x*0.01f, g_Resolution.y*0.53f, Buffer, g_Resolution.y*0.03f, 255, 192, 128, 255);

					}
				}
			}
				else if (g_Mouse.IsBetween(g_Resolution.x - boxsize * 6 + i *boxsize*1.2 - 2, g_Resolution.y - boxsize - g_Resolution.x*0.01f - 2, boxsize + 4, boxsize + 4, g_Mouse.Coords.x, g_Mouse.Coords.y))
				{
					//Print Weapon information
					_Window::RenderOverlay(g_Resolution.x*0.99f - boxsize * 6, g_Resolution.y *0.025f, boxsize * 6, g_Resolution.y*0.2f, r, g, b, a);

					float skile = 0.013f*min(g_Resolution.y*0.2f, boxsize * 6);
					sprute.setScale(skile, skile);
					sprute.setPosition(g_Resolution.x*0.99f - boxsize * 3 - 32.f*skile, g_Resolution.y*0.125f - 32.f*skile);
					g_Window->draw(sprute);


					_Window::RenderTextB(g_Resolution.x - boxsize * 6 - g_Resolution.x*0.01f, g_Resolution.y*0.25f, players[camera_follows].Items[i].szName, g_Resolution.y*0.03f, 255, 192, 128, 255);

					_Window::RenderOverlay(g_Resolution.x*0.99f - boxsize * 6, g_Resolution.y*0.29, boxsize * 6, 0.0028f*g_Resolution.y, 255, 192, 128, 255);



					if (players[camera_follows].Items[i].iType >= 4)
					{
						char Buffer[64];
						sprintf(Buffer, "Healing Power: %d\0", players[camera_follows].Items[i].iHealAmount);
						_Window::RenderTextB(g_Resolution.x - boxsize * 6 - g_Resolution.x*0.01f, g_Resolution.y*0.33f, Buffer, g_Resolution.y*0.03f, 255, 192, 128, 255);

						sprintf(Buffer, "Heal Maximum: %d\0", players[camera_follows].Items[i].iHealMax);
						_Window::RenderTextB(g_Resolution.x - boxsize * 6 - g_Resolution.x*0.01f, g_Resolution.y*0.38f, Buffer, g_Resolution.y*0.03f, 255, 192, 128, 255);

						sprintf(Buffer, "Carriable Maximum: %d\0", players[camera_follows].Items[i].iMaxBullets);
						_Window::RenderTextB(g_Resolution.x - boxsize * 6 - g_Resolution.x*0.01f, g_Resolution.y*0.43f, Buffer, g_Resolution.y*0.03f, 255, 192, 128, 255);

						sprintf(Buffer, "Time to consume: %.1f\0", players[camera_follows].Items[i].fHealTime);
						_Window::RenderTextB(g_Resolution.x - boxsize * 6 - g_Resolution.x*0.01f, g_Resolution.y*0.48f, Buffer, g_Resolution.y*0.03f, 255, 192, 128, 255);

					}
					else
					{
						char Buffer[64];
						if (players[camera_follows].Items[i].iType == 0 || players[camera_follows].Items[i].iType == 2 || players[camera_follows].Items[i].iType == 3)
							sprintf(Buffer, "Damage: %d - %d\0", players[camera_follows].Items[i].iDamageEnd, players[camera_follows].Items[i].iDamageStart);
						else if (players[camera_follows].Items[i].iType == 1)
							sprintf(Buffer, "Damage: %d - %d\0", players[camera_follows].Items[i].iDamageEnd*players[camera_follows].Items[i].iPellets, players[camera_follows].Items[i].iDamageStart*players[camera_follows].Items[i].iPellets);
						_Window::RenderTextB(g_Resolution.x - boxsize * 6 - g_Resolution.x*0.01f, g_Resolution.y*0.33f, Buffer, g_Resolution.y*0.03f, 255, 192, 128, 255);

						sprintf(Buffer, "Range: %.1f\0", players[camera_follows].Items[i].fRange);
						_Window::RenderTextB(g_Resolution.x - boxsize * 6 - g_Resolution.x*0.01f, g_Resolution.y*0.38f, Buffer, g_Resolution.y*0.03f, 255, 192, 128, 255);

						sprintf(Buffer, "Magazine Size: %d\0", players[camera_follows].Items[i].iMaxBullets);
						_Window::RenderTextB(g_Resolution.x - boxsize * 6 - g_Resolution.x*0.01f, g_Resolution.y*0.43f, Buffer, g_Resolution.y*0.03f, 255, 192, 128, 255);

						sprintf(Buffer, "Firerate: %.2f\0", players[camera_follows].Items[i].fFirerate);
						_Window::RenderTextB(g_Resolution.x - boxsize * 6 - g_Resolution.x*0.01f, g_Resolution.y*0.48f, Buffer, g_Resolution.y*0.03f, 255, 192, 128, 255);

						if (players[camera_follows].Items[i].iReloadMethod == 1)
							sprintf(Buffer, "Reload Time: %.2f\0", players[camera_follows].Items[i].fReloadTime);
						else if (!players[camera_follows].Items[i].IsConsumable())
							sprintf(Buffer, "Reload Time: %.2f\0", players[camera_follows].Items[i].fReloadTime*players[camera_follows].Items[i].iMaxBullets);
						_Window::RenderTextB(g_Resolution.x - boxsize * 6 - g_Resolution.x*0.01f, g_Resolution.y*0.53f, Buffer, g_Resolution.y*0.03f, 255, 192, 128, 255);


				}

			}

		}
	}
}


void dc_match::DrawHelpButtons()
{
	static bool bRun = false;
	static char* Empty = "UNBOUND";
	static char* KeyNames[256];


	if (!bRun)
	{
		bRun = true;

		

		KeyNames[1] = "MOUSE1";
		KeyNames[2] = "MOUSE2";
		KeyNames[4] = "MOUSE3";
		KeyNames[8] = "BACKSPACE";
		KeyNames[9] = "TAB";
		KeyNames[0x0D] = "ENTER";
		KeyNames[0x10] = "SHIFT";
		KeyNames[0x11] = "CTRL";
		KeyNames[0x12] = "ALT";
		KeyNames[0x14] = "CAPS_LOCK";
		KeyNames[0x1B] = "ESC";
		KeyNames[0x20] = "SPACE";
		KeyNames[0x21] = "PG_UP";
		KeyNames[0x22] = "PG_DOWN";
		KeyNames[0x23] = "END";
		KeyNames[0x24] = "HOME";
		KeyNames[0x25] = "LEFT_ARROW";
		KeyNames[0x26] = "UP_ARROW";
		KeyNames[0x27] = "RIGHT_ARROW";
		KeyNames[0x28] = "DOWN_ARROW";
		KeyNames[0x2D] = "INSERT";
		KeyNames[0x2E] = "DEL";
		for (int i = 0; i < 10; i++) {
			KeyNames[0x30+i] = new char[4];
			sprintf(KeyNames[0x30+i], "%c\0", '0' + i);
		}
		for (int i = 0x41; i <= 0x5A; i++)
		{
			KeyNames[i] = new char[4];
			sprintf(KeyNames[i], "%c\0", 'A' + i-0x41);
		}
		for (int i = 0; i < 10; i++) {
			KeyNames[0x60 + i] = new char[8];
			sprintf(KeyNames[0x60+i], "NUM_%c\0", '0' + i);
		}
		KeyNames[0x6A] = "NUM_MULT";
		KeyNames[0x6B] = "NUM_PLUS";
		KeyNames[0x6D] = "NUM_MINUS";
		KeyNames[0x6E] = "NUM_DOT";
		KeyNames[0x6F] = "NUM_PER";

		for (int i = 0; i < 24; i++)
		{
			KeyNames[0x70 + i] = new char[8];
			sprintf(KeyNames[0x70 + i], "F%d\0", i);
		}
		KeyNames[0x90] = "NUMLOCK";
		KeyNames[0x91] = "SCRLOCK";
		KeyNames[0xA0] = "LSHIFT";
		KeyNames[0xA1] = "RSHIFT";
		KeyNames[0xA2] = "LCTRL";
		KeyNames[0xA3] = "RCTRL";
		KeyNames[0xA4] = "LALT";
		KeyNames[0xA5] = "RALT";


		for (int i = 0; i < 256; i++)if(KeyNames[i] == nullptr)KeyNames[i] = "undef" ;
	}

	int fontSize = 0.03f*g_Resolution.y;

	int TextHeight = _Window::GetHeightForFontsize(fontSize); 

	int pusy = 0;

	for (auto db : DrawButs)
	{
		//Chest
		//Draws a box containing the button to press in order to open a chest
		if (db.TYPE == 7)
		{
			auto ChestOpenButton = KeyBinds->find(DCK_SHOOT);
			if (ChestOpenButton == -1)continue;
			char ButtonBuffer[32], PressBuffer[16] = "Press  ", ToOpen[32] = "  to open chest", FullBuffer[96];
			sprintf(ButtonBuffer, KeyNames[ChestOpenButton]);
			sprintf(FullBuffer, "%s%s%s", PressBuffer, ButtonBuffer, ToOpen);
			auto fullBufSize = _Window::GetTextSize(FullBuffer, fontSize);
			auto butBufSize = _Window::GetTextSize(ButtonBuffer, fontSize);
			auto pressBufSize = _Window::GetTextSize(PressBuffer, fontSize);

			sf::RectangleShape Rect;

			Rect.setFillColor(sf::Color::Transparent);
			Rect.setOutlineColor(sf::Color::White);
			Rect.setOutlineThickness(1.f);
			Rect.setSize(sf::Vector2f(butBufSize.x + 10, TextHeight + 4));
			Rect.setPosition(sf::Vector2f(0.5f*(g_Resolution.x - fullBufSize.x) + pressBufSize.x - 5, 0.8f*g_Resolution.y+pusy));
			g_Window->draw(Rect);

			_Window::RenderTextB(0.5f*(g_Resolution.x - fullBufSize.x), 0.8f*g_Resolution.y + pusy, PressBuffer, fontSize, 255, 255, 255);

			for(int i = -1; i <= 1;i++)
				for(int j = -1; j <= 1; j++)
					_Window::RenderTextB(0.5f*(g_Resolution.x - fullBufSize.x) + pressBufSize.x+i, 0.8f*g_Resolution.y + pusy +j, ButtonBuffer, fontSize, 0,0,0);
			_Window::RenderTextB(0.5f*(g_Resolution.x - fullBufSize.x)+pressBufSize.x, 0.8f*g_Resolution.y + pusy, ButtonBuffer, fontSize, 255, 255, 255);
			_Window::RenderTextB(0.5f*(g_Resolution.x - fullBufSize.x) + pressBufSize.x+butBufSize.x, 0.8f*g_Resolution.y + pusy, ToOpen, fontSize, 255, 255, 255);

		}
		//Air drop
		//Draws a box containing the button to press in order to open an air drop
		else if (db.TYPE == 9)
		{
			auto ChestOpenButton = KeyBinds->find(DCK_SHOOT);
			if (ChestOpenButton == -1)continue;
			char ButtonBuffer[32], PressBuffer[16] = "Press  ", ToOpen[32] = "  to open air drop", FullBuffer[96];
			sprintf(ButtonBuffer, KeyNames[ChestOpenButton]);
			sprintf(FullBuffer, "%s%s%s", PressBuffer, ButtonBuffer, ToOpen);
			auto fullBufSize = _Window::GetTextSize(FullBuffer, fontSize);
			auto butBufSize = _Window::GetTextSize(ButtonBuffer, fontSize);
			auto pressBufSize = _Window::GetTextSize(PressBuffer, fontSize);

			sf::RectangleShape Rect;

			Rect.setFillColor(sf::Color::Transparent);
			Rect.setOutlineColor(sf::Color::White);
			Rect.setOutlineThickness(1.f);
			Rect.setSize(sf::Vector2f(butBufSize.x + 10, TextHeight + 4));
			Rect.setPosition(sf::Vector2f(0.5f*(g_Resolution.x - fullBufSize.x) + pressBufSize.x - 5, 0.8f*g_Resolution.y + pusy));
			g_Window->draw(Rect);

			_Window::RenderTextB(0.5f*(g_Resolution.x - fullBufSize.x), 0.8f*g_Resolution.y + pusy, PressBuffer, fontSize, 255, 255, 255);

			for (int i = -1; i <= 1; i++)
				for (int j = -1; j <= 1; j++)
					_Window::RenderTextB(0.5f*(g_Resolution.x - fullBufSize.x) + pressBufSize.x + i, 0.8f*g_Resolution.y + pusy + j, ButtonBuffer, fontSize, 0, 0, 0);
			_Window::RenderTextB(0.5f*(g_Resolution.x - fullBufSize.x) + pressBufSize.x, 0.8f*g_Resolution.y + pusy, ButtonBuffer, fontSize, 255, 255, 255);
			_Window::RenderTextB(0.5f*(g_Resolution.x - fullBufSize.x) + pressBufSize.x + butBufSize.x, 0.8f*g_Resolution.y + pusy, ToOpen, fontSize, 255, 255, 255);

		}
		//Item pickup
		//Draws a box containing the button to press in order to pick up an item
		//It contains two buttons in case of a full inventory
		else if (db.TYPE == 8)
		{
			{
				auto ChestOpenButton = KeyBinds->find(DCK_SHOOT);
				if (ChestOpenButton == -1)continue;
				char ButtonBuffer[32], PressBuffer[16] = "Press  ", ToPickup[16] = "  to pick up ", WeaponBuffer[64], FullBuffer[128];
				if(players[0].hasFreeSlot() != -1)
					sprintf(ButtonBuffer, KeyNames[ChestOpenButton]);
				else
					sprintf(ButtonBuffer, "%s+%s",KeyNames[KeyBinds->find(DCK_ALTERNATIVE)], KeyNames[ChestOpenButton]);
				sprintf(WeaponBuffer, "%s (%d/%d)", g_Items[db.WeaponListIndex].szName, db.WeaponBullets, g_Items[db.WeaponListIndex].iMaxBullets);
				sprintf(FullBuffer, "%s%s%s%s", PressBuffer, ButtonBuffer, ToPickup, WeaponBuffer);
				int rarity = g_Items[db.WeaponListIndex].iRarity;


				auto fullBufSize = _Window::GetTextSize(FullBuffer, fontSize);
				auto butBufSize = _Window::GetTextSize(ButtonBuffer, fontSize);
				auto pressBufSize = _Window::GetTextSize(PressBuffer, fontSize);
				auto pickBufSize = _Window::GetTextSize(ToPickup, fontSize);


				sf::RectangleShape Rect;

				Rect.setFillColor(sf::Color::Transparent);
				Rect.setOutlineColor(sf::Color::White);
				Rect.setSize(sf::Vector2f(butBufSize.x + 10, TextHeight + 4));
				Rect.setOutlineThickness(1.f);
				Rect.setPosition(sf::Vector2f(0.5f*(g_Resolution.x - fullBufSize.x) + pressBufSize.x - 5, 0.8f*g_Resolution.y + pusy));
				g_Window->draw(Rect);

				_Window::RenderTextB(0.5f*(g_Resolution.x - fullBufSize.x), 0.8f*g_Resolution.y + pusy, PressBuffer, fontSize, 255, 255, 255);

				for (int i = -1; i <= 1; i++)
					for (int j = -1; j <= 1; j++)
						_Window::RenderTextB(0.5f*(g_Resolution.x - fullBufSize.x) + pressBufSize.x + i, 0.8f*g_Resolution.y + pusy + j, ButtonBuffer, fontSize, 0, 0, 0);
				_Window::RenderTextB(0.5f*(g_Resolution.x - fullBufSize.x) + pressBufSize.x, 0.8f*g_Resolution.y + pusy, ButtonBuffer, fontSize, 255, 255, 255);
				
				_Window::RenderTextB(0.5f*(g_Resolution.x - fullBufSize.x) + pressBufSize.x + butBufSize.x, 0.8f*g_Resolution.y + pusy, ToPickup, fontSize, 255, 255, 255);
				
				static sf::Color rarities[] = { sf::Color(255,255,255,128),sf::Color(90, 180, 0, 170),sf::Color(60, 190, 250, 200),sf::Color(200, 105, 235, 255),sf::Color(240, 150, 40, 255),sf::Color(255,32,32,255) };
				char r = rarities[rarity].r;
				char g = rarities[rarity].g;
				char b = rarities[rarity].b;
				
				_Window::RenderTextB(0.5f*(g_Resolution.x - fullBufSize.x) + pressBufSize.x + butBufSize.x + pickBufSize.x, 0.8f*g_Resolution.y + pusy, WeaponBuffer, fontSize, r,g,b);

			}
		}

		pusy+=TextHeight+4;
	}

	if (players[0].iHealth <= 0)return;
	//Bus jump box
	if (players[0].bOnBus && bBusJumpable)
	{
		{
			auto Button = KeyBinds->find(DCK_JUMPOFFBUS);
			char ButtonBuffer[32], PressBuffer[16] = "Press  ", ToOpen[32] = "  to jump out", FullBuffer[96];
			sprintf(ButtonBuffer, KeyNames[Button]);
			sprintf(FullBuffer, "%s%s%s", PressBuffer, ButtonBuffer, ToOpen);
			auto fullBufSize = _Window::GetTextSize(FullBuffer, fontSize);
			auto butBufSize = _Window::GetTextSize(ButtonBuffer, fontSize);
			auto pressBufSize = _Window::GetTextSize(PressBuffer, fontSize);

			sf::RectangleShape Rect;

			Rect.setFillColor(sf::Color::Transparent);
			Rect.setOutlineColor(sf::Color::White);
			Rect.setOutlineThickness(1.f);
			Rect.setSize(sf::Vector2f(butBufSize.x + 10, TextHeight + 4));
			Rect.setPosition(sf::Vector2f(0.5f*(g_Resolution.x - fullBufSize.x) + pressBufSize.x - 5, 0.8f*g_Resolution.y + pusy));
			g_Window->draw(Rect);

			_Window::RenderTextB(0.5f*(g_Resolution.x - fullBufSize.x), 0.8f*g_Resolution.y + pusy, PressBuffer, fontSize, 255, 255, 255);

			for (int i = -1; i <= 1; i++)
				for (int j = -1; j <= 1; j++)
					_Window::RenderTextB(0.5f*(g_Resolution.x - fullBufSize.x) + pressBufSize.x + i, 0.8f*g_Resolution.y + pusy + j, ButtonBuffer, fontSize, 0, 0, 0);
			_Window::RenderTextB(0.5f*(g_Resolution.x - fullBufSize.x) + pressBufSize.x, 0.8f*g_Resolution.y + pusy, ButtonBuffer, fontSize, 255, 255, 255);
			_Window::RenderTextB(0.5f*(g_Resolution.x - fullBufSize.x) + pressBufSize.x + butBufSize.x, 0.8f*g_Resolution.y + pusy, ToOpen, fontSize, 255, 255, 255);

		}
	}
	//Descend box
	else if (players[0].fFreeFallHeight > 0.f && !players[0].bOnBus)
	{
		auto Button = KeyBinds->find(DCK_DESCEND);
		char ButtonBuffer[32], PressBuffer[16] = "Hold  ", ToOpen[32] = "  to descend quickly", FullBuffer[96];

		if (GetKeyStatus(DCK_DESCEND, true))
		{
			sprintf(PressBuffer, "Release  ");
			sprintf(ToOpen, "  to descend slower");
		}
		sprintf(ButtonBuffer, KeyNames[Button]);
		sprintf(FullBuffer, "%s%s%s", PressBuffer, ButtonBuffer, ToOpen);
		auto fullBufSize = _Window::GetTextSize(FullBuffer, fontSize);
		auto butBufSize = _Window::GetTextSize(ButtonBuffer, fontSize);
		auto pressBufSize = _Window::GetTextSize(PressBuffer, fontSize);

		sf::RectangleShape Rect;

		Rect.setFillColor(sf::Color::Transparent);
		Rect.setOutlineColor(sf::Color::White);
		Rect.setOutlineThickness(1.f);
		Rect.setSize(sf::Vector2f(butBufSize.x + 10, TextHeight + 4));
		Rect.setPosition(sf::Vector2f(0.5f*(g_Resolution.x - fullBufSize.x) + pressBufSize.x - 5, 0.8f*g_Resolution.y + pusy));
		g_Window->draw(Rect);

		_Window::RenderTextB(0.5f*(g_Resolution.x - fullBufSize.x), 0.8f*g_Resolution.y + pusy, PressBuffer, fontSize, 255, 255, 255);

		for (int i = -1; i <= 1; i++)
			for (int j = -1; j <= 1; j++)
				_Window::RenderTextB(0.5f*(g_Resolution.x - fullBufSize.x) + pressBufSize.x + i, 0.8f*g_Resolution.y + pusy + j, ButtonBuffer, fontSize, 0, 0, 0);
		_Window::RenderTextB(0.5f*(g_Resolution.x - fullBufSize.x) + pressBufSize.x, 0.8f*g_Resolution.y + pusy, ButtonBuffer, fontSize, 255, 255, 255);
		_Window::RenderTextB(0.5f*(g_Resolution.x - fullBufSize.x) + pressBufSize.x + butBufSize.x, 0.8f*g_Resolution.y + pusy, ToOpen, fontSize, 255, 255, 255);

	}



	DrawButs.clear();
}



void dc_match::RemoveExpiredEffects()
{
	for (int i = effects.dmg_effects.size() - 1; i >= 0; i--)
	{
		if (ServerTime - effects.dmg_effects[i].clockBegin > 0.5f)effects.dmg_effects.erase(effects.dmg_effects.begin() + i);
	}
	for (int i = effects.sht_effects.size() - 1; i >= 0; i--)
	{
		if (ServerTime - effects.sht_effects[i].clockBegin > 0.5f)effects.sht_effects.erase(effects.sht_effects.begin() + i);
	}
	for (int i = effects.kilnot_effects.size() - 1; i >= 0; i--)
	{
		if (ServerTime - effects.kilnot_effects[i].clockBegin > 5.f)effects.kilnot_effects.erase(effects.kilnot_effects.begin() + i);
	}
	for (int i = effects.shb_effects.size() - 1; i >= 0; i--)
	{
		if (ServerTime - effects.shb_effects[i].clockBegin > 0.5f)effects.shb_effects.erase(effects.shb_effects.begin() + i);
	}
	for (int i = effects.dth_effects.size() - 1; i >= 0; i--)
	{
		if (ServerTime - effects.dth_effects[i].clockBegin > 1.f)effects.dth_effects.erase(effects.dth_effects.begin() + i);
	}
	for (int i = effects.ade_effects.size() - 1; i >= 0; i--)
	{
		if (ServerTime -effects.ade_effects[i].clockBegin > 3.f)effects.ade_effects.erase(effects.ade_effects.begin() + i);
	}

	for (int i = effects.sce_effects.size() - 1; i >= 0; i--)
	{
		if (ServerTime -effects.sce_effects[i].clockBegin > effects.sce_effects[i].lifetime)effects.sce_effects.erase(effects.sce_effects.begin() + i);
	}
}

void dc_match::SimulateAirdrops()
{
	if (GetCurrentStormPhase() > 15)return;

	fTimeTillNextAirdrop -= timeDiffSinceLastFrame;

	if (fTimeTillNextAirdrop < 0.f)
	{
		sf::Vector2f secNextMid = StormMids[GetCurrentStormPhase() + 2];
		float secNextSize = min(900.f,s_size[GetCurrentStormPhase() + 2]);


		for (int i = 0; i < 2; i++)
		{
			sf::Vector2f npos(-10000, -10000);
			while (GetDistance(npos, secNextMid) > secNextSize*0.5f)
			{
				npos.x = g_RandomDevice.RandomFloat(secNextMid.x - secNextSize*0.5f, secNextMid.x + secNextSize*0.5f);
				npos.y = g_RandomDevice.RandomFloat(secNextMid.y - secNextSize*0.5f, secNextMid.y + secNextSize*0.5f);
			}

			dc_airdrop AD;
			AD.vPosition = npos;
			AD.airdropid = TotalAirdrops;
			AD.ClockBegin = ServerTime;
			Demo_SnapshotUpdateAirdropSpawn(AD.vPosition, AD.airdropid);
			TotalAirdrops++;
			AirDrops.push_back(AD);

		}

		fTimeTillNextAirdrop += g_RandomDevice.RandomFloat(NEXT_AIRDROP_MINTIME, NEXT_AIRDROP_MAXTIME);



		dc_airdropeffect AEF;
		AEF.clockBegin = ServerTime;
		effects.ade_effects.push_back(AEF);
	}

}

void dc_match::DrawEffects(sf::Vector2f V)
{
	RemoveExpiredEffects();

	for (auto it : effects.dmg_effects)
	{
		//it.draw(players[camera_follows].vPosition.x, players[camera_follows].vPosition.y, camera_width);
		it.draw(V.x, V.y, camera_width,ServerTime);
	}
	for (auto it : effects.sht_effects)
	{
		//it.draw(players[camera_follows].vPosition.x, players[camera_follows].vPosition.y, camera_width);
		it.draw(V.x, V.y, camera_width,ServerTime);
	}
	int KillPose = 0;
	for (int i = 0; i < effects.kilnot_effects.size();i++)
	{
		
		auto it = effects.kilnot_effects[i];
		it.draw(0.02f*i*g_Resolution.y,camera_follows, 0.03f*KillPose*g_Resolution.y,ServerTime);
		if (camera_follows == it.Killer)KillPose++;

		if (camera_follows == it.Killer) //It's because data from the players is inaccessible in an effect
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
			sprintf(BufferB, "%s", players[it.Target].szName);
			sprintf(BufferC, "Eliminated %s",players[it.Target].szName);

			auto Dims = _Window::GetTextSize(BufferC, g_Resolution.y * 0.03f);
			auto Dims2 = _Window::GetTextSize(BufferA, g_Resolution.y * 0.03f);
			_Window::RenderTextB(g_Resolution.x*0.5f - Dims.x*0.5f, g_Resolution.y*0.7f + y2, BufferA, g_Resolution.y*0.03f, 222, 222, 222, alpha);
			
			for(int i = -1; i <= 1; i++)
				for(int j = -1; j <= 1;j++)
					_Window::RenderTextB(g_Resolution.x*0.5f - Dims.x* 0.5f + Dims2.x+i, g_Resolution.y*0.7f + y2+i, BufferB, g_Resolution.y*0.03f, 0,0,0, 0.00392156862*(alpha*alpha));

			
			_Window::RenderTextB(g_Resolution.x*0.5f - Dims.x* 0.5f + Dims2.x, g_Resolution.y*0.7f + y2, BufferB, g_Resolution.y*0.03f, 225, 180, 32, alpha);


			if (g_Sounds.CheckDynamicSound(100 + it.Target) == -1 && diff < 0.5f)
			{
				g_Sounds.AddNewDynamicSound(100 + it.Target, 39, 10000, players[camera_follows].vPosition, g_Config.mastervolume.Value, players[camera_follows].vPosition, 0.f, 0.16f);
			}

		}
	}
	for (auto it : effects.shb_effects)
	{
		it.draw(V.x, V.y, camera_width,ServerTime);
	}

	for (auto it : effects.dth_effects)
	{
		it.draw(V.x, V.y, camera_width,ServerTime);
	}
	for (auto it : effects.ade_effects)
	{
		it.draw(ServerTime);
	}
	for (auto it : effects.sce_effects)
	{
		it.draw(ServerTime);
	}
}

void dc_match::DrawMark(sf::Vector2f Coords, sf::Color Color, bool ignore_onscreen, sf::Vector2f V)
{
	static dc_clock ThicknessClock;

	if (ThicknessClock.deltaTime() > 1500)ThicknessClock.Update();
	int thickdiff = ThicknessClock.deltaTime();

	sf::Vector2f blocksize((float)(g_Resolution.x) / camera_width, (float)(g_Resolution.x) / camera_width);

	auto MarkSCR = map.world_to_screen(V.x, V.y, camera_width, Coords.x, Coords.y);

	//if (ignore_onscreen && MarkSCR.x >= 0 && MarkSCR.x <= g_Resolution.x && MarkSCR.y >= 0 && MarkSCR.y <= g_Resolution.y)return;

	//If the marker is on screen
	if (MarkSCR.x >= 0 && MarkSCR.x <= g_Resolution.x && MarkSCR.y >= 0 && MarkSCR.y <= g_Resolution.y)
	{
		auto vCamera = V;
		float tx = g_Resolution.x / 2 + (Coords.x - vCamera.x)*blocksize.x;
		//tx += blocksize.x / 4;
		float ty = g_Resolution.y / 2 + (Coords.y - vCamera.y)*blocksize.y;

		float thickness = (5.f+10.f*0.00133f*abs(thickdiff-750))*(g_Resolution.x / 1280.f)*(10.f/camera_width);
		float height = (150.f*g_Resolution.x) / 1280.f*(10.f/ camera_width);
		sf::Vertex Vert[3] =
		{
			sf::Vertex(sf::Vector2f(tx,ty),Color,sf::Vector2f()),
			sf::Vertex(sf::Vector2f(tx + thickness,ty-height),sf::Color(255,255,255,0),sf::Vector2f()),
			sf::Vertex(sf::Vector2f(tx-thickness,ty - height),sf::Color(255,255,255,0),sf::Vector2f())
		};

		sf::BlendMode additiveBlending = sf::BlendAdd;

		g_Window->draw(Vert, 3, sf::PrimitiveType::Triangles,additiveBlending);
		


	}
	else
	{
		auto diffVec = MarkSCR - sf::Vector2f(0.5f*g_Resolution.x, 0.5f*g_Resolution.y);
		sf::Vector2f posX(-100, -100);
		if (diffVec.x > 0)
		{
			posX.x = 0.45f*g_Resolution.x / diffVec.x;
		}
		else if (diffVec.x < 0)
		{
			posX.x = -0.45f*g_Resolution.x / diffVec.x;
		}
		else
			posX.x = 0.5f*g_Resolution.x;

		if (diffVec.y > 0)
		{
			posX.y = 0.45f*g_Resolution.y / diffVec.y;
		}
		else if (diffVec.y < 0)
		{
			posX.y = -0.45f*g_Resolution.y / diffVec.y;
		}
		else
			posX.y = 0.5f*g_Resolution.y;

		sf::CircleShape C;
		C.setRadius(0.025f*g_Resolution.y);
		C.setOrigin(0.025f*g_Resolution.y, 0.025f*g_Resolution.y);

		float XX = 0.5f*g_Resolution.x + min(posX.x,posX.y)*diffVec.x;
		float YY = 0.5f*g_Resolution.y + min(posX.x, posX.y)*diffVec.y;

		C.setPosition(XX,YY);
		C.setFillColor(Color);
		C.setOutlineColor(sf::Color::Black);
		C.setOutlineThickness(1.f);
		g_Window->draw(C);

		char Buffer[16];
		float dist = GetDistance(Coords, players[camera_follows].vPosition);
		sprintf(Buffer, "%.1fM\0", dist);
		if(YY < 0.5f*g_Resolution.y)
		_Window::RenderTextBMiddle(XX- 0.025f*g_Resolution.y, YY+ 0.01f*g_Resolution.y, 0.05f*g_Resolution.y, 0.05f*g_Resolution.y, Buffer, 16, 0, 0, 0, 255);
		else
		_Window::RenderTextBMiddle(XX - 0.025f*g_Resolution.y, YY - 0.075f*g_Resolution.y, 0.05f*g_Resolution.y, 0.05f*g_Resolution.y, Buffer, 16, 0, 0, 0, 255);

		//TODO:OutlineEffect;
	}

}

void dc_match::DrawBus(sf::Vector2f V)
{
	
	sf::Vector2f blocksize((float)(g_Resolution.x) / camera_width, (float)(g_Resolution.x) / camera_width);

	//auto vCamera = players[camera_follows].vPosition;
	auto vCamera = V;
	static sf::Sprite spr;
	float scale = blocksize.x / 128;
	spr.setScale(scale, scale);
	spr.setTexture(*g_Textures.get(50));
	spr.setOrigin(400, 300);

	auto dirvec = BusEndPosition - BusStartPosition;

	spr.setRotation(vec2angle(dirvec.x, dirvec.y)+180.f);


	float tx = g_Resolution.x / 2 + (BusCurrentPosition.x - vCamera.x)*blocksize.x;
	//tx += blocksize.x / 4;
	float ty = g_Resolution.y / 2 + (BusCurrentPosition.y - vCamera.y)*blocksize.y;
	spr.setPosition(tx,ty);



	if (tx <= -g_Resolution.x || tx >= 2 * g_Resolution.x || ty <= -g_Resolution.y || ty >= 2 * g_Resolution.y)return;
	_Window::AddToRenderList(spr);
}

void dc_match::DrawBus(sf::RenderTexture* T ,sf::Vector2f V)
{

	sf::Vector2f blocksize((float)(g_Resolution.x) / camera_width, (float)(g_Resolution.x) / camera_width);

	//auto vCamera = players[camera_follows].vPosition;
	auto vCamera = V;
	static sf::Sprite spr;
	float scale = blocksize.x / 128;
	spr.setScale(scale, scale);
	spr.setTexture(*g_Textures.get(50));
	spr.setOrigin(400, 300);

	auto dirvec = BusEndPosition - BusStartPosition;

	spr.setRotation(vec2angle(dirvec.x, dirvec.y) + 180.f);


	float tx = g_Resolution.x / 2 + (BusCurrentPosition.x - vCamera.x)*blocksize.x;
	//tx += blocksize.x / 4;
	float ty = g_Resolution.y / 2 + (BusCurrentPosition.y - vCamera.y)*blocksize.y;
	spr.setPosition(tx, ty);



	if (tx <= -g_Resolution.x || tx >= 2 * g_Resolution.x || ty <= -g_Resolution.y || ty >= 2 * g_Resolution.y)return;
	T->draw(spr);
}

void dc_match::DrawMinimap()
{
	if (show_minimap)
	{
		map.show_minimap(players[camera_follows].vPosition.x, players[camera_follows].vPosition.y, camera_width, true,GetCurrentStormMiddle(),GetCurrentStormDiameter()/2);

		static sf::Sprite markersprite;
		markersprite.setTexture(*g_Textures.get(51));
		float scale = 0.078125f* g_Resolution.x*0.005f;
		markersprite.setScale(scale, scale);
		markersprite.setTextureRect(sf::IntRect(320, 0, 64, 64));
		static sf::Color PlayerColors[4] = { sf::Color(20, 80, 225, 255), sf::Color(225, 192, 32, 255), sf::Color(225, 32, 160, 255), sf::Color(160, 255, 32, 255) };
		markersprite.setOrigin(32, 61);


		for (int i = 0; i < 4; i++)
		{
			if (PlayerMarker[i] != sf::Vector2f(-1, -1))
			{
				markersprite.setColor(PlayerColors[i]);
				auto x = g_Resolution.x*0.25 + PlayerMarker[i].x*0.5f*g_Resolution.x / 1000.f;
				auto y = g_Resolution.y*0.5 - g_Resolution.x*0.25 + PlayerMarker[i].y*0.5f*g_Resolution.x / 1000.f;

				markersprite.setPosition(x, y);
				g_Window->draw(markersprite);
			}
		}

		if (bBusMoving)
		{
			//DrawBusRoute
			auto busstart = map.screen_to_world(BusStartPosition.x, BusStartPosition.y, camera_width, g_Resolution.x / 2, g_Resolution.y / 2);
			auto busend = map.screen_to_world(BusEndPosition.x, BusEndPosition.y, camera_width, g_Resolution.x / 2, g_Resolution.y / 2);

			float stop = g_Resolution.y*0.5 - g_Resolution.x*0.25 + g_Resolution.x*0.5*(busstart.y) / 1000;
			float sleft = g_Resolution.x*0.25 + g_Resolution.x*0.5*(busstart.x) / 1000;
			float etop = g_Resolution.y*0.5 - g_Resolution.x*0.25 + g_Resolution.x*0.5*(busend.y) / 1000;
			float eleft = g_Resolution.x*0.25 + g_Resolution.x*0.5*(busend.x) / 1000;

			auto pointdist = GetDistance(sf::Vector2f(eleft, etop), sf::Vector2f(sleft, stop));

			sf::RectangleShape Rect;
			Rect.setSize(sf::Vector2f(pointdist, 0.005555f*g_Resolution.y));
			Rect.setRotation(vec2angle(eleft - sleft, etop - stop));
			Rect.setFillColor(sf::Color(80, 160, 255, 96));
			Rect.setPosition(sleft, stop);
			Rect.setOrigin(sf::Vector2f(0, 0.0027777f*g_Resolution.y));
			static dc_clock WaveClock;
			static bool WaveStart = false;

			float tdiff = 0.001f * WaveClock.deltaTime();

			//Drawing 31 small moving lines in a straight line to show the bus's route
			std::vector<float> intersects;
			std::vector<float> lengths;
			for (int i = 0; i < 31; i++)
			{
				intersects.push_back(0.0334f*pointdist*(2 * tdiff + i));
				if (i == 0)lengths.push_back(0.0334f*pointdist*(2 * tdiff));
				else if (i < 30)lengths.push_back(0.0334f*pointdist);
				if (i == 30)lengths.push_back(pointdist - (0.0334f*pointdist*(2 * tdiff + 29)));
			}
			int intersectid = 0;
			for (float S = 0.f; S < pointdist;)
			{
				float length = lengths[intersectid];

				float mtop = stop + S / pointdist*(etop - stop);
				float mleft = sleft + S / pointdist*(eleft - sleft);

				sf::RectangleShape MiniRect;
				MiniRect.setSize(sf::Vector2f(length, 0.002777f*g_Resolution.y));
				MiniRect.setRotation(vec2angle(eleft - sleft, etop - stop));
				if ((intersectid + WaveStart) % 2 == 0)
					MiniRect.setFillColor(sf::Color(0, 0, 0, 96));
				else
					MiniRect.setFillColor(sf::Color(255, 255, 255, 96));
				MiniRect.setPosition(mleft, mtop);
				MiniRect.setOrigin(sf::Vector2f(0, 0.5f*0.0027777f*g_Resolution.y));

				S = intersects[intersectid];
				intersectid++;

				g_Window->draw(MiniRect);
			}


			if (WaveClock.deltaTime() > 500) {
				WaveStart = !WaveStart;
				WaveClock.Update();
			}

			//Blue on top of the line
			g_Window->draw(Rect);

			//DrawBusOnTop
			static sf::Sprite spr;
			float scale = 1.f / 800.f*0.042f * g_Resolution.y;
			spr.setScale(scale, scale);
			spr.setTexture(*g_Textures.get(50));
			spr.setOrigin(400, 300);

			auto dirvec = BusEndPosition - BusStartPosition;

			spr.setRotation(vec2angle(dirvec.x, dirvec.y) + 180.f);
			auto topleft = map.screen_to_world(BusCurrentPosition.x, BusCurrentPosition.y, camera_width, g_Resolution.x / 2, g_Resolution.y / 2);
			float top = g_Resolution.y*0.5 - g_Resolution.x*0.25 + g_Resolution.x*0.5*(topleft.y) / 1000;
			float left = g_Resolution.x*0.25 + g_Resolution.x*0.5*(topleft.x) / 1000;
			spr.setPosition(left, top);

			g_Window->draw(spr);


		}


		//DrawStorm
		DrawStormOnMiniMap();
		DrawAirDropOnMinimap();




		//DrawplayersonTopCheat
		if ((g_Config.gm_cheats.Value >= 1.f && g_Config.ch_show_players_on_map.Value >= 1.f) || players[0].iHealth <= 0)DrawPlayersOnMinimapCheat();
	}
	else 
	{
		static float minimapAlpha = 1.f;

		if (g_Mouse.IsBetween(g_Resolution.x*0.8, 0, g_Resolution.x*0.2, g_Resolution.x*0.15+g_Resolution.y*0.0833))
		{
			minimapAlpha -= 2.66f * timeDiffSinceLastFrame;
			if (minimapAlpha < 0.33f)
				minimapAlpha = 0.33f;
		}
		else
		{
			minimapAlpha += 2.66f * timeDiffSinceLastFrame;
			if (minimapAlpha > 1.f)
				minimapAlpha = 1.f;
		}

		auto dirvec = BusEndPosition - BusStartPosition;

		auto busang = vec2angle(dirvec.x, dirvec.y) + 180.f;
		map.show_minimapui(players[camera_follows].vPosition.x, players[camera_follows].vPosition.y, camera_width+players[camera_follows].bOnBus*60.f, BusCurrentPosition.x, BusCurrentPosition.y, busang,GetCurrentStormMiddle(),GetCurrentStormDiameter()/2);
		

		//DrawCirclePlayer
		sf::CircleShape Cshape;
		Cshape.setPosition(g_Resolution.x*0.8+g_Resolution.x*0.075f, g_Resolution.y*0.05 + g_Resolution.x*0.075f);
		Cshape.setRadius(g_Resolution.y*0.005f);
		Cshape.setOrigin(g_Resolution.y*0.005f, g_Resolution.y*0.005f);
		Cshape.setFillColor(sf::Color(255, 255, 255, minimapAlpha*255));
		Cshape.setOutlineColor(sf::Color(0, 0, 0, minimapAlpha * 255));
		Cshape.setOutlineThickness(1.f);
		g_Window->draw(Cshape);
		
		auto CurrentPhase = GetCurrentStormPhase();
		auto CurrentStormMid = GetCurrentStormMiddle();
		auto CurrentRadius = GetCurrentStormDiameter() / 2;

		sf::Vector2f StormMid[] = { CurrentStormMid,StormMids[CurrentPhase],StormMids[CurrentPhase + 1] };
		float Radiuses[] = { CurrentRadius,s_size[CurrentPhase] / 2,s_size[CurrentPhase + 1] / 2 };

		for (int i = 0; i < 3; i++)
		{
			if (CurrentPhase <= 2)
			{
				if (i > 0)continue;
			}
			if (CurrentPhase == 3 || CurrentPhase == 5 || CurrentPhase == 7 || CurrentPhase == 9 || CurrentPhase == 11)
			{
				if (i == 1)continue;
			}
			else if (i > 1)continue;

			float Distance = GetDistance(players[camera_follows].vPosition, StormMid[i]);



			if (Distance > Radiuses[i])
			{
				auto Startpoint = sf::Vector2f(g_Resolution.x*0.8 + g_Resolution.x*0.075f, g_Resolution.y*0.05 + g_Resolution.x*0.075f);
				float revarea = 50.f + camera_width;
				auto DiffVector = ToUnitVector(StormMid[i] - players[camera_follows].vPosition);
				DiffVector *= (Distance - Radiuses[i]);

				auto AngleVector = ToUnitVector(DiffVector);

				float scaling = (float)(0.15f*g_Resolution.x) / revarea;


				if (abs(DiffVector.x) < revarea/2 && abs(DiffVector.y) < revarea/2)
				{
					auto Endpoint = Startpoint + DiffVector*scaling;
					sf::Vertex V[] = { sf::Vertex(Startpoint,sf::Color(255,255,255,minimapAlpha*255),sf::Vector2f()),
						sf::Vertex(Endpoint,sf::Color(255,255,255,minimapAlpha*255),sf::Vector2f())};
					g_Window->draw(V, 2, sf::PrimitiveType::Lines);
				}
				else
				{

					if (abs(DiffVector.x) > revarea/2)
					{
						DiffVector /= abs(DiffVector.x);
						DiffVector *= revarea/2;
					}
					if (abs(DiffVector.y) > revarea / 2)
					{
						DiffVector /= abs(DiffVector.y);
						DiffVector *= revarea / 2;
					}
					auto dist = GetLength(DiffVector);

					auto Endpoint = Startpoint + DiffVector*scaling;
					sf::Vertex V[] = { sf::Vertex(Startpoint,sf::Color(255,255,255,minimapAlpha*255),sf::Vector2f()),
						sf::Vertex(Endpoint,sf::Color(255,255,255,minimapAlpha*255),sf::Vector2f()) };
					g_Window->draw(V, 2, sf::PrimitiveType::Lines);
				}

			}


		}
		DrawStormOnMinimapUI();

		//DrawInformation
		float timetillnext = GetTimeTillNextStormPhase();
		int logo = GetCurrentStormPhaseLogo();
		
		if (logo == 3 && 0.001f*t_clock.deltaTime() - s_times[GetCurrentStormPhase()] < 1.f && effects.sce_effects.size() <= 0)
		{
			dc_stormclosingeffect sce;
			sce.clockBegin = ServerTime;
			sce.lifetime = GetTimeTillNextStormPhase();
			effects.sce_effects.push_back(sce);
		}

		static sf::Sprite markersprite;
		markersprite.setTexture(*g_Textures.get(51));
		float scale = 0.667f*0.078125f* g_Resolution.x*0.005f;
		markersprite.setScale(scale, scale);
		markersprite.setTextureRect(sf::IntRect(logo*64, 0, 64, 64));

		markersprite.setPosition(0.8f*g_Resolution.x, 0.05f*g_Resolution.y + 0.15f*g_Resolution.x);
		markersprite.setColor(sf::Color(255, 255, 255, minimapAlpha * 255));
		int minutesleft = 0;
		int secondsleft = 0;

		while (timetillnext >= 60.f)
		{
			minutesleft++;
			timetillnext -= 60.f;
		}
		secondsleft = timetillnext;

		char TimeBuffer[16];
		sprintf(TimeBuffer, "%d:%s%d", minutesleft, ((secondsleft < 10) ? "0" : ""), secondsleft);

		_Window::RenderOverlay(0.8f*g_Resolution.x, 0.05f*g_Resolution.y + 0.15f*g_Resolution.x, 0.15*g_Resolution.x, g_Resolution.y*0.0333f, 0, 0, 0, minimapAlpha*64);

		if (GetCurrentStormPhase() != 17) {
			g_Window->draw(markersprite);
			_Window::RenderTextB(0.8f*g_Resolution.x + scale*72.f, 0.055f*g_Resolution.y + 0.15f*g_Resolution.x, TimeBuffer, 0.0223*g_Resolution.y, 255, 255, 255, minimapAlpha*255);
		}
		markersprite.setTextureRect(sf::IntRect(1 * 64, 0, 64, 64));
		markersprite.setPosition(0.85f*g_Resolution.x, 0.05f*g_Resolution.y + 0.15f*g_Resolution.x);
		g_Window->draw(markersprite);

		sprintf(TimeBuffer, "%d", GetAlivePlayers());
		_Window::RenderTextB(0.85f*g_Resolution.x + scale*72.f, 0.055f*g_Resolution.y + 0.15f*g_Resolution.x, TimeBuffer, 0.0223*g_Resolution.y, 255, 255, 255, minimapAlpha*255);

		markersprite.setTextureRect(sf::IntRect(0 * 64, 0, 64, 64));
		markersprite.setPosition(0.9f*g_Resolution.x, 0.05f*g_Resolution.y + 0.15f*g_Resolution.x);
		g_Window->draw(markersprite);

		sprintf(TimeBuffer, "%d", players[camera_follows].Stats.iEliminations);
		_Window::RenderTextB(0.9f*g_Resolution.x + scale*72.f, 0.055f*g_Resolution.y + 0.15f*g_Resolution.x, TimeBuffer, 0.0223*g_Resolution.y, 255, 255, 255, minimapAlpha*255);

	}
}



void dc_match::DrawAirDropOnMinimap()
{
	static sf::Sprite chspr;
	static bool brun = false;
	if (!brun)
	{
		brun = true;
		chspr.setTexture(*g_Textures.get(67));
		chspr.setOrigin(32, 32);
		chspr.setTextureRect(sf::IntRect(0, 0, 64, 64));
	}



	float size = 10.f;

	auto topleft = sf::Vector2f(g_Resolution.x*0.25, g_Resolution.y*0.5 - g_Resolution.x*0.25);
	auto mapsize = sf::Vector2f(g_Resolution.x*0.5f, g_Resolution.x*0.5f);

	float skale = 1.f / (64.f * 72.f)*g_Resolution.x;
	chspr.setScale(skale,skale);

	for (int i = 0; i < AirDrops.size(); i++)
	{
		auto position = AirDrops[i].vPosition;

		chspr.setPosition(topleft.x + (0.001f*position.x*mapsize.x), topleft.y + (0.001f*position.y*mapsize.y));
		g_Window->draw(chspr);
	}


}

void dc_match::DrawPlayersOnMinimapCheat()
{
	for (int i = 0; i < 100; i++)
	{
		if (players[i].iHealth <= 0)continue;
		auto pl = map.screen_to_world(players[i].vPosition.x, players[i].vPosition.y, camera_width, g_Resolution.x / 2, g_Resolution.y / 2);
		float pltop = g_Resolution.y*0.5 - g_Resolution.x*0.25 + g_Resolution.x*0.5*(pl.y) / 1000;
		float plleft = g_Resolution.x*0.25 + g_Resolution.x*0.5*(pl.x) / 1000;
	
		float radius = 2.f;
		sf::CircleShape c;
		c.setPosition(plleft, pltop);
		c.setOrigin(radius, radius);
		c.setRadius(radius);
		c.setOutlineThickness(2.f);
		c.setFillColor(sf::Color::White);
		c.setOutlineColor(sf::Color::Black);
		g_Window->draw(c);

	}



}

void dc_match::DrawStormOnMiniMap()
{

	static sf::RenderTexture rendText;
	static bool runFirst = false;
	static sf::Vector2i resolution = g_Resolution;

	if (!runFirst || resolution != g_Resolution)
	{
		rendText.create(g_Resolution.x*0.5, g_Resolution.x*0.5);
		runFirst = true;
		resolution = g_Resolution;
	}
	rendText.clear(sf::Color::Transparent);


	sf::Vector2f CurrentStormMid = GetCurrentStormMiddle();
	sf::Vector2f NextStormMid = GetNextStormMiddle();
	float CurrentRadius = GetCurrentStormDiameter()/2;
	float NextRadius = GetNextStormDiameter()/2;



	int CurrentPhase = GetCurrentStormPhase();
	if (CurrentPhase == 17)return;
	//Drawing current storm state, the storm state when it finishes and the next stormstate
	//In a moving zone this shows the current storm, and where it reaches (2 times the latter)
	//In a standing zone this shows the current storm state, the storm state when it finishes, which are the same, and the next stormstate
	sf::Vector2f StormMid[] = { CurrentStormMid,StormMids[CurrentPhase],StormMids[CurrentPhase + 1] };
	float Radiuses[] = { CurrentRadius,s_size[CurrentPhase]/2,s_size[CurrentPhase + 1]/2 };

	for (int i = 0; i < 3; i++)
	{
		if (CurrentPhase <= 2)
		{
			if (i > 0)continue;
		}
		if (CurrentPhase == 3 || CurrentPhase == 5 || CurrentPhase == 7 || CurrentPhase == 9 || CurrentPhase == 11)
		{
			if (i == 1)continue;
		}
		else if (i > 1)continue;

		auto stmid = map.screen_to_world(StormMid[i].x, StormMid[i].y, camera_width, g_Resolution.x / 2, g_Resolution.y / 2);
		auto stmoved = map.screen_to_world(StormMid[i].x + Radiuses[i], StormMid[i].y, camera_width, g_Resolution.x / 2, g_Resolution.y / 2);

		float mitop = g_Resolution.y*0.5 - g_Resolution.x*0.25 + g_Resolution.x*0.5*(stmid.y) / 1000;
		float mileft = g_Resolution.x*0.25 + g_Resolution.x*0.5*(stmid.x) / 1000;
		float motop = g_Resolution.y*0.5 - g_Resolution.x*0.25 + g_Resolution.x*0.5*(stmoved.y) / 1000;
		float moleft = g_Resolution.x*0.25 + g_Resolution.x*0.5*(stmoved.x) / 1000;
		auto radius = GetDistance(sf::Vector2f(mileft, mitop), sf::Vector2f(moleft, motop));

		sf::CircleShape c;
		c.setPosition(mileft-g_Resolution.x*0.25f, mitop-g_Resolution.y*0.5f+g_Resolution.x*0.25f);
		c.setOrigin(radius+1.f, radius+1.f);
		c.setRadius(radius+1.f);
		c.setFillColor(sf::Color::Transparent);
		c.setOutlineColor(sf::Color::White);
		c.setOutlineThickness(2.f);
		rendText.draw(c);

		auto charp = map.screen_to_world(players[camera_follows].vPosition.x, players[camera_follows].vPosition.y, camera_width, g_Resolution.x / 2, g_Resolution.y / 2);
		float chtop = g_Resolution.y*0.5 - g_Resolution.x*0.25 + g_Resolution.x*0.5*(charp.y) / 1000;
		float chleft = g_Resolution.x*0.25 + g_Resolution.x*0.5*(charp.x) / 1000;

		float distfrommid = GetDistance(sf::Vector2f(mitop, mileft), sf::Vector2f(chtop, chleft));
		
		if (distfrommid > radius)
		{
			sf::Vector2f Cpoint = radius*sf::Vector2f(chleft, chtop) + (distfrommid - radius)*sf::Vector2f(mileft, mitop);
			Cpoint /= distfrommid;
			Cpoint.x -= g_Resolution.x*0.25;
			Cpoint.y -= -g_Resolution.x*0.25 + g_Resolution.y*0.5;
			sf::Vertex v[] =
			{
				sf::Vertex(sf::Vector2f(chleft-g_Resolution.x*0.25,chtop + g_Resolution.x*0.25 - g_Resolution.y*0.5),sf::Color(255,255,255,255),sf::Vector2f()),
				sf::Vertex(Cpoint, sf::Color(255, 255, 255, 255), sf::Vector2f())
			};
			rendText.draw(v, 2, sf::PrimitiveType::Lines);
		}
		sf::Sprite sprite;
		sprite.setTexture(rendText.getTexture());
		sprite.setPosition(sf::Vector2f(g_Resolution.x*0.5f, g_Resolution.y*0.5f));
		sprite.setOrigin(sf::Vector2f(g_Resolution.x*0.25f, g_Resolution.x*0.25f));
		sprite.setScale(1.f, -1.f);
		g_Window->draw(sprite);

	}

	

}

void dc_match::DrawStormOnMinimapUI()
{
	static sf::RenderTexture rendText;
	static sf::Vector2i resolution = g_Resolution;
	static bool setup = false;

	if (!setup || resolution != g_Resolution)
	{
		rendText.create(g_Resolution.x*0.15, g_Resolution.x*0.15);
		resolution = g_Resolution;
		setup = true;
	}
	rendText.clear(sf::Color::Transparent);
	sf::Vector2f CurrentStormMid = GetCurrentStormMiddle();
	sf::Vector2f NextStormMid = GetNextStormMiddle();
	float CurrentRadius = GetCurrentStormDiameter() / 2;
	float NextRadius = GetNextStormDiameter() / 2;

	int CurrentPhase = GetCurrentStormPhase();
	if (CurrentPhase == 17)return;
	//Drawing current storm state, the storm state when it finishes and the next stormstate
	//In a moving zone this shows the current storm, and where it reaches (2 times the latter)
	//In a standing zone this shows the current storm state, the storm state when it finishes, which are the same, and the next stormstate
	sf::Vector2f StormMid[] = { CurrentStormMid,StormMids[CurrentPhase],StormMids[CurrentPhase + 1] };
	float Radiuses[] = { CurrentRadius,s_size[CurrentPhase] / 2,s_size[CurrentPhase + 1] / 2 };



	float revarea = 50.f + camera_width + players[camera_follows].bOnBus*60.f;
	float unitSize = (float)(g_Resolution.x*0.15) / revarea;



	for (int i = 0; i < 3; i++)
	{
		if (CurrentPhase <= 2)
		{
			if (i > 0)continue;
		}
		if (CurrentPhase == 3 || CurrentPhase == 5 || CurrentPhase == 7 || CurrentPhase == 9 || CurrentPhase == 11)
		{
			if (i == 1)continue;
		}
		else if (i > 1)continue;

		auto stmid = unitSize*(StormMid[i] - players[camera_follows].vPosition) + 0.5f*sf::Vector2f(g_Resolution.x*0.15,g_Resolution.x*0.15);
		auto strad = Radiuses[i] * unitSize;

		sf::CircleShape c;
		c.setPosition(stmid);
		c.setRadius(strad);
		c.setOrigin(sf::Vector2f(strad, strad));
		c.setFillColor(sf::Color::Transparent);
		c.setOutlineColor(sf::Color::White);
		c.setOutlineThickness(2.f);
		c.setPointCount(90);
		rendText.draw(c);

		//float distfrommid = GetDistance(StormMid[i], players[camera_follows].vPosition);

		//if (distfrommid > Radiuses[i])
		//{
		//	sf::Vector2f Cpoint = radius*sf::Vector2f(chleft, chtop) + (distfrommid - radius)*sf::Vector2f(mileft, mitop);
		//	Cpoint /= distfrommid;

		//	sf::Vertex v[] =
		//	{
		//		sf::Vertex(sf::Vector2f(chleft,chtop),sf::Color(255,255,255,255),sf::Vector2f()),
		//		sf::Vertex(Cpoint, sf::Color(255, 255, 255, 255), sf::Vector2f())
		//	};
		//	g_Window->draw(v, 2, sf::PrimitiveType::Lines);
		//}



	}
	sf::Sprite rendSprite;
	rendSprite.setTexture(rendText.getTexture());
	rendSprite.setPosition(g_Resolution.x*0.8, g_Resolution.y*0.05f+g_Resolution.x*0.15);
	rendSprite.setScale(1.f, -1.f);
	g_Window->draw(rendSprite);


}

void dc_match::DrawAllStormOnMiniMap()
{

	for (int i = 0; i < 17; i++)
	{
		auto CurrentStormMid = StormMids[i];
		auto CurrentRadius = s_size[i] / 2.f;
		auto stmid = map.screen_to_world(CurrentStormMid.x, CurrentStormMid.y, camera_width, g_Resolution.x / 2, g_Resolution.y / 2);
		auto stmoved = map.screen_to_world(CurrentStormMid.x + CurrentRadius, CurrentStormMid.y, camera_width, g_Resolution.x / 2, g_Resolution.y / 2);

		float mitop = g_Resolution.y*0.5 - g_Resolution.x*0.25 + g_Resolution.x*0.5*(stmid.y) / 1000;
		float mileft = g_Resolution.x*0.25 + g_Resolution.x*0.5*(stmid.x) / 1000;
		float motop = g_Resolution.y*0.5 - g_Resolution.x*0.25 + g_Resolution.x*0.5*(stmoved.y) / 1000;
		float moleft = g_Resolution.x*0.25 + g_Resolution.x*0.5*(stmoved.x) / 1000;
		auto radius = GetDistance(sf::Vector2f(mileft, mitop), sf::Vector2f(moleft, motop));

		sf::CircleShape c;
		c.setPosition(mileft, mitop);
		c.setOrigin(radius, radius);
		c.setRadius(radius);
		c.setFillColor(sf::Color::Transparent);
		c.setOutlineColor(sf::Color::White);
		c.setOutlineThickness(2.f);

		g_Window->draw(c);
	}
}

sf::Color dc_match::GetCurrentStormColor()
{
	static dc_clock Clock;
	static dc_clock LightningClock;
	static int CurrentCI = 0;
	static int NextCI = 1;


	if (Random(0, 1000*g_Framerate) < 600)LightningClock.Update();

	sf::Color Colors[] = { sf::Color(160,0,225,48),
		sf::Color(110,25,225,48),
		sf::Color(120,10,230,48),
		sf::Color(160,30,230,48),
		sf::Color(170,0,240,48),
		sf::Color(160,0,225,60),
		sf::Color(120,0,180,48),
		sf::Color(200,0,255,48),
		sf::Color(130,30,210,48),
		sf::Color(180,0,125,48),
		sf::Color(225,0,160,48)
	};
	sf::Color LightningColor(255, 255, 255, 72);
	if (Clock.deltaTime() > 500)
	{
		CurrentCI = NextCI;
		NextCI = Random(0, 10);
		Clock.Update();
	}
	int DIFF = Clock.deltaTime();
	int R = DIFF*Colors[NextCI].r + (500 - DIFF)*Colors[CurrentCI].r;
	int G = DIFF*Colors[NextCI].g + (500 - DIFF)*Colors[CurrentCI].g;
	int B = DIFF*Colors[NextCI].b + (500 - DIFF)*Colors[CurrentCI].b;
	int A = DIFF*Colors[NextCI].a + (500 - DIFF)*Colors[CurrentCI].a;
	R /= 500; G /= 500; B /= 500; A /= 500;

	int LDIFF = LightningClock.deltaTime()+50;

	if (LDIFF < 250)
	{
		R = LDIFF*R + (250 - LDIFF)*LightningColor.r; R /= 250;
		G = LDIFF*G + (250 - LDIFF)*LightningColor.g; G /= 250;
		B = LDIFF*B + (250 - LDIFF)*LightningColor.b; B /= 250;
		A = LDIFF*A + (250 - LDIFF)*LightningColor.a; A /= 250;
	}


	return sf::Color(R, G, B, A);
}




void dc_match::DrawStorm(sf::Vector2f V)
{
	sf::Color StormColor = GetCurrentStormColor();

	
	
	auto TL = map.screen_to_world(V.x, V.y, camera_width, 0, 0);
	auto TR = map.screen_to_world(V.x, V.y, camera_width, g_Resolution.x, 0);
	auto BL = map.screen_to_world(V.x, V.y, camera_width, 0, g_Resolution.y);
	auto BR = map.screen_to_world(V.x, V.y, camera_width, g_Resolution.x, g_Resolution.y);

	auto screendiaminworld = GetDistance(TL, BR);
	auto screendiam = GetDistance(sf::Vector2f(0, 0), sf::Vector2f(g_Resolution.x, g_Resolution.y));
	auto pixelinworld = (TR.x - TL.x) / g_Resolution.x;

	auto sMidonScreen = map.world_to_screen(V.x, V.y, camera_width, GetCurrentStormMiddle().x, GetCurrentStormMiddle().y);

	//ConLog("\n%.1f %.1f | %.1f %.1f # %.1f %.1f %.1f %.1f", TL.x, TL.y, BR.x, BR.y, IsPointInStorm(TL), IsPointInStorm(TR), IsPointInStorm(BL), IsPointInStorm(BR));

	if (IsPointInStorm(TL) && IsPointInStorm(TR) && IsPointInStorm(BL) && IsPointInStorm(BR) && screendiaminworld <= GetCurrentStormDiameter())
	{
		_Window::RenderOverlay(0, 0, g_Resolution.x, g_Resolution.y, StormColor.r, StormColor.g, StormColor.b, StormColor.a);
	}
	else if (screendiaminworld > GetCurrentStormDiameter() && (sMidonScreen.x < -g_Resolution.x/2 || sMidonScreen.x > 1.5f*g_Resolution.x || sMidonScreen.y < -g_Resolution.y/2 || sMidonScreen.y > 1.5f*g_Resolution.y  ))
		_Window::RenderOverlay(0, 0, g_Resolution.x, g_Resolution.y, StormColor.r, StormColor.g, StormColor.b, StormColor.a);
	else
	{


		auto M = GetCurrentStormMiddle();
		auto r = GetCurrentStormDiameter() / 2;



		std::vector<sf::Vector2f> Points;
		std::vector<sf::Vector2f> PointsOuter;
		for (int i = 0; i <= 360; i++)
		{
			float cur_ang = 1.f*i;
			sf::Vector2f Point = angle2vec(cur_ang)*r + M;
			sf::Vector2f PointOuter = angle2vec(cur_ang)*(r+screendiaminworld*2) + M;

			auto SP = map.world_to_screen(V.x, V.y, camera_width, Point.x, Point.y);
			auto SPO = map.world_to_screen(V.x, V.y, camera_width, PointOuter.x, PointOuter.y);

			Points.push_back(SP);
			PointsOuter.push_back(SPO);
		}
		std::vector<sf::Vertex> Verts;
		//This is drawing trapezoids which will look like a circle
		for (int i = 0; i < 360; i++)
		{
			sf::Vertex A(Points[i], StormColor, sf::Vector2f());
			sf::Vertex B(PointsOuter[i], StormColor, sf::Vector2f());
			sf::Vertex C(PointsOuter[i+1], StormColor, sf::Vector2f());
			sf::Vertex D(Points[i+1], StormColor, sf::Vector2f());

			Verts.push_back(A);
			Verts.push_back(B);
			Verts.push_back(C);
			Verts.push_back(D);
		}

		g_Window->draw(&Verts[0], Verts.size(), sf::PrimitiveType::Quads);


		if (r > 0.1f)
		{
			std::vector<sf::Vector2f> PointsOuterA;
			for (int i = 0; i <= 360; i++)
			{
				float cur_ang = 1.f*i;
				sf::Vector2f PointOuter = angle2vec(cur_ang)*(r + pixelinworld * 2) + M;
				auto SPO = map.world_to_screen(V.x, V.y, camera_width, PointOuter.x, PointOuter.y);

				PointsOuterA.push_back(SPO);
			}
			std::vector<sf::Vertex> VertsA;
			for (int i = 0; i < 360; i++)
			{
				sf::Vertex A(Points[i], sf::Color(StormColor.r, StormColor.g, StormColor.b, 255), sf::Vector2f());
				sf::Vertex B(PointsOuterA[i], sf::Color(StormColor.r, StormColor.g, StormColor.b, 255), sf::Vector2f());
				sf::Vertex C(PointsOuterA[i + 1], sf::Color(StormColor.r, StormColor.g, StormColor.b, 255), sf::Vector2f());
				sf::Vertex D(Points[i + 1], sf::Color(StormColor.r, StormColor.g, StormColor.b, 255), sf::Vector2f());

				VertsA.push_back(A);
				VertsA.push_back(B);
				VertsA.push_back(C);
				VertsA.push_back(D);
			}

			g_Window->draw(&VertsA[0], VertsA.size(), sf::PrimitiveType::Quads);
		}
	}

}

void dc_match::DrawStorm(sf::RenderTexture* T,sf::Vector2f V)
{
	sf::Color StormColor = GetCurrentStormColor();



	auto TL = map.screen_to_world(V.x, V.y, camera_width, 0, 0);
	auto TR = map.screen_to_world(V.x, V.y, camera_width, g_Resolution.x, 0);
	auto BL = map.screen_to_world(V.x, V.y, camera_width, 0, g_Resolution.y);
	auto BR = map.screen_to_world(V.x, V.y, camera_width, g_Resolution.x, g_Resolution.y);

	auto screendiaminworld = GetDistance(TL, BR);
	auto screendiam = GetDistance(sf::Vector2f(0, 0), sf::Vector2f(g_Resolution.x, g_Resolution.y));
	auto pixelinworld = (TR.x - TL.x) / g_Resolution.x;

	auto sMidonScreen = map.world_to_screen(V.x, V.y, camera_width, GetCurrentStormMiddle().x, GetCurrentStormMiddle().y);

	//ConLog("\n%.1f %.1f | %.1f %.1f # %.1f %.1f %.1f %.1f", TL.x, TL.y, BR.x, BR.y, IsPointInStorm(TL), IsPointInStorm(TR), IsPointInStorm(BL), IsPointInStorm(BR));

	if (IsPointInStorm(TL) && IsPointInStorm(TR) && IsPointInStorm(BL) && IsPointInStorm(BR) && screendiaminworld <= GetCurrentStormDiameter())
	{
		sf::RectangleShape rect;
		rect.setPosition(0, 0);
		rect.setSize(sf::Vector2f(g_Resolution.x, g_Resolution.y));
		rect.setFillColor(StormColor);
		T->draw(rect);
	}
	else if (screendiaminworld > GetCurrentStormDiameter() && (sMidonScreen.x < -g_Resolution.x / 2 || sMidonScreen.x > 1.5f*g_Resolution.x || sMidonScreen.y < -g_Resolution.y / 2 || sMidonScreen.y > 1.5f*g_Resolution.y))
	{
		sf::RectangleShape rect;
		rect.setPosition(0, 0);
		rect.setSize(sf::Vector2f(g_Resolution.x, g_Resolution.y));
		rect.setFillColor(StormColor);
		T->draw(rect);
	}
	else
	{
		auto M = GetCurrentStormMiddle();
		auto r = GetCurrentStormDiameter() / 2;

		std::vector<sf::Vector2f> Points;
		std::vector<sf::Vector2f> PointsOuter;
		for (int i = 0; i <= 360; i++)
		{
			float cur_ang = 1.f*i;
			sf::Vector2f Point = angle2vec(cur_ang)*r + M;
			sf::Vector2f PointOuter = angle2vec(cur_ang)*(r + screendiaminworld * 2) + M;

			auto SP = map.world_to_screen(V.x, V.y, camera_width, Point.x, Point.y);
			auto SPO = map.world_to_screen(V.x, V.y, camera_width, PointOuter.x, PointOuter.y);

			Points.push_back(SP);
			PointsOuter.push_back(SPO);
		}
		std::vector<sf::Vertex> Verts;
		for (int i = 0; i < 360; i++)
		{
			sf::Vertex A(Points[i], StormColor, sf::Vector2f());
			sf::Vertex B(PointsOuter[i], StormColor, sf::Vector2f());
			sf::Vertex C(PointsOuter[i + 1], StormColor, sf::Vector2f());
			sf::Vertex D(Points[i + 1], StormColor, sf::Vector2f());

			Verts.push_back(A);
			Verts.push_back(B);
			Verts.push_back(C);
			Verts.push_back(D);
		}

		T->draw(&Verts[0], Verts.size(), sf::PrimitiveType::Quads);


		if (r > 0.1f)
		{
			std::vector<sf::Vector2f> PointsOuterA;
			for (int i = 0; i <= 360; i++)
			{
				float cur_ang = 1.f*i;
				sf::Vector2f PointOuter = angle2vec(cur_ang)*(r + pixelinworld * 2) + M;
				auto SPO = map.world_to_screen(V.x, V.y, camera_width, PointOuter.x, PointOuter.y);

				PointsOuterA.push_back(SPO);
			}
			std::vector<sf::Vertex> VertsA;
			for (int i = 0; i < 360; i++)
			{
				sf::Vertex A(Points[i], sf::Color(StormColor.r, StormColor.g, StormColor.b, 255), sf::Vector2f());
				sf::Vertex B(PointsOuterA[i], sf::Color(StormColor.r, StormColor.g, StormColor.b, 255), sf::Vector2f());
				sf::Vertex C(PointsOuterA[i + 1], sf::Color(StormColor.r, StormColor.g, StormColor.b, 255), sf::Vector2f());
				sf::Vertex D(Points[i + 1], sf::Color(StormColor.r, StormColor.g, StormColor.b, 255), sf::Vector2f());

				VertsA.push_back(A);
				VertsA.push_back(B);
				VertsA.push_back(C);
				VertsA.push_back(D);
			}

			T->draw(&VertsA[0], VertsA.size(), sf::PrimitiveType::Quads);
		}

	}

}

void dc_match::DrawVictoryEffect()
{
	int wID = 0;
	for (int i = 0; i < 100; i++)if (players[i].iHealth > 0) { wID = i; break; }
	float Diff = 0.001f*MatchEndClock.deltaTime();
	sf::Vector2i Dim;
	//Pulse
	if (Diff >= 1.f && Diff < 1.5f)
	{
		float TextSize = g_Resolution.y*0.1f+(Diff-1.f)*g_Resolution.y*0.1f;
		Dim = _Window::GetTextSize("\nVICTORY\n\n", TextSize);

		int Alpha = 255-(Diff-1.f)*510;
		if (players[0].iHealth > 0)
		_Window::RenderTextBAdditive(0.5f*(g_Resolution.x - Dim.x), 0.2f*g_Resolution.y - 0.5f*Dim.y, "\nVICTORY", TextSize, 225, 180, 32, Alpha);
	}

	//OutLine
	if(Diff >= 0.f)
	{
		float TextSize = g_Resolution.y*0.1f;
		if (Diff < 0.5f)
			TextSize = Diff * 2 * g_Resolution.y*0.1f;
		int Alpha = 255;
		if (Diff < 0.5f)Alpha = (Diff) * 255 * 2;
		Dim = _Window::GetTextSize("\nVICTORY\n\n", TextSize);
		if (players[0].iHealth > 0)
			for(int i = -2; i <=2;i++)
				for(int j = -2;j < 2;j++)
					_Window::RenderTextB(0.5f*(g_Resolution.x - Dim.x)+i, 0.2f*g_Resolution.y - 0.5f*Dim.y+j, "\nVICTORY\n", TextSize, 0,0,0, Alpha);
	}

	//Victory Sign
	if(Diff >= 0.5f)
	{
		float TextSize = g_Resolution.y*0.1f;
		if(Diff < 1.f)
			TextSize = (Diff-1.5f) * (-2) * g_Resolution.y*0.1f;
		Dim = _Window::GetTextSize("\nVICTORY\n\n", TextSize);

		int Alpha = 255;
		if (Diff < 1.f)Alpha = (Diff-0.5f) * 255 * 2;
		if (players[0].iHealth > 0)
			_Window::RenderTextBAdditive(0.5f*(g_Resolution.x - Dim.x), 0.2f*g_Resolution.y -0.5f*Dim.y, "\nVICTORY\n", TextSize, 225, 180, 32, Alpha);
	}
	//Victory Text
	if(Diff >= 1.5f)
	{
		float TextSize = g_Resolution.y*0.04f;
		if (Diff < 2.f) TextSize = g_Resolution.y*0.02f + (Diff - 1.5f)*g_Resolution.y*0.04f;
		int Alpha = 255;
		if (Diff < 2.f)Alpha = (Diff-1.5f) * 2 * 255;

		char Buffer[128]; sprintf(Buffer, "%s won with %d eliminations", players[wID].szName, players[wID].Stats.iEliminations);


		auto DimB = _Window::GetTextSize(Buffer, TextSize);

		_Window::RenderTextB(0.5f*(g_Resolution.x - DimB.x), 0.2f*g_Resolution.y + 0.5f*Dim.y, Buffer, TextSize, 255, 255, 255, Alpha);
	}

}

void dc_match::DrawAll()
{
	static dc_clock Clock;

	if (Clock.deltaTime() > 1000)Clock.Update();
	float timediff = timeDiffSinceLastFrame;


	auto vC = GetCameraPosition();
	//Essentially this line below makes the player be on the other side of the screen
	auto V = map.cursor_to_world(vC.x, vC.y, camera_width);
	DrawMap(V);
	DrawPlayers(V);


	map.drawitems(V.x, V.y, camera_width);
	
	if (bBusMoving)DrawBus(V);
	SimulateProjectiles(timediff,V);
	SimulateExplosives(timediff,V);
	Demo_SnapshotUpdateExplosives();
	DrawEffects(V);
	DrawStorm(V);
	
	if (bMatchEnded != 1)
	{
		DrawUI(V);
		if (show_inventory)
			DrawInventoryPage();
		else {
			DrawCrosshair(V);
			DrawMinimap();
		}
	}
	else DrawVictoryEffect();
		
	if (players[0].iHealth <= 0)
		DrawSpectatorInfo();


	Clock.Update();
}

void dc_match::CheckCollisions(int i, float t)
{

	if (players[i].bOnBus)return;

	int x = players[i].vPosition.x;
	int y = players[i].vPosition.y;

	if (players[i].vVelocity.x == 0 && players[i].vVelocity.x == 0)return;

	for (int j = 0; j < 100; j++)
	{
		if (i == j)continue;
		if (players[j].iHealth <= 0)continue;
		if (abs(players[i].fFreeFallHeight - players[j].fFreeFallHeight) > 5.f)continue;
		if (players[i].fFreeFallHeight > 75.f)continue;
		if(abs(players[i].vPosition.x+players[i].vVelocity.x*t- players[j].vPosition.x) < 0.5f && abs(players[i].vPosition.y-players[i].vVelocity.y*t - players[j].vPosition.y) <0.5f)
		{
			if (players[i].vVelocity.x > 0.1f)
			{
				if (players[i].vPosition.x + players[i].vVelocity.x*t > players[j].vPosition.x-0.5f)
				{
					players[i].vVelocity.x *= -1.f;
					//players[i].vPosition.x = players[j].vPosition.x - 0.5f;
				}
			}
			else if (players[i].vVelocity.x < -0.1f)
			{
				if (players[i].vPosition.x + players[i].vVelocity.x*t < players[j].vPosition.x + 0.5f)
				{
					players[i].vVelocity.x *= -1.f;
					//players[i].vPosition.x = players[j].vPosition.x + 0.5f;
				}
			}
			if (players[i].vVelocity.y > 0.1f)
			{
				if (players[i].vPosition.y - players[i].vVelocity.y*t < players[j].vPosition.y + 0.5f)
				{
					players[i].vVelocity.y *= -1.f;
					//players[i].vPosition.y = players[j].vPosition.y + 0.5f;
				}
			}
			else 	if (players[i].vVelocity.y < -0.1f)
			{
				if (players[i].vPosition.y - players[i].vVelocity.y*t > players[j].vPosition.y - 0.5f)
				{
					players[i].vVelocity.y *= -1.f;
					//players[i].vPosition.y = players[j].vPosition.y - 0.5f;
				}
			}

		}
	}
	if (players[i].fFreeFallHeight > 5.f)return;
	if (x >= map.size.x - 1 || y >= map.size.y - 1 || x <= 0 || y <= 0)return;

	if (players[i].vVelocity.x < 0)
	{
		if (map.lines[y].blocks[x].walls[0].iHealth > 0)
		{
			if (players[i].vPosition.x + players[i].vVelocity.x*t - 0.25 < x)
			{
				players[i].vPosition.x = float(x) + 0.26;
				players[i].vVelocity.x = 0;
			}
		}
	}
	else
	{
		if (map.lines[y].blocks[x+1].walls[0].iHealth > 0)
		{
			if (players[i].vPosition.x + players[i].vVelocity.x*t + 0.25 > x+1)
			{
				players[i].vPosition.x = float(x+1) - 0.26;
				players[i].vVelocity.x = 0;
			}
		}
	}

	if (players[i].vVelocity.y > 0)
	{
		
		if (map.lines[y].blocks[x].walls[1].iHealth > 0)
		{
			if (players[i].vPosition.y - players[i].vVelocity.y*t - 0.25 < y)
			{
				players[i].vPosition.y = float(y) + 0.26;
				players[i].vVelocity.y = 0;
			}
		}
	}
	else
	{
		if (map.lines[y+1].blocks[x].walls[1].iHealth > 0)
		{
			if (players[i].vPosition.y - players[i].vVelocity.y*t + 0.25 > y + 1)
			{
				players[i].vPosition.y = float(y + 1) - 0.26;
				players[i].vVelocity.y = 0;
			}
		}
	}

	////Fix this, bots get stuck for some reason
	//return;

	//float Xs[] = { players[i].vPosition.x + 0.25f,players[i].vPosition.x + 0.25f,players[i].vPosition.x - 0.25f,players[i].vPosition.x - 0.25f };
	//float Ys[] = { players[i].vPosition.y + 0.25f,players[i].vPosition.y - 0.25f,players[i].vPosition.y + 0.25f,players[i].vPosition.y - 0.25f };

	//

	//for (int j = 0; j < 4; j++)

	//{

	//	float plX = Xs[j];
	//	float plY = Ys[j];
	//	int x = (int)Xs[j];
	//	int y = (int)Ys[j];

	//	if (x >= map.size.x - 1 || y >= map.size.y - 1 || x <= 0 || y <= 0)continue;

	//	if (players[i].vVelocity.x < -0.01)
	//	{
	//		if (map.lines[y].blocks[x].walls[0].iHealth > 0)
	//		{
	//			if (plX + players[i].vVelocity.x*t < x)
	//			{
	//				//players[i].vPosition.x = float(x) + 0.26;
	//				players[i].vVelocity.x = 0;
	//			}
	//		}
	//	}
	//	else if (players[i].vVelocity.x > 0.01)
	//	{
	//		if (map.lines[y].blocks[x + 1].walls[0].iHealth > 0)
	//		{
	//			if (plX + players[i].vVelocity.x*t > x + 1)
	//			{
	//				//players[i].vPosition.x = float(x + 1) - 0.26;
	//				players[i].vVelocity.x = 0;
	//			}
	//		}
	//	}

	//	if (players[i].vVelocity.y > 0.01)
	//	{

	//		if (map.lines[y].blocks[x].walls[1].iHealth > 0)
	//		{
	//			if (plY - players[i].vVelocity.y*t < y)
	//			{
	//				//players[i].vPosition.y = float(y) + 0.26;
	//				players[i].vVelocity.y = 0;
	//			}
	//		}
	//	}
	//	else if (players[i].vVelocity.y < -0.01)
	//	{
	//		if (map.lines[y + 1].blocks[x].walls[1].iHealth > 0)
	//		{
	//			if (plY - players[i].vVelocity.y*t > y + 1)
	//			{
	//				//players[i].vPosition.y = float(y + 1) - 0.26;
	//				players[i].vVelocity.y = 0;
	//			}
	//		}
	//	}
	//}
}

void dc_match::Start(int bs)
{
	//loading themap
	map.load("BigSize");
	//Creating storm and bus
	GenerateBusRoute();
	GenerateStorms();
	//Getting all the walls for faster trace ray calculations
	map.begin_lines();

	//Killing all bots previously
	for (int i = 1; i < 100; i++)
	{
		players[i].iHealth = 0;
	}
	players[0].iHealth = 100;
	players[0].vPosition = BusCurrentPosition;

	int shrink = 25;
	//Resurrecting enough bots
	for (int i = 1; i < bs; i++)
	{
		players[i].iHealth = 100;
		players[i].vPosition = BusCurrentPosition;
	}





	//Creating the bots
	BotBegin(EasyCases, NormalCases, HardCases, ExpertCases);
	bBusMoving = true;

	map.day_time = Random(0, 7200);

	for (int i = 0; i < 100; i++)
	{
		players[i].bOnBus = true;
	}

	fTimeTillNextAirdrop = NEXT_AIRDROP_MINTIME + g_RandomDevice.RandomFloat(NEXT_AIRDROP_MINTIME, NEXT_AIRDROP_MAXTIME);

	//Starting a demo
	if (DemoRecord == 1)
	{
		Demo_CreateSnapshotPointers();
		dc_demo_metadata meData;
		meData.Setup(this);
		std::thread TH(Demo_Convert,this,meData);
		//Detaching so it can run when this scope ends
		TH.detach();
	}

	ServerStartClock.Update();
}

void dc_match::PlayerCheckCurrentLocationForData(int player)
{
	if (players[player].fFreeFallHeight > 10.f)return;
	for (int i = 0;i<  map.labels.size();i++)
	{
		auto l = map.labels[i];
		if (GetDistance(players[player].vPosition, l.vPosition) > l.size)continue;
		if (IsIn(players[player].Stats.VisitedPositions, i))continue;
		players[player].Stats.VisitedPositions.push_back(i);
	}
}

void dc_match::PlayerJumpOffBus(int player)
{
	if (!bBusJumpable)return;
	players[player].bOnBus = false;
	players[player].fFreeFallHeight = 100.f;
}

void dc_match::PlayerDescent(int player, float diff, float speed)
{
	if(players[player].fFreeFallHeight > 0.f)
		players[player].fFreeFallHeight -= diff * speed;


}

void dc_match::PlayerOpenChest(int player, int  chest_id)
{
	if (players[player].fFreeFallHeight > 0.f)return;
	if (chest_id < 0 || players[player].fOpeningTime > 0.f || map.chests[chest_id].bOpen || GetDistance(players[player].vPosition,map.chests[chest_id].vPosition) > 2.f)return;
	players[player].iOpeningChest = chest_id;
	players[player].fOpeningTime = CHEST_OPENTIME;
}

void dc_match::PlayerOpenAirdrop(int player, int airdrop_id)
{
	if (players[player].fFreeFallHeight > 0.f)return;


	int AirDropInd = -1;
	for (int i = 0; i < AirDrops.size(); i++)
		if (AirDrops[i].airdropid == airdrop_id)AirDropInd = i;

	if (AirDropInd < 0 || players[player].fOpeningTime > 0.f || GetDistance(players[player].vPosition, AirDrops[AirDropInd].vPosition) > 2.f)return;
	if (ServerTime - AirDrops[AirDropInd].ClockBegin < AIRDROP_FALLINGTIME)return;
	players[player].iOpeningAirdrop = airdrop_id;
	players[player].fOpeningTime = AIRDROP_OPENTIME;
}



bool dc_match::OverChest()
{
	auto V = map.cursor_to_world(players[camera_follows].vPosition.x, players[camera_follows].vPosition.y, camera_width);
	//auto mx = players[camera_follows].vPosition.x;
	
	//auto my = players[camera_follows].vPosition.y;
	auto mx = V.x;
	auto my = V.y;
	auto width = camera_width;
	float height = width*g_Resolution.y / g_Resolution.x;
	sf::Vector2f blocksize((float)(g_Resolution.x) / width, (float)(g_Resolution.x) / width);
	float scale = (float)(blocksize.x) / 128;

	if (scale < 0.5f)return false;

	bool ret = false;
	for (int i = 0; i < map.chests.size(); i++)
	{
		auto ch = map.chests[i];
		if (ch.bOpen)continue;
		if (ch.vPosition.x > mx - 2 && ch.vPosition.x < mx  + 2 && ch.vPosition.y > my - 2 && ch.vPosition.y < my + 2)
		{
			float _x = mx - ch.vPosition.x;
			float _y = my - ch.vPosition.y;

			if (g_Mouse.IsBetween(g_Resolution.x / 2 - _x*blocksize.x, g_Resolution.y / 2 - _y*blocksize.y, 64 * scale, 64 * scale, g_Mouse.Coords.x, g_Mouse.Coords.y))
			{
				ret = true;
				if (g_Mouse.hasReleased())
				{
					PlayerOpenChest(0, i);
					return true;
				}
				dc_buttoninfo Binfo;
				Binfo.TYPE = 7;
				Binfo.chest_id = i;
				DrawButs.push_back(Binfo);
			}

		}
	}
	for (int i = 0; i < AirDrops.size(); i++)
	{
		auto ch = AirDrops[i];
		if (ServerTime - ch.ClockBegin < AIRDROP_FALLINGTIME)continue;
		if (ch.vPosition.x > mx - 2 && ch.vPosition.x < mx + 2 && ch.vPosition.y > my - 2 && ch.vPosition.y < my + 2)
		{
			float _x = mx - ch.vPosition.x+0.25f;
			float _y = my - ch.vPosition.y+0.25f;

			if (g_Mouse.IsBetween(g_Resolution.x / 2 - _x*blocksize.x, g_Resolution.y / 2 - _y*blocksize.y, 64 * scale, 64 * scale, g_Mouse.Coords.x, g_Mouse.Coords.y))
			{
				ret = true;
				if (g_Mouse.hasReleased())
				{
					PlayerOpenAirdrop(0, ch.airdropid);
					return true;
				}
				dc_buttoninfo Binfo;
				Binfo.TYPE = 9;
				Binfo.chest_id = i;
				DrawButs.push_back(Binfo);
			}

		}
	}
	return ret;
}

int dc_match::GetLowestPlayerID()
{

	for (int i = 0; i < 100; i++)if (players[i].iHealth > 0)return i;
	return 0;
}

int dc_match::GetAlivePlayers()
{
	int count = 0;
	for (int i = 0; i < 100; i++)if (players[i].iHealth > 0)count++;
	return count;
}



void dc_match::PlayerPickupItem(int player, int slot, int itemid)
{
	if (players[player].fFreeFallHeight > 0.f)return;
	auto &ch = map.items[itemid];

	if (ch.bOwned || GetDistance(players[player].vPosition, ch.vPosition) > 2.0f)return;
	//For consumables
	if(ch.IsConsumable())
	{
		auto fslot = players[player].hasFreeSlot();
		if (fslot != -1)
		{
			for (int i = 0; i < 5; i++)
			{
				if (!ch.bOwned 
					&& players[player].Items[i].bValidated 
					&& players[player].Items[i].IsConsumable() 
					&& players[player].Items[i].id == ch.id 
					&& players[player].Items[i].iBullets < players[player].Items[i].iMaxBullets)
				{
					int addpossible = players[player].Items[i].iMaxBullets - players[player].Items[i].iBullets;

					if (addpossible >= ch.iBullets)
					{
						players[player].Items[i].iBullets += ch.iBullets;
						ch.bOwned = true;
						
						//map.delete_items();
					}
					else
					{
						players[player].Items[i].iBullets = players[player].Items[i].iMaxBullets;
						ch.iBullets -= addpossible;
					}
				}
			}

			if (!ch.bOwned)
			{
				players[player].Items[fslot] = ch;
				ch.bOwned = true;
				
			}

		}
		//For consumables
		else
		{

			for (int i = 0; i < 5; i++)
			{
				if (!ch.bOwned
					&& players[player].Items[i].IsConsumable()
					&& players[player].Items[i].id == ch.id
					&& players[player].Items[i].iBullets < players[player].Items[i].iMaxBullets)
				{
					auto addpossible = players[player].Items[i].iMaxBullets - players[player].Items[i].iBullets;

					if (addpossible <= ch.iBullets)
					{
						players[player].Items[i].iBullets += addpossible;
						ch.iBullets -= addpossible;
						if (ch.iBullets == 0)
						{
							ch.bOwned = true;
							
						}
					}
					else
					{
						players[player].Items[i].iBullets += ch.iBullets;
						ch.iBullets = 0;
						ch.bOwned = true;
						
					}
				}
			}

			//if (ch.bOwned)map.delete_items();

		}

		


	}
	else
	{
		auto fslot = players[player].hasFreeSlot();
		if (fslot != -1)
		{
			players[player].Items[fslot] = ch;
			ch.bOwned = true;
			//map.delete_items();
		}
		
	}

	if (ch.bOwned)
	{
		//ConLog("\nDropped:", ch.GameIdx);
		Demo_SnapshotUpdateItemPickup(ch.GameIdx);
	}
}

bool dc_match::OverItem()
{
	//TODO: dropok ne essenek egymásra
	auto V = map.cursor_to_world(players[camera_follows].vPosition.x, players[camera_follows].vPosition.y, camera_width);
	//auto mx = players[camera_follows].vPosition.x;
	//auto my = players[camera_follows].vPosition.y;
	auto mx = V.x;
	auto my = V.y;
	
	auto width = camera_width;
	float height = width*g_Resolution.y / g_Resolution.x;
	sf::Vector2f blocksize((float)(g_Resolution.x) / width, (float)(g_Resolution.x) / width);
	float scale = (float)(blocksize.x) / 128;

	if (scale < 0.5f)return false;
	static dc_item st_item;


	if (GetKeyStatus(DCK_SHOOT,false))st_item.bValidated = false;

	
	int ID = -1;

	for (int i = 0; i < map.items.size(); i++)
	{
		auto &ch = map.items[i];

		if (GetDistance(players[camera_follows].vPosition,ch.vPosition))
		{
			float _x = mx - ch.vPosition.x;
			float _y = my - ch.vPosition.y;
			float _ox, _oy;
			if (ID == -1)
			{
				_ox = mx - map.items[0].vPosition.x;
				_oy = my - map.items[0].vPosition.y;
			}
			else
			{
				_ox = mx - map.items[ID].vPosition.x;
				_oy = my - map.items[ID].vPosition.y;
			}


			if (g_Mouse.IsBetween(g_Resolution.x / 2 - _x*blocksize.x, g_Resolution.y / 2 - _y*blocksize.y, 32 * scale, 32 * scale, g_Mouse.Coords.x, g_Mouse.Coords.y))
			{
				if (GetDistance(sf::Vector2f(g_Resolution.x / 2 - _x*blocksize.x + scale * 16, g_Resolution.y / 2 - _y*blocksize.y + scale * 16), sf::Vector2f(g_Mouse.Coords.x, g_Mouse.Coords.y))
					<= GetDistance(sf::Vector2f(g_Resolution.x / 2 - _ox*blocksize.x + scale * 16, g_Resolution.y / 2 - _oy*blocksize.y + scale * 16), sf::Vector2f(g_Mouse.Coords.x, g_Mouse.Coords.y)))
					ID = i;
			}
		}
	}

	if (ID != -1)
	{



		auto &ch = map.items[ID];
		float _x = mx - ch.vPosition.x;
		float _y = my - ch.vPosition.y;

		if (g_Mouse.IsBetween(g_Resolution.x / 2 - _x*blocksize.x, g_Resolution.y / 2 - _y*blocksize.y, 32 * scale, 32 * scale, g_Mouse.Coords.x, g_Mouse.Coords.y))
		{
			_Window::RenderOverlay(g_Resolution.x / 2 - _x*blocksize.x, g_Resolution.y / 2 - _y*blocksize.y, 32 * scale, 32 * scale, 255, 255, 255, 48);

			if (g_Mouse.hasReleased())
			{
				if (GetKeyStatus(DCK_ALTERNATIVE, true))PlayerDropWeapon(0, players[0].iSelectedWeapon);
				PlayerPickupItem(0, 0, ID);
				return true;
			}
			dc_buttoninfo Binfo;
			Binfo.TYPE = 8;
			Binfo.WeaponListIndex = map.items[ID].ListIndex;
			Binfo.WeaponBullets = map.items[ID].iBullets;
			DrawButs.push_back(Binfo);

		}
		return true;
	}
	return false;
}

void dc_match::PlayerMove(int player, float angle)
{
	players[player].bMoved = true;
	if (players[player].fFreeFallHeight > 0.f)
	{
		auto diff = timeDiffSinceLastFrame;
		auto neededvelocity = angle2vec(angle)*UNIT_FREEFALL_SPEED;
		auto remainingvelocity = neededvelocity - players[player].vVelocity;
		//players[player].vVelocity = (diff*neededvelocity + (UNIT_ACCEL_TIME - diff)*players[player].vVelocity) / UNIT_ACCEL_TIME;
		players[player].vVelocity += (remainingvelocity * diff / (UNIT_ACCEL_TIME));
	}
	else
	{
		auto diff = timeDiffSinceLastFrame;
		auto neededvelocity = angle2vec(angle)*UNIT_RUN_SPEED;

		if (map.is_on_map(sf::Vector2i(players[player].vPosition))
			&& (map.lines[players[player].vPosition.y].blocks[players[player].vPosition.x].iTexture == 29 || map.lines[players[player].vPosition.y].blocks[players[player].vPosition.x].iTexture == 6))
			neededvelocity *= (UNIT_RUN_SPEED_WATER / UNIT_RUN_SPEED);
		if (players[player].fReloadDelay > 0.f)neededvelocity *= UNIT_RELOAD_SPEED_MULT;
		auto remainingvelocity = neededvelocity- players[player].vVelocity;
		//players[player].vVelocity = (diff*neededvelocity + (UNIT_ACCEL_TIME - diff)*players[player].vVelocity) / UNIT_ACCEL_TIME;
		players[player].vVelocity += (remainingvelocity * diff / (UNIT_ACCEL_TIME+players[player].GetCurrentWeaponWeight()));
	}
}



void dc_match::ControlInventory()
{
	float boxsize = 0.11f*g_Resolution.y;
	auto skale = (float)boxsize / 64.f;

	if (players[0].iHealth <= 0)return;
	ControlMove();
	for (int i = 0; i < 5; i++)
	{
		if (g_Mouse.hasJustClicked(false))
		{
			if (g_Mouse.IsBetween(g_Resolution.x - boxsize * 6 + i *boxsize*1.2, g_Resolution.y - boxsize - g_Resolution.x*0.01f, boxsize, boxsize, g_Mouse.Coords.x, g_Mouse.Coords.y))
			{
				if (weapon_selected_to_swap == -1 && players[0].Items[i].bValidated)weapon_selected_to_swap = i;
			}
		}
		else if (g_Mouse.hasReleased(false))
		{
			if (g_Mouse.IsBetween(0, 0, g_Resolution.x - boxsize * 6 - g_Resolution.x*0.02f, g_Resolution.y, g_Mouse.Coords.x, g_Mouse.Coords.y))
			{
				if (weapon_selected_to_swap == i)
				{
					PlayerDropWeapon(0, i);
					weapon_selected_to_swap = -1;
				}
			}
			else if (g_Mouse.IsBetween(g_Resolution.x - boxsize * 6 + i *boxsize*1.2, g_Resolution.y - boxsize - g_Resolution.x*0.01f, boxsize, boxsize, g_Mouse.Coords.x, g_Mouse.Coords.y))
			{
				if (weapon_selected_to_swap != -1 && weapon_selected_to_swap != i)
				{
					PlayerSwapWeaponInventory(0, weapon_selected_to_swap, i);

					/*					if (players[0].Items[i].IsConsumable() 
						&& players[0].Items[weapon_selected_to_swap].IsConsumable() 
						&& players[0].Items[weapon_selected_to_swap].ListIndex == players[0].Items[i].ListIndex 
						&& players[0].Items[i].iBullets != players[0].Items[i].iMaxBullets)
					{
						auto addpossible = players[0].Items[i].iMaxBullets - players[0].Items[i].iBullets;
						if (addpossible >= players[0].Items[weapon_selected_to_swap].iBullets)
						{
							players[0].Items[i].iBullets += addpossible;
							players[0].Items[weapon_selected_to_swap].iBullets -= addpossible;
							players[0].Items[weapon_selected_to_swap].bValidated = false;
						}
						else
						{
							players[0].Items[i].iBullets += addpossible;
							players[0].Items[weapon_selected_to_swap].iBullets -= addpossible;
						}

					}
					else
					{
						auto A = players[0].Items[i];
						players[0].Items[i] = players[0].Items[weapon_selected_to_swap];
						players[0].Items[weapon_selected_to_swap] = A;

						if (players[0].iSelectedWeapon == weapon_selected_to_swap)players[0].iSelectedWeapon = i;
					}*/
				}
				weapon_selected_to_swap = -1;
			}
			
		}
	}
	if(g_Mouse.hasReleased(false))				weapon_selected_to_swap = -1;
}

void dc_match::ControlMinimap(float timediff)
{
	if (players[0].bOnBus)
	{
		if(GetKeyStatus(DCK_JUMPOFFBUS,false))PlayerJumpOffBus(0);
	}
	else if (players[0].fFreeFallHeight > 0)
	{
		if (GetKeyStatus(DCK_DESCEND,true))	PlayerDescent(0, timediff, 6.f);
	}

	if (GetKeyStatus(DCK_MARKERPLACE, false))
	{

		float scale = (float)g_Resolution.x / 2000.f;
		if (g_Mouse.IsBetween(g_Resolution.x*0.25, g_Resolution.y*0.5 - g_Resolution.x*0.25, 0.5f*g_Resolution.x, 0.5f*g_Resolution.x, g_Mouse.Coords.x, g_Mouse.Coords.y))
		{
			auto X = (g_Mouse.Coords.x - g_Resolution.x*0.25) / (0.5f*g_Resolution.x) * 1000;
			auto Y = (g_Mouse.Coords.y - (g_Resolution.y*0.5 - g_Resolution.x*0.25)) / (0.5f*g_Resolution.x) * 1000;

			PlayerMarker[0] = sf::Vector2f(X, Y);

			if (players[0].iHealth <= 0)
			{
				if (GetKeyStatus(DCK_ALTERNATIVE,true))
				{
					int closestid = 1;
					for (int i = 1; i < 100; i++)
					{
						if (players[i].iHealth <= 0)continue;
						if (GetDistance(PlayerMarker[0], players[i].vPosition) < GetDistance(PlayerMarker[0], players[closestid].vPosition))closestid = i;
					}
					camera_follows = closestid;
				}
			}
			else if (g_Config.gm_cheats.Value >= 1.f && g_Config.ch_teleportmarker.Value >= 1.f)
			{
				players[0].vPosition = sf::Vector2f(X, Y);
			}

		}
	}
	else if (GetKeyStatus(DCK_MARKERREMOVE,true))
	{
		PlayerMarker[0] = sf::Vector2f(-1, -1);
	}

	if(players[0].iHealth > 0)
		ControlMove();

}

void dc_match::ControlMove()
{
	if (players[0].bOnBus)return;
	bool _W = GetKeyStatus(DCK_UP,true), _S = GetKeyStatus(DCK_DOWN, true), _A = GetKeyStatus(DCK_LEFT, true), _D = GetKeyStatus(DCK_RIGHT, true);

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
		bool anglecontrol = (g_Config.p_movement_type.Value >= 1.f);
		if (GetKeyStatus(DCK_ALTERNATIVE, true))anglecontrol = !anglecontrol;
		if (anglecontrol)
			PlayerMove(0, players[0].fAngle - adif);
		else
			PlayerMove(0, 90 - adif);

	}
}


void dc_match::Control(float timediff)
{
	if (LockInput)return;
	if (GetKeyStatus(DCK_OPENINVENTORY, false)) {
		show_inventory = !show_inventory;
		show_minimap = false;
	}
	if (show_inventory)
	{
		if (GetKeyStatus(DCK_CLOSEMENU,true))show_inventory = false;
		if (players[0].iHealth <= 0)return;
		ControlInventory();
	}
	else if (show_minimap)
	{
		if (GetKeyStatus(DCK_CLOSEMENU, true))show_minimap = false;
		ControlMinimap(timediff);
	}
	else
	{
		if (players[0].iHealth <= 0)return;
		//players[0].fAngle = atan2f(g_Mouse.Coords.y - g_Resolution.y / 2,- g_Mouse.Coords.x - g_Resolution.x / 2);
		players[0].fAngle = vec2angle(g_Mouse.Coords.x - g_Resolution.x / 2, -(g_Mouse.Coords.y - g_Resolution.y / 2));

		//ConLog("\n%d | %d     --->  %.2f", g_Mouse.Coords.x - g_Resolution.x / 2, -(g_Mouse.Coords.y - g_Resolution.y / 2), players[0].fAngle);

		ControlMove();

		if (GetKeyStatus(DCK_DROPITEM, false))PlayerDropWeapon(0, players[0].iSelectedWeapon);

		bool oc = OverChest();
		bool oi = OverItem();

		bool can_shoot = !(oc || oi);


		for (int i = 0; i < 5; i++)
		{
			if (GetKeyStatus(DCK_SLOT1+i, true))PlayerSwapWeapon(0, i);
		}

		int boxsize = g_Resolution.y*0.11f;
		/*for (int i = 0; i < 5; i++)
		{
			if (g_Mouse.IsBetween(g_Resolution.x - boxsize * 6 + i *boxsize*1.2, g_Resolution.y - boxsize - g_Resolution.x*0.01f, boxsize, boxsize, g_Mouse.Coords.x, g_Mouse.Coords.y))
			{
				if (g_Mouse.hasReleased() && g_Mouse.IsClickValid())
				{
					//PlayerDropWeapon(0, i);

				}
			}
		}*/

		if (players[0].Items[players[0].iSelectedWeapon].bAuto)
		{
			if (GetKeyStatus(DCK_SHOOT,true) && can_shoot)
			{
				PlayerShootWeapon(0);
			}
		}
		

		else if (GetKeyStatus(DCK_SHOOT, false) && can_shoot)
			PlayerShootWeapon(0);

		if (GetKeyStatus(DCK_RELOAD,true))PlayerReloadWeapon(0);

		if (players[0].bOnBus)
		{
			if (GetKeyStatus(DCK_JUMPOFFBUS, false))PlayerJumpOffBus(0);
		}
		else if (players[0].fFreeFallHeight > 0)
		{
			if (GetKeyStatus(DCK_DESCEND, true))	PlayerDescent(0, timediff, 6.f);
		}
	}
}


void DistinctBotLoop(dc_match* M, float diff)
{
	for (int i = 1; i < 100; i++)
	{
		if (M->players[i].iHealth <= 0)continue;
		M->BotThink(i, diff);
	}

}


void dc_match::AddGunShotSound(int listid, sf::Vector2f orp)
{
	float Volume = g_Config.mastervolume.Value*100.f;
	float DefModi = g_RandomDevice.RandomFloat(0.9f, 1.0f);
	DefModi *= g_Items[listid].fVolumeMulti;
	g_Sounds.AddNewSound(g_Items[listid].iSoundID, g_Items[listid].fAudibleDistance, orp, Volume, players[camera_follows].vPosition,DefModi);
}

void dc_match::SimulateFootsteps()
{
	float Volume = 100.f*g_Config.mastervolume.Value;
	for (int i = 0; i < 100; i++)
	{
		if (players[i].iHealth <= 0)continue;
		float DefModi = 0.4f;
		if (i == camera_follows)DefModi = 0.05f;

		if (players[i].DistanceTillNextFootStep < 0.f)
		{
			if (!map.is_on_map(sf::Vector2i(players[i].vPosition.x, players[i].vPosition.y)))

			{
				players[i].DistanceTillNextFootStep = 0.f;
				continue;
			}
			switch (map.lines[players[i].vPosition.y].blocks[players[i].vPosition.x].iTexture)
			{
			case 0:
			case 25:
			case 26:
			case 27:
			case 28:
			case 30:
			case 31:
			case 44:
			{

				players[i].DistanceTillNextFootStep += UNIT_FOOTSTEPSIZEGRASS*g_RandomDevice.RandomFloat(0.9, 1.1);
				if (Random(1, 100) <= 50)
					g_Sounds.AddNewSound(0, FOOTSTEP_AUDIODISTANCE, players[i].vPosition, Volume, players[camera_follows].vPosition, DefModi);
				else
					g_Sounds.AddNewSound(1, FOOTSTEP_AUDIODISTANCE, players[i].vPosition, Volume, players[camera_follows].vPosition, DefModi);
				break;
			}

			case 1:
			case 2:
			case 8:
			case 19:
			case 20:
			case 21:
			case 22:
			case 23:
			case 24:
			{
				players[i].DistanceTillNextFootStep += UNIT_FOOTSTEPSIZEWOOD*g_RandomDevice.RandomFloat(0.9, 1.1);
				if (Random(1, 100) <= 50)
					g_Sounds.AddNewSound(2, FOOTSTEP_AUDIODISTANCE, players[i].vPosition, Volume, players[camera_follows].vPosition, DefModi);
				else
					g_Sounds.AddNewSound(3, FOOTSTEP_AUDIODISTANCE, players[i].vPosition, Volume, players[camera_follows].vPosition, DefModi);
				break;
			}
			case 13:
			case 32:
			case 9:
			case 62:
			case 63:
			{
				players[i].DistanceTillNextFootStep += UNIT_FOOTSTEPSIZESAND*g_RandomDevice.RandomFloat(0.9, 1.1);
				if (Random(1, 100) <= 50)
					g_Sounds.AddNewSound(4, FOOTSTEP_AUDIODISTANCE, players[i].vPosition, Volume, players[camera_follows].vPosition, DefModi);
				else
					g_Sounds.AddNewSound(5, FOOTSTEP_AUDIODISTANCE, players[i].vPosition, Volume, players[camera_follows].vPosition, DefModi);
				break;
			}
			case 14:
			case 49:
			case 64:
			case 65:
			case 66:
			{
				players[i].DistanceTillNextFootStep += UNIT_FOOTSTEPSIZESNOW*g_RandomDevice.RandomFloat(0.9, 1.1);
				if (Random(1, 100) <= 50)
					g_Sounds.AddNewSound(6, FOOTSTEP_AUDIODISTANCE, players[i].vPosition, Volume, players[camera_follows].vPosition, DefModi);
				else
					g_Sounds.AddNewSound(7, FOOTSTEP_AUDIODISTANCE, players[i].vPosition, Volume, players[camera_follows].vPosition, DefModi);
				break;
			}
			case 15:
			case 16:
			case 17:
			case 18:
			case 33:
			case 34:
			case 7:
			case 10:
			case 11:
			case 12:
			case 35:
			case 36:
			case 37:
			case 38:
			case 39:
			case 40:
			case 41:
			case 42:
			case 43:
			case 60:
			case 61:
			{
				players[i].DistanceTillNextFootStep += UNIT_FOOTSTEPSIZETILE*g_RandomDevice.RandomFloat(0.9, 1.1);
				if (Random(1, 100) <= 50)
					g_Sounds.AddNewSound(8, FOOTSTEP_AUDIODISTANCE, players[i].vPosition, Volume, players[camera_follows].vPosition, DefModi);
				else
					g_Sounds.AddNewSound(9, FOOTSTEP_AUDIODISTANCE, players[i].vPosition, Volume, players[camera_follows].vPosition, DefModi);
				break;
			}
			case 45:
			case 46:
			case 47:
			case 48:
			case 59:
			{
				players[i].DistanceTillNextFootStep += UNIT_FOOTSTEPSIZEMETAL*g_RandomDevice.RandomFloat(0.9, 1.1);
				if (Random(1, 100) <= 50)
					g_Sounds.AddNewSound(10, FOOTSTEP_AUDIODISTANCE, players[i].vPosition, Volume, players[camera_follows].vPosition, DefModi);
				else
					g_Sounds.AddNewSound(11, FOOTSTEP_AUDIODISTANCE, players[i].vPosition, Volume, players[camera_follows].vPosition, DefModi);
				break;
			}
			case 6:
			case 29:
			{
				players[i].DistanceTillNextFootStep += UNIT_FOOTSTEPSIZEWATER*g_RandomDevice.RandomFloat(0.9, 1.1);
				if (Random(1, 100) <= 50)
					g_Sounds.AddNewSound(12, FOOTSTEP_AUDIODISTANCE, players[i].vPosition, Volume, players[camera_follows].vPosition, DefModi);
				else
					g_Sounds.AddNewSound(13, FOOTSTEP_AUDIODISTANCE, players[i].vPosition, Volume, players[camera_follows].vPosition, DefModi);
				break;
			}
			default:
			{
				players[i].DistanceTillNextFootStep += UNIT_FOOTSTEPSIZETILE*g_RandomDevice.RandomFloat(0.9, 1.1);
				if (Random(1, 100) <= 50)
					g_Sounds.AddNewSound(8, FOOTSTEP_AUDIODISTANCE, players[i].vPosition, Volume, players[camera_follows].vPosition, DefModi);
				else
					g_Sounds.AddNewSound(9, FOOTSTEP_AUDIODISTANCE, players[i].vPosition, Volume, players[camera_follows].vPosition, DefModi);
				break;
			}
			}





		}
		//printf("\n%d Dist: %f || Numbero Sounds: %d", i, players[i].DistanceTillNextFootStep, g_Sounds.SoundContainer.size());
	}
}

void dc_match::LoopPlayers()
{

	int playercount = GetAlivePlayers();

	static dc_clock clock;
	auto diff = timeDiffSinceLastFrame;
	clock.Update();
	for (int i = 0; i < 100; i++)
	{
		if (players[i].iHealth <= 0)continue;
		if (players[i].fFreeFallHeight > 0)PlayerDescent(i, diff, 1.5f); //Automatic descend

		players[i].SimulateSlurp(diff); //For healing
		CheckCollisions(i, diff);
		players[i].vPosition.x += players[i].vVelocity.x * diff;
		players[i].vPosition.y -= players[i].vVelocity.y * diff; //This is inverted

		if (players[i].fFreeFallHeight <= 0.f) {
			auto l = GetLength(players[i].vVelocity*diff); //length of how much they moved
			players[i].DistanceTillNextFootStep -= l; //For footstep sounds
			players[i].Stats.fDistanceWalked += l;

			
			if (!players[i].bOnBus && players[i].Stats.LandingPosition == sf::Vector2f(-1.f, -1.f))
				players[i].Stats.LandingPosition = players[i].vPosition; //If there is no landing position, andd they are on land, we set the first landing position
		}
		players[i].bMoved = false; //We reset the bMoved, because it is inrelevant without input in this frame

		if(players[i].fFreeFallHeight <= 0.f)
		players[i].Stats.fTimeAlive += diff; //Time alive only counts after a unit landed


		if (players[i].CalculateVelocity() > 2.f) //Too fast movement will make the spreaad bigger, and cancel healing, spread reducing is calculated with moving bloom decrease
		{
			if (players[i].Items[players[i].iSelectedWeapon].bValidated)players[i].fBloomSize -= (players[i].Items[players[i].iSelectedWeapon].fBloomMovingDecrease * diff);
			if (players[i].Items[players[i].iSelectedWeapon].bValidated && players[i].fBloomSize < players[i].Items[players[i].iSelectedWeapon].fBloomMovingMinSize)
				players[i].fBloomSize = players[i].Items[players[i].iSelectedWeapon].fBloomMovingMinSize;



			players[i].fHealTime = 0.f;
		}
		else //spread reducing is calculated with standing bloom decrease
		{
			if (players[i].Items[players[i].iSelectedWeapon].bValidated)players[i].fBloomSize -= (players[i].Items[players[i].iSelectedWeapon].fBloomStandingDecrease * diff);

			if (players[i].Items[players[i].iSelectedWeapon].bValidated && players[i].fBloomSize < players[i].Items[players[i].iSelectedWeapon].fBloomMinSize)
				players[i].fBloomSize = players[i].Items[players[i].iSelectedWeapon].fBloomMinSize;

		}

		//Setting the min limit of bloom in case it gets lower
		if (players[i].fBloomSize < players[i].Items[players[i].iSelectedWeapon].fBloomMinSize)players[i].fBloomSize = players[i].Items[players[i].iSelectedWeapon].fBloomMinSize;
		if (players[i].fBloomSize > players[i].Items[players[i].iSelectedWeapon].fBloomMaxSize)players[i].fBloomSize = players[i].Items[players[i].iSelectedWeapon].fBloomMaxSize;

		//Auto-reload if there is no more bullets in the weapon
		if (players[i].GetCurrentWeapon().bValidated && !players[i].GetCurrentWeapon().IsConsumable() && players[i].Items[players[i].iSelectedWeapon].iBullets <= 0 && players[i].fReloadDelay <= 0.f)
		{
			players[i].fReloadDelay = players[i].Items[players[i].iSelectedWeapon].fReloadTime;
		}

		//In case the unit is opening something
		if (players[i].iOpeningChest != -1 || players[i].iOpeningAirdrop != -1)
		{
			players[i].fOpeningTime -= diff;
			if (players[i].fOpeningTime < 0.f) //This means that it has been opened
			{
				if (players[i].iOpeningChest != -1)
				{
					if (GetDistance(players[i].vPosition, map.chests[players[i].iOpeningChest].vPosition) >= 2.f)
					{
						players[i].iOpeningChest = -1;
					}

					//Checking if the chest hasn't been opened by another unit, and if it's still in range
					if (players[i].iOpeningChest != -1 && !map.chests[players[i].iOpeningChest].bOpen) 
					{
						map.chests[players[i].iOpeningChest].bOpen = true;
						dc_item weapon, heal; //In a chest we want to spawn a weapon and a consumable
						auto pos = map.chests[players[i].iOpeningChest].vPosition;
						weapon.id = 10000; heal.id = 0;
						//TODO: Remove the weapon
						while (weapon.IsConsumable()) // should have used do-while 
						{
							int r = weapon.GetRandomWeaponID();
							pos = map.chests[players[i].iOpeningChest].vPosition + sf::Vector2f(-RandFloat()*0.25f, RandFloat()*0.5f - 0.25f);
							weapon.create(r, pos);
							//weapon.vPosition = pos;
						}
						weapon.GameIdx = TotalItems; TotalItems++;
						Demo_SnapshotUpdateItemSpawn(weapon.GameIdx, weapon.ListIndex, weapon.vPosition);
						Demo_SnapshotUpdateItemDrop(weapon.GameIdx,weapon.vPosition);
						map.items.push_back(weapon);
						while (!heal.IsConsumable()) // should have used do-while
						{
							int r = heal.GetRandomWeaponID();
							pos = map.chests[players[i].iOpeningChest].vPosition + sf::Vector2f(RandFloat()*0.25f, RandFloat()*0.5f - 0.25f);
							heal.create(r, pos);
							//heal.vPosition = pos;
						}

						heal.GameIdx = TotalItems; TotalItems++;
						Demo_SnapshotUpdateItemSpawn(heal.GameIdx, heal.ListIndex, heal.vPosition);
						Demo_SnapshotUpdateItemDrop(heal.GameIdx,heal.vPosition);
						map.items.push_back(heal);
						players[i].Stats.Chests.push_back(players[i].iOpeningChest);
						Demo_SnapshotUpdateChest(players[i].iOpeningChest);
					}
				}
				else if (players[i].iOpeningAirdrop != -1)
				{
					int AirDropInd = -1;
					for (int j = 0; j < AirDrops.size(); j++)
					{
						if (AirDrops[j].airdropid == players[i].iOpeningAirdrop)AirDropInd = j;
					}

					if (GetDistance(players[i].vPosition, AirDrops[AirDropInd].vPosition) >= 2.f)
					{
						AirDropInd = -1;
						players[i].iOpeningAirdrop = -1;
					}
					if (AirDropInd != -1)
					{
						auto pos = AirDrops[AirDropInd].vPosition;
						Demo_SnapshotUpdateAirdropRemove(AirDrops[AirDropInd].airdropid);
						AirDrops.erase(AirDrops.begin() + AirDropInd);
						dc_item Items[5];

						

						for (int j = 0; j < 5; j++)
						{
							//For an airdrop, we spawn 2 heals, and 3 legendary or better weapons
							if (j <= 1)
							{
								Items[j].id = 10000;
								int r = Items[j].GetRandomWeaponID();
								while (Items[j].IsConsumable() || Items[j].iRarity < 4)
								{
									int r = Items[j].GetRandomWeaponID();
									Items[j].create(r, pos+0.5f*angle2vec(j*72.f));
								}
							}
							else
							{
								Items[j].id = 0;
								int r = Items[j].GetRandomWeaponID();
								while (!Items[j].IsConsumable() || Items[j].iRarity < 0)
								{
									int r = Items[j].GetRandomWeaponID();
									Items[j].create(r, pos + 0.5f*angle2vec(j*72.f));
								}
							}

							Items[j].GameIdx = TotalItems; TotalItems++;
							Demo_SnapshotUpdateItemSpawn(Items[j].GameIdx, Items[j].ListIndex, Items[j].vPosition);
							Demo_SnapshotUpdateItemDrop(Items[j].GameIdx, Items[j].vPosition);
							map.items.push_back(Items[j]);
						}
					}
				}
				players[i].iOpeningChest = -1;
				players[i].iOpeningAirdrop = -1;
			}
		}
		//Reducing some delays
		else if (players[i].fPulloutDelay > 0.f)
		{
			players[i].fPulloutDelay -= diff;
		}
		else if (players[i].fReloadDelay > 0.f)
		{
			players[i].fReloadDelay -= diff;
			//If the reload delay is over, and the reload method is Full-Magazine
			if (players[i].fReloadDelay <= 0.f && players[i].GetCurrentWeapon().iReloadMethod == 1) 
			{
				players[i].Items[players[i].iSelectedWeapon].iBullets = players[i].Items[players[i].iSelectedWeapon].iMaxBullets;
			}
			//If the reload delay is over, and the reload method is One-Bullet
			else if (players[i].fReloadDelay <= 0.f && players[i].GetCurrentWeapon().iReloadMethod == 2)
			{
				players[i].Items[players[i].iSelectedWeapon].iBullets++;
				//Continuing reloading if the mag is not full
				if (players[i].Items[players[i].iSelectedWeapon].iBullets < players[i].Items[players[i].iSelectedWeapon].iMaxBullets)
					players[i].fReloadDelay += players[i].GetCurrentWeapon().fReloadTime;
			}
		}
		if (players[i].fShootDelay > 0.f)
			players[i].fShootDelay -= diff;
		if (players[i].fFSADelay > 0.f)
			players[i].fFSADelay -= diff;
		if (players[i].fHealTime > 0.f && players[i].GetCurrentWeapon().bValidated)
		{
			players[i].fHealTime -= diff;
			if (players[i].fHealTime <= 0.f )
			{
				int healtype = players[i].Items[players[i].iSelectedWeapon].iType - 4;
				int healamount = players[i].Items[players[i].iSelectedWeapon].iHealAmount;
				int healmax = players[i].Items[players[i].iSelectedWeapon].iHealMax;

				if (healtype == 0)
				{
					if (healmax > players[i].iHealth)
					{
						players[i].iHealth += healamount;
						if (players[i].iHealth > healmax)players[i].iHealth = healmax;
						players[i].Items[players[i].iSelectedWeapon].iBullets--;
					}
				}
				else if (healtype == 1)
				{
					if (healmax > players[i].iShield)
					{
						players[i].iShield += healamount;
						if (players[i].iShield > healmax)players[i].iShield = healmax;
						players[i].Items[players[i].iSelectedWeapon].iBullets--;
					}
				}
				else
				{
					dc_slurptypeheal H;
					H.fHealRate = players[i].GetCurrentWeapon().fHealRateProgressive;
					H.fHealTimeLeft = 0.f;
					H.healLeft = healamount;

					players[i].SlurpContainer.push_back(H);
					players[i].Items[players[i].iSelectedWeapon].iBullets--;
				}

				if (players[i].Items[players[i].iSelectedWeapon].iBullets <= 0)players[i].Items[players[i].iSelectedWeapon].bValidated = false;
			}
		}
		else if (players[i].fHealTime > 0.f)players[i].fHealTime = 0.f;
		
		//Damaging if the player is in storm
		//Damaging only starts if the unit has been in storm for more than a second
		if (IsPointInStorm(players[i].vPosition))
		{
			players[i].StormSpentTime += diff;
			if (players[i].StormSpentTime > 1.f)
			{
				players[i].StormSpentTime -= 1.f;
				players[i].Damage(GetCurrentStormDamage(),true);
				//If the unit dies to storm
				if (players[i].iHealth <= 0)
				{
					//If the unit hasn't taken damage for 15 seconds
					if (players[i].gothitLastClock.deltaTime() > 1000.f*KILL_OWNERTIME)
					{
						dc_killnoticeeffect kl;
						kl.clockBegin = ServerTime;
						sprintf(kl.message, "%s was lost to storm", players[i].szName);
						kl.Killer = i;
						kl.Target = i;
						effects.kilnot_effects.push_back(kl);
					}
					//If the unit has taken damage in the last 15 seconds, that means, that the elimination goes to the previous person who shot them
					else
					{
						players[players[i].gotHitLastPlayerID].Stats.iEliminations++;
						dc_killnoticeeffect kl;
						kl.clockBegin = ServerTime;
						sprintf(kl.message, "%s eliminated %s with the storm", players[players[i].gotHitLastPlayerID].szName,players[i].szName);
						kl.Killer = players[i].gotHitLastPlayerID;
						kl.Target = i;
						effects.kilnot_effects.push_back(kl);
						if (camera_follows == i)camera_follows = players[i].gotHitLastPlayerID;
					}
				}
			}
		}
		else
		{
			players[i].StormClock.Update();
			players[i].StormSpentTime = 0.f;
		}	
		//This one is for challenge progress
		//Checking if the player is in any named location
		PlayerCheckCurrentLocationForData(i);
	}
	for (int i = 0; i < 100; i++)
	{
		//0 is for the player, they are controlled in an unique way
		if (i == 0)Control(diff);
		else if (players[i].iHealth> 0) {
			//If cheats enabled, and bot_stop is > 1, bot's are frozen
			//Otherwise they act
			if(g_Config.ch_bot_stop.Value < 1.f || g_Config.gm_cheats.Value < 1.f)BotThink(i, diff);

		}
		if (players[i].iHealth > 0 && !players[i].bMoved) //If the unit hasn't moved, we slow them down in a smooth way
		{

			players[i].vVelocity.x = players[i].vVelocity.x * pow(UNIT_SLOWDOWN_FACTOR, diff * 1000);
			players[i].vVelocity.y = players[i].vVelocity.y * pow(UNIT_SLOWDOWN_FACTOR, diff * 1000);

		}

	}

	//When the game is close to end, we check for it
	if (playercount <= 5)FinishMatch();
}

void dc_match::ScrollMap()
{
	if (LockInput)return;
	camera_width *= pow(1.1, -g_Mouse.scroll);
	if (camera_width < 10)camera_width = 10;
	else if (camera_width > 50)camera_width = 50;
}

void dc_match::DoCheatStuff()
{
	if (g_Config.gm_cheats.Value < 1.f)return;
	if (g_Keyboard.keys[VK_F2]) {
		players[0].iHealth = 100; players[0].iShield = 100;
	}
	if (g_Keyboard.keys[VK_F3])players[0].iHealth = 0;
	if (g_Keyboard.hasJustPressed(VK_F1)) {
		players[camera_follows].iHealth = 0;
		PlayerKill(camera_follows);
	}
	if (GetAsyncKeyState(VK_F4))
	{
		players[1].iHealth = 100; players[1].iShield = 100;
		players[1].vPosition = sf::Vector2f(players[camera_follows].vPosition.x + Random(-5, 5), players[camera_follows].vPosition.y + Random(-5, 5));
		BotData[1].Changables.DistantTargetType = 0;
		//players[1].vPosition = sf::Vector2f(1001, 900);
	}

	if (g_Keyboard.hasJustPressed(VK_F5))
	{
		dc_item weapon;

		auto id = weapon.GetRandomWeaponID();
		players[0].Items[players[0].iSelectedWeapon].create(id, sf::Vector2f());


	}

	if (GetAsyncKeyState(VK_F6) & 1)
		GenerateStorms();

	int chs = 0;
	for (auto it : map.chests)if (!it.bOpen)chs++;

	static bool bTest = false;
	if (!bTest)
	{
		bTest = true;
		for (int i = 0; i < map.chests.size(); i++)
		{
			bool bB = map.chests[i].bOpen;
			//ConLog("\n#%d | (%.1f,%.1f) | Open: %d", i, map.chests[i].vPosition.x, map.chests[i].vPosition.y, bB);
		}
	}

	if (g_Config.ch_debug_info.Value >= 1.f)
	{
		char buf[64]; sprintf(buf, "Kills: %d\nAlive players: %d\nAvailable Chests: %d (%d)", players[camera_follows].Stats.iEliminations, GetAlivePlayers(), chs, map.chests.size());
		_Window::RenderTextB(0, 100, buf, 36);


		char plubuf[320];
		sprintf(plubuf, "Watching (%d) %s\nTargeting %d\nPosition: %.2f %.2f\nVelocity: %.2f %.2f", camera_follows, players[camera_follows].szName, 0, players[camera_follows].vPosition.x, players[camera_follows].vPosition.y, players[camera_follows].vVelocity.x, players[camera_follows].vVelocity.y);
		//if (BotData[camera_follows].move_path.size() > 0)
		sprintf(plubuf, "%s\nMoving to (%d): %.2f %.2f", plubuf, BotData[camera_follows].Changables.DistantTargetType, BotData[camera_follows].Changables.DistantTargetPoint.x, BotData[camera_follows].Changables.DistantTargetPoint.y);
		sprintf(plubuf, "%s\nleft chests: %d", plubuf, BotData[camera_follows].Changables.RestOfChests.size());
		sprintf(plubuf, "%s\n%d/%d %d/%d %d/%d %d/%d %d/%d", plubuf,
			GetIndex(BotData[camera_follows].WeaponPreferences[0], players[camera_follows].Items[0].ListIndex), BotData[camera_follows].GoodEnoughRanking[0],
			GetIndex(BotData[camera_follows].WeaponPreferences[1], players[camera_follows].Items[1].ListIndex), BotData[camera_follows].GoodEnoughRanking[1],
			GetIndex(BotData[camera_follows].WeaponPreferences[2], players[camera_follows].Items[2].ListIndex), BotData[camera_follows].GoodEnoughRanking[2],
			GetIndex(BotData[camera_follows].WeaponPreferences[3], players[camera_follows].Items[3].ListIndex), BotData[camera_follows].GoodEnoughRanking[3],
			GetIndex(BotData[camera_follows].WeaponPreferences[4], players[camera_follows].Items[4].ListIndex), BotData[camera_follows].GoodEnoughRanking[4]
		);
		sprintf(plubuf, "%s\nNoticed: %d, Targeting: %d", plubuf, BotData[camera_follows].Changables.NoticedPlayerIDs.size(), BotData[camera_follows].Changables.TargetedPlayerIDs.size());
		if (BotData[camera_follows].Changables.TargetedPlayerIDs.size() > 0)
		{
			sprintf(plubuf, "%s (Target: %d)", plubuf, BotData[camera_follows].Changables.TargetedPlayerIDs[0]);
		}

		_Window::RenderTextB(0, 320, plubuf, 20, 255, 255, 111, 255);
		if (GetAsyncKeyState(VK_F4))
		{
			auto id = GetClosestChestIDToPlayer(0);
			if (id != -1)
			{
				auto cord = sf::Vector2i(map.chests[id].vPosition.x, map.chests[id].vPosition.y);
				CreateSmallMovementMap(sf::Vector2i(players[camera_follows].vPosition.x, players[camera_follows].vPosition.y), sf::Vector2i(10, 10), cord);
			}
		}
	}
}

void dc_match::FinishMatch()
{
	if (GetAlivePlayers() > 1)return;
	bMatchEnded = 1;
	MatchEndClock.Update();
}

void dc_match::Do()
{
	static dc_clock Clock;
	if (Clock.deltaTime() > 500)Clock.Update(); //lag nullification
	
	if (bMatchEnded != 1)
	timeDiffSinceLastFrame = 0.001f*Clock.deltaTime();
	Clock.Update();


	p_bShouldUpdatelines = false;
	
	if(players[camera_follows].iHealth <= 0)
		camera_follows = GetLowestPlayerID();

	if (GetKeyStatus(DCK_SWAP_TO_OTHER_PLAYER,false))
	{
		if (camera_follows == 99)camera_follows = -1;
		for (int t = camera_follows+1; t < 100; t++)
		{
			camera_follows = t;
			if (players[t].iHealth > 0)
			{
				if (GetKeyStatus(DCK_ALTERNATIVE,true) && !players[t].bOnBus)break;
				else if (!GetKeyStatus(DCK_ALTERNATIVE,true))break;
			}

		}
	}

	
	if (players[0].iHealth > 0)camera_follows = 0;

	//Deleting items that have been picked up
	map.delete_items();
	ClearUnreachableItems();


	map.simulate_day();

	dc_match::DrawAll();
	SimulateBus();
	if(bMatchEnded != 1)
	LoopPlayers();
	SimulateFootsteps();
	SimulateAirdrops();
	g_Sounds.ManipulateAllSounds(g_Config.mastervolume.Value*100.f, players[camera_follows].vPosition);
	g_Sounds.ManipulateDynamicSounds(g_Config.mastervolume.Value*100.f, players[camera_follows].vPosition);

	ScrollMap();

	if (DemoRecord == 1)
	{
		Demo_LoopSnapshots();
		float TickLength = 1.f / DemoTickBase;
		while (ServerTime - lastTickTime > TickLength)
		{
			lastTickTime += TickLength;
			Demo_CreateSnapshot();
		}

	}

	if (GetKeyStatus(DCK_OPENMINIMAP,false)) { show_minimap = !show_minimap; show_inventory = false; }


	DoCheatStuff();



	ServerTime += timeDiffSinceLastFrame;
}