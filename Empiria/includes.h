#pragma once
#include <d3d9.h>
#include <Windows.h>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include "fastParser.h"
#include "_Tek.h"
#include "FileSys.h"
#include <chrono>
#include "_Window.h"
#include "_Audio.h"
#include <vector>
#include "Random.h"

extern RandomDevice g_RandomDevice;
extern unsigned int g_Framerate;

extern sf::RenderWindow* g_Window;

#define PI 3.14159265
#define ConLog printf


static int llrand() {
	int r = 0;

	for (int i = 0; i < 2; ++i) {
		r = (r << 15) | (rand() & 0x7FFF);
	}

	return r & 0xFFFFFFFF;
}

static int Random(int RandMin, int RandMax) 
{
	return g_RandomDevice.RandomInt(RandMin, RandMax);

}




static float RandFloat()
{
	return g_RandomDevice.RandomFloat(0, 1);
}


struct coord
{
	int x, y;
};

struct keyboard_t
{
	SHORT __stdcall last_keys[256];
	SHORT __stdcall keys[256];

	void Update()
	{
		for (int i = 0; i < 256; i++)
		{
			last_keys[i] = keys[i];
			keys[i] = GetAsyncKeyState(i);
		}
	}

	void Reset()
	{
		for (int i = 0; i < 256; i++)
		{
			last_keys[i] = 0;
			keys[i] = 0;
		}
	}

	bool hasJustPressed(unsigned int i)
	{
		return !last_keys[i] && keys[i];
	}

	bool hasReleased(unsigned int i)
	{
		return last_keys[i] && !keys[i];
	}
	//////////////////////////////////////////////
	/// Adds a new character 'add' at the end of a char-array
	//////////////////////////////////////////////
	void UpdateTextLastChar(char* text, char add, int* len)
	{
		text[*len] = add;
		text[*len + 1] = '\0';
		(*len)++;
	}
	//////////////////////////////////////////////
	/// Hard-coded, the very bad way.
	/// Check for key presses, and adds new characters to the char-array 'text' until it reaches 'maxlen'
	/// TODO: Use the SFML equivalent of this
	//////////////////////////////////////////////
	void UpdateText(char* text, int* len, int maxlen)
	{
		if (*len != maxlen)
		{
			bool shift = keys[VK_SHIFT];
			bool alt_gr = keys[VK_CONTROL] && keys[VK_MENU];

#define UTLC(t,a) UpdateTextLastChar(t,a,len)

			if (shift)
			{
				if (keys[0x30] & 1)UTLC(text, '§');
				if (keys[0x31] & 1)UTLC(text, '\'');
				if (keys[0x32] & 1)UTLC(text, '"');
				if (keys[0x33] & 1)UTLC(text, '+');
				if (keys[0x34] & 1)UTLC(text, '!');
				if (keys[0x35] & 1)UTLC(text, '%');
				if (keys[0x36] & 1)UTLC(text, '/');
				if (keys[0x37] & 1)UTLC(text, '=');
				if (keys[0x38] & 1)UTLC(text, '(');
				if (keys[0x39] & 1)UTLC(text, ')');

				for (int i = 0x41; i <= 0x5A; i++)if (keys[i] & 1)UTLC(text, 'A' + i - 0x41);

				if (keys[188] & 1)UTLC(text, '?');
				if (keys[190] & 1)UTLC(text, ':');
				if (keys[189] & 1)UTLC(text, '_');
			}
			else if (alt_gr)
			{
				if (keys[0x31] & 1)UTLC(text, '~');
				if (keys[0x32] & 1)UTLC(text, '¡');
				if (keys[0x33] & 1)UTLC(text, '^');
				if (keys[0x34] & 1)UTLC(text, '¢');
				if (keys[0x35] & 1)UTLC(text, '°');
				if (keys[0x36] & 1)UTLC(text, '²');
				if (keys[0x37] & 1)UTLC(text, '`');
				if (keys[0x38] & 1)UTLC(text, 'ÿ');
				if (keys[0x39] & 1)UTLC(text, '´');

				if (keys[0x41] & 1)UTLC(text, 'ä');
				if (keys[0x42] & 1)UTLC(text, '{');
				if (keys[0x43] & 1)UTLC(text, '&');
				if (keys[0x44] & 1)UTLC(text, 'Ð');
				if (keys[0x45] & 1)UTLC(text, 'Ä');
				if (keys[0x46] & 1)UTLC(text, '[');
				if (keys[0x47] & 1)UTLC(text, ']');
				if (keys[0x49] & 1)UTLC(text, 'Í');
				if (keys[0x4A] & 1)UTLC(text, 'í');
				if (keys[0x4B] & 1)UTLC(text, '³');
				if (keys[0x4C] & 1)UTLC(text, '£');
				if (keys[0x4E] & 1)UTLC(text, '}');
				if (keys[0x51] & 1)UTLC(text, '\\');
				if (keys[0x53] & 1)UTLC(text, 'ð');
				if (keys[0x55] & 1)UTLC(text, '€');
				if (keys[0x56] & 1)UTLC(text, '@');
				if (keys[0x57] & 1)UTLC(text, '|');
				if (keys[0x58] & 1)UTLC(text, '#');
				if (keys[0x59] & 1)UTLC(text, '>');

				if (keys[188] & 1)UTLC(text, ';');
				if (keys[190] & 1)UTLC(text, '>');
				if (keys[189] & 1)UTLC(text, '*');

			}
			else
			{
				for (int i = 0x30; i < 0x3A; i++)
				{
					if (keys[i] & 1)UTLC(text, '0' - 0x30 + i);
				}
				for (int i = 0x41; i <= 0x5A; i++)
				{
					if (keys[i] & 1)UTLC(text, 'a' + i - 0x41);
				}

				if (keys[188] & 1)UTLC(text, ',');
				if (keys[190] & 1)UTLC(text, '.');
				if (keys[189] & 1)UTLC(text, '-');
			}

			for (int i = 96; i < 106; i++)
			{
				if (keys[i] & 1)UTLC(text, '0' + i - 96);
			}
			if (keys[111] & 1)UTLC(text, '/');
			if (keys[106] & 1)UTLC(text, '*');
			if (keys[109] & 1)UTLC(text, '+');
			if (keys[107] & 1)UTLC(text, '+');

			if (keys[VK_SPACE] & 1)UTLC(text, ' ');
		}
		if (keys[VK_BACK] & 1) { if (*len > 0) { text[(*len) - 1] = '\0'; (*len)--; } }

	}


};
extern keyboard_t g_Keyboard;


