#include "FileSys.h"
#include "_Tek.h"
#include "includes.h"

filesystem g_Files;

file_t filesystem::GetFileByName(char* name)
{
	auto _name = name;
	for (int i = cur_ent - 1; i >= 0; i--)
	{
		if (!(strcmp(_name, names[i])))
			return file[i];
	}
}

void filesystem::LoadTEK(char* tekname)
{
	int found = 0;

	_Tek::DispackTEKToFilesWithNames(tekname, &file[cur_ent], found, names[cur_ent], 100);
	cur_ent += found;
	Sleep(2);
}

void filesystem::LoadFile(char* name)
{
	file_t F;
	F.ReadInMemory(name);
	file[cur_ent] = F;
	sprintf(names[cur_ent], name);
	cur_ent++;
}


void filesystem::LoadAll()
{
	LoadTEK("basics.tek");
	LoadTEK("imap.tek");
	LoadTEK("travian.tek");
	LoadTEK("texx.tek");
	LoadTEK("dctextures.tek");
	LoadTEK("dcsounds.tek");
	if (!IsEditor)
	{
		LoadFile("BotNamesEasy.txt");
		LoadFile("BotNamesNormal.txt");
		LoadFile("BotNamesHard.txt");
		LoadFile("BotNamesExpert.txt");
	}
}

void filesystem::ListLoadedFiles()
{
	for (int i = 0; i < cur_ent; i++)
	{
		printf("%d\t| %s\n",i, names[i]);
	}
}

file_t filesystem::GetFileByID(unsigned id)
{
	return file[id];
}

unsigned filesystem::GetIDByName(char* name)
{
	for (int i = cur_ent - 1; i >= 0; i--)
	{
		if (!(strcmp(name, names[i])))
			return i;
	}


}