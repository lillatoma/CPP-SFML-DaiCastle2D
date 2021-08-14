#include "DaiCastle.h"



void dc_quest::Init()
{
	bool bEasy = Random(1, 100) <= 80;
	location1 = -1; location2 = -1; location3 = -1;
	if (bEasy)
	{
		tierReward = 5;
		int r = Random(1, 10000);
		if (r <= 3500)
		{
			type = (Random(1, 100) <= 35);
			if (type == 1)
			{
				location1 = Random(0, g_Map.labels.size() - 1);
			}

			int r2 = Random(1, 10000);
			if (r2 <= 5000)
			{
				killweapontype = 0;
				needed = 7;
			}
			else if (r2 <= 5600)
			{
				killweapontype = 1;
				needed = 3;
			}
			else if (r2 <= 6500)
			{
				killweapontype = 2;
				needed = 5;
			}
			else if (r2 <= 7300)
			{
				killweapontype = 3;
				needed = 3;
			}
			else if (r2 <= 8300)
			{
				killweapontype = 4;
				needed = 5;
			}
			else if (r2 <= 8800)
			{
				killweapontype = 5;
				needed = 1;
			}
			else if (r2 <= 9300)
			{
				killweapontype = 6;
				needed = 1;
			}
			else
			{
				killweapontype = 7;
				needed = 3;
			}
		}
		else if (r <= 6000)
		{
			type = 2 + (Random(1, 100) <= 35);
			if (type == 3)
			{
				location1 = Random(0, g_Map.labels.size() - 1);
				needed = 7;
			}
			else needed = 10;
		}
		else if (r <= 7250)
		{
			type = 4;
			location1 = Random(0, g_Map.labels.size() - 1);
			needed = 1;
		}
		else if (r <= 8000)
		{
			type = 5;
			location1 = Random(0, g_Map.labels.size() - 1);
			do { location2 = Random(0, g_Map.labels.size() - 1); } while (location2 == location1);
			do { location3 = Random(0, g_Map.labels.size() - 1); } while (location3 == location1 || location3 == location2);
			needed = 1;
		}
		else if (r <= 9000)
		{
			type = 6;
			needed = 1;
		}
		else
		{
			type = 7;
			needed = 3;
		}
	}
	else
	{
		tierReward = 10;
		int r = Random(1, 10000);
		if (r <= 6000)
		{
			type = (Random(1, 100) <= 35);
			if (type == 1)
			{
				location1 = Random(0, g_Map.labels.size() - 1);
			}
			else oneMatch = Random(1, 10000) < 2500;

			int r2 = Random(1, 10000);
			if (r2 <= 5000)
			{
				killweapontype = 0;
				needed = 14;
			}
			else if (r2 <= 5600)
			{
				killweapontype = 1;
				needed = 7;
			}
			else if (r2 <= 6500)
			{
				killweapontype = 2;
				needed = 9;
			}
			else if (r2 <= 7300)
			{
				killweapontype = 3;
				needed = 7;
			}
			else if (r2 <= 8300)
			{
				killweapontype = 4;
				needed = 9;
			}
			else if (r2 <= 8800)
			{
				killweapontype = 5;
				needed = 3;
			}
			else if (r2 <= 9300)
			{
				killweapontype = 6;
				needed = 3;
			}
			else
			{
				killweapontype = 7;
				needed = 7;
			}
		}
		else if (r <= 8000)
		{
			type = 2 + (Random(1, 100) <= 35);
			if (type == 3)
			{
				location1 = Random(0, g_Map.labels.size() - 1);
				needed = 15;
			}
			else needed = 25;
		}
		else 
		{
			type = 5;
			location1 = Random(0, g_Map.labels.size() - 1);
			do { location2 = Random(0, g_Map.labels.size() - 1); } while (location2 == location1);
			do { location3 = Random(0, g_Map.labels.size() - 1); } while (location3 == location1 || location3 == location2);
			needed = 1;
			oneMatch = true;
		}
	}
	totalNeeded = needed;
}

bool dc_game::HasMatch()
{
	return Match != nullptr;
}

