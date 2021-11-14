#include "DaiCastle.h"


dc_config g_Config;



/////////////////////////////////////////////
///Returns vector (x,y) where x is the index of the first character of the 'word'th word in 'inputtext'
/// and y is the length of that word
/////////////////////////////////////////////
sf::Vector2i TrimString(char* inputtext, int word)
{
	int WordsFound = 0;
	int LastSpace = 0;
	int len = strlen(inputtext);
	for (int i = 0; i < len; i++)
	{
		if (i != 0 && inputtext[i] == ' ' && inputtext[i - 1] != ' ')
		{
			WordsFound++;
			if (WordsFound == word)
			{
				return{ LastSpace,i - LastSpace };

			}
		}
		if (i == strlen(inputtext) - 1 && WordsFound == word - 1)
		{
			return{ LastSpace,i - LastSpace + 1 };
		}
		if (inputtext[i] == ' ')LastSpace = i + 1;
	}

	return sf::Vector2i(-1, -1);
}
/////////////////////////////////////////////
///Returns if the first 'len' characters of 'text' represents a number
/////////////////////////////////////////////
bool IsANumber(char* text, int len)
{
	int DotCount = 0;
	int MinusCount = 0;

	bool Good = true;

	for (int i = 0; i < len; i++)
	{
		if (text[i] == '.')DotCount++;
		else if (text[i] == '-')MinusCount++;
		else if (text[i] >= '0' && text[i] <= '9');
		else Good = false;
	}

	return Good && DotCount <= 1 && MinusCount <= 1;
}

/////////////////////////////////////////////
///Converts the first 'len' characters of 'text' to a floating point number
/////////////////////////////////////////////
float TextToFloat(char* text, int len)
{
	int High = 0;
	int Low = 0;
	int LowDivisor = 0;
	bool Decimal = false;
	bool Negative = false;

	for (int i = 0; i < len; i++)
	{
		if (i == 0 && text[0] == '-')
		{
			Negative = true;
		}
		else if (text[i] == '.')Decimal = true;
		else if (!Decimal)
		{
			High = 10 * High + (text[i] - ('0'));
		}
		else if (Decimal)
		{
			Low = 10 * Low + (text[i] - ('0'));
			LowDivisor++;
		}
	}

	if (Negative)return -(1.f*High + pow(0.1f, LowDivisor)*Low);
	else return (1.f*High + pow(0.1f, LowDivisor)*Low);
}
/////////////////////////////////////////////
///Converts the first 'len' characters of 'text' to an integer
/////////////////////////////////////////////
int TextToInt(char* text, int len)
{
	int High = 0;

	bool Negative = false;

	for (int i = 0; i < len; i++)
	{
		if (i == 0 && text[0] == '-')
		{
			Negative = true;
		}

			High = 10 * High + (text[i] - ('0'));


	}

	if (Negative) return -High;
	else return High;
}


dc_convar* dc_config::GetConVar(int index)
{
	auto pointer = (dc_convar*)this + index;
	return pointer;
}

sf::Vector2i dc_config::EditCVar(char* inputtext)
{

	auto Trim1 = TrimString(inputtext, 1);

	if (Trim1.x == -1)
		return{ -1,0 };


	for (int i = 0; i < sizeof(dc_config) / sizeof(dc_convar); i++)
	{
		auto pointer = (dc_convar*)(this) + i; // + i * sizeof(dc_convar);

		if (strlen(pointer->CommandName) == Trim1.y && !strncmp(pointer->CommandName, inputtext + Trim1.x, Trim1.y))
		{
			auto Trim2 = TrimString(inputtext, 2);

			if (Trim2.x == -1)
				return{ i,0 };


			if (pointer->Cheat && g_Config.gm_cheats.Value < 1)return{ i,2 };

			if (IsANumber(inputtext + Trim2.x, Trim2.y))
			{
				float n = TextToFloat(inputtext + Trim2.x, Trim2.y);
				pointer->Value = n;

				if (pointer->Execute)pointer->Execute();

				return{ i,1 };
			}

		}
	}
	return{ -1,0 };
}



void dc_game::DrawConsole()
{

	static dc_clock Clock;
	static bool vertline = false;
	if (Clock.deltaTime() > 500)
	{
		vertline = !vertline;
		Clock.Update();
	}


	_Window::RenderOverlay(0, 0, g_Resolution.x, g_Resolution.y, 0, 0, 0, 64);
	_Window::RenderOverlay(0, 0, g_Resolution.x, g_Resolution.y*0.45f, 0, 0, 32, 192);
	_Window::RenderOverlay(0, g_Resolution.y*0.40f, g_Resolution.x, g_Resolution.y*0.05f, 0, 0, 96, 192);
	_Window::RenderOverlay(0, g_Resolution.y*0.45f, g_Resolution.x, g_Resolution.y*0.005f, 0, 0, 192, 255);
	ConLog(".");
	for (int i = console_pos; i < console_pos + 15 && i < ConsoleLogs.size(); i++)
	{
		int RelativePos = i-console_pos;
		int msgPos = ConsoleLogs.size() - 1 - i;
		_Window::RenderTextB(0.005f*g_Resolution.x, g_Resolution.y*(0.40f - (1+RelativePos)*0.0267f), ConsoleLogs[msgPos]->msg, 16, ConsoleLogs[msgPos]->Color.r, ConsoleLogs[msgPos]->Color.g, ConsoleLogs[msgPos]->Color.b, ConsoleLogs[msgPos]->Color.a);
	}

	char Buffer[140];
	if (vertline)
		sprintf(Buffer, "> %s|", ConsoleMessage);
	else
		sprintf(Buffer, "> %s", ConsoleMessage);
	_Window::RenderTextB(0.01f*g_Resolution.x, g_Resolution.y*(0.41f), Buffer, 23, 192,192,192,255);



	int consize = max((15), ((int)ConsoleLogs.size()));
	
	_Window::RenderOverlay(g_Resolution.x*0.9875f, g_Resolution.y*0.005f, g_Resolution.x*0.005f, g_Resolution.y*0.39f, 32, 32, 128, 255);
	
	int slidepos = g_Resolution.y*0.39f;
	int spush = (((float)console_pos) / consize)*0.385f*g_Resolution.y;
	slidepos -= spush;
	int slidesize = max(g_Resolution.y*0.385f*(15.f / consize),g_Resolution.y*0.01f);


	//printf("\nSlide | Pos: %d | Size: %d , valami: %d | ConSize: %d Pos: %d", slidepos, slidesize, spush, consize, console_pos);

	_Window::RenderOverlay(g_Resolution.x*0.985f, slidepos-slidesize, g_Resolution.x*0.01f, slidesize, 32, 32, 192, 255);
}

void dc_game::ScrollConsole()
{
	console_pos += g_Mouse.scroll;
	if (console_pos > (int)ConsoleLogs.size() - 15)console_pos = ConsoleLogs.size() - 15;
	if (console_pos < 0)console_pos = 0;

}

int CompareTrimmedMessage(char* Command, sf::Vector2i Trim, char* Sub)
{
	//printf("\nCTM Input: Command: %s | Sub: %s | Trim: %d %d", Command, Sub, Trim.x, Trim.y);
	if (strlen(Sub) != Trim.y)return 1;
	return strncmp(Command + Trim.x, Sub, Trim.y);
}

/////////////////////////////////////////////
///Returns a vector of (x,y) where x is a start of a word, y is the length of the same word
///This vector 'contains' all the words from 'text' 
/////////////////////////////////////////////
std::vector<sf::Vector2i> TrimStringFully(char* text)
{
	char* subText = text;

	std::vector<sf::Vector2i> Trims;

	int Wasted = 0;

	while (strlen(subText) != 0)
	{
		auto Trim = TrimString(subText, 1);
		if (Trim.x != -1)
		{

			int wa = Wasted + Trim.x+Trim.y;
			Trim.x += Wasted;
			Wasted = wa;
			subText = text+Wasted;
			Trims.push_back(Trim);
		}
		else break;
	}
	
	for (int i = Trims.size() - 1; i >= 0; i--)
	{
		if (Trims[i].y <= 0)Trims.erase(Trims.begin() + i);
		else if (Trims[i].y >= 1)
		{
			bool deletion = true;
			while (text[Trims[i].x] == ' ')
			{
				Trims[i].x++;
				Trims[i].y--;
				if (Trims[i].y == 0)
				{break;
				}
			}
			while (text[Trims[i].x + Trims[i].y - 1] == ' ')
			{
				Trims[i].y--;
				if (Trims[i].y == 0)break;
			}

			if (Trims[i].y != 0)deletion = false;
			if(deletion)Trims.erase(Trims.begin() + i);
		}
	}



	return Trims;
}

