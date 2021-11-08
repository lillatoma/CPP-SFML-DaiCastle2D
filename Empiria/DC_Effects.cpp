#include "DaiCastle.h"

void dc_damageeffect::draw(float mx, float my, float width, float ServerTime)
{
	float diff = ServerTime - clockBegin;
	auto screen_pos = dc_map::world_to_screen(mx, my, width, position.x, position.y);
	screen_pos += sf::Vector2f(0, abs((diff - 0.25f) / 0.5f)*g_Resolution.y*0.05f);

	if (screen_pos.x < 0 || screen_pos.x > g_Resolution.x || screen_pos.y < 0 || screen_pos.y > g_Resolution.y)return;

	static char buffer[8];
	sprintf(buffer, "%d", damage);

	_Window::RenderTextB(screen_pos.x, screen_pos.y, buffer, 24 * g_Resolution.y / 720, color.r, color.g, color.g, min(255,2*color.a*(0.5f-diff)/0.5f));
}

void dc_shieldbreakeffect::draw(float mx, float my, float width,float servertime)
{
	float diff = servertime-clockBegin;


	auto p = dc_map::world_to_screen(mx, my, width, position.x, position.y);
	auto p2 = dc_map::world_to_screen(mx, my, width, position.x+0.15, position.y);
	auto rad = (p2.x - p.x)*(1+diff*1);
	int alpha = min(128, max(0, (128 - 128 * diff*2)));

	sf::CircleShape C;
	C.setFillColor(sf::Color::Transparent);
	C.setOutlineColor(sf::Color(32, 80, 225, alpha));
	C.setOutlineThickness(rad+rad*diff*2);
	C.setPosition(p - sf::Vector2f(rad, rad));
	C.setRadius(rad);
	sf::BlendMode additiveBlending = sf::BlendAdd;
	g_Window->draw(C,additiveBlending);
}

void dc_shieldbreakeffect::draw(sf::RenderTexture* T,float mx, float my, float width, float servertime)
{
	float diff = servertime - clockBegin;


	auto p = dc_map::world_to_screen(mx, my, width, position.x, position.y);
	auto p2 = dc_map::world_to_screen(mx, my, width, position.x + 0.15, position.y);
	auto rad = (p2.x - p.x)*(1 + diff * 1);
	int alpha = min(128, max(0, (128 - 128 * diff * 2)));

	sf::CircleShape C;
	C.setFillColor(sf::Color::Transparent);
	C.setOutlineColor(sf::Color(32, 80, 225, alpha));
	C.setOutlineThickness(rad + rad*diff * 2);
	C.setPosition(p - sf::Vector2f(rad, rad));
	C.setRadius(rad);

	sf::BlendMode additiveBlending = sf::BlendAdd;
	T->draw(C,additiveBlending);
}

void dc_shoteffect::draw(float mx, float my, float width, float ServerTime)
{
	float diff = ServerTime-clockBegin;
	auto sp= dc_map::world_to_screen(mx, my, width, start.x, start.y);
	auto ep = dc_map::world_to_screen(mx, my, width, end.x, end.y);
	int alpha = min(255, 255 * 1.5*(0.5f - diff) / 0.5f);

	sf::Vertex vert[] = { sf::Vertex(sp,sf::Color(255,192,64,alpha),sf::Vector2f()),
		sf::Vertex(ep,sf::Color(255,64,64,alpha),sf::Vector2f()) };
	g_Window->draw(vert, 2, sf::PrimitiveType::Lines);
}

void dc_shoteffect::draw(sf::RenderTexture*T,float mx, float my, float width, float ServerTime)
{
	float diff = ServerTime - clockBegin;
	auto sp = dc_map::world_to_screen(mx, my, width, start.x, start.y);
	auto ep = dc_map::world_to_screen(mx, my, width, end.x, end.y);
	int alpha = min(255, 255 * 1.5*(0.5f - diff) / 0.5f);

	sf::Vertex vert[] = { sf::Vertex(sp,sf::Color(255,192,64,alpha),sf::Vector2f()),
		sf::Vertex(ep,sf::Color(255,64,64,alpha),sf::Vector2f()) };
	T->draw(vert, 2, sf::PrimitiveType::Lines);
}

