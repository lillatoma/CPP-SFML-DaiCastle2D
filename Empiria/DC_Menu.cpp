#include "DaiCastle.h"

char* WrapNames[8] = { "Default","White","Black","Misty","Gold","Inverted","Corrupted","Camouflage" };

char* SkinNames[] = { "Default","Camouflage","Red Arrow","Pac Monster","Basketball","Dark","Earth","Love","Superball","Radar" };

char* GliderNames[] = { "Default","Umbrella","Red Umbrella","Dark","Blue Arrow" };


void dc_game::DoMainMenu()
{
	//PLAY BUTTON
	if (g_Mouse.IsBetween(g_Resolution.x*0.75f, g_Resolution.y*0.8f, g_Resolution.x*0.2f, g_Resolution.y*0.1f, g_Mouse.Coords.x, g_Mouse.Coords.y) &&
		g_Mouse.IsClickValid() && g_Mouse.hasReleased())
		GM_STATE = 1;

	//GAMEMODE ARROWS
	float fontsize = 0.03f*g_Resolution.y;
	auto lineHeight = _Window::GetTextSize("a\n", fontsize).y - _Window::GetTextSize("a", fontsize).y;
	float scale = (1.f*lineHeight + g_Resolution.y*0.01f) / 64.f;

	if (g_Mouse.IsBetween(g_Resolution.x*0.75f, g_Resolution.y*0.78f - lineHeight, scale * 64, scale * 64, g_Mouse.Coords.x, g_Mouse.Coords.y) &&
		g_Mouse.IsClickValid() && g_Mouse.hasJustClicked())
		MatchType--;
	else if (g_Mouse.IsBetween(g_Resolution.x*0.95f - scale*32.f, g_Resolution.y*0.78f - lineHeight, scale * 32, scale * 64, g_Mouse.Coords.x, g_Mouse.Coords.y) &&
		g_Mouse.IsClickValid() && g_Mouse.hasReleased())
		MatchType++;

	if (MatchType < 0)MatchType = 1;
	else if (MatchType > 1)MatchType = 0;

	//PLAYERNAME
	if (g_Mouse.IsBetween(g_Resolution.x*0.75f, g_Resolution.y*0.1f, g_Resolution.x*0.2f, lineHeight + 4, g_Mouse.Coords.x, g_Mouse.Coords.y) &&
		g_Mouse.IsClickValid() && g_Mouse.hasJustClicked())
		bNameEditSelected = !bNameEditSelected;
	else if (!g_Mouse.IsBetween(g_Resolution.x*0.75f, g_Resolution.y*0.1f, g_Resolution.x*0.2f, lineHeight + 4, g_Mouse.Coords.x, g_Mouse.Coords.y) && g_Mouse.IsClickValid() && g_Mouse.hasJustClicked()
		|| g_Keyboard.keys[VK_ESCAPE] || g_Keyboard.keys[VK_RETURN] || OW_STATUS != 0)
		bNameEditSelected = false;

	int szLen = strlen(ThePlayer.szName);
	if (bNameEditSelected)g_Keyboard.UpdateText(ThePlayer.szName, &szLen, 64);

	//Statistics Button

	if (g_Mouse.IsBetween(0.75f*g_Resolution.x, g_Resolution.y*0.75f - lineHeight - (lineHeight + 4), 0.2f*g_Resolution.x, lineHeight + 4, g_Mouse.Coords.x, g_Mouse.Coords.y) &&
		g_Mouse.IsClickValid() && g_Mouse.hasReleased())GM_STATE = 2;


	//Replays Button
	if (g_Mouse.IsBetween(0.75f*g_Resolution.x, g_Resolution.y*0.75f - lineHeight - 2 * (lineHeight + 4) - 1, 0.2f*g_Resolution.x, lineHeight + 4, g_Mouse.Coords.x, g_Mouse.Coords.y) &&
		g_Mouse.IsClickValid() && g_Mouse.hasReleased())GM_STATE = 4;

	//Player on Left
	DoMainMenuCharacterVision();

	//LeftSideBar
	DoLeftSideMenubar();

}

void dc_game::DrawMainMenuBg()
{
	static dc_clock Clock;
	static int cIndex1 = -1, cIndex2 = -1;

	static sf::Texture txAdd, txMult;
	static sf::Sprite spAdd, spMult;

	static sf::Texture bgTex;
	static sf::Sprite bgSpr;


	static bool mvAdd, mvMult;
	static float speedAdd, speedMult;
	static float posAdd, posMult;

	float Scale = 0.00092592592f*g_Resolution.y;
	int RangeLeft = 0;
	int RangeRight = 5760 - Scale*g_Resolution.x;

	if (Cloud1Index == -1 || Cloud2Index == -1)
	{
		Cloud1Index = Random(55, 58);
		Cloud2Index = Random(55, 58);
		bgTex = *g_Textures.get(54);
		bgSpr.setTexture(bgTex);
	}

	if (cIndex1 != Cloud1Index || cIndex2 != Cloud2Index)
	{
		cIndex1 = Cloud1Index;
		cIndex2 = Cloud2Index;
		txAdd = *g_Textures.get(cIndex1);
		txMult = *g_Textures.get(cIndex2);
		spAdd.setTexture(txAdd);
		spMult.setTexture(txMult);
		mvAdd = Random(0, 1);
		mvMult = !mvAdd;
		speedAdd = g_RandomDevice.RandomFloat(20.f, 100.f);
		speedMult = g_RandomDevice.RandomFloat(20.f, 100.f);
		posAdd = Random(RangeLeft, RangeRight);
		posMult = Random(RangeLeft, RangeRight);
	}

	float diff = 0.001f*Clock.deltaTime();

	if (mvAdd)
	{
		posAdd += speedAdd*diff;
		if (posAdd > RangeRight)
		{
			posAdd = RangeRight;
			speedAdd = g_RandomDevice.RandomFloat(20.f, 100.f);
			mvAdd = !mvAdd;
		}
	}
	else
	{
		posAdd -= speedAdd*diff;
		if (posAdd < RangeLeft)
		{
			posAdd = RangeLeft;
			speedAdd = g_RandomDevice.RandomFloat(20.f, 100.f);
			mvAdd = !mvAdd;
		}
	}

	if (mvMult)
	{
		posMult += speedMult*diff;
		if (posMult > RangeRight)
		{
			posMult = RangeRight;
			speedMult = g_RandomDevice.RandomFloat(20.f, 100.f);
			mvMult = !mvMult;
		}
	}
	else
	{
		posMult -= speedMult*diff;
		if (posMult < RangeLeft)
		{
			posMult = RangeLeft;
			speedMult = g_RandomDevice.RandomFloat(20.f, 100.f);
			mvMult = !mvMult;
		}
	}

	Clock.Update();

	bgSpr.setScale(Scale, Scale);
	spAdd.setScale(Scale, Scale);
	spMult.setScale(Scale, Scale);

	g_Window->draw(bgSpr);

	sf::BlendMode additiveBlending = sf::BlendAdd;
	sf::BlendMode multiplyBlending = sf::BlendMultiply;

	spAdd.setTextureRect(sf::IntRect(posAdd, 0, (1.f / Scale)*g_Resolution.x, 1080));

	spMult.setTextureRect(sf::IntRect(posMult, 0, (1.f / Scale)*g_Resolution.x, 1080));
	spMult.setColor(sf::Color(255, 255, 255, 128));
	//printf("\nPosAdd: %d %d %f %d", posAdd, 0, (1.f/Scale)*g_Resolution.x , 1080);

	g_Window->draw(spMult, multiplyBlending);
	g_Window->draw(spAdd, additiveBlending);

}

void dc_game::DrawMainMenuPlayButton()
{
	static sf::Sprite logosSprite;
	static bool bRun = false;
	if (!bRun)
	{
		logosSprite.setTexture(*g_Textures.get(51));
		bRun = true;
	}

	//Text Above
	//TODO: All other gamemodes
	char* TextAbove[] = { "Solo","Arena Solo","Duo","Duo Fill","Trio","Trio Fill","Squad","Squad Fill","50v50" };
	{
		float fontsize = 0.03f*g_Resolution.y;
		auto lineHeight = _Window::GetTextSize("a\n", fontsize).y - _Window::GetTextSize("a", fontsize).y;
		auto Dim = _Window::GetTextSize(TextAbove[MatchType], g_Resolution.y*0.03f);
		_Window::RenderOverlay(g_Resolution.x*0.75f, g_Resolution.y*0.78f - lineHeight, g_Resolution.x*0.2f, lineHeight + g_Resolution.y*0.01f, 192, 192, 192, 64);
		_Window::RenderTextB(g_Resolution.x*0.85f - Dim.x*0.5f, g_Resolution.y*0.785f - lineHeight, TextAbove[MatchType], fontsize);

		float scale = (1.f*lineHeight + g_Resolution.y*0.01f) / 64.f;

		logosSprite.setPosition(g_Resolution.x*0.75f, g_Resolution.y*0.78f - lineHeight);
		logosSprite.setTextureRect(sf::IntRect(6 * 64, 0, 64, 64));
		logosSprite.setScale(scale, scale);
		if (g_Mouse.IsBetween(g_Resolution.x*0.75f, g_Resolution.y*0.78f - lineHeight, scale * 64, scale * 64, g_Mouse.Coords.x, g_Mouse.Coords.y) &&
			g_Mouse.IsClickValid() && g_Mouse.isHolding())
			logosSprite.setColor(sf::Color(128, 128, 128));
		else if (g_Mouse.IsBetween(g_Resolution.x*0.75f, g_Resolution.y*0.78f - lineHeight, scale * 64, scale * 64, g_Mouse.Coords.x, g_Mouse.Coords.y))
			logosSprite.setColor(sf::Color(225, 180, 128));
		else logosSprite.setColor(sf::Color(192, 192, 192));
		g_Window->draw(logosSprite);

		logosSprite.setPosition(g_Resolution.x*0.95f - scale*64.f, g_Resolution.y*0.78f - lineHeight);
		logosSprite.setTextureRect(sf::IntRect(7 * 64, 0, 64, 64));
		logosSprite.setScale(scale, scale);
		if (g_Mouse.IsBetween(g_Resolution.x*0.95f - scale*32.f, g_Resolution.y*0.78f - lineHeight, scale * 32, scale * 64, g_Mouse.Coords.x, g_Mouse.Coords.y) &&
			g_Mouse.IsClickValid() && g_Mouse.isHolding())
			logosSprite.setColor(sf::Color(128, 128, 128));
		else if (g_Mouse.IsBetween(g_Resolution.x*0.95f - scale*32.f, g_Resolution.y*0.78f - lineHeight, scale * 32, scale * 64, g_Mouse.Coords.x, g_Mouse.Coords.y))
			logosSprite.setColor(sf::Color(225, 180, 128));
		else logosSprite.setColor(sf::Color(192, 192, 192));
		g_Window->draw(logosSprite);

		//IWindow::RenderOverlay(g_Resolution.x*0.95f - scale*32.f, g_Resolution.y*0.78f - lineHeight, scale * 32, scale * 64, 255, 255, 255, 255);

		//logosSprite.setTextureRect(sf::IntRect(0,0,960))
	}

	//Button
	{
		auto Dim = _Window::GetTextSize("\nPLAY\n\n", g_Resolution.y*0.075f);
		if (g_Mouse.IsBetween(g_Resolution.x*0.75f, g_Resolution.y*0.8f, g_Resolution.x*0.2f, g_Resolution.y*0.1f, g_Mouse.Coords.x, g_Mouse.Coords.y) &&
			g_Mouse.IsClickValid() && g_Mouse.isHolding())
		{
			_Window::RenderOverlay(g_Resolution.x*0.75f, g_Resolution.y*0.8f, g_Resolution.x*0.2f, g_Resolution.y*0.1f, 185, 150, 16, 255);
			_Window::RenderTextB(g_Resolution.x*0.85f - Dim.x*0.5f, g_Resolution.y*0.85f - Dim.y*0.5f, "\nPLAY\n", g_Resolution.y*0.075f);
		}
		else if (g_Mouse.IsBetween(g_Resolution.x*0.75f, g_Resolution.y*0.8f, g_Resolution.x*0.2f, g_Resolution.y*0.1f, g_Mouse.Coords.x, g_Mouse.Coords.y))
		{
			_Window::RenderOverlay(g_Resolution.x*0.75f, g_Resolution.y*0.8f, g_Resolution.x*0.2f, g_Resolution.y*0.1f, 245, 210, 96, 255);
			_Window::RenderTextB(g_Resolution.x*0.85f - Dim.x*0.5f, g_Resolution.y*0.85f - Dim.y*0.5f, "\nPLAY", g_Resolution.y*0.075f, 32, 32, 64, 255);
		}
		else {
			_Window::RenderOverlay(g_Resolution.x*0.75f, g_Resolution.y*0.8f, g_Resolution.x*0.2f, g_Resolution.y*0.1f, 225, 180, 32, 255);
			_Window::RenderTextB(g_Resolution.x*0.85f - Dim.x*0.5f, g_Resolution.y*0.85f - Dim.y*0.5f, "\nPLAY", g_Resolution.y*0.075f, 32, 32, 64, 255);
		}


	}
}

void dc_game::DrawMainMenuMap()
{
	static sf::Image img;
	static sf::Texture tex;
	static sf::Sprite spr;
	static bool run_first = false;

	if (!run_first)
	{
		img.create(1000, 1000, sf::Color(255, 255, 255, 255));
		auto modulate_color = g_Map.get_modulation_color();
		for (int x = 0; x < 1000; x++)
		{
			for (int y = 0; y < 1000; y++)
			{




				auto color = g_Textures.getavgcolor(g_Map.lines[y].blocks[x].iTexture);

				auto r = color.r*modulate_color.r / 255;
				auto g = color.g*modulate_color.g / 255;
				auto b = color.b*modulate_color.b / 255;
				img.setPixel(x, y, sf::Color(r, g, b, 255));

			}
		}

		tex.loadFromImage(img);
		tex.setSmooth(true);
		spr.setTexture(tex);

		run_first = true;
	}
	float scale = (0.35f*g_Resolution.x) / 1000.f;
	_Window::RenderOverlay(g_Resolution.x*0.325f, g_Resolution.y*0.45f - (scale / 2)*(1000.f), g_Resolution.x*0.4f, g_Resolution.y*0.1f + scale*1000.f, 192, 192, 192, 64);

	spr.setScale(scale, scale);
	spr.setPosition(g_Resolution.x*0.35f, g_Resolution.y*0.5f - (scale / 2)*(1000.f));

	g_Window->draw(spr);

}

void dc_game::DrawMainMenuPlayerProfile()
{
	static sf::Sprite logosSprite;
	static bool bRun = false;
	if (!bRun)
	{
		logosSprite.setTexture(*g_Textures.get(51));
		bRun = true;
	}

	float fontsize = 0.03f*g_Resolution.y;
	auto lineHeight = _Window::GetTextSize("a\n", fontsize).y - _Window::GetTextSize("a", fontsize).y;
	float scale = (1.f*lineHeight + g_Resolution.y*0.01f) / 64.f;

	_Window::RenderOverlay(g_Resolution.x*0.75f, g_Resolution.y*0.05f, g_Resolution.x*0.2f, g_Resolution.y*0.70 - lineHeight, 192, 192, 192, 64);

	_Window::RenderTextBMiddleC(g_Resolution.x*0.75f, g_Resolution.y*0.05f, g_Resolution.x*0.2f, g_Resolution.y*0.05f, "PLAYER PROFILE", fontsize);

	//PlayerName
	if (bNameEditSelected)
		_Window::RenderOverlay(g_Resolution.x*0.75f, g_Resolution.y*0.1f, g_Resolution.x*0.2f, lineHeight + 4, 225, 180, 32, 255);
	else if (g_Mouse.IsBetween(g_Resolution.x*0.75f, g_Resolution.y*0.1f, g_Resolution.x*0.2f, lineHeight + 4, g_Mouse.Coords.x, g_Mouse.Coords.y))
		_Window::RenderOverlay(g_Resolution.x*0.75f, g_Resolution.y*0.1f, g_Resolution.x*0.2f, lineHeight + 4, 255, 255, 255, 255);
	else
		_Window::RenderOverlay(g_Resolution.x*0.75f, g_Resolution.y*0.1f, g_Resolution.x*0.2f, lineHeight + 4, 225, 225, 225, 255);
	{
		int nfontsize = fontsize;
		int flen = _Window::GetTextSize(ThePlayer.szName, nfontsize).x;
		if (flen > (g_Resolution.x*0.2f - 4))
		{
			float Bigness = (1.f*flen) / (1.f*g_Resolution.x*0.2f - 4);
			nfontsize = floor((1.f / Bigness)*nfontsize);
		}
		_Window::RenderTextB(g_Resolution.x*0.75f + 2, g_Resolution.y*0.1f, ThePlayer.szName, nfontsize, 0, 0, 0);

	}

	//Level Bar
	char Buffer[16]; sprintf(Buffer, "%d", ThePlayer.Level + 1);
	int textlengthA = _Window::GetTextSize("Level ", fontsize).x;
	int textlengthB = _Window::GetTextSize(Buffer, fontsize*1.34f).x;
	int textheightA = _Window::GetHeightForFontsize(fontsize);
	int textheightB = _Window::GetHeightForFontsize(fontsize*1.34f);
	int heightdiff = textheightB - textheightA;
	_Window::RenderTextB(g_Resolution.x*0.95f - textlengthA - textlengthB - g_Resolution.x*0.01f, g_Resolution.y*0.1f + 2 * lineHeight + 8 + heightdiff, "Level", fontsize);
	_Window::RenderTextB(g_Resolution.x*0.95f - textlengthB - g_Resolution.x*0.01f, g_Resolution.y*0.1f + 2 * lineHeight + 8, Buffer, fontsize*1.34f);

	int currentY = g_Resolution.y*0.1f + 2 * lineHeight + 8 + textheightB;

	_Window::RenderOverlay(g_Resolution.x*0.76f, currentY + 2, g_Resolution.x*0.18f, 6, 0, 0, 0, 255);

	int XpCurrent = ThePlayer.Xp;
	int XpUnder;
	if (ThePlayer.Level == 0)XpUnder = 0;
	else XpUnder = GetXpNeededForLevel(ThePlayer.Level - 1);
	int ProgressiveXp = XpCurrent - XpUnder;
	int XpNeeded = GetXpNeededForLevel(ThePlayer.Level) - XpUnder;

	float progress = 1.f*ProgressiveXp / XpNeeded;

	_Window::RenderOverlay(g_Resolution.x*0.76f + 1, currentY + 3, progress*(g_Resolution.x*0.18f - 2), 4, 0, 192, 64, 255);

	currentY = currentY + 10;

	if (ThePlayer.Level == 99)
	{
		_Window::RenderTextB(g_Resolution.x*0.95f - textlengthB - 10, currentY, "MAX", fontsize*1.34f);
	}
	else
	{
		char BufferB[16]; sprintf(BufferB, "%d/", ProgressiveXp);
		char BufferC[16]; sprintf(BufferC, "%d", XpNeeded);
		textlengthA = _Window::GetTextSize(BufferB, fontsize).x;
		textlengthB = _Window::GetTextSize(BufferC, fontsize*1.34f).x;
		_Window::RenderTextB(g_Resolution.x*0.95f - textlengthA - textlengthB - g_Resolution.x*0.01f, currentY + heightdiff, BufferB, fontsize);
		_Window::RenderTextB(g_Resolution.x*0.95f - textlengthB - g_Resolution.x*0.01f, currentY, BufferC, fontsize*1.34f);

	}

	//Tier Bar

	currentY = currentY + textheightB;

	int TierProgress = ThePlayer.TierStars;
	int Tier = ThePlayer.Tier;

	sprintf(Buffer, "%d", ThePlayer.Tier + 1);
	textlengthA = _Window::GetTextSize("Tier ", fontsize).x;
	textlengthB = _Window::GetTextSize(Buffer, fontsize*1.34f).x;
	_Window::RenderTextB(g_Resolution.x*0.95f - textlengthA - textlengthB - g_Resolution.x*0.01f, currentY + heightdiff, "Tier", fontsize);
	_Window::RenderTextB(g_Resolution.x*0.95f - textlengthB - g_Resolution.x*0.01f, currentY, Buffer, fontsize*1.34f);

	currentY = currentY + textheightB;






	int tierlength = (g_Resolution.x*0.18f - 27) / 10;
	int tierHeight = (g_Resolution.y*0.005f);

	for (int i = 0; i < 10; i++)
	{
		int posX = g_Resolution.x*0.76f + (tierlength + 3)*i;
		int posY = currentY + 4;
		if (i >= TierProgress)
			_Window::RenderOverlay(posX, posY, tierlength, tierHeight, 0, 0, 0, 255);
		else
			_Window::RenderOverlay(posX, posY, tierlength, tierHeight, 225, 180, 32, 255);
	}

	currentY = currentY + tierHeight + 15;



	if (MatchType == 1)
	{
		_Window::RenderOverlay(g_Resolution.x*0.76f, currentY, g_Resolution.x*0.18f, g_Resolution.y*0.05f, 225, 180, 32, 255);
		char Buffer[64]; sprintf(Buffer, "Arena Level %d ~ %d points", GetArenaLevel()+1,ThePlayer.ArenaPoints);
		auto textLen = _Window::GetTextSize(Buffer, g_Resolution.y*0.02f).x;
		
		_Window::RenderTextBMiddleC(g_Resolution.x*0.765f, currentY, textLen, _Window::GetHeightForFontsize(g_Resolution.y*0.02f), Buffer,g_Resolution.y*0.02f,32,32,96);

		auto nextLevelNeeded = GetArenaNeededForNextLevel();

		
		char BufferB[64]; 
		if (nextLevelNeeded > 0)
			sprintf(BufferB, "%d points for next level", nextLevelNeeded);
		else sprintf(BufferB, "MAX level");

		textLen = _Window::GetTextSize(BufferB, g_Resolution.y*0.02f).x;

		_Window::RenderTextBMiddleC(g_Resolution.x*0.935f-textLen, currentY+g_Resolution.y*0.05f-_Window::GetHeightForFontsize(g_Resolution.y*0.02f), textLen, _Window::GetHeightForFontsize(g_Resolution.y*0.02f), BufferB, g_Resolution.y*0.02f, 32, 32, 96);


		currentY += g_Resolution.y*0.05f + g_Resolution.y*0.01f;
	}

	for (int i = 0; i < 2; i++)
	{
		int height = DrawChallenge(i, g_Resolution.x*0.755f, currentY, g_Resolution.x*0.19, g_Resolution.y*0.05f);

		if (g_Mouse.IsBetween(0.75f*g_Resolution.x, currentY, 0.2f*g_Resolution.x, height - 2, g_Mouse.Coords.x, g_Mouse.Coords.y))
		{
			static sf::Sprite markersprite;
			markersprite.setTexture(*g_Textures.get(51));
			float scale = 0.078125f* g_Resolution.x*0.005f;
			markersprite.setScale(scale, scale);
			markersprite.setTextureRect(sf::IntRect(320, 0, 64, 64));
			markersprite.setOrigin(32, 61);

			markersprite.setColor(sf::Color(222, 180, 32, 255));
			auto loc = ThePlayer.Quests[i].location1;
			if (loc != -1)
			{
				auto cord = g_Map.labels[loc].vPosition;
				float s_scale = (0.35f*g_Resolution.x) / 1000.f;
				float sx = g_Resolution.x*0.35f, sy = g_Resolution.y*0.5f - (s_scale / 2)*(1000.f);
				float sizer = 0.35f*g_Resolution.x;
				markersprite.setPosition(sx + cord.x*sizer / 1000, sy + cord.y*sizer / 1000);
				g_Window->draw(markersprite);
			}
			loc = ThePlayer.Quests[i].location2;
			if (loc != -1)
			{
				auto cord = g_Map.labels[loc].vPosition;
				float s_scale = (0.35f*g_Resolution.x) / 1000.f;
				float sx = g_Resolution.x*0.35f, sy = g_Resolution.y*0.5f - (s_scale / 2)*(1000.f);
				float sizer = 0.35f*g_Resolution.x;
				markersprite.setPosition(sx + cord.x*sizer / 1000, sy + cord.y*sizer / 1000);
				g_Window->draw(markersprite);
			}
			loc = ThePlayer.Quests[i].location3;
			if (loc != -1)
			{
				auto cord = g_Map.labels[loc].vPosition;
				float s_scale = (0.35f*g_Resolution.x) / 1000.f;
				float sx = g_Resolution.x*0.35f, sy = g_Resolution.y*0.5f - (s_scale / 2)*(1000.f);
				float sizer = 0.35f*g_Resolution.x;
				markersprite.setPosition(sx + cord.x*sizer / 1000, sy + cord.y*sizer / 1000);
				g_Window->draw(markersprite);
			}

		}


		currentY += height;
	}

	//Statistics Button
	if (g_Mouse.IsBetween(0.75f*g_Resolution.x, g_Resolution.y*0.75f - lineHeight - (lineHeight + 4), 0.2f*g_Resolution.x, lineHeight + 4, g_Mouse.Coords.x, g_Mouse.Coords.y) &&
		g_Mouse.IsClickValid() && g_Mouse.isHolding())
	{
		_Window::RenderOverlay(0.75f*g_Resolution.x, g_Resolution.y*0.75f - lineHeight - (lineHeight + 4), 0.2f*g_Resolution.x, lineHeight + 4, 180, 150, 16, 255);
	}
	else if (g_Mouse.IsBetween(0.75f*g_Resolution.x, g_Resolution.y*0.75f - lineHeight - (lineHeight + 4), 0.2f*g_Resolution.x, lineHeight + 4, g_Mouse.Coords.x, g_Mouse.Coords.y))
	{
		_Window::RenderOverlay(0.75f*g_Resolution.x, g_Resolution.y*0.75f - lineHeight - (lineHeight + 4), 0.2f*g_Resolution.x, lineHeight + 4, 255, 255, 64, 255);

	}
	else
		_Window::RenderOverlay(0.75f*g_Resolution.x, g_Resolution.y*0.75f - lineHeight - (lineHeight + 4), 0.2f*g_Resolution.x, lineHeight + 4, 240, 215, 32, 255);

	_Window::RenderTextBMiddleC(0.75f*g_Resolution.x, g_Resolution.y*0.75f - lineHeight - (lineHeight + 4), 0.2f*g_Resolution.x, lineHeight + 4, "Statistics", fontsize, 0, 0, 0);

	//Replays Button
	if (g_Mouse.IsBetween(0.75f*g_Resolution.x, g_Resolution.y*0.75f - lineHeight - 2 * (lineHeight + 4) - 1, 0.2f*g_Resolution.x, lineHeight + 4, g_Mouse.Coords.x, g_Mouse.Coords.y) &&
		g_Mouse.IsClickValid() && g_Mouse.isHolding())
	{
		_Window::RenderOverlay(0.75f*g_Resolution.x, g_Resolution.y*0.75f - lineHeight - 2 * (lineHeight + 4) - 1, 0.2f*g_Resolution.x, lineHeight + 4, 180, 150, 16, 255);
	}
	else if (g_Mouse.IsBetween(0.75f*g_Resolution.x, g_Resolution.y*0.75f - lineHeight - 2 * (lineHeight + 4) - 1, 0.2f*g_Resolution.x, lineHeight + 4, g_Mouse.Coords.x, g_Mouse.Coords.y))
	{
		_Window::RenderOverlay(0.75f*g_Resolution.x, g_Resolution.y*0.75f - lineHeight - 2 * (lineHeight + 4) - 1, 0.2f*g_Resolution.x, lineHeight + 4, 255, 255, 64, 255);

	}
	else
		_Window::RenderOverlay(0.75f*g_Resolution.x, g_Resolution.y*0.75f - lineHeight - 2 * (lineHeight + 4) - 1, 0.2f*g_Resolution.x, lineHeight + 4, 240, 215, 32, 255);

	_Window::RenderTextBMiddleC(0.75f*g_Resolution.x, g_Resolution.y*0.75f - lineHeight - 2 * (lineHeight + 4) - 1, 0.2f*g_Resolution.x, lineHeight + 4, "Replays", fontsize, 0, 0, 0);


}