#define CTM CompareTrimmedMessage

std::vector<char*> dc_game::GetAllNonCvarCommands()
{
	std::vector<char*> Return = { "player","clear","echo","camera","spawn","time","dps","commands","convars","find","bind","unbind","exec","quit","quit_prompt","record","stoprecord","layer","bot" };
	return Return;
}

std::vector<char*> dc_game::GetAllConvars()
{
	std::vector<char*> Return;
	for (int i = 0; i < sizeof(dc_config) / sizeof(dc_convar); i++)
	{
		auto pointer = (dc_convar*)(&g_Config) + i; 
		char* New = new char[strlen(pointer->CommandName) + 4];
		sprintf(New, pointer->CommandName);
		Return.push_back(New);
	}

	return Return;
}


void dc_game::ConsoleExecuteCommand(char* cm)
{
	printf("\nCommand: '%s'", cm);
	auto Value = g_Config.EditCVar(cm);
	auto Trim = TrimString(cm, 1);


	if (Trim.x == -1)
	{
		//LogError("Woaw! What's that? Eugh!");
		return;
	}

	if (Value.x != -1)
	{
		auto ptr = g_Config.GetConVar(Value.x);
		if (Value.y == 0)LogMessage("|  \"%s\" is %f", sf::Color(225,180,32), ptr->CommandName, ptr->Value);
		else if (Value.y == 1)LogMessage("|  \"%s\" is set to %f", sf::Color(225, 180, 32), ptr->CommandName, ptr->Value);
		else if (Value.y == 2)LogMessage("|  \"%s\" is a cheat. Set \"gm_cheats\" to 1 to use it", sf::Color(225, 180, 32), ptr->CommandName, ptr->Value);
	}
	else if (!CTM(cm, Trim, "player") && cmdPlayer(cm));
	else if (!CTM(cm, Trim, "clear") && cmdClear(cm));
	else if (!CTM(cm, Trim, "echo") && cmdEcho(cm,Trim));
	else if (!CTM(cm, Trim, "camera") && cmdCamera(cm));
	else if (!CTM(cm, Trim, "spawn") && cmdSpawn(cm));
	else if (!CTM(cm, Trim, "time") && cmdTime(cm));
	else if (!CTM(cm, Trim, "dps") && cmdDPS(cm));
	else if (!CTM(cm, Trim, "commands") && cmdCommands(cm));
	else if (!CTM(cm, Trim, "convars") && cmdConvars(cm));
	else if (!CTM(cm, Trim, "find") && cmdFind(cm));
	else if (!CTM(cm, Trim, "bind") && cmdBind(cm));
	else if (!CTM(cm, Trim, "unbind") && cmdUnbind(cm));
	else if (!CTM(cm, Trim, "exec") && cmdExec(cm));
	else if (!CTM(cm, Trim, "quit_prompt"))OW_STATUS = 5;
	else if (!CTM(cm, Trim, "quit"))Quit();
	else if (!CTM(cm, Trim, "record"))
	{
		if (DViewer)DViewer->Recording = true;
		else LogError("|  Could not start recording out of a demo");
	}
	else if (!CTM(cm, Trim, "stoprecord"))
	{
		if (DViewer) {
			DViewer->Recording = false;
			DViewer->Frame = 0;
			DViewer->Takes++;
		}
		else LogError("|  Could not stop recording out of a demo");
	}
	else if (!CTM(cm, Trim, "layer") && cmdLayer(cm));
	else if (!CTM(cm, Trim, "bot") && cmdBot(cm));
	else LogError("|  Could not execute command \"%s\"", cm);
}

std::vector<char*> dc_game::GetAllKeyNames()
{
	static bool bRun = false;
	static char* KeyNames[256];


	if (!bRun)
	{
		bRun = true;



		KeyNames[1] = "MOUSE1";
		KeyNames[2] = "MOUSE2";
		KeyNames[4] = "MOUSE3";
		KeyNames[8] = "BACKSPACE";
		KeyNames[9] = "TAB";
		KeyNames[0x0D] = "ENTER";
		KeyNames[0x10] = "SHIFT";
		KeyNames[0x11] = "CTRL";
		KeyNames[0x12] = "ALT";
		KeyNames[0x14] = "CAPS_LOCK";
		KeyNames[0x1B] = "ESC";
		KeyNames[0x20] = "SPACE";
		KeyNames[0x21] = "PG_UP";
		KeyNames[0x22] = "PG_DOWN";
		KeyNames[0x23] = "END";
		KeyNames[0x24] = "HOME";
		KeyNames[0x25] = "LEFT_ARROW";
		KeyNames[0x26] = "UP_ARROW";
		KeyNames[0x27] = "RIGHT_ARROW";
		KeyNames[0x28] = "DOWN_ARROW";
		KeyNames[0x2D] = "INSERT";
		KeyNames[0x2E] = "DEL";
		for (int i = 0; i < 10; i++) {
			KeyNames[0x30 + i] = new char[4];
			sprintf(KeyNames[0x30 + i], "%c\0", '0' + i);
		}
		for (int i = 0x41; i <= 0x5A; i++)
		{
			KeyNames[i] = new char[4];
			sprintf(KeyNames[i], "%c\0", 'A' + i - 0x41);
		}
		for (int i = 0; i < 10; i++) {
			KeyNames[0x60 + i] = new char[8];
			sprintf(KeyNames[0x60 + i], "NUM_%c\0", '0' + i);
		}
		KeyNames[0x6A] = "NUM_MULT";
		KeyNames[0x6B] = "NUM_PLUS";
		KeyNames[0x6D] = "NUM_MINUS";
		KeyNames[0x6E] = "NUM_DOT";
		KeyNames[0x6F] = "NUM_PER";

		for (int i = 0; i < 24; i++)
		{
			KeyNames[0x70 + i] = new char[8];
			sprintf(KeyNames[0x70 + i], "F%d\0", i);
		}
		KeyNames[0x90] = "NUMLOCK";
		KeyNames[0x91] = "SCRLOCK";
		KeyNames[0xA0] = "LSHIFT";
		KeyNames[0xA1] = "RSHIFT";
		KeyNames[0xA2] = "LCTRL";
		KeyNames[0xA3] = "RCTRL";
		KeyNames[0xA4] = "LALT";
		KeyNames[0xA5] = "RALT";


		for (int i = 0; i < 256; i++)if (KeyNames[i] == nullptr)KeyNames[i] = "undef";


	}
	std::vector<char*> Ret;
	for (int i = 0; i < 256; i++)Ret.push_back(KeyNames[i]);
	
	return Ret;
}

std::vector<char*> dc_game::GetAllActNames()
{
	//return{ "shoot","up","down","right","left","reload","slot1","slot2","slot3","slot4","slot5","drop","openinv","openmap","placemarker","removemarker","conopen","jumpoff","descend","alter","closemenu","swapplayer","conenter" };

	return { "shoot","up","down","right","left","reload","slot1","slot2","slot3","slot4","slot5","drop","openinv","openmap","placemarker","removemarker","conopen","jumpoff","descend","alter","closemenu","swapplayer","conenter","none","none2","none3","none4","none5","none6","none7","none8","none9","none10"};

}