void dc_killnoticeeffect::draw(float y, int cfollows, float y2, float ServerTime)
{
	float diff = ServerTime-clockBegin;
	int alpha = 255;
	if (diff >= 4.f)
	{
		alpha = 255 - (diff - 4.f) * 255;
	}
	_Window::RenderTextB(0.0234375*g_Resolution.x, g_Resolution.y*0.6f + y, message, g_Resolution.y*0.02f, 255, 255, 255, alpha);
	return;
	if (cfollows == Killer)
	{
		


		char BufferA[64] = "Eliminated ", BufferB[64];
		char BufferC[64];
		sprintf(BufferB, "%d", Target);
		sprintf(BufferC, "Eliminated %d");

		auto Dims = _Window::GetTextSize(BufferC, g_Resolution.y * 0.03f);
		auto Dims2 = _Window::GetTextSize(BufferA, g_Resolution.y * 0.03f);
		_Window::RenderTextB(g_Resolution.x*0.5f-Dims.x*0.5f, g_Resolution.y*0.7f + y2, BufferA, g_Resolution.y*0.03f, 222, 222, 222, alpha);
		_Window::RenderTextB(g_Resolution.x*0.5f - Dims.x* 0.5f+Dims2.x, g_Resolution.y*0.7f + y2, BufferB, g_Resolution.y*0.03f, 225, 180, 32, alpha);

	}
}

void dc_deatheffect::draw(float mx, float my, float width, float ServerTime)
{
	float deathTime = 0.75f;

	auto p = dc_map::world_to_screen(mx, my, width, position.x, position.y);
	sf::Vector2f blocksize((float)(g_Resolution.x) / width, (float)(g_Resolution.x) / width);
	float scale = blocksize.x / 128;

	float diff = ServerTime-clockBegin;

	static sf::Sprite sp;
	static bool run = false;
	if (!run)
	{
		sp.setTexture(*g_Textures.get(3));
		run = true;
	}


	int tex_height = max(0, 64 - diff * (64.f/deathTime));
	sp.setOrigin(32, 32);
	sp.setTextureRect(sf::IntRect(64 + iTexture * 64, 0, 64, tex_height));
	sp.setPosition(p);
	sp.setScale(scale, scale);
	sp.setRotation(-fRotation+90.f);


	int Alpha = 255 - diff * (255.f/deathTime);
	sp.setColor(sf::Color(255, 255, 255, Alpha));
	g_Window->draw(sp);

	Alpha = diff * (255.f/deathTime);
	sp.setColor(sf::Color(255, 255, 255, Alpha));
	sf::BlendMode additiveBlending = sf::BlendAdd;
	g_Window->draw(sp, additiveBlending);


	Alpha = 255 - diff * (255.f / deathTime);
	sp.setColor(sf::Color(255, 255, 255, Alpha));
	sp.setTextureRect(sf::IntRect(0, 0, 64, tex_height));
	g_Window->draw(sp);
}

void dc_deatheffect::draw(sf::RenderTexture*T,float mx, float my, float width, float ServerTime)
{
	float deathTime = 0.75f;

	auto p = dc_map::world_to_screen(mx, my, width, position.x, position.y);
	sf::Vector2f blocksize((float)(g_Resolution.x) / width, (float)(g_Resolution.x) / width);
	float scale = blocksize.x / 128;

	float diff = ServerTime - clockBegin;

	static sf::Sprite sp;
	static bool run = false;
	if (!run)
	{
		sp.setTexture(*g_Textures.get(3));
		run = true;
	}


	int tex_height = max(0, 64 - diff * (64.f / deathTime));
	sp.setOrigin(32, 32);
	sp.setTextureRect(sf::IntRect(64 + iTexture * 64, 0, 64, tex_height));
	sp.setPosition(p);
	sp.setScale(scale, scale);
	sp.setRotation(-fRotation + 90.f);


	int Alpha = 255 - diff * (255.f / deathTime);
	sp.setColor(sf::Color(255, 255, 255, Alpha));
	T->draw(sp);

	Alpha = diff * (255.f / deathTime);
	sp.setColor(sf::Color(255, 255, 255, Alpha));
	sf::BlendMode additiveBlending = sf::BlendAdd;
	T->draw(sp, additiveBlending);


	Alpha = 255 - diff * (255.f / deathTime);
	sp.setColor(sf::Color(255, 255, 255, Alpha));
	sp.setTextureRect(sf::IntRect(0, 0, 64, tex_height));
	T->draw(sp);
}