void dc_game::DoLeftSideMenubar()
{
	float fontsize = g_Resolution.y*0.03f;
	auto lineHeight = _Window::GetHeightForFontsize(fontsize);
	if (g_Mouse.IsBetween(0.05f*g_Resolution.x, g_Resolution.y*0.75f - (lineHeight + 4), 0.25f*g_Resolution.x, lineHeight + 4, g_Mouse.Coords.x, g_Mouse.Coords.y) &&
		g_Mouse.IsClickValid() && g_Mouse.hasReleased())
	{
		GM_STATE = 6;
	}
	if (g_Mouse.IsBetween(0.05f*g_Resolution.x, g_Resolution.y*0.75f - 2 * (lineHeight + 4) - 1, 0.25f*g_Resolution.x, lineHeight + 4, g_Mouse.Coords.x, g_Mouse.Coords.y) &&
		g_Mouse.IsClickValid() && g_Mouse.hasReleased())
	{
		GM_STATE = 3;
	}
}

void dc_game::DrawLeftSideMenubar()
{
	_Window::RenderOverlay(g_Resolution.x*0.05f, g_Resolution.y*0.45f, g_Resolution.x*0.25f, g_Resolution.y*0.3f, 192, 192, 192, 64);

	float fontsize = g_Resolution.y*0.03f;
	auto lineHeight = _Window::GetHeightForFontsize(fontsize);

	//Credits Button
	if (g_Mouse.IsBetween(0.05f*g_Resolution.x, g_Resolution.y*0.75f - (lineHeight + 4), 0.25f*g_Resolution.x, lineHeight + 4, g_Mouse.Coords.x, g_Mouse.Coords.y) &&
		g_Mouse.IsClickValid() && g_Mouse.isHolding())
	{
		_Window::RenderOverlay(0.05f*g_Resolution.x, g_Resolution.y*0.75f - (lineHeight + 4), 0.25f*g_Resolution.x, lineHeight + 4, 180, 150, 16, 255);
	}
	else if (g_Mouse.IsBetween(0.05f*g_Resolution.x, g_Resolution.y*0.75f - (lineHeight + 4), 0.25f*g_Resolution.x, lineHeight + 4, g_Mouse.Coords.x, g_Mouse.Coords.y))
	{
		_Window::RenderOverlay(0.05f*g_Resolution.x, g_Resolution.y*0.75f- (lineHeight + 4), 0.25f*g_Resolution.x, lineHeight + 4, 255, 255, 64, 255);

	}
	else
		_Window::RenderOverlay(0.05f*g_Resolution.x, g_Resolution.y*0.75f - (lineHeight + 4), 0.25f*g_Resolution.x, lineHeight + 4, 240, 215, 32, 255);

	_Window::RenderTextBMiddleC(0.05f*g_Resolution.x, g_Resolution.y*0.75f - (lineHeight + 4), 0.25f*g_Resolution.x, lineHeight + 4, "Credits", fontsize, 0, 0, 0);


	//Settings Button
	if (g_Mouse.IsBetween(0.05f*g_Resolution.x, g_Resolution.y*0.75f - 2*(lineHeight + 4)-1, 0.25f*g_Resolution.x, lineHeight + 4, g_Mouse.Coords.x, g_Mouse.Coords.y) &&
		g_Mouse.IsClickValid() && g_Mouse.isHolding())
	{
		_Window::RenderOverlay(0.05f*g_Resolution.x, g_Resolution.y*0.75f - 2*(lineHeight + 4)-1, 0.25f*g_Resolution.x, lineHeight + 4, 180, 150, 16, 255);
	}
	else if (g_Mouse.IsBetween(0.05f*g_Resolution.x, g_Resolution.y*0.75f - 2*(lineHeight + 4)-1, 0.25f*g_Resolution.x, lineHeight + 4, g_Mouse.Coords.x, g_Mouse.Coords.y))
	{
		_Window::RenderOverlay(0.05f*g_Resolution.x, g_Resolution.y*0.75f - 2*(lineHeight + 4)-1, 0.25f*g_Resolution.x, lineHeight + 4, 255, 255, 64, 255);

	}
	else
		_Window::RenderOverlay(0.05f*g_Resolution.x, g_Resolution.y*0.75f - 2*(lineHeight + 4)-1, 0.25f*g_Resolution.x, lineHeight + 4, 240, 215, 32, 255);

	_Window::RenderTextBMiddleC(0.05f*g_Resolution.x, g_Resolution.y*0.75f - 2*(lineHeight + 4)-1, 0.25f*g_Resolution.x, lineHeight + 4, "Settings", fontsize, 0, 0, 0);

}

void dc_game::DrawMainMenu()
{
	DrawMainMenuBg();
	DrawMainMenuMap();
	DrawMainMenuPlayButton();
	DrawMainMenuPlayerProfile();
	DrawMainMenuCharacterVision();

	DrawLeftSideMenubar();

}

void dc_game::DoStatisticsMenu()
{
	if (g_Keyboard.keys[VK_ESCAPE])GM_STATE = 0;
	DoBackButton();
}

void dc_game::DrawStatisticsMenu()
{
	DrawMainMenuBg();
	DrawBackButton();

	char* Texts[] = { "Level","Experience","Matches Played","Matches Won","Win rate","Average Placement","Top 25 placements","Top 10 placements","Total Damage","Kill/Death","Total Eliminations","Pistol Eliminations","SMG Eliminations","Shotgun Eliminations","Rifle Eliminations","Sniper Eliminations","Explosive Eliminations","Machinegun Eliminations","Distance Traveled","Time Alive","Quests Finished" };
	double Vals[] = { ThePlayer.Level+1,ThePlayer.Xp,ThePlayer.TotalMatches, ThePlayer.TotalWins, max(0,(100.f*ThePlayer.TotalWins) / ThePlayer.TotalMatches) , max(0,(1.f*ThePlayer.TotalPlacement) / ThePlayer.TotalMatches), ThePlayer.TotalTop25s, ThePlayer.TotalTop10s, ThePlayer.TotalDamage, ((float)ThePlayer.TotalKills)/(max(1,ThePlayer.TotalMatches-ThePlayer.TotalWins)), ThePlayer.TotalKills, ThePlayer.TotalPistolKills, ThePlayer.TotalSubmachinegunKills, ThePlayer.TotalShotgunKills, ThePlayer.TotalRifleKills, ThePlayer.TotalSniperKills, ThePlayer.TotalExplosiveKills, ThePlayer.TotalMachinegunKills, 1.0*ThePlayer.DistanceTravelledHigh + ThePlayer.DistanceTravelledLow, ThePlayer.TotalTimeAlive, ThePlayer.QuestsFinished };
	char* Format[] = { "%.0f","%.0f","%.0f","%.0f","%.1f%%","%.1f","%.0f","%.0f","%.0f","%.2f","%.0f", "%.0f", "%.0f", "%.0f", "%.0f", "%.0f", "%.0f", "%.0f", "%.2fm", "%d:%s%d:%s%d", "%.0f" };
	int totalRows = 20;


	int fontsize = g_Resolution.y;
	auto lineHeight = _Window::GetTextSize("a\n", fontsize).y - _Window::GetTextSize("a", fontsize).y;

	float RowHeight = (0.9f*g_Resolution.y - 3 * totalRows + 3) / totalRows;
	int MaxFontSize = (RowHeight) / lineHeight*fontsize;

	int RowLength = 0;
	for (int i = 0; i < totalRows; i++)
	{
		auto dim = _Window::GetTextSize(Texts[i], MaxFontSize);
		if (dim.x > RowLength)RowLength = dim.x;
	}
	MaxFontSize -= 1;
	RowLength += 6;
	int RowLengthB = _Window::GetTextSize("9999:99:99", MaxFontSize).x;
	for (int i = 0; i < totalRows; i++)
	{
		_Window::RenderOverlay(0.15f*g_Resolution.x, 0.05f*g_Resolution.y + (3 + RowHeight)*i, RowLength, RowHeight, 64, 64, 160, 128);

		int l = _Window::GetTextSize(Texts[i], MaxFontSize).x;
		_Window::RenderTextB(0.15f*g_Resolution.x + RowLength - 3 - l, 0.05f*g_Resolution.y + (3 + RowHeight)*i, Texts[i], MaxFontSize);

		_Window::RenderOverlay(0.15f*g_Resolution.x + RowLength + 3, 0.05f*g_Resolution.y + (3 + RowHeight)*i, RowLengthB, RowHeight, 64, 64, 160, 128);

		if (i == 19)
		{
			int Hours = 0, Minutes = 0, Seconds = 0;
			int time = Vals[i];
			while (time > 3600) { Hours++; time -= 3600; }
			while (time > 60) { Minutes++; time -= 60; }
			Seconds = time;

			char Buffer[32]; sprintf(Buffer, Format[i], Hours, ((Minutes < 10) ? ("0") : ("")), Minutes, ((Seconds < 10) ? "0" : ""), Seconds);
			_Window::RenderTextBMiddleC(0.15f*g_Resolution.x + RowLength + 3, 0.05f*g_Resolution.y + (3 + RowHeight)*i, RowLengthB, RowHeight, Buffer, MaxFontSize);
		}
		else
		{
			if (isnan(Vals[i]))Vals[i] = 0;

			char Buffer[16]; sprintf(Buffer, Format[i], Vals[i]);
			_Window::RenderTextBMiddleC(0.15f*g_Resolution.x + RowLength + 3, 0.05f*g_Resolution.y + (3 + RowHeight)*i, RowLengthB, RowHeight, Buffer, MaxFontSize);
		}

	}


}


void dc_game::DoInDemoEscapeMenu()
{
	if (g_Mouse.IsBetween(0.025f*g_Resolution.x, g_Resolution.y*0.8f, 0.25f*g_Resolution.x, g_Resolution.y*0.1f, g_Mouse.Coords.x, g_Mouse.Coords.y) &&
		g_Mouse.IsClickValid() && g_Mouse.hasReleased())
	{

		GM_STATE = 4;

		delete DViewer;
		DViewer = nullptr;
	}

	if (g_Mouse.IsBetween(0.025f*g_Resolution.x, g_Resolution.y*0.675f, 0.25f*g_Resolution.x, g_Resolution.y*0.1f, g_Mouse.Coords.x, g_Mouse.Coords.y) &&
		g_Mouse.IsClickValid() && g_Mouse.hasReleased())
	{
		OW_STATUS = 3;
	}


}

void dc_game::DrawInDemoEscapeMenu()
{
	_Window::RenderOverlay(0, 0, 0.3f*g_Resolution.x, g_Resolution.y, 0, 0, 0, 128);
	auto Dim = _Window::GetTextSize("\nLeave match\n\n", g_Resolution.y*0.05f);

	if (g_Mouse.IsBetween(0.025f*g_Resolution.x, g_Resolution.y*0.8f, 0.25f*g_Resolution.x, g_Resolution.y*0.1f, g_Mouse.Coords.x, g_Mouse.Coords.y) &&
		g_Mouse.IsClickValid() && g_Mouse.isHolding())
	{
		_Window::RenderOverlay(g_Resolution.x*0.025f, g_Resolution.y*0.8f, 0.25f* g_Resolution.x, g_Resolution.y*0.1f, 185, 150, 16, 255);
		_Window::RenderTextB(g_Resolution.x*0.15f - Dim.x*0.5f, g_Resolution.y*0.85f - Dim.y*0.5f, "\nLeave match\n\n", g_Resolution.y*0.05f);
	}
	else if (g_Mouse.IsBetween(0.025f*g_Resolution.x, g_Resolution.y*0.8f, 0.25f*g_Resolution.x, g_Resolution.y*0.1f, g_Mouse.Coords.x, g_Mouse.Coords.y))
	{
		_Window::RenderOverlay(g_Resolution.x*0.025f, g_Resolution.y*0.8f, 0.25f* g_Resolution.x, g_Resolution.y*0.1f, 245, 210, 96, 255);
		_Window::RenderTextB(g_Resolution.x*0.15f - Dim.x*0.5f, g_Resolution.y*0.85f - Dim.y*0.5f, "\nLeave match\n\n", g_Resolution.y*0.05f, 32, 32, 64, 255);
	}
	else
	{
		_Window::RenderOverlay(g_Resolution.x*0.025f, g_Resolution.y*0.8f, 0.25f* g_Resolution.x, g_Resolution.y*0.1f, 225, 180, 32, 255);
		_Window::RenderTextB(g_Resolution.x*0.15f - Dim.x*0.5f, g_Resolution.y*0.85f - Dim.y*0.5f, "\nLeave match\n\n", g_Resolution.y*0.05f, 32, 32, 64, 255);
	}

	Dim = _Window::GetTextSize("\nSettings\n\n", g_Resolution.y*0.05f);

	if (g_Mouse.IsBetween(0.025f*g_Resolution.x, g_Resolution.y*0.675f, 0.25f*g_Resolution.x, g_Resolution.y*0.1f, g_Mouse.Coords.x, g_Mouse.Coords.y) &&
		g_Mouse.IsClickValid() && g_Mouse.isHolding())
	{
		_Window::RenderOverlay(g_Resolution.x*0.025f, g_Resolution.y*0.675f, 0.25f* g_Resolution.x, g_Resolution.y*0.1f, 185, 150, 16, 255);
		_Window::RenderTextB(g_Resolution.x*0.15f - Dim.x*0.5f, g_Resolution.y*0.725f - Dim.y*0.5f, "\nSettings\n\n", g_Resolution.y*0.05f);
	}
	else if (g_Mouse.IsBetween(0.025f*g_Resolution.x, g_Resolution.y*0.675f, 0.25f*g_Resolution.x, g_Resolution.y*0.1f, g_Mouse.Coords.x, g_Mouse.Coords.y))
	{
		_Window::RenderOverlay(g_Resolution.x*0.025f, g_Resolution.y*0.675f, 0.25f* g_Resolution.x, g_Resolution.y*0.1f, 245, 210, 96, 255);
		_Window::RenderTextB(g_Resolution.x*0.15f - Dim.x*0.5f, g_Resolution.y*0.725f - Dim.y*0.5f, "\nSettings\n\n", g_Resolution.y*0.05f, 32, 32, 64, 255);
	}
	else
	{
		_Window::RenderOverlay(g_Resolution.x*0.025f, g_Resolution.y*0.675f, 0.25f* g_Resolution.x, g_Resolution.y*0.1f, 225, 180, 32, 255);
		_Window::RenderTextB(g_Resolution.x*0.15f - Dim.x*0.5f, g_Resolution.y*0.725f - Dim.y*0.5f, "\nSettings\n\n", g_Resolution.y*0.05f, 32, 32, 64, 255);
	}

}