void dc_game::StartNewMatch()
{
	if (Match == nullptr)
	{
		if (MatchType == 0)
		{
			Match = new dc_match;
			if (g_Config.m_record_replay.Value >= 1)Match->DemoRecord = 1;
			else Match->DemoRecord = 0;

			if (Match->DemoRecord != 1)Match->canDelete = true;

			sprintf(Match->players[0].szName, ThePlayer.szName);
			Match->players[0].iGliderTexture = ThePlayer.SelectedGlider;
			Match->players[0].iSkinTexture = ThePlayer.SelectedSkin;
			Match->players[0].iWeaponWrapTexture = ThePlayer.SelectedWrap;

			Match->Start(1, 1, 100);
			Match->KeyBinds = &this->Binds;
		}
		else
		{
			Match = new dc_match;
			if (g_Config.m_record_replay.Value >= 1)Match->DemoRecord = 1;
			else Match->DemoRecord = 0;

			if (Match->DemoRecord != 1)Match->canDelete = true;

			Match->PlayerHealReward = 50;
			Match->MatchType = 1;
			
			auto Diffs = GetBotDifficultiesForArenaLevel(GetArenaLevel());

			Match->EasyCases = Diffs[0];
			Match->NormalCases = Diffs[1];
			Match->HardCases = Diffs[2];
			Match->ExpertCases = Diffs[3];

			sprintf(Match->players[0].szName, ThePlayer.szName);
			Match->players[0].iGliderTexture = ThePlayer.SelectedGlider;
			Match->players[0].iSkinTexture = ThePlayer.SelectedSkin;
			Match->players[0].iWeaponWrapTexture = ThePlayer.SelectedWrap;

			Match->Start(1, 1, 100);
			Match->KeyBinds = &this->Binds;
		}

	}



}

void dc_game::StartNewDemoViewer(char* buffer)
{
	if (DViewer == nullptr)
	{
		DViewer = new dc_demo_viewer;
		file_t F;
		F.ReadInMemory(buffer);
		DViewer->Demo.convert_back(F);
		DViewer->Setup();
		DViewer->KeyBinds = &this->Binds;
	}
}



void dc_game::SetupDefaultBinds()
{
	for (int i = 0; i < 64; i++)Binds.KeysPrimary[i] = 0;
	Binds.KeysPrimary[DCK_SHOOT] = 0x01;
	Binds.KeysPrimary[DCK_UP] = 0x57; //W key;
	Binds.KeysPrimary[DCK_DOWN] = 0x53; //S key;
	Binds.KeysPrimary[DCK_LEFT] = 0x41; // A key;
	Binds.KeysPrimary[DCK_RIGHT] = 0x44; // D key;
	Binds.KeysPrimary[DCK_DROPITEM] = VK_MENU; //ALT key
	Binds.KeysPrimary[DCK_JUMPOFFBUS] = VK_SPACE;
	Binds.KeysPrimary[DCK_DESCEND] = VK_SPACE;
	Binds.KeysPrimary[DCK_RELOAD] = 0x52; //R key
	Binds.KeysPrimary[DCK_SLOT1] = 0x31; //1 key
	Binds.KeysPrimary[DCK_SLOT2] = 0x32; //2 key
	Binds.KeysPrimary[DCK_SLOT3] = 0x33; //3 key
	Binds.KeysPrimary[DCK_SLOT4] = 0x34; //4 key
	Binds.KeysPrimary[DCK_SLOT5] = 0x35; //5 key
	Binds.KeysPrimary[DCK_OPENINVENTORY] = 0x49; //I key
	Binds.KeysPrimary[DCK_OPENMINIMAP] = 0x4D; //M key
	Binds.KeysPrimary[DCK_MARKERPLACE] = 0x01;
	Binds.KeysPrimary[DCK_MARKERREMOVE] = 0x02;
	Binds.KeysPrimary[DCK_OPENCONSOLE] = 0x30; //0 key
	Binds.KeysPrimary[DCK_ALTERNATIVE] = VK_SHIFT;
	Binds.KeysPrimary[DCK_CLOSEMENU] = VK_ESCAPE;
	Binds.KeysPrimary[DCK_SWAP_TO_OTHER_PLAYER] = VK_RETURN;
	Binds.KeysPrimary[DCK_CONSOLE_ENTER] = VK_RETURN;


	Binds.KeysSecondary[DCK_UP] = VK_UP; //W key;
	Binds.KeysSecondary[DCK_DOWN] = VK_DOWN; //S key;
	Binds.KeysSecondary[DCK_LEFT] = VK_LEFT; // A key;
	Binds.KeysSecondary[DCK_RIGHT] = VK_RIGHT; // D key;
}

void fps_max()
{
	g_Framerate = g_Config.fps_max.Value;
	g_Window->setFramerateLimit(g_Framerate);
}

void g_res_x()
{
	g_Resolution.x = g_Config.g_res_x.Value;

}

void g_res_y()
{
	g_Resolution.y = g_Config.g_res_y.Value;

}

void g_antialias_level()
{
	int level = 1; //g_Config.g_antialias_level.Value;
	if (level < 0)level = 0;
	if (level > 5)level = 5;
	int AAs[] = { 0, 1, 2, 4, 8, 16 };
	int aalevel = AAs[level];

	if (aalevel > 1)
	{
		for (int i = 0; i < g_Textures.t.size() - 1; i++)
			g_Textures.get(i)->setSmooth(true);
	}
	else
	{
		for (int i = 0; i < g_Textures.t.size() - 1; i++)
			g_Textures.get(i)->setSmooth(false);
	}

	auto s = g_Window->getSettings();
	s.antialiasingLevel = aalevel;
	g_Window->close();

}