bool dc_game::cmdBot(char* cm)
{
	if (!Match) {
		LogError("|  You can only use 'bot' commands while in a match");
		return false;
	}
	auto Trims = TrimStringFully(cm);

	if (Trims.size() <= 1)
	{
		LogMessage("|  bot difficulties", sf::Color(225, 180, 32));
		LogMessage("|  bot difficulties_alive", sf::Color(225, 180, 32));
		return true;
	}
	else
	{
		if (!CTM(cm, Trims[1], "difficulties"))
		{
			std::vector<int> Difficulty[4];



			for (int i = 1; i < 100; i++)
			{
				for(int j = 0; j < 4; j++)
					if (Match->BotData[i].botDifficulty == j)Difficulty[j].push_back(i);

			}

			char Buffer[128];
			char* Texts[4] = { "Easy","Normal","Hard","Expert" };
			for (int i = 0; i < 4; i++)
			{
				sprintf(Buffer, "|  %s:",Texts[i]);
				for (int j = 0; j < Difficulty[i].size(); j++)
				{
					sprintf(Buffer, "%s %d", Buffer, (Difficulty[i])[j]);
					if (j % 32 == 31)
					{
						LogMessage(Buffer, sf::Color(225, 180, 32));
						sprintf(Buffer, "|  %s:", Texts[i]);
					}
				}
				if (Difficulty[i].size() % 32 != 31)
					LogMessage(Buffer, sf::Color(225, 180, 32));
			}
			return true;
		}
		else if (!CTM(cm, Trims[1], "difficulties_alive"))
		{
			std::vector<int> Difficulty[4];



			for (int i = 1; i < 100; i++)
			{
				for (int j = 0; j < 4; j++)
					if (Match->BotData[i].botDifficulty == j && Match->players[i].iHealth > 0)Difficulty[j].push_back(i);

			}

			char Buffer[128];
			char* Texts[4] = { "Easy","Normal","Hard","Expert" };
			for (int i = 0; i < 4; i++)
			{
				sprintf(Buffer, "|  %s:", Texts[i]);
				for (int j = 0; j < Difficulty[i].size(); j++)
				{
					sprintf(Buffer, "%s %d", Buffer, (Difficulty[i])[j]);
					if (j % 32 == 31)
					{
						LogMessage(Buffer, sf::Color(225, 180, 32));
						sprintf(Buffer, "|  %s:", Texts[i]);
					}
				}
				if(Difficulty[i].size() %32 != 31)
					LogMessage(Buffer, sf::Color(225, 180, 32));
			}
			return true;
		}

	}
	return false;
}

bool dc_game::cmdLayer(char* cm)
{
	if (!DViewer) {
		LogError("|  You can only edit layers while watching a replay");
		return false;
	}

	auto Trims = TrimStringFully(cm);
	if (Trims.size() <= 1)
	{
		LogMessage("|  layer add #name", sf::Color(225, 180, 32));
		LogMessage("|  layer all", sf::Color(225, 180, 32));
		LogMessage("|  layer #name map 0|1", sf::Color(225, 180, 32));
		LogMessage("|  layer #name chests 0|1", sf::Color(225, 180, 32));
		LogMessage("|  layer #name shadows 0|1", sf::Color(225, 180, 32));
		LogMessage("|  layer #name items 0|1", sf::Color(225, 180, 32));
		LogMessage("|  layer #name players 0|1", sf::Color(225, 180, 32));
		LogMessage("|  layer #name shots 0|1", sf::Color(225, 180, 32));
		LogMessage("|  layer #name exps 0|1", sf::Color(225, 180, 32));
		LogMessage("|  layer #name effects 0|1", sf::Color(225, 180, 32));
		LogMessage("|  layer #name storm 0|1", sf::Color(225, 180, 32));
		LogMessage("|  layer #name render 0|1", sf::Color(225, 180, 32));
		LogMessage("|  layer #name save 0|1", sf::Color(225, 180, 32));
		LogMessage("|  layer #name color #r #g #b", sf::Color(225, 180, 32));
		LogMessage("|  layer #name remove", sf::Color(225, 180, 32));
	}
	if (Trims.size() >= 2)
	{
		if (!CTM(cm, Trims[1], "all"))
		{
			for (int i = 0; i < DViewer->RenderingLayers.size(); i++)
			{
				auto& RL = DViewer->RenderingLayers[i];
					LogMessage("|  Layer '%s'",sf::Color(225,180,32),RL.Name);
			}
			return true;
		}
	}
	if (Trims.size() >= 3)
	{
		if (!CTM(cm, Trims[1], "add"))
		{
			for (int i = 0; i < DViewer->RenderingLayers.size(); i++)
			{
				auto& RL = DViewer->RenderingLayers[i];
				if (!CTM(cm, Trims[2], RL.Name))
				{
					LogError("|  There exists a layer with name '%s'", RL.Name);
					return false;
				}
			}
			dc_demo_renderlayer RL;
			sprintf(RL.Name, "%.*s", min(31, Trims[2].y), cm + Trims[2].x);
			LogMessage("|  Layer '%s' was added",sf::Color(225,180,32), RL.Name);
			DViewer->RenderingLayers.push_back(RL);
			return true;
		}
		for (int i = 0; i < DViewer->RenderingLayers.size(); i++)
		{
			auto& RL = DViewer->RenderingLayers[i];
			if (!CTM(cm, Trims[1], RL.Name))
			{
				if (Trims.size() >= 3)
				{
					if (!CTM(cm, Trims[2], "remove"))
					{
						LogMessage("|  Layer '%s' was removed", sf::Color(225, 180, 32), RL.Name);
						DViewer->RenderingLayers.erase(DViewer->RenderingLayers.begin() + i);
						return true;
					}
					if (Trims.size() >= 4)
					{
						if (!CTM(cm, Trims[2], "map"))
						{
							if (IsANumber(cm + Trims[3].x, Trims[3].y))
							{
								int V = TextToInt(cm + Trims[3].x, Trims[3].y);
								DViewer->RenderingLayers[i].AllowMap = V;
								LogMessage("|  Layer '%s' has map set to %d", sf::Color(225, 180, 32), RL.Name, V);
								return true;
							}
						}
						if (!CTM(cm, Trims[2], "chests"))
						{
							if (IsANumber(cm + Trims[3].x, Trims[3].y))
							{
								int V = TextToInt(cm + Trims[3].x, Trims[3].y);
								DViewer->RenderingLayers[i].AllowChests = V;
								LogMessage("|  Layer '%s' has chests set to %d", sf::Color(225, 180, 32), RL.Name, V);
								return true;
							}
						}
						if (!CTM(cm, Trims[2], "shadows"))
						{
							if (IsANumber(cm + Trims[3].x, Trims[3].y))
							{
								int V = TextToInt(cm + Trims[3].x, Trims[3].y);
								DViewer->RenderingLayers[i].AllowShadows = V;
								LogMessage("|  Layer '%s' has shadows set to %d", sf::Color(225, 180, 32), RL.Name, V);
								return true;
							}
						}
						if (!CTM(cm, Trims[2], "items"))
						{
							if (IsANumber(cm + Trims[3].x, Trims[3].y))
							{
								int V = TextToInt(cm + Trims[3].x, Trims[3].y);
								DViewer->RenderingLayers[i].AllowItems = V;
								LogMessage("|  Layer '%s' has items set to %d", sf::Color(225, 180, 32), RL.Name, V);
								return true;
							}
						}
						if (!CTM(cm, Trims[2], "players"))
						{
							if (IsANumber(cm + Trims[3].x, Trims[3].y))
							{
								int V = TextToInt(cm + Trims[3].x, Trims[3].y);
								DViewer->RenderingLayers[i].AllowPlayers = V;
								LogMessage("|  Layer '%s' has players set to %d", sf::Color(225, 180, 32), RL.Name, V);
								return true;
							}
						}
						if (!CTM(cm, Trims[2], "shots"))
						{
							if (IsANumber(cm + Trims[3].x, Trims[3].y))
							{
								int V = TextToInt(cm + Trims[3].x, Trims[3].y);
								DViewer->RenderingLayers[i].AllowShootEffects = V;
								LogMessage("|  Layer '%s' has shots set to %d", sf::Color(225, 180, 32), RL.Name, V);
								return true;
							}
						}
						if (!CTM(cm, Trims[2], "exps"))
						{
							if (IsANumber(cm + Trims[3].x, Trims[3].y))
							{
								int V = TextToInt(cm + Trims[3].x, Trims[3].y);
								DViewer->RenderingLayers[i].AllowExplosives = V;
								LogMessage("|  Layer '%s' has exps set to %d", sf::Color(225, 180, 32), RL.Name, V);
								return true;
							}
						}
						if (!CTM(cm, Trims[2], "effects"))
						{
							if (IsANumber(cm + Trims[3].x, Trims[3].y))
							{
								int V = TextToInt(cm + Trims[3].x, Trims[3].y);
								DViewer->RenderingLayers[i].AllowDamageEffects = V;
								LogMessage("|  Layer '%s' has effects set to %d", sf::Color(225, 180, 32), RL.Name, V);
								return true;
							}
						}
						if (!CTM(cm, Trims[2], "storm"))
						{
							if (IsANumber(cm + Trims[3].x, Trims[3].y))
							{
								int V = TextToInt(cm + Trims[3].x, Trims[3].y);
								DViewer->RenderingLayers[i].AllowStorm = V;
								LogMessage("|  Layer '%s' has storm set to %d", sf::Color(225, 180, 32), RL.Name, V);
								return true;
							}
						}
						if (!CTM(cm, Trims[2], "render"))
						{
							if (IsANumber(cm + Trims[3].x, Trims[3].y))
							{
								int V = TextToInt(cm + Trims[3].x, Trims[3].y);
								DViewer->RenderingLayers[i].Should_Render = V;
								LogMessage("|  Layer '%s' has render set to %d", sf::Color(225, 180, 32), RL.Name, V);
								return true;
							}
						}
						if (!CTM(cm, Trims[2], "save"))
						{
							if (IsANumber(cm + Trims[3].x, Trims[3].y))
							{
								int V = TextToInt(cm + Trims[3].x, Trims[3].y);
								DViewer->RenderingLayers[i].Should_Export = V;
								LogMessage("|  Layer '%s' has save set to %d", sf::Color(225, 180, 32), RL.Name, V);
								return true;
							}
						}
						if (Trims.size() >= 6)
						{
							if (!CTM(cm, Trims[2], "color"))
							{
								int R = -1, G = -1, B = -1;

								if (IsANumber(cm + Trims[3].x, Trims[3].y))
									R = TextToInt(cm + Trims[3].x, Trims[3].y);
								if (IsANumber(cm + Trims[4].x, Trims[4].y))
									G = TextToInt(cm + Trims[4].x, Trims[4].y);
								if (IsANumber(cm + Trims[5].x, Trims[5].y))
									B = TextToInt(cm + Trims[5].x, Trims[5].y);

								if (R < 0 || G < 0 || B < 0 || R > 255 || G > 255 || B > 255)
									LogError("|  Invalid Color: %d %d %d", R, G, B);
								else
								{
									DViewer->RenderingLayers[i].BackgroundColor = sf::Color(R, G, B);
									LogMessage("|  Layer '%s' has color set to (%d,%d,%d)", sf::Color(225, 180, 32), RL.Name, R,G,B);
									return true;
								}
							}
						}


					}
				}
			}
		}
	}


	return false;
}