void dc_game::DoIngameEscapeMenu()
{
	if (g_Mouse.IsBetween(0.025f*g_Resolution.x, g_Resolution.y*0.8f, 0.25f*g_Resolution.x, g_Resolution.y*0.1f, g_Mouse.Coords.x, g_Mouse.Coords.y) &&
		g_Mouse.IsClickValid() && g_Mouse.hasReleased())
	{
		if (Match->players[0].iHealth > 0)
		{
			Match->players[0].iHealth = 0;
			Match->PlayerKill(0);

		}

		GM_STATE = 0;

		EvaluateMatch();
		CheckLevels();
		
		Match->Demo_ShouldEnd = true;
		int j = 0;
		while (!Match->canDelete)
		{
			ConLog(".", Match->canDelete);
			if (Match->canDelete)
				break;

		}
		delete Match;
		Match = nullptr;
		SaveProfile();
	}

	if (g_Mouse.IsBetween(0.025f*g_Resolution.x, g_Resolution.y*0.675f, 0.25f*g_Resolution.x, g_Resolution.y*0.1f, g_Mouse.Coords.x, g_Mouse.Coords.y) &&
		g_Mouse.IsClickValid() && g_Mouse.hasReleased())
	{
		OW_STATUS = 3;
	}

	if (g_Mouse.IsBetween(0.025f*g_Resolution.x, g_Resolution.y*0.55f, 0.25f*g_Resolution.x, g_Resolution.y*0.1f, g_Mouse.Coords.x, g_Mouse.Coords.y) &&
		g_Mouse.IsClickValid() && g_Mouse.hasReleased())
	{
		if (Match && (Match->players[0].iHealth <= 0 || Match->bMatchEnded))
		{
			OW_STATUS = 4;
		}
	}
}

void dc_game::DrawIngameEscapeMenu()
{
	_Window::RenderOverlay(0, 0, 0.3f*g_Resolution.x, g_Resolution.y, 0, 0, 0, 128);
	auto Dim = _Window::GetTextSize("\nLeave match\n\n", g_Resolution.y*0.05f);

	if (g_Mouse.IsBetween(0.025f*g_Resolution.x, g_Resolution.y*0.8f, 0.25f*g_Resolution.x, g_Resolution.y*0.1f, g_Mouse.Coords.x, g_Mouse.Coords.y) &&
		g_Mouse.IsClickValid() && g_Mouse.isHolding())
	{
		_Window::RenderOverlay(g_Resolution.x*0.025f, g_Resolution.y*0.8f, 0.25f* g_Resolution.x, g_Resolution.y*0.1f, 185, 150, 16, 255);
		_Window::RenderTextB(g_Resolution.x*0.15f - Dim.x*0.5f, g_Resolution.y*0.85f - Dim.y*0.5f, "\nLeave match\n\n", g_Resolution.y*0.05f);
	}
	else if (g_Mouse.IsBetween(0.025f*g_Resolution.x, g_Resolution.y*0.8f, 0.25f*g_Resolution.x, g_Resolution.y*0.1f, g_Mouse.Coords.x, g_Mouse.Coords.y))
	{
		_Window::RenderOverlay(g_Resolution.x*0.025f, g_Resolution.y*0.8f, 0.25f* g_Resolution.x, g_Resolution.y*0.1f, 245, 210, 96, 255);
		_Window::RenderTextB(g_Resolution.x*0.15f - Dim.x*0.5f, g_Resolution.y*0.85f - Dim.y*0.5f, "\nLeave match\n\n", g_Resolution.y*0.05f, 32, 32, 64, 255);
	}
	else
	{
		_Window::RenderOverlay(g_Resolution.x*0.025f, g_Resolution.y*0.8f, 0.25f* g_Resolution.x, g_Resolution.y*0.1f, 225, 180, 32, 255);
		_Window::RenderTextB(g_Resolution.x*0.15f - Dim.x*0.5f, g_Resolution.y*0.85f - Dim.y*0.5f, "\nLeave match\n\n", g_Resolution.y*0.05f, 32, 32, 64, 255);
	}

	Dim = _Window::GetTextSize("\nSettings\n\n", g_Resolution.y*0.05f);

	if (g_Mouse.IsBetween(0.025f*g_Resolution.x, g_Resolution.y*0.675f, 0.25f*g_Resolution.x, g_Resolution.y*0.1f, g_Mouse.Coords.x, g_Mouse.Coords.y) &&
		g_Mouse.IsClickValid() && g_Mouse.isHolding())
	{
		_Window::RenderOverlay(g_Resolution.x*0.025f, g_Resolution.y*0.675f, 0.25f* g_Resolution.x, g_Resolution.y*0.1f, 185, 150, 16, 255);
		_Window::RenderTextB(g_Resolution.x*0.15f - Dim.x*0.5f, g_Resolution.y*0.725f - Dim.y*0.5f, "\nSettings\n\n", g_Resolution.y*0.05f);
	}
	else if (g_Mouse.IsBetween(0.025f*g_Resolution.x, g_Resolution.y*0.675f, 0.25f*g_Resolution.x, g_Resolution.y*0.1f, g_Mouse.Coords.x, g_Mouse.Coords.y))
	{
		_Window::RenderOverlay(g_Resolution.x*0.025f, g_Resolution.y*0.675f, 0.25f* g_Resolution.x, g_Resolution.y*0.1f, 245, 210, 96, 255);
		_Window::RenderTextB(g_Resolution.x*0.15f - Dim.x*0.5f, g_Resolution.y*0.725f - Dim.y*0.5f, "\nSettings\n\n", g_Resolution.y*0.05f, 32, 32, 64, 255);
	}
	else
	{
		_Window::RenderOverlay(g_Resolution.x*0.025f, g_Resolution.y*0.675f, 0.25f* g_Resolution.x, g_Resolution.y*0.1f, 225, 180, 32, 255);
		_Window::RenderTextB(g_Resolution.x*0.15f - Dim.x*0.5f, g_Resolution.y*0.725f - Dim.y*0.5f, "\nSettings\n\n", g_Resolution.y*0.05f, 32, 32, 64, 255);
	}

	if (Match && (Match->players[0].iHealth <= 0 || Match->bMatchEnded))
	{
		Dim = _Window::GetTextSize("\nShow stats\n\n", g_Resolution.y*0.05f);

		if (g_Mouse.IsBetween(0.025f*g_Resolution.x, g_Resolution.y*0.55f, 0.25f*g_Resolution.x, g_Resolution.y*0.1f, g_Mouse.Coords.x, g_Mouse.Coords.y) &&
			g_Mouse.IsClickValid() && g_Mouse.isHolding())
		{
			_Window::RenderOverlay(g_Resolution.x*0.025f, g_Resolution.y*0.55f, 0.25f* g_Resolution.x, g_Resolution.y*0.1f, 185, 150, 16, 255);
			_Window::RenderTextB(g_Resolution.x*0.15f - Dim.x*0.5f, g_Resolution.y*0.60f - Dim.y*0.5f, "\nShow stats\n\n", g_Resolution.y*0.05f);
		}
		else if (g_Mouse.IsBetween(0.025f*g_Resolution.x, g_Resolution.y*0.55f, 0.25f*g_Resolution.x, g_Resolution.y*0.1f, g_Mouse.Coords.x, g_Mouse.Coords.y))
		{
			_Window::RenderOverlay(g_Resolution.x*0.025f, g_Resolution.y*0.55f, 0.25f* g_Resolution.x, g_Resolution.y*0.1f, 245, 210, 96, 255);
			_Window::RenderTextB(g_Resolution.x*0.15f - Dim.x*0.5f, g_Resolution.y*0.60f - Dim.y*0.5f, "\nShow stats\n\n", g_Resolution.y*0.05f, 32, 32, 64, 255);
		}
		else
		{
			_Window::RenderOverlay(g_Resolution.x*0.025f, g_Resolution.y*0.55f, 0.25f* g_Resolution.x, g_Resolution.y*0.1f, 225, 180, 32, 255);
			_Window::RenderTextB(g_Resolution.x*0.15f - Dim.x*0.5f, g_Resolution.y*0.60f - Dim.y*0.5f, "\nShow stats\n\n", g_Resolution.y*0.05f, 32, 32, 64, 255);
		}
	}

	int y = DrawChallengeWithProgress(0, g_Resolution.x*0.35f, g_Resolution.y*0.02f, g_Resolution.x*0.6f, g_Resolution.y*0.1f);
	DrawChallengeWithProgress(1, g_Resolution.x*0.35f, g_Resolution.y*0.02f + y, g_Resolution.x*0.6f, g_Resolution.y*0.1f);
}





void dc_game::DrawIngameSettingsMenu()
{
	_Window::RenderOverlay(0, 0, g_Resolution.x, g_Resolution.y, 0, 0, 0, 128);


	auto fontsize = g_Resolution.x*0.03f;
	auto lineHeight = _Window::GetHeightForFontsize(fontsize);

	char* SettNames[] = { "Controls","Video","Audio" };

	float Length = g_Resolution.x*0.3f - 2;







	//Buttons
	for (int i = 0; i < 3; i++)
	{
		if (g_Mouse.IsBetween(0.05f*g_Resolution.x + i*(1 + Length), g_Resolution.y*0.05f, Length, lineHeight + 4, g_Mouse.Coords.x, g_Mouse.Coords.y) &&
			g_Mouse.IsClickValid() && g_Mouse.isHolding())
		{
			_Window::RenderOverlay(0.05f*g_Resolution.x + i*(1 + Length), g_Resolution.y*0.05f, Length, lineHeight + 4, 180, 150, 16, 255);
		}
		else if (i == SettingsState)
		{
			_Window::RenderOverlay(0.05f*g_Resolution.x + i*(1 + Length), g_Resolution.y*0.05f, Length, lineHeight + 4, 180, 150, 16, 255);
		}
		else if (g_Mouse.IsBetween(0.05f*g_Resolution.x + i*(1 + Length), g_Resolution.y*0.05f, Length, lineHeight + 4, g_Mouse.Coords.x, g_Mouse.Coords.y))
		{
			_Window::RenderOverlay(0.05f*g_Resolution.x + i*(1 + Length), g_Resolution.y*0.05f, Length, lineHeight + 4, 255, 255, 64, 255);

		}
		else
			_Window::RenderOverlay(0.05f*g_Resolution.x + i*(1 + Length), g_Resolution.y*0.05f, Length, lineHeight + 4, 240, 215, 32, 255);

		_Window::RenderTextBMiddleC(0.05f*g_Resolution.x + i*(1 + Length), g_Resolution.y*0.05f, Length, lineHeight + 4, SettNames[i], fontsize, 0, 0, 0);
	}

	if (SettingsState == 0)
	{
		_Window::RenderOverlay(g_Resolution.x*0.05f, g_Resolution.y*0.15, g_Resolution.y*0.08f, g_Resolution.y*0.08f, 128, 128, 128, 128);

		if (g_Config.p_movement_type.Value >= 1)
			_Window::RenderOverlay(g_Resolution.x*0.05f + 2, g_Resolution.y*0.15 + 2, g_Resolution.y*0.08f - 4, g_Resolution.y*0.08f - 4, 64, 64, 192, 255);

		auto width = _Window::GetTextSize("Directional movement", fontsize).x;
		_Window::RenderOverlay(g_Resolution.x*0.05f + g_Resolution.y*0.09f + 2, g_Resolution.y*0.15, width + 12, g_Resolution.y*0.08f, 192, 192, 192, 64);
		_Window::RenderTextBMiddleC(g_Resolution.x*0.05f + g_Resolution.y*0.09f + 2, g_Resolution.y*0.15, width + 12, g_Resolution.y*0.08f, "Directional movement", fontsize, 255, 255, 255, 255);

		auto KeyNames = GetAllKeyNames();

		std::vector<char*> ActNames = { "Shoot","Move forward","Move backward","Move right","Move left","Reload weapon","Slot 1","Slot 2","Slot 3","Slot 4","Slot 5","Drop item","Open Inventory","Open Map","Place Marker","Remove Marker","Open Console","Jump Off","Descend","Alternative","Close Menu","Swap Player","Console enter" };
		std::vector<int> Sorrend = { 1,2,4,3,19,0,5,6,7,8,9,10,11,12,13,17,18,20,21,14,15,16,22 };

		sf::Vector2f TX(g_Resolution.x*0.05f, g_Resolution.y*0.25f);
		float MaxH = g_Resolution.y*0.7f;
		float MaxW = g_Resolution.x*0.9f;
		float OneH = MaxH / 12;
		float OneW = MaxW / 2;

		float Perc[4] = { 0.f,0.4f,0.7f,1.f };


		for (int i = 0; i < 23; i++)
		{
			int High = i / 12;
			int Low = i % 12;

			for (int j = 0; j < 3; j++)
			{
				std::vector<char*> Texts;
				Texts.push_back(ActNames[Sorrend[i]]);
				if (Binds.KeysPrimary[Sorrend[i]])Texts.push_back(KeyNames[Binds.KeysPrimary[Sorrend[i]]]);
				else Texts.push_back("");
				if (Binds.KeysSecondary[Sorrend[i]])Texts.push_back(KeyNames[Binds.KeysSecondary[Sorrend[i]]]);
				else Texts.push_back("");

				sf::RectangleShape R;
				R.setPosition(TX.x + (Perc[j] + High)*OneW, TX.y + Low*OneH);
				R.setSize(sf::Vector2f(OneW*(Perc[j + 1] - Perc[j]) - 1, OneH - 1));

				if (g_Mouse.IsBetween(R.getPosition().x, R.getPosition().y, R.getSize().x, R.getSize().y, g_Mouse.Coords.x, g_Mouse.Coords.y)
					&& g_Mouse.IsClickValid() && g_Mouse.isHolding())
					R.setFillColor(sf::Color(160, 120, 16));
				else if (g_Mouse.IsBetween(R.getPosition().x, R.getPosition().y, R.getSize().x, R.getSize().y, g_Mouse.Coords.x, g_Mouse.Coords.y))
					R.setFillColor(sf::Color(255, 222, 64));
				else R.setFillColor(sf::Color(225, 180, 32));

				g_Window->draw(R);
				_Window::RenderTextBMiddleC(R.getPosition().x, R.getPosition().y, R.getSize().x, R.getSize().y, Texts[j], g_Resolution.y*0.025f, 0, 0, 0);

			}
		}


	}
	if (SettingsState == 1)
	{
		auto width = _Window::GetTextSize("Brightness", fontsize).x;
		_Window::RenderOverlay(g_Resolution.x*0.05f, g_Resolution.y*0.15f, width + 6, lineHeight + 4, 192, 192, 192, 64);
		_Window::RenderTextBMiddleC(g_Resolution.x*0.05f, g_Resolution.y*0.15f, width + 6, lineHeight + 4, "Brightness", fontsize, 255, 255, 255, 255);

		float barlength = g_Resolution.x*0.95f - (g_Resolution.x*0.05f + width + g_Resolution.x*0.01f);
		_Window::RenderOverlay(g_Resolution.x*0.05f + width + g_Resolution.x*0.01f, g_Resolution.y*0.15f, barlength, lineHeight + 4, 64, 64, 64, 128);
		float sliderlength = g_Resolution.x*0.02f;
		float cum_barlength = barlength - sliderlength;

		float sliderPos = (g_Resolution.x*0.05f + width + 0.5f*sliderlength) + ((2.f*g_Config.g_brightness.Value - 1.f)*cum_barlength);

		_Window::RenderOverlay(sliderPos, g_Resolution.y*0.145f, sliderlength, lineHeight + 4 + g_Resolution.y*0.01f, 255, 255, 255, 255);

		sf::Vector2i Resolutions[] = { sf::Vector2i(640,480),sf::Vector2i(800,600),sf::Vector2i(1024,768),sf::Vector2i(1280,960),sf::Vector2i(1440,1080), sf::Vector2i(640,360),sf::Vector2i(1024,576),sf::Vector2i(1280,720),sf::Vector2i(1600,900),sf::Vector2i(1920,1080), sf::Vector2i(640,400),sf::Vector2i(1280,800),sf::Vector2i(1680,1050),sf::Vector2i(1680,720) };





		width = _Window::GetTextSize("Resolution", fontsize).x;
		_Window::RenderOverlay(g_Resolution.x*0.056, g_Resolution.y*0.16f + lineHeight + 4, width + 6, lineHeight + 4, 192, 192, 192, 64);
		_Window::RenderTextBMiddleC(g_Resolution.x*0.05f, g_Resolution.y*0.16f + lineHeight + 4, width + 6, lineHeight + 4, "Resolution", fontsize, 255, 255, 255, 255);

		auto AvailableWidth = g_Resolution.x*0.95f - (g_Resolution.x*0.05f + width + g_Resolution.x*0.01f);
		auto AvailableHeight = g_Resolution.y*0.7f - (g_Resolution.y*0.16f + lineHeight + 4);

		auto OneWidth = AvailableWidth / 2 - 1;
		auto OneHeight = AvailableHeight / 7 - 6;

		sf::Vector2f T = sf::Vector2f(g_Resolution.x*0.05f + width + g_Resolution.x*0.01f, (g_Resolution.y*0.16f + lineHeight + 4));
		_Window::RenderOverlay(T.x, T.y, AvailableWidth, AvailableHeight, 64, 0, 0, 64);

		for (int i = 0; i < 14; i++)
		{
			int High = i / 7;
			int Low = i % 7;

			auto pX = T.x + High*(OneWidth + 1);
			auto pY = T.y + Low*(OneHeight + 1);

			sf::RectangleShape rShape;
			rShape.setPosition(pX, pY);
			rShape.setSize(sf::Vector2f(OneWidth, OneHeight));
			if (g_Mouse.IsBetween(pX, pY, OneWidth, OneHeight, g_Mouse.Coords.x, g_Mouse.Coords.y)
				&& g_Mouse.IsClickValid() && g_Mouse.isHolding())
			{
				if (i % 2 == 0)
					rShape.setFillColor(sf::Color(44, 44, 66, 255));
				else rShape.setFillColor(sf::Color(55, 55, 82, 255));
			}
			else if (i == SelectedVideoSetting)
			{
				rShape.setFillColor(sf::Color(55, 155, 82, 255));
			}
			else if (g_Mouse.IsBetween(pX, pY, OneWidth, OneHeight, g_Mouse.Coords.x, g_Mouse.Coords.y))
			{
				if (i % 2 == 0)
					rShape.setFillColor(sf::Color(96, 96, 144, 255));
				else rShape.setFillColor(sf::Color(112, 112, 168, 255));
			}
			else
			{
				if (i % 2 == 0)
					rShape.setFillColor(sf::Color(64, 64, 96, 255));
				else rShape.setFillColor(sf::Color(80, 80, 120, 255));
			}
			g_Window->draw(rShape);

			char Buffer[32]; sprintf(Buffer, "%dx%d", Resolutions[i].x, Resolutions[i].y);
			_Window::RenderTextBMiddleC(pX, pY, OneWidth, OneHeight, Buffer, g_Resolution.y*0.03f);
		}
		if (g_Mouse.IsBetween(g_Resolution.x*0.75f, g_Resolution.y*0.85f, g_Resolution.x*0.2f, g_Resolution.y*0.1f, g_Mouse.Coords.x, g_Mouse.Coords.y)
			&& g_Mouse.IsClickValid() && g_Mouse.isHolding())
			_Window::RenderOverlay(g_Resolution.x*0.75f, g_Resolution.y*0.85f, g_Resolution.x*0.2f, g_Resolution.y*0.1f, 160, 110, 16, 255);
		else if (g_Mouse.IsBetween(g_Resolution.x*0.75f, g_Resolution.y*0.85f, g_Resolution.x*0.2f, g_Resolution.y*0.1f, g_Mouse.Coords.x, g_Mouse.Coords.y))
			_Window::RenderOverlay(g_Resolution.x*0.75f, g_Resolution.y*0.85f, g_Resolution.x*0.2f, g_Resolution.y*0.1f, 255, 222, 64, 255);
		else _Window::RenderOverlay(g_Resolution.x*0.75f, g_Resolution.y*0.85f, g_Resolution.x*0.2f, g_Resolution.y*0.1f, 225, 180, 32, 255);
		_Window::RenderTextBMiddleC(g_Resolution.x*0.75f, g_Resolution.y*0.85f, g_Resolution.x*0.2f, g_Resolution.y*0.1f, "APPLY", g_Resolution.y*0.05f, 0, 0, 0, 255);



		_Window::RenderOverlay(T.x, g_Resolution.y*0.71, g_Resolution.y*0.08f, g_Resolution.y*0.08f, 128, 128, 128, 128);

		if (SettingFullscreen == 1)
			_Window::RenderOverlay(T.x + 2, g_Resolution.y*0.71 + 2, g_Resolution.y*0.08f - 4, g_Resolution.y*0.08f - 4, 64, 64, 192, 255);

		width = _Window::GetTextSize("Full screen", fontsize).x;
		_Window::RenderOverlay(T.x + g_Resolution.y*0.09f + 2, g_Resolution.y*0.71, width + 12, g_Resolution.y*0.08f, 192, 192, 192, 64);
		_Window::RenderTextBMiddleC(T.x + g_Resolution.y*0.09f + 2, g_Resolution.y*0.71, width + 12, g_Resolution.y*0.08f, "Full screen", fontsize, 255, 255, 255, 255);


	}

	if (SettingsState == 2)
	{

		auto width = _Window::GetTextSize("Master volume", fontsize).x;
		_Window::RenderOverlay(g_Resolution.x*0.05f, g_Resolution.y*0.15f, width + 6, lineHeight + 4, 192, 192, 192, 64);
		_Window::RenderTextBMiddleC(g_Resolution.x*0.05f, g_Resolution.y*0.15f, width + 6, lineHeight + 4, "Master volume", fontsize, 255, 255, 255, 255);

		float barlength = g_Resolution.x*0.95f - (g_Resolution.x*0.05f + width + g_Resolution.x*0.01f);
		_Window::RenderOverlay(g_Resolution.x*0.05f + width + g_Resolution.x*0.01f, g_Resolution.y*0.15f, barlength, lineHeight + 4, 64, 64, 64, 128);
		float sliderlength = g_Resolution.x*0.02f;
		float cum_barlength = barlength - sliderlength;

		float sliderPos = (g_Resolution.x*0.05f + width + 0.5f*sliderlength) + g_Config.mastervolume.Value*cum_barlength;

		_Window::RenderOverlay(sliderPos, g_Resolution.y*0.145f, sliderlength, lineHeight + 4 + g_Resolution.y*0.01f, 255, 255, 255, 255);
	}


}

