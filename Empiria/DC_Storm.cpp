#include "DaiCastle.h"


//float s_times[] = { 0.f,20.f,40.f, 60.f,180.f , 300.f,570.f , 660.f,720.f , 780.f,825.0f , 870.f,915.f ,960.0f,985.f,1010.0f,1030.0f,2500.f };

//float s_times[] = { 0.f,60.f,120.f, 240.f,360.f , 480.f,570.f , 660.f,720.f , 780.f,825.0f , 870.f,915.f ,960.0f,985.f,1010.0f,1030.0f,2500.f };
//int s_damage[] = { 3,3,3,3,3,3,3,6,6,5,5,7,10,10,10,10,10,10,10,10,10,10 };
//float s_times[] = { 0.f,6.f,12.f, 24.f,36.f , 48.f,57.f , 66.f,72.f , 78.f,82.0f , 87.f,91.f ,96.0f,98.f,101.0f,103.0f,2500.f };
//int s_damage[] = { 1,1,1,1,1,1,1,2,2,5,5,7,10,10,10,10,10,10,10,10,10,10 };
//float s_size[] = { 2000.f,2000.f,2000.f, 2000.f,750.f , 750.f,350.f , 350.f,180.f , 180.f,90.f , 90.f,50.f ,30.f,15.f,5.f,0.f,0.f};

int dc_match::GetCurrentStormPhase()
{
	for (int i = 0; i < 18; i++)
	{
		if (ServerTime <= s_times[i])return i;
	}
}

int dc_match::GetCurrentStormDamage()
{
	return s_damage[GetCurrentStormPhase()];
}

int dc_match::GetNextStormDamage()
{
	return s_damage[GetCurrentStormPhase() + 1];
}

float dc_match::GetCurrentStormRadius()
{
	int phase = GetCurrentStormPhase();
	float previous_rad = s_size[phase - 1];
	float next_rad = s_size[phase];
	float phase_timelength = s_times[phase] - s_times[phase - 1];
	float current_time = ServerTime - s_times[phase - 1];

	return (current_time*next_rad + (phase_timelength - current_time)*previous_rad)/phase_timelength;
}


sf::Vector2f dc_match::GetCurrentStormMiddle()
{
	int phase = GetCurrentStormPhase();
	sf::Vector2f previous_mid = StormMids[phase - 1];
	sf::Vector2f next_mid = StormMids[phase];
	float phase_timelength = s_times[phase] - s_times[phase - 1];
	float current_time = ServerTime - s_times[phase - 1];

	return (current_time*next_mid + (phase_timelength - current_time)*previous_mid) / phase_timelength;
}

float dc_match::GetNextStormRadius()
{
	int phase = GetCurrentStormPhase();
	return s_size[phase];
}

sf::Vector2f dc_match::GetNextStormMiddle()
{
	int phase = GetCurrentStormPhase();
	return StormMids[phase];
}

float dc_match::GetTimeTillNextStormPhase()
{
	int phase = GetCurrentStormPhase();
	return s_times[phase] - ServerTime;
}

int dc_match::GetCurrentStormPhaseLogo()
{
	int phase = GetCurrentStormPhase();
	switch (phase)
	{
	case 0: return 4; break;
	case 1: return 4; break;
	case 2: return 2; break;
	case 3: return 2; break;
	case 4: return 3; break;
	case 5: return 2; break;
	case 6: return 3; break;
	case 7: return 2; break;
	case 8: return 3; break;
	case 9: return 2; break;
	case 10: return 3; break;
	case 11: return 2; break;
	case 12: return 3; break;
	default: return 3; break;
	}
}

void dc_match::GenerateStorms()
{
	t_clock.Update();

	StormMids[0] = sf::Vector2f(500, 500); //Bus Starts
	StormMids[1] = sf::Vector2f(500, 500); //Bus ends
	StormMids[2] = sf::Vector2f(500, 500); //Storm forms
	StormMids[3] = sf::Vector2f(500, 500); //First storm starts moving
	float length, angle, r;
	r = 250;
	length = sqrt(Random(0, r*r));
	angle = 0.1f*Random(0, 3600);
	StormMids[4] = sf::Vector2f(500, 500) + angle2vec(angle)*length; // First storm ends
	StormMids[5] = StormMids[4]; //Second storm starts moving
	
	r = s_size[4] - s_size[6]; r /= 2.f;
	length = sqrt(Random(0, r*r));
	angle = 0.1f*Random(0, 3600);
	StormMids[6] = StormMids[4] + angle2vec(angle)*length; // Second storm ends
	StormMids[7] = StormMids[6];

	r = s_size[6] - s_size[8]; r /= 2.f;
	length = sqrt(Random(0, r*r));
	angle = 0.1f*Random(0, 3600);
	StormMids[8] = StormMids[6] + angle2vec(angle)*length; //Third storm ends
	StormMids[9] = StormMids[8];

	r = s_size[8] - s_size[10]; r /= 2.f;
	length = sqrt(Random(0, r*r));
	if (MatchType == 1)length = 0.5f*s_size[8]; //Half-in half-out
	angle = 0.1f*Random(0, 3600);
	StormMids[10] = StormMids[8] + angle2vec(angle)*length; //Fourth storm ends
	StormMids[11] = StormMids[10];

	r = s_size[11] - s_size[12]; r /= 2.f;
	length = sqrt(Random(0, r*r));
	if (MatchType == 1)length = 0.1f*Random(450,600);
	angle = 0.1f*Random(0, 3600);
	StormMids[12] = StormMids[11] + angle2vec(angle)*length;

	r = s_size[12] - s_size[13]; r /= 2.f;
	length = sqrt(Random(0, r*r));
	if (MatchType == 1)length = 0.1f*Random(250, 500);
	angle = 0.1f*Random(0, 3600);
	StormMids[13] = StormMids[12] + angle2vec(angle)*length;

	r = s_size[13] - s_size[14]; r /= 2.f;
	length = sqrt(Random(0, r*r));
	if (MatchType == 1)length = 0.1f*Random(300, 500);
	angle = 0.1f*Random(0, 3600);
	StormMids[14] = StormMids[13] + angle2vec(angle)*length;

	r = s_size[14] - s_size[15]; r /= 2.f;
	length = sqrt(Random(0, r*r));
	if (MatchType == 1)length = 0.1f*Random(300, 500);
	angle = 0.1f*Random(0, 3600);
	StormMids[15] = StormMids[14] + angle2vec(angle)*length;

	r = s_size[15] - s_size[16]; r /= 2.f;
	length = sqrt(Random(0, r*r));
	if (MatchType == 1)length = 0.1f*Random(200, 400);
	angle = 0.1f*Random(0, 3600);
	StormMids[16] = StormMids[15] + angle2vec(angle)*length;

	StormMids[17] = StormMids[16];



	for (int i = 0; i < 17; i++)
	{
		ConLog("\n#%d | TimeStart: %.1f | Middle: %.1f %.1f | Radius: %.1f | Damage: %d", i, s_times[i], StormMids[i].x, StormMids[i].y, s_size[i], s_damage[i]);
	}
}

float dc_match::IsPointInStorm(sf::Vector2f p)
{
	//ConLog("\np: %.2f %.2f ~ SMiddle %.2f %.2f | %.2f %.2f:", p.x, p.y, GetCurrentStormMiddle().x, GetCurrentStormMiddle().y,
	//	(GetDistance(p, GetCurrentStormMiddle())),GetCurrentStormRadius());

	return max(0,(GetDistance(p, GetCurrentStormMiddle()) - GetCurrentStormRadius()/2));
}