void dc_game::SetupUnlockables()
{
	Unlockables.push_back(dc_lockerunlockable(0, 0, -1, 0, "Default Skin"));
	Unlockables.push_back(dc_lockerunlockable(1, 0, -1, 0, "Default Glider"));
	Unlockables.push_back(dc_lockerunlockable(2, 0, -1, 0, "Default Wrap"));

	Unlockables.push_back(dc_lockerunlockable(0, 1, 5, 1,"Camouflage"));
	Unlockables.push_back(dc_lockerunlockable(0, 5, 10, 2, "Dark"));
	Unlockables.push_back(dc_lockerunlockable(0, 7, 15, 2, "Love"));
	Unlockables.push_back(dc_lockerunlockable(0, 2, 20, 3, "Red Arrow"));
	Unlockables.push_back(dc_lockerunlockable(0, 6, 25, 3, "Earth Ball"));
	Unlockables.push_back(dc_lockerunlockable(0, 9, 30, 2, "Radar"));
	Unlockables.push_back(dc_lockerunlockable(0, 8, 35, 3, "Super Ball"));
	Unlockables.push_back(dc_lockerunlockable(0, 4, 40, 4, "Basketball"));
	Unlockables.push_back(dc_lockerunlockable(0, 3, 45, 4, "Pac Monster"));

	Unlockables.push_back(dc_lockerunlockable(1, 3, 6, 1, "Black"));
	Unlockables.push_back(dc_lockerunlockable(1, 1, 11, 2, "Umbrella"));
	Unlockables.push_back(dc_lockerunlockable(1, 4, 18, 3, "Blue Arrow"));
	Unlockables.push_back(dc_lockerunlockable(1, 2, 26, 4, "Red Umbrella"));

	Unlockables.push_back(dc_lockerunlockable(2, 2, 3, 1, "All Black"));
	Unlockables.push_back(dc_lockerunlockable(2, 1, 9, 1, "All White"));
	Unlockables.push_back(dc_lockerunlockable(2, 5, 13, 2, "Inverted"));
	Unlockables.push_back(dc_lockerunlockable(2, 7, 16, 2, "Leafy"));
	Unlockables.push_back(dc_lockerunlockable(2, 4, 22, 3, "Golden"));
	Unlockables.push_back(dc_lockerunlockable(2, 6, 27, 4, "Corrupted"));
	Unlockables.push_back(dc_lockerunlockable(2, 3, 32, 4, "Misty"));

}

void dc_game::Setup()
{
	ThePlayer.Quests[0].Init();
	ThePlayer.Quests[1].Init();
	SetupDefaultBinds();
	dc_consolelog* m = new dc_consolelog("\0", sf::Color());
	OldConsoleMessages.push_back(m);

	g_Config.fps_max.Execute = (fps_max);
	g_Config.g_res_x.Execute = (g_res_x);
	g_Config.g_res_y.Execute = (g_res_y);
	//g_Config.g_antialias_level.Execute = (g_antialias_level);

	//if (!cmdExec("exec config.cfg"))
	//{

	//	SaveConfig("cfg\\config.cfg");
	//	cmdExec("exec config.cfg");
	//}
	if (!LoadProfile());
		SaveProfile();
	SettingFullscreen = g_Config.g_fullscreen.Value;
	sf::Vector2i Resolutions[] = { sf::Vector2i(640,480),sf::Vector2i(800,600),sf::Vector2i(1024,768),sf::Vector2i(1280,960),sf::Vector2i(1440,1080), sf::Vector2i(640,360),sf::Vector2i(1024,576),sf::Vector2i(1280,720),sf::Vector2i(1600,900),sf::Vector2i(1920,1080), sf::Vector2i(640,400),sf::Vector2i(1280,800),sf::Vector2i(1680,1050),sf::Vector2i(1680,720) };
	for (int i = 0; i < 14; i++)if (Resolutions[i] == g_Resolution)SelectedVideoSetting = i;
	
	CheckLevels();
	CheckTiers();
	//cmdClear("");
	for (int i = 0; i < 32; i++)ThePlayer.SkinUnlocked[i] = false;
	for (int i = 0; i < 16; i++)ThePlayer.GliderUnlocked[i] = false;
	for (int i = 0; i < 8; i++)ThePlayer.WrapUnlocked[i] = false;
	ThePlayer.SkinUnlocked[0] = true;
	ThePlayer.GliderUnlocked[0] = true;
	ThePlayer.WrapUnlocked[0] = true;
	SetupUnlockables();

	for (int i = 0; i < 2; i++)
	{
		if (ThePlayer.Quests[i].killweapontype < 0 || ThePlayer.Quests[i].location1 < -1 || ThePlayer.Quests[i].location2 <-1 || ThePlayer.Quests[i].location3 < -1
			|| ThePlayer.Quests[i].needed <= 0 || ThePlayer.Quests[i].tierReward < 5 || ThePlayer.Quests[i].totalNeeded < 0 || ThePlayer.Quests[i].type < 0)ThePlayer.Quests[i].Init();
	}

	Match = nullptr;
	DViewer = nullptr;

	ThePlayer.szName[63] = '\0';
}