void dc_game::DoIngameSettingsMenu()
{

	//Buttons
	auto fontsize = g_Resolution.x*0.03f;
	auto lineHeight = _Window::GetHeightForFontsize(fontsize);
	float Length = g_Resolution.x*0.3f - 2;
	for (int i = 0; i < 3; i++)
	{
		if (g_Mouse.IsBetween(0.05f*g_Resolution.x + i*(1 + Length), g_Resolution.y*0.05f, Length, lineHeight + 4, g_Mouse.Coords.x, g_Mouse.Coords.y) &&
			g_Mouse.IsClickValid() && g_Mouse.hasReleased())
			SettingsState = i;
	}

	if (SettingsState == 0)
	{

		if (g_Mouse.IsBetween(g_Resolution.x*0.05f, g_Resolution.y*0.15, g_Resolution.y*0.08f, g_Resolution.y*0.08f, g_Mouse.Coords.x, g_Mouse.Coords.y)
			&& g_Mouse.IsClickValid() && g_Mouse.hasReleased())
		{
			if (g_Config.p_movement_type.Value < 1.f)g_Config.p_movement_type.Value = 1.f;
			else g_Config.p_movement_type.Value = 0.f;
		}

		sf::Vector2f TX(g_Resolution.x*0.05f, g_Resolution.y*0.25f);
		float MaxH = g_Resolution.y*0.7f;
		float MaxW = g_Resolution.x*0.9f;
		float OneH = MaxH / 12;
		float OneW = MaxW / 2;

		float Perc[4] = { 0.f,0.4f,0.7f,1.f };
		std::vector<int> Sorrend = { 1,2,4,3,19,0,5,6,7,8,9,10,11,12,13,17,18,20,21,14,15,16,22 };

		for (int i = 0; i < 23; i++)
		{
			int High = i / 12;
			int Low = i % 12;

			for (int j = 0; j < 3; j++)
			{
				if (g_Mouse.IsBetween(TX.x + (Perc[j] + High)*OneW, TX.y + Low*OneH, OneW*(Perc[j + 1] - Perc[j]) - 1, OneH - 1, g_Mouse.Coords.x, g_Mouse.Coords.y)
					&& g_Mouse.IsClickValid() && g_Mouse.hasReleased())
				{
					if (j == 0)
					{
						Binds.KeysPrimary[Sorrend[i]] = 0;
						Binds.KeysSecondary[Sorrend[i]] = 0;
					}
					else if (j == 1)
					{
						OW_STATUS = 7;
						SettingKeySelected = Sorrend[i];
						SettingPrimerity = 0;
						PressKeyWaitFrames = 2;
					}
					else if (j == 2)
					{
						OW_STATUS = 7;
						SettingKeySelected = Sorrend[i];
						SettingPrimerity = 1;
						PressKeyWaitFrames = 2;
					}
				}

			}
		}
	}

	if (SettingsState == 1)
	{
		//Master volume slider
		auto width = _Window::GetTextSize("Brightness", fontsize).x;


		float barlength = g_Resolution.x*0.95f - (g_Resolution.x*0.05f + width + g_Resolution.x*0.01f);

		float sliderlength = g_Resolution.x*0.02f;
		float cum_barlength = barlength - sliderlength;

		float sliderPos = (g_Resolution.x*0.05f + width + g_Resolution.x*0.01f) + g_Config.mastervolume.Value*cum_barlength;
		float sliderStart = (g_Resolution.x*0.05f + width + g_Resolution.x*0.01f);
		static bool MV_Drag = false;

		if (g_Mouse.IsBetween(g_Resolution.x*0.05f + width + g_Resolution.x*0.01f, g_Resolution.y*0.15f, barlength, lineHeight + 4, g_Mouse.Coords.x, g_Mouse.Coords.y)
			&& g_Mouse.hasJustClicked())MV_Drag = true;
		if (!g_Mouse.left_click)MV_Drag = false;

		if (MV_Drag)
		{
			float perc = ((float)g_Mouse.Coords.x - sliderStart) / cum_barlength;
			if (perc < 0)perc = 0;
			if (perc > 1)perc = 1;
			g_Config.g_brightness.Value = 0.5f + 0.5f*perc;
		}

		sf::Vector2i Resolutions[] = { sf::Vector2i(640,480),sf::Vector2i(800,600),sf::Vector2i(1024,768),sf::Vector2i(1280,960),sf::Vector2i(1440,1080), sf::Vector2i(640,360),sf::Vector2i(1024,576),sf::Vector2i(1280,720),sf::Vector2i(1600,900),sf::Vector2i(1920,1080), sf::Vector2i(640,400),sf::Vector2i(1280,800),sf::Vector2i(1680,1050),sf::Vector2i(1680,720) };

		width = _Window::GetTextSize("Resolution", fontsize).x;

		auto AvailableWidth = g_Resolution.x*0.95f - (g_Resolution.x*0.05f + width + g_Resolution.x*0.01f);
		auto AvailableHeight = g_Resolution.y*0.7f - (g_Resolution.y*0.16f + lineHeight + 4);

		auto OneWidth = AvailableWidth / 2 - 1;
		auto OneHeight = AvailableHeight / 7 - 6;

		sf::Vector2f T = sf::Vector2f(g_Resolution.x*0.05f + width + g_Resolution.x*0.01f, (g_Resolution.y*0.16f + lineHeight + 4));

		for (int i = 0; i < 14; i++)
		{
			int High = i / 7;
			int Low = i % 7;

			auto pX = T.x + High*(OneWidth + 1);
			auto pY = T.y + Low*(OneHeight + 1);

			if (g_Mouse.IsBetween(pX, pY, OneWidth, OneHeight, g_Mouse.Coords.x, g_Mouse.Coords.y)
				&& g_Mouse.IsClickValid() && g_Mouse.isHolding())
			{
				SelectedVideoSetting = i;
			}


		}
		if (g_Mouse.IsBetween(g_Resolution.x*0.75f, g_Resolution.y*0.85f, g_Resolution.x*0.2f, g_Resolution.y*0.1f, g_Mouse.Coords.x, g_Mouse.Coords.y)
			&& g_Mouse.IsClickValid() && g_Mouse.hasReleased())
		{
			if (g_Resolution != Resolutions[SelectedVideoSetting] || g_Config.g_fullscreen.Value != SettingFullscreen)
			{
				g_Resolution = Resolutions[SelectedVideoSetting];
				g_Window->close();

				g_Config.g_res_x.Value = g_Resolution.x;
				g_Config.g_res_y.Value = g_Resolution.y;
				g_Config.g_fullscreen.Value = SettingFullscreen;

				_Window::CreateTheWindow();
			}
		}

		if (g_Mouse.IsBetween(T.x, g_Resolution.y*0.71, g_Resolution.y*0.08f, g_Resolution.y*0.08f, g_Mouse.Coords.x, g_Mouse.Coords.y)
			&& g_Mouse.IsClickValid() && g_Mouse.hasReleased())
			SettingFullscreen = !SettingFullscreen;
	}


	if (SettingsState == 2)
	{
		//Master volume slider
		auto width = _Window::GetTextSize("Master volume", fontsize).x;


		float barlength = g_Resolution.x*0.95f - (g_Resolution.x*0.05f + width + g_Resolution.x*0.01f);

		float sliderlength = g_Resolution.x*0.02f;
		float cum_barlength = barlength - sliderlength;

		float sliderPos = (g_Resolution.x*0.05f + width + g_Resolution.x*0.01f) + g_Config.mastervolume.Value*cum_barlength;
		float sliderStart = (g_Resolution.x*0.05f + width + g_Resolution.x*0.01f);
		static bool MV_Drag = false;

		if (g_Mouse.IsBetween(g_Resolution.x*0.05f + width + g_Resolution.x*0.01f, g_Resolution.y*0.15f, barlength, lineHeight + 4, g_Mouse.Coords.x, g_Mouse.Coords.y)
			&& g_Mouse.hasJustClicked())MV_Drag = true;
		if (!g_Mouse.left_click)MV_Drag = false;

		if (MV_Drag)
		{
			float perc = ((float)g_Mouse.Coords.x - sliderStart) / cum_barlength;
			if (perc < 0)perc = 0;
			if (perc > 1)perc = 1;
			g_Config.mastervolume.Value = perc;
		}
	}
}

void dc_game::DrawShowStatsMenu()
{
	_Window::RenderOverlay(0, 0, g_Resolution.x, g_Resolution.y, 0, 0, 0, 128);
	char BufferText[32], BufferPrint[32];
	{
		sprintf(BufferText, "Placement: ");
		sprintf(BufferPrint, "%d\0", Match->players[0].Stats.iPlacement);
		auto Dim = _Window::GetTextSize(BufferText, 0.04f*g_Resolution.y);

		_Window::RenderTextB(0.01f*g_Resolution.x, 0.2f*g_Resolution.y, BufferText, 0.04f*g_Resolution.y, 255, 255, 255, 255);
		_Window::RenderTextB(0.01f*g_Resolution.x + Dim.x, 0.2f*g_Resolution.y, BufferPrint, 0.04f*g_Resolution.y, 225, 180, 32, 255);
	}

	{
		sprintf(BufferText, "Eliminations: ");
		sprintf(BufferPrint, "%d\0", Match->players[0].Stats.iEliminations);
		auto Dim = _Window::GetTextSize(BufferText, 0.04f*g_Resolution.y);

		_Window::RenderTextB(0.01f*g_Resolution.x, 0.26f*g_Resolution.y, BufferText, 0.04f*g_Resolution.y, 255, 255, 255, 255);
		_Window::RenderTextB(0.01f*g_Resolution.x + Dim.x, 0.26f*g_Resolution.y, BufferPrint, 0.04f*g_Resolution.y, 225, 180, 32, 255);
	}
	{
		sprintf(BufferText, "Damage dealt: ");
		sprintf(BufferPrint, "%d\0", Match->players[0].Stats.iDamageDealt);
		auto Dim = _Window::GetTextSize(BufferText, 0.04f*g_Resolution.y);

		_Window::RenderTextB(0.01f*g_Resolution.x, 0.32f*g_Resolution.y, BufferText, 0.04f*g_Resolution.y, 255, 255, 255, 255);
		_Window::RenderTextB(0.01f*g_Resolution.x + Dim.x, 0.32f*g_Resolution.y, BufferPrint, 0.04f*g_Resolution.y, 225, 180, 32, 255);
	}
	{
		sprintf(BufferText, "Damage taken: ");
		sprintf(BufferPrint, "%d\0", Match->players[0].Stats.iDamageTaken);
		auto Dim = _Window::GetTextSize(BufferText, 0.04f*g_Resolution.y);

		_Window::RenderTextB(0.01f*g_Resolution.x, 0.38f*g_Resolution.y, BufferText, 0.04f*g_Resolution.y, 255, 255, 255, 255);
		_Window::RenderTextB(0.01f*g_Resolution.x + Dim.x, 0.38f*g_Resolution.y, BufferPrint, 0.04f*g_Resolution.y, 225, 180, 32, 255);
	}
	{
		sprintf(BufferText, "Shots Fired: ");
		sprintf(BufferPrint, "%d\0", Match->players[0].Stats.iShotsTaken);
		auto Dim = _Window::GetTextSize(BufferText, 0.04f*g_Resolution.y);

		_Window::RenderTextB(0.01f*g_Resolution.x, 0.44f*g_Resolution.y, BufferText, 0.04f*g_Resolution.y, 255, 255, 255, 255);
		_Window::RenderTextB(0.01f*g_Resolution.x + Dim.x, 0.44*g_Resolution.y, BufferPrint, 0.04f*g_Resolution.y, 225, 180, 32, 255);
	}
	{
		float Accuracy = 0.f;
		if (Match->players[0].Stats.iShotsTaken)Accuracy = (100.f*Match->players[0].Stats.iShotsHit) / (1.f*Match->players[0].Stats.iShotsTaken);
		sprintf(BufferText, "Shots Hit: ");
		sprintf(BufferPrint, "%d (%.1f%c)\0", Match->players[0].Stats.iShotsHit, Accuracy, '%');
		auto Dim = _Window::GetTextSize(BufferText, 0.04f*g_Resolution.y);

		_Window::RenderTextB(0.01f*g_Resolution.x, 0.50f*g_Resolution.y, BufferText, 0.04f*g_Resolution.y, 255, 255, 255, 255);
		_Window::RenderTextB(0.01f*g_Resolution.x + Dim.x, 0.50f*g_Resolution.y, BufferPrint, 0.04f*g_Resolution.y, 225, 180, 32, 255);
	}

	{
		sprintf(BufferText, "Distance walked: ");
		sprintf(BufferPrint, "%.1fm\0", Match->players[0].Stats.fDistanceWalked);
		auto Dim = _Window::GetTextSize(BufferText, 0.04f*g_Resolution.y);

		_Window::RenderTextB(0.01f*g_Resolution.x, 0.56f*g_Resolution.y, BufferText, 0.04f*g_Resolution.y, 255, 255, 255, 255);
		_Window::RenderTextB(0.01f*g_Resolution.x + Dim.x, 0.56f*g_Resolution.y, BufferPrint, 0.04f*g_Resolution.y, 225, 180, 32, 255);
	}
	{
		sprintf(BufferText, "Time alive: ");
		int Minutes = 0, Seconds = 0;
		int Time = Match->players[0].Stats.fTimeAlive;

		while (Time > 60)
		{
			Minutes++;
			Time -= 60;
		}
		Seconds = Time;


		sprintf(BufferPrint, "%d:%s%d", Minutes, ((Seconds<10) ? ("0") : ("")), Seconds);
		auto Dim = _Window::GetTextSize(BufferText, 0.04f*g_Resolution.y);

		_Window::RenderTextB(0.01f*g_Resolution.x, 0.62f*g_Resolution.y, BufferText, 0.04f*g_Resolution.y, 255, 255, 255, 255);
		_Window::RenderTextB(0.01f*g_Resolution.x + Dim.x, 0.62f*g_Resolution.y, BufferPrint, 0.04f*g_Resolution.y, 225, 180, 32, 255);
	}

}

void dc_game::DoShowStatsMenu()
{

}


int dc_game::DrawChallenge(int i, int x, int y, int w, int h)
{



	char Buffer[256];
	int ChallengeNameLines = 1;
	if (ThePlayer.Quests[i].type == 0 || ThePlayer.Quests[i].type == 1)
	{
		if (ThePlayer.Quests[i].killweapontype == 0)sprintf(Buffer, "Eliminations");
		else if (ThePlayer.Quests[i].killweapontype == 1)sprintf(Buffer, "Pistol eliminations");
		else if (ThePlayer.Quests[i].killweapontype == 2)sprintf(Buffer, "SMG eliminations");
		else if (ThePlayer.Quests[i].killweapontype == 3)sprintf(Buffer, "Shotgun eliminations");
		else if (ThePlayer.Quests[i].killweapontype == 4)sprintf(Buffer, "Rifle eliminations");
		else if (ThePlayer.Quests[i].killweapontype == 5)sprintf(Buffer, "Sniper eliminations");
		else if (ThePlayer.Quests[i].killweapontype == 6)sprintf(Buffer, "Explosive eliminations");
		else if (ThePlayer.Quests[i].killweapontype == 7)sprintf(Buffer, "Machine gun eliminations");

		if (ThePlayer.Quests[i].oneMatch)sprintf(Buffer, "%s in one match", Buffer);

		if (ThePlayer.Quests[i].type == 1) {
			char MiniBuffer[64];
			for (int j = 0; j < strlen(g_Map.labels[ThePlayer.Quests[i].location1].n); j++)
			{
				if (g_Map.labels[ThePlayer.Quests[i].location1].n[j] == '\n') {
					MiniBuffer[j] = ' ';
					MiniBuffer[j + 1] = '\0';
				}
				else {
					MiniBuffer[j] = g_Map.labels[ThePlayer.Quests[i].location1].n[j];
					MiniBuffer[j + 1] = '\0';
				}
			}

			sprintf(Buffer, "%s\n%s", Buffer, MiniBuffer);
			ChallengeNameLines++;
		}
	}
	else if (ThePlayer.Quests[i].type == 2 || ThePlayer.Quests[i].type == 3)
	{
		sprintf(Buffer, "Open chests");
		if (ThePlayer.Quests[i].oneMatch)sprintf(Buffer, "%s in one match", Buffer);

		if (ThePlayer.Quests[i].type == 3) {
			char MiniBuffer[64];
			for (int j = 0; j < strlen(g_Map.labels[ThePlayer.Quests[i].location1].n); j++)
			{
				if (g_Map.labels[ThePlayer.Quests[i].location1].n[j] == '\n') {
					MiniBuffer[j] = ' ';
					MiniBuffer[j + 1] = '\0';
				}
				else {
					MiniBuffer[j] = g_Map.labels[ThePlayer.Quests[i].location1].n[j];
					MiniBuffer[j + 1] = '\0';
				}
			}

			sprintf(Buffer, "%s\n%s", Buffer, MiniBuffer);
			ChallengeNameLines++;
		}
	}
	else if (ThePlayer.Quests[i].type == 4)
	{
		char MiniBuffer[64];
		for (int j = 0; j < strlen(g_Map.labels[ThePlayer.Quests[i].location1].n); j++)
		{
			if (g_Map.labels[ThePlayer.Quests[i].location1].n[j] == '\n') {
				MiniBuffer[j] = ' ';
				MiniBuffer[j + 1] = '\0';
			}
			else {
				MiniBuffer[j] = g_Map.labels[ThePlayer.Quests[i].location1].n[j];
				MiniBuffer[j + 1] = '\0';
			}
		}

		sprintf(Buffer, "Land at %s", MiniBuffer);
	}
	else if (ThePlayer.Quests[i].type == 5)
	{
		sprintf(Buffer, "Visit");
		if (ThePlayer.Quests[i].oneMatch)sprintf(Buffer, "%s in one match", Buffer);


		char MiniBuffer[64];
		if (ThePlayer.Quests[i].location1 != -1)
		{
			for (int j = 0; j < strlen(g_Map.labels[ThePlayer.Quests[i].location1].n); j++)
			{
				if (g_Map.labels[ThePlayer.Quests[i].location1].n[j] == '\n') {
					MiniBuffer[j] = ' ';
					MiniBuffer[j + 1] = '\0';
				}
				else {
					MiniBuffer[j] = g_Map.labels[ThePlayer.Quests[i].location1].n[j];
					MiniBuffer[j + 1] = '\0';
				}
			}
			sprintf(Buffer, "%s\n%s", Buffer, MiniBuffer);
			ChallengeNameLines++;
		}
		if (ThePlayer.Quests[i].location2 != -1)
		{
			for (int j = 0; j < strlen(g_Map.labels[ThePlayer.Quests[i].location2].n); j++)
			{
				if (g_Map.labels[ThePlayer.Quests[i].location2].n[j] == '\n') {
					MiniBuffer[j] = ' ';
					MiniBuffer[j + 1] = '\0';
				}
				else {
					MiniBuffer[j] = g_Map.labels[ThePlayer.Quests[i].location2].n[j];
					MiniBuffer[j + 1] = '\0';
				}
			}
			sprintf(Buffer, "%s\n%s", Buffer, MiniBuffer);
			ChallengeNameLines++;
		}

		if (ThePlayer.Quests[i].location3 != -1)
		{
			for (int j = 0; j < strlen(g_Map.labels[ThePlayer.Quests[i].location3].n); j++)
			{
				if (g_Map.labels[ThePlayer.Quests[i].location3].n[j] == '\n') {
					MiniBuffer[j] = ' ';
					MiniBuffer[j + 1] = '\0';
				}
				else {
					MiniBuffer[j] = g_Map.labels[ThePlayer.Quests[i].location3].n[j];
					MiniBuffer[j + 1] = '\0';
				}
			}
			sprintf(Buffer, "%s\n%s", Buffer, MiniBuffer);
			ChallengeNameLines++;
		}

	}
	else if (ThePlayer.Quests[i].type == 6)sprintf(Buffer, "Place top 10");
	else if (ThePlayer.Quests[i].type == 7)sprintf(Buffer, "Place top 25");

	int tier = ThePlayer.Quests[i].tierReward;
	int progress = ThePlayer.Quests[i].totalNeeded - ThePlayer.Quests[i].needed;
	int needed = ThePlayer.Quests[i].totalNeeded;
	float progperc = (1.f*progress) / needed;


	int fontsize = g_Resolution.y*(0.1f*w / (g_Resolution.x));

	auto lineheight = _Window::GetHeightForFontsize(fontsize);
	auto texH = ChallengeNameLines*lineheight;
	h = max(h, texH);


	if (tier == 5)
	{
		_Window::RenderOverlay(x, y, w, h + g_Resolution.y*0.005f + 10, 32, 32, 128, 255);
		_Window::RenderOverlay(x, y, w*0.0125f, h + g_Resolution.y*0.005f + 10, 64, 64, 255, 255);
		_Window::RenderTextB(x + 0.02631*w, y, Buffer, fontsize);

		char ProgressBuffer[16];
		sprintf(ProgressBuffer, "%d/%d", progress, needed);
		int leee = _Window::GetTextSize(ProgressBuffer, fontsize).x;

		_Window::RenderTextB(x + 0.97368421052*w - leee, y + h + 0.005f*g_Resolution.y - lineheight, ProgressBuffer, fontsize);
		_Window::RenderOverlay(x + 0.02631*w, y + h + 0.005f*g_Resolution.y, 0.9473f*w, 8, 0, 0, 0, 255);

		_Window::RenderOverlay(x + 0.02631*w, y + h + 0.005f*g_Resolution.y + 1, progperc*(0.9473f*w - 2), 6, 0, 177, 222, 255);
	}
	else
	{
		_Window::RenderOverlay(x, y, w, h + g_Resolution.y*0.005f + 10, 128, 32, 32, 255);
		_Window::RenderOverlay(x, y, w*0.0125f, h + g_Resolution.y*0.005f + 10, 255, 64, 64, 255);
		_Window::RenderTextB(x + 0.02631*w, y, Buffer, fontsize);

		char ProgressBuffer[16];
		sprintf(ProgressBuffer, "%d/%d", progress, needed);
		int leee = _Window::GetTextSize(ProgressBuffer, fontsize).x;

		_Window::RenderTextB(x + 0.97368421052*w - leee, y + h + 0.005f*g_Resolution.y - lineheight, ProgressBuffer, fontsize);
		_Window::RenderOverlay(x + 0.02631*w, y + h + 0.005f*g_Resolution.y, 0.9473f*w, 8, 0, 0, 0, 255);

		_Window::RenderOverlay(x + 0.02631*w, y + h + 0.005f*g_Resolution.y + 1, progperc*(0.9473f*w - 2), 6, 225, 128, 32, 255);
	}

	return h + g_Resolution.y*0.005f + 14;
}