bool dc_game::cmdExec(char* cm)
{
	auto Trims = TrimStringFully(cm);
	if (Trims.size() <= 1)
	{
		LogMessage("|  Usage: exec config.cfg", sf::Color(225, 180, 32));
		LogMessage("|  Note: cfg files must be in cfg/ folder", sf::Color(225, 180, 32));
		return true;
	}
	else
	{
		auto Name = new char[Trims[1].y + 12];
		sprintf(Name, "cfg\\%.*s", Trims[1].y, cm + Trims[1].x);
		auto res = LoadConfig(Name);
		if (res)
		{
			LogMessage("|  %s was successfully loaded", sf::Color(225,180,32), Name);
			delete[] Name;
			return true;
		}
		else {
			LogError("|  %s couldn't be found", Name);
			delete[] Name;
			return false;
		}
	}
}


bool dc_game::cmdUnbind(char* cm)
{
	static bool bRun = false;
	static char* KeyNames[256];
	static char* ActNames[] = { "shoot","up","down","right","left","reload","slot1","slot2","slot3","slot4","slot5","drop","openinv","openmap","placemarker","removemarker","conopen","jumpoff","descend","alter","closemenu","swapplayer","conenter" };


	if (!bRun)
	{
		bRun = true;



		KeyNames[1] = "MOUSE1";
		KeyNames[2] = "MOUSE2";
		KeyNames[4] = "MOUSE3";
		KeyNames[8] = "BACKSPACE";
		KeyNames[9] = "TAB";
		KeyNames[0x0D] = "ENTER";
		KeyNames[0x10] = "SHIFT";
		KeyNames[0x11] = "CTRL";
		KeyNames[0x12] = "ALT";
		KeyNames[0x14] = "CAPS_LOCK";
		KeyNames[0x1B] = "ESC";
		KeyNames[0x20] = "SPACE";
		KeyNames[0x21] = "PG_UP";
		KeyNames[0x22] = "PG_DOWN";
		KeyNames[0x23] = "END";
		KeyNames[0x24] = "HOME";
		KeyNames[0x25] = "LEFT_ARROW";
		KeyNames[0x26] = "UP_ARROW";
		KeyNames[0x27] = "RIGHT_ARROW";
		KeyNames[0x28] = "DOWN_ARROW";
		KeyNames[0x2D] = "INSERT";
		KeyNames[0x2E] = "DEL";
		for (int i = 0; i < 10; i++) {
			KeyNames[0x30 + i] = new char[4];
			sprintf(KeyNames[0x30 + i], "%c\0", '0' + i);
		}
		for (int i = 0x41; i <= 0x5A; i++)
		{
			KeyNames[i] = new char[4];
			sprintf(KeyNames[i], "%c\0", 'A' + i - 0x41);
		}
		for (int i = 0; i < 10; i++) {
			KeyNames[0x60 + i] = new char[8];
			sprintf(KeyNames[0x60 + i], "NUM_%c\0", '0' + i);
		}
		KeyNames[0x6A] = "NUM_MULT";
		KeyNames[0x6B] = "NUM_PLUS";
		KeyNames[0x6D] = "NUM_MINUS";
		KeyNames[0x6E] = "NUM_DOT";
		KeyNames[0x6F] = "NUM_PER";

		for (int i = 0; i < 24; i++)
		{
			KeyNames[0x70 + i] = new char[8];
			sprintf(KeyNames[0x70 + i], "F%d\0", i);
		}
		KeyNames[0x90] = "NUMLOCK";
		KeyNames[0x91] = "SCRLOCK";
		KeyNames[0xA0] = "LSHIFT";
		KeyNames[0xA1] = "RSHIFT";
		KeyNames[0xA2] = "LCTRL";
		KeyNames[0xA3] = "RCTRL";
		KeyNames[0xA4] = "LALT";
		KeyNames[0xA5] = "RALT";


		for (int i = 0; i < 256; i++)if (KeyNames[i] == nullptr)KeyNames[i] = "undef";


	}

	auto Trims = TrimStringFully(cm);
	if (Trims.size() <= 1)
	{
		LogMessage("|  Usage: unbind #button #cmd", sf::Color(225, 180, 32));
		LogMessage("|  unbind keylist - keynames", sf::Color(225, 180, 32));
		LogMessage("|  unbind cmdlist - action names", sf::Color(225, 180, 32));
		LogMessage("|  Usage: unbind all", sf::Color(225, 180, 32));
		return true;
	}
	else
	{
		int KeyID = -1;
		for (int i = 0; i < 256; i++) {
			if (!strstr(KeyNames[i], "undef") && !CTM(cm, Trims[1], KeyNames[i]))
				KeyID = i;
		}
		if (!CTM(cm, Trims[1], "keylist"))
		{
			for (int i = 0; i < 256; i++)
				if (!strstr(KeyNames[i], "undef"))LogMessage("|  %s", sf::Color(225, 180, 32), KeyNames[i]);
			return true;
		}
		else if (!CTM(cm, Trims[1], "cmdlist"))
		{
			for (int i = 0; i < 23; i++)
				if (!strstr(ActNames[i], "undef"))LogMessage("|  %s", sf::Color(225, 180, 32), ActNames[i]);
			return true;
		}
		else if (!CTM(cm, Trims[1], "all"))
		{
			for (int i = 0; i < 32; i++)
			{
				Binds.KeysPrimary[i] = 0;
				Binds.KeysSecondary[i] = 0;
			}
			return true;
		}
		else if (KeyID != -1)
		{
			if (Trims.size() == 2)
			{
				LogMessage("|  '%s' has been unbound", sf::Color(225, 180, 32), KeyNames[KeyID]);
				for (int i = 0; i < 23; i++)
				{
					if (Binds.KeysPrimary[i] == KeyID)Binds.KeysPrimary[i] = 0;
					if (Binds.KeysSecondary[i] == KeyID)Binds.KeysSecondary[i] = 0;
				}
				return true;
			}
			else
			{
				int ActID = -1;
				for (int i = 0; i < 23; i++) {
					if (!strstr(ActNames[i], "undef") && !CTM(cm, Trims[2], ActNames[i]))
						ActID = i;
				}
				if (ActID != -1)
				{



					if (Binds.KeysPrimary[ActID] == KeyID)
					{
						Binds.KeysPrimary[ActID] = 0;
						LogMessage("|  '%s' has been unbound", sf::Color(225, 180, 32), KeyNames[KeyID]);
					}
					if (Binds.KeysSecondary[ActID] == KeyID)
					{
						Binds.KeysSecondary[ActID] = 0;
						LogMessage("|  '%s' has been unbound", sf::Color(225, 180, 32), KeyNames[KeyID]);
					}
					return true;
				}
				else
				{
					LogError("|  '%.*s' is not an action", Trims[2].y, cm + Trims[2].x);
				}
			}
		}
		else
		{
			LogError("|  '%.*s' is not a key", Trims[1].y, cm + Trims[1].x);
		}

	}
	return false;
}