void dc_game::LogMessage(char* msg, sf::Color color)
{
	if (g_Config.con_silent.Value >= 1.f)return;
	dc_consolelog* m = new dc_consolelog(msg, color);
	ConsoleLogs.push_back(m);
	ConsoleMessageIndex = 0;
}

void dc_game::LogConsoleMessage()
{
	if (g_Config.con_silent.Value >= 1.f)return;
	dc_consolelog* m = new dc_consolelog("%s\0", sf::Color(),ConsoleMessage);
	OldConsoleMessages.push_back(m);
	//ConsoleMessageIndex = OldConsoleMessages.size() - 1;
	ConsoleMessageIndex = 0;
}

bool dc_game::GetKeyStatus(int KEY, bool Continuous)
{
	if (Continuous)
	{
		if (Binds.KeysPrimary[KEY] && g_Keyboard.keys[Binds.KeysPrimary[KEY]])return true;
		if (Binds.KeysSecondary[KEY] && g_Keyboard.keys[Binds.KeysSecondary[KEY]])return true;
	}
	else
	{
		if (Binds.KeysPrimary[KEY] && g_Keyboard.hasJustPressed(Binds.KeysPrimary[KEY]))return true;
		if (Binds.KeysSecondary[KEY] && g_Keyboard.hasJustPressed(Binds.KeysSecondary[KEY]))return true;
	}
	return false;
}


void dc_game::CheckLevels()
{
	while (ThePlayer.Xp > GetXpNeededForLevel(ThePlayer.Level) && ThePlayer.Level < 99)
	{
		ThePlayer.Level++;
		if (ThePlayer.Level % 10 == 0)ThePlayer.TierStars += 10;
		else if (ThePlayer.Level % 5 == 0)ThePlayer.TierStars += 5;
		else ThePlayer.TierStars += 2;
	}
	while (ThePlayer.TierStars > 9 && ThePlayer.Tier < 99)
	{
		ThePlayer.Tier++;
		ThePlayer.TierStars -= 10;
	}

	if (ThePlayer.Xp > GetXpNeededForLevel(99))ThePlayer.Xp = GetXpNeededForLevel(99);

	if (ThePlayer.Tier == 99 && ThePlayer.Tier > 0)ThePlayer.Tier = 0;

	CheckTiers();
}

void dc_game::CheckTiers()
{
	for (int i = 0; i < Unlockables.size();i++)
	{
		auto ul = Unlockables[i];
		if (ul.Tier <= ThePlayer.Tier)
		{
			if (ul.Type == 0)
				if (!ThePlayer.SkinUnlocked[ul.Index])
				{
					ThePlayer.SkinUnlocked[ul.Index] = true;
					dc_lockergoteffect LG;
					LG.lockerUnlockable = &Unlockables[i];
					Effects.LG_Effects.push_back(LG);
				}
			if (ul.Type == 1)
				if (!ThePlayer.GliderUnlocked[ul.Index])
				{
					ThePlayer.GliderUnlocked[ul.Index] = true;
					dc_lockergoteffect LG;
					LG.lockerUnlockable = &Unlockables[i];
					Effects.LG_Effects.push_back(LG);
				}
			if (ul.Type == 2)
				if (!ThePlayer.WrapUnlocked[ul.Index])
				{
					ThePlayer.WrapUnlocked[ul.Index] = true;
					dc_lockergoteffect LG;
					LG.lockerUnlockable = &Unlockables[i];
					Effects.LG_Effects.push_back(LG);
				}
		}
	}
}

int dc_game::GetXpNeededForLevel(int level)
{
	static int Xp[100];
	
	static bool bRun = false;
	if (!bRun)
	{
		int tXp[100];
		tXp[0] = 100;

		for (int i = 1; i < 100; i++)
		{
			tXp[i] = tXp[i - 1] + 50 + tXp[i - 1] * 0.015f;
			tXp[i] = tXp[i] / 5 * 5;
			//ConLog("\nLevel %d - Xp: %d", i + 1, tXp[i]);
		}

		for (int i = 0; i < 100; i++) {
			Xp[i] = 0;
			for (int j = 0; j <= i; j++)
			{
				Xp[i]+=tXp[j];
			}
			//ConLog("\nLevel %d - Total Xp: %d", i + 1, Xp[i]);
		}
		bRun = true;
	}
	return Xp[level];
}

