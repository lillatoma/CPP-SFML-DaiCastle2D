#include "ITek.h"

/*
void ITek::CreateTEK(char* _output)
{
std::ofstream current;
int files = 0;
for (int i = 0; i < 100; i++)
{
if (strcmp(input[i], ""))files += 1;
}

if (files)
{

file[0].OpenHandle(_output);
file[0].GetHandle(current);


for (int i = 0; i < 100; i++)
if (strcmp(input[i], ""))
{
Sleep(25);
file[i].ChangeHandle(current);
printf("input: %s\n", input[i]);
file[i].WriteAnything("$$$$$$");
file[i].WriteAnything(input[i]);
file[i].WriteAnything("$$$$$$_-_$startcontent__$");

file[i].DumpToHandle();
file[i].WriteAnything("$__endcontent$_-_\n");
file[i].GetHandle(current);

}

printf("%s created\n", _output);
}
}
*/
enum States
{
	SEEKING_NAME_START,
	SEEKING_NAME_END,
	SEEKING_CONTENT_START,
	SEEKING_CONTENT_END
};

void ITek::DispackTEK(char* tekname_)
{
	if (strcmp(tekname_, ""))
	{
		file_t TEK_file;
		TEK_file.ReadInMemory(tekname_);
		auto size = TEK_file.size;
		auto loc = TEK_file.loc_in_mem;
		char State = SEEKING_NAME_START;
		auto files = new file_t[100];
		auto names = new char*[100];
		auto lengths = new int[100];
		char filesfound = 0;


		for (int i = 0; i < size;)
		{
			if (State == SEEKING_NAME_START)
			{
				if (strstr(loc + i, "$$$$$$"))
				{
					i += 6 - (i > 0);
					names[filesfound] = loc + i;
					State = SEEKING_NAME_END;
				}
			}
			else if (State == SEEKING_NAME_END)
			{
				auto end = strstr(loc + i, "$$$$$$");
				lengths[filesfound] = end - names[filesfound];
				i += lengths[filesfound];
				i += 6;

				State = SEEKING_CONTENT_START;
			}
			else if (State == SEEKING_CONTENT_START)
			{
				auto contentstart = strstr(loc + i, "_-_$startcontent__$") + 19;
				files[filesfound].loc_in_mem = contentstart;
				i += 19;
				State = SEEKING_CONTENT_END;
			}
			else if (State == SEEKING_CONTENT_END)
			{
				auto endcontent = strstr(loc + i, "$__endcontent$_-_");
				if (endcontent)
				{
					files[filesfound].size = endcontent - files[filesfound].loc_in_mem + 1;
					i += endcontent - (loc + i) + 19;

					filesfound++;
					State = SEEKING_NAME_START;
				}
				else
				{
					if (strlen(loc + i))
					{
						i += strlen(loc + i);
					}
					else i++;
				}
			}


		}

		for (int i = 0; i < filesfound; i++)
		{
			char _name[128] = "";
			strcpy(_name, "dispack\\");

			//_mkdir("dispack");
			strncpy(_name + 8, names[i], lengths[i]);
			for (int i = 0; i < strlen(_name); i++)
			{
				char _buf[128];
				auto per = strstr(_name + i, "\\");
				if (per)
				{

					strncpy(_buf, _name, per - _name);
					_buf[per - _name] = '\0';
					i += per - _name - i;
					_mkdir(_buf);
					printf("Making Dir - %s\n", _buf);
				}
			}
			printf("Dispacking - %s\n", _name);
			files[i].Dump(_name);
		}


		delete[] files;
		delete[] lengths;
		delete[] names;

	}
}