bool dc_game::cmdBind(char* cm)
{
	static bool bRun = false;
	static char* KeyNames[256];
	static char* ActNames[] = { "shoot","up","down","right","left","reload","slot1","slot2","slot3","slot4","slot5","drop","openinv","openmap","placemarker","removemarker","conopen","jumpoff","descend","alter","closemenu","swapplayer","conenter" };


	if (!bRun)
	{
		bRun = true;



		KeyNames[1] = "MOUSE1";
		KeyNames[2] = "MOUSE2";
		KeyNames[4] = "MOUSE3";
		KeyNames[8] = "BACKSPACE";
		KeyNames[9] = "TAB";
		KeyNames[0x0D] = "ENTER";
		KeyNames[0x10] = "SHIFT";
		KeyNames[0x11] = "CTRL";
		KeyNames[0x12] = "ALT";
		KeyNames[0x14] = "CAPS_LOCK";
		KeyNames[0x1B] = "ESC";
		KeyNames[0x20] = "SPACE";
		KeyNames[0x21] = "PG_UP";
		KeyNames[0x22] = "PG_DOWN";
		KeyNames[0x23] = "END";
		KeyNames[0x24] = "HOME";
		KeyNames[0x25] = "LEFT_ARROW";
		KeyNames[0x26] = "UP_ARROW";
		KeyNames[0x27] = "RIGHT_ARROW";
		KeyNames[0x28] = "DOWN_ARROW";
		KeyNames[0x2D] = "INSERT";
		KeyNames[0x2E] = "DEL";
		for (int i = 0; i < 10; i++) {
			KeyNames[0x30 + i] = new char[4];
			sprintf(KeyNames[0x30 + i], "%c\0", '0' + i);
		}
		for (int i = 0x41; i <= 0x5A; i++)
		{
			KeyNames[i] = new char[4];
			sprintf(KeyNames[i], "%c\0", 'A' + i - 0x41);
		}
		for (int i = 0; i < 10; i++) {
			KeyNames[0x60 + i] = new char[8];
			sprintf(KeyNames[0x60 + i], "NUM_%c\0", '0' + i);
		}
		KeyNames[0x6A] = "NUM_MULT";
		KeyNames[0x6B] = "NUM_PLUS";
		KeyNames[0x6D] = "NUM_MINUS";
		KeyNames[0x6E] = "NUM_DOT";
		KeyNames[0x6F] = "NUM_PER";

		for (int i = 0; i < 24; i++)
		{
			KeyNames[0x70 + i] = new char[8];
			sprintf(KeyNames[0x70 + i], "F%d\0", i);
		}
		KeyNames[0x90] = "NUMLOCK";
		KeyNames[0x91] = "SCRLOCK";
		KeyNames[0xA0] = "LSHIFT";
		KeyNames[0xA1] = "RSHIFT";
		KeyNames[0xA2] = "LCTRL";
		KeyNames[0xA3] = "RCTRL";
		KeyNames[0xA4] = "LALT";
		KeyNames[0xA5] = "RALT";


		for (int i = 0; i < 256; i++)if (KeyNames[i] == nullptr)KeyNames[i] = "undef";


	}

	auto Trims = TrimStringFully(cm);
	if (Trims.size() <= 1)
	{
		LogMessage("|  Usage: bind #button #cmd", sf::Color(225, 180, 32));
		LogMessage("|  bind keylist - keynames", sf::Color(225, 180, 32));
		LogMessage("|  bind cmdlist - action names", sf::Color(225, 180, 32));
		return true;
	}
	else
	{
		int KeyID = -1;
		for (int i = 0; i < 256; i++) {
			if (!strstr(KeyNames[i], "undef") && !CTM(cm, Trims[1], KeyNames[i]))
				KeyID = i;
		}
		if (!CTM( cm, Trims[1], "keylist"))
		{
			for (int i = 0; i < 256; i++)
				if (!strstr(KeyNames[i], "undef"))LogMessage("|  %s", sf::Color(225, 180, 32), KeyNames[i]);
		}
		else if (!CTM( cm, Trims[1], "cmdlist"))
		{
			for (int i = 0; i < 23; i++)
				if (!strstr(ActNames[i], "undef"))LogMessage("|  %s", sf::Color(225, 180, 32), ActNames[i]);
		}
		else if (KeyID != -1)
		{
			if (Trims.size() == 2)
			{
				LogMessage("|  Bound on '%s'", sf::Color(225, 180, 32), KeyNames[KeyID]);
				for (int i = 0; i < 23; i++)
				{
					if (Binds.KeysPrimary[i] == KeyID)LogMessage("|  %s", sf::Color(225,180,32), ActNames[i]);
					if (Binds.KeysSecondary[i] == KeyID)LogMessage("|  %s", sf::Color(225, 180, 32), ActNames[i]);
				}

			}
			else
			{
				int ActID = -1;
				for (int i = 0; i < 23; i++) {
					if (!strstr(ActNames[i], "undef") && !CTM(cm, Trims[2], ActNames[i]))
						ActID = i;
				}
				if (ActID != -1)
				{
					if (Binds.KeysPrimary[ActID] == 0)
					{
						Binds.KeysPrimary[ActID] = KeyID;
						LogMessage("|  Action '%s' bound to '%s'", sf::Color(225, 180, 32), ActNames[ActID], KeyNames[KeyID]);
					}
					else if (Binds.KeysSecondary[ActID] == 0 && Binds.KeysSecondary[ActID] != KeyID)
					{
						Binds.KeysSecondary[ActID] = KeyID;
						LogMessage("|  Action '%s' bound to '%s'", sf::Color(225, 180, 32), ActNames[ActID], KeyNames[KeyID]);
					}
					else if (Binds.KeysSecondary[ActID] == 0 && Binds.KeysSecondary[ActID] == KeyID)
					{
						LogError("|  Action '%s' is alreaddy bound to '%s'", ActNames[ActID], KeyNames[KeyID]);
					}
					else
					{
						LogError("|  Action '%s' is already bound to '%s' and '%s'. Unbind it first.", ActNames[ActID], KeyNames[Binds.KeysPrimary[ActID]],KeyNames[Binds.KeysSecondary[ActID]]);
					}
				}
				else
				{
					LogError("|  '%.*s' is not an action", Trims[2].y, cm + Trims[2].x);
				}
			}
		}
		else
		{
			LogError("|  '%.*s' is not a key", Trims[1].y, cm + Trims[1].x);
		}

	}
	return false;
}

bool dc_game::cmdCommands(char* cm)
{
	auto CommandList = GetAllNonCvarCommands();
	LogMessage("|  List of executable commands", sf::Color(225, 180, 32));
	LogMessage("|  ", sf::Color(225, 180, 32));
	for (auto c : CommandList)
	{
		LogMessage("|  '%s'", sf::Color(225, 180, 32), c);
	}
	return true;
}

bool dc_game::cmdConvars(char* cm)
{
	auto ConvarList = GetAllConvars();
	LogMessage("|  List of existing Console Variables", sf::Color(225, 180, 32));
	LogMessage("|  ", sf::Color(225, 180, 32));
	for (auto c : ConvarList)
	{
		LogMessage("|  '%s'", sf::Color(225, 180, 32), c);
	}
	return true;
}

