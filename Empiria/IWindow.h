#pragma once
#include "includes.h"

struct IWindow
{
	static void AddToRenderList(sf::Drawable &drawable);
	static void RenderOverlay(int x, int y, int w, int h, int r, int g, int b, int _a);

	static void RenderText(int x, int y, char* text, int fontsize, int r = 255, int g = 255, int b = 255, int _a = 255);
	static void RenderTextB(int x, int y, char* text, int fontsize, int r = 255, int g = 255, int b = 255, int _a = 255);
	static void RenderTextBAdditive(int x, int y, char* text, int fontsize, int r = 255, int g = 255, int b = 255, int _a = 255);
	static void RenderTextBMiddle(int _x, int _y, int _w, int _h, char* text, int fontsize, int r = 255, int g = 255, int b = 255, int _a = 255);
	static void RenderTextBMiddleC(int _x, int _y, int _w, int _h, char* text, int fontsize, int r = 255, int g = 255, int b = 255, int _a = 255);
	static sf::Vector2i GetTextSize(char* text, int fontsize);
	static int GetHeightForFontsize(int fontsize);
	static sf::Vector2i GetRealTextSize(char* text, int fontsize);

	static void RenderTexture(sf::Texture t, sf::Sprite a, int x, int y, int r = 255, int g = 255, int b = 255, int _a = 255);

	static void CreateTheWindow();
};