int dc_game::CalcExpForMatch()
{
	int timeAlive = (Match->players[0].Stats.fTimeAlive + 0.5f);
	int eliminations = Match->players[0].Stats.Elims.size();
	int placement = Match->players[0].Stats.iPlacement;

	int Xp = timeAlive;
	Xp += (eliminations * 75);

	if (placement < 50)Xp += 100;
	if (placement < 25)Xp += 100;
	if (placement < 15)Xp += 100;
	if (placement < 10)Xp += 100;
	if (placement < 5)Xp += 100;
	if (placement < 3)Xp += 100;
	if (placement <= 1)Xp += 250;

	ConLog("\nMatch Ended! Time: %d Elims: %d Placement: %d - Xp total: %d", timeAlive, eliminations, placement, Xp);

	return Xp;
}

int dc_game::GetEvaluateMatchForQuests(int i)
{

	int extraprog = 0;

		if (ThePlayer.Quests[i].type == 0 || ThePlayer.Quests[i].type == 1)
		{

			for (auto e : Match->players[0].Stats.Elims)
			{

				if (ThePlayer.Quests[i].type == 1)
				{
					float radius = g_Map.labels[ThePlayer.Quests[i].location1].size;
					sf::Vector2f middle = g_Map.labels[ThePlayer.Quests[i].location1].vPosition;
					if (GetDistance(e.targetPos, middle) > radius)continue;
				}
				if (ThePlayer.Quests[i].killweapontype == 0)
					extraprog++;
				else if (ThePlayer.Quests[i].killweapontype == 1 && g_Items[e.WeaponListindex].IsPistol())
					extraprog++;
				else if (ThePlayer.Quests[i].killweapontype == 2 && g_Items[e.WeaponListindex].IsSmg())
					extraprog++;
				else if (ThePlayer.Quests[i].killweapontype == 3 && g_Items[e.WeaponListindex].IsShotgun())
					extraprog++;
				else if (ThePlayer.Quests[i].killweapontype == 4 && g_Items[e.WeaponListindex].IsRifle())
					extraprog++;
				else if (ThePlayer.Quests[i].killweapontype == 5 && g_Items[e.WeaponListindex].IsSniper())
					extraprog++;
				else if (ThePlayer.Quests[i].killweapontype == 6 && g_Items[e.WeaponListindex].IsExplosive())
					extraprog++;
				else if (ThePlayer.Quests[i].killweapontype == 7 && g_Items[e.WeaponListindex].IsMachinegun())
					extraprog++;
			}
		}
		else if (ThePlayer.Quests[i].type == 2 || ThePlayer.Quests[i].type == 3)
		{
			for (auto c : Match->players[0].Stats.Chests)
			{
				if (ThePlayer.Quests[i].type == 3)
				{
					float radius = g_Map.labels[ThePlayer.Quests[i].location1].size;
					sf::Vector2f middle = g_Map.labels[ThePlayer.Quests[i].location1].vPosition;
					if (GetDistance(g_Map.chests[c].vPosition, middle) > radius)continue;
				}
				extraprog++;
			}
		}
		else if (ThePlayer.Quests[i].type == 4)
		{

			auto pos = Match->players[0].Stats.LandingPosition;
			float radius = g_Map.labels[ThePlayer.Quests[i].location1].size;
			sf::Vector2f middle = g_Map.labels[ThePlayer.Quests[i].location1].vPosition;
			if (GetDistance(pos, middle) <= radius)extraprog++;
		}
		else if (ThePlayer.Quests[i].type == 5)
		{
			auto locationList = Match->players[0].Stats.VisitedPositions;

			bool good1 = false, good2 = false, good3 = false;

			if (IsIn(locationList, ThePlayer.Quests[i].location1))good1 = true;
			if (IsIn(locationList, ThePlayer.Quests[i].location2))good2 = true;
			if (IsIn(locationList, ThePlayer.Quests[i].location3))good3 = true;

			if (ThePlayer.Quests[i].oneMatch)
			{
				if (good1&&good2&&good3)extraprog++;
			}
			else
			{
				if (good1)ThePlayer.Quests[i].location1 = -1;
				if (good2)ThePlayer.Quests[i].location2 = -1;
				if (good3)ThePlayer.Quests[i].location3 = -1;

				if (ThePlayer.Quests[i].location1 == -1
					&& ThePlayer.Quests[i].location2 == -1
					&& ThePlayer.Quests[i].location3 == -1)extraprog++;
			}

		}
		else if (ThePlayer.Quests[i].type == 6)
		{
			if (Match->GetAlivePlayers() <= 10)extraprog++;
		}
		else if (ThePlayer.Quests[i].type == 7)
		{
			if (Match->GetAlivePlayers() <= 25)extraprog++;
		}


		if (extraprog > ThePlayer.Quests[i].needed)extraprog = ThePlayer.Quests[i].needed;

		return extraprog;
}