void dc_airdropeffect::draw(float ServerTime)
{
	float d = ServerTime - clockBegin;

	int fontsize = g_Resolution.x*0.03f;
	float textlen = _Window::GetTextSize("AIR DROP INCOMING", fontsize).x;
	float textheight = _Window::GetHeightForFontsize(fontsize);
	float blocklen = textlen + g_Resolution.x*0.05f;
	float blockheight = textheight + g_Resolution.y*0.01f;
	int alphaBlock = 128;
	int alphaText = 255;

	if (d < 0.5f)
	{
		blocklen = 2 * d*blocklen;
		alphaBlock = d * 255;
	}
	if (d > 2.5f)
	{
		blocklen = 2 * (3.f - d)*blocklen;
		alphaBlock = (3.f - d) * 255;
	}

	_Window::RenderOverlay(0.5f*(g_Resolution.x - blocklen), g_Resolution.y*0.05f, blocklen, blockheight, 255, 255, 255, alphaBlock);

	if (d > 0.5f && d < 2.5f)
	{
		if (d < 1.f)
		{
			alphaText= (d-0.5f) * 510;
		}
		if (d > 2.f)
		{
			alphaText = (2.5f-d) * 510;
		}

		_Window::RenderTextB(0.5f*(g_Resolution.x - textlen), g_Resolution.y*0.055f, "AIR DROP INCOMING", fontsize, 0, 0, 0, alphaText);


	}

	




}

void dc_stormclosingeffect::draw(float ServerTime)
{
	float d = ServerTime - clockBegin;
	if (d > 3.f)return;
	int fontsize = g_Resolution.x*0.03f;
	float textlen = _Window::GetTextSize("STORM CLOSING", fontsize).x;
	float textheight = _Window::GetHeightForFontsize(fontsize);
	float blocklen = textlen + g_Resolution.x*0.05f;
	float blockheight = textheight + g_Resolution.y*0.01f;
	int alphaBlock = 128;
	int alphaText = 255;

	if (d < 0.5f)
	{
		blocklen = 2 * d*blocklen;
		alphaBlock = d * 255;
	}
	if (d > 2.5f)
	{
		blocklen = 2 * (3.f - d)*blocklen;
		alphaBlock = (3.f - d) * 255;
	}

	_Window::RenderOverlay(0.5f*(g_Resolution.x - blocklen), g_Resolution.y*0.05f, blocklen, blockheight, 255, 255, 255, alphaBlock);

	if (d > 0.5f && d < 2.5f)
	{
		if (d < 1.f)
		{
			alphaText = (d - 0.5f) * 510;
		}
		if (d > 2.f)
		{
			alphaText = (2.5f - d) * 510;
		}

		_Window::RenderTextB(0.5f*(g_Resolution.x - textlen), g_Resolution.y*0.055f, "STORM CLOSING", fontsize, 0, 0, 0, alphaText);


	}






}