bool dc_game::cmdFind(char* cm)
{
	auto Trims = TrimStringFully(cm);

	if (Trims.size() <= 1)
	{
		LogMessage("|  Usage: find #something", sf::Color(225, 180, 32));
		return true;
	}
	auto CommandList = GetAllNonCvarCommands();
	auto ConvarList = GetAllConvars();

	for (int i = 0; i < ConvarList.size(); i++)
		CommandList.push_back(ConvarList[i]);

	auto Alphabetic = [=](char* a, char* b)
	{
		int minLen = min(strlen(a), strlen(b));

		for (int i = 0; i < minLen; i++)
		{
			if (a[i] < b[i])return true;
			else if (b[i] < a[i])return false;
		}
		if (strlen(b) > strlen(a)) return false;
		else if (strlen(b) < strlen(a))return true;
		return false;
	};
	
	std::vector<char*> Goods;

	char* trimactual = new char[Trims[1].y+4];
	sprintf(trimactual, "%.*s", Trims[1].y, cm + Trims[1].x);

	for (auto c : CommandList)
	{
		if (strstr(c, trimactual))Goods.push_back(c);
	}

	if (Goods.size() <= 0)
	{
		LogError("|  Couldn't find \"%s\"",  trimactual);
	}
	else
	{
		std::sort(Goods.begin(), Goods.end(), Alphabetic);
		LogMessage("|  Found %d in total", sf::Color(225, 180, 32),Goods.size());
		LogMessage("|  ", sf::Color(225, 180, 32));
		for (auto c : Goods)
			LogMessage("|  '%s'", sf::Color(225, 180, 32), c);
	}
	delete[]trimactual;

	return true;
}

bool dc_game::cmdDPS(char* cm)
{
	auto Trims = TrimStringFully(cm);
	if (Trims.size() <= 1)
	{
		LogMessage("|  Usage: dps #distance #maxwriteout", sf::Color(225, 180, 32));
		return true;
	}
	else
	{
		if (IsANumber(cm + Trims[1].x, Trims[1].y))
		{
			std::vector<int> Id_List;
			for (int i = 0; i < g_Items.size(); i++)Id_List.push_back(i);

			std::vector<int> Id_ListStanding;
			for (int i = 0; i < g_Items.size(); i++)Id_ListStanding.push_back(i);

			float Range = TextToFloat(cm + Trims[1].x, Trims[1].y);
			if (Range < 0)Range = 0;
			auto dmgcomp = [=](int a, int b)
			{
				return g_Items[a].CalculateDPS(Range, false) >= g_Items[b].CalculateDPS(Range, false);
			};
			auto dmgcompstanding = [=](int a, int b)
			{
				return g_Items[a].CalculateDPS(Range, true) >= g_Items[b].CalculateDPS(Range, true);
			};

			std::sort(Id_List.begin(), Id_List.end(), dmgcomp);
			std::sort(Id_ListStanding.begin(), Id_ListStanding.end(), dmgcompstanding);


			if (Trims.size() > 2 && IsANumber(cm + Trims[2].x, Trims[2].y))
			{
				int maxWriteout = (int)TextToFloat(cm + Trims[2].x, Trims[2].y);
				if (maxWriteout < 1)maxWriteout = 1;
				if (maxWriteout > g_Items.size())maxWriteout = g_Items.size();
				LogMessage("|  DPS at Distance %.2f - Moving", sf::Color(225, 180, 32),Range);
				for (int i = 0; i < maxWriteout; i++)
				{
					sf::Color c(128, 128, 128);
					if (i == 0) c = sf::Color(225, 180, 122);
					if (i == 1)c = sf::Color(225, 225, 225);
					if (i == 2) c = sf::Color(230, 120, 23);
					LogMessage("|  %d - %s - %.2f", c,i+1,g_Items[Id_List[i]].szName, g_Items[Id_List[i]].CalculateDPS(Range, false));
				}
				LogMessage("|  DPS at Distance %.2f - Standing", sf::Color(225, 180, 32), Range);
				for (int i = 0; i < maxWriteout; i++)
				{
					sf::Color c(128, 128, 128);
					if (i == 0) c = sf::Color(225, 180, 122);
					if (i == 1)c = sf::Color(225, 225, 225);
					if (i == 2) c = sf::Color(230, 120, 23);
					LogMessage("|  %d - %s - %.2f", c, i+1, g_Items[Id_ListStanding[i]].szName, g_Items[Id_ListStanding[i]].CalculateDPS(Range, true));
				}
				return true;
			}
			else
			{
				int maxWriteout = g_Items.size();
				LogMessage("|  DPS at Distance %.2f - Moving", sf::Color(225, 180, 32), Range);
				for (int i = 0; i < maxWriteout; i++)
				{
					sf::Color c(128, 128, 128);
					if (i == 0) c = sf::Color(225, 180, 122);
					if (i == 1)c = sf::Color(225, 225, 225);
					if (i == 2) c = sf::Color(230, 120, 23);
					LogMessage("|  %d - %s - %.2f", c, i+1, g_Items[Id_List[i]].szName, g_Items[Id_List[i]].CalculateDPS(Range, false));
				}
				LogMessage("|  DPS at Distance %.2f - Standing", sf::Color(225, 180, 32), Range);
				for (int i = 0; i < maxWriteout; i++)
				{
					sf::Color c(128, 128, 128);
					if (i == 0) c = sf::Color(225, 180, 122);
					if (i == 1)c = sf::Color(225, 225, 225);
					if (i == 2) c = sf::Color(230, 120, 23);
					LogMessage("|  %d - %s - %.2f", c, i+1, g_Items[Id_ListStanding[i]].szName, g_Items[Id_ListStanding[i]].CalculateDPS(Range, true));
				}
			}
			return true;
		}
		else
		{

			LogError("|  '%.*s' is not a number", Trims[1].y, cm + Trims[1].x);
		}

	}
	return false;
}


bool dc_game::cmdTime(char* cm)
{
	if (Match == nullptr)
	{
		LogError("|  \"time\" command can only be used during a match.");
		return false;
	}
	auto Trims = TrimStringFully(cm);
	if (Trims.size() <= 1)
	{
		LogMessage("|  Time is: %d", sf::Color(225, 180, 32), Match->map.day_time);
		return true;
	}
	else
	{
		if (IsANumber(cm + Trims[1].x, Trims[1].y))
		{
			auto num = (int)TextToFloat(cm + Trims[1].x, Trims[1].y);
			Match->map.day_time = num;
			LogMessage("|  Time set to: %d", sf::Color(225, 180, 32), num);
			return true;
		}
		else
		{

			LogError("|  '%.*s' is not a number", Trims[1].y, cm + Trims[1].x);
		}

	}
	return false;
}

bool dc_game::cmdCamera(char* cm)
{
	if (Match == nullptr)
	{
		LogError("|  \"camera\" command can only be used during a match.");
		return false;
	}
	auto Trims = TrimStringFully(cm);
	if (Trims.size() <= 1)
	{
		LogMessage("|  Camera Follows: %d", sf::Color(225, 180, 32), Match->camera_follows);
		return true;
	}
	else
	{
		int PlayerID = -1;
		if (IsANumber(cm + Trims[1].x, Trims[1].y))
		{
			PlayerID = TextToInt(cm + Trims[1].x, Trims[1].y);
		}
		while (Match->GetAlivePlayers() <= 0 || Match->players[PlayerID].iHealth <= 0)
		{
			PlayerID++;
			if (PlayerID == 100)PlayerID = 0;
		}
		Match->camera_follows = PlayerID;
		LogMessage("|  Camera now follows: %d", sf::Color(225, 180, 32), Match->camera_follows);
		return true;
	}
	return false;
}