void ITek::DispackTEKToFiles(char* tekname_, file_t* startfile, int& found)
{
	if (strcmp(tekname_, ""))
	{
		file_t* TEK_file = new file_t;
		TEK_file->ReadInMemory(tekname_);
		auto size = TEK_file->size;
		auto loc = TEK_file->loc_in_mem;
		char State = SEEKING_NAME_START;
		auto files = new file_t[100];
		auto names = new char*[100];
		auto lengths = new int[100];
		char filesfound = 0;


		for (int i = 0; i < size;)
		{
			if (State == SEEKING_NAME_START)
			{
				if (strstr(loc + i, "$$$$$$"))
				{
					i += 6 - (i > 0);
					names[filesfound] = loc + i;
					State = SEEKING_NAME_END;
				}
			}
			else if (State == SEEKING_NAME_END)
			{
				auto end = strstr(loc + i, "$$$$$$");
				lengths[filesfound] = end - names[filesfound];
				i += lengths[filesfound];
				i += 6;

				State = SEEKING_CONTENT_START;
			}
			else if (State == SEEKING_CONTENT_START)
			{
				auto contentstart = strstr(loc + i, "_-_$startcontent__$") + 19;
				files[filesfound].loc_in_mem = contentstart;
				i += 19;
				State = SEEKING_CONTENT_END;
			}
			else if (State == SEEKING_CONTENT_END)
			{
				auto endcontent = strstr(loc + i, "$__endcontent$_-_");
				if (endcontent)
				{
					files[filesfound].size = endcontent - files[filesfound].loc_in_mem + 1;
					i += endcontent - (loc + i) + 19;

					filesfound++;
					State = SEEKING_NAME_START;
				}
				else
				{
					if (strlen(loc + i))
					{
						i += strlen(loc + i);
					}
					else i++;
				}
			}


		}
		/*
		for (int i = 0; i < filesfound; i++)
		{
		char _name[128] = "";
		strcpy(_name, "dispack\\");

		//_mkdir("dispack");
		strncpy(_name + 8, names[i], lengths[i]);
		for (int i = 0; i < strlen(_name); i++)
		{
		char _buf[128];
		auto per = strstr(_name + i, "\\");
		if (per)
		{

		strncpy(_buf, _name, per - _name);
		_buf[per - _name] = '\0';
		i += per - _name - i;
		_mkdir(_buf);
		printf("Making Dir - %s\n", _buf);
		}
		}
		printf("Dispacking - %s\n", _name);
		files[i].Dump(_name);
		}
		*/
		for (int i = 0; i < filesfound; i++)
		{
			(startfile + i)->loc_in_mem = files[i].loc_in_mem;
			(startfile + i)->size = files[i].size;
		}
		found = filesfound;



		delete[] files;
		delete[] lengths;
		delete[] names;

	}
}

void ITek::DispackTEKToFilesWithNames(char* tekname_, file_t* startfile, int& found, char* startname, unsigned int deltaName)
{
	if (strcmp(tekname_, ""))
	{
		file_t* TEK_file = new file_t;
		TEK_file->ReadInMemory(tekname_);
		auto size = TEK_file->size;
		auto loc = TEK_file->loc_in_mem;
		char State = SEEKING_NAME_START;
		auto files = new file_t[100];
		auto names = new char*[100];
		auto lengths = new int[100];
		char filesfound = 0;


		for (int i = 0; i < size;)
		{
			if (State == SEEKING_NAME_START)
			{
				if (strstr(loc + i, "$$$$$$"))
				{
					i += 6 - (i > 0);
					names[filesfound] = loc + i;
					State = SEEKING_NAME_END;
				}
			}
			else if (State == SEEKING_NAME_END)
			{
				auto end = strstr(loc + i, "$$$$$$");
				lengths[filesfound] = end - names[filesfound];
				i += lengths[filesfound];
				i += 6;

				State = SEEKING_CONTENT_START;
			}
			else if (State == SEEKING_CONTENT_START)
			{
				auto contentstart = strstr(loc + i, "_-_$startcontent__$") + 19;
				files[filesfound].loc_in_mem = contentstart;
				i += 19;
				State = SEEKING_CONTENT_END;
			}
			else if (State == SEEKING_CONTENT_END)
			{
				auto endcontent = strstr(loc + i, "$__endcontent$_-_");
				if (endcontent)
				{
					files[filesfound].size = endcontent - files[filesfound].loc_in_mem + 1;
					i += endcontent - (loc + i) + 19;

					filesfound++;
					State = SEEKING_NAME_START;
				}
				else
				{
					if (strlen(loc + i))
					{
						i += strlen(loc + i);
					}
					else i++;
				}
			}


		}
		/*
		for (int i = 0; i < filesfound; i++)
		{
		char _name[128] = "";
		strcpy(_name, "dispack\\");

		//_mkdir("dispack");
		strncpy(_name + 8, names[i], lengths[i]);
		for (int i = 0; i < strlen(_name); i++)
		{
		char _buf[128];
		auto per = strstr(_name + i, "\\");
		if (per)
		{

		strncpy(_buf, _name, per - _name);
		_buf[per - _name] = '\0';
		i += per - _name - i;
		_mkdir(_buf);
		printf("Making Dir - %s\n", _buf);
		}
		}
		printf("Dispacking - %s\n", _name);
		files[i].Dump(_name);
		}
		*/
		for (int i = 0; i < filesfound; i++)
		{
			(startfile + i)->loc_in_mem = files[i].loc_in_mem;
			(startfile + i)->size = files[i].size;
			strncpy(startname + i * deltaName, names[i], min(deltaName - 1, lengths[i]));
			sprintf(startname + i*deltaName, "%s\0", startname + i*deltaName);
		}
		found = filesfound;



		delete[] files;
		delete[] lengths;
		delete[] names;

	}
}