void dc_globalquestdoneeffect::draw()
{
	float diff = 0.001f*Clock.deltaTime();

	float DefOverlayAlpha = 128;
	if (diff < 0.25f)DefOverlayAlpha = diff * 512;
	else if (diff > 2.75)DefOverlayAlpha = (3.f - diff) * 512;

	_Window::RenderOverlay(0, 0, g_Resolution.x, g_Resolution.y, 0, 0, 0, DefOverlayAlpha);



	char Buffer[256];
	sprintf(Buffer, Quest.questName);
	


	float newprogress = max(0.f, min(1.f, (diff - 0.5) / 1.25f));
	float underprogress = max(0.f, min(1.f, (diff - 0.5) / 1.25f - 0.125));
	float ChScale = 1.f;
	if (diff >= 0.25f && diff <= 0.5f)ChScale = 1.f + (0.5f - diff) * 4.f;
	int ChAlpha = 255;
	if (diff >= 0.25f && diff <= 0.5f)ChAlpha = 255 + (diff - 0.5f) * 255 * 4;
	if (diff < 0.25f || diff > 2.75f)ChAlpha = 0;
	if (diff >= 2.5f && diff < 2.75f)ChAlpha = 255 - (diff - 2.5f) * 255 * 4;


	auto x = g_Resolution.x*0.25f;
	auto y = g_Resolution.y*0.4f;
	auto w = g_Resolution.x*0.5f;
	auto h = g_Resolution.y*0.2f;

	int fontsize = g_Resolution.y*(0.1f*w / (g_Resolution.x));


	auto lineheight = _Window::GetHeightForFontsize(fontsize);
	auto texH = 1*lineheight;
	h = max(h, texH);

	auto BufLength = _Window::GetTextSize(Buffer, fontsize);
	int tier = 5;
	if (tier == 5)
	{
		_Window::RenderOverlay(x - (ChScale - 1)*w, y - (ChScale - 1)*(g_Resolution.y*0.005f + 18), ChScale*w, ChScale*(h + g_Resolution.y*0.005f + 18), 32, 32, 128, ChAlpha);
		_Window::RenderOverlay(x - (ChScale - 1)*(w*0.0125f), y - (ChScale - 1)*(h + g_Resolution.y*0.005f + 18), ChScale*w*0.0125f, ChScale*(h + g_Resolution.y*0.005f + 18), 64, 64, 255, ChAlpha);
		_Window::RenderTextB(x + 0.02631*w - (ChScale - 1)*BufLength.x, y - (ChScale - 1)*(g_Resolution.y*0.005f + 10), Buffer, fontsize, 255, 255, 255, ChAlpha);


		char ProgressBuffer[16];
		sprintf(ProgressBuffer, "FINISHED");
		int leee = _Window::GetTextSize(ProgressBuffer, fontsize).x;

		_Window::RenderTextB(x + 0.97368421052*w - leee, y + h + 0.005f*g_Resolution.y - lineheight, ProgressBuffer, fontsize, 255, 255, 255, max(0, min(ChAlpha, (diff - 1.7f) * 510)));

		_Window::RenderOverlay(x + 0.02631*w - (ChScale - 1)*0.9473f*w, y + h + 0.005f*g_Resolution.y + (ChScale - 1) * 8, (ChScale)*0.9473f*w, ChScale * 8, 0, 0, 0, ChAlpha);
		_Window::RenderOverlay(x + 0.02631*w, y + h + 0.005f*g_Resolution.y + 1, ChScale*newprogress*(0.9473f*w - 2), 6, 0, 177, 222, ChAlpha);

		_Window::RenderOverlay(x + 0.02631*w + ChScale*underprogress*(0.9473f*w - 2), y + h + 0.005f*g_Resolution.y + 1, ChScale*(newprogress - underprogress)*(0.9473f*w - 2), 6, 64, 222, 255, ChAlpha);

	}
	else if (tier == 10)
	{
		_Window::RenderOverlay(x - (ChScale - 1)*w, y - (ChScale - 1)*(g_Resolution.y*0.005f + 18), ChScale*w, ChScale*(h + g_Resolution.y*0.005f + 18), 128, 32, 32, ChAlpha);
		_Window::RenderOverlay(x - (ChScale - 1)*(w*0.0125f), y - (ChScale - 1)*(h + g_Resolution.y*0.005f + 18), ChScale*w*0.0125f, ChScale*(h + g_Resolution.y*0.005f + 18), 255, 64, 64, ChAlpha);
		_Window::RenderTextB(x + 0.02631*w - (ChScale - 1)*BufLength.x, y - (ChScale - 1)*(g_Resolution.y*0.005f + 10), Buffer, fontsize, 255, 255, 255, ChAlpha);

		char ProgressBuffer[16];
		sprintf(ProgressBuffer, "FINISHED");
		int leee = _Window::GetTextSize(ProgressBuffer, fontsize).x;

		_Window::RenderTextB(x + 0.97368421052*w - leee, y + h + 0.005f*g_Resolution.y - lineheight, ProgressBuffer, fontsize, 255, 255, 255, max(0, min(ChAlpha, (diff - 1.7f) * 510)));

		_Window::RenderOverlay(x + 0.02631*w - (ChScale - 1)*0.9473f*w, y + h + 0.005f*g_Resolution.y + (ChScale - 1) * 8, (ChScale)*0.9473f*w, ChScale * 8, 0, 0, 0, ChAlpha);
		_Window::RenderOverlay(x + 0.02631*w, y + h + 0.005f*g_Resolution.y + 1, ChScale*newprogress*(0.9473f*w - 2), 6, 225, 128, 32, ChAlpha);

		_Window::RenderOverlay(x + 0.02631*w + ChScale*underprogress*(0.9473f*w - 2), y + h + 0.005f*g_Resolution.y + 1, ChScale*(newprogress - underprogress)*(0.9473f*w - 2), 6, 255, 210, 64, ChAlpha);

	}

	if (g_Sounds.CheckDynamicSound(555) == -1 && diff < 0.5f)
	{
		g_Sounds.AddNewDynamicSound(555, 39, 10000, sf::Vector2f(0, 0), g_Config.mastervolume.Value, sf::Vector2f(0, 0), 0.f, 0.16f);
	}
}