void dc_game::EvaluateMatchForQuests()
{
	
	for (int i = 0; i < 2; i++)
	{
		if (ThePlayer.Quests[i].type == 0 || ThePlayer.Quests[i].type == 1)
		{

			for (auto e : Match->players[0].Stats.Elims)
			{

				if (ThePlayer.Quests[i].type == 1)
				{
					float radius = g_Map.labels[ThePlayer.Quests[i].location1].size;
					sf::Vector2f middle = g_Map.labels[ThePlayer.Quests[i].location1].vPosition;
					if(GetDistance(e.targetPos, middle) > radius)continue;
				}
				if (ThePlayer.Quests[i].killweapontype == 0)
					ThePlayer.Quests[i].needed--;
				else if (ThePlayer.Quests[i].killweapontype == 1 && g_Items[e.WeaponListindex].IsPistol())
					ThePlayer.Quests[i].needed--;
				else if (ThePlayer.Quests[i].killweapontype == 2 && g_Items[e.WeaponListindex].IsSmg())
					ThePlayer.Quests[i].needed--;
				else if (ThePlayer.Quests[i].killweapontype == 3 && g_Items[e.WeaponListindex].IsShotgun())
					ThePlayer.Quests[i].needed--;
				else if (ThePlayer.Quests[i].killweapontype == 4 && g_Items[e.WeaponListindex].IsRifle())
					ThePlayer.Quests[i].needed--;
				else if (ThePlayer.Quests[i].killweapontype == 5 && g_Items[e.WeaponListindex].IsSniper())
					ThePlayer.Quests[i].needed--;
				else if (ThePlayer.Quests[i].killweapontype == 6 && g_Items[e.WeaponListindex].IsExplosive())
					ThePlayer.Quests[i].needed--;
				else if (ThePlayer.Quests[i].killweapontype == 7 && g_Items[e.WeaponListindex].IsMachinegun())
					ThePlayer.Quests[i].needed--;
			}
		}
		else if (ThePlayer.Quests[i].type == 2 || ThePlayer.Quests[i].type == 3)
		{
			for (auto c : Match->players[0].Stats.Chests)
			{
				if (ThePlayer.Quests[i].type == 3)
				{
					float radius = g_Map.labels[ThePlayer.Quests[i].location1].size;
					sf::Vector2f middle = g_Map.labels[ThePlayer.Quests[i].location1].vPosition;
					if(GetDistance(g_Map.chests[c].vPosition, middle) > radius)continue;
				}
				ThePlayer.Quests[i].needed--;
			}
		}
		else if (ThePlayer.Quests[i].type == 4)
		{

			auto pos = Match->players[0].Stats.LandingPosition;
			float radius = g_Map.labels[ThePlayer.Quests[i].location1].size;
			sf::Vector2f middle = g_Map.labels[ThePlayer.Quests[i].location1].vPosition;
			if (GetDistance(pos, middle) <= radius)ThePlayer.Quests[i].needed=-1;
		}
		else if (ThePlayer.Quests[i].type == 5)
		{
			auto locationList = Match->players[0].Stats.VisitedPositions;

			bool good1 = false, good2 = false, good3 = false;

			if (IsIn(locationList, ThePlayer.Quests[i].location1))good1 = true;
			if (IsIn(locationList, ThePlayer.Quests[i].location2))good2 = true;
			if (IsIn(locationList, ThePlayer.Quests[i].location3))good3 = true;

			if (ThePlayer.Quests[i].oneMatch)
			{
				if (good1&&good2&&good3)ThePlayer.Quests[i].needed--;
			}
			else
			{
				if (good1)ThePlayer.Quests[i].location1 = -1;
				if (good2)ThePlayer.Quests[i].location2 = -1;
				if (good3)ThePlayer.Quests[i].location3 = -1;

				if (ThePlayer.Quests[i].location1 == -1
					&& ThePlayer.Quests[i].location2 == -1
					&& ThePlayer.Quests[i].location3 == -1)ThePlayer.Quests[i].needed--;
			}

		}
		else if (ThePlayer.Quests[i].type == 6)
		{
			if (Match->players[0].Stats.iPlacement <= 10)ThePlayer.Quests[i].needed--;
		}
		else if (ThePlayer.Quests[i].type == 7)
		{
			if (Match->players[0].Stats.iPlacement <= 25)ThePlayer.Quests[i].needed--;
		}
		if (ThePlayer.Quests[i].oneMatch && ThePlayer.Quests[i].needed > 0)ThePlayer.Quests[i].needed = ThePlayer.Quests[i].totalNeeded;

		if (ThePlayer.Quests[i].needed <= 0)
		{
			ThePlayer.TierStars += ThePlayer.Quests[i].tierReward;
			dc_questdoneeffect QDE;
			QDE.Quest = ThePlayer.Quests[i];
			Effects.QD_Effects.push_back(QDE);
			ThePlayer.Quests[i].Init();
		}
	}
}