int dc_game::DrawChallengeWithProgress(int i, int x, int y, int w, int h)
{



	char Buffer[256];
	int ChallengeNameLines = 1;
	if (ThePlayer.Quests[i].type == 0 || ThePlayer.Quests[i].type == 1)
	{
		if (ThePlayer.Quests[i].killweapontype == 0)sprintf(Buffer, "Eliminations");
		else if (ThePlayer.Quests[i].killweapontype == 1)sprintf(Buffer, "Pistol eliminations");
		else if (ThePlayer.Quests[i].killweapontype == 2)sprintf(Buffer, "SMG eliminations");
		else if (ThePlayer.Quests[i].killweapontype == 3)sprintf(Buffer, "Shotgun eliminations");
		else if (ThePlayer.Quests[i].killweapontype == 4)sprintf(Buffer, "Rifle eliminations");
		else if (ThePlayer.Quests[i].killweapontype == 5)sprintf(Buffer, "Sniper eliminations");
		else if (ThePlayer.Quests[i].killweapontype == 6)sprintf(Buffer, "Explosive eliminations");
		else if (ThePlayer.Quests[i].killweapontype == 7)sprintf(Buffer, "Machine gun eliminations");

		if (ThePlayer.Quests[i].oneMatch)sprintf(Buffer, "%s in one match", Buffer);

		if (ThePlayer.Quests[i].type == 1) {
			char MiniBuffer[64];
			for (int j = 0; j < strlen(g_Map.labels[ThePlayer.Quests[i].location1].n); j++)
			{
				if (g_Map.labels[ThePlayer.Quests[i].location1].n[j] == '\n') {
					MiniBuffer[j] = ' ';
					MiniBuffer[j + 1] = '\0';
				}
				else {
					MiniBuffer[j] = g_Map.labels[ThePlayer.Quests[i].location1].n[j];
					MiniBuffer[j + 1] = '\0';
				}
			}

			sprintf(Buffer, "%s\n%s", Buffer, MiniBuffer);
			ChallengeNameLines++;
		}
	}
	else if (ThePlayer.Quests[i].type == 2 || ThePlayer.Quests[i].type == 3)
	{
		sprintf(Buffer, "Open chests");
		if (ThePlayer.Quests[i].oneMatch)sprintf(Buffer, "%s in one match", Buffer);

		if (ThePlayer.Quests[i].type == 3) {
			char MiniBuffer[64];
			for (int j = 0; j < strlen(g_Map.labels[ThePlayer.Quests[i].location1].n); j++)
			{
				if (g_Map.labels[ThePlayer.Quests[i].location1].n[j] == '\n') {
					MiniBuffer[j] = ' ';
					MiniBuffer[j + 1] = '\0';
				}
				else {
					MiniBuffer[j] = g_Map.labels[ThePlayer.Quests[i].location1].n[j];
					MiniBuffer[j + 1] = '\0';
				}
			}

			sprintf(Buffer, "%s\n%s", Buffer, MiniBuffer);
			ChallengeNameLines++;
		}
	}
	else if (ThePlayer.Quests[i].type == 4)
	{
		char MiniBuffer[64];
		for (int j = 0; j < strlen(g_Map.labels[ThePlayer.Quests[i].location1].n); j++)
		{
			if (g_Map.labels[ThePlayer.Quests[i].location1].n[j] == '\n') {
				MiniBuffer[j] = ' ';
				MiniBuffer[j + 1] = '\0';
			}
			else {
				MiniBuffer[j] = g_Map.labels[ThePlayer.Quests[i].location1].n[j];
				MiniBuffer[j + 1] = '\0';
			}
		}

		sprintf(Buffer, "Land at %s", MiniBuffer);
	}
	else if (ThePlayer.Quests[i].type == 5)
	{
		sprintf(Buffer, "Visit");
		if (ThePlayer.Quests[i].oneMatch)sprintf(Buffer, "%s in one match", Buffer);


		char MiniBuffer[64];
		if (ThePlayer.Quests[i].location1 != -1)
		{
			for (int j = 0; j < strlen(g_Map.labels[ThePlayer.Quests[i].location1].n); j++)
			{
				if (g_Map.labels[ThePlayer.Quests[i].location1].n[j] == '\n') {
					MiniBuffer[j] = ' ';
					MiniBuffer[j + 1] = '\0';
				}
				else {
					MiniBuffer[j] = g_Map.labels[ThePlayer.Quests[i].location1].n[j];
					MiniBuffer[j + 1] = '\0';
				}
			}
			sprintf(Buffer, "%s\n%s", Buffer, MiniBuffer);
			ChallengeNameLines++;
		}
		if (ThePlayer.Quests[i].location2 != -1)
		{
			for (int j = 0; j < strlen(g_Map.labels[ThePlayer.Quests[i].location2].n); j++)
			{
				if (g_Map.labels[ThePlayer.Quests[i].location2].n[j] == '\n') {
					MiniBuffer[j] = ' ';
					MiniBuffer[j + 1] = '\0';
				}
				else {
					MiniBuffer[j] = g_Map.labels[ThePlayer.Quests[i].location2].n[j];
					MiniBuffer[j + 1] = '\0';
				}
			}
			sprintf(Buffer, "%s\n%s", Buffer, MiniBuffer);
			ChallengeNameLines++;
		}

		if (ThePlayer.Quests[i].location3 != -1)
		{
			for (int j = 0; j < strlen(g_Map.labels[ThePlayer.Quests[i].location3].n); j++)
			{
				if (g_Map.labels[ThePlayer.Quests[i].location3].n[j] == '\n') {
					MiniBuffer[j] = ' ';
					MiniBuffer[j + 1] = '\0';
				}
				else {
					MiniBuffer[j] = g_Map.labels[ThePlayer.Quests[i].location3].n[j];
					MiniBuffer[j + 1] = '\0';
				}
			}
			sprintf(Buffer, "%s\n%s", Buffer, MiniBuffer);
			ChallengeNameLines++;
		}

	}
	else if (ThePlayer.Quests[i].type == 6)sprintf(Buffer, "Place top 10");
	else if (ThePlayer.Quests[i].type == 7)sprintf(Buffer, "Place top 25");

	int tier = ThePlayer.Quests[i].tierReward;
	int progress = ThePlayer.Quests[i].totalNeeded - ThePlayer.Quests[i].needed;
	int needed = ThePlayer.Quests[i].totalNeeded;
	float progperc = (1.f*progress) / needed;
	int newprogress = progress + GetEvaluateMatchForQuests(i);
	float newprogperc = (1.f*newprogress) / needed;

	int fontsize = g_Resolution.y*(0.1f*w / (g_Resolution.x));

	auto lineheight = _Window::GetHeightForFontsize(fontsize);
	auto texH = ChallengeNameLines*lineheight;
	h = max(h, texH);



	if (tier == 5)
	{
		_Window::RenderOverlay(x, y, w, h + g_Resolution.y*0.005f + 10, 32, 32, 128, 255);
		_Window::RenderOverlay(x, y, w*0.0125f, h + g_Resolution.y*0.005f + 10, 64, 64, 255, 255);
		_Window::RenderTextB(x + 0.02631*w, y, Buffer, fontsize);

		char ProgressBuffer[16];
		sprintf(ProgressBuffer, "%d/%d", newprogress, needed);
		int leee = _Window::GetTextSize(ProgressBuffer, fontsize).x;

		_Window::RenderTextB(x + 0.97368421052*w - leee, y + h + 0.005f*g_Resolution.y - lineheight, ProgressBuffer, fontsize);
		_Window::RenderOverlay(x + 0.02631*w, y + h + 0.005f*g_Resolution.y, 0.9473f*w, 8, 0, 0, 0, 255);
		_Window::RenderOverlay(x + 0.02631*w, y + h + 0.005f*g_Resolution.y + 1, newprogperc*(0.9473f*w - 2), 6, 64, 215, 255, 255);
		_Window::RenderOverlay(x + 0.02631*w, y + h + 0.005f*g_Resolution.y + 1, progperc*(0.9473f*w - 2), 6, 0, 177, 222, 255);
	}
	else
	{
		_Window::RenderOverlay(x, y, w, h + g_Resolution.y*0.005f + 10, 128, 32, 32, 255);
		_Window::RenderOverlay(x, y, w*0.0125f, h + g_Resolution.y*0.005f + 10, 255, 64, 64, 255);
		_Window::RenderTextB(x + 0.02631*w, y, Buffer, fontsize);

		char ProgressBuffer[16];
		sprintf(ProgressBuffer, "%d/%d", newprogress, needed);
		int leee = _Window::GetTextSize(ProgressBuffer, fontsize).x;


		_Window::RenderTextB(x + 0.97368421052*w - leee, y + h + 0.005f*g_Resolution.y - lineheight, ProgressBuffer, fontsize);
		_Window::RenderOverlay(x + 0.02631*w, y + h + 0.005f*g_Resolution.y, 0.9473f*w, 8, 0, 0, 0, 255);

		_Window::RenderOverlay(x + 0.02631*w, y + h + 0.005f*g_Resolution.y + 1, newprogperc*(0.9473f*w - 2), 6, 255, 220, 96, 255);
		_Window::RenderOverlay(x + 0.02631*w, y + h + 0.005f*g_Resolution.y + 1, progperc*(0.9473f*w - 2), 6, 225, 128, 32, 255);
	}

	return h + g_Resolution.y*0.005f + 14;
}

void dc_game::DoBackButton()
{
	if (g_Mouse.IsBetween(g_Resolution.x*0.01f, g_Resolution.y*0.01f, g_Resolution.x*0.05f, g_Resolution.y*0.03f, g_Mouse.Coords.x, g_Mouse.Coords.y)
		&& g_Mouse.IsClickValid() && g_Mouse.hasReleased())
	{
		GM_STATE = 0;
	}
}

void dc_game::DrawBackButton()
{
	_Window::RenderOverlay(g_Resolution.x*0.01f, g_Resolution.y*0.01f, g_Resolution.x*0.05f, g_Resolution.y*0.03f, 0, 0, 0, 255);
	if (g_Mouse.IsBetween(g_Resolution.x*0.01f, g_Resolution.y*0.01f, g_Resolution.x*0.05f, g_Resolution.y*0.03f, g_Mouse.Coords.x, g_Mouse.Coords.y)
		&& g_Mouse.IsClickValid() && g_Mouse.isHolding())
		_Window::RenderOverlay(g_Resolution.x*0.01f + 1, g_Resolution.y*0.01f + 1, g_Resolution.x*0.05f - 2, g_Resolution.y*0.03f - 2, 144,128, 32, 255);
	else if (g_Mouse.IsBetween(g_Resolution.x*0.01f, g_Resolution.y*0.01f, g_Resolution.x*0.05f, g_Resolution.y*0.03f, g_Mouse.Coords.x, g_Mouse.Coords.y))
		_Window::RenderOverlay(g_Resolution.x*0.01f + 1, g_Resolution.y*0.01f + 1, g_Resolution.x*0.05f - 2, g_Resolution.y*0.03f - 2, 255, 222, 64, 255);
	else
		_Window::RenderOverlay(g_Resolution.x*0.01f + 1, g_Resolution.y*0.01f + 1, g_Resolution.x*0.05f - 2, g_Resolution.y*0.03f - 2, 220, 160, 0, 255);

	_Window::RenderTextBMiddleC(g_Resolution.x*0.01f, g_Resolution.y*0.01f, g_Resolution.x*0.05f, g_Resolution.y*0.03f, "Back", g_Resolution.y*0.02f, 0, 0, 0, 255);

}

void dc_game::DrawQuitButton()
{
	_Window::RenderOverlay(g_Resolution.x*0.96f, g_Resolution.y*0.01f, g_Resolution.x*0.03f, g_Resolution.y*0.03f, 0, 0, 0, 255);
	if(g_Mouse.IsBetween(g_Resolution.x*0.96f,g_Resolution.y*0.01f,g_Resolution.x*0.03f,g_Resolution.y*0.03f,g_Mouse.Coords.x,g_Mouse.Coords.y)
		&& g_Mouse.IsClickValid() && g_Mouse.isHolding())
		_Window::RenderOverlay(g_Resolution.x*0.96f+1, g_Resolution.y*0.01f+1, g_Resolution.x*0.03f-2, g_Resolution.y*0.03f-2, 128, 32, 32, 255);
	else if (g_Mouse.IsBetween(g_Resolution.x*0.96f, g_Resolution.y*0.01f, g_Resolution.x*0.03f, g_Resolution.y*0.03f, g_Mouse.Coords.x, g_Mouse.Coords.y))
		_Window::RenderOverlay(g_Resolution.x*0.96f + 1, g_Resolution.y*0.01f + 1, g_Resolution.x*0.03f - 2, g_Resolution.y*0.03f - 2, 255, 64, 64, 255);
	else
		_Window::RenderOverlay(g_Resolution.x*0.96f + 1, g_Resolution.y*0.01f + 1, g_Resolution.x*0.03f - 2, g_Resolution.y*0.03f - 2, 255, 0, 0, 255);

	_Window::RenderTextBMiddleC(g_Resolution.x*0.96f, g_Resolution.y*0.01f, g_Resolution.x*0.03f, g_Resolution.y*0.03f, "X", g_Resolution.y*0.02f, 0, 0, 0, 255);
}

void dc_game::DoQuitButton()
{
	if (g_Mouse.IsBetween(g_Resolution.x*0.96f, g_Resolution.y*0.01f, g_Resolution.x*0.03f, g_Resolution.y*0.03f, g_Mouse.Coords.x, g_Mouse.Coords.y)
		&& g_Mouse.IsClickValid() && g_Mouse.hasReleased())
	{
		OW_STATUS = 5;
	}
}

void dc_game::DrawQuitPrompt()
{
	_Window::RenderOverlay(0, 0, g_Resolution.x, g_Resolution.y, 0, 0, 0, 96);

	_Window::RenderOverlay(g_Resolution.x*0.35f, g_Resolution.y*0.3f, g_Resolution.x*0.3f, g_Resolution.y*0.4f, 32, 96, 192, 255);
	_Window::RenderOverlay(g_Resolution.x*0.35f+2, g_Resolution.y*0.3f+2, g_Resolution.x*0.3f-4, g_Resolution.y*0.4f-4, 16, 48,96, 255);

	_Window::RenderTextB(g_Resolution.x*0.36f, g_Resolution.y*0.31f, "Would you like to quit?", g_Resolution.y*0.02f);


	if (g_Mouse.IsBetween(g_Resolution.x*0.37f, g_Resolution.y*0.6f, g_Resolution.x*0.1f, g_Resolution.y*0.08f, g_Mouse.Coords.x, g_Mouse.Coords.y)
		&& g_Mouse.IsClickValid() && g_Mouse.isHolding())
		_Window::RenderOverlay(g_Resolution.x*0.37f, g_Resolution.y*0.6f, g_Resolution.x*0.1f, g_Resolution.y*0.08f, 140,110,32, 255);
	else if (g_Mouse.IsBetween(g_Resolution.x*0.37f, g_Resolution.y*0.6f, g_Resolution.x*0.1f, g_Resolution.y*0.08f, g_Mouse.Coords.x, g_Mouse.Coords.y))
		_Window::RenderOverlay(g_Resolution.x*0.37f, g_Resolution.y*0.6f, g_Resolution.x*0.1f, g_Resolution.y*0.08f, 255,230,64, 255);
	else _Window::RenderOverlay(g_Resolution.x*0.37f, g_Resolution.y*0.6f, g_Resolution.x*0.1f, g_Resolution.y*0.08f, 225,180,32, 255);

	_Window::RenderTextBMiddleC(g_Resolution.x*0.37f, g_Resolution.y*0.6f, g_Resolution.x*0.1f, g_Resolution.y*0.08f, "NO", g_Resolution.y*0.03f,0,0,0);

	if (g_Mouse.IsBetween(g_Resolution.x*0.53f, g_Resolution.y*0.6f, g_Resolution.x*0.1f, g_Resolution.y*0.08f, g_Mouse.Coords.x, g_Mouse.Coords.y)
		&& g_Mouse.IsClickValid() && g_Mouse.isHolding())
		_Window::RenderOverlay(g_Resolution.x*0.53f, g_Resolution.y*0.6f, g_Resolution.x*0.1f, g_Resolution.y*0.08f, 140,110,32, 255);
	else if (g_Mouse.IsBetween(g_Resolution.x*0.53f, g_Resolution.y*0.6f, g_Resolution.x*0.1f, g_Resolution.y*0.08f, g_Mouse.Coords.x, g_Mouse.Coords.y))
		_Window::RenderOverlay(g_Resolution.x*0.53f, g_Resolution.y*0.6f, g_Resolution.x*0.1f, g_Resolution.y*0.08f, 255,230,64, 255);
	else _Window::RenderOverlay(g_Resolution.x*0.53f, g_Resolution.y*0.6f, g_Resolution.x*0.1f, g_Resolution.y*0.08f, 225,180,32, 255);

	_Window::RenderTextBMiddleC(g_Resolution.x*0.53f, g_Resolution.y*0.6f, g_Resolution.x*0.1f, g_Resolution.y*0.08f, "YES", g_Resolution.y*0.03f,0,0,0);
}

void dc_game::DoQuitPrompt()
{
	if (g_Mouse.IsBetween(g_Resolution.x*0.37f, g_Resolution.y*0.6f, g_Resolution.x*0.1f, g_Resolution.y*0.08f, g_Mouse.Coords.x, g_Mouse.Coords.y)
		&& g_Mouse.IsClickValid() && g_Mouse.hasReleased())OW_STATUS = 0;
	
	if (g_Mouse.IsBetween(g_Resolution.x*0.53f, g_Resolution.y*0.6f, g_Resolution.x*0.1f, g_Resolution.y*0.08f, g_Mouse.Coords.x, g_Mouse.Coords.y)
		&& g_Mouse.IsClickValid() && g_Mouse.hasReleased())Quit();

	if(!g_Mouse.IsBetween(g_Resolution.x*0.35f, g_Resolution.y*0.3f, g_Resolution.x*0.3f, g_Resolution.y*0.4f, g_Mouse.Coords.x, g_Mouse.Coords.y)
		&& g_Mouse.IsClickValid() && g_Mouse.hasReleased())OW_STATUS = 0;
}

int GetRandomTextureBackground(bool update = false)
{
	static bool run = false;
	static std::vector<int> nontextures;
	if (!run)
	{
		nontextures.push_back(3);
		nontextures.push_back(4);
		nontextures.push_back(5);
		nontextures.push_back(50);
		nontextures.push_back(51);
		nontextures.push_back(52);
		nontextures.push_back(53);
		nontextures.push_back(54);
		nontextures.push_back(55);
		nontextures.push_back(56);
		nontextures.push_back(57);
		nontextures.push_back(58);
		nontextures.push_back(67);
		nontextures.push_back(68);

		run = true;
	}

	static int TextReturn = 3;
	if(update || IsIn(nontextures,TextReturn))
	{
		TextReturn = 3;
		while (IsIn(nontextures, TextReturn))
		{
			TextReturn = Random(0, g_Textures.t.size() - 1);
		}
	}
	return TextReturn;
}

