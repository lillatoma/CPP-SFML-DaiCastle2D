#pragma once

#include "DaiCastle.h"

struct dcn_map
{
	std::vector<dc_blockline> lines;
	std::vector<dc_chest> chests;
	std::vector<dc_item> items; //onground;
	std::vector<dc_label> labels;


	sf::Vector2i size;


	int day_time = 0;


	void simulate_day();
	sf::Color get_modulation_color();
	float get_shadow_angle();
	float get_shadow_length();


	void define(int sx, int sy);
	void draw(float mx, float my, float width);
	void beginshadows(float mx, float my, float width);

	void drawitems(float mx, float my, float width);

	void delete_items();
	void mark_for_delete(dc_item it);
	int get_item_id(dc_item it);

	void begin_lines();
	void update_lines();
	void delete_line(sf::Vector2f s, sf::Vector2f e, int typ);

	void load(char* n);

	void show_minimap(float &mx, float &my, float width, bool show_only_player);

	static sf::Vector2f screen_to_world(float mx, float my, float width, float x, float y);
	static sf::Vector2f cursor_to_world(float mx, float my, float width);
	static sf::Vector2f world_to_screen(float mx, float my, float width, float x, float y);
	dc_tracedata trace_ray(sf::Vector2f a, sf::Vector2f b);
};
