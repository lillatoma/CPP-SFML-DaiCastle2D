#include "IWindow.h"

void IWindow::AddToRenderList(sf::Drawable &drawable)
{
	g_Window->draw(drawable);
}

void IWindow::RenderOverlay(int x, int y,int w, int h, int r, int g, int b, int _a)
{
	sf::RectangleShape RShape;
	RShape.setPosition(x, y);
	RShape.setSize(sf::Vector2f(w, h));
	RShape.setFillColor(sf::Color(r, g, b, _a));
	g_Window->draw(RShape);
}

void IWindow::RenderText(int x, int y, char* text, int fontsize, int r, int g, int b, int _a)
{
	static bool bLoaded = false;
	static file_t f = g_Files.GetFileByName("character.png");
	static sf::Texture t;
	static sf::Sprite a;


	int _x = x, _y = y;




	if (!bLoaded)
	{
		bLoaded = true;
		t.loadFromMemory(f.loc_in_mem, f.size);
		a.setTexture(t);
	}


	a.setScale(sf::Vector2f(1.0f*fontsize / 32, 1.0f*fontsize / 32));
	a.setColor(sf::Color(r, g, b, _a));
	int len = strlen(text);
	for (int i = 0; i < len; i++)
	{
		int High = text[i] / 16;
		int Low = text[i] % 16;

		if (text[i] == '\n')
		{
			_y += fontsize*0.8f + 1; _x = x;
		}
		else
		{
			a.setPosition(_x, _y);
			a.setTextureRect(sf::IntRect(32 * Low, 32 * High, 32, 32));
			_x += fontsize * 0.8f;
			IWindow::AddToRenderList(a);
		}

	}

}

void IWindow::RenderTextB(int x, int y, char* text, int fontsize, int r, int g, int b, int _a)
{
	static bool loaded = false;
	static sf::Font font;
	static file_t f = g_Files.GetFileByName("arial.ttf");
	if (!loaded)
	{
		font.loadFromMemory(f.loc_in_mem, f.size);
		loaded = true;
	}

	static sf::Text Text;
	Text.setFont(font);
	Text.setString(text);
	Text.setCharacterSize(fontsize);
	Text.setPosition(x, y);
	Text.setFillColor(sf::Color(r, g, b, _a));
		
	IWindow::AddToRenderList(Text);

}

void IWindow::RenderTextBAdditive(int x, int y, char* text, int fontsize, int r, int g, int b, int _a)
{
	static bool loaded = false;
	static sf::Font font;
	static file_t f = g_Files.GetFileByName("arial.ttf");
	if (!loaded)
	{
		font.loadFromMemory(f.loc_in_mem, f.size);
		loaded = true;
	}

	static sf::Text Text;
	Text.setFont(font);
	Text.setString(text);
	Text.setCharacterSize(fontsize);
	Text.setPosition(x, y);
	Text.setFillColor(sf::Color(r, g, b, _a));
	sf::BlendMode additiveBlending = sf::BlendAdd;
	g_Window->draw(Text, additiveBlending);

	//IWindow::AddToRenderList(Text);

}

void IWindow::RenderTexture(sf::Texture t, sf::Sprite a, int x, int y, int r, int g, int b, int _a )
{

	a.setPosition(x, y);
	a.setColor(sf::Color(r, g, b, _a));


	IWindow::AddToRenderList(a);
}

int IWindow::GetHeightForFontsize(int fontsize)
{
	return GetTextSize("A\n", fontsize).y - GetTextSize("A", fontsize).y;
}

sf::Vector2i IWindow::GetTextSize(char* text, int fontsize)
{
	static bool loaded = false;
	static sf::Font font;
	static file_t f = g_Files.GetFileByName("arial.ttf");
	if (!loaded)
	{
		font.loadFromMemory(f.loc_in_mem, f.size);
		loaded = true;
	}

	static sf::Text Text;
	Text.setFont(font);
	Text.setString(text);
	Text.setCharacterSize(fontsize);

	auto bound = Text.getLocalBounds();
	return sf::Vector2i(bound.width, bound.height);
}

sf::Vector2i IWindow::GetRealTextSize(char* text, int fontsize)
{
	
}

void IWindow::RenderTextBMiddle(int _x, int _y, int _w, int _h, char* text, int fontsize, int r, int g, int b, int _a)
{
	auto bound = GetTextSize(text, fontsize);

	RenderTextB(_x + (_w - bound.x) / 2, _y + ((_h - bound.y) / 2), text, fontsize, r, g, b, _a);
}

void IWindow::RenderTextBMiddleC(int _x, int _y, int _w, int _h, char* text, int fontsize, int r, int g, int b, int _a)
{
	char* NewBuffer = new char[strlen(text) + 16];
	sprintf(NewBuffer, "\n%s\n\n", text);

	auto bound = GetTextSize(NewBuffer, fontsize);

	RenderTextB(_x + (_w - bound.x) / 2, _y + ((_h - bound.y) / 2), NewBuffer, fontsize, r, g, b, _a);
	delete[] NewBuffer;
}

#include "DaiCastle.h"

void IWindow::CreateTheWindow()
{
	g_Window->close();
	if(g_Config.g_fullscreen.Value >= 1.f)
		g_Window->create(sf::VideoMode(g_Resolution.x, g_Resolution.y, 32U), "DaiCastle 2D Battle Royale Game", (sf::Style::Titlebar | sf::Style::Close | sf::Style::Fullscreen));
	else
		g_Window->create(sf::VideoMode(g_Resolution.x, g_Resolution.y, 32U), "DaiCastle 2D Battle Royale Game", (sf::Style::Titlebar | sf::Style::Close));

	g_Window->setFramerateLimit(g_Framerate);

}