void dc_game::DoMainMenuCharacterVision()
{
	float scale = (0.25f*g_Resolution.y / 128.f);

	if (g_Mouse.IsBetween(g_Resolution.x*0.06f, g_Resolution.y*0.1f, scale * 128, scale * 128, g_Mouse.Coords.x, g_Mouse.Coords.y)
		&& g_Mouse.IsClickValid() && g_Mouse.hasReleased())GetRandomTextureBackground(true);

	for (int i = 0; i < 3; i++)
	{
		if (g_Mouse.IsBetween(g_Resolution.x*0.06f + scale * 128 + 4, g_Resolution.y*0.1f + 0.334f*i*g_Resolution.y*0.25f, g_Resolution.x*0.29f - (g_Resolution.x*0.06f + scale * 128 + 4), g_Resolution.y*0.25f / 3 - 2, g_Mouse.Coords.x, g_Mouse.Coords.y)
			&& g_Mouse.IsClickValid() && g_Mouse.hasReleased())CharacterVisionStatus = i;
	}
	float fontsize = 0.03f*g_Resolution.y;
	auto lineHeight = _Window::GetTextSize("a\n", fontsize).y - _Window::GetTextSize("a", fontsize).y;
	if (GM_STATE == 0 && g_Mouse.IsBetween(g_Resolution.x*0.05f, g_Resolution.y*0.375f, g_Resolution.x*0.25f, lineHeight + 4, g_Mouse.Coords.x, g_Mouse.Coords.y)
		&& g_Mouse.IsClickValid() && g_Mouse.hasReleased())
	{
		GM_STATE = 5;
		LockerPush = ThePlayer.Tier;
	}
}
void dc_game::DrawMainMenuCharacterVision()
{
	_Window::RenderOverlay(g_Resolution.x*0.05f, g_Resolution.y*0.05f, g_Resolution.x*0.25f, g_Resolution.y*0.325f, 192, 192, 192, 64);
	
	_Window::RenderTextBMiddleC(g_Resolution.x*0.05f, g_Resolution.y*0.05f, g_Resolution.x*0.25f, g_Resolution.y*0.05f, "CHARACTER VIEW", g_Resolution.y*0.03f);
	static sf::Sprite spTex, spPl, spGl, spWW;
	spTex.setTexture(*g_Textures.get(GetRandomTextureBackground()));
	
	float scale = (0.25f*g_Resolution.y / 128.f);

	spTex.setScale(scale, scale);
	spTex.setPosition(g_Resolution.x*0.06f, g_Resolution.y*0.1f);
	g_Window->draw(spTex);

	spPl.setTexture(*g_Textures.get(3));
	spGl.setTexture(*g_Textures.get(68));
	spWW.setTexture(*g_Textures.get(53));

	if (CharacterVisionStatus == 2)
	{
		static dc_clock Clock;
		static int wID = Random(0, 30);

		if (Clock.deltaTime() > 500)
		{
			wID = Random(0, 30);
			Clock.Update();
		}

		spWW.setPosition(g_Resolution.x*0.06f + scale*(64), g_Resolution.y*0.1f + scale*(64));
		spWW.setTextureRect(sf::IntRect(96 * wID, 96*ThePlayer.SelectedWrap, 96,96));
		spWW.setOrigin(48, 48);
		spWW.setScale(scale, scale);
		g_Window->draw(spWW);
	}

	spPl.setPosition(g_Resolution.x*0.06f + scale*(64), g_Resolution.y*0.1f + scale*(64));
	spPl.setTextureRect(sf::IntRect(64 * (ThePlayer.SelectedSkin + 1), 0, 64, 64));
	spPl.setOrigin(32, 32);
	spPl.setScale(scale, scale);
	g_Window->draw(spPl);
	spPl.setTextureRect(sf::IntRect(0, 0, 64, 64));
	g_Window->draw(spPl);

	if (CharacterVisionStatus == 1)
	{
		spGl.setPosition(g_Resolution.x*0.06f + scale*(64), g_Resolution.y*0.1f + scale*(64));
		spGl.setTextureRect(sf::IntRect(128 * (ThePlayer.SelectedGlider), 0, 128, 128));
		spGl.setOrigin(64, 64);
		spGl.setScale(scale, scale);
		g_Window->draw(spGl);
	}

	char* tT[] = { "Skin","Glider","Wrap" };
	for (int i = 0; i < 3; i++)
	{
		if(g_Mouse.IsBetween(g_Resolution.x*0.06f + scale * 128 + 4, g_Resolution.y*0.1f + 0.334f*i*g_Resolution.y*0.25f, g_Resolution.x*0.29f - (g_Resolution.x*0.06f + scale * 128 + 4), g_Resolution.y*0.25f / 3 - 2,g_Mouse.Coords.x,g_Mouse.Coords.y)
			&& g_Mouse.IsClickValid() && g_Mouse.isHolding())
		_Window::RenderOverlay(g_Resolution.x*0.06f + scale * 128 + 4, g_Resolution.y*0.1f+0.334f*i*g_Resolution.y*0.25f, g_Resolution.x*0.29f - (g_Resolution.x*0.06f + scale * 128 + 4), g_Resolution.y*0.25f / 3 - 2, 140, 110, 32, 255);
		else if (i == CharacterVisionStatus)
			_Window::RenderOverlay(g_Resolution.x*0.06f + scale * 128 + 4, g_Resolution.y*0.1f + 0.334f*i*g_Resolution.y*0.25f, g_Resolution.x*0.29f - (g_Resolution.x*0.06f + scale * 128 + 4), g_Resolution.y*0.25f / 3 - 2, 140, 110, 32, 255);

		else if (g_Mouse.IsBetween(g_Resolution.x*0.06f + scale * 128 + 4, g_Resolution.y*0.1f + 0.334f*i*g_Resolution.y*0.25f, g_Resolution.x*0.29f - (g_Resolution.x*0.06f + scale * 128 + 4), g_Resolution.y*0.25f / 3 - 2, g_Mouse.Coords.x, g_Mouse.Coords.y))
			_Window::RenderOverlay(g_Resolution.x*0.06f + scale * 128 + 4, g_Resolution.y*0.1f + 0.334f*i*g_Resolution.y*0.25f, g_Resolution.x*0.29f - (g_Resolution.x*0.06f + scale * 128 + 4), g_Resolution.y*0.25f / 3 - 2, 255, 230, 64, 255);
		else
			_Window::RenderOverlay(g_Resolution.x*0.06f + scale * 128 + 4, g_Resolution.y*0.1f + 0.334f*i*g_Resolution.y*0.25f, g_Resolution.x*0.29f - (g_Resolution.x*0.06f + scale * 128 + 4), g_Resolution.y*0.25f / 3 - 2, 225, 180, 32, 255);

		_Window::RenderTextBMiddleC(g_Resolution.x*0.06f + scale * 128 + 4, g_Resolution.y*0.1f + 0.334f*i*g_Resolution.y*0.25f, g_Resolution.x*0.29f - (g_Resolution.x*0.06f + scale * 128 + 4), g_Resolution.y*0.25f / 3 - 2, tT[i], g_Resolution.y*0.02f, 0, 0, 0, 255);
	}

	if (GM_STATE == 0)
	{
		float fontsize = 0.03f*g_Resolution.y;
		auto lineHeight = _Window::GetTextSize("a\n", fontsize).y - _Window::GetTextSize("a", fontsize).y;

		if (g_Mouse.IsBetween(g_Resolution.x*0.05f, g_Resolution.y*0.375f, g_Resolution.x*0.25f, lineHeight + 4, g_Mouse.Coords.x, g_Mouse.Coords.y)
			&& g_Mouse.IsClickValid() && g_Mouse.isHolding())
			_Window::RenderOverlay(g_Resolution.x*0.05f, g_Resolution.y*0.375f, g_Resolution.x*0.25f, lineHeight + 4, 160, 120, 16, 255);
		else if (g_Mouse.IsBetween(g_Resolution.x*0.05f, g_Resolution.y*0.375f, g_Resolution.x*0.25f, lineHeight + 4, g_Mouse.Coords.x, g_Mouse.Coords.y))
			_Window::RenderOverlay(g_Resolution.x*0.05f, g_Resolution.y*0.375f, g_Resolution.x*0.25f, lineHeight + 4, 255, 222, 64, 255);
		else _Window::RenderOverlay(g_Resolution.x*0.05f, g_Resolution.y*0.375f, g_Resolution.x*0.25f, lineHeight + 4, 225, 180, 32, 255);

		_Window::RenderTextBMiddleC(g_Resolution.x*0.05f, g_Resolution.y*0.375f, g_Resolution.x*0.25f, lineHeight + 4, "Locker", fontsize, 0, 0, 0, 255);
	}
}

void dc_game::DoLockerMenu()
{
	DoBackButton();
	DoMainMenuCharacterVision();

	float totalSize = g_Resolution.x*0.84f;
	float oneSize = totalSize / 7;
	float lScale = 0.5f*oneSize / 64.f;
	if (g_Mouse.IsBetween(g_Resolution.x*0.05f - lScale * 36, g_Resolution.y*0.95f - oneSize + lScale * 32, lScale * 32, lScale * 64, g_Mouse.Coords.x, g_Mouse.Coords.y)
		&& g_Mouse.IsClickValid() && g_Mouse.hasReleased())LockerPush -= 5;

	if (g_Mouse.IsBetween(g_Resolution.x*0.95f + lScale * 4, g_Resolution.y*0.95f - oneSize + lScale * 32, lScale * 32, lScale * 64, g_Mouse.Coords.x, g_Mouse.Coords.y)
		&& g_Mouse.IsClickValid() && g_Mouse.hasReleased())LockerPush += 5;


	if (LockerPush < 0)LockerPush = 0;
	if (LockerPush > 93)LockerPush = 93;

	DoLockerInventory();
}

void dc_game::DrawLockerItemShowCase(int lu_index)
{
	auto u = Unlockables[lu_index];

	_Window::RenderOverlay(g_Resolution.x*0.05f, g_Resolution.y*0.375f, g_Resolution.x*0.02f + g_Resolution.y*0.25f, g_Resolution.y*0.275f, 192, 192, 192, 64);

	static sf::Color rarities[] = { sf::Color(255,255,255,128),sf::Color(90, 180, 0, 170),sf::Color(60, 190, 250, 200),sf::Color(200, 105, 235, 255),sf::Color(240, 150, 40, 255), sf::Color(255,32,32,255) };
	char r = rarities[Unlockables[lu_index].iRarity].r;
	char g = rarities[Unlockables[lu_index].iRarity].g;
	char b = rarities[Unlockables[lu_index].iRarity].b;
	char a = rarities[Unlockables[lu_index].iRarity].a;

	_Window::RenderTextBMiddleC(g_Resolution.x*0.05f, g_Resolution.y*0.625f, g_Resolution.x*0.02f+g_Resolution.y*0.25f, g_Resolution.y*0.025f, Unlockables[lu_index].szName, g_Resolution.y*0.02f, r, g, b, a);

	static sf::Sprite spTex, spPl, spGl, spWW;
	spTex.setTexture(*g_Textures.get(GetRandomTextureBackground()));

	float scale = (0.25f*g_Resolution.y / 128.f);

	spTex.setScale(scale, scale);
	spTex.setPosition(g_Resolution.x*0.06f, g_Resolution.y*0.35f);
	g_Window->draw(spTex);

	spPl.setTexture(*g_Textures.get(3));
	spGl.setTexture(*g_Textures.get(68));
	spWW.setTexture(*g_Textures.get(53));

	if (u.Type == 2)
	{
		static dc_clock Clock;
		static int wID = Random(0, 30);

		if (Clock.deltaTime() > 500)
		{
			wID = Random(0, 30);
			Clock.Update();
		}

		spWW.setPosition(g_Resolution.x*0.06f + scale*(64), g_Resolution.y*0.35f + scale*(64));
		spWW.setTextureRect(sf::IntRect(96 * wID, 96 * u.Index, 96, 96));
		spWW.setOrigin(48, 48);
		spWW.setScale(scale, scale);
		g_Window->draw(spWW);
	}
	int ind = ThePlayer.SelectedSkin;
	if (u.Type == 0)ind = u.Index;
	spPl.setPosition(g_Resolution.x*0.06f + scale*(64), g_Resolution.y*0.35f + scale*(64));
	spPl.setTextureRect(sf::IntRect(64 * (ind + 1), 0, 64, 64));
	spPl.setOrigin(32, 32);
	spPl.setScale(scale, scale);
	g_Window->draw(spPl);
	spPl.setTextureRect(sf::IntRect(0, 0, 64, 64));
	g_Window->draw(spPl);

	if (u.Type == 1)
	{
		spGl.setPosition(g_Resolution.x*0.06f + scale*(64), g_Resolution.y*0.35f + scale*(64));
		spGl.setTextureRect(sf::IntRect(128 * (u.Index), 0, 128, 128));
		spGl.setOrigin(64, 64);
		spGl.setScale(scale, scale);
		g_Window->draw(spGl);
	}


}

void dc_game::DrawLockerMenuNextUnlockables()
{
	float totalSize = g_Resolution.x*0.84f;
	float oneSize = totalSize / 7;

	static sf::Sprite spPl, spGl, spWW;
	spPl.setTexture(*g_Textures.get(3));
	spGl.setTexture(*g_Textures.get(68));
	spWW.setTexture(*g_Textures.get(53));

	for (int i = 0; i < 7; i++)
	{
		int fontsize = 0.02f*g_Resolution.y;
		int textHeight = _Window::GetHeightForFontsize(fontsize);


		sf::RectangleShape Rect;
		Rect.setSize(sf::Vector2f(oneSize, oneSize));
		Rect.setPosition(g_Resolution.x*0.05f + (oneSize + 0.01f*g_Resolution.x)*i, g_Resolution.y*0.95f - oneSize);
		Rect.setFillColor(sf::Color(192, 192, 192, 64));
		if (ThePlayer.Tier > LockerPush+i)
		{
			Rect.setOutlineThickness(1.f);
			Rect.setOutlineColor(sf::Color(160, 240, 32));
		}
		else if (ThePlayer.Tier == LockerPush + i)
		{
			Rect.setOutlineThickness(1.f);
			Rect.setOutlineColor(sf::Color(255,255,255));
		}
		g_Window->draw(Rect);

		//IWindow::RenderOverlay(g_Resolution.x*0.05f + (oneSize + 0.01f*g_Resolution.x)*i, g_Resolution.y*0.95f- oneSize, oneSize, oneSize, 192, 192, 192, 64);

		int tier = LockerPush+i;
		char Buffer[16]; sprintf(Buffer, "Tier %d", tier+1);
		_Window::RenderTextB(g_Resolution.x*0.05f + (oneSize + 0.01f*g_Resolution.x)*i, g_Resolution.y*0.95f - oneSize - textHeight - 2, Buffer, fontsize);

		for (int j = 0; j< Unlockables.size();j++)
		{
			
			auto &u = Unlockables[j];
			if (u.Tier == tier)
			{
				if(g_Mouse.IsBetween(g_Resolution.x*0.05f + (oneSize + 0.01f*g_Resolution.x)*i, g_Resolution.y*0.95f - oneSize, oneSize, oneSize,g_Mouse.Coords.x,g_Mouse.Coords.y))
					DrawLockerItemShowCase(j);
				if (u.Type == 0)
				{
					float scale = (oneSize - g_Resolution.x*0.02f)/64.f;
					spPl.setScale(scale, scale);
					spPl.setPosition(g_Resolution.x*0.05f + (oneSize + 0.01f*g_Resolution.x)*i + 0.5f*oneSize, g_Resolution.y*0.95f - 0.5f*oneSize);
					spPl.setOrigin(32, 32);
					spPl.setTextureRect(sf::IntRect((u.Index + 1) * 64, 0, 64, 64));
					g_Window->draw(spPl);
					spPl.setTextureRect(sf::IntRect(0, 0, 64, 64));
					g_Window->draw(spPl);
				}
				if (u.Type == 1)
				{
					float scale = (oneSize - g_Resolution.x*0.02f) / 128.f;
					spGl.setScale(scale, scale);
					spGl.setPosition(g_Resolution.x*0.05f + (oneSize + 0.01f*g_Resolution.x)*i + 0.5f*oneSize, g_Resolution.y*0.95f - 0.5f*oneSize);
					spGl.setOrigin(64, 64);
					spGl.setTextureRect(sf::IntRect((u.Index) * 128, 0, 128, 128));
					g_Window->draw(spGl);
				}
				if (u.Type == 2)
				{
					static dc_clock Clock;
					static int wID = Random(0, 30);
					if (Clock.deltaTime() > 500)
					{
						wID = Random(0, 30);
						Clock.Update();
					}



					float scale = (oneSize - g_Resolution.x*0.02f) / 96.f;
					spWW.setScale(scale, scale);
					spWW.setPosition(g_Resolution.x*0.05f + (oneSize + 0.01f*g_Resolution.x)*i + 0.5f*oneSize, g_Resolution.y*0.95f - 0.5f*oneSize);
					spWW.setOrigin(48, 48);
					spWW.setTextureRect(sf::IntRect(wID*96, u.Index*96, 64, 64));
					g_Window->draw(spWW);

					spPl.setScale(scale, scale);
					spPl.setPosition(g_Resolution.x*0.05f + (oneSize + 0.01f*g_Resolution.x)*i + 0.5f*oneSize, g_Resolution.y*0.95f - 0.5f*oneSize);
					spPl.setOrigin(32, 32);
					spPl.setTextureRect(sf::IntRect(ThePlayer.SelectedSkin * 64+64, 0, 64, 64));
					g_Window->draw(spPl);
					spPl.setTextureRect(sf::IntRect(0, 0, 64, 64));
					g_Window->draw(spPl);
				}
			}
		}

	
	}

	static sf::Sprite logosSprite;
	static bool bRun = false;
	if (!bRun)
	{
		logosSprite.setTexture(*g_Textures.get(51));
		bRun = true;
	}

	float lScale = 0.5f*oneSize / 64.f;
	logosSprite.setScale(lScale, lScale);

	logosSprite.setTextureRect(sf::IntRect(64 * 6, 0, 64, 64));

	logosSprite.setPosition(g_Resolution.x*0.05f - lScale * 36, g_Resolution.y*0.95f - oneSize+lScale*32);

	if (g_Mouse.IsBetween(g_Resolution.x*0.05f - lScale * 36, g_Resolution.y*0.95f - oneSize + lScale * 32, lScale * 32, lScale * 64, g_Mouse.Coords.x, g_Mouse.Coords.y)
		&& g_Mouse.IsClickValid() && g_Mouse.isHolding())
		logosSprite.setColor(sf::Color(192, 192, 192));
	else 	if (g_Mouse.IsBetween(g_Resolution.x*0.05f - lScale * 36, g_Resolution.y*0.95f - oneSize + lScale * 32, lScale * 32, lScale * 64, g_Mouse.Coords.x, g_Mouse.Coords.y))
		logosSprite.setColor(sf::Color(255, 220, 64));
	else logosSprite.setColor(sf::Color(225, 225, 225));


	g_Window->draw(logosSprite);


	logosSprite.setTextureRect(sf::IntRect(64 * 7, 0, 64, 64));

	logosSprite.setPosition(g_Resolution.x*0.95f - lScale * 24, g_Resolution.y*0.95f - oneSize + lScale * 32);

	if (g_Mouse.IsBetween(g_Resolution.x*0.95f + lScale * 4, g_Resolution.y*0.95f - oneSize + lScale * 32, lScale * 32, lScale * 64, g_Mouse.Coords.x, g_Mouse.Coords.y)
		&& g_Mouse.IsClickValid() && g_Mouse.isHolding())
		logosSprite.setColor(sf::Color(192, 192, 192));
	else 	if (g_Mouse.IsBetween(g_Resolution.x*0.95f + lScale * 4, g_Resolution.y*0.95f - oneSize + lScale * 32, lScale * 32, lScale * 64, g_Mouse.Coords.x, g_Mouse.Coords.y))
		logosSprite.setColor(sf::Color(255, 220, 64));
	else logosSprite.setColor(sf::Color(225, 225, 225));


	g_Window->draw(logosSprite);

}

std::vector<int> dc_game::GetUnlockedIndexes(int type)
{
	std::vector<int> r;
	if (type == 0)
	{
		for (int i = 0; i < Unlockables.size(); i++)
			if (Unlockables[i].Type == 0 && ThePlayer.SkinUnlocked[Unlockables[i].Index])r.push_back(i);
	}
	if (type == 1)
	{
		for (int i = 0; i < Unlockables.size(); i++)
			if (Unlockables[i].Type == 1 && ThePlayer.GliderUnlocked[Unlockables[i].Index])r.push_back(i);
	}
	if (type == 2)
	{
		for (int i = 0; i < Unlockables.size(); i++)
			if (Unlockables[i].Type == 2 && ThePlayer.WrapUnlocked[Unlockables[i].Index])r.push_back(i);
	}
	return r;
}

