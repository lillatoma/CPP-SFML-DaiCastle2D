#include "fastParser.h"
#include <string>
#include <iostream>
#include <math.h>
#include <sys/stat.h>


void OperatorRead::InitKeyValues(int size)
{
	if (this->stored_info || this->valsize > 0)
	{
		delete[] stored_info;
	}
	stored_info = new keyval_t[size];
	valsize = size;
}

int OperatorRead::GetFileSize(char* filename)
{
	auto file = std::ifstream(filename);
	std::string str;
	char* alloc = new char[expected_filesize];
	if (file.good())
	{
		getline(file, str);
		strcpy(alloc, str.c_str());
	}
	while (file.good())
	{
		getline(file, str);
		sprintf(alloc, "%s\n%s", alloc, str.c_str());
	}
	int len = strlen(alloc);
	delete[]alloc;
	return len;
}
int OperatorRead::GetLineSize(char* filename)
{
	auto file = std::ifstream(filename);
	std::string str;
	char* alloc = new char[expected_filesize];
	int lines = 0;
	if (file.good())
	{
		getline(file, str);
		strcpy(alloc, str.c_str());
		lines++;
	}
	while (file.good())
	{
		getline(file, str);
		lines++;
	}
	delete[]alloc;
	return lines;
}

void OperatorRead::ReadFileInMemory(char* filename)
{
	auto file = std::ifstream(filename);
	std::string str;
	int size = GetFileSize(filename);
	char* alloc = new char[size];
	this->linecount = GetLineSize(filename);

	this->linevalues = new int[linecount + 1];

	int used_lines = 0;
	linevalues[0] = 0;
	if (file.good())
	{
		getline(file, str);
		strcpy(alloc, str.c_str());
	}
	while (file.good())
	{
		used_lines++;
		linevalues[used_lines] = strlen(alloc);
		getline(file, str);
		sprintf(alloc, "%s\n%s", alloc, str.c_str());
	}
	linevalues[used_lines + 1] = size;
	file_read_in_mem = alloc;
}

void OperatorRead::AddKeyValue(char* filter, DWORD value, KeyValType valtype)
{
	auto pointed = stored_info;




	strcpy(pointed[current_key_val].required, filter);

	pointed[current_key_val].value_to_change = (char*)value;
	pointed[current_key_val].type = valtype;


	this->current_key_val++;
}

void OperatorRead::InterpretAsInt(char* sbstr, int dependency_id)
{
	bool Negative = false;
	int len = strlen(sbstr);
	int k_val = 0;
	for (int i = 0; i < len; i++)
	{
		auto c = sbstr[i];
		if (c == '-')Negative = !Negative;
		if (c >= '0' && c <= '9')
		{
			k_val *= 10;
			k_val += c - '0';
		}
	}
	k_val *= (Negative) ? (-1) : (1);
	*((int*)((stored_info)[dependency_id].value_to_change)) = k_val;

}
void OperatorRead::InterpretAsBool(char* sbstr, int dependency_id)
{
	bool Negative = false;
	int len = strlen(sbstr);
	int k_val = 0;
	for (int i = 0; i < len; i++)
	{
		auto c = sbstr[i];
		if (c == '-')Negative = !Negative;
		if (c >= '0' && c <= '9')
		{
			k_val *= 10;
			k_val += c - '0';
		}
	}
	k_val *= (Negative) ? (-1) : (1);
	*((bool*)((stored_info)[dependency_id].value_to_change)) = k_val;

}


void OperatorRead::InterpretAsFloat(char* sbstr, int dependency_id)
{
	bool Negative = false;
	int len = strlen(sbstr);
	int bef_f = 0, aft_f = 0, floatingnums = 0;
	bool floating = false;
	for (int i = 0; i < len; i++)
	{
		auto c = sbstr[i];
		if (c == '-')Negative = !Negative;
		if (c == '.' || c == ',')floating = true;
		if (c >= '0' && c <= '9')
		{
			if (floating)
			{
				aft_f *= 10;
				aft_f += c - '0';
				floatingnums += 1;
			}
			else
			{
				bef_f *= 10;
				bef_f += c - '0';
			}
		}
	}
	float k_val = bef_f + aft_f / pow(10, floatingnums);
	k_val *= (Negative) ? (-1) : (1);
	*((float*)((stored_info)[dependency_id].value_to_change)) = k_val;

}

