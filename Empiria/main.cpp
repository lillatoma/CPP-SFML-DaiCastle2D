#include "includes.h"
#include "gameheaders.h"
#include "DaiCastle.h"
#include "ThreadManager.h"


std::vector<char*> g_Mes;
RandomDevice g_RandomDevice;
sf::RenderWindow* g_Window = new sf::RenderWindow;
mouse_t g_Mouse;
unsigned int g_Framerate = 60;
sf::Vector2i g_Resolution(1600, 900);
//dc_map Map;


dc_mapeditor* Editor;
keyboard_t g_Keyboard;

bool IsEditor = false;

std::string ApplicationName;
std::string appLocation;

std::vector<std::string> get_all_files_names_within_folder(std::string folder)
{
	std::vector<std::string> names;
	std::string search_path = folder + "/*.*";
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			// read all (real) files in current folder
			// , delete '!' read other 2 default folder . and ..
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				names.push_back(fd.cFileName);
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	return names;
}


void MakeNeededFolders()
{
	char Buffer[261];
	sprintf(Buffer, "%sdemos",appLocation.c_str());
	_mkdir(Buffer);
	sprintf(Buffer, "%scfg", appLocation.c_str());
	_mkdir(Buffer);
}

int main(int argc, char **argv)
{

	srand(time(NULL));

	g_Files.LoadAll();
	g_Files.ListLoadedFiles();
	dc_textures::define_all();
	dc_item::define_all();
	g_Sounds.DefineAllSounds();

	//
	char myPath[_MAX_PATH + 1];
	GetModuleFileName(NULL, myPath, _MAX_PATH);
	ChopAppName(myPath);
	MakeNeededFolders();
	dc_game Game;
	//if (IsEditor)
	//{
	//	Editor->Start();
	//	g_Resolution = sf::Vector2i(1280, 720);
	//	g_Window->create(sf::VideoMode(g_Resolution.x, g_Resolution.y), "DaiCastle 2D Battle Royale | Map Editor", (sf::Style::Titlebar | sf::Style::Close));
	//}
	//else
	{
		g_Map.load("BigSize");
		FreeConsole();
		
		Game.Setup();
		IWindow::CreateTheWindow();
	}



	while (g_Window->isOpen())
	{
		static int m_x = 0, m_y = 0;
		int scroll = 0;
		sf::Event _event;
		while (g_Window->pollEvent(_event))
		{
			switch (_event.type)
			{
			case sf::Event::Closed:
				Game.Quit();
				g_Window->close();
				break;
			case sf::Event::MouseMoved:
				m_x = _event.mouseMove.x;
				m_y = _event.mouseMove.y;
				break;
			case sf::Event::MouseWheelMoved:
				scroll = _event.mouseWheel.delta;
				break;
			}


		}
		g_Window->clear(sf::Color(255, 255, 255, 0));

		if (GetActiveWindow()) {
			g_Mouse.Update(m_x, m_y, scroll);
			g_Keyboard.Update();
		}
		else
		{
			g_Mouse.Reset();
			g_Keyboard.Reset();
		}


		//for (int i = 0; i < g_Mes.size(); i++)
		//	printf(g_Mes[i]);
		//g_Mes.clear();

		Game.Do();
		if (g_Window->isOpen())
		g_Window->display();

	}
}