struct mouse_t
{
	int scroll = 0;
	coord leftclickCoords;
	coord rightclickCoords;
	coord Coords;
	bool left_click = false, right_click = false;
	bool last_left = false, last_right = false;

	bool isHolding(bool leftfalse__righttrue = false)
	{
		if (leftfalse__righttrue)return right_click;
		else return left_click;
	}

	bool hasReleased(bool leftfalse__righttrue = false)
	{
		if (leftfalse__righttrue)
		{
			return last_right && !right_click;
		}
		else return last_left && !left_click;
	}

	bool hasJustClicked(bool leftfalse__righttrue = false)
	{
		if (leftfalse__righttrue)
		{
			return !last_right && right_click;
		}
		else return !last_left && left_click;
	}

	void Reset()
	{
		left_click = false;
		right_click = false;
		last_left = false;
		last_right = false;
		scroll = 0;
	}

	void Update(int x, int y, int scr)
	{
		scroll = scr;
		Coords.x = x; Coords.y = y;
		last_left = left_click;
		last_right = right_click;
		left_click = GetAsyncKeyState(0x01);
		right_click = GetAsyncKeyState(0x02);

		if (hasJustClicked(false))
		{
			leftclickCoords = Coords;
		}
		if (hasJustClicked(true))
		{
			rightclickCoords = Coords;
		}

	}

	bool IsClickValid(bool leftfalse__righttrue = false)
	{
		if (leftfalse__righttrue)
		{
			if (abs(rightclickCoords.x - Coords.x) > 15 || abs(rightclickCoords.y - Coords.y) > 15)return false;
			//if (!hasJustClicked(leftfalse__righttrue) && !hasReleased(leftfalse__righttrue))return false;
		}
		else
		{
			if (abs(leftclickCoords.x - Coords.x) > 15 || abs(leftclickCoords.y - Coords.y) > 15)return false;
			//if (!hasJustClicked(leftfalse__righttrue) && !hasReleased(leftfalse__righttrue))return false;
		}
		return true;
	}

