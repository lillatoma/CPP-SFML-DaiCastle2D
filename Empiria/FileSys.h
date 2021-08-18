#pragma once
#include "_Tek.h"

struct filesystem
{
	file_t file[10000];
	char names[10000][100];
	unsigned int cur_ent = 0;

	file_t GetFileByName(char* name);
	file_t GetFileByID(unsigned id);
	unsigned int GetIDByName(char* name);
	void LoadAll();
	void ListLoadedFiles();
	void LoadFile(char* File);
	void AddFile(file_t F);

private: void LoadTEK(char* tekname);
};

extern filesystem g_Files;