void OperatorRead::InterpretAsString(char* sbstr, int dependency_id)
{
	int len = strlen(sbstr);
	strncpy(stored_info[dependency_id].value_to_change, sbstr, len);
	stored_info[dependency_id].value_to_change[len] = '\0';
}

void OperatorRead::InterpretLines()
{
	for (int i = 0; i < linecount; i++)
		InterpretLine(i);
}

void OperatorRead::InterpretLineExact(int line, int dependency_id)
{

	int diff = linevalues[line + 1] - linevalues[line];



	char* currentline = new char[diff + 1];
	strcpy(currentline, "");
	strncpy(currentline, file_read_in_mem + linevalues[line], diff);
	currentline[diff] = '\0';
	auto comment = strstr(currentline, "//");
	if (comment)
	{
		diff = comment - currentline;
		delete[]currentline;
		currentline = new char[diff + 1];
		strcpy(currentline, "");
		strncpy(currentline, file_read_in_mem + linevalues[line], diff);
		currentline[diff] = '\0';

	}
	int i = dependency_id;
	{
		char* mask = new char[strlen((stored_info)[i].required) + 32];
		sprintf(mask, "%c%s%c", 36, (stored_info)[i].required, 36);

		auto found = strstr(currentline, mask);

		if (found)
		{
			auto len = strlen(mask);

			auto start_per = strstr(currentline + len + 3, "$");


			if (start_per)
			{
				auto end_per = strstr(start_per + 1, "$");
				if (end_per)
				{
					char value[256];
					strncpy(value, start_per + 1, end_per - start_per - 1);
					value[end_per - start_per - 1] = '\0';
					if (stored_info[i].type == T_INT)InterpretAsInt(value, i);
					else if (stored_info[i].type == T_FLOAT)InterpretAsFloat(value, i);
					else if (stored_info[i].type == T_CHARARRAY)InterpretAsString(value, i);
				}
			}
		}
		delete[]mask;
	}












	delete[]currentline;





	//delete[]currentline;
	//delete[]pad;
}

void OperatorRead::InterpretLine(int line)
{

	int diff = linevalues[line + 1] - linevalues[line];



	char* currentline = new char[diff + 1];
	strcpy(currentline, "");
	strncpy(currentline, file_read_in_mem + linevalues[line], diff);
	currentline[diff] = '\0';
	auto comment = strstr(currentline, "//");
	if (comment)
	{
		diff = comment - currentline;
		delete[]currentline;
		currentline = new char[diff + 1];
		strcpy(currentline, "");
		strncpy(currentline, file_read_in_mem + linevalues[line], diff);
		currentline[diff] = '\0';

	}
	for (int i = 0; i < current_key_val; i++)
	{
		char* mask = new char[strlen((stored_info)[i].required) + 32];
		sprintf(mask, "%c%s%c", 36, (stored_info)[i].required, 36);

		auto found = strstr(currentline, mask);

		if (found)
		{
			auto len = strlen(mask);

			auto start_per = strstr(currentline + len + 3, "$");


			if (start_per)
			{
				auto end_per = strstr(start_per + 1, "$");
				if (end_per)
				{
					char value[256];
					strncpy(value, start_per + 1, end_per - start_per - 1);
					value[end_per - start_per - 1] = '\0';
					if (stored_info[i].type == T_INT)InterpretAsInt(value, i);
					else if (stored_info[i].type == T_FLOAT)InterpretAsFloat(value, i);
					else if (stored_info[i].type == T_CHARARRAY)InterpretAsString(value, i);
					else if (stored_info[i].type == T_BOOL)InterpretAsBool(value, i);
					break;
				}
			}
		}
		delete[]mask;
	}












	delete[]currentline;





	//delete[]currentline;
	//delete[]pad;
}

