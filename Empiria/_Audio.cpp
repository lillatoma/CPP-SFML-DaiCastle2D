#include "_Audio.h"

sf::Vector3f stereoPanPosition(sf::Vector2f diffpose, float Top)
{
	float angle = vec2angle(diffpose.x, -diffpose.y);


	return sf::Vector3f( cos(angle*PI/360.f),sin(angle*PI / 360.f),Top );
}

dc_sound::dc_sound(file_t b, float audist, sf::Vector2f orp, float mastervolume, sf::Vector2f CurrentPosition, float defmodi)
{
	DefaultVolumeModifier = defmodi;
	Buffer.loadFromMemory(b.loc_in_mem,b.size);
	sound.setBuffer(Buffer);
	AudibleDistance = audist;
	OriginalPosition = orp;
	manipulate(mastervolume, CurrentPosition,true);
	sound.play();
}

void dc_sound::manipulate(float mastervolume, sf::Vector2f CurrentPosition, bool ignorecheck)
{
	float distance = GetDistance(OriginalPosition, CurrentPosition);
	if (distance > AudibleDistance)
	{
		sound.stop();
	}
	if (!ignorecheck && sound.getStatus() == sf::Sound::Stopped) {
		deletable = true;
		return;
	}
	auto DiffVec = OriginalPosition - CurrentPosition;
	float Volume = pow(minmax(0, (AudibleDistance - distance) / AudibleDistance, 1.f), 2)*DefaultVolumeModifier;
	sound.setPosition(stereoPanPosition(DiffVec,Volume));

	sound.setVolume(Volume*mastervolume);

}

dc_sounddynamic::dc_sounddynamic(file_t b,int snid,float audist, sf::Vector2f SoundPosition, float mastervolume, sf::Vector2f CamPosition,float starttime, float defmodi)
{
	SND_ID = snid;
	DefaultVolumeModifier = defmodi;
	Buffer.loadFromMemory(b.loc_in_mem, b.size);
	sound.setBuffer(Buffer);
	AudibleDistance = audist;
	sndPosition = SoundPosition;
	manipulate(mastervolume, SoundPosition,CamPosition, true);
	sound.setPlayingOffset(sf::seconds(starttime));
	sound.play();
}

void dc_sounddynamic::manipulate(float mastervolume, sf::Vector2f soundposition, sf::Vector2f CamPosition, bool ignorecheck)
{
	sndPosition = soundposition;
	float distance = GetDistance(sndPosition, CamPosition);
	if (distance > AudibleDistance)
	{
		sound.stop();
	}
	if (!ignorecheck && sound.getStatus() == sf::Sound::Stopped) {
		deletable = true;
		return;
	}
	auto DiffVec = sndPosition - CamPosition;
	float Volume = pow(minmax(0, (AudibleDistance - distance) / AudibleDistance, 1.f), 2)*DefaultVolumeModifier;
	sound.setPosition(stereoPanPosition(DiffVec, Volume));

	sound.setVolume(Volume*mastervolume);

}


void AudioContainer::AddSoundBuffer(file_t File)
{
	//sf::SoundBuffer* Buff = new sf::SoundBuffer;
	//Buff->loadFromMemory(File.loc_in_mem, File.size);
	AllSoundBuffers.push_back(File);
}





void AudioContainer::AddNewSound(int scindex, float audist, sf::Vector2f orp, float mastervolume, sf::Vector2f CurrentPosition, float defmodi)
{
	if ((audist - GetLength(orp - CurrentPosition)) < 0)return;
	dc_sound* n = new dc_sound(g_Sounds.AllSoundBuffers[scindex], audist, orp, mastervolume, CurrentPosition,defmodi);

	SoundContainer.push_back(n);

	//printf("\nNew Aud: %d | %.f %.f | %.f %.f ", scindex, orp.x, orp.y, CurrentPosition.x, CurrentPosition.y);
}

void AudioContainer::AddNewDynamicSound(int saveindex, int scindex, float audist, sf::Vector2f snp, float mastervolume, sf::Vector2f CamPos, float soundstarttime, float defmodi)
{
	if ((audist - GetLength(snp - CamPos)) < 0)return;
	dc_sounddynamic* n = new dc_sounddynamic(g_Sounds.AllSoundBuffers[scindex], saveindex, audist, snp, mastervolume, CamPos, soundstarttime,defmodi);

	DynamicSoundContainer.push_back(n);
}

int AudioContainer::CheckDynamicSound(int saveindex)
{
	for (int i = DynamicSoundContainer.size() - 1; i >= 0; i--)
	{
		if (DynamicSoundContainer[i]->SND_ID == saveindex)return i;
	}

	return -1;
}

void AudioContainer::SetDynamicSound(int saveindex, float mastervolume, sf::Vector2f soundpos, sf::Vector2f campos)
{
	for (int i = 0; i < DynamicSoundContainer.size(); i++)
	{
		if (DynamicSoundContainer[i]->SND_ID == saveindex)
		{
			DynamicSoundContainer[i]->manipulate(mastervolume, soundpos, campos);
		}
	}
}