bool dc_game::cmdSpawn(char* cm)
{
	if (Match == nullptr)
	{
		LogError("|  \"spawn\" commands can only be used during a match.");
		return false;
	}

	auto Trims = TrimStringFully(cm);
	if (Trims.size() <= 1)
	{
		LogMessage("|  spawn: item #id/name (%d-%d), randomitem, chest, player #id, player_floating #id", sf::Color(225, 180, 32), 0,g_Items.size()-1);
		return true;
	}
	else
	{
		if (!CTM(cm, Trims[1], "chest"))
		{
			dc_chest Chest;
			Chest.bOpen = false;
			Chest.vPosition = Match->players[Match->camera_follows].vPosition;
			Match->map.chests.push_back(Chest);

		}
		else if (!CTM(cm, Trims[1], "randomitem"))
		{
			int wpnIndex = Random(0, g_Items.size() - 1);
			auto item = g_Items[wpnIndex];
			item.vPosition = Match->players[Match->camera_follows].vPosition + sf::Vector2f(RandFloat()*0.5f - 0.25f, RandFloat()*0.5f - 0.25f);
			item.GameIdx = Match->TotalItems;
			Match->TotalItems++;
			Match->map.items.push_back(item);

			LogMessage("|  Item spawned: %s", sf::Color(225, 180, 32), item.szName);
		}
			else if (!CTM(cm, Trims[1], "item"))
			{
				if (Trims.size() >= 3)
				{
					int wpnIndex = -1;
					if (IsANumber(cm + Trims[2].x, Trims[2].y))
					{
						wpnIndex = TextToInt(cm + Trims[2].x, Trims[2].y);
					}
					else
					{
						std::vector<char*>wpnNames = { "revo_com","revo_unc","revo_rar","revo_epi","revo_leg","mp8_com","mp8_unc","mp8_rar","mp8_epi","mp8_leg","silen_com","silen_unc","silen_rar","bandages","medkit","smallshield","bigshield","slurpjuice","chugjug","glock_com","glock_unc","glock_rar","usp_epi","usp_leg","ar_com","ar_unc","ar_rar","ar_epi","ar_leg","minigun_epi","minigun_leg","scopedar_unc","scopedar_rar","scopedar_epi","spas_com","spas_unc","spas_rar","spas_epi","spas_leg","leone_com","leone_unc","leone_rar","leone_epi","leone_leg","thomson_com","thomson_unc","thomson_rar","thomson_epi","thomson_leg","kor_com","kor_unc","kor_rar","kor_epi","kor_leg","famas_com","famas_unc","famas_rar","famas_epi","famas_leg","tacti_com","tacti_unc","tacti_rar","tacti_epi","tacti_leg","magnum_rar","magnum_epi","magnum_leg","hunting_unc","hunting_rar","semiauto_unc","semiauto_rar","semiauto_epi","rl_rar","rl_epi","rl_leg","gl_rar","gl_epi","gl_leg","grenade","lmg_rar","lmg_epi","lmg_leg","dbarrel_rar","dbarrel_epi","dbarrel_leg","combat_rar","combat_epi","combat_leg","tommy_com","tommy_unc","tommy_rar","silen_myt","tommy_myt","minigun_myt","hunting_myt","ar_myt"};
						for (int i = 0; i < wpnNames.size(); i++)
						{
							if (!CTM(cm, Trims[2], wpnNames[i])) { wpnIndex = i; break; }
						}
					
					}
					if (wpnIndex >= 0 && wpnIndex < g_Items.size())
					{
						auto item = g_Items[wpnIndex];
						item.vPosition = Match->players[Match->camera_follows].vPosition + sf::Vector2f(RandFloat()*0.5f-0.25f,RandFloat()*0.5f-0.25f);
						item.GameIdx = Match->TotalItems;
						Match->TotalItems++;
						Match->map.items.push_back(item);
						LogMessage("|  Item spawned: %s", sf::Color(225, 180, 32), item.szName);
					}
					else
					{
						LogError("|  Invalid index/name added.");
					}
				}
				else
				{
					LogError("|  No index/name added");
				}
			}
			else if (!CTM(cm, Trims[1], "player"))
			{
				if (Trims.size() >= 3)
				{
					int plIndex = -1;
					if (IsANumber(cm + Trims[2].x, Trims[2].y))
					{
						plIndex = TextToInt(cm + Trims[2].x, Trims[2].y);
					}
					if (plIndex >= 0 && plIndex < 99)
					{
						Match->players[plIndex].iHealth = 100;
						Match->players[plIndex].bOnBus = false;
						Match->players[plIndex].bGodMode = false;
						Match->players[plIndex].fFreeFallHeight = 0.f;
						Match->players[plIndex].iShield = 0;
						Match->players[plIndex].iOpeningChest = -1;
						Match->players[plIndex].vPosition = Match->players[Match->camera_follows].vPosition + sf::Vector2f(RandFloat()*0.5f - 0.25f, RandFloat()*0.5f - 0.25f);
						Match->players[plIndex].Items[0].bValidated = false;
						Match->players[plIndex].Items[1].bValidated = false;
						Match->players[plIndex].Items[2].bValidated = false;
						Match->players[plIndex].Items[3].bValidated = false;
						Match->players[plIndex].Items[4].bValidated = false;
					}
					else
					{
						LogError("|  Invalid index added.");
					}
				}
				else
				{
					LogError("|  No index added");
				}
			}

			else if (!CTM(cm, Trims[1], "player_floating"))
			{
				if (Trims.size() >= 3)
				{
					int plIndex = -1;
					if (IsANumber(cm + Trims[2].x, Trims[2].y))
					{
						plIndex = TextToInt(cm + Trims[2].x, Trims[2].y);
					}
					if (plIndex >= 0 && plIndex < 99)
					{
						Match->players[plIndex].iHealth = 100;
						Match->players[plIndex].bOnBus = false;
						Match->players[plIndex].bGodMode = false;
						Match->players[plIndex].fFreeFallHeight = 100.f;
						Match->players[plIndex].iShield = 0;
						Match->players[plIndex].iOpeningChest = -1;
						Match->players[plIndex].vPosition = Match->players[Match->camera_follows].vPosition + sf::Vector2f(RandFloat()*0.5f - 0.25f, RandFloat()*0.5f - 0.25f);
						Match->players[plIndex].Items[0].bValidated = false;
						Match->players[plIndex].Items[1].bValidated = false;
						Match->players[plIndex].Items[2].bValidated = false;
						Match->players[plIndex].Items[3].bValidated = false;
						Match->players[plIndex].Items[4].bValidated = false;
					}
					else
					{
						LogError("|  Invalid index added.");
					}
				}
				else
				{
					LogError("|  No index added");
				}
			}
			else 
			{
				int wpnIndex = -1;
				std::vector<char*>wpnNames = { "revo_com","revo_unc","revo_rar","revo_epi","revo_leg","mp8_com","mp8_unc","mp8_rar","mp8_epi","mp8_leg","silen_com","silen_unc","silen_rar","bandages","medkit","smallshield","bigshield","slurpjuice","chugjug","glock_com","glock_unc","glock_rar","usp_epi","usp_leg","ar_com","ar_unc","ar_rar","ar_epi","ar_leg","minigun_epi","minigun_leg","scopedar_unc","scopedar_rar","scopedar_epi","spas_com","spas_unc","spas_rar","spas_epi","spas_leg","leone_com","leone_unc","leone_rar","leone_epi","leone_leg","thomson_com","thomson_unc","thomson_rar","thomson_epi","thomson_leg","kor_com","kor_unc","kor_rar","kor_epi","kor_leg","famas_com","famas_unc","famas_rar","famas_epi","famas_leg","tacti_com","tacti_unc","tacti_rar","tacti_epi","tacti_leg","magnum_rar","magnum_epi","magnum_leg","hunting_unc","hunting_rar","semiauto_unc","semiauto_rar","semiauto_epi","rl_rar","rl_epi","rl_leg","gl_rar","gl_epi","gl_leg","grenade","lmg_rar","lmg_epi","lmg_leg" };
				for (int i = 0; i < wpnNames.size(); i++)
				{
					if (!CTM(cm, Trims[1], wpnNames[i])) { wpnIndex = i; break; }
				}


				if (wpnIndex >= 0 && wpnIndex < g_Items.size())
				{
					auto item = g_Items[wpnIndex];
					item.vPosition = Match->players[Match->camera_follows].vPosition + sf::Vector2f(RandFloat()*0.5f - 0.25f, RandFloat()*0.5f - 0.25f);
					Match->map.items.push_back(item);
					LogMessage("|  Item spawned: %s", sf::Color(225, 180, 32), item.szName);
					return true;
				}
			}

	}
	return false;
}

