#include "DaiCastle.h"

void dc_game::show_fps()
{
	static dc_clock clock;
	static int fps_counted = 0;

	static int count = 0;

	if (clock.GetDiff() >= 1000)
	{
		fps_counted = count;
		count = 0;
		clock.Update();
	}
	char buf[16];

	if (g_Config.fps_enable.Value < 1.f)return;

	sprintf(buf, "%d FPS", fps_counted);

	auto dim = IWindow::GetTextSize(buf, g_Resolution.y*0.0333f);

	IWindow::RenderTextB(g_Resolution.x*0.95f-dim.x,g_Resolution.y*0.005f, buf, g_Resolution.y*0.0333f, 255, 0, 0, 255);

	

	count++;
}

int dc_match::GetAvailableChestNumber()
{
	int n = 0;
	for (int i = 0; i < map.chests.size(); i++)
	{
		if (!map.chests[i].bOpen)n++;

	}
	return n;
}

std::vector<int> dc_match::GetAvailableChests(sf::Vector2f pos, float radius)
{
	std::vector<int> R;
	for (int i = 0; i < map.chests.size(); i++)
	{
		if (map.chests[i].bOpen)continue;
		if (GetDistance(pos, map.chests[i].vPosition) <= radius)R.push_back(i);

	}
	return R;
}

int dc_match::GetClosestChestWithExceptions(sf::Vector2f Mid,std::vector<int> Exceptions)
{
	int retID = -1;
	
	for (int i = 0; i < map.chests.size(); i++)
	{
		if (IsIn(Exceptions, i))continue;
		if (IsPointInStorm(map.chests[i].vPosition))continue;
		if (retID == -1 || GetDistance(map.chests[i].vPosition, Mid) < GetDistance(map.chests[retID].vPosition, Mid))retID = i;
	}
	return retID;
}


int dc_match::GetClosestChestToPosition(sf::Vector2f Pos)
{
	int chest_id = -1;
	float chest_distance = 0.f;
	for (int i = 0; i < map.chests.size(); i++)
	{
		auto chest = map.chests[i];
		if (chest.bOpen)continue;
		auto dist = GetDistance(Pos, chest.vPosition);
		if (chest_id == -1)
		{
			chest_id = i;
			chest_distance = dist;
		}
		else if (dist < chest_distance)
		{
			chest_id = i;
			chest_distance = dist;
		}
	}
	return chest_id;
}

void dc_match::PrintAllWeaponDPS()
{
	for (int i = 0; i < g_Items.size(); i++)
	{

		ConLog("\n#%d | Standing | %s | 2.5m: %.3f | 10m: %.3f | 20m: %.3f | 40m: %.3f",
			i, g_Items[i].szName, g_Items[i].CalculateDPS(2.5, true), g_Items[i].CalculateDPS(10., true), g_Items[i].CalculateDPS(20., true), g_Items[i].CalculateDPS(40., true));
	}

	for (int i = 0; i < g_Items.size(); i++)
	{
		ConLog("\n#%d | Moving | %s | 2.5m: %.3f | 10m: %.3f | 20m: %.3f | 40m: %.3f",
			i, g_Items[i].szName, g_Items[i].CalculateDPS(2.5, false), g_Items[i].CalculateDPS(10., false), g_Items[i].CalculateDPS(20., false), g_Items[i].CalculateDPS(40., false));

	}
}

void dc_match::ClearUnreachableItems()
{
	static dc_clock Clock;
	if (Clock.GetDiff() > 1000)
	{
		float FurthestOutDistance = 0.f;
		sf::Vector2f CurrentStormMiddle = GetCurrentStormMiddle();
		float CurrentStormRadius = GetCurrentStormDiameter();
		for (int i = 0; i < 100; i++)
		{
			if (players[i].iHealth <= 0)continue;
			if (GetDistance(CurrentStormMiddle, players[i].vPosition) > FurthestOutDistance)FurthestOutDistance = GetDistance(CurrentStormMiddle, players[i].vPosition);
		}

		for (int i = map.items.size() - 1; i >= 0; i--)
		{
			if (map.items[i].bOwned)map.items.erase(map.items.begin() + i);
			else if (GetDistance(CurrentStormMiddle, map.items[i].vPosition) > (10.f + max(FurthestOutDistance, CurrentStormRadius / 2)))map.items.erase(map.items.begin() + i);
		}
		Clock.Update();
	}
}

bool dc_match::GetKeyStatus(int KEY, bool Continuous)
{
	if (LockInput)return false;
	if (Continuous)
	{
		if (KeyBinds->KeysPrimary[KEY] && g_Keyboard.keys[KeyBinds->KeysPrimary[KEY]])return true;
		if (KeyBinds->KeysSecondary[KEY] && g_Keyboard.keys[KeyBinds->KeysSecondary[KEY]])return true;
	}
	else
	{
		if (KeyBinds->KeysPrimary[KEY] && g_Keyboard.hasJustPressed(KeyBinds->KeysPrimary[KEY]))return true;
		if (KeyBinds->KeysSecondary[KEY] && g_Keyboard.hasJustPressed(KeyBinds->KeysSecondary[KEY]))return true;
	}
	return false;
}