void AudioContainer::ManipulateAllSounds(float mastervolume, sf::Vector2f CurrentPosition)
{
	for (auto&s : SoundContainer)
		s->manipulate(mastervolume, CurrentPosition);

	//printf("\n Before Sounds: %d", SoundContainer.size());


	for (int i = SoundContainer.size() - 1; i >= 0; i--)
	{
		if (SoundContainer[i]->deletable)
		{
			delete SoundContainer[i];
			SoundContainer.erase(SoundContainer.begin() + i);
		}
	}
	///printf(" | AfterSounds: %d", SoundContainer.size());
}

void AudioContainer::ManipulateDynamicSounds(float mastervolume, sf::Vector2f CamPosition)
{
	for (auto &s : DynamicSoundContainer)
		s->manipulate(mastervolume, s->sndPosition, CamPosition);

	for (int i = DynamicSoundContainer.size() - 1; i >= 0; i--)
	{
		if (DynamicSoundContainer[i]->deletable)
		{
			delete DynamicSoundContainer[i];
			DynamicSoundContainer.erase(DynamicSoundContainer.begin() + i);
		}

	}
}

void AudioContainer::DefineAllSounds()
{
	AddSoundBuffer(g_Files.GetFileByName("grassstep-1.ogg"));
	AddSoundBuffer(g_Files.GetFileByName("grassstep-2.ogg"));
	AddSoundBuffer(g_Files.GetFileByName("woodstep-1.ogg"));
	AddSoundBuffer(g_Files.GetFileByName("woodstep-2.ogg"));
	AddSoundBuffer(g_Files.GetFileByName("sandstep-1.ogg"));
	AddSoundBuffer(g_Files.GetFileByName("sandstep-2.ogg"));
	AddSoundBuffer(g_Files.GetFileByName("snowstep-1.ogg"));
	AddSoundBuffer(g_Files.GetFileByName("snowstep-2.ogg"));
	AddSoundBuffer(g_Files.GetFileByName("tilestep-1.ogg"));
	AddSoundBuffer(g_Files.GetFileByName("tilestep-2.ogg"));

	AddSoundBuffer(g_Files.GetFileByName("metalstep-1.ogg")); //10
	AddSoundBuffer(g_Files.GetFileByName("metalstep-2.ogg"));
	AddSoundBuffer(g_Files.GetFileByName("waterstep-1.ogg"));
	AddSoundBuffer(g_Files.GetFileByName("waterstep-2.ogg"));
	AddSoundBuffer(g_Files.GetFileByName("wpn_glock-1.ogg"));
	AddSoundBuffer(g_Files.GetFileByName("wpn_famas-2.ogg")); //15
	AddSoundBuffer(g_Files.GetFileByName("wpn_leone-1.ogg"));
	AddSoundBuffer(g_Files.GetFileByName("wpn_silenced-1.ogg"));
	AddSoundBuffer(g_Files.GetFileByName("wpn_usp-1.ogg"));
	AddSoundBuffer(g_Files.GetFileByName("wpn_kor91k-1.ogg"));

	AddSoundBuffer(g_Files.GetFileByName("wpn_revolver-1.ogg")); //20
	AddSoundBuffer(g_Files.GetFileByName("wpn_tacticat-2.ogg"));
	AddSoundBuffer(g_Files.GetFileByName("wpn_hunting-1.ogg"));
	AddSoundBuffer(g_Files.GetFileByName("wpn_awp-1.ogg"));
	AddSoundBuffer(g_Files.GetFileByName("wpn_ara1-1.ogg"));
	AddSoundBuffer(g_Files.GetFileByName("wpn_mp8-1.ogg")); //25
	AddSoundBuffer(g_Files.GetFileByName("wpn_minigun-2.ogg"));
	AddSoundBuffer(g_Files.GetFileByName("wpn_scoped-1.ogg"));
	AddSoundBuffer(g_Files.GetFileByName("wpn_spas-1.ogg"));
	AddSoundBuffer(g_Files.GetFileByName("wpn_semiauto-1.ogg"));

	AddSoundBuffer(g_Files.GetFileByName("wpn_thomson-1.ogg")); //30
	AddSoundBuffer(g_Files.GetFileByName("heal-1.ogg")); 
	AddSoundBuffer(g_Files.GetFileByName("slurp-1.ogg")); 
	AddSoundBuffer(g_Files.GetFileByName("wpn_rl-1.ogg"));
	AddSoundBuffer(g_Files.GetFileByName("wpn_gl-1.ogg"));
	AddSoundBuffer(g_Files.GetFileByName("wpn_grenade-1.ogg")); //35
	AddSoundBuffer(g_Files.GetFileByName("explosion-1.ogg"));
	AddSoundBuffer(g_Files.GetFileByName("wall_hit-1.ogg"));
	AddSoundBuffer(g_Files.GetFileByName("busmusic.ogg"));
	AddSoundBuffer(g_Files.GetFileByName("killnotice.ogg"));

	AddSoundBuffer(g_Files.GetFileByName("wpn_lmg-1.ogg")); //40
	AddSoundBuffer(g_Files.GetFileByName("wpn_dbarrel-1.ogg"));
	AddSoundBuffer(g_Files.GetFileByName("wpn_combat-1.ogg"));
	AddSoundBuffer(g_Files.GetFileByName("wpn_drumgun-1.ogg"));

	ConLog("\nTotal sounds loaded: %d", AllSoundBuffers.size());
}

AudioContainer g_Sounds;