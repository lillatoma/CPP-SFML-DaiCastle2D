#pragma once
#include "fastParser.h"
#include <iostream>
#include <direct.h>

struct _Tek
{
	static void CreateTEK(char* _output);
	static void DispackTEK(char* tekname_);
	static void DispackTEKToFiles(char* tekname_, file_t* startfile, int& found);
	static void DispackTEKToFilesWithNames(char* tekname_, file_t* startfile, int& found, char* startname, unsigned int deltaName);

};