void dc_game::EvaluateMatchForArenaPoints()
{
	int elims = Match->players[0].Stats.iEliminations;
	int placement = Match->players[0].Stats.iPlacement;

	int ArenaReward = 0;

	if (placement <= 50)ArenaReward += (51 - placement);
	if (placement <= 25)ArenaReward += 10;
	if (placement <= 10)ArenaReward += 15;
	if (placement <= 3)ArenaReward += 10;
	if (placement <= 1)ArenaReward += 25;

	ArenaReward += elims * 15;

	ThePlayer.ArenaPoints += ArenaReward;
}

int dc_game::GetArenaLevel()
{
	int points = ThePlayer.ArenaPoints;

	if (points < 200)return 0;
	if (points < 500)return 1;
	if (points < 1000)return 2;
	if (points < 1500)return 3;
	if (points < 2000)return 4;
	if (points < 3000)return 5;
	if (points < 4000)return 6;
	if (points < 6000)return 7;
	if (points < 10000)return 8;
	return 9;
}

int dc_game::GetArenaNeededForNextLevel()
{
	int points = ThePlayer.ArenaPoints;

	if (points < 200)return 200-points;
	if (points < 500)return 500-points;
	if (points < 1000)return 1000-points;
	if (points < 1500)return 1500-points;
	if (points < 2000)return 2000-points;
	if (points < 3000)return 3000-points;
	if (points < 4000)return 4000-points;
	if (points < 6000)return 6000-points;
	if (points < 10000)return 10000-points;
	return 0;
}

std::vector<int> dc_game::GetBotDifficultiesForArenaLevel(int i)
{
	if (i == 0)return{ 900,100,0,0 };
	if (i == 1)return{ 750,250,0,0 };
	if (i == 2)return{ 600,375,25,0 };
	if (i == 3)return{ 475,300,100,25 };
	if (i == 4)return{ 325,475,125,75 };
	if (i == 5)return{ 50,500,300,150 };
	if (i == 6)return{ 0,200,400,300 };
	if (i == 7)return{ 0,0,500,500 };
	if (i == 8)return{ 0,0,200,800 };
	if (i >= 9)return{ 0,0,0,1000 };
}

void dc_game::EvaluateMatch()
{
	if (!Match)return;

	if (Match->players[0].bOnBus)return;

	if (Match->MatchType == 1)
		EvaluateMatchForArenaPoints();

	ThePlayer.TotalMatches++;

	float intPart = 0;
	float fPart = modf(Match->players[0].Stats.fDistanceWalked, &intPart);
	ThePlayer.DistanceTravelledLow += fPart;
	while (ThePlayer.DistanceTravelledLow > 1)
	{
		ThePlayer.DistanceTravelledLow -= 1;
		ThePlayer.DistanceTravelledHigh += 1;
	}
	ThePlayer.DistanceTravelledHigh += intPart;

	ThePlayer.TotalTimeAlive += (Match->players[0].Stats.fTimeAlive + 0.5f);

	for (int i = 0; i < Match->players[0].Stats.Elims.size(); i++)
	{
		auto elim = Match->players[0].Stats.Elims[i];
		
		auto item = g_Items[elim.WeaponListindex];

		ThePlayer.TotalKills++;

		if (item.IsPistol())ThePlayer.TotalPistolKills++;
		else if (item.IsShotgun())ThePlayer.TotalShotgunKills++;
		else if (item.IsSmg())ThePlayer.TotalSubmachinegunKills++;
		else if (item.IsRifle())ThePlayer.TotalRifleKills++;
		else if (item.IsSniper())ThePlayer.TotalSniperKills++;
		else if (item.IsExplosive())ThePlayer.TotalExplosiveKills++;
		else if (item.IsMachinegun())ThePlayer.TotalMachinegunKills++;

	}
	ThePlayer.TotalDamage += Match->players[0].Stats.iDamageDealt;
	ThePlayer.LastMatchStats = Match->players[0].Stats;

	ThePlayer.TotalPlacement += Match->players[0].Stats.iPlacement;
	if (Match->players[0].Stats.iPlacement <= 1)ThePlayer.TotalWins++;
	if (Match->players[0].Stats.iPlacement <= 10)ThePlayer.TotalTop10s++;
	if (Match->players[0].Stats.iPlacement <= 25)ThePlayer.TotalTop25s++;

	ThePlayer.Xp += CalcExpForMatch();
	EvaluateMatchForQuests();
}


