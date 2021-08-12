#include "DaiCastle.h"

dc_textures g_Textures;

void dc_textures::add(char* n)
{
	auto f = g_Files.GetFileByName(n);

	sf::Texture tex;
	tex.loadFromMemory(f.loc_in_mem, f.size);
	t.push_back(tex);


	auto img = tex.copyToImage();
	auto img_siz = img.getSize();
	

	int64_t R = 0, G = 0, B = 0, A = 0;

	if(img_siz.x < 512 && img_siz.y < 512)
	for (int x = 0; x < img_siz.x; x++)
	{
		for (int y = 0; y < img_siz.y; y++)
		{
			auto pixel = img.getPixel(x, y);
			R += pixel.r;
			G += pixel.g;
			B += pixel.b;
			A += pixel.a;
		}
	}
	R /= (img_siz.x*img_siz.y);
	G /= (img_siz.x*img_siz.y);
	B /= (img_siz.x*img_siz.y);
	A /= (img_siz.x*img_siz.y);


	ac.push_back(sf::Color(R, G, B, A));

	nam.push_back(n);

	printf("\n%s added to the textures", n);
}

sf::Texture* dc_textures::get(int id)
{
	return &t[id];
}

char* dc_textures::getname(int id)
{
	return nam[id];
}

sf::Color dc_textures::getavgcolor(int id)
{
	return ac[id];
}

void dc_textures::define_all()
{
	g_Textures.add("t_grs.png"); //0 //
	g_Textures.add("t_wdpl_h.png"); //
	g_Textures.add("t_wdpl_v.png"); //
	g_Textures.add("dballs.png");
	g_Textures.add("chest.png");
	g_Textures.add("weaponsNew.png"); //5
	g_Textures.add("t_wtr.png"); 
	g_Textures.add("t_rck.png"); //
	g_Textures.add("t_boxx.png"); //
	g_Textures.add("t_drt.png"); //
	
	g_Textures.add("t_blk_cncrt.png"); //10 //
	g_Textures.add("t_white_cncrt.png"); //
	g_Textures.add("t_til_cncrt.png"); //
	g_Textures.add("t_snd.png"); //
	g_Textures.add("t_snow.png"); //
	g_Textures.add("t_til_1.png"); //15 //
	g_Textures.add("t_til_2.png"); //
	g_Textures.add("t_til_3.png");//
	g_Textures.add("t_tile_4.png");//
	g_Textures.add("t_wdpl_h2.png");//
	
	g_Textures.add("t_wdpl_v2.png"); //20
	g_Textures.add("t_wdpl_h3.png");  //
	g_Textures.add("t_wdpl_v3.png");//
	g_Textures.add("t_wdpl_h4.png");//
	g_Textures.add("t_wdpl_v4.png");//
	g_Textures.add("t_grs_2.png"); //25 //
	g_Textures.add("t_grs_3.png"); //
	g_Textures.add("t_grs_4.png");//
	g_Textures.add("t_grs_5.png");//
	g_Textures.add("t_water_safe.png"); //
	
	g_Textures.add("t_treelike.png"); //30 //
	g_Textures.add("t_fakegrass.png"); //
	g_Textures.add("t_sndway.png"); //
	g_Textures.add("t_til_5.png"); //
	g_Textures.add("t_til_6.png"); //
	g_Textures.add("t_yel_cncrt.png"); //35 //
	g_Textures.add("t_brk_1a.png"); //
	g_Textures.add("t_brk_1b.png"); //
	g_Textures.add("t_brk_2a.png"); //
	g_Textures.add("t_brk_2b.png"); //
	
	g_Textures.add("t_brk_3a.png"); //40 //
	g_Textures.add("t_brk_3b.png"); //
	g_Textures.add("t_brk_4a.png"); //
	g_Textures.add("t_brk_4b.png"); //
	g_Textures.add("t_wheat.png"); //
	g_Textures.add("t_cnt_1.png"); //45
	g_Textures.add("t_cnt_2.png");
	g_Textures.add("t_cnt_3.png");
	g_Textures.add("t_cnt_4.png");
	g_Textures.add("t_snway.png");
	
	g_Textures.add("battlebus.png"); //50
	g_Textures.add("logos.png");
	g_Textures.add("explos.png");
	g_Textures.add("ballweapons.png");
	g_Textures.add("dcbackground.png");
	g_Textures.add("cloud1.png"); //55
	g_Textures.add("cloud2.png");
	g_Textures.add("cloud3.png");
	g_Textures.add("cloud4.png");
	g_Textures.add("t_mtl.png");

	g_Textures.add("t_rck2.png"); //60
	g_Textures.add("t_rck3.png"); 
	g_Textures.add("t_snd2.png");
	g_Textures.add("t_snd3.png");
	g_Textures.add("t_snw_treelike.png");
	g_Textures.add("t_snw2.png"); //65
	g_Textures.add("t_snw3.png");
	g_Textures.add("airdrop.png");
	g_Textures.add("glider.png");
}