void dc_game::DoLockerInventory()
{
	float totalSizeA = g_Resolution.x*(0.575f - 0.04f);
	float totalSizeB = g_Resolution.y*(0.78f - 0.02f);
	float oneSize = min(totalSizeA / 5, totalSizeB / 3);

	auto UnlInds = GetUnlockedIndexes(CharacterVisionStatus);


	for (int i = 0; i < 15; i++)
	{
		int High = i / 5;
		int Low = i % 5;

		int X = g_Resolution.x*0.325f + Low * (oneSize + g_Resolution.x*0.01f);
		int Y = g_Resolution.y*0.05f + High * (oneSize + g_Resolution.y*0.01f);


		if (i < UnlInds.size())
		{
			if (g_Mouse.IsBetween(X, Y, oneSize, oneSize, g_Mouse.Coords.x, g_Mouse.Coords.y) &&
				g_Mouse.IsClickValid() &&g_Mouse.hasReleased())
			{
				auto u = Unlockables[UnlInds[i]];
				if (u.Type == 0)ThePlayer.SelectedSkin = u.Index;
				if (u.Type == 1)ThePlayer.SelectedGlider = u.Index;
				if (u.Type == 2)ThePlayer.SelectedWrap = u.Index;

			}


		}


	}
}

void dc_game::DrawLockerInventory()
{
	float totalSizeA = g_Resolution.x*(0.575f-0.04f);
	float totalSizeB = g_Resolution.y*(0.66f-0.02f);
	float oneSize = min(totalSizeA / 5, totalSizeB / 3);

	auto UnlInds = GetUnlockedIndexes(CharacterVisionStatus);
	static sf::Sprite spPl, spGl, spWW;
	spPl.setTexture(*g_Textures.get(3));
	spGl.setTexture(*g_Textures.get(68));
	spWW.setTexture(*g_Textures.get(53));

	for (int i = 0; i < 15; i++)
	{
		int High = i / 5;
		int Low = i % 5;

		int X = g_Resolution.x*0.325f + Low * (oneSize + g_Resolution.x*0.01f);
		int Y = g_Resolution.y*0.05f + High * (oneSize + g_Resolution.y*0.01f);

		sf::RectangleShape rect;
		rect.setPosition(X, Y);
		rect.setSize(sf::Vector2f(oneSize, oneSize));
		rect.setFillColor(sf::Color(192, 192, 192, 64));
		if (i < UnlInds.size())
		{
			auto u = Unlockables[UnlInds[i]];
			if (u.Type == 0 && u.Index == ThePlayer.SelectedSkin)
			{
				rect.setOutlineThickness(1.f);
				rect.setOutlineColor(sf::Color(255, 255, 255));
			}
			if (u.Type == 1 && u.Index == ThePlayer.SelectedGlider)
			{
				rect.setOutlineThickness(1.f);
				rect.setOutlineColor(sf::Color(255, 255, 255));
			}
			if (u.Type == 2 && u.Index == ThePlayer.SelectedWrap)
			{
				rect.setOutlineThickness(1.f);
				rect.setOutlineColor(sf::Color(255, 255, 255));
			}
		}
		g_Window->draw(rect);

		if (i < UnlInds.size())
		{
			auto u = Unlockables[UnlInds[i]];

			if (g_Mouse.IsBetween(X, Y, oneSize, oneSize, g_Mouse.Coords.x, g_Mouse.Coords.y))
				DrawLockerItemShowCase(UnlInds[i]);

			if (u.Type == 0)
			{
				float scale = (oneSize - g_Resolution.x*0.02f) / 64.f;
				spPl.setScale(scale, scale);
				spPl.setPosition(X+ 0.5f*oneSize, Y + 0.5f*oneSize);
				spPl.setOrigin(32, 32);
				spPl.setTextureRect(sf::IntRect((u.Index + 1) * 64, 0, 64, 64));
				g_Window->draw(spPl);
				spPl.setTextureRect(sf::IntRect(0, 0, 64, 64));
				g_Window->draw(spPl);
			}
			if (u.Type == 1)
			{
				float scale = (oneSize - g_Resolution.x*0.02f) / 128.f;
				spGl.setScale(scale, scale);
				spGl.setPosition(X + 0.5f*oneSize, Y + 0.5f*oneSize);
				spGl.setOrigin(64, 64);
				spGl.setTextureRect(sf::IntRect((u.Index) * 128, 0, 128, 128));
				g_Window->draw(spGl);
			}
			if (u.Type == 2)
			{
				static dc_clock Clock;
				static int wID = Random(0, 30);
				if (Clock.deltaTime() > 500)
				{
					wID = Random(0, 30);
					Clock.Update();
				}



				float scale = (oneSize - g_Resolution.x*0.02f) / 96.f;
				spWW.setScale(scale, scale);
				spWW.setPosition(X + 0.5f*oneSize, Y + 0.5f*oneSize);
				spWW.setOrigin(48, 48);
				spWW.setTextureRect(sf::IntRect(wID * 96, u.Index * 96, 64, 64));
				g_Window->draw(spWW);

				spPl.setScale(scale, scale);
				spPl.setPosition(X + 0.5f*oneSize, Y + 0.5f*oneSize);
				spPl.setOrigin(32, 32);
				spPl.setTextureRect(sf::IntRect(ThePlayer.SelectedSkin * 64 + 64, 0, 64, 64));
				g_Window->draw(spPl);
				spPl.setTextureRect(sf::IntRect(0, 0, 64, 64));
				g_Window->draw(spPl);
			}
		}


	}
}


void dc_game::DrawLockerMenu()
{
	DrawMainMenuBg();
	DrawBackButton();
	DrawMainMenuCharacterVision();
	DrawLockerMenuNextUnlockables();
	DrawLockerInventory();
}



void dc_game::DoSettingsMenu()
{
	DoBackButton();
	
	//Buttons
	auto fontsize = g_Resolution.x*0.03f;
	auto lineHeight = _Window::GetHeightForFontsize(fontsize);
	float Length = g_Resolution.x*0.3f - 2;
	for (int i = 0; i < 3; i++)
	{
		if (g_Mouse.IsBetween(0.05f*g_Resolution.x + i*(1 + Length), g_Resolution.y*0.05f, Length, lineHeight + 4, g_Mouse.Coords.x, g_Mouse.Coords.y) &&
			g_Mouse.IsClickValid() && g_Mouse.hasReleased())
			SettingsState = i;
	}

	if (SettingsState == 0)
	{

		if (g_Mouse.IsBetween(g_Resolution.x*0.05f, g_Resolution.y*0.15, g_Resolution.y*0.08f, g_Resolution.y*0.08f, g_Mouse.Coords.x, g_Mouse.Coords.y)
			&& g_Mouse.IsClickValid() && g_Mouse.hasReleased())
		{
			if (g_Config.p_movement_type.Value < 1.f)g_Config.p_movement_type.Value = 1.f;
			else g_Config.p_movement_type.Value = 0.f;
		}

		sf::Vector2f TX(g_Resolution.x*0.05f, g_Resolution.y*0.25f);
		float MaxH = g_Resolution.y*0.7f;
		float MaxW = g_Resolution.x*0.9f;
		float OneH = MaxH / 12;
		float OneW = MaxW / 2;

		float Perc[4] = { 0.f,0.4f,0.7f,1.f };
		std::vector<int> Sorrend = { 1,2,4,3,19,0,5,6,7,8,9,10,11,12,13,17,18,20,21,14,15,16,22 };

		for (int i = 0; i < 23; i++)
		{
			int High = i / 12;
			int Low = i % 12;

			for (int j = 0; j < 3; j++)
			{
				if (g_Mouse.IsBetween(TX.x + (Perc[j] + High)*OneW, TX.y + Low*OneH, OneW*(Perc[j + 1] - Perc[j]) - 1, OneH - 1, g_Mouse.Coords.x, g_Mouse.Coords.y)
					&& g_Mouse.IsClickValid() && g_Mouse.hasReleased())
				{
					if (j == 0)
					{
						Binds.KeysPrimary[Sorrend[i]] = 0;
						Binds.KeysSecondary[Sorrend[i]] = 0;
					}
					else if (j == 1)
					{
						OW_STATUS = 6;
						SettingKeySelected = Sorrend[i];
						SettingPrimerity = 0;
						PressKeyWaitFrames = 2;
					}
					else if (j == 2)
					{
						OW_STATUS = 6;
						SettingKeySelected = Sorrend[i];
						SettingPrimerity = 1;
						PressKeyWaitFrames = 2;
					}
				}

			}
		}
	}

	if (SettingsState == 1)
	{
		//Master volume slider
		auto width = _Window::GetTextSize("Brightness", fontsize).x;


		float barlength = g_Resolution.x*0.95f - (g_Resolution.x*0.05f + width + g_Resolution.x*0.01f);

		float sliderlength = g_Resolution.x*0.02f;
		float cum_barlength = barlength - sliderlength;

		float sliderPos = (g_Resolution.x*0.05f + width + g_Resolution.x*0.01f) + g_Config.mastervolume.Value*cum_barlength;
		float sliderStart = (g_Resolution.x*0.05f + width + g_Resolution.x*0.01f);
		static bool MV_Drag = false;

		if (g_Mouse.IsBetween(g_Resolution.x*0.05f + width + g_Resolution.x*0.01f, g_Resolution.y*0.15f, barlength, lineHeight + 4, g_Mouse.Coords.x, g_Mouse.Coords.y)
			&& g_Mouse.hasJustClicked())MV_Drag = true;
		if (!g_Mouse.left_click)MV_Drag = false;

		if (MV_Drag)
		{
			float perc = ((float)g_Mouse.Coords.x - sliderStart) / cum_barlength;
			if (perc < 0)perc = 0;
			if (perc > 1)perc = 1;
			g_Config.g_brightness.Value = 0.5f+0.5f*perc;
		}

		sf::Vector2i Resolutions[] = { sf::Vector2i(640,480),sf::Vector2i(800,600),sf::Vector2i(1024,768),sf::Vector2i(1280,960),sf::Vector2i(1440,1080), sf::Vector2i(640,360),sf::Vector2i(1024,576),sf::Vector2i(1280,720),sf::Vector2i(1600,900),sf::Vector2i(1920,1080), sf::Vector2i(640,400),sf::Vector2i(1280,800),sf::Vector2i(1680,1050),sf::Vector2i(1680,720) };

		width = _Window::GetTextSize("Resolution", fontsize).x;
		
		auto AvailableWidth = g_Resolution.x*0.95f - (g_Resolution.x*0.05f + width + g_Resolution.x*0.01f);
		auto AvailableHeight = g_Resolution.y*0.7f - (g_Resolution.y*0.16f + lineHeight + 4);

		auto OneWidth = AvailableWidth / 2 - 1;
		auto OneHeight = AvailableHeight / 7 - 6;

		sf::Vector2f T = sf::Vector2f(g_Resolution.x*0.05f + width + g_Resolution.x*0.01f, (g_Resolution.y*0.16f + lineHeight + 4));
		
		for (int i = 0; i < 14; i++)
		{
			int High = i / 7;
			int Low = i % 7;

			auto pX = T.x + High*(OneWidth + 1);
			auto pY = T.y + Low*(OneHeight + 1);

			if (g_Mouse.IsBetween(pX, pY, OneWidth, OneHeight, g_Mouse.Coords.x, g_Mouse.Coords.y)
				&& g_Mouse.IsClickValid() && g_Mouse.isHolding())
			{
				SelectedVideoSetting = i;
			}


		}
		if (g_Mouse.IsBetween(g_Resolution.x*0.75f, g_Resolution.y*0.85f, g_Resolution.x*0.2f, g_Resolution.y*0.1f, g_Mouse.Coords.x, g_Mouse.Coords.y)
			&& g_Mouse.IsClickValid() && g_Mouse.hasReleased())
		{
			if (g_Resolution != Resolutions[SelectedVideoSetting] || g_Config.g_fullscreen.Value != SettingFullscreen)
			{
				g_Resolution = Resolutions[SelectedVideoSetting];
				g_Window->close();
				
				g_Config.g_res_x.Value = g_Resolution.x;
				g_Config.g_res_y.Value = g_Resolution.y;
				g_Config.g_fullscreen.Value = SettingFullscreen;

				_Window::CreateTheWindow();
			}
		}

		if (g_Mouse.IsBetween(T.x, g_Resolution.y*0.71, g_Resolution.y*0.08f, g_Resolution.y*0.08f, g_Mouse.Coords.x, g_Mouse.Coords.y)
			&& g_Mouse.IsClickValid() && g_Mouse.hasReleased())
			SettingFullscreen = !SettingFullscreen;
	}


	if (SettingsState == 2)
	{
		//Master volume slider
		auto width = _Window::GetTextSize("Master volume", fontsize).x;


		float barlength = g_Resolution.x*0.95f - (g_Resolution.x*0.05f + width + g_Resolution.x*0.01f);

		float sliderlength = g_Resolution.x*0.02f;
		float cum_barlength = barlength - sliderlength;

		float sliderPos = (g_Resolution.x*0.05f + width + g_Resolution.x*0.01f) + g_Config.mastervolume.Value*cum_barlength;
		float sliderStart = (g_Resolution.x*0.05f + width + g_Resolution.x*0.01f);
		static bool MV_Drag = false;

		if (g_Mouse.IsBetween(g_Resolution.x*0.05f + width + g_Resolution.x*0.01f, g_Resolution.y*0.15f, barlength, lineHeight + 4, g_Mouse.Coords.x, g_Mouse.Coords.y)
			&& g_Mouse.hasJustClicked())MV_Drag = true;
		if (!g_Mouse.left_click)MV_Drag = false;

		if (MV_Drag)
		{
			float perc = ((float)g_Mouse.Coords.x - sliderStart) / cum_barlength;
			if (perc < 0)perc = 0;
			if (perc > 1)perc = 1;
			g_Config.mastervolume.Value = perc;
		}
	}
}

void dc_game::DrawSettingsMenu()
{
	DrawMainMenuBg();
	DrawBackButton();

	auto fontsize = g_Resolution.x*0.03f;
	auto lineHeight = _Window::GetHeightForFontsize(fontsize);

	char* SettNames[] = { "Controls","Video","Audio" };

	float Length = g_Resolution.x*0.3f - 2;







	//Buttons
	for(int i = 0; i < 3;i++)
	{
		if (g_Mouse.IsBetween(0.05f*g_Resolution.x + i*(1 + Length), g_Resolution.y*0.05f, Length, lineHeight + 4, g_Mouse.Coords.x, g_Mouse.Coords.y) &&
			g_Mouse.IsClickValid() && g_Mouse.isHolding())
		{
			_Window::RenderOverlay(0.05f*g_Resolution.x+i*(1+Length), g_Resolution.y*0.05f , Length, lineHeight + 4, 180, 150, 16, 255);
		}
		else if (i == SettingsState)
		{
			_Window::RenderOverlay(0.05f*g_Resolution.x + i*(1 + Length), g_Resolution.y*0.05f, Length, lineHeight + 4, 180, 150, 16, 255);
		}
		else if (g_Mouse.IsBetween(0.05f*g_Resolution.x + i*(1 + Length), g_Resolution.y*0.05f, Length, lineHeight + 4, g_Mouse.Coords.x, g_Mouse.Coords.y))
		{
			_Window::RenderOverlay(0.05f*g_Resolution.x + i*(1 + Length), g_Resolution.y*0.05f, Length, lineHeight + 4, 255, 255, 64, 255);

		}
		else
			_Window::RenderOverlay(0.05f*g_Resolution.x + i*(1 + Length), g_Resolution.y*0.05f, Length, lineHeight + 4, 240, 215, 32, 255);

		_Window::RenderTextBMiddleC(0.05f*g_Resolution.x + i*(1 + Length), g_Resolution.y*0.05f, Length, lineHeight + 4, SettNames[i], fontsize, 0, 0, 0);
	}

	if (SettingsState == 0)
	{
		_Window::RenderOverlay(g_Resolution.x*0.05f, g_Resolution.y*0.15, g_Resolution.y*0.08f, g_Resolution.y*0.08f, 128, 128, 128, 128);

		if (g_Config.p_movement_type.Value >= 1)
			_Window::RenderOverlay(g_Resolution.x*0.05f + 2, g_Resolution.y*0.15 + 2, g_Resolution.y*0.08f - 4, g_Resolution.y*0.08f - 4, 64, 64, 192, 255);

		auto width = _Window::GetTextSize("Directional movement", fontsize).x;
		_Window::RenderOverlay(g_Resolution.x*0.05f + g_Resolution.y*0.09f + 2, g_Resolution.y*0.15, width + 12, g_Resolution.y*0.08f, 192, 192, 192, 64);
		_Window::RenderTextBMiddleC(g_Resolution.x*0.05f + g_Resolution.y*0.09f + 2, g_Resolution.y*0.15, width + 12, g_Resolution.y*0.08f, "Directional movement", fontsize, 255, 255, 255, 255);

		auto KeyNames = GetAllKeyNames();

		std::vector<char*> ActNames = { "Shoot","Move forward","Move backward","Move right","Move left","Reload weapon","Slot 1","Slot 2","Slot 3","Slot 4","Slot 5","Drop item","Open Inventory","Open Map","Place Marker","Remove Marker","Open Console","Jump Off","Descend","Alternative","Close Menu","Swap Player","Console enter" };
		std::vector<int> Sorrend = { 1,2,4,3,19,0,5,6,7,8,9,10,11,12,13,17,18,20,21,14,15,16,22 };
		
		sf::Vector2f TX(g_Resolution.x*0.05f, g_Resolution.y*0.25f);
		float MaxH = g_Resolution.y*0.7f;
		float MaxW = g_Resolution.x*0.9f;
		float OneH = MaxH / 12;
		float OneW = MaxW / 2;

		float Perc[4] = { 0.f,0.4f,0.7f,1.f };


		for (int i = 0; i < 23; i++)
		{
			int High = i / 12;
			int Low = i % 12;

			for (int j = 0; j < 3; j++)
			{
				std::vector<char*> Texts;
				Texts.push_back(ActNames[Sorrend[i]]);
				if (Binds.KeysPrimary[Sorrend[i]])Texts.push_back(KeyNames[Binds.KeysPrimary[Sorrend[i]]]);
				else Texts.push_back("");
				if (Binds.KeysSecondary[Sorrend[i]])Texts.push_back(KeyNames[Binds.KeysSecondary[Sorrend[i]]]);
				else Texts.push_back("");

				sf::RectangleShape R;
				R.setPosition(TX.x + (Perc[j] + High)*OneW, TX.y + Low*OneH);
				R.setSize(sf::Vector2f(OneW*(Perc[j + 1] - Perc[j]) - 1, OneH-1));
				
				if (g_Mouse.IsBetween(R.getPosition().x, R.getPosition().y, R.getSize().x, R.getSize().y, g_Mouse.Coords.x, g_Mouse.Coords.y)
					&& g_Mouse.IsClickValid() && g_Mouse.isHolding())
					R.setFillColor(sf::Color(160, 120, 16));
				else if (g_Mouse.IsBetween(R.getPosition().x, R.getPosition().y, R.getSize().x, R.getSize().y, g_Mouse.Coords.x, g_Mouse.Coords.y))
					R.setFillColor(sf::Color(255, 222, 64));
				else R.setFillColor(sf::Color(225, 180, 32));

				g_Window->draw(R);
				_Window::RenderTextBMiddleC(R.getPosition().x, R.getPosition().y, R.getSize().x, R.getSize().y, Texts[j], g_Resolution.y*0.025f, 0, 0, 0);
				
			}
		}


	}
	if (SettingsState == 1)
	{
		auto width = _Window::GetTextSize("Brightness", fontsize).x;
		_Window::RenderOverlay(g_Resolution.x*0.05f, g_Resolution.y*0.15f, width + 6, lineHeight + 4, 192, 192, 192, 64);
		_Window::RenderTextBMiddleC(g_Resolution.x*0.05f, g_Resolution.y*0.15f, width + 6, lineHeight + 4, "Brightness", fontsize, 255, 255, 255, 255);

		float barlength = g_Resolution.x*0.95f - (g_Resolution.x*0.05f + width + g_Resolution.x*0.01f);
		_Window::RenderOverlay(g_Resolution.x*0.05f + width + g_Resolution.x*0.01f, g_Resolution.y*0.15f, barlength, lineHeight + 4, 64, 64, 64, 128);
		float sliderlength = g_Resolution.x*0.02f;
		float cum_barlength = barlength - sliderlength;

		float sliderPos = (g_Resolution.x*0.05f + width + 0.5f*sliderlength) + ((2.f*g_Config.g_brightness.Value-1.f)*cum_barlength);

		_Window::RenderOverlay(sliderPos, g_Resolution.y*0.145f, sliderlength, lineHeight + 4 + g_Resolution.y*0.01f, 255, 255, 255, 255);

		sf::Vector2i Resolutions[] = { sf::Vector2i(640,480),sf::Vector2i(800,600),sf::Vector2i(1024,768),sf::Vector2i(1280,960),sf::Vector2i(1440,1080), sf::Vector2i(640,360),sf::Vector2i(1024,576),sf::Vector2i(1280,720),sf::Vector2i(1600,900),sf::Vector2i(1920,1080), sf::Vector2i(640,400),sf::Vector2i(1280,800),sf::Vector2i(1680,1050),sf::Vector2i(1680,720) };





		width = _Window::GetTextSize("Resolution", fontsize).x;
		_Window::RenderOverlay(g_Resolution.x*0.056, g_Resolution.y*0.16f+lineHeight+4, width + 6, lineHeight + 4, 192, 192, 192, 64);
		_Window::RenderTextBMiddleC(g_Resolution.x*0.05f, g_Resolution.y*0.16f+lineHeight+4, width + 6, lineHeight + 4, "Resolution", fontsize, 255, 255, 255, 255);

		auto AvailableWidth = g_Resolution.x*0.95f - (g_Resolution.x*0.05f + width + g_Resolution.x*0.01f);
		auto AvailableHeight = g_Resolution.y*0.7f - (g_Resolution.y*0.16f + lineHeight + 4);

		auto OneWidth = AvailableWidth/2 - 1;
		auto OneHeight = AvailableHeight/7 - 6;

		sf::Vector2f T = sf::Vector2f(g_Resolution.x*0.05f + width + g_Resolution.x*0.01f, (g_Resolution.y*0.16f + lineHeight + 4));
		_Window::RenderOverlay(T.x, T.y, AvailableWidth, AvailableHeight, 64, 0, 0, 64);

		for (int i = 0; i < 14; i++)
		{
			int High = i / 7;
			int Low = i % 7;

			auto pX = T.x + High*(OneWidth + 1);
			auto pY = T.y + Low*(OneHeight + 1);

			sf::RectangleShape rShape;
			rShape.setPosition(pX, pY);
			rShape.setSize(sf::Vector2f(OneWidth, OneHeight));
			if (g_Mouse.IsBetween(pX, pY, OneWidth, OneHeight, g_Mouse.Coords.x, g_Mouse.Coords.y)
				&& g_Mouse.IsClickValid() && g_Mouse.isHolding())
			{
				if (i % 2 == 0)
					rShape.setFillColor(sf::Color(44, 44, 66, 255));
				else rShape.setFillColor(sf::Color(55, 55, 82, 255));
			}
			else if (i == SelectedVideoSetting)
			{
				rShape.setFillColor(sf::Color(55, 155, 82, 255));
			}
			else if (g_Mouse.IsBetween(pX, pY, OneWidth, OneHeight, g_Mouse.Coords.x, g_Mouse.Coords.y))
			{
				if (i % 2 == 0)
					rShape.setFillColor(sf::Color(96, 96, 144, 255));
				else rShape.setFillColor(sf::Color(112, 112, 168, 255));
			}
			else
			{
				if (i % 2 == 0)
					rShape.setFillColor(sf::Color(64, 64, 96, 255));
				else rShape.setFillColor(sf::Color(80, 80, 120, 255));
			}
			g_Window->draw(rShape);

			char Buffer[32]; sprintf(Buffer, "%dx%d", Resolutions[i].x, Resolutions[i].y);
			_Window::RenderTextBMiddleC(pX, pY, OneWidth, OneHeight, Buffer, g_Resolution.y*0.03f);
		}
		if(g_Mouse.IsBetween(g_Resolution.x*0.75f, g_Resolution.y*0.85f, g_Resolution.x*0.2f, g_Resolution.y*0.1f,g_Mouse.Coords.x,g_Mouse.Coords.y)
			&& g_Mouse.IsClickValid() && g_Mouse.isHolding())
			_Window::RenderOverlay(g_Resolution.x*0.75f, g_Resolution.y*0.85f, g_Resolution.x*0.2f, g_Resolution.y*0.1f, 160, 110, 16, 255);
		else if (g_Mouse.IsBetween(g_Resolution.x*0.75f, g_Resolution.y*0.85f, g_Resolution.x*0.2f, g_Resolution.y*0.1f, g_Mouse.Coords.x, g_Mouse.Coords.y))
			_Window::RenderOverlay(g_Resolution.x*0.75f, g_Resolution.y*0.85f, g_Resolution.x*0.2f, g_Resolution.y*0.1f, 255, 222, 64, 255);
		else _Window::RenderOverlay(g_Resolution.x*0.75f, g_Resolution.y*0.85f, g_Resolution.x*0.2f, g_Resolution.y*0.1f, 225, 180, 32, 255);
		_Window::RenderTextBMiddleC(g_Resolution.x*0.75f, g_Resolution.y*0.85f, g_Resolution.x*0.2f, g_Resolution.y*0.1f,"APPLY",g_Resolution.y*0.05f, 0,0,0, 255);
		


		_Window::RenderOverlay(T.x, g_Resolution.y*0.71, g_Resolution.y*0.08f, g_Resolution.y*0.08f, 128,128,128, 128);

		if (SettingFullscreen == 1)
			_Window::RenderOverlay(T.x+2, g_Resolution.y*0.71+2, g_Resolution.y*0.08f-4, g_Resolution.y*0.08f-4, 64, 64, 192, 255);
		
		width = _Window::GetTextSize("Full screen", fontsize).x;
		_Window::RenderOverlay(T.x+g_Resolution.y*0.09f+2, g_Resolution.y*0.71, width + 12, g_Resolution.y*0.08f, 192, 192, 192, 64);
		_Window::RenderTextBMiddleC(T.x + g_Resolution.y*0.09f+2, g_Resolution.y*0.71, width + 12,g_Resolution.y*0.08f, "Full screen", fontsize, 255, 255, 255, 255);


	}

	if (SettingsState == 2)
	{

		auto width = _Window::GetTextSize("Master volume", fontsize).x;
		_Window::RenderOverlay(g_Resolution.x*0.05f, g_Resolution.y*0.15f, width + 6, lineHeight + 4, 192, 192, 192, 64);
		_Window::RenderTextBMiddleC(g_Resolution.x*0.05f, g_Resolution.y*0.15f, width + 6, lineHeight + 4,"Master volume",fontsize, 255,255,255,255);

		float barlength = g_Resolution.x*0.95f - (g_Resolution.x*0.05f + width + g_Resolution.x*0.01f);
		_Window::RenderOverlay(g_Resolution.x*0.05f + width + g_Resolution.x*0.01f, g_Resolution.y*0.15f, barlength, lineHeight + 4, 64, 64, 64, 128);
		float sliderlength = g_Resolution.x*0.02f;
		float cum_barlength = barlength - sliderlength;

		float sliderPos = (g_Resolution.x*0.05f + width + 0.5f*sliderlength) + g_Config.mastervolume.Value*cum_barlength;

		_Window::RenderOverlay(sliderPos, g_Resolution.y*0.145f, sliderlength, lineHeight + 4 + g_Resolution.y*0.01f, 255,255,255,255);
	}


}