void dc_questdoneeffect::draw()
{
	float diff = 0.001f*Clock.deltaTime();

	float DefOverlayAlpha = 128;
	if (diff < 0.25f)DefOverlayAlpha = diff * 512;
	else if (diff > 2.75)DefOverlayAlpha = (3.f - diff) * 512;

	_Window::RenderOverlay(0, 0, g_Resolution.x, g_Resolution.y, 0, 0, 0, DefOverlayAlpha);

	

	char Buffer[256];
	int ChallengeNameLines = 1;
	if (Quest.type == 0 || Quest.type == 1)
	{
		if (Quest.killweapontype == 0)sprintf(Buffer, "Eliminations");
		else if (Quest.killweapontype == 1)sprintf(Buffer, "Pistol eliminations");
		else if (Quest.killweapontype == 2)sprintf(Buffer, "SMG eliminations");
		else if (Quest.killweapontype == 3)sprintf(Buffer, "Shotgun eliminations");
		else if (Quest.killweapontype == 4)sprintf(Buffer, "Rifle eliminations");
		else if (Quest.killweapontype == 5)sprintf(Buffer, "Sniper eliminations");
		else if (Quest.killweapontype == 6)sprintf(Buffer, "Explosive eliminations");
		else if (Quest.killweapontype == 7)sprintf(Buffer, "Machine gun eliminations");

		if (Quest.oneMatch)sprintf(Buffer, "%s in one match", Buffer);

		if (Quest.type == 1) {
			char MiniBuffer[64];
			for (int j = 0; j < strlen(g_Map.labels[Quest.location1].n); j++)
			{
				if (g_Map.labels[Quest.location1].n[j] == '\n') {
					MiniBuffer[j] = ' ';
					MiniBuffer[j + 1] = '\0';
				}
				else {
					MiniBuffer[j] = g_Map.labels[Quest.location1].n[j];
					MiniBuffer[j + 1] = '\0';
				}
			}

			sprintf(Buffer, "%s\n%s", Buffer, MiniBuffer);
			ChallengeNameLines++;
		}
	}
	else if (Quest.type == 2 || Quest.type == 3)
	{
		sprintf(Buffer, "Open chests");
		if (Quest.oneMatch)sprintf(Buffer, "%s in one match", Buffer);

		if (Quest.type == 3) {
			char MiniBuffer[64];
			for (int j = 0; j < strlen(g_Map.labels[Quest.location1].n); j++)
			{
				if (g_Map.labels[Quest.location1].n[j] == '\n') {
					MiniBuffer[j] = ' ';
					MiniBuffer[j + 1] = '\0';
				}
				else {
					MiniBuffer[j] = g_Map.labels[Quest.location1].n[j];
					MiniBuffer[j + 1] = '\0';
				}
			}

			sprintf(Buffer, "%s\n%s", Buffer, MiniBuffer);
			ChallengeNameLines++;
		}
	}
	else if (Quest.type == 4)
	{
		char MiniBuffer[64];
		for (int j = 0; j < strlen(g_Map.labels[Quest.location1].n); j++)
		{
			if (g_Map.labels[Quest.location1].n[j] == '\n') {
				MiniBuffer[j] = ' ';
				MiniBuffer[j + 1] = '\0';
			}
			else {
				MiniBuffer[j] = g_Map.labels[Quest.location1].n[j];
				MiniBuffer[j + 1] = '\0';
			}
		}

		sprintf(Buffer, "Land at %s", MiniBuffer);
	}
	else if (Quest.type == 5)
	{
		sprintf(Buffer, "Visit");
		if (Quest.oneMatch)sprintf(Buffer, "%s in one match", Buffer);


		char MiniBuffer[64];
		if (Quest.location1 != -1)
		{
			for (int j = 0; j < strlen(g_Map.labels[Quest.location1].n); j++)
			{
				if (g_Map.labels[Quest.location1].n[j] == '\n') {
					MiniBuffer[j] = ' ';
					MiniBuffer[j + 1] = '\0';
				}
				else {
					MiniBuffer[j] = g_Map.labels[Quest.location1].n[j];
					MiniBuffer[j + 1] = '\0';
				}
			}
			sprintf(Buffer, "%s\n%s", Buffer, MiniBuffer);
			ChallengeNameLines++;
		}
		if (Quest.location2 != -1)
		{
			for (int j = 0; j < strlen(g_Map.labels[Quest.location2].n); j++)
			{
				if (g_Map.labels[Quest.location2].n[j] == '\n') {
					MiniBuffer[j] = ' ';
					MiniBuffer[j + 1] = '\0';
				}
				else {
					MiniBuffer[j] = g_Map.labels[Quest.location2].n[j];
					MiniBuffer[j + 1] = '\0';
				}
			}
			sprintf(Buffer, "%s\n%s", Buffer, MiniBuffer);
			ChallengeNameLines++;
		}

		if (Quest.location3 != -1)
		{
			for (int j = 0; j < strlen(g_Map.labels[Quest.location3].n); j++)
			{
				if (g_Map.labels[Quest.location3].n[j] == '\n') {
					MiniBuffer[j] = ' ';
					MiniBuffer[j + 1] = '\0';
				}
				else {
					MiniBuffer[j] = g_Map.labels[Quest.location3].n[j];
					MiniBuffer[j + 1] = '\0';
				}
			}
			sprintf(Buffer, "%s\n%s", Buffer, MiniBuffer);
			ChallengeNameLines++;
		}

	}
	else if (Quest.type == 6)sprintf(Buffer, "Place top 10");
	else if (Quest.type == 7)sprintf(Buffer, "Place top 25");



	float newprogress = max(0.f,min(1.f, (diff - 0.5) / 1.25f));
	float underprogress = max(0.f, min(1.f, (diff - 0.5) / 1.25f-0.125));
	float ChScale = 1.f;
	if (diff >= 0.25f && diff <= 0.5f)ChScale = 1.f + (0.5f - diff) * 4.f;
	int ChAlpha = 255;
	if (diff >= 0.25f && diff <= 0.5f)ChAlpha = 255 + (diff-0.5f) * 255*4;
	if (diff < 0.25f || diff > 2.75f)ChAlpha = 0;
	if (diff >= 2.5f && diff < 2.75f)ChAlpha = 255 - (diff - 2.5f) * 255 * 4;
	int tier = Quest.tierReward;
	

	auto x = g_Resolution.x*0.25f;
	auto y = g_Resolution.y*0.4f;
	auto w = g_Resolution.x*0.5f;
	auto h = g_Resolution.y*0.2f;

	int fontsize = g_Resolution.y*(0.1f*w / (g_Resolution.x));


	auto lineheight = _Window::GetHeightForFontsize(fontsize);
	auto texH = ChallengeNameLines*lineheight;
	h = max(h, texH);

	auto BufLength = _Window::GetTextSize(Buffer, fontsize);
	if (tier == 5)
	{
		_Window::RenderOverlay(x-(ChScale-1)*w, y-(ChScale-1)*(g_Resolution.y*0.005f + 18), ChScale*w, ChScale*(h + g_Resolution.y*0.005f + 18), 32, 32, 128, ChAlpha);
		_Window::RenderOverlay(x-(ChScale-1)*(w*0.0125f), y-(ChScale-1)*(h + g_Resolution.y*0.005f + 18), ChScale*w*0.0125f, ChScale*(h + g_Resolution.y*0.005f + 18), 64, 64, 255, ChAlpha);
		_Window::RenderTextB(x + 0.02631*w-(ChScale-1)*BufLength.x, y- (ChScale - 1)*(g_Resolution.y*0.005f + 10), Buffer, fontsize,255,255,255, ChAlpha);


		char ProgressBuffer[16];
		sprintf(ProgressBuffer, "FINISHED");
		int leee = _Window::GetTextSize(ProgressBuffer, fontsize).x;

		_Window::RenderTextB(x + 0.97368421052*w - leee, y + h + 0.005f*g_Resolution.y - lineheight, ProgressBuffer, fontsize,255,255,255,max(0,min(ChAlpha,(diff-1.7f)*510)));

		_Window::RenderOverlay(x + 0.02631*w-(ChScale-1)*0.9473f*w, y + h + 0.005f*g_Resolution.y+(ChScale-1)*8, (ChScale)*0.9473f*w, ChScale*8, 0, 0, 0, ChAlpha);
		_Window::RenderOverlay(x + 0.02631*w, y + h + 0.005f*g_Resolution.y + 1, ChScale*newprogress*(0.9473f*w - 2), 6, 0, 177, 222, ChAlpha);
		
		_Window::RenderOverlay(x + 0.02631*w+ ChScale*underprogress*(0.9473f*w - 2), y + h + 0.005f*g_Resolution.y + 1, ChScale*(newprogress-underprogress)*(0.9473f*w - 2), 6, 64, 222, 255, ChAlpha);
	
	}
	else if (tier == 10)
	{
		_Window::RenderOverlay(x - (ChScale - 1)*w, y - (ChScale - 1)*(g_Resolution.y*0.005f + 18), ChScale*w, ChScale*(h + g_Resolution.y*0.005f + 18), 128,32,32, ChAlpha);
		_Window::RenderOverlay(x - (ChScale - 1)*(w*0.0125f), y - (ChScale - 1)*(h + g_Resolution.y*0.005f + 18), ChScale*w*0.0125f, ChScale*(h + g_Resolution.y*0.005f + 18), 255,64,64, ChAlpha);
		_Window::RenderTextB(x + 0.02631*w - (ChScale - 1)*BufLength.x, y - (ChScale - 1)*(g_Resolution.y*0.005f + 10), Buffer, fontsize, 255, 255, 255, ChAlpha);

		char ProgressBuffer[16];
		sprintf(ProgressBuffer, "FINISHED");
		int leee = _Window::GetTextSize(ProgressBuffer, fontsize).x;

		_Window::RenderTextB(x + 0.97368421052*w - leee, y + h + 0.005f*g_Resolution.y - lineheight, ProgressBuffer, fontsize, 255, 255, 255, max(0, min(ChAlpha, (diff - 1.7f) * 510)));

		_Window::RenderOverlay(x + 0.02631*w - (ChScale - 1)*0.9473f*w, y + h + 0.005f*g_Resolution.y + (ChScale - 1) * 8, (ChScale)*0.9473f*w, ChScale * 8, 0, 0, 0, ChAlpha);
		_Window::RenderOverlay(x + 0.02631*w, y + h + 0.005f*g_Resolution.y + 1, ChScale*newprogress*(0.9473f*w - 2), 6, 225,128,32, ChAlpha);

		_Window::RenderOverlay(x + 0.02631*w + ChScale*underprogress*(0.9473f*w - 2), y + h + 0.005f*g_Resolution.y + 1, ChScale*(newprogress - underprogress)*(0.9473f*w - 2), 6, 255,210,64, ChAlpha);

	}

	if (g_Sounds.CheckDynamicSound(555) == -1 && diff < 0.5f)
	{
		g_Sounds.AddNewDynamicSound(555, 39, 10000, sf::Vector2f(0,0), g_Config.mastervolume.Value, sf::Vector2f(0,0), 0.f, 0.16f);
	}
}