	bool IsBetween(int x, int y, int w, int h, int checkx = INT32_MIN, int checky = INT32_MIN)
	{
		if (checkx == INT32_MIN)checkx = Coords.x;
		if (checky == INT32_MIN)checky = Coords.y;
		return x < checkx && y < checky && checkx < x + w && checky < y + h;
	}

};

static float vec2angle(float x, float y)
{
	return atan2f(y, x) * 180 / PI;


	float hypotenuse = sqrt(x*x + y*y);

	float angle = 90.f;

	if (x != 0.f)
	{
		auto param = y / x;
		angle = atan(param) * 180 / PI;
		if (x <= 0)angle += 180;
	}
	return angle;
}

static sf::Vector2f angle2vec(float angle)
{
	return sf::Vector2f(cos(angle*PI / 180), sin(angle*PI / 180));
}

static float anglediff(float a, float b)
{
	while (a < 0)a += 360;
	while (a > 360)a -= 360;
	while (b < 0)b += 360;
	while (b > 360)b -= 360;

	float diff = b - a;
	if (diff >= 180)diff = 180 - diff;
	else if (diff <= -180)diff = -180 - diff;
	return diff;
}

template<typename Ty> static int GetIndex(std::vector<Ty>& Vec, Ty elem)
{
	for (int i = 0; i < Vec.size(); i++)
	{
		if (elem == Vec[i])return i;
	}
	return -1;
}

 template<typename Ty> static Ty RandomData(std::vector<int> Cases, std::vector<Ty> results)
{
	if (results.size() == 0 || Cases.size() == 0)return Ty();
	int totalCases = 0;
	for (c : Cases)
	{
		totalCases += c;
	}
	int r = Random(1, totalCases);

	for (int i = 0; i < Cases.size(); i++)
	{
		if (r <= Cases[i])return results[i];
		else r -= Cases[i];
	}
	return results[results.size() - 1];

}
 template<typename Ty> static bool IsIn(std::vector<Ty> Vec, Ty Elem)
{
	 for (auto v : Vec) { 
		 if (v == Elem)return true;
	 }
	return false;
}

 struct dc_clock
 {
	 std::chrono::time_point<std::chrono::steady_clock> last = std::chrono::high_resolution_clock::now();

	 //////////////////////////////////////////////
	 /// Returns the time passed since the last Update() call in milliseconds
	 //////////////////////////////////////////////
	 inline int deltaTime()
	 {
		 auto now = std::chrono::high_resolution_clock::now();
		 return std::chrono::duration_cast<std::chrono::milliseconds>(now - last).count();
	 }
	 //////////////////////////////////////////////
	 /// Sets the clock's measuring point to the current time
	 //////////////////////////////////////////////
	 void Update()
	 {
		 last = std::chrono::high_resolution_clock::now();
	 }
 };


 static float GetDistance(sf::Vector2f a, sf::Vector2f b)
 {
	 auto dx = a.x - b.x, dy = a.y - b.y;
	 return sqrt(dx*dx + dy*dy);
 }

 static float GetLength(sf::Vector2f a)
 {
	 return sqrt(a.x*a.x + a.y*a.y);
 }


 static sf::Vector2f GetUnit(sf::Vector2f a)
 {
	 return a / GetDistance(a, sf::Vector2f(0, 0));
 }

 static float minmax(float minim, float yourval, float maxim)
 {
	 return max(minim, min(yourval, maxim));
 }

extern mouse_t g_Mouse;
extern sf::Vector2i g_Resolution;

extern std::vector<char*> g_Mes;
extern bool IsEditor;

extern std::string appLocation;

//////////////////////////////////////////////
/// Returns the application's location without the application name
/// For example: C:\\Users\\BigFluffKat7\\Documents\\test.exe -> C:\\Users\\BigFluffKat7\\Documents\\
//////////////////////////////////////////////
static void ChopAppName(char* string)
{
	int lastPer = 0;

	for (int i = 0; i < strlen(string); i++)
		if (string[i] == '\\')lastPer = i+1;
	
	char* ApplicationLocation = new char[lastPer + 1];
	
	sprintf(ApplicationLocation,"%.*s", lastPer, string);
	appLocation = ApplicationLocation;
}