void dc_game::DrawPressKeyOL()
{
	_Window::RenderOverlay(0, 0, g_Resolution.x, g_Resolution.y, 0, 0, 0, 96);

	_Window::RenderOverlay(g_Resolution.x*0.35f, g_Resolution.y*0.3f, g_Resolution.x*0.3f, g_Resolution.y*0.4f, 32, 96, 192, 255);
	_Window::RenderOverlay(g_Resolution.x*0.35f + 2, g_Resolution.y*0.3f + 2, g_Resolution.x*0.3f - 4, g_Resolution.y*0.4f - 4, 16, 48, 96, 255);

	_Window::RenderTextBMiddleC(g_Resolution.x*0.35f, g_Resolution.y*0.3f, g_Resolution.x*0.3f, g_Resolution.y*0.4f, "Press a key", g_Resolution.y*0.02f);

}

void dc_game::DoPressKeyOL()
{



	if (PressKeyWaitFrames > 0)
	{
		PressKeyWaitFrames--;
		return;
	}

	if (!g_Mouse.IsBetween(g_Resolution.x*0.35f, g_Resolution.y*0.3f, g_Resolution.x*0.3f, g_Resolution.y*0.4f, g_Mouse.Coords.x, g_Mouse.Coords.y)
		&& g_Mouse.IsClickValid() && g_Mouse.hasReleased())
	{
		SettingPrimerity = -1;
		SettingKeySelected = -1;
		if (OW_STATUS == 6)
			OW_STATUS = 0;
		else if (OW_STATUS == 7)
			OW_STATUS = 3;
		
	}

	if (SettingPrimerity == -1 || SettingKeySelected == -1)
	{
		if (OW_STATUS == 6)
			OW_STATUS = 0;
		else if (OW_STATUS == 7)
			OW_STATUS = 3;
		return;
	}

	for(int i = 0; i < 255; i++)
		if (g_Keyboard.hasReleased(i))
		{
			if (SettingPrimerity == 0)Binds.KeysPrimary[SettingKeySelected] = i;
			else if (SettingPrimerity == 1)Binds.KeysSecondary[SettingKeySelected] = i;

			SettingPrimerity = -1;
			SettingKeySelected = -1;
			if (OW_STATUS == 6)
				OW_STATUS = 0;
			else if (OW_STATUS == 7)
				OW_STATUS = 3;
		}
}

void dc_game::DoCreditsMenu()
{
	DoBackButton();
}

float texW(char* t,float s)
{
	return _Window::GetTextSize(t, s).x;
}

float texH(int l, float s)
{
	return l * _Window::GetHeightForFontsize(s);
}

void dc_game::DrawCreditsMenu()
{
	DrawMainMenuBg();
	DrawBackButton();

	float tX = g_Resolution.x*0.06f;
	float tY = g_Resolution.y*0.05f;
	float fontSize = g_Resolution.y*0.1f;
	char Buffer[128]; sprintf(Buffer,"DaiCastle");
	_Window::RenderTextB(tX, tY, Buffer, fontSize,225,225,225);
	tY += texH(1, fontSize);

	sprintf(Buffer, "Graphics: ");
	fontSize = g_Resolution.y*0.05f;
	_Window::RenderTextB(tX, tY, Buffer, fontSize,192,192,192);
	tX += texW("Graphics: ", fontSize);

	sprintf(Buffer, "zENKII @ GlitchHub");
	_Window::RenderTextB(tX, tY, Buffer, fontSize,225,180,32);
	tX = g_Resolution.x*0.06f;
	tY += texH(1, fontSize);

	sprintf(Buffer, "Sounds: ");
	_Window::RenderTextB(tX, tY, Buffer, fontSize, 192, 192, 192);
	tX += texW("Sounds: ", fontSize);
	
	auto tNpush = tX+max(texW("Gun Sounds: ", fontSize), max(texW("Bus Music: ", fontSize), texW("Footsteps: ", fontSize)));
	sprintf(Buffer, "zENKII @ GlitchHub\nMarkvard\nYouTube @ Creative Commons");
	_Window::RenderTextB(tNpush, tY, Buffer, fontSize, 225, 180, 32);
	sprintf(Buffer, "Gun Sounds: ");
	_Window::RenderTextB(tNpush- texW("Gun Sounds: ", fontSize), tY, Buffer, fontSize, 192,192,192);
	sprintf(Buffer, "Bus Music: ");
	_Window::RenderTextB(tNpush - texW("Bus Music: ", fontSize), tY+texH(1, fontSize), Buffer, fontSize, 192,192,192);
	sprintf(Buffer, "Footsteps: ");
	_Window::RenderTextB(tNpush - texW("Footsteps: ", fontSize), tY + texH(2, fontSize), Buffer, fontSize, 192, 192, 192);

	tX = g_Resolution.x*0.06f;
	tY += texH(3, fontSize);

	sprintf(Buffer, "Programming: ");
	_Window::RenderTextB(tX, tY, Buffer, fontSize, 192, 192, 192);
	tX += texW("Programming: ", fontSize);

	sprintf(Buffer, "zENKII @ GlitchHub");
	_Window::RenderTextB(tX, tY, Buffer, fontSize, 225, 180, 32);
	tX = g_Resolution.x*0.06f;
	tY += texH(1, fontSize);

}

std::vector<std::string> dc_game::GetAllDemoNames(bool Update)
{
	static std::vector<std::string> names;
	static bool bRun = false;

	if (!bRun || Update)
	{
		names.clear();





		std::string search_path = appLocation;
		search_path += "demos\\*.dem";

		WIN32_FIND_DATA fd;
		HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
		if (hFind != INVALID_HANDLE_VALUE) {
			do {
				// read all (real) files in current folder
				// , delete '!' read other 2 default folder . and ..
				if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
					names.push_back(fd.cFileName);
				}
			} while (::FindNextFile(hFind, &fd));
			::FindClose(hFind);
		}

		bRun = true;
	}
	return names;
}


void dc_game::DoDemoMenu()
{

	DoBackButton();

	auto demoNames = GetAllDemoNames();

	int RenderTotal = 20;
	float textSize = g_Resolution.y*0.0225f;
	float LineHeight = _Window::GetHeightForFontsize(textSize);
	float LineLength = _Window::GetTextSize("MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM", textSize).x;

	//Selecting
	for (int i = DemoCoordinate; i < demoNames.size() && i < DemoCoordinate + RenderTotal; i++)
	{
	
		if (g_Mouse.IsBetween(g_Resolution.x*0.075f + 2, g_Resolution.y*0.075f + (i - DemoCoordinate)*LineHeight, LineLength, LineHeight, g_Mouse.Coords.x, g_Mouse.Coords.y)
			&& g_Mouse.IsClickValid() && g_Mouse.hasReleased())
			DemoSelected = i;

	}
	//Scrolling
	if (g_Mouse.IsBetween(g_Resolution.x*0.075f, g_Resolution.y*0.075f, LineLength + 4, RenderTotal * LineHeight, g_Mouse.Coords.x, g_Mouse.Coords.y))
	{
		auto scroll = g_Mouse.scroll;
		DemoCoordinate -= scroll;
		
		if (DemoCoordinate > ((int)demoNames.size()) - RenderTotal)DemoCoordinate = ((int)demoNames.size()) - RenderTotal;
		if (DemoCoordinate < 0)DemoCoordinate = 0;
	}

	//Refresh
	if (g_Mouse.IsBetween(g_Resolution.x*0.085f + LineLength, g_Resolution.y*0.075f, g_Resolution.x*0.925f - (g_Resolution.x*0.085f + LineLength), g_Resolution.y*0.1f, g_Mouse.Coords.x, g_Mouse.Coords.y)
		&& g_Mouse.IsClickValid() && g_Mouse.hasReleased())
		GetAllDemoNames(true);

	//Play
	if (DemoSelected >= 0 && DemoSelected < demoNames.size() && g_Mouse.IsBetween(g_Resolution.x*0.085f + LineLength, g_Resolution.y*0.2f, g_Resolution.x*0.925f - (g_Resolution.x*0.085f + LineLength), g_Resolution.y*0.1f, g_Mouse.Coords.x, g_Mouse.Coords.y)
		&& g_Mouse.IsClickValid() && g_Mouse.hasReleased())
	{


		GM_STATE = 7;


		for (int i = 0; i < demoNames.size(); i++)
		{
			if (i == DemoSelected)printf("\n   %s", demoNames[i].c_str());
			else printf("\n%s", demoNames[i].c_str());
		}

		printf("\n\nFile: %s", demoNames[DemoSelected].c_str());

		char buffer[256]; sprintf(buffer, "%sdemos\\", appLocation);
		sprintf(buffer, "%s%s", buffer, (demoNames[DemoSelected].c_str()));
		ConLog("\nBuffer: %s", buffer);
		StartNewDemoViewer(buffer);
	}

	if (g_Mouse.IsBetween(g_Resolution.x*0.075f, g_Resolution.y*0.085f + RenderTotal * LineHeight, g_Resolution.y*0.08f, g_Resolution.y*0.08f, g_Mouse.Coords.x, g_Mouse.Coords.y) && g_Mouse.IsClickValid() &&g_Mouse.hasReleased())
	{
		if (g_Config.m_record_replay.Value >= 1.f)g_Config.m_record_replay.Value = 0.f;
		else g_Config.m_record_replay.Value = 1.f;
	}

}


void dc_game::DrawDemoMenu()
{
	DrawMainMenuBg();
	DrawBackButton();

	_Window::RenderOverlay(g_Resolution.x*0.05f, g_Resolution.y*0.05f, g_Resolution.x*0.9f, g_Resolution.y*0.9f, 192, 192, 192, 64);

	auto demoNames = GetAllDemoNames();

	int RenderTotal = 20;
	float textSize = g_Resolution.y*0.0225f;
	float LineHeight = _Window::GetHeightForFontsize(textSize);
	float LineLength = _Window::GetTextSize("MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM", textSize).x;

	_Window::RenderOverlay(g_Resolution.x*0.075f, g_Resolution.y*0.075f, LineLength + 4, RenderTotal * LineHeight, 0, 0, 0, 192);

	for (int i = DemoCoordinate; i < demoNames.size() && i < DemoCoordinate + RenderTotal; i++)
	{
		if (i == DemoSelected)
			_Window::RenderOverlay(g_Resolution.x*0.075f+2, g_Resolution.y*0.075f + (i-DemoCoordinate)*LineHeight, LineLength, LineHeight, 32, 128,192, 255);

		_Window::RenderTextB(g_Resolution.x*0.075f + 2, g_Resolution.y*0.075f + (i - DemoCoordinate)*LineHeight, (char*)demoNames[i].c_str(), textSize);
	}

	if (g_Mouse.IsBetween(g_Resolution.x*0.085f + LineLength, g_Resolution.y*0.075f, g_Resolution.x*0.925f - (g_Resolution.x*0.085f + LineLength), g_Resolution.y*0.1f, g_Mouse.Coords.x, g_Mouse.Coords.y)
		&& g_Mouse.IsClickValid() && g_Mouse.isHolding())
		_Window::RenderOverlay(g_Resolution.x*0.085f + LineLength, g_Resolution.y*0.075f, g_Resolution.x*0.925f - (g_Resolution.x*0.085f + LineLength), g_Resolution.y*0.1f, 160, 120, 24, 255);
	else if (g_Mouse.IsBetween(g_Resolution.x*0.085f + LineLength, g_Resolution.y*0.075f, g_Resolution.x*0.925f - (g_Resolution.x*0.085f + LineLength), g_Resolution.y*0.1f, g_Mouse.Coords.x, g_Mouse.Coords.y))
		_Window::RenderOverlay(g_Resolution.x*0.085f + LineLength, g_Resolution.y*0.075f, g_Resolution.x*0.925f - (g_Resolution.x*0.085f + LineLength), g_Resolution.y*0.1f, 255, 222, 64, 255);
	else 
		_Window::RenderOverlay(g_Resolution.x*0.085f + LineLength, g_Resolution.y*0.075f, g_Resolution.x*0.925f - (g_Resolution.x*0.085f + LineLength), g_Resolution.y*0.1f, 225,180,32, 255);

	_Window::RenderTextBMiddleC(g_Resolution.x*0.085f + LineLength, g_Resolution.y*0.075f, g_Resolution.x*0.925f - (g_Resolution.x*0.085f + LineLength), g_Resolution.y*0.1f, "REFRESH", g_Resolution.y*0.03f, 0, 0, 0);

	if (g_Mouse.IsBetween(g_Resolution.x*0.085f + LineLength, g_Resolution.y*0.2f, g_Resolution.x*0.925f - (g_Resolution.x*0.085f + LineLength), g_Resolution.y*0.1f, g_Mouse.Coords.x, g_Mouse.Coords.y)
		&& g_Mouse.IsClickValid() && g_Mouse.isHolding())
		_Window::RenderOverlay(g_Resolution.x*0.085f + LineLength, g_Resolution.y*0.2f, g_Resolution.x*0.925f - (g_Resolution.x*0.085f + LineLength), g_Resolution.y*0.1f, 160, 120, 24, 255);
	else if (g_Mouse.IsBetween(g_Resolution.x*0.085f + LineLength, g_Resolution.y*0.2f, g_Resolution.x*0.925f - (g_Resolution.x*0.085f + LineLength), g_Resolution.y*0.1f, g_Mouse.Coords.x, g_Mouse.Coords.y))
		_Window::RenderOverlay(g_Resolution.x*0.085f + LineLength, g_Resolution.y*0.2f, g_Resolution.x*0.925f - (g_Resolution.x*0.085f + LineLength), g_Resolution.y*0.1f, 255, 222, 64, 255);
	else
		_Window::RenderOverlay(g_Resolution.x*0.085f + LineLength, g_Resolution.y*0.2f, g_Resolution.x*0.925f - (g_Resolution.x*0.085f + LineLength), g_Resolution.y*0.1f, 225, 180, 32, 255);

	_Window::RenderTextBMiddleC(g_Resolution.x*0.085f + LineLength, g_Resolution.y*0.2f, g_Resolution.x*0.925f - (g_Resolution.x*0.085f + LineLength), g_Resolution.y*0.1f, "PLAY", g_Resolution.y*0.03f, 0, 0, 0);


	float fontsize = g_Resolution.y*0.03f;

	_Window::RenderOverlay(g_Resolution.x*0.075f, g_Resolution.y*0.085f+ RenderTotal * LineHeight, g_Resolution.y*0.08f, g_Resolution.y*0.08f, 128, 128, 128, 128);

	if (g_Config.m_record_replay.Value >= 1)
		_Window::RenderOverlay(g_Resolution.x*0.075f + 2, g_Resolution.y*0.085f + RenderTotal * LineHeight + 2, g_Resolution.y*0.08f - 4, g_Resolution.y*0.08f - 4, 64, 64, 192, 255);

	auto width = _Window::GetTextSize("Record Demos", fontsize).x;
	_Window::RenderOverlay(g_Resolution.x*0.075f + g_Resolution.y*0.09f + 2, g_Resolution.y*0.095f + RenderTotal * LineHeight, width + 12, g_Resolution.y*0.06f, 192, 192, 192, 64);
	_Window::RenderTextBMiddleC(g_Resolution.x*0.075f + g_Resolution.y*0.09f + 2, g_Resolution.y*0.095f + RenderTotal * LineHeight, width + 12, g_Resolution.y*0.06f, "Record Demos", fontsize, 255, 255, 255, 255);


}