bool dc_game::cmdClear(char* cm)
{
	ConsoleLogs.clear();
	console_pos = 0;
	return true;
}

bool dc_game::cmdEcho(char* cm,sf::Vector2i Trim)
{
	float originalValue = g_Config.con_silent.Value;
	g_Config.con_silent.Value = 0.f;
	LogMessage("|  %s", sf::Color(225,180,32),cm+Trim.x+Trim.y);
	g_Config.con_silent.Value = originalValue;
	return true;
}

bool dc_game::cmdPlayer(char* cm)
{
	if (Match == nullptr)
	{
		LogError("|  \"player\" commands can only be used during a match.");
		return false;
	}
	if (!g_Config.gm_cheats.Value >= 1.f)
	{
		LogError("|  \"player\" commmand are cheat commands. Try using \"gm_cheats 1\".");
		return false;
	}

	auto Trims = TrimStringFully(cm);

	if (Trims.size() <= 1)
	{
		auto KillLeaders = Match->GetKillLeaders();
		LogMessage("|  Total players alive: %d", sf::Color(225, 180, 32),Match->GetAlivePlayers());
		for (int i = 0; i < 5; i++)
		{
			if(KillLeaders[i] == 0)LogMessage("|  Player (%d) %s: Kills: %d %s", sf::Color(0, 255, 32), KillLeaders[i],Match->players[KillLeaders[i]].szName,Match->players[KillLeaders[i]].Stats.iEliminations, ((Match->players[KillLeaders[i]].iHealth > 0) ? "" : "- (dead)"));
			else LogMessage("|  Player (%d) %s: Kills: %d %s", sf::Color(225, 180, 32), KillLeaders[i], Match->players[KillLeaders[i]].szName, Match->players[KillLeaders[i]].Stats.iEliminations, ((Match->players[KillLeaders[i]].iHealth > 0) ? "" : "- (dead)"));
		}
		return true;
	}
	else
	{
		if (!CTM(cm, Trims[1], "help"))
		{
			LogMessage("|  player #id: Reveals information.", sf::Color(225, 180, 32));
			LogMessage("|  player #id kill: Kills player.", sf::Color(225, 180, 32));
			LogMessage("|  player #id god: Turns god mode on/off.", sf::Color(225, 180, 32));
			LogMessage("|  player #id teleport #x #y: Teleports player.", sf::Color(225, 180, 32));
			LogMessage("|  player #id health #hp #sh: Changes health and shield.", sf::Color(225, 180, 32));
		}
		int PlayerID = -1;
		if (IsANumber(cm + Trims[1].x, Trims[1].y))
		{
			PlayerID = TextToInt(cm + Trims[1].x, Trims[1].y);
		}
		if (PlayerID < 0 || PlayerID > 99)
		{
			LogError("|  Error in \"player\": Define the player index (0-99). Use \"player help\".");
			return true;
		}
		if (Trims.size() == 2)
		{
			LogMessage("|  Player #%d - Name: '%s' -  %s", sf::Color(225, 180, 32), PlayerID, Match->players[PlayerID].szName,((Match->players[PlayerID].iHealth > 0)?"":"(dead)"));
			LogMessage("|  Health: %d - Shield: %d", sf::Color(225, 180, 32), Match->players[PlayerID].iHealth,Match->players[PlayerID].iShield);
			LogMessage("|  Position: %.f %.f", sf::Color(225, 180, 32), Match->players[PlayerID].vPosition.x, Match->players[PlayerID].vPosition.y);
			return true;
		}
		else
		{
			if (!CTM(cm, Trims[2], "kill"))
			{
				LogMessage("|  Player #%d has been killed", sf::Color(225, 180, 32), PlayerID);
				Match->players[PlayerID].iHealth = 0;
				Match->players[PlayerID].iShield = 0;
				Match->PlayerKill(PlayerID);
				return true;
			}
			else if (!CTM(cm, Trims[2], "teleport"))
			{
				if (Trims.size() <= 4)
				{
					LogMessage("|  Usage: player #id teleport #x #y", sf::Color(225, 180, 32));
				}
				else
				{
					if (IsANumber(cm + Trims[3].x, Trims[3].y) && IsANumber(cm + Trims[4].x, Trims[4].y))
					{
						float X = TextToFloat(cm + Trims[3].x, Trims[3].y);
						float Y = TextToFloat(cm + Trims[4].x, Trims[4].y);

						LogMessage("|  Player #%d has been teleported to %.2f %.2f", sf::Color(225, 180, 32), PlayerID,X,Y);
						Match->players[PlayerID].vPosition = sf::Vector2f(X, Y);
						return true;
					}
				}
			}
			else if (!CTM(cm, Trims[2], "god"))
			{
				Match->players[PlayerID].bGodMode = !Match->players[PlayerID].bGodMode;
				LogMessage("|  Player #%d now has god mode %s", sf::Color(225, 180, 32), PlayerID, ((Match->players[PlayerID].bGodMode) ? ("on") : ("off")));
				return true;
			}
			else if (!CTM(cm, Trims[2], "health"))
			{
				if (IsANumber(cm + Trims[3].x, Trims[3].y) && IsANumber(cm + Trims[4].x, Trims[4].y))
				{
					int HP = TextToInt(cm + Trims[3].x, Trims[3].y);
					int SH = TextToInt(cm + Trims[4].x, Trims[4].y);

					if (HP < 0)HP = 0;
					else if (HP > 100)HP = 100;
					if (SH < 0)SH = 0;
					if (SH > 100)SH = 100;

					LogMessage("|  Player #%d has health set to (%d|%d)", sf::Color(225, 180, 32), PlayerID, HP,SH);
					Match->players[PlayerID].iHealth = HP;
					Match->players[PlayerID].iShield = SH;
					return true;
				}
			}
		}
	}

	return false;
}

void dc_game::MoveConsoleMessages()
{
	if (OldConsoleMessages.size() <= 0)return;

	int ConMesi = ConsoleMessageIndex;

	if (g_Keyboard.keys[VK_UP]&1)ConsoleMessageIndex--;
	else if (g_Keyboard.keys[VK_DOWN] & 1)ConsoleMessageIndex++;


	if (ConMesi != ConsoleMessageIndex)
	{
		if (ConsoleMessageIndex < 0)ConsoleMessageIndex = OldConsoleMessages.size() - 1;
		if (ConsoleMessageIndex > OldConsoleMessages.size() - 1)ConsoleMessageIndex = 0;

		sprintf(ConsoleMessage, "%s\0", OldConsoleMessages[ConsoleMessageIndex]->msg);
	}
}

void dc_game::DoConsole()
{
	ScrollConsole();
	MoveConsoleMessages();
	int len = strlen(ConsoleMessage);
	g_Keyboard.UpdateText(ConsoleMessage, &len,120);

	if (GetKeyStatus(DCK_CONSOLE_ENTER, false) && len >= 2)
	{
		LogConsoleMessage();
		LogMessage("> %s", sf::Color(192, 192, 192), ConsoleMessage);
		ConsoleExecuteCommand(ConsoleMessage);
		sprintf(ConsoleMessage, "\0\0"); //Resetting the console message
		//LogMessage("Pushing Back", sf::Color(192, 192, 192));
	}


	int therange = max(0, (int)ConsoleLogs.size()-15);

	if (g_Mouse.left_click && g_Mouse.IsBetween(g_Resolution.x*0.985f, g_Resolution.y*0.005f, g_Resolution.x*0.1f, g_Resolution.y*0.39f, g_Mouse.leftclickCoords.x, g_Mouse.leftclickCoords.y))
	{

		float percent = ((float)g_Mouse.Coords.y - g_Resolution.y*0.005f)/ (0.39f*g_Resolution.y);
		float numThisway = (1-percent)*therange+0.5f;
		if (numThisway < 0)numThisway = 0;
		else if (numThisway > ConsoleLogs.size() - 15)numThisway = ConsoleLogs.size()-15;
		console_pos = numThisway;
	}
	//int slidepos = g_Resolution.y*0.39f;
	//int spush = (((float)console_pos) / consize)*0.385f*g_Resolution.y;
	//slidepos -= spush;
	//int slidesize = g_Resolution.y*0.385f*(15.f / consize);


}