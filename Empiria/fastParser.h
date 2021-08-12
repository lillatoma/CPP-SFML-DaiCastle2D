#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <fstream>

enum KeyValType
{
	T_FLOAT,
	T_INT,
	T_BOOL,
	T_CHARARRAY

};

struct keyval_t
{
	KeyValType type;
	char required[64];
	char* value_to_change;
};

struct OperatorRead
{
	std::ofstream output;
	keyval_t* stored_info = nullptr;
	int current_key_val = 0;
	int valsize = 0;
	unsigned int expected_filesize = 1024 * 1024;
	char* file_read_in_mem;
	int* linevalues;
	int linecount = 0;


	void InitKeyValues(int size);
	void AddKeyValue(char* filter, DWORD value, KeyValType valtype);
	int GetFileSize(char* filename);
	int GetLineSize(char* filename);
	void ReadFileInMemory(char* fiiename);

	void InterpretLines();
	void InterpretLine(int line);
	void InterpretLineExact(int line, int dependency_id);
	void InterpretAsInt(char* sbstr, int dependency_id);
	void InterpretAsFloat(char* sbstr, int dependency_id);
	void InterpretAsString(char* sbstr, int dependency_id);
	void InterpretAsBool(char* sbstr, int dependency_id);


	void WriteInit(char* filename);
	void WriteKeyValue(int i);
	void WriteAllKeyValues();
	void WritePre(char* text);
	void WriteClear(char* original_name);
	void WriteClose();
};

struct file_t
{
	//READ
	char* loc_in_mem;
	unsigned int size;
	unsigned int lines = 0;

	void GetAbsSize(char* location);
	void ReadInMemory(char* location);
	void GetLineCount(char* location);


	//WRITE
	void Dump(char* location, bool drawscr = false);
};