void dc_lockergoteffect::draw()
{
	static sf::Sprite spPl, spGl, spWW;
	spPl.setTexture(*g_Textures.get(3));
	spGl.setTexture(*g_Textures.get(68));
	spWW.setTexture(*g_Textures.get(53));

	auto pointer = (dc_lockerunlockable*)lockerUnlockable;

	float diff = 0.001f*Clock.deltaTime();

	float DefOverlayAlpha = 128;
	if (diff < 0.25f)DefOverlayAlpha = diff * 512;
	else if (diff > 2.75)DefOverlayAlpha = (3.f - diff) * 512;

	_Window::RenderOverlay(0, 0, g_Resolution.x, g_Resolution.y, 0, 0, 0, DefOverlayAlpha);

	//Sphere
	float rot = 120.f*(diff / 3.f);
	int alphaSp = 255;
	if (diff < 0.25f || diff > 2.75f)alphaSp = 0;
	if (diff >= 0.25f && diff < 0.5f)alphaSp = (diff - 0.25f) * 1020;
	if (diff >= 2.5f && diff <= 2.75f)alphaSp = -(diff - 2.75f) * 1020;

	std::vector<sf::Vertex> VertArray;
	static sf::Color raritieses[] = { sf::Color(255,255,255,128),sf::Color(90, 180, 0, 170),sf::Color(60, 190, 250, 200),sf::Color(200, 105, 235, 255),sf::Color(240, 150, 40, 255), sf::Color(255,32,32,255) };
	sf::Color rarities = raritieses[pointer->iRarity];
	auto color = sf::Color(rarities.r, rarities.g, rarities.b, (1.f / 255.f)*alphaSp*rarities.a);
	VertArray.push_back(sf::Vertex(sf::Vector2f(0.5f*g_Resolution.x, 0.5f*g_Resolution.y), color, sf::Vector2f()));

	int sprAlpha = 255;
	if (diff < 0.5f || diff >2.5f)sprAlpha = 0;
	if (diff >= 0.5f && diff < 0.75f)sprAlpha = (diff - 0.5f) * 1020;
	if (diff >= 2.25f && diff < 2.5f)sprAlpha = -(diff - 2.5f) * 1020;

	spPl.setColor(sf::Color(255, 255, 255, sprAlpha));
	spGl.setColor(sf::Color(255, 255, 255, sprAlpha));
	spWW.setColor(sf::Color(255, 255, 255, sprAlpha));
	for (int i = 0; i <= 360; i++)
	{
		int mod = i % 30;
		int modLow = i - mod;
		int modHigh = i - mod+30;
		int modDiff = min(abs(i - modLow), abs(i - modHigh));

		float length = g_Resolution.y*0.4f+modDiff*g_Resolution.y*0.01f;
		auto dVec = angle2vec(i+rot);

		VertArray.push_back(sf::Vertex(sf::Vector2f(0.5f*g_Resolution.x, 0.5f*g_Resolution.y)+length*dVec, sf::Color(255,255,255,0), sf::Vector2f()));
	}

	sf::BlendMode addBlend = sf::BlendAdd;
	g_Window->draw(&VertArray[0], VertArray.size(), sf::TriangleFan, addBlend);


	if (pointer->Type == 0)
	{
		float scale = g_Resolution.y*0.4f / 64.f;
		spPl.setScale(scale, scale);
		spPl.setTextureRect(sf::IntRect(64 + 64 * pointer->Index, 0, 64, 64));
		spPl.setOrigin(32, 32);
		spPl.setPosition(sf::Vector2f(0.5f*g_Resolution.x, 0.5f*g_Resolution.y));
		g_Window->draw(spPl);
		spPl.setTextureRect(sf::IntRect(0, 0, 64, 64));
		g_Window->draw(spPl);
	}
	if (pointer->Type == 1)
	{
		float scale = g_Resolution.y*0.4f / 128.f;


		spGl.setScale(scale, scale);
		spGl.setTextureRect(sf::IntRect(128 * pointer->Index, 0, 128,128));
		spGl.setPosition(sf::Vector2f(0.5f*g_Resolution.x, 0.5f*g_Resolution.y));
		spGl.setOrigin(64,64);
		g_Window->draw(spGl);
	}
	else if (pointer->Type == 2)
	{
		float scale = g_Resolution.y*0.4f / 96.f;
		
		spWW.setScale(scale, scale);
		spWW.setTextureRect(sf::IntRect(0, 96*pointer->Index, 96,96));
		spWW.setPosition(sf::Vector2f(0.5f*g_Resolution.x, 0.5f*g_Resolution.y));
		spWW.setOrigin(48,48);
		g_Window->draw(spWW);
		
		spPl.setScale(scale, scale);
		spPl.setTextureRect(sf::IntRect(64, 0, 64, 64));
		spPl.setOrigin(32, 32);
		spPl.setPosition(sf::Vector2f(0.5f*g_Resolution.x, 0.5f*g_Resolution.y));
		g_Window->draw(spPl);
		spPl.setTextureRect(sf::IntRect(0, 0, 64, 64));
		g_Window->draw(spPl);

	}

	if (g_Sounds.CheckDynamicSound(556) == -1 && diff < 0.5f)
	{
		g_Sounds.AddNewDynamicSound(556, 39, 10000, sf::Vector2f(0, 0), g_Config.mastervolume.Value, sf::Vector2f(0, 0), 0.f, 0.16f);
	}
}