void dc_game::Quit()
{
	if (GM_STATE == 1 && Match)
	{
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
	}


	_mkdir("cfg");
	SaveConfig("cfg\\config.cfg");
	SaveProfile();
	g_Window->close();
}

void dc_game::Do()
{
	LockInput = (OW_STATUS > 0) || (TotalEffectCount());


	if (GetKeyStatus(DCK_OPENCONSOLE,false))
	{
		if (OW_STATUS == 1)CloseConsole();
		else OpenConsole();
	}
	else if (g_Keyboard.hasJustPressed(VK_ESCAPE))
	{
		if (OW_STATUS == 2)OW_STATUS = 0;
		else if (OW_STATUS == 3)OW_STATUS = 2;
		else if (OW_STATUS == 4)OW_STATUS = 2;
		else OW_STATUS = 2;
		if (GM_STATE != 1 && GM_STATE != 7)
			GM_STATE = 0;
	}
	if (GM_STATE == 0)
	{
		DrawMainMenu();
		
		if(!LockInput)
		DoMainMenu();
	}

	else if (GM_STATE == 1)
	{
		if (!HasMatch())StartNewMatch();
		Match->LockInput = OW_STATUS > 0;
		Match->Do();


	}
	else if (GM_STATE == 2)
	{
		DrawStatisticsMenu();
		if (!LockInput)
			DoStatisticsMenu();
	}
	else if (GM_STATE == 3)
	{
		DrawSettingsMenu();
		if (!LockInput)
			DoSettingsMenu();
	}
	else if (GM_STATE == 4)
	{
		DrawDemoMenu();
		if (!LockInput)
			DoDemoMenu();
	}
	else if (GM_STATE == 5)
	{
		DrawLockerMenu();
		if (!LockInput)
			DoLockerMenu();
	}
	else if (GM_STATE == 6)
	{
		DrawCreditsMenu();
		if (!LockInput)
			DoCreditsMenu();
	}
	else if (GM_STATE == 7)
	{
		if (DViewer)
		{
			DViewer->LockInput = OW_STATUS > 0;
			DViewer->Do();
		}
		else GM_STATE = 4;
	}
	if (OW_STATUS == 0);
	else if (OW_STATUS == 1)
	{
		DoConsole();
		DrawConsole();
	}
	else if (OW_STATUS == 2)
	{
		if (Match)
		{
			DrawIngameEscapeMenu();
			DoIngameEscapeMenu();
		}
		else if (DViewer)
		{
			DrawInDemoEscapeMenu();
			DoInDemoEscapeMenu();
		}
		else OW_STATUS = 0;
	}
	else if (OW_STATUS == 3)
	{
		if (Match)
		{
			DrawIngameSettingsMenu();
			DoIngameSettingsMenu();
		}
		else OW_STATUS = 0;
	}
	else if (OW_STATUS == 4)
	{
		if (Match)
		{
			DrawShowStatsMenu();
			DoShowStatsMenu();
		}
		else OW_STATUS = 0;
	}
	else if (OW_STATUS == 5)
	{
		DoQuitPrompt();
		DrawQuitPrompt();
	}
	else if (OW_STATUS == 6)
	{
		DoPressKeyOL();
		DrawPressKeyOL();
	}
	else if (OW_STATUS == 7)
	{
		if (Match)
		{
			DrawIngameSettingsMenu();
			DoIngameSettingsMenu();
			DoPressKeyOL();
			DrawPressKeyOL();
		}
		else OW_STATUS = 0;
	}
	if (GM_STATE != 1)
	{
		g_Sounds.ManipulateAllSounds(g_Config.mastervolume.Value*100.f, sf::Vector2f(0, 0));
		g_Sounds.ManipulateDynamicSounds(g_Config.mastervolume.Value*100.f, sf::Vector2f(0, 0));

		if (GM_STATE != 7)
		{
			DrawQuitButton();
			if (!LockInput)DoQuitButton();
		}
	}
	DrawEffects();
	if (g_Config.g_brightness.Value < 1.f)
		IWindow::RenderOverlay(0, 0, g_Resolution.x, g_Resolution.y, 0, 0, 0, max(0, 255 - g_Config.g_brightness.Value * 255));

	show_fps();
}