void OperatorRead::WriteInit(char* filename)
{

	output.open(filename, std::fstream::app);
}

void OperatorRead::WritePre(char* text)
{
	output << text;
}
void OperatorRead::WriteKeyValue(int i)
{

	output << "  $";
	output << stored_info[i].required;
	output << "$  $";
	if (stored_info[i].type == T_INT)
	{
		output << *((int*)stored_info[i].value_to_change) << "$ ;\n";
	}
	else if (stored_info[i].type == T_BOOL)
	{
		output << *((bool*)stored_info[i].value_to_change) << "$ ;\n";
	}
	else 	if (stored_info[i].type == T_FLOAT)
	{
		output << *((float*)stored_info[i].value_to_change) << "$ ;\n";
	}
	else 	if (stored_info[i].type == T_CHARARRAY)
	{
		output << stored_info[i].value_to_change << "$ ;\n";
	}

}
void OperatorRead::WriteAllKeyValues()
{
	for (int i = 0; i < current_key_val; i++)
	{
		output << "  $";
		output << stored_info[i].required;
		output << "$  $";
		if (stored_info[i].type == T_INT)
		{
			output << *((int*)stored_info[i].value_to_change) << "$ ;\n";
		}
		else if (stored_info[i].type == T_BOOL)
		{
			output << *((bool*)stored_info[i].value_to_change) << "$ ;\n";
		}
		else 	if (stored_info[i].type == T_FLOAT)
		{
			output << *((float*)stored_info[i].value_to_change) << "$ ;\n";
		}
		else 	if (stored_info[i].type == T_CHARARRAY)
		{
			output << stored_info[i].value_to_change << "$ ;\n";
		}

	}
}

void OperatorRead::WriteClear(char* original_name)
{
	std::ofstream GStream;
	GStream.open(original_name);
	GStream << "";
	GStream.close();
	output.clear();
}

void OperatorRead::WriteClose()
{
	output.close();
}










void file_t::GetLineCount(char* location)
{
	auto file_b = std::ifstream(location, std::ios::binary);
	std::string c;
	lines = 0;
	while (file_b.good())
	{
		getline(file_b, c);
		lines++;
	}
	printf("Lines: %d\n", lines);
	size -= lines;
}

void file_t::GetAbsSize(char* location)
{
	auto file = std::ifstream(location, std::ios::binary);

	size = 0;
	/*
	char T;
	while (file.good())
	{
	file.read(&T, 1);
	size++;
	}
	*/
	struct stat st;
	stat(location, &st);
	//printf("Stat says : %d\n", st.st_size);
	size = st.st_size + 1;


}

void file_t::ReadInMemory(char* location)
{
	auto file = std::ifstream(location, std::ios::binary);
	//GetLineCount(location);
	GetAbsSize(location);

	loc_in_mem = new char[size+4];

	/*
	for(unsigned int i = 0; i < size; i++)
	{
	file.read(loc_in_mem+i, 1);
	}
	*/
	file.read(loc_in_mem, size);


	//file.read(loc_in_mem, size);

	//fopen()
	loc_in_mem[size] = '\0';


}


#include "DaiCastle.h"
void file_t::Dump(char* location, bool drawscr)
{
	auto of_ = std::ofstream(location, std::ios::binary);
	bool last_was_enter = false;
	bool current_enter = false;
	dc_clock clock;
	for (unsigned int i = 1; i <= size;)
	{/*
	 if (*(loc_in_mem + i - 1) == '\n')current_enter = true;
	 else current_enter = false;
	 if(!(last_was_enter && current_enter))
	 */
		int l = strlen(loc_in_mem + i - 1);
		if (l)
		{
			of_ << (loc_in_mem + i - 1);
			i += l;
		}
		else
		{
			of_ << *(loc_in_mem + i - 1);
			i++;
		}
		//last_was_enter = current_enter;

		//if (i% 1000 == 0 && clock.deltaTime() > 16)
		//{
		//	dc_mapeditor::DrawSaveScreen(location, (float(i) / size));
		//	clock.Update();
		//}

	}
	of_.close();
}