void dc_game::RemoveExpiredEffects()
{
	for (int i = Effects.QD_Effects.size() - 1; i >= 0; i--)
		if (Effects.QD_Effects[i].Clock.deltaTime() > 3000)Effects.QD_Effects.erase(Effects.QD_Effects.begin() + i);
	for (int i = Effects.GQD_Effects.size() - 1; i >= 0; i--)
		if (Effects.GQD_Effects[i].Clock.deltaTime() > 3000)Effects.GQD_Effects.erase(Effects.GQD_Effects.begin() + i);
	for (int i = Effects.LG_Effects.size() - 1; i >= 0; i--)
		if (Effects.LG_Effects[i].Clock.deltaTime() > 3000)Effects.LG_Effects.erase(Effects.LG_Effects.begin() + i);




}

int dc_game::TotalEffectCount()
{
	int R = 0;
	for (int i = Effects.GQD_Effects.size() - 1; i >= 0; i--)
		R++;
	for (int i = Effects.QD_Effects.size() - 1; i >= 0; i--)
		R++;
	for (int i = Effects.LG_Effects.size() - 1; i >= 0; i--)
		R++;
	return R;
}

void dc_game::DrawEffects()
{
	RemoveExpiredEffects();
	bool drawing = false;
	for (int i = 0; i < Effects.GQD_Effects.size(); i++)
	{
		if (drawing)Effects.GQD_Effects[i].Clock.Update();
		else { Effects.GQD_Effects[i].draw(); drawing = true; }
	}
	for (int i = 0; i < Effects.QD_Effects.size(); i++)
	{
		if (drawing)Effects.QD_Effects[i].Clock.Update();
		else { Effects.QD_Effects[i].draw(); drawing = true; }
	}
	for (int i = 0; i < Effects.LG_Effects.size(); i++)
	{
		if (drawing)Effects.LG_Effects[i].Clock.Update();
		else { Effects.LG_Effects[i].draw(); drawing = true; }
	}
}