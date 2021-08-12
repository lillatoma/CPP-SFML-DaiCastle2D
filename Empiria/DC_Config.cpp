#include "DaiCastle.h"

bool dc_game::LoadProfile()
{
	file_t File;
	File.ReadInMemory("profile.md");

	unsigned int profilesize = sizeof(dc_playerprofile);
	if (File.size < profilesize-32)return false;

	//For Whatever the fuck the reason was, I couldn't copy memory from the file to the profile

	auto right = (dc_playerprofile*)File.loc_in_mem;

	ThePlayer = *right;

	//ThePlayer.ArenaPoints = right->ArenaPoints;
	//ThePlayer.DistanceTravelledHigh = right->DistanceTravelledHigh;
	//ThePlayer.DistanceTravelledLow = right->DistanceTravelledLow;
	//for (int i = 0; i < 16; i++)
	//	ThePlayer.GliderUnlocked[i] = right->GliderUnlocked[i];
	//ThePlayer.LastMatchKills = right->LastMatchKills;
	//ThePlayer.LastMatchPlacement = right->LastMatchPlacement;
	////ThePlayer.LastMatchStats = right->LastMatchStats;
	//ThePlayer.Level = right->Level;
	//ThePlayer.Quests[0] = right->Quests[0];
	//ThePlayer.Quests[1] = right->Quests[1];
	//ThePlayer.QuestsFinished = right->QuestsFinished;
	//ThePlayer.SelectedGlider = right->SelectedGlider;
	//ThePlayer.SelectedSkin = right->SelectedSkin;
	//ThePlayer.SelectedWrap = right->SelectedWrap;
	//for (int i = 0; i < 32; i++)
	//	ThePlayer.SkinUnlocked[i] = right->SkinUnlocked[i];
	//sprintf(ThePlayer.szName, right->szName);
	//ThePlayer.Tier = right->Tier;
	//ThePlayer.TierStars = right->TierStars;
	//ThePlayer.TotalDamage = right->TotalDamage;
	//ThePlayer.TotalExplosiveKills = right->TotalExplosiveKills;
	//ThePlayer.TotalKills = right->TotalKills;
	//ThePlayer.TotalMachinegunKills = right->TotalMachinegunKills;
	//ThePlayer.TotalMatches = right->TotalMatches;
	//ThePlayer.TotalPistolKills = right->TotalPistolKills;
	//ThePlayer.TotalPlacement = right->TotalPlacement;
	//ThePlayer.TotalRifleKills = right->TotalRifleKills;
	//ThePlayer.TotalShotgunKills = right->TotalShotgunKills;
	//ThePlayer.TotalSniperKills = right->TotalSniperKills;
	//ThePlayer.TotalSubmachinegunKills = right->TotalTimeAlive;
	//ThePlayer.TotalTimeAlive = right->TotalTimeAlive;
	//ThePlayer.TotalTop10s = right->TotalTop10s;
	//ThePlayer.TotalTop25s = right->TotalTop25s;
	//ThePlayer.TotalWins = right->TotalWins;
	//for (int i = 0; i < 8; i++)
	//	ThePlayer.WrapUnlocked[i] = right->WrapUnlocked[i];
	//ThePlayer.Xp = right->Xp;






	delete[] File.loc_in_mem;
	return true;
}

void dc_game::SaveProfile()
{
	char* Buffer = new char[sizeof(dc_playerprofile) + 4];
	for (unsigned int i = 0; i < sizeof(dc_playerprofile); i++)
	{
		*(Buffer + i) = *(((char*)(&ThePlayer)) + i);
	}
	file_t File;
	File.loc_in_mem = Buffer;
	File.size = sizeof(dc_playerprofile);

	File.Dump("profile.md");

	delete[]Buffer;
}

bool dc_game::LoadConfig(char* name)
{
	for (int i = 0; i < cfgNames.size(); i++)
	{
		if (strstr(name, cfgNames[i]))return false;
	}


	std::vector<char*> CommandList;

	auto File = file_t();
	File.ReadInMemory(name);
	if (File.size < 10)return false;

	auto cfgName = new char[strlen(name) + 4];
	sprintf(cfgName, name);
	cfgNames.push_back(cfgName);

	printf(File.loc_in_mem);

	int Enter = 0;
	for (int i = 0; i < File.size; i++)
	{
		if (File.loc_in_mem[i] == '\n' || File.loc_in_mem[i] == '\r')
		{
			int size = snprintf(NULL, 0, "%.*s\0", i - Enter , File.loc_in_mem + Enter) + 4;
			char* Name = new char[size];
			sprintf(Name, "%.*s\0", i - Enter, File.loc_in_mem + Enter);
			CommandList.push_back(Name);
			Enter = i + 1;
		}
		else if ( i == File.size - 1)
		{
			int size = snprintf(NULL, 0, "%.*s\0", i - Enter, File.loc_in_mem + Enter) + 4;
			char* Name = new char[size];
			sprintf(Name, "%.*s\0", i - Enter, File.loc_in_mem + Enter);
			CommandList.push_back(Name);
			Enter = i + 1;
		}
	}

	//for (int i = 0; i < CommandList.size(); i++)
	//	printf("\n'%s'", CommandList[i]);
	float originalValue = g_Config.con_silent.Value;
	g_Config.con_silent.Value = 2.f;

	for (auto c : CommandList)
	{
		ConsoleExecuteCommand(c);
		if (c) delete[] c;
	}
	g_Config.con_silent.Value = originalValue;

	for(int i = 0; i < cfgNames.size();i++)
		if (strstr(name, cfgNames[i]))
		{
			cfgNames.erase(cfgNames.begin() + i);
			break;
		}


	delete[]File.loc_in_mem;

	return true;
}

void dc_game::SaveConfig(char* name)
{
	char Buffer[4 * 4096] = "unbind all";
	auto KN = GetAllKeyNames();
	auto AN = GetAllActNames();
	for (int i = 0; i < 32; i++)
	{
		if (Binds.KeysPrimary[i] != 0)
		{
			sprintf(Buffer, "%s\nbind %s %s", Buffer, KN[Binds.KeysPrimary[i]], AN[i]);
		}
		if (Binds.KeysSecondary[i] != 0)
		{
			sprintf(Buffer, "%s\nbind %s %s", Buffer, KN[Binds.KeysSecondary[i]], AN[i]);
		}
	}
	for (int i = 0; i < sizeof(dc_config) / sizeof(dc_convar); i++)
	{
		auto pointer = (dc_convar*)&g_Config + i; // + i * sizeof(dc_convar);

		if (pointer->Cheat)continue;
		if (strstr(pointer->CommandName, "gm_cheats"))continue;
		if (strstr(pointer->CommandName, "con_silent"))continue;
		sprintf(Buffer, "%s\n%s %f", Buffer, pointer->CommandName, pointer->Value);
	}
	sprintf(Buffer, "%s\nexec autorun.cfg\n", Buffer);
	file_t F;
	F.loc_in_mem = Buffer;
	F.size = strlen(Buffer);
	F.Dump(name);
}