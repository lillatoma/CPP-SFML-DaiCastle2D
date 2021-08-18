#pragma once
#include "includes.h"


static sf::Vector3f stereoPanPosition(sf::Vector2f diffpose);


struct dc_sounddynamic
{
	int SND_ID;
	float DefaultVolumeModifier = 1.f;
	bool deletable = false;
	sf::SoundBuffer Buffer;
	sf::Sound sound;
	sf::Vector2f sndPosition;
	float AudibleDistance;

	dc_sounddynamic() {}

	dc_sounddynamic(file_t b, int snid, float audist, sf::Vector2f SoundPosition, float mastervolume, sf::Vector2f CamPosition, float starttime = 0.f, float defmodi = 1.f);


	void manipulate(float mastervolume, sf::Vector2f SoundPosition,sf::Vector2f CurrentPosition, bool ignorecheck = false);

};


struct dc_sound
{
	float DefaultVolumeModifier = 1.f;
	bool deletable = false;
	sf::SoundBuffer Buffer;
	sf::Sound sound;
	sf::Vector2f OriginalPosition;
	float AudibleDistance;

	dc_sound() {}

	dc_sound(file_t b, float audist, sf::Vector2f orp, float mastervolume, sf::Vector2f CurrentPosition, float defmodi);


	void manipulate(float mastervolume, sf::Vector2f CurrentPosition, bool ignorecheck = false);

};

struct AudioContainer
{
	std::vector<file_t> AllSoundBuffers;
	std::vector<dc_sound*> SoundContainer;
	std::vector<dc_sounddynamic*> DynamicSoundContainer;


	void AddSoundBuffer(file_t File);
	void ManipulateAllSounds(float mastervolume, sf::Vector2f CurrentPosition);
	void AddNewSound(int scindex, float audist, sf::Vector2f orp, float mastervolume, sf::Vector2f CurrentPosition);
	void AddNewSound(int scindex, float audist, sf::Vector2f orp, float mastervolume, sf::Vector2f CurrentPosition, float defmodi = 1.f);

	void AddNewDynamicSound(int saveindex, int scindex, float audist, sf::Vector2f snp, float mastervolume, sf::Vector2f CamPos, float soundstarttime = 0.f, float defmodi = 1.f);

	int CheckDynamicSound(int saveindex); //Gives latest dynamic sound id
	void SetDynamicSound(int saveindex, float mastervolume, sf::Vector2f soundposition, sf::Vector2f CurrentPosition);
	void ManipulateDynamicSounds(float mastervolume, sf::Vector2f CamPosition);

	void DefineAllSounds();


};

extern AudioContainer g_Sounds;