std::vector<int> dc_match::GetKillLeaders()
{
	std::vector<int> IDs;

	auto killcomp = [=](int a, int b)
	{
		return players[a].Stats.iEliminations >= players[b].Stats.iEliminations;
	};
	for (int i = 0; i < 100; i++)IDs.push_back(i);

	std::sort(IDs.begin(), IDs.end(), killcomp);

	return IDs;
}

void dc_match::BotGiveNames()
{
	static std::vector<char*> EasyNames;
	static std::vector<char*> NormalNames;
	static std::vector<char*> HardNames;
	static std::vector<char*> ExpertNames;

	static bool bHasrun = false;

	if (!bHasrun)
	{


		{
			auto File = g_Files.GetFileByName("BotNamesEasy.txt");
			int Enter = 0;
			for (int i = 0; i < File.size; i++)
			{
				if (File.loc_in_mem[i] == '\n')
				{
					int size = snprintf(NULL, 0, "%.*s\0", i - Enter - 1, File.loc_in_mem + Enter) + 4;
					char* Name = new char[size];
					sprintf(Name, "%.*s\0", i - Enter - 1, File.loc_in_mem + Enter);
					EasyNames.push_back(Name);
					Enter = i + 1;
				}
			}
		}
		{
			auto File = g_Files.GetFileByName("BotNamesNormal.txt");
			int Enter = 0;
			for (int i = 0; i < File.size; i++)
			{
				if (File.loc_in_mem[i] == '\n')
				{
					int size = snprintf(NULL, 0, "%.*s\0", i - Enter - 1, File.loc_in_mem + Enter) + 4;
					char* Name = new char[size];
					sprintf(Name, "%.*s\0", i - Enter - 1, File.loc_in_mem + Enter);
					NormalNames.push_back(Name);
					Enter = i + 1;
				}
			}
		}
		{
			auto File = g_Files.GetFileByName("BotNamesHard.txt");
			int Enter = 0;
			for (int i = 0; i < File.size; i++)
			{
				if (File.loc_in_mem[i] == '\n')
				{
					int size = snprintf(NULL, 0, "%.*s\0", i - Enter - 1, File.loc_in_mem + Enter) + 4;
					char* Name = new char[size];
					sprintf(Name, "%.*s\0", i - Enter - 1, File.loc_in_mem + Enter);
					HardNames.push_back(Name);
					Enter = i + 1;
				}
			}
		}
		{
			auto File = g_Files.GetFileByName("BotNamesExpert.txt");
			int Enter = 0;
			for (int i = 0; i < File.size; i++)
			{
				if (File.loc_in_mem[i] == '\n')
				{
					int size = snprintf(NULL, 0, "%.*s\0", i - Enter - 1, File.loc_in_mem + Enter) + 4;
					char* Name = new char[size];
					sprintf(Name, "%.*s\0", i - Enter - 1, File.loc_in_mem + Enter);
					ExpertNames.push_back(Name);
					Enter = i + 1;
				}
			}
		}
		bHasrun = true;
	}

	std::vector<int> easy, normal, hard, expert;
	for (int i = 0; i < EasyNames.size(); i++)easy.push_back(i);
	for (int i = 0; i < NormalNames.size(); i++)normal.push_back(i);
	for (int i = 0; i < HardNames.size(); i++)hard.push_back(i);
	for (int i = 0; i < ExpertNames.size(); i++)expert.push_back(i);


	for (int i = 1; i < 100; i++)
	{
		if (BotData[i].botDifficulty == 0)
		{
			int r = Random(0, easy.size() - 1);
			sprintf(players[i].szName,"%s\0", EasyNames[easy[r]]);
			easy.erase(easy.begin() + r);
		}
		if (BotData[i].botDifficulty == 1)
		{
			int r = Random(0, normal.size() - 1);
			sprintf(players[i].szName, "%s\0", NormalNames[normal[r]]);
			normal.erase(normal.begin() + r);
		}
		if (BotData[i].botDifficulty == 2)
		{
			int r = Random(0, hard.size() - 1);
			sprintf(players[i].szName, "%s\0", HardNames[hard[r]]);
			hard.erase(hard.begin() + r);
		}
		if (BotData[i].botDifficulty == 3)
		{
			int r = Random(0, expert.size() - 1);
			sprintf(players[i].szName, "%s\0", ExpertNames[expert[r]]);
			expert.erase(expert.begin() + r);
		}
	}
}

sf::Vector2f dc_match::GetCameraPosition()
{
	if (vCameraMode == 0)
		return vCameraPosition;
	else return players[camera_follows].vPosition;
}