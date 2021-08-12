#include "gamestructs.h"
/*

struct _settings_t
{
	float MovementSpeed = 6.f;

}Settings;






item_t g_ItemList[1000];

int Tickets[10000];
int current_ticket = 0;

void FillTickets(int with_this, int how_much)
{
	for (int i = 0; i < how_much; i++)
	{
		Tickets[current_ticket] = with_this;
		current_ticket++;
	}
}

////
// Common: 20-24
// Uncommon: 15-18
// Rare: 10-12
// Epic:  6-8
// Legendary: 3-5
////
void item_t::SetUpAllWeapons()
{
	g_ItemList[100].Setup(100,50, 30, 10, 2.5, 6, 12, 16, 8, 2, 1, 1, "Tactical Shotgun (Common)");
	g_ItemList[101].Setup(101,55, 32, 11, 2.5, 6, 12, 17, 8, 2, 1, 1, "Tactical Shotgun (Uncommon)");
	g_ItemList[102].Setup(102,60, 35, 12, 2.5, 7, 13, 17, 8, 2, 1, 1, "Tactical Shotgun (Rare)");
	FillTickets(100, 23);
	FillTickets(101, 17);
	FillTickets(102, 10);
	g_ItemList[110].Setup(110,95, 40, 15, 2, 8, 14, 21, 5, 1, 1, 1, "Pump Shotgun (Uncommon)");
	g_ItemList[111].Setup(111,100, 41, 16, 2, 8, 14, 22, 5, 1, 1, 1, "Pump Shotgun (Rare)");
	g_ItemList[112].Setup(112,105, 43, 17, 2, 8, 15, 22, 5, 1, 1, 1, "Pump Shotgun (Epic)");
	g_ItemList[113].Setup(113,110, 45, 18, 2, 8, 15, 23, 5, 1, 1, 1, "Pump Shotgun (Legendary)");
	FillTickets(110, 15);
	FillTickets(111, 10);
	FillTickets(112, 6);
	FillTickets(113, 3);
	g_ItemList[120].Setup(120,70, 40, 20, 2.5, 11, 18, 28, 5, 1, 1, 1, "Heavy Shotgun (Epic)");
	g_ItemList[121].Setup(121,77, 44, 22, 2.5, 11, 19, 30, 5, 1, 1, 1, "Heavy Shotgun (Legendary)");
	FillTickets(120, 8);
	FillTickets(121, 5);

	g_ItemList[200].Setup(200,24, 18, 12, 2, 24, 40, 80, 16, 4, 2, 1, "Pistol (Common)");
	g_ItemList[201].Setup(201,25, 18, 12, 2, 26, 45, 86, 16, 4, 2, 1, "Pistol (Uncommon)");
	g_ItemList[202].Setup(202,27, 20, 13, 2, 28, 50, 92, 16, 4, 2, 1, "Silenced Pistol (Rare)");
	g_ItemList[203].Setup(203,28, 20, 14, 2, 28, 50, 92, 16, 4, 2, 1, "Silenced Pistol (Epic)");
	//g_ItemList[204].Setup(30, 19, 13, 2, 28, 50, 92, 16, 4, 2, 1, "Silenced Pistol (Legendary)");
	FillTickets(200, 24);
	FillTickets(201, 17);
	FillTickets(202, 10);
	FillTickets(203, 7);
	//FillTickets(204, 3);
	g_ItemList[210].Setup(210,19, 11, 6, 2, 18, 36, 80, 30, 9, 2, 2, "Submachinegun (Common)");
	g_ItemList[211].Setup(211,20, 12, 6, 2, 19, 38, 83, 30, 9, 2, 2, "Submachinegun (Uncommon)");
	g_ItemList[212].Setup(212,21, 13, 7, 2, 20, 40, 86, 30, 9, 2, 2, "Submachinegun (Rare)");
	FillTickets(210, 22);
	FillTickets(211, 17);
	FillTickets(212, 10);
	g_ItemList[220].Setup(220,18, 13, 7, 2, 24, 44, 80, 40, 10, 2, 2, "Compact SMG (Epic)");
	g_ItemList[221].Setup(221,19, 14, 8, 2, 25, 46, 85, 40, 10, 2, 2, "Compact SMG (Legendary)");
	FillTickets(220, 8);
	FillTickets(221, 4);
	g_ItemList[230].Setup(230,40, 28, 18, 2, 24, 40, 80, 16, 4, 2, 1, "Dual Pistols (Rare)");
	g_ItemList[231].Setup(231,44, 30, 20, 2, 26, 44, 85, 16, 4, 2, 1, "Dual Pistols (Epic)");
	FillTickets(230, 12);
	FillTickets(231, 6);

	g_ItemList[300].Setup(300,30, 26, 19, 2, 50, 100, 150, 30, 6, 3, 2, "Assault Rifle (Common)");
	g_ItemList[301].Setup(301,31, 27, 20, 2, 50, 100, 150, 30, 6, 3, 2, "Assault Rifle (Uncommon)");
	g_ItemList[302].Setup(302,32, 27, 20, 2, 50, 100, 150, 30, 6, 3, 2, "Assault Rifle (Rare)");
	g_ItemList[303].Setup(303,34, 28, 21, 2, 53, 105, 160, 30, 6, 3, 2, "Assault Rifle (Epic)");
	g_ItemList[304].Setup(304,35, 29, 22, 2, 53, 105, 160, 30, 6, 3, 2, "Assault Rifle (Legendary)");
	FillTickets(300, 24);
	FillTickets(301, 17);
	FillTickets(302, 11);
	FillTickets(303, 7);
	FillTickets(304, 4);
	g_ItemList[310].Setup(310,44, 38, 30, 2, 60, 110, 160, 25, 3, 3, 2, "Heavy Assault Rifle (Rare)");
	g_ItemList[311].Setup(311,46, 39, 31, 2, 63, 115, 168, 25, 3, 3, 2, "Heavy Assault Rifle (Epic)");
	g_ItemList[312].Setup(312,48, 41, 33, 2, 63, 115, 168, 25, 3, 3, 2, "Heavy Assault Rifle (Legendary)");
	FillTickets(310, 12);
	FillTickets(311, 6);
	FillTickets(312, 3);
	g_ItemList[320].Setup(320,70, 60, 50, 2, 60, 100, 200, 7, 1, 3, 1, "Hand Cannon (Epic)");
	g_ItemList[321].Setup(321,75, 64, 53, 2, 60, 100, 200, 7, 1, 3, 1, "Hand Cannon (Legendary)");
	FillTickets(320, 7);
	FillTickets(321, 3);

	g_ItemList[400].Setup(400,85, 85, 85, 2.5, 200, 200, 200, 1, 1, 4, 3, "Hunting Rifle (Uncommon)");
	g_ItemList[401].Setup(401,90, 90, 90, 2.5, 200, 200, 200, 1, 1, 4, 3, "Hunting Rifle (Rare)");
	g_ItemList[410].Setup(410,105, 105, 105, 2.5, 200, 200, 200, 1, 1, 4, 3, "Bolt-Action Sniper Rifle (Rare)");
	g_ItemList[411].Setup(411,110, 110, 110, 2.5, 200, 200, 200, 1, 1, 4, 3, "Bolt-Action Sniper Rifle (Epic)");
	g_ItemList[420].Setup(420,150, 150, 150, 2.5, 200, 200, 200, 1, 1, 4, 3, "Heavy Sniper Rifle (Epic)");
	g_ItemList[421].Setup(421,157, 157, 157, 2.5, 200, 200, 200, 1, 1, 4, 3, "Heavy Sniper Rifle (Legendary)");
	FillTickets(400, 18);
	FillTickets(401, 12);
	FillTickets(410, 10);
	FillTickets(411, 8);
	FillTickets(420, 3);
	FillTickets(421, 1);

	g_ItemList[500].Setup(500,true, false, 15, 5, "Bandage");
	g_ItemList[501].Setup(501,true, false, 100, 1, "Med-Kit");
	g_ItemList[502].Setup(502,false, true, 25, 3, "Small Shield Potion");
	g_ItemList[503].Setup(503,false, true, 50, 1, "Shield Potion");

	FillTickets(500, 40);
	FillTickets(501, 25);
	FillTickets(502, 25);
	FillTickets(503, 20);






}

int item_t::GetRandomItem()
{
	int r = Random(0, current_ticket-1);

	
	//Setup(g_ItemList[Tickets[r]]);

	return Tickets[r];
}

void item_t::Copy(int a)
{
	Setup(g_ItemList[a]);

}

void item_t::Shoot(unit_t* shooter, unit_t* target)
{
	if (iBullets <= 0)return;
	if (!target->bAlive)return;


	iBullets -= 1;
	target->s_iShotsDodged++;





	int atk = shooter->GetAimSkill(iAimType);
	int def = target->gsGamestyle->skill.defending;
	int randtotal = (atk + def) * 1;
	int r = Random(1, randtotal);
	if (r < randtotal*0 + def)return;




	auto dist = shooter->vecPosition.DistTo(target->vecPosition);

	if (isSniper())
	{
		if (Random(0, dist) > 40)return;
	}
	else if (isAR())
	{
		if (Random(0, dist) > 50)return;
	}
	else if (isSecondary())
	{
		if (Random(0, dist) > 25)return;
	}


	int damage = 0;
	if (dist < iDropoffRange1)damage = iDamage1;
	else if (dist < iDropoffRange2)damage = iDamage2;
	else if (dist < iRange)damage = iDamage3;
	else return;

	int r1 = Random(1, 100);
	if (r1 < 25)damage *= fHeadshotMultiplier;

	target->GetDamage(damage);
	target->s_iShotsDodged--;
	if (iAimType == 1)shooter->s_iShotsFlicked++;
	else if (iAimType == 2)shooter->s_iShotsTracked++;
	else if (iAimType == 3)shooter->s_iShotsPredicted++;

	if (!target->bAlive)
	{
		shooter->s_iEliminations++;
		printf("\n%d eliminated %d with %s (%d) (%d | %d) from %.1f meter", shooter->iID,target->iID,szName,shooter->s_iEliminations,shooter->iHealth,shooter->iArmor,dist);
		if (target->hasShotgun())shooter->Loot(false, &target->itShotgun);
		if (target->hasSecondary())shooter->Loot(false, &target->itSecondary_weapon);
		if (target->hasAR())shooter->Loot(false, &target->itMid_range);
		if (target->hasSniper())shooter->Loot(false, &target->itSniper);
	

		if (target->iID == 0 || shooter->iID == 0)
		{
			target->pMatch->inInfo.Add(shooter->iID, target->iID, iID);
		}


	}


}













bool unit_t::hasShotgun()
{
	return itShotgun.doesExist;
}

bool unit_t::hasSecondary()
{
	return itSecondary_weapon.doesExist;
}

bool unit_t::hasAR()
{
	return itMid_range.doesExist;
}

bool unit_t::hasSniper()
{
	return itSniper.doesExist;
}

bool unit_t::NeedsShield()
{
	return iArmor < 100;
}

bool unit_t::NeedsHealth()
{
	return iHealth < 100;
}

bool unit_t::NeedsWeapons()
{
	int shotgun_preference = gsGamestyle->shotgun_preference; // 0 - tactical, 1 - pump, 2 - heavy
	int secondary_preference = gsGamestyle->secondary_preference; //0 - smg, 1 - compact smg, 2 - dual pistol
	int ar_preference = gsGamestyle->ar_preference; //0 - ar, 1 - heavy ar, 2 - deagle


	if ((shotgun_preference == 0 && itShotgun.iID < 103) || (shotgun_preference == 1 && itShotgun.iID >= 110 && itShotgun.iID <= 113) || (shotgun_preference == 2 && itShotgun.iID >= 120 && itShotgun.iID <= 121));
	else return true;
	if ((secondary_preference == 0 && itSecondary_weapon.iID >= 210 && itSecondary_weapon.iID <= 212)
		|| (secondary_preference == 1 && itSecondary_weapon.iID >= 220 && itSecondary_weapon.iID <= 221)
		|| (secondary_preference == 2 && itSecondary_weapon.iID >= 230 && itSecondary_weapon.iID <= 231))
	{
	}
	else return true;
	if ((ar_preference == 0 && itMid_range.iID >= 300 && itMid_range.iID <= 304)
		|| (ar_preference == 1 && itMid_range.iID >= 310 && itMid_range.iID <= 312)
		|| (ar_preference == 2 && itMid_range.iID >= 320 && itMid_range.iID <= 321)
		);
	else return true;

	if (!hasSniper() || hasSniper() && itSniper.iID < 410)return true;
	return false;
}

bool unit_t::NeedsToLoot()
{
	return NeedsHealth() || NeedsShield() || NeedsWeapons();
}

void unit_t::GetDamage(int damage, bool is_storm)
{
	{
		if (!is_storm)
		{
			if (damage >= iArmor)
			{
				damage -= iArmor;
				iArmor = 0;
				iHealth -= damage;
			}
			else iArmor -= damage;
		}
		else iHealth -= damage;

		if (iHealth <= 0)
		{
			iHealth = 0;
			bAlive = false;
			s_Position = pMatch->GetAliveTeams()+1;
		}

	}
}

void unit_t::Loot(bool should_generate, item_t* fixed)
{
	item_t Item;

	int r = Random(1, 10000);


	int n = 1000 + pow(gsGamestyle->skill.looting, 10.f / 11) * 3;
	if (n > 2500)n = 2500;

	if (r > n && should_generate)return;

	int item_id = item_t::GetRandomItem();

	if (should_generate)
		Item.Copy(item_id);
	else
		Item.Copy(fixed->iID);


	int shotgun_preference = gsGamestyle->shotgun_preference; // 0 - tactical, 1 - pump, 2 - heavy
	int secondary_preference = gsGamestyle->secondary_preference; //0 - smg, 1 - compact smg, 2 - dual pistol
	int ar_preference = gsGamestyle->ar_preference; //0 - ar, 1 - heavy ar, 2 - deagle

	s_iItemsFound++;

	if (Item.isShotgun())
	{
		if (hasShotgun())
		{
			if (shotgun_preference == 0 && Item.iID < 103)
			{
				if (Item.iID >= itShotgun.iID || itShotgun.iID > 103)itShotgun.Setup(Item);
			}
			else if (shotgun_preference == 1 && Item.iID >= 110 && Item.iID <= 113)
			{
				if ((itShotgun.iID >= 110 && itShotgun.iID <= 113 && Item.iID >= itShotgun.iID) || itShotgun.iID < 110 || itShotgun.iID > 113)itShotgun.Setup(Item);
			}
			else if (shotgun_preference == 2 && Item.iID >= 120 && Item.iID <= 121)
			{
				if ((itShotgun.iID >= 120 && itShotgun.iID <= 121 && Item.iID >= itShotgun.iID) || itShotgun.iID < 120 || itShotgun.iID > 121)itShotgun.Setup(Item);
			}
			else if (Item.iID >= itShotgun.iID)
			{
				if ((shotgun_preference == 0 && itShotgun.iID < 103) || (shotgun_preference == 1 && itShotgun.iID >= 110 && itShotgun.iID <= 113) || (shotgun_preference == 2 && itShotgun.iID >= 120 && itShotgun.iID <= 121));
				else itShotgun.Setup(Item);
			}
		}
		else itShotgun.Setup(Item);
	}
	else if (Item.isSecondary())
	{
		if (hasSecondary())
		{
			if (secondary_preference == 0 && Item.iID >= 210 && Item.iID <= 212)
			{
				if (itSecondary_weapon.iID < 210 || itSecondary_weapon.iID > 212)itSecondary_weapon.Setup(Item);
				if (Item.iID > itSecondary_weapon.iID && itSecondary_weapon.iID >= 210 && itSecondary_weapon.iID <= 212)itSecondary_weapon.Setup(Item);
			}
			else if (secondary_preference == 1 && Item.iID >= 220 && Item.iID <= 221)
			{
				if (itSecondary_weapon.iID < 220 || itSecondary_weapon.iID > 221)itSecondary_weapon.Setup(Item);
				if (Item.iID > itSecondary_weapon.iID && itSecondary_weapon.iID >= 220 && itSecondary_weapon.iID <= 221)itSecondary_weapon.Setup(Item);
			}
			else if (secondary_preference == 2 && Item.iID >= 230 && Item.iID <= 231)
			{
				if (itSecondary_weapon.iID < 230 || itSecondary_weapon.iID > 231)itSecondary_weapon.Setup(Item);
				if (Item.iID > itSecondary_weapon.iID && itSecondary_weapon.iID >= 230 && itSecondary_weapon.iID <= 231)itSecondary_weapon.Setup(Item);
			}
			else if(Item.iID >= itSecondary_weapon.iID)
			{
				if ((secondary_preference == 0 && itSecondary_weapon.iID >= 210 && itSecondary_weapon.iID <= 212)
					|| (secondary_preference == 1 && itSecondary_weapon.iID >= 220 && itSecondary_weapon.iID <= 221)
					|| (secondary_preference == 2 && itSecondary_weapon.iID >= 230 && itSecondary_weapon.iID <= 231))
				{
				}
				else itSecondary_weapon.Setup(Item);
			}
		}
		else itSecondary_weapon.Setup(Item);
		
	}
	else if (Item.isAR())
	{
		if (hasAR())
		{
			if (ar_preference == 0 && Item.iID >= 300 && Item.iID <= 304)
			{
				if (itMid_range.iID < 300 || itMid_range.iID > 304)itMid_range.Setup(Item);
				if (itMid_range.iID >= 300 && itMid_range.iID <= 304 && Item.iID >= itMid_range.iID)itMid_range.Setup(Item);
			}
			else if (ar_preference == 1 && Item.iID >= 310 && Item.iID <= 312)
			{
				if (itMid_range.iID < 310 || itMid_range.iID > 312)itMid_range.Setup(Item);
				if (itMid_range.iID >= 310 && itMid_range.iID <= 312 && Item.iID >= itMid_range.iID)itMid_range.Setup(Item);
			}
			else if (ar_preference == 2 && Item.iID >= 320 && Item.iID <= 321)
			{
				if (itMid_range.iID < 320 || itMid_range.iID > 321)itMid_range.Setup(Item);
				if (itMid_range.iID >= 320 && itMid_range.iID <= 321 && Item.iID >= itMid_range.iID)itMid_range.Setup(Item);
			}
			else if (Item.iID > itMid_range.iID)
			{
				if ((ar_preference == 0 && itMid_range.iID >= 300 && itMid_range.iID <= 304)
					|| (ar_preference == 1 && itMid_range.iID >= 310 && itMid_range.iID <= 312)
					|| (ar_preference == 2 && itMid_range.iID >= 320 && itMid_range.iID <= 321)
					);
				else itMid_range.Setup(Item);
			}
			{

			}
		}
		else itMid_range.Setup(Item);
	}
	else if (Item.isSniper())
	{
		if (hasSniper())
		{
			if (Item.iID >= itSniper.iID)itSniper.Setup(Item);
		}
		else itSniper.Setup(Item);
	}
	else
	{
		if (Item.iID == 0)
		{
			printf("\nItem with no ID found! It's name is %s", Item.szName);
		}

		if (Item.iID == 500)
		{
			if (iHealth < 75)iHealth = 75;
			//if (itHeal.doesExist)
		}
		if (Item.iID == 501)
		{
			if (iHealth < 100)iHealth = 100;
		}
		if (Item.iID == 502)
		{
			if (iArmor < 50)iArmor = 50;
		}
		if (Item.iID == 503)
		{
			if (iArmor < 100)iArmor += 50;
			if (iArmor > 100)iArmor = 100;
		}

	}



}

void unit_t::Explore()
{
	
	
	Vector rVec;
	while (true)
	{
		int r_deg = Random(0, 360);
		rVec = Vector(cos(r_deg*PI / 180), sin(r_deg*PI / 180), 0) * Settings.MovementSpeed + vecPosition;
		
		if (abs(rVec.x) > 1250.f || abs(rVec.y) > 1250.f)continue;
		
		if (pMatch->IsInCircle(rVec) || pMatch->circle_size < 10)break;


	}

	vecPosition = rVec;
}



void unit_t::Spot()
{
	int spot_range = 0;

	if (hasSniper())spot_range = 150;
	else if (hasAR())spot_range = 120;
	else if (hasSecondary())spot_range = 50;
	else spot_range = 20;

	for (int i = 0; i < 100; i++)
	{
		if (i == iID)continue;
		if (iTeam == pMatch->players[i]->iTeam)continue;
		auto dist = vecPosition.DistTo(pMatch->players[i]->vecPosition);
		if (dist > spot_range)continue;

		int spot_chance = 0;

		if (dist < 20)spot_chance = 400;
		else if (dist < 50)spot_chance = 160;
		else if (dist < 100)spot_chance = 65;
		else spot_chance = 15;

		auto r = Random(1, 1000);

		if (r < spot_chance)
		{
			iTargetID = i;
			break;
		}


	}
}

int unit_t::GetTotalElims()
{
	{
		int k = 0;
		for (int i = 0; i < 100; i++)if (pMatch->players[i]->iTeam == iTeam)k += pMatch->players[i]->s_iEliminations;
		return k;
	}
}

void unit_t::RunToCircle()
{
	float dist = vecPosition.DistTo(pMatch->vecNextMiddle);
	Vector nVec = (dist - Settings.MovementSpeed) * vecPosition + (Settings.MovementSpeed)*pMatch->vecNextMiddle;
	nVec = nVec / dist;
	vecPosition = nVec;
}

void unit_t::Push()
{
	float dist = vecPosition.DistTo(pMatch->players[iTargetID]->vecPosition);
	Vector nVec = (dist - Settings.MovementSpeed) * vecPosition + (Settings.MovementSpeed)*pMatch->players[iTargetID]->vecPosition;
	nVec = nVec / dist;
	vecPosition = nVec;
}

void unit_t::Attack()
{
	if (iTargetID == -1 || !pMatch->players[iTargetID]->bAlive)return;

	auto dist = vecPosition.DistTo(pMatch->players[iTargetID]->vecPosition);

	auto target = pMatch->players[iTargetID];

	if (dist < 15)
	{
		if (!itShotgun.isEmpty())
		{
			for (int i = 0; i < itShotgun.iFireRate; i++)
				itShotgun.Shoot(this, target);
		}
		else if (!itSecondary_weapon.isEmpty())
		{
			for (int i = 0; i < itSecondary_weapon.iFireRate; i++)itSecondary_weapon.Shoot(this, target);
		}
		else if (!itMid_range.isEmpty())
		{
			for (int i = 0; i < itMid_range.iFireRate; i++)itMid_range.Shoot(this, target);
		}
		else if (!itShotgun.doesExist)Loot();
		else itShotgun.Reload();
	}
	else if (dist < 30)
	{
		if (!itSecondary_weapon.isEmpty())
		{
			for (int i = 0; i < itSecondary_weapon.iFireRate; i++)itSecondary_weapon.Shoot(this, target);
		}
		else if (!itMid_range.isEmpty())
		{
			for (int i = 0; i < itMid_range.iFireRate; i++)itMid_range.Shoot(this, target);
		}
		else if (!itShotgun.isEmpty())
		{
			for (int i = 0; i < itShotgun.iFireRate; i++)
				itShotgun.Shoot(this, target);
		}
		else if (!itSecondary_weapon.doesExist)Loot();
		else itSecondary_weapon.Reload();
	}
	else if (dist < 75)
	{
		if (!itMid_range.isEmpty())
		{
			for (int i = 0; i < itMid_range.iFireRate; i++)itMid_range.Shoot(this, target);
		}
		else if (!itSecondary_weapon.isEmpty())
		{
			for (int i = 0; i < itSecondary_weapon.iFireRate; i++)itSecondary_weapon.Shoot(this, target);
		}
		else if (!itSniper.isEmpty())itSniper.Shoot(this, target);
		else if (!itMid_range.doesExist)Push();
		else itMid_range.Reload();


	}
	else if (dist < 150)
	{
		if (!itSniper.isEmpty())itSniper.Shoot(this, target);
		else if (!itMid_range.isEmpty())
		{
			for (int i = 0; i < itMid_range.iFireRate; i++)itMid_range.Shoot(this, target);
		}
		else if (!itMid_range.doesExist)Push();
		else if (!itSniper.doesExist)Push();
		else itSniper.Reload();
	}
	else if (dist < 200)
	{
		if (!itSniper.isEmpty())itSniper.Shoot(this, target);
		else itSniper.Reload();
	}

}



void unit_t::Think()
{
	if (!hasShotgun() && !hasSecondary() && !hasAR())
	{
		Loot();
		return;
	}


	if (iTargetID == -1)
	{
		


		if (pMatch->IsInNextCircle(vecPosition))
		{
			int r = Random(0, 100);
			
			if (r < 16)
				RunToCircle();
			else if (r < 30 && !NeedsToLoot())
				RunToCircle();
			else if (r < 75 && NeedsToLoot())
				Loot();
			else Explore();
		}
		else
		{
			float dist_to_circle = vecPosition.DistTo(pMatch->vecNextMiddle) - pMatch->next_circle_size;
			float dist_from_storm = pMatch->circle_size - vecPosition.DistTo(pMatch->vecNextMiddle);
			int ticks_to_close = pMatch->ticks_from_circle_change;

			if ((dist_to_circle / Settings.MovementSpeed) + 3 >= ticks_to_close || !pMatch->IsInCircle(vecPosition))RunToCircle();
			else
			{
				int r1 = Random(1, 100);
				if (true && r1 < 50)Loot();
				else if (r1 > 90)Explore();
				else RunToCircle();
			}


		}




		Spot();
	}
	else
	{
		//if (iTargetID == 0 || iID == 0)Sleep(5);
		int spot_range = 0;

		if (hasSniper())spot_range = 200;
		else if (hasAR())spot_range = itMid_range.iRange;
		else if (hasSecondary())spot_range = itSecondary_weapon.iRange;
		else spot_range = itShotgun.iRange;

		auto dist = vecPosition.DistTo(pMatch->players[iTargetID]->vecPosition);
		if (!pMatch->players[iTargetID]->bAlive || dist > spot_range)
		{
			iTargetID = -1;
			Think();
			return;
		}



		if (Random(1, 250) < dist || Random(0,100) < 40)Push();
		else Attack();



	}






}






int match_t::GetStormDamage()
{
	switch (current_circle)
	{
	case 0:
	case 1:
	case 2:
	case 3:
		return 1;
		break;
	case 4:
	case 5:
		return 2;
		break;
	case 6:
	case 7:
		return 5;
		break;
	default:
		return 8;
		break;
	}
}

float match_t::GetStormSize(int w)
{
	switch (w)
	{
	case 0:
	case 1:
		return 2500;
		break;
	case 2:
	case 3:
		return 750;
		break;
	case 4:
	case 5: 
		return 430;
		break;
	case 6:
	case 7:
		return 250;
		break;
	case 8:
	case 9:
		return 125;
		break;
	case 10:
		return 60;
		break;
	case 11:
		return 30;
		break;
	case 12:
		return 10;
		break;
	default:
		return 0;
		break;


	}
}

int match_t::GetStormTime(int w)
{
	switch (w)
	{
	case 0:
		return 200;
		break;
	case 1:
		return 180;
		break;
	case 2:
	case 3:
		return 120;
		break;
	case 4:
	case 5:
		return 90;
		break;
	case 6:
	case 7:
		return 70;
		break;
	case 8:
	case 9:
		return 50;
		break;
	default:
		return 30;
		break;


	}
}

bool match_t::IsInCircle(Vector v)
{
	return v.DistTo(vecCircleMiddle) < circle_size;

}

bool match_t::IsInNextCircle(Vector v)
{
	return v.DistTo(vecCircleMiddle) < next_circle_size;

}


void match_t::SimulateCircle()
{
	for (int i = 0; i < 100; i++)
	{
		if (!players[i]->bAlive)continue;
		if (!IsInCircle(players[i]->vecPosition))
		{
			players[i]->GetDamage(GetStormDamage(), true);
			//players[i]->iHealth -= GetStormDamage();
			if (players[i]->iHealth <= 0)
			{
				//printf("\n|%d|\n%s\n%s\n%s\n%s", i, players[i]->itShotgun.szName,players[i]->itSecondary_weapon.szName,players[i]->itMid_range.szName,players[i]->itSniper.szName);
				printf("\n%d was lost in the storm", i);

				players[i]->iHealth = 0;
				players[i]->bAlive = false;
			}
		}
	}

	if (ticks_from_circle_change <= 0)
	{
		current_circle++;
		next_circle_size = GetStormSize(current_circle);
		ticks_from_circle_change = GetStormTime(current_circle);
		if (current_circle >= 13)
		{
			auto nextCircleMiddle = Vector(0, 0, 0);
		}

		else
		{
			auto nextCircleMiddle = Vector(0, 0, 0);
			if (circle_size != next_circle_size)
			{
				while (true)
				{


					auto x = Random(vecCircleMiddle.x - (circle_size + GetStormSize(current_circle + 1)), vecCircleMiddle.x + (circle_size + GetStormSize(current_circle + 1)));
					auto y = Random(vecCircleMiddle.y - (circle_size + GetStormSize(current_circle + 1)), vecCircleMiddle.y + (circle_size + GetStormSize(current_circle + 1)));

					nextCircleMiddle = Vector(x, y, 0);


					//printf("\nGenerating: %.f | %.f -- DistTo: %.f | StormSize: %.f", nextCircleMiddle.x, nextCircleMiddle.y, nextCircleMiddle.DistTo(vecCircleMiddle), circle_size - GetStormSize(current_circle) + 3);

					if (nextCircleMiddle.DistTo(vecCircleMiddle) <= circle_size - GetStormSize(current_circle + 1) + 1
						&& (nextCircleMiddle.DistTo(Vector(0,0,0)) < 1250-GetStormSize(current_circle+1)  ))
					{
						break;
					}

				}
				vecNextMiddle = nextCircleMiddle;
			}
		}
	}
	else
	{
		Vector Vec = (vecNextMiddle + (ticks_from_circle_change - 1) * vecCircleMiddle) / ticks_from_circle_change;
		vecCircleMiddle = Vec;
		float size = (next_circle_size + (ticks_from_circle_change - 1) * circle_size) / ticks_from_circle_change;
		circle_size = size;

	}


	//printf("\n#%d | %d remaining | [%.f,%.f] | Size: %f", current_circle, ticks_from_circle_change, vecCircleMiddle.x, vecCircleMiddle.y, circle_size);

	ticks_from_circle_change--;

}

void match_t::DrawOneCircleOnMap(Vector cord, float size, sf::Color c)
{
	float x = (1280 - 600) / 2;
	float y = (720 - 600) / 2;

	float rel_x = cord.x * 600 / 2500;
	float rel_y = cord.y * 600 / 2500;

	float c_size = size * 300 / 1250;

	x = x + rel_x - c_size + 300;
	y = y + rel_y - c_size + 300;

	sf::CircleShape circle(c_size);

	circle.setPosition(x, y);

	circle.setFillColor(sf::Color(255, 255, 255, 0));
	circle.setOutlineColor(c);
	circle.setOutlineThickness(2.f);

	circle.setPointCount(300);

	IWindow::AddToRenderList(circle);
}

void match_t::DrawCircle()
{
	IWindow::RenderOverlay((1280 - 600) / 2, 60, 600, 600, 255, 255, 255, 16);

	DrawOneCircleOnMap(vecCircleMiddle, circle_size, sf::Color(255, 255, 255, 128));
	DrawOneCircleOnMap(vecNextMiddle, next_circle_size, sf::Color(0, 255, 128, 128));

}

int match_t::GetAliveTeams()
{
	int a = 0;
	bool t[100];
	for (int i = 0; i < 100; i++)
		t[i] = false;

	for (int i = 0; i < 100; i++)
		if (players[i]->bAlive)
			t[players[i]->iTeam] = true;

	for (int i = 0; i < 100; i++)
		if (t[i])a++;



	return a;
}

int match_t::GetAlivePlayers()
{
	int a = 0;
	for (int i = 0; i < 100; i++)
		if (players[i]->bAlive)a++;



	return a;
}

void match_t::DrawPlayers()
{
	for (int i = 0; i < 100; i++)
	{
		if (players[i]->bAlive)
		{
			if (players[i]->iID == 0 && players[i]->iTargetID == -1)
				DrawOneCircleOnMap(players[i]->vecPosition, 1, sf::Color(255, 255, 255, 255));
			else if(players[i]->iTeam == players[0]->iTeam && players[i]->iTargetID == -1)
				DrawOneCircleOnMap(players[i]->vecPosition, 1, sf::Color(0, 255, 128, 255));
			else if (players[i]->iTargetID == -1)
			{
				if(players[i] ->s_iEliminations >= 10)

					DrawOneCircleOnMap(players[i]->vecPosition, 1, sf::Color(128, 255, 255, 255));
				else if (players[i]->s_iEliminations >= 5)
					DrawOneCircleOnMap(players[i]->vecPosition, 1, sf::Color(0, 160, 255, 255));
				else
				DrawOneCircleOnMap(players[i]->vecPosition, 1, sf::Color(0, 0, 255, 255));
			}
			else
				DrawOneCircleOnMap(players[i]->vecPosition, 1, sf::Color(255, 120, 0, 255));
		}

		DrawOneCircleOnMap(hotspot, 16, sf::Color(64, 64, 64, 32));
	}

	if (players[0]->bAlive)DrawViewRange();
}

void match_t::DrawViewRange()
{
	int spot_range;
	auto p = players[0];
	if (p->hasSniper())spot_range = 200;
	else if (p->hasAR())spot_range = p->itMid_range.iRange;
	else if (p->hasSecondary())spot_range = p->itSecondary_weapon.iRange;
	else spot_range = p->itShotgun.iRange;

	DrawOneCircleOnMap(players[0]->vecPosition, spot_range, sf::Color(128, 128, 128, 64));
}

void match_t::DrawLoadout()
{
	auto p = players[0];
	char buffer[300];
	sprintf(buffer, "Health: %d\nArmor: %d\n%s\n%s\n%s\n%s\nEliminations:%d (%d)\nPlayers left: %d\nPosition: %d", p->iHealth, p->iArmor,
		(p->hasShotgun() ? (p->itShotgun.szName) : ("")),
		(p->hasSecondary() ? (p->itSecondary_weapon.szName) : ("")),
		(p->hasAR() ? (p->itMid_range.szName) : ("")),
		(p->hasSniper() ? (p->itSniper.szName) : ("")), p->s_iEliminations, p->GetTotalElims(),
		GetAlivePlayers(),
		((p->bAlive)?GetAliveTeams():(p->s_Position))
	);

	IWindow::RenderText(0, 0, 16, 255, 255, 255, 255, buffer);

	IWindow::RenderOverlay(20, 660, 300, 10, 32, 32, 32, 255);
	IWindow::RenderOverlay(20, 680, 300, 10, 32, 32, 32, 255);
	IWindow::RenderOverlay(20, 660, p->iHealth*3, 10, 32, 255, 80, 255);
	IWindow::RenderOverlay(20, 680, p->iArmor * 3, 10, 32, 160, 255, 255);


	static bool bLoaded = false;
	static file_t f[20];
	static sf::Texture t[20];
	static sf::Sprite a[20];

	if (!bLoaded)
	{
		f[0] = g_Files.GetFileByName("t_tactical.png");
		f[1] = g_Files.GetFileByName("t_pump.png");
		f[2] = g_Files.GetFileByName("t_heavyshotgun.png");
		f[3] = g_Files.GetFileByName("t_pistol.png");
		f[4] = g_Files.GetFileByName("t_supp_pistol.png");
		f[5] = g_Files.GetFileByName("t_smg.png");
		f[6] = g_Files.GetFileByName("t_compact.png");
		f[7] = g_Files.GetFileByName("t_dual.png");
		f[8] = g_Files.GetFileByName("t_m4a1.png");
		f[9] = g_Files.GetFileByName("t_scar.png");
		f[10] = g_Files.GetFileByName("t_heavyar.png");
		f[11] = g_Files.GetFileByName("t_deagle.png");
		f[12] = g_Files.GetFileByName("t_hunt.png");
		f[13] = g_Files.GetFileByName("t_bolt.png");
		f[14] = g_Files.GetFileByName("t_heavysniper.png");

		for (int i = 0; i < 15; i++)
		{
			t[i].loadFromMemory(f[i].loc_in_mem, f[i].size);
			a[i].setTexture(t[i]);
			a[i].setScale(sf::Vector2f(150.f / 128, 150.f / 128));
		}
		bLoaded = true;
	}



	int shotgun = -1, secondary = -1, ar = -1, sniper = -1;
	if (p->itShotgun.doesExist)
	{
		if (p->itShotgun.iID < 110)shotgun = 0;
		else if (p->itShotgun.iID < 120)shotgun = 1;
		else shotgun = 2;
	}
	if (p->itSecondary_weapon.doesExist)
	{
		if (p->itSecondary_weapon.iID < 202)secondary = 3;
		else if (p->itSecondary_weapon.iID < 210)secondary = 4;
		else if (p->itSecondary_weapon.iID < 220)secondary = 5;
		else if (p->itSecondary_weapon.iID < 230)secondary = 6;
		else secondary = 7;
	}
	if (p->itMid_range.doesExist)
	{
		if (p->itMid_range.iID < 303)ar = 8;
		else if (p->itMid_range.iID < 310)ar = 9;
		else if (p->itMid_range.iID < 320)ar = 10;
		else ar = 11;
	}
	if (p->itSniper.doesExist)
	{
		if (p->itSniper.iID < 410)sniper = 12;
		else if (p->itSniper.iID < 420)sniper = 13;
		else sniper = 14;
	}

	char shg[16], sec[16], arr[16], sni[16];



	IWindow::RenderOverlay(1110, 30, 150, 150, 32, 32, 32, 255);
	IWindow::RenderOverlay(1110, 200, 150, 150, 32, 32, 32, 255);
	IWindow::RenderOverlay(1110, 370, 150, 150, 32, 32, 32, 255);
	IWindow::RenderOverlay(1110, 540, 150, 150, 32, 32, 32, 255);

	if(p->itShotgun.doesExist)
	if(p->itShotgun.iRarity == 0)IWindow::RenderOverlay(1110, 30, 150, 150, 192, 192, 192, 255);
	else if (p->itShotgun.iRarity == 1)IWindow::RenderOverlay(1110, 30, 150, 150, 90, 180, 0, 255);
	else if (p->itShotgun.iRarity == 2)IWindow::RenderOverlay(1110, 30, 150, 150, 60, 190, 250, 255);
	else if (p->itShotgun.iRarity == 3)IWindow::RenderOverlay(1110, 30, 150, 150, 200, 105, 235, 255);
	else if (p->itShotgun.iRarity == 4)IWindow::RenderOverlay(1110, 30, 150, 150, 240, 150, 40, 255);
	
	if(p->itSecondary_weapon.doesExist)
	if (p->itSecondary_weapon.iRarity == 0)IWindow::RenderOverlay(1110, 200, 150, 150, 192, 192, 192, 255);
	else if (p->itSecondary_weapon.iRarity == 1)IWindow::RenderOverlay(1110, 200, 150, 150, 90, 180, 0, 255);
	else if (p->itSecondary_weapon.iRarity == 2)IWindow::RenderOverlay(1110, 200, 150, 150, 60, 190, 250, 255);
	else if (p->itSecondary_weapon.iRarity == 3)IWindow::RenderOverlay(1110, 200, 150, 150, 200, 105, 235, 255);
	else if (p->itSecondary_weapon.iRarity == 4)IWindow::RenderOverlay(1110, 200, 150, 150, 240, 150, 40, 255);

	if(p->itMid_range.doesExist)
	if (p->itMid_range.iRarity == 0)IWindow::RenderOverlay(1110, 370, 150, 150, 192, 192, 192, 255);
	else if (p->itMid_range.iRarity == 1)IWindow::RenderOverlay(1110, 370, 150, 150, 90, 180, 0, 255);
	else if (p->itMid_range.iRarity == 2)IWindow::RenderOverlay(1110, 370, 150, 150, 60, 190, 250, 255);
	else if (p->itMid_range.iRarity == 3)IWindow::RenderOverlay(1110, 370, 150, 150, 200, 105, 235, 255);
	else if (p->itMid_range.iRarity == 4)IWindow::RenderOverlay(1110, 370, 150, 150, 240, 150, 40, 255);

	if(p->itSniper.doesExist)
	if (p->itSniper.iRarity == 0)IWindow::RenderOverlay(1110, 540, 150, 150, 192, 192, 192, 255);
	else if (p->itSniper.iRarity == 1)IWindow::RenderOverlay(1110, 540, 150, 150, 90, 180, 0, 255);
	else if (p->itSniper.iRarity == 2)IWindow::RenderOverlay(1110, 540, 150, 150, 60, 190, 250, 255);
	else if (p->itSniper.iRarity == 3)IWindow::RenderOverlay(1110, 540, 150, 150, 200, 105, 235, 255);
	else if (p->itSniper.iRarity == 4)IWindow::RenderOverlay(1110, 540, 150, 150, 240, 150, 40, 255);

	if (shotgun != -1)
	{
		a[shotgun].setPosition(1110, 30);
		IWindow::AddToRenderList(a[shotgun]);
		sprintf(shg, "%d", p->itShotgun.iBullets);
		IWindow::RenderText(1110, 130, 28, 255, 255, 255, 255, shg);

	}
	if (secondary != -1)
	{
		a[secondary].setPosition(1110, 200);
		IWindow::AddToRenderList(a[secondary]);
		sprintf(sec, "%d", p->itSecondary_weapon.iBullets);
		IWindow::RenderText(1110, 300, 28, 255, 255, 255, 255, sec);
	}
	if (ar != -1)
	{
		a[ar].setPosition(1110, 370);
		IWindow::AddToRenderList(a[ar]);
		sprintf(arr, "%d", p->itMid_range.iBullets);
		IWindow::RenderText(1110, 470, 28, 255, 255, 255, 255, arr);
	}
	if (sniper != -1)
	{
		a[sniper].setPosition(1110, 540);
		IWindow::AddToRenderList(a[sniper]);
		sprintf(sni, "%d", p->itSniper.iBullets);
		IWindow::RenderText(1110, 640, 28, 255, 255, 255, 255, sni);
	}




}
void match_t::DrawIngameInformation()
{
	auto p = players[0];
	char buffer[300];
	sprintf(buffer, "Shots flicked: %d\nShots tracked: %d\nShots predicted: %d\nShots dodged: %d\nItems found: %d\nSeconds survived:%d",
		p->s_iShotsFlicked,p->s_iShotsTracked,p->s_iShotsPredicted,p->s_iShotsDodged,p->s_iItemsFound,p->s_iSecondsSurvived);


	char tuffer[2500] = "";
	auto t = &inInfo;

	while (t != nullptr)
	{
		static char* L[] = { "","Noob ", "Sweaty " };
		int ki = 0, ta = 0;

		if (players[t->killer]->GetTotalSkill() >= players[0]->GetTotalSkill() * 1.5)ki = 2;
		else if (players[t->killer]->GetTotalSkill() * 2 <= players[0]->GetTotalSkill())ki = 1;

		if (players[t->target]->GetTotalSkill() >= players[0]->GetTotalSkill() * 1.5)ta = 2;
		else if (players[t->target]->GetTotalSkill() * 2 <= players[0]->GetTotalSkill())ta = 1;

		if (t->next)
		sprintf(tuffer, "%s%s%d eliminated %s%d with %s\n",tuffer, L[ki],t->killer, L[ta],t->target, g_ItemList[t->weapon].szName);
		t = t->next;
	}





	IWindow::RenderText(0, 200, 16, 255, 255, 255, 255, buffer);
	IWindow::RenderText(0, 300, 16, 255, 255, 255, 128, tuffer);
}

void match_t::DrawEndgameInformation()
{
	auto p = players[0];
	char buffer[300];

	buffer[0] = '\0';

	for (int i = 0; i < 100; i++)
	{
		if (players[i]->bAlive)

		{
			auto  a = players[i]->gsGamestyle->skill;
			int b = a.atk_flick + a.atk_predict + a.atk_track + a.defending + a.looting;
			sprintf(buffer, "%sPlayer: %d with %d kills won the game (%d)\n", buffer, i, players[i]->s_iEliminations,b);
		}
	}

	IWindow::RenderText(400, 40, 16, 255, 255, 255, 255, buffer);
}

void match_t::SimulatePlayers()
{
	for (int i = 0; i < 100; i++)
	{
		if (players[i]->bAlive)
		{
			players[i]->Think();
			players[i]->s_iSecondsSurvived++;
		}
	}
}

void match_t::SimulateTick()
{
	if (GetAliveTeams() > 1)
	{
		SimulatePlayers();
		SimulateCircle();
	}
	else for(int i = 0; i < 100;i++)players[i]->iTargetID = -1;


	//if (!players[0]->bAlive || GetAliveTeams() == 1)
	{
		DrawIngameInformation();
	}
	if (GetAliveTeams() <= 1)DrawEndgameInformation();

	DrawCircle();


	DrawPlayers();

	DrawLoadout();








}
gamestyle_t* match_t::GenerateGameStyle(int matches_played)
{
	auto gs = new gamestyle_t;
	gs->shotgun_preference = Random(0,2);
	gs->ar_preference = Random(0,2);
	gs->secondary_preference = Random(0,2);

	int m_played = 0;

	if (matches_played < 100)
	{
		int r = Random(1, 100);
		if (r <= 50) // beginner
		{
			m_played = Random(0, 2)*Random(0, 2)*Random(0,2);
		}
		else if (r <= 75)
		{
			m_played = Random(0, 4)*Random(0, 3)*Random(1,2);
		}
		else if (r <= 95)
		{
			m_played = Random(1, 4)*Random(1, 3)*Random(1, 2) * Random(1, 2);
		}
		else m_played = Random(50, 90);
	}
	else
	{
		int r = Random(1, 500);
		if (r <= 175)
		{
			m_played = Random(0, matches_played / 10) * Random(0,1);
		}
		else if (r <= 375)
		{
			m_played = Random(matches_played / 10, matches_played / 4);
		}
		else if (r <= 485)
		{
			m_played = Random(matches_played / 4, matches_played / 3);
		}
		else if (r <= 497)
		{
			m_played = Random(matches_played / 3, matches_played / 2);
		}
		else m_played = matches_played;
	}

	int total_skills = m_played * 6;


	for (int i = 0; i < total_skills;)
	{
		int step = 1;
		if (total_skills > 2000)step = 10;
		else if (total_skills > 100)step = 5;

		int r = Random(1, 5);

		if (r == 0)gs->skill.atk_flick += step;
		else if (r == 1)gs->skill.atk_track += step;
		else if (r == 2)gs->skill.atk_predict += step;
		else if (r == 3)gs->skill.defending += step;
		else if (r == 4)gs->skill.looting += step;

		i += step;
	}


	return gs;
}


void match_t::Delete()
{
	for (int i = 1; i < 100; i++)
	{
		delete[] players[i]->gsGamestyle;
		delete[] players[i];
	}

	inInfo.Clear();
}

void match_t::SetupMatch(gamestyle_t* gsLocal, int gametype, int matches_played, int hotdroplevel)
{
	 hotspot = Vector(Random(-800, 800), Random(-800, 800), 0);
	 //inInfo.Clear();
	current_circle = 1;
	ticks_from_circle_change = 200;
	circle_size = 2500.f;
	next_circle_size = 2500.f;
	vecCircleMiddle = Vector(0, 0, 0);
	vecNextMiddle = Vector(0, 0, 0);

	if (gametype == 0)
	{
		

		for (int i = 0; i < 100; i++)
		{
			players[i] = new unit_t;
			players[i]->iTeam = i;
			players[i]->bAlive = true;
			players[i]->iArmor = 0;
			players[i]->iHealth = 100;
			players[i]->iTargetID = -1;

			int r = Random(1, 100);

			if (hotdroplevel == 0 && i == 0)r = 100;
			if (hotdroplevel == 1&& i == 0)r = 30;
			if (hotdroplevel == 2&& i == 0)r = 5;

			if (r < 10)
			{
				players[i]->vecPosition = Vector(hotspot.x + Random(-50, 25), hotspot.y + Random(-50, 50), 0);
			}
			else if (r < 33)
			{
				players[i]->vecPosition = Vector(hotspot.x + Random(-250, 250), hotspot.y + Random(-250, 250), 0);
			}
			else
				players[i]->vecPosition = Vector(Random(-1250, 1250), Random(-1250, 1250), 0);
			players[i]->pMatch = this;
			players[i]->iID = i;

			players[i]->gsGamestyle = GenerateGameStyle(matches_played);


		}

	}
	else if (gametype == 1)
	{
		for (int t = 0; t < 50; t++)
		{
			Vector teampos;
			int r = Random(1, 100);
			if (r < 10)
			{
				teampos = Vector(hotspot.x + Random(-50, 25), hotspot.y + Random(-50, 50), 0);
			}
			else if (r < 33)
			{
				teampos = Vector(hotspot.x + Random(-250, 250), hotspot.y + Random(-250, 250), 0);
			}
			else
				teampos = Vector(Random(-1150, 1150), Random(-1150, 1150), 0);
			for (int i = 0; i < 2; i++)
			{
				players[2*t+i] = new unit_t;
				players[2*t+i]->iTeam = t;
				players[2*t+i]->bAlive = true;
				players[2*t+i]->iArmor = 0;
				players[2*t+i]->iHealth = 100;
				players[2*t+i]->iTargetID = -1;

				players[2 * t + i]->vecPosition = Vector(teampos.x + Random(-100, 100), teampos.y + Random(-100, 100), 0);


				
				players[2*t+i]->pMatch = this;
				players[2*t+i]->iID = 2*t+i;

				players[2*t+i]->gsGamestyle = GenerateGameStyle(matches_played);

			}
		}
	}
	else if (gametype ==2)
	{
		for (int t = 0; t < 25; t++)
		{


			Vector teampos;
			int r = Random(1, 100);



			if (r < 10)
			{
				teampos = Vector(hotspot.x + Random(-50, 50), hotspot.y + Random(-50, 50), 0);
			}
			else if (r < 33)
			{
				teampos = Vector(hotspot.x + Random(-250, 250), hotspot.y + Random(-250, 250), 0);
			}
			else
				teampos = Vector(Random(-1150, 1150), Random(-1150, 1150), 0);
			for (int i = 0; i < 4; i++)
			{
				players[4 * t + i] = new unit_t;
				players[4 * t + i]->iTeam = t;
				players[4 * t + i]->bAlive = true;
				players[4 * t + i]->iArmor = 0;
				players[4 * t + i]->iHealth = 100;
				players[4 * t + i]->iTargetID = -1;

				players[4 * t + i]->vecPosition = Vector(teampos.x + Random(-100, 100), teampos.y + Random(-100, 100), 0);



				players[4 * t + i]->pMatch = this;
				players[4 * t + i]->iID = 4 * t + i;

				players[4 * t + i]->gsGamestyle = GenerateGameStyle(matches_played);

			}
		}
	}
	else if (gametype == 3)
	{
		for (int t = 0; t < 50; t++)
		{
			Vector teampos;
			int r = Random(1, 100);
			if (t == 0 && hotdroplevel == 0)r = 100;
			if (t == 0 && hotdroplevel == 1)r = 30;
			if (t == 0 && hotdroplevel == 2)r = 5;
			if (r < 10)
			{
				teampos = Vector(hotspot.x + Random(-50, 25), hotspot.y + Random(-50, 50), 0);
			}
			else if (r < 33)
			{
				teampos = Vector(hotspot.x + Random(-250, 250), hotspot.y + Random(-250, 250), 0);
			}
			else
				teampos = Vector(Random(-1150, 1150), Random(-1150, 1150), 0);
			for (int i = 0; i < 2; i++)
			{

				players[2 * t + i] = new unit_t;
				players[2 * t + i]->iTeam = t;
				players[2 * t + i]->bAlive = true;
				if (t == 0 && i != 0)
					players[2 * t + i]->bAlive = false;
				players[2 * t + i]->iArmor = 0;
				players[2 * t + i]->iHealth = 100;
				players[2 * t + i]->iTargetID = -1;

				players[2 * t + i]->vecPosition = Vector(teampos.x + Random(-100, 100), teampos.y + Random(-100, 100), 0);



				players[2 * t + i]->pMatch = this;
				players[2 * t + i]->iID = 2 * t + i;

				players[2 * t + i]->gsGamestyle = GenerateGameStyle(matches_played);

			}
		}
	}
	else
	{
		for (int t = 0; t < 25; t++)
		{
			Vector teampos;
			int r = Random(1, 100);
			if (t == 0 && hotdroplevel == 0)r = 100;
			if (t == 0 && hotdroplevel == 1)r = 30;
			if (t == 0 && hotdroplevel == 2)r = 5;
			if (r < 10)
			{
				teampos = Vector(hotspot.x + Random(-50, 25), hotspot.y + Random(-50, 50), 0);
			}
			else if (r < 33)
			{
				teampos = Vector(hotspot.x + Random(-250, 250), hotspot.y + Random(-250, 250), 0);
			}
			else
				teampos = Vector(Random(-1150, 1150), Random(-1150, 1150), 0);
			for (int i = 0; i < 4; i++)
			{
				players[4 * t + i] = new unit_t;
				players[4 * t + i]->iTeam = t;
				players[4 * t + i]->bAlive = true;
				if (t == 0 && i != 0)
					players[2 * t + i]->bAlive = false;
				players[4 * t + i]->iArmor = 0;
				players[4 * t + i]->iHealth = 100;
				players[4 * t + i]->iTargetID = -1;

				players[4 * t + i]->vecPosition = Vector(teampos.x + Random(-100, 100), teampos.y + Random(-100, 100), 0);



				players[4 * t + i]->pMatch = this;
				players[4 * t + i]->iID = 4 * t + i;

				players[4 * t + i]->gsGamestyle = GenerateGameStyle(matches_played);

			}
		}
	}

	players[0]->gsGamestyle = gsLocal;

}



void game_t::StartGame()
{
	item_t Item;
	Item.SetUpAllWeapons();

	gsGameStyle.ar_preference = 0;
	gsGameStyle.secondary_preference = 0;
	gsGameStyle.shotgun_preference = 0;
	
	gsGameStyle.skill.atk_flick = 3;
	gsGameStyle.skill.atk_predict = 3;
	gsGameStyle.skill.atk_track = 3;
	gsGameStyle.skill.defending = 5;
	gsGameStyle.skill.looting = 1;
	
	/*
	gsGameStyle.skill.atk_flick = 100;
	gsGameStyle.skill.atk_predict = 100;
	gsGameStyle.skill.atk_track = 100;
	gsGameStyle.skill.defending = 100;
	gsGameStyle.skill.looting = 100;
	//

	if (GetAsyncKeyState(VK_RETURN))bInMatch = false;
	bInMatch = false;
}


void game_t::DrawStatistics()
{
	static bool bLoaded = false;
	static file_t f = g_Files.GetFileByName("stat_bg.png");
	static sf::Texture t;
	static sf::Sprite a;

	if (!bLoaded)
	{
		bLoaded = true;
		t.loadFromMemory(f.loc_in_mem, f.size);
		a.setTexture(t);
	}

	IWindow::AddToRenderList(a);


	char buffer[256];
	float winrate = ((float)psSolos.iWins) / psSolos.iMatches * 100;
	float kdr = ((float)psSolos.iKills) / (psSolos.iMatches - psSolos.iWins);
	if (psSolos.iMatches == 0) {
		kdr = 0; winrate = 0;
	}
	else if (psSolos.iMatches - psSolos.iWins == 0)kdr = psSolos.iKills;



	if (bShowOverallStats)
	{
		{
			auto dum = psSolos;
			int eks = 100;


			winrate = ((float)dum.iWins) / dum.iMatches * 100;
			kdr = ((float)dum.iKills) / (dum.iMatches - dum.iWins);
			if (dum.iMatches == 0) {
				kdr = 0; winrate = 0;
			}
			else if (dum.iMatches - dum.iWins == 0)kdr = dum.iKills;

			char mp[16], t25[16], t10[16], win[16], wr[16], el[16], kd[16], mk[16];

			sprintf(mp, "%d", dum.iMatches);
			sprintf(t25, "%d", dum.iTopSmalls);
			sprintf(t10, "%d", dum.iTopBigs);
			sprintf(win, "%d", dum.iWins);
			sprintf(el, "%d", dum.iKills);
			sprintf(wr, "%.2f%%", winrate);
			sprintf(kd, "%.2f", kdr);
			sprintf(mk, "%d", dum.iMostKills);

			IWindow::RenderText(eks, 100, 24, 255, 255, 255, 255, "Solos");
			IWindow::RenderText(eks, 125, 18, 255, 255, 255, 255, "Matches Played:");
			IWindow::RenderText(eks, 145, 18, 255, 255, 255, 255, "Top 25's:");
			IWindow::RenderText(eks, 195, 18, 255, 255, 255, 255, "Top 10's:");
			IWindow::RenderText(eks, 245, 18, 255, 255, 255, 255, "Victories:");
			IWindow::RenderText(eks, 295, 18, 255, 255, 255, 255, "Winrate:");
			IWindow::RenderText(eks, 345, 18, 255, 255, 255, 255, "Eliminations:");
			IWindow::RenderText(eks, 395, 18, 255, 255, 255, 255, "K/D Ratio:");
			IWindow::RenderText(eks, 445, 18, 255, 255, 255, 255, "Most Kills:");

			IWindow::RenderText(eks + 220, 124, 20, 255, 255, 255, 255, mp);
			IWindow::RenderText(eks + 220, 144, 20, 255, 255, 255, 255, t25);
			IWindow::RenderText(eks + 220, 194, 20, 255, 255, 255, 255, t10);
			IWindow::RenderText(eks + 220, 244, 20, 255, 255, 255, 255, win);
			if (winrate > 20.f)
				IWindow::RenderText(eks + 220, 294, 20, 0, 255, 0, 255, wr);
			else if (winrate > 7.5f)
				IWindow::RenderText(eks + 220, 294, 20, 255, 255, 0, 255, wr);
			else IWindow::RenderText(eks + 220, 294, 20, 255, 0, 0, 255, wr);
			IWindow::RenderText(eks + 220, 344, 20, 255, 255, 255, 255, el);
			if (kdr > 5.f)
				IWindow::RenderText(eks + 220, 394, 20, 0, 255, 0, 255, kd);
			else if (kdr > 2.f)
				IWindow::RenderText(eks + 220, 394, 20, 255, 255, 0, 255, kd);
			else IWindow::RenderText(eks + 220, 394, 20, 255, 0, 0, 255, kd);
			IWindow::RenderText(eks + 220, 444, 20, 255, 255, 255, 255, mk);

			for (int i = 0; i < 6; i++)
				IWindow::RenderOverlay(eks, 170 + i * 50, 300, 15, 32, 32, 32, 255);

			IWindow::RenderOverlay(eks + 2, 170, 296 * dum.iTopSmalls / max(dum.iMatches, 1), 11, 0, 192, 0, 255);
			IWindow::RenderOverlay(eks + 2, 220, 296 * dum.iTopBigs / max(1, dum.iMatches), 11, 0, 192, 0, 255);
			IWindow::RenderOverlay(eks + 2, 270, 296 * dum.iWins / max(1, dum.iMatches), 11, 0, 192, 0, 255);
			IWindow::RenderOverlay(eks + 2, 320, min(296 * dum.iWins / max(1, dum.iMatches) * 5, 296), 11, 0, 192, 0, 255);
			IWindow::RenderOverlay(eks + 2, 370, min(296 * dum.iKills / max(1, dum.iMatches) / 5, 296), 11, 0, 192, 0, 255);
			IWindow::RenderOverlay(eks + 2, 420, min(296 * kdr / 5, 296), 11, 0, 192, 0, 255);
		}

		{
			auto dum = psDuos;
			int eks = 490;


			winrate = ((float)dum.iWins) / dum.iMatches * 100;
			kdr = ((float)dum.iKills) / (dum.iMatches - dum.iWins);
			if (dum.iMatches == 0) {
				kdr = 0; winrate = 0;
			}
			else if (dum.iMatches - dum.iWins == 0)kdr = dum.iKills;

			char mp[16], t25[16], t10[16], win[16], wr[16], el[16], kd[16], mk[16];

			sprintf(mp, "%d", dum.iMatches);
			sprintf(t25, "%d", dum.iTopSmalls);
			sprintf(t10, "%d", dum.iTopBigs);
			sprintf(win, "%d", dum.iWins);
			sprintf(el, "%d", dum.iKills);
			sprintf(wr, "%.2f%%", winrate);
			sprintf(kd, "%.2f", kdr);
			sprintf(mk, "%d", dum.iMostKills);

			IWindow::RenderText(eks, 100, 24, 255, 255, 255, 255, "Duos");
			IWindow::RenderText(eks, 125, 18, 255, 255, 255, 255, "Matches Played:");
			IWindow::RenderText(eks, 145, 18, 255, 255, 255, 255, "Top 12's:");
			IWindow::RenderText(eks, 195, 18, 255, 255, 255, 255, "Top 6's:");
			IWindow::RenderText(eks, 245, 18, 255, 255, 255, 255, "Victories:");
			IWindow::RenderText(eks, 295, 18, 255, 255, 255, 255, "Winrate:");
			IWindow::RenderText(eks, 345, 18, 255, 255, 255, 255, "Eliminations:");
			IWindow::RenderText(eks, 395, 18, 255, 255, 255, 255, "K/D Ratio:");
			IWindow::RenderText(eks, 445, 18, 255, 255, 255, 255, "Most Kills:");

			IWindow::RenderText(eks + 220, 124, 20, 255, 255, 255, 255, mp);
			IWindow::RenderText(eks + 220, 144, 20, 255, 255, 255, 255, t25);
			IWindow::RenderText(eks + 220, 194, 20, 255, 255, 255, 255, t10);
			IWindow::RenderText(eks + 220, 244, 20, 255, 255, 255, 255, win);
			if (winrate > 20.f)
				IWindow::RenderText(eks + 220, 294, 20, 0, 255, 0, 255, wr);
			else if (winrate > 7.5f)
				IWindow::RenderText(eks + 220, 294, 20, 255, 255, 0, 255, wr);
			else IWindow::RenderText(eks + 220, 294, 20, 255, 0, 0, 255, wr);
			IWindow::RenderText(eks + 220, 344, 20, 255, 255, 255, 255, el);
			if (kdr > 5.f)
				IWindow::RenderText(eks + 220, 394, 20, 0, 255, 0, 255, kd);
			else if (kdr > 2.f)
				IWindow::RenderText(eks + 220, 394, 20, 255, 255, 0, 255, kd);
			else IWindow::RenderText(eks + 220, 394, 20, 255, 0, 0, 255, kd);
			IWindow::RenderText(eks + 220, 444, 20, 255, 255, 255, 255, mk);

			for (int i = 0; i < 6; i++)
				IWindow::RenderOverlay(eks, 170 + i * 50, 300, 15, 32, 32, 32, 255);

			IWindow::RenderOverlay(eks + 2, 170, 296 * dum.iTopSmalls / max(dum.iMatches, 1), 11, 0, 192, 0, 255);
			IWindow::RenderOverlay(eks + 2, 220, 296 * dum.iTopBigs / max(1, dum.iMatches), 11, 0, 192, 0, 255);
			IWindow::RenderOverlay(eks + 2, 270, 296 * dum.iWins / max(1, dum.iMatches), 11, 0, 192, 0, 255);
			IWindow::RenderOverlay(eks + 2, 320, min(296 * dum.iWins / max(1, dum.iMatches) * 5, 296), 11, 0, 192, 0, 255);
			IWindow::RenderOverlay(eks + 2, 370, min(296 * dum.iKills / max(1, dum.iMatches) / 5, 296), 11, 0, 192, 0, 255);
			IWindow::RenderOverlay(eks + 2, 420, min(296 * kdr / 5, 296), 11, 0, 192, 0, 255);
		}


		{
			auto dum = psSquads;
			int eks = 880;


			winrate = ((float)dum.iWins) / dum.iMatches * 100;
			kdr = ((float)dum.iKills) / (dum.iMatches - dum.iWins);
			if (dum.iMatches == 0) {
				kdr = 0; winrate = 0;
			}
			else if (dum.iMatches - dum.iWins == 0)kdr = dum.iKills;

			char mp[16], t25[16], t10[16], win[16], wr[16], el[16], kd[16], mk[16];

			sprintf(mp, "%d", dum.iMatches);
			sprintf(t25, "%d", dum.iTopSmalls);
			sprintf(t10, "%d", dum.iTopBigs);
			sprintf(win, "%d", dum.iWins);
			sprintf(el, "%d", dum.iKills);
			sprintf(wr, "%.2f%%", winrate);
			sprintf(kd, "%.2f", kdr);
			sprintf(mk, "%d", dum.iMostKills);

			IWindow::RenderText(eks, 100, 24, 255, 255, 255, 255, "Squads");
			IWindow::RenderText(eks, 125, 18, 255, 255, 255, 255, "Matches Played:");
			IWindow::RenderText(eks, 145, 18, 255, 255, 255, 255, "Top 6's:");
			IWindow::RenderText(eks, 195, 18, 255, 255, 255, 255, "Top 3's:");
			IWindow::RenderText(eks, 245, 18, 255, 255, 255, 255, "Victories:");
			IWindow::RenderText(eks, 295, 18, 255, 255, 255, 255, "Winrate:");
			IWindow::RenderText(eks, 345, 18, 255, 255, 255, 255, "Eliminations:");
			IWindow::RenderText(eks, 395, 18, 255, 255, 255, 255, "K/D Ratio:");
			IWindow::RenderText(eks, 445, 18, 255, 255, 255, 255, "Most Kills:");

			IWindow::RenderText(eks + 220, 124, 20, 255, 255, 255, 255, mp);
			IWindow::RenderText(eks + 220, 144, 20, 255, 255, 255, 255, t25);
			IWindow::RenderText(eks + 220, 194, 20, 255, 255, 255, 255, t10);
			IWindow::RenderText(eks + 220, 244, 20, 255, 255, 255, 255, win);
			if (winrate > 20.f)
				IWindow::RenderText(eks + 220, 294, 20, 0, 255, 0, 255, wr);
			else if (winrate > 7.5f)
				IWindow::RenderText(eks + 220, 294, 20, 255, 255, 0, 255, wr);
			else IWindow::RenderText(eks + 220, 294, 20, 255, 0, 0, 255, wr);
			IWindow::RenderText(eks + 220, 344, 20, 255, 255, 255, 255, el);
			if (kdr > 5.f)
				IWindow::RenderText(eks + 220, 394, 20, 0, 255, 0, 255, kd);
			else if (kdr > 2.f)
				IWindow::RenderText(eks + 220, 394, 20, 255, 255, 0, 255, kd);
			else IWindow::RenderText(eks + 220, 394, 20, 255, 0, 0, 255, kd);
			IWindow::RenderText(eks + 220, 444, 20, 255, 255, 255, 255, mk);

			for (int i = 0; i < 6; i++)
				IWindow::RenderOverlay(eks, 170 + i * 50, 300, 15, 32, 32, 32, 255);

			IWindow::RenderOverlay(eks + 2, 170, 296 * dum.iTopSmalls / max(dum.iMatches, 1), 11, 0, 192, 0, 255);
			IWindow::RenderOverlay(eks + 2, 220, 296 * dum.iTopBigs / max(1, dum.iMatches), 11, 0, 192, 0, 255);
			IWindow::RenderOverlay(eks + 2, 270, 296 * dum.iWins / max(1, dum.iMatches), 11, 0, 192, 0, 255);
			IWindow::RenderOverlay(eks + 2, 320, min(296 * dum.iWins / max(1, dum.iMatches) * 5, 296), 11, 0, 192, 0, 255);
			IWindow::RenderOverlay(eks + 2, 370, min(296 * dum.iKills / max(1, dum.iMatches) / 5, 296), 11, 0, 192, 0, 255);
			IWindow::RenderOverlay(eks + 2, 420, min(296 * kdr / 5, 296), 11, 0, 192, 0, 255);
		}

		int ov_elim = psSolos.iKills + psDuos.iKills + psSquads.iKills;
		int ov_mat = psSolos.iMatches + psDuos.iMatches + psSquads.iMatches;
		int ov_win = psSolos.iWins + psDuos.iWins + psSquads.iWins;
		float kdr = 0;
		float wr = 0;

		if (ov_mat == 0)
		{
			kdr = 0, wr = 0;
		}
		else
		{
			if (ov_mat - ov_win == 0)kdr = ov_elim;
			else kdr = ((float)(ov_elim)) / (ov_mat - ov_win);
			wr = ((float)ov_win) / ov_mat * 100; 
		}

		IWindow::RenderText(150, 30, 30, 255, 255, 255, 255, "Overall");

		char mat[32], wn[32] , eli[32], winr[32], kd[32];

		sprintf(mat, "Matches: %d", ov_mat);
		sprintf(wn, "Wins: %d", ov_win);
		sprintf(eli, "Kills: %d", ov_elim);
		sprintf(winr, "Winrate: %.1f%%", wr);
		sprintf(kd, "KDR: %.2f", kdr);

		IWindow::RenderText(360, 20, 20, 255, 255, 255, 255, mat);
		IWindow::RenderText(360, 60, 20, 255, 255, 255, 255, wn);
		IWindow::RenderText(600, 20, 20, 255, 255, 255, 255, eli);
		IWindow::RenderText(600, 60, 20, 255, 255, 255, 255, kd);
		IWindow::RenderText(840, 35, 30, 255, 255, 255, 255, winr);

	}
	else
	{
		{
			auto dum = psSeasonSolos;
			int eks = 100;


			winrate = ((float)dum.iWins) / dum.iMatches * 100;
			kdr = ((float)dum.iKills) / (dum.iMatches - dum.iWins);
			if (dum.iMatches == 0) {
				kdr = 0; winrate = 0;
			}
			else if (dum.iMatches - dum.iWins == 0)kdr = dum.iKills;

			char mp[16], t25[16], t10[16], win[16], wr[16], el[16], kd[16], mk[16];

			sprintf(mp, "%d", dum.iMatches);
			sprintf(t25, "%d", dum.iTopSmalls);
			sprintf(t10, "%d", dum.iTopBigs);
			sprintf(win, "%d", dum.iWins);
			sprintf(el, "%d", dum.iKills);
			sprintf(wr, "%.2f%%", winrate);
			sprintf(kd, "%.2f", kdr);
			sprintf(mk, "%d", dum.iMostKills);

			IWindow::RenderText(eks, 100, 24, 255, 255, 255, 255, "Solos");
			IWindow::RenderText(eks, 125, 18, 255, 255, 255, 255, "Matches Played:");
			IWindow::RenderText(eks, 145, 18, 255, 255, 255, 255, "Top 25's:");
			IWindow::RenderText(eks, 195, 18, 255, 255, 255, 255, "Top 10's:");
			IWindow::RenderText(eks, 245, 18, 255, 255, 255, 255, "Victories:");
			IWindow::RenderText(eks, 295, 18, 255, 255, 255, 255, "Winrate:");
			IWindow::RenderText(eks, 345, 18, 255, 255, 255, 255, "Eliminations:");
			IWindow::RenderText(eks, 395, 18, 255, 255, 255, 255, "K/D Ratio:");
			IWindow::RenderText(eks, 445, 18, 255, 255, 255, 255, "Most Kills:");

			IWindow::RenderText(eks + 220, 124, 20, 255, 255, 255, 255, mp);
			IWindow::RenderText(eks + 220, 144, 20, 255, 255, 255, 255, t25);
			IWindow::RenderText(eks + 220, 194, 20, 255, 255, 255, 255, t10);
			IWindow::RenderText(eks + 220, 244, 20, 255, 255, 255, 255, win);
			if (winrate > 20.f)
				IWindow::RenderText(eks + 220, 294, 20, 0, 255, 0, 255, wr);
			else if (winrate > 7.5f)
				IWindow::RenderText(eks + 220, 294, 20, 255, 255, 0, 255, wr);
			else IWindow::RenderText(eks + 220, 294, 20, 255, 0, 0, 255, wr);
			IWindow::RenderText(eks + 220, 344, 20, 255, 255, 255, 255, el);
			if (kdr > 5.f)
				IWindow::RenderText(eks + 220, 394, 20, 0, 255, 0, 255, kd);
			else if (kdr > 2.f)
				IWindow::RenderText(eks + 220, 394, 20, 255, 255, 0, 255, kd);
			else IWindow::RenderText(eks + 220, 394, 20, 255, 0, 0, 255, kd);
			IWindow::RenderText(eks + 220, 444, 20, 255, 255, 255, 255, mk);

			for (int i = 0; i < 6; i++)
				IWindow::RenderOverlay(eks, 170 + i * 50, 300, 15, 32, 32, 32, 255);

			IWindow::RenderOverlay(eks + 2, 170, 296 * dum.iTopSmalls / max(dum.iMatches, 1), 11, 0, 192, 0, 255);
			IWindow::RenderOverlay(eks + 2, 220, 296 * dum.iTopBigs / max(1, dum.iMatches), 11, 0, 192, 0, 255);
			IWindow::RenderOverlay(eks + 2, 270, 296 * dum.iWins / max(1, dum.iMatches), 11, 0, 192, 0, 255);
			IWindow::RenderOverlay(eks + 2, 320, min(296 * dum.iWins / max(1, dum.iMatches) * 5, 296), 11, 0, 192, 0, 255);
			IWindow::RenderOverlay(eks + 2, 370, min(296 * dum.iKills / max(1, dum.iMatches) / 5, 296), 11, 0, 192, 0, 255);
			IWindow::RenderOverlay(eks + 2, 420, min(296 * kdr / 5, 296), 11, 0, 192, 0, 255);
		}

		{
			auto dum = psSeasonDuos;
			int eks = 490;


			winrate = ((float)dum.iWins) / dum.iMatches * 100;
			kdr = ((float)dum.iKills) / (dum.iMatches - dum.iWins);
			if (dum.iMatches == 0) {
				kdr = 0; winrate = 0;
			}
			else if (dum.iMatches - dum.iWins == 0)kdr = dum.iKills;

			char mp[16], t25[16], t10[16], win[16], wr[16], el[16], kd[16], mk[16];

			sprintf(mp, "%d", dum.iMatches);
			sprintf(t25, "%d", dum.iTopSmalls);
			sprintf(t10, "%d", dum.iTopBigs);
			sprintf(win, "%d", dum.iWins);
			sprintf(el, "%d", dum.iKills);
			sprintf(wr, "%.2f%%", winrate);
			sprintf(kd, "%.2f", kdr);
			sprintf(mk, "%d", dum.iMostKills);

			IWindow::RenderText(eks, 100, 24, 255, 255, 255, 255, "Duos");
			IWindow::RenderText(eks, 125, 18, 255, 255, 255, 255, "Matches Played:");
			IWindow::RenderText(eks, 145, 18, 255, 255, 255, 255, "Top 12's:");
			IWindow::RenderText(eks, 195, 18, 255, 255, 255, 255, "Top 6's:");
			IWindow::RenderText(eks, 245, 18, 255, 255, 255, 255, "Victories:");
			IWindow::RenderText(eks, 295, 18, 255, 255, 255, 255, "Winrate:");
			IWindow::RenderText(eks, 345, 18, 255, 255, 255, 255, "Eliminations:");
			IWindow::RenderText(eks, 395, 18, 255, 255, 255, 255, "K/D Ratio:");
			IWindow::RenderText(eks, 445, 18, 255, 255, 255, 255, "Most Kills:");

			IWindow::RenderText(eks + 220, 124, 20, 255, 255, 255, 255, mp);
			IWindow::RenderText(eks + 220, 144, 20, 255, 255, 255, 255, t25);
			IWindow::RenderText(eks + 220, 194, 20, 255, 255, 255, 255, t10);
			IWindow::RenderText(eks + 220, 244, 20, 255, 255, 255, 255, win);
			if (winrate > 20.f)
				IWindow::RenderText(eks + 220, 294, 20, 0, 255, 0, 255, wr);
			else if (winrate > 7.5f)
				IWindow::RenderText(eks + 220, 294, 20, 255, 255, 0, 255, wr);
			else IWindow::RenderText(eks + 220, 294, 20, 255, 0, 0, 255, wr);
			IWindow::RenderText(eks + 220, 344, 20, 255, 255, 255, 255, el);
			if (kdr > 5.f)
				IWindow::RenderText(eks + 220, 394, 20, 0, 255, 0, 255, kd);
			else if (kdr > 2.f)
				IWindow::RenderText(eks + 220, 394, 20, 255, 255, 0, 255, kd);
			else IWindow::RenderText(eks + 220, 394, 20, 255, 0, 0, 255, kd);
			IWindow::RenderText(eks + 220, 444, 20, 255, 255, 255, 255, mk);

			for (int i = 0; i < 6; i++)
				IWindow::RenderOverlay(eks, 170 + i * 50, 300, 15, 32, 32, 32, 255);

			IWindow::RenderOverlay(eks + 2, 170, 296 * dum.iTopSmalls / max(dum.iMatches, 1), 11, 0, 192, 0, 255);
			IWindow::RenderOverlay(eks + 2, 220, 296 * dum.iTopBigs / max(1, dum.iMatches), 11, 0, 192, 0, 255);
			IWindow::RenderOverlay(eks + 2, 270, 296 * dum.iWins / max(1, dum.iMatches), 11, 0, 192, 0, 255);
			IWindow::RenderOverlay(eks + 2, 320, min(296 * dum.iWins / max(1, dum.iMatches) * 5, 296), 11, 0, 192, 0, 255);
			IWindow::RenderOverlay(eks + 2, 370, min(296 * dum.iKills / max(1, dum.iMatches) / 5, 296), 11, 0, 192, 0, 255);
			IWindow::RenderOverlay(eks + 2, 420, min(296 * kdr / 5, 296), 11, 0, 192, 0, 255);
		}


		{
			auto dum = psSeasonSquads;
			int eks = 880;


			winrate = ((float)dum.iWins) / dum.iMatches * 100;
			kdr = ((float)dum.iKills) / (dum.iMatches - dum.iWins);
			if (dum.iMatches == 0) {
				kdr = 0; winrate = 0;
			}
			else if (dum.iMatches - dum.iWins == 0)kdr = dum.iKills;

			char mp[16], t25[16], t10[16], win[16], wr[16], el[16], kd[16], mk[16];

			sprintf(mp, "%d", dum.iMatches);
			sprintf(t25, "%d", dum.iTopSmalls);
			sprintf(t10, "%d", dum.iTopBigs);
			sprintf(win, "%d", dum.iWins);
			sprintf(el, "%d", dum.iKills);
			sprintf(wr, "%.2f%%", winrate);
			sprintf(kd, "%.2f", kdr);
			sprintf(mk, "%d", dum.iMostKills);

			IWindow::RenderText(eks, 100, 24, 255, 255, 255, 255, "Squads");
			IWindow::RenderText(eks, 125, 18, 255, 255, 255, 255, "Matches Played:");
			IWindow::RenderText(eks, 145, 18, 255, 255, 255, 255, "Top 6's:");
			IWindow::RenderText(eks, 195, 18, 255, 255, 255, 255, "Top 3's:");
			IWindow::RenderText(eks, 245, 18, 255, 255, 255, 255, "Victories:");
			IWindow::RenderText(eks, 295, 18, 255, 255, 255, 255, "Winrate:");
			IWindow::RenderText(eks, 345, 18, 255, 255, 255, 255, "Eliminations:");
			IWindow::RenderText(eks, 395, 18, 255, 255, 255, 255, "K/D Ratio:");
			IWindow::RenderText(eks, 445, 18, 255, 255, 255, 255, "Most Kills:");

			IWindow::RenderText(eks + 220, 124, 20, 255, 255, 255, 255, mp);
			IWindow::RenderText(eks + 220, 144, 20, 255, 255, 255, 255, t25);
			IWindow::RenderText(eks + 220, 194, 20, 255, 255, 255, 255, t10);
			IWindow::RenderText(eks + 220, 244, 20, 255, 255, 255, 255, win);
			if (winrate > 20.f)
				IWindow::RenderText(eks + 220, 294, 20, 0, 255, 0, 255, wr);
			else if (winrate > 7.5f)
				IWindow::RenderText(eks + 220, 294, 20, 255, 255, 0, 255, wr);
			else IWindow::RenderText(eks + 220, 294, 20, 255, 0, 0, 255, wr);
			IWindow::RenderText(eks + 220, 344, 20, 255, 255, 255, 255, el);
			if (kdr > 5.f)
				IWindow::RenderText(eks + 220, 394, 20, 0, 255, 0, 255, kd);
			else if (kdr > 2.f)
				IWindow::RenderText(eks + 220, 394, 20, 255, 255, 0, 255, kd);
			else IWindow::RenderText(eks + 220, 394, 20, 255, 0, 0, 255, kd);
			IWindow::RenderText(eks + 220, 444, 20, 255, 255, 255, 255, mk);

			for (int i = 0; i < 6; i++)
				IWindow::RenderOverlay(eks, 170 + i * 50, 300, 15, 32, 32, 32, 255);

			IWindow::RenderOverlay(eks + 2, 170, 296 * dum.iTopSmalls / max(dum.iMatches, 1), 11, 0, 192, 0, 255);
			IWindow::RenderOverlay(eks + 2, 220, 296 * dum.iTopBigs / max(1, dum.iMatches), 11, 0, 192, 0, 255);
			IWindow::RenderOverlay(eks + 2, 270, 296 * dum.iWins / max(1, dum.iMatches), 11, 0, 192, 0, 255);
			IWindow::RenderOverlay(eks + 2, 320, min(296 * dum.iWins / max(1, dum.iMatches) * 5, 296), 11, 0, 192, 0, 255);
			IWindow::RenderOverlay(eks + 2, 370, min(296 * dum.iKills / max(1, dum.iMatches) / 5, 296), 11, 0, 192, 0, 255);
			IWindow::RenderOverlay(eks + 2, 420, min(296 * kdr / 5, 296), 11, 0, 192, 0, 255);
		}

		int ov_elim = psSeasonSolos.iKills + psSeasonDuos.iKills + psSeasonSquads.iKills;
		int ov_mat = psSeasonSolos.iMatches + psSeasonDuos.iMatches + psSeasonSquads.iMatches;
		int ov_win = psSeasonSolos.iWins + psSeasonDuos.iWins + psSeasonSquads.iWins;
		float kdr = 0;
		float wr = 0;

		if (ov_mat == 0)
		{
			kdr = 0, wr = 0;
		}
		else
		{
			if (ov_mat - ov_win == 0)kdr = ov_elim;
			else kdr = ((float)(ov_elim)) / (ov_mat - ov_win);
			wr = ((float)ov_win) / ov_mat * 100;
		}

		IWindow::RenderText(150, 30, 30, 255, 255, 255, 255, "Season");

		char mat[32], wn[32], eli[32], winr[32], kd[32];

		sprintf(mat, "Matches: %d", ov_mat);
		sprintf(wn, "Wins: %d", ov_win);
		sprintf(eli, "Kills: %d", ov_elim);
		sprintf(winr, "Winrate: %.1f%%", wr);
		sprintf(kd, "KDR: %.2f", kdr);

		IWindow::RenderText(360, 20, 20, 255, 255, 255, 255, mat);
		IWindow::RenderText(360, 60, 20, 255, 255, 255, 255, wn);
		IWindow::RenderText(600, 20, 20, 255, 255, 255, 255, eli);
		IWindow::RenderText(600, 60, 20, 255, 255, 255, 255, kd);
		IWindow::RenderText(840, 35, 30, 255, 255, 255, 255, winr);

	}

	IWindow::RenderOverlay(490, 480, 300, 80, 64, 64, 64, 255);
	if (bShowOverallStats)IWindow::RenderOverlay(490, 480, 150, 80, 16, 192, 16, 255);
	else IWindow::RenderOverlay(640, 480, 150, 80, 120, 192, 16, 255);

	IWindow::RenderText(507, 510, 20, 255, 255, 255, 255, "Overall");
	IWindow::RenderText(665, 510, 20, 255, 255, 255, 255, "Season");

	if (g_Mouse.hasReleased(false) && g_Mouse.IsClickValid(false))
	{
		if (g_Mouse.IsBetween(490, 480, 150, 80, g_Mouse.Coords.x, g_Mouse.Coords.y))bShowOverallStats = true;
		else if (g_Mouse.IsBetween(640, 480, 150, 80, g_Mouse.Coords.x, g_Mouse.Coords.y))bShowOverallStats = false;
	}

}


void game_t::DrawUIBar()
{
	static bool bLoaded = false;
	static file_t f = g_Files.GetFileByName("ui_menu.png");
	static sf::Texture t;
	static sf::Sprite a;

	if (!bLoaded)
	{
		bLoaded = true;
		t.loadFromMemory(f.loc_in_mem, f.size);
		a.setTexture(t);
	}


	for (int i = 0; i < 5; i++)
	{
		a.setPosition(240+i*160, 600);
		a.setTextureRect(sf::IntRect(160 * i, 0, 160, 120));

		if (i == iCurrentTab)
		{
			a.setColor(sf::Color(0, 255, 0, 255));
		}
		else a.setColor(sf::Color(192, 192, 192, 255));

		IWindow::AddToRenderList(a);
	}

	if (g_Mouse.hasReleased(false) && g_Mouse.IsClickValid(false))
	{
		for (int i = 0; i < 5; i++)
		{
			if (g_Mouse.IsBetween(240 + i * 160, 600, 160, 120, g_Mouse.leftclickCoords.x, g_Mouse.leftclickCoords.y))iCurrentTab = i;
		}
	}

}



void game_t::DrawPlay()
{
	static bool bLoaded = false;
	static file_t f = g_Files.GetFileByName("play_bg.png");
	static sf::Texture t;
	static sf::Sprite a;

	if (!bLoaded)
	{
		bLoaded = true;
		t.loadFromMemory(f.loc_in_mem, f.size);
		a.setTexture(t);
	}

	IWindow::RenderTexture(t, a, 0, 0);

	sf::Color selected = sf::Color(0, 255, 0, 255);
	sf::Color not_selected = sf::Color(192, 192, 192, 255);

	IWindow::RenderText(300,100, 30, 255, 255, 255, 255, "Gamemode");
	
	IWindow::RenderText(690, 100, 30, 255, 255, 255, 255, "Aggressivity");
	sf::Color c;

	static bool fill = false;

	for (int i = 0; i < 3; i++)
	{
		if (iGameModeSelected == i)c = selected;
		else c = not_selected;

		IWindow::RenderOverlay(290, 130+i*70, 300, 70, c.r, c.g, c.b, c.a);

		if (g_Mouse.hasReleased(false) && g_Mouse.IsClickValid(false))
		{
			if (g_Mouse.IsBetween(290, 130 + i * 70, 300, 70, g_Mouse.leftclickCoords.x, g_Mouse.leftclickCoords.y))iGameModeSelected = i;
		}

		if (i == iHotdropLevel)c = selected;
		else c = not_selected;

		IWindow::RenderOverlay(690, 130 + i * 70, 300, 70, c.r, c.g, c.b, c.a);

		if (g_Mouse.hasReleased(false) && g_Mouse.IsClickValid(false))
		{
			if (g_Mouse.IsBetween(690, 130 + i * 70, 300, 70, g_Mouse.leftclickCoords.x, g_Mouse.leftclickCoords.y))iHotdropLevel = i;
		}
	}

	if (g_Mouse.hasReleased(false) && g_Mouse.IsClickValid(false))
	{
		if (g_Mouse.IsBetween(290, 380, 300, 70, g_Mouse.leftclickCoords.x, g_Mouse.leftclickCoords.y))fill = !fill;
	}

	if (fill)
	{
		IWindow::RenderOverlay(290, 380, 300, 70, 64, 192, 64, 255);
		IWindow::RenderText(370, 395, 40, 255, 255, 255, 255, "Fill");
	}
	else
	{
		IWindow::RenderOverlay(290, 380, 300, 70, 192, 64, 64, 255);
		IWindow::RenderText(325, 395, 40, 255, 255, 255, 255, "No fill");
	}

	IWindow::RenderText(370, 146, 40, 255, 255, 255, 255, "Solo");
	IWindow::RenderText(380, 216, 40, 255, 255, 255, 255, "Duo");
	IWindow::RenderText(360, 286, 40, 255, 255, 255, 255, "Squad");


	IWindow::RenderText(700, 146, 32, 255, 255, 255, 255, "Safe drop");
	IWindow::RenderText(700, 216, 32, 255, 255, 255, 255, "Hot drop");
	IWindow::RenderText(700, 286, 32, 255, 255, 255, 255, "Super hot");

	IWindow::RenderOverlay(440, 500, 400, 80, 0, 192, 0, 255);
	IWindow::RenderText(440, 515, 50, 255, 255, 255, 255, "PLAY!");

	bool enter = GetAsyncKeyState(VK_RETURN) & 1;
	IWindow::RenderOverlay(850, 475, 220, 116, 128, 128, 128, 255);
	if (bAutoplay)
		IWindow::RenderOverlay(860, 500, 200, 80, 0, 192, 0, 255);
	else 
		IWindow::RenderOverlay(860, 500, 200, 80, 192, 0, 0, 255);
	IWindow::RenderText(860, 475, 25, 255, 255, 255, 255, "Autoplay");

	if (bAutoplay)
	{
		using namespace std::chrono;
		static int count = 0;
		static auto last = high_resolution_clock::now();
		auto now = high_resolution_clock::now();
		static int fps = 0;

		count++;

		char time[16];

		int diff = duration_cast<milliseconds>(now - last).count();
		sprintf(time, "%d.%d", (5000 - diff) / 1000, (5000 - diff) % 1000 / 10);

		IWindow::RenderText(880, 530, 40, 255, 255, 255, 255, time);

		//if()

		if (diff < 0)
		{
			last = now;
		}

		if (diff > 5000) {
			last += std::chrono::milliseconds(1000000);
			int gm = iGameModeSelected;
			if (gm && !fill)gm += 2;
			pMatch = new match_t;
			printf("\nStarting match with %d gamemode %d hotdroplevel", iGameModeSelected, iHotdropLevel);
			pMatch->SetupMatch(&gsGameStyle, gm, psSolos.iMatches + psSquads.iMatches + psDuos.iMatches, iHotdropLevel);
			bInMatch = true;
		}
	}

	if (g_Mouse.hasReleased(false) && g_Mouse.IsClickValid(false) || enter)
	{
		
		if (g_Mouse.IsBetween(440, 500, 400, 80, g_Mouse.leftclickCoords.x, g_Mouse.leftclickCoords.y) || enter)
		{
			int gm = iGameModeSelected;
			if (gm && !fill)gm += 2;
			pMatch = new match_t;
			printf("\nStarting match with %d gamemode %d hotdroplevel", iGameModeSelected, iHotdropLevel);
			pMatch->SetupMatch(&gsGameStyle, gm, psSolos.iMatches + psSquads.iMatches + psDuos.iMatches, iHotdropLevel);
			bInMatch = true;
		}
		else if (g_Mouse.IsBetween(860, 500, 200, 80, g_Mouse.leftclickCoords.x, g_Mouse.leftclickCoords.y))bAutoplay = !bAutoplay;
		else if (!enter)bAutoplay = false;
	}
	
}

void game_t::DrawSkill()
{
	static bool bLoaded = false;
	static file_t f[20];
	static sf::Texture t[20];
	static sf::Sprite a[20];

	if (!bLoaded)
	{
		f[0] = g_Files.GetFileByName("t_tactical.png");
		f[1] = g_Files.GetFileByName("t_pump.png");
		f[2] = g_Files.GetFileByName("t_heavyshotgun.png");
		f[3] = g_Files.GetFileByName("t_pistol.png");
		f[4] = g_Files.GetFileByName("t_supp_pistol.png");
		f[5] = g_Files.GetFileByName("t_smg.png");
		f[6] = g_Files.GetFileByName("t_compact.png");
		f[7] = g_Files.GetFileByName("t_dual.png");
		f[8] = g_Files.GetFileByName("t_m4a1.png");
		f[9] = g_Files.GetFileByName("t_scar.png");
		f[10] = g_Files.GetFileByName("t_heavyar.png");
		f[11] = g_Files.GetFileByName("t_deagle.png");
		f[12] = g_Files.GetFileByName("t_hunt.png");
		f[13] = g_Files.GetFileByName("t_bolt.png");
		f[14] = g_Files.GetFileByName("t_heavysniper.png");
		f[15] = g_Files.GetFileByName("skill_bg.png");

		for (int i = 0; i < 16; i++)
		{
			t[i].loadFromMemory(f[i].loc_in_mem, f[i].size);
			a[i].setTexture(t[i]);
			if (i != 15)
			a[i].setScale(sf::Vector2f(150.f / 128, 150.f / 128));
		}
		bLoaded = true;
	}

	int skillpoint = experience / 200;
	int xplev = experience - skillpoint * 200;

	IWindow::RenderTexture(t[15], a[15], 0, 0);

	IWindow::RenderOverlay(340, 10, 600, 100, 192, 192, 192, 255);
	IWindow::RenderText(340, 15, 20, 0, 0, 0, 255, "Experience");

	char buf[40];
	sprintf(buf, "Skillpoints: %d", skillpoint);
	IWindow::RenderText(635, 15, 20, 0, 0, 0, 255, buf);

	IWindow::RenderOverlay(360, 50, 560, 50, 16, 16, 16, 255);
	IWindow::RenderOverlay(360, 50, 560*xplev/200, 50, 16, 192, 16, 255);

	for (int i = 1; i < 10; i++)
	{
		IWindow::RenderOverlay(359 + i * 56, 50, 2, 50, 16, 16, 16, 255);
	}

	for (int i = 0; i < 5; i++)
	{
		if (skillpoint == 0)continue;
		IWindow::RenderOverlay(1180, 150 + i * 70, 60, 60, 192, 192, 192, 255);
		IWindow::RenderOverlay(1210, 165 + i * 70, 2, 30, 0,0,0, 255);
		IWindow::RenderOverlay(1195, 180 + i * 70, 30, 2, 0, 0, 0, 255);
	}

	if (g_Mouse.hasReleased(false) && g_Mouse.IsClickValid(false) && skillpoint >= 1)
	{
		int leptek = 1;
		if (skillpoint > 10)leptek = 2;
		if (skillpoint > 50)leptek = 5;
		if (skillpoint > 200)leptek = 10;
		experience -= leptek * 200;
		if (g_Mouse.IsBetween(1180, 150, 60, 60, g_Mouse.leftclickCoords.x, g_Mouse.leftclickCoords.y))gsGameStyle.skill.atk_flick += leptek;
		else if (g_Mouse.IsBetween(1180, 220, 60, 60, g_Mouse.leftclickCoords.x, g_Mouse.leftclickCoords.y))gsGameStyle.skill.atk_track += leptek;
		else if (g_Mouse.IsBetween(1180, 290, 60, 60, g_Mouse.leftclickCoords.x, g_Mouse.leftclickCoords.y))gsGameStyle.skill.atk_predict += leptek;
		else if (g_Mouse.IsBetween(1180, 360, 60, 60, g_Mouse.leftclickCoords.x, g_Mouse.leftclickCoords.y))gsGameStyle.skill.defending += leptek;
		else if (g_Mouse.IsBetween(1180, 430, 60, 60, g_Mouse.leftclickCoords.x, g_Mouse.leftclickCoords.y))gsGameStyle.skill.looting += leptek;
		else experience += leptek * 200;


	}


	IWindow::RenderText(680, 167, 40, 255, 255, 255, 255, "Flicking");
	IWindow::RenderText(680, 237, 40, 255, 255, 255, 255, "Tracking");
	IWindow::RenderText(680, 307, 40, 255, 255, 255, 255, "Predicting");
	IWindow::RenderText(680, 377, 40, 255, 255, 255, 255, "Dodging");
	IWindow::RenderText(680, 447, 40, 255, 255, 255, 255, "Looting");

	char _f[16], _t[16], _p[16], _d[16], _l[16];

	sprintf(_f, "%d", gsGameStyle.skill.atk_flick);
	sprintf(_t, "%d", gsGameStyle.skill.atk_track);
	sprintf(_p, "%d", gsGameStyle.skill.atk_predict);
	sprintf(_d, "%d", gsGameStyle.skill.defending);
	sprintf(_l, "%d", gsGameStyle.skill.looting);

	IWindow::RenderText(1050, 167, 40, 255, 255, 255, 255, _f);
	IWindow::RenderText(1050, 237, 40, 255, 255, 255, 255, _t);
	IWindow::RenderText(1050, 307, 40, 255, 255, 255, 255, _p);
	IWindow::RenderText(1050, 377, 40, 255, 255, 255, 255, _d);
	IWindow::RenderText(1050, 447, 40, 255, 255, 255, 255, _l);


	for (int i = 0; i < 3; i++)
	{
		int d[] = { 0, 1, 2 };
		if (i == gsGameStyle.shotgun_preference)
			IWindow::RenderOverlay(130+i*110, 130, 100, 100, 32, 192, 32, 192);
		else IWindow::RenderOverlay(130+i*110, 130, 100, 100, 192, 192, 192, 192);

		if (g_Mouse.IsClickValid(false) && g_Mouse.hasReleased(false))
		{
			if (g_Mouse.IsBetween(130 + i * 110, 130, 100, 100, g_Mouse.leftclickCoords.x, g_Mouse.leftclickCoords.y))gsGameStyle.shotgun_preference = i;
		}
		a[d[i]].setScale(100.f / 128, 100.f / 128);
		a[d[i]].setPosition(130 + i * 110, 130);
		IWindow::AddToRenderList(a[d[i]]);
	}

	for (int i = 0; i < 3; i++)
	{
		int d[] = { 5,6,7 };
		if (i == gsGameStyle.secondary_preference)
			IWindow::RenderOverlay(130 + i * 110, 260, 100, 100, 32, 192, 32, 192);
		else IWindow::RenderOverlay(130 + i * 110, 260, 100, 100, 192, 192, 192, 192);
		if (g_Mouse.IsClickValid(false) && g_Mouse.hasReleased(false))
		{
			if (g_Mouse.IsBetween(130 + i * 110, 260, 100, 100, g_Mouse.leftclickCoords.x, g_Mouse.leftclickCoords.y))gsGameStyle.secondary_preference = i;
		}
		a[d[i]].setScale(100.f / 128, 100.f / 128);
		a[d[i]].setPosition(130 + i * 110, 260);
		IWindow::AddToRenderList(a[d[i]]);
	}

	for (int i = 0; i < 3; i++)
	{
		int d[] = {9,10,11};
		if (i == gsGameStyle.ar_preference)
			IWindow::RenderOverlay(130 + i * 110, 390, 100, 100, 32, 192, 32, 192);
		else IWindow::RenderOverlay(130 + i * 110, 390, 100, 100, 192, 192, 192, 192);
		if (g_Mouse.IsClickValid(false) && g_Mouse.hasReleased(false))
		{
			if (g_Mouse.IsBetween(130 + i * 110, 390, 100, 100, g_Mouse.leftclickCoords.x, g_Mouse.leftclickCoords.y))gsGameStyle.ar_preference = i;
		}
		a[d[i]].setScale(100.f / 128, 100.f / 128);
		a[d[i]].setPosition(130 + i * 110, 390);
		IWindow::AddToRenderList(a[d[i]]);
	}
}


void game_t::DrawUI()
{
	//Draw cursor
	static bool bLoaded = false;
	static file_t f = g_Files.GetFileByName("cursor.png");
	static sf::Texture t;
	static sf::Sprite a;

	DrawUIBar();

	if (!bLoaded)
	{
		bLoaded = true;
		t.loadFromMemory(f.loc_in_mem, f.size);
		a.setTexture(t);
	}

	IWindow::RenderTexture(t, a, g_Mouse.Coords.x, g_Mouse.Coords.y);






}



void game_t::DrawHistory()
{
	//printf("\nDrawHistory");
	//for (int i = iRecentMatch + 9; i > iRecentMatch - 1; i--)
	//{
		//if (previousMatches[i % 10].valid)
	//	{
	//		DrawARecord(i % 10, 40 + i * 56);
	//	}
	//}

	IWindow::RenderText(480, 10, 30, 255, 255, 255, 255, "Match History");

	for (int i = 0; i < 10; i++)
	{
		if (previousMatches[i].valid)
			DrawARecord(i, 40 + i * 55);
	}
}

void game_t::DrawARecord(int id, int y)
{

	char pos[16], mode[16],  elim[16], time[16];

	int _time = previousMatches[id].match_length;
	int min = 0, sec = 0;
	while (_time > 60)
	{
		_time -= 60;
		min++;
	}
	sec = _time;

	sprintf(time, "%d:%s%d", min, ((sec < 10) ? "0" : ""), sec);
	sprintf(pos, "#%d", previousMatches[id].placement);
	int mod = previousMatches[id].gametype;
	if (mod == 0)
		sprintf(mode, "Solo");
	else if (mod == 1)
		sprintf(mode, "Duo");
	else sprintf(mode, "Squad");
	sprintf(elim, "%d kills", previousMatches[id].eliminations);

	IWindow::RenderOverlay(300, y, 680, 50, 230, 220, 164, 255);
	IWindow::RenderText(300, y + 5, 40, 0, 0, 0, 255, pos);

	IWindow::RenderText(400, y + 10, 30, 0, 0, 0, 255, mode);
	IWindow::RenderText(550, y + 12, 25, 0, 0, 0, 255, time);
	IWindow::RenderText(700, y + 10, 30, 0, 0, 0, 255, elim);

}

void game_t::Do()
{
	if (bInMatch)
	{
		pMatch->SimulateTick();
		if (pMatch->GetAliveTeams() == 1 || !pMatch->players[0]->bAlive)
		{
			IWindow::RenderText(500, 640, 20, 255, 0, 0, 255, "Press SPACE to return");

			bool awkay = false;

			if (bAutoplay)
			{
				using namespace std::chrono;
				static int count = 0;
				static auto last = high_resolution_clock::now();
				auto now = high_resolution_clock::now();
				static int fps = 0;

				count++;

				char time[16];

				int diff = duration_cast<milliseconds>(now - last).count();
				sprintf(time, "%d.%d", (5000 - diff) / 1000, (5000 - diff) % 1000 / 10);

				IWindow::RenderText(880, 530, 40, 255, 255, 255, 255, time);

				//if()

				if (diff < 0)
				{
					last = now;
				}

				if (diff > 5000) {
					last += std::chrono::milliseconds(1000000);
					awkay = true;
				}
			}

			if (GetAsyncKeyState(VK_SPACE) || awkay)
			{
				gsGameStyle.skill.defending += pMatch->players[0]->s_iShotsDodged / 20;
				gsGameStyle.skill.atk_flick += pMatch->players[0]->s_iShotsFlicked / 5;
				gsGameStyle.skill.atk_track += pMatch->players[0]->s_iShotsTracked / 20;
				gsGameStyle.skill.atk_predict += pMatch->players[0]->s_iShotsPredicted / 2;
				gsGameStyle.skill.looting += pMatch->players[0]->s_iItemsFound / 40;

				experience += pMatch->players[0]->s_iSecondsSurvived + pMatch->players[0]->s_iEliminations * 200;

				if (psSeasonSolos.iMatches + psSeasonDuos.iMatches + psSeasonSquads.iMatches == 100)
				{
					psSeasonSolos.Reset();
					psSeasonDuos.Reset();
					psSeasonSquads.Reset();
				}




		
				if (pMatch->players[0]->bAlive)
				{
					if (iGameModeSelected == 0)
					{
						psSolos.iWins++;
						psSolos.iWinstreak++;
						psSeasonSolos.iWins++;
					
					}
					else if (iGameModeSelected == 1 || iGameModeSelected == 3)
					{
						psDuos.iWins++;
						psSeasonDuos.iWins++;
						psDuos.iWinstreak++;
					}
					else
					{
						psSquads.iWins++;
						psSeasonSquads.iWins++;
						psSquads.iWinstreak++;
					}
				}
				if (iGameModeSelected == 0)
				{

					psSolos.iKills += pMatch->players[0]->s_iEliminations;
					psSolos.iMatches++;
					int pos = pMatch->players[0]->s_Position;
					if (pos <= 25)psSolos.iTopSmalls++;
					if (pos <= 10)psSolos.iTopBigs++;

					if (pMatch->players[0]->s_iEliminations > psSolos.iMostKills)psSolos.iMostKills = pMatch->players[0]->s_iEliminations;

					psSeasonSolos.iKills += pMatch->players[0]->s_iEliminations;
					psSeasonSolos.iMatches++;
					pos = pMatch->players[0]->s_Position;
					if (pos <= 25)psSeasonSolos.iTopSmalls++;
					if (pos <= 10)psSeasonSolos.iTopBigs++;

					if (pMatch->players[0]->s_iEliminations > psSeasonSolos.iMostKills)psSeasonSolos.iMostKills = pMatch->players[0]->s_iEliminations;

					for (int i = 8; i >= 0; i--)
					{
						previousMatches[i + 1] = previousMatches[i];
					}

					previousMatches[0].eliminations = pMatch->players[0]->s_iEliminations;
					previousMatches[0].gametype = 0;
					previousMatches[0].match_length = pMatch->players[0]->s_iSecondsSurvived;
					previousMatches[0].placement = pMatch->players[0]->s_Position;
					previousMatches[0].valid = true;


				}
				else if (iGameModeSelected == 1 ||iGameModeSelected == 3)
				{
					psDuos.iKills += pMatch->players[0]->s_iEliminations;
					psDuos.iMatches++;
					int pos = pMatch->players[0]->s_Position;
					if (pos <= 12)psDuos.iTopSmalls++;
					if (pos <= 6)psDuos.iTopBigs++;

					if (pMatch->players[0]->s_iEliminations > psDuos.iMostKills)psDuos.iMostKills = pMatch->players[0]->s_iEliminations;

					psSeasonDuos.iKills += pMatch->players[0]->s_iEliminations;
					psSeasonDuos.iMatches++;
					pos = pMatch->players[0]->s_Position;
					if (pos <= 12)psSeasonDuos.iTopSmalls++;
					if (pos <= 6)psSeasonDuos.iTopBigs++;

					if (pMatch->players[0]->s_iEliminations > psSeasonDuos.iMostKills)psSeasonDuos.iMostKills = pMatch->players[0]->s_iEliminations;

					for (int i = 8; i >= 0; i--)
					{
						previousMatches[i + 1] = previousMatches[i];
					}

					previousMatches[0].eliminations = pMatch->players[0]->s_iEliminations;
					previousMatches[0].gametype = 1;
					previousMatches[0].match_length = pMatch->players[0]->s_iSecondsSurvived;
					previousMatches[0].placement = pMatch->players[0]->s_Position;
					previousMatches[0].valid = true;
				}
				else
				{
					psSquads.iKills += pMatch->players[0]->s_iEliminations;
					psSquads.iMatches++;
					int pos = pMatch->players[0]->s_Position;
					if (pos <= 6)psSquads.iTopSmalls++;
					if (pos <= 3)psSquads.iTopBigs++;

					if (pMatch->players[0]->s_iEliminations > psSquads.iMostKills)psSquads.iMostKills = pMatch->players[0]->s_iEliminations;

					psSeasonSquads.iKills += pMatch->players[0]->s_iEliminations;
					psSeasonSquads.iMatches++;
					pos = pMatch->players[0]->s_Position;
					if (pos <= 6)psSeasonSquads.iTopSmalls++;
					if (pos <= 3)psSeasonSquads.iTopBigs++;

					if (pMatch->players[0]->s_iEliminations > psSeasonSquads.iMostKills)psSeasonSquads.iMostKills = pMatch->players[0]->s_iEliminations;
					for (int i = 8; i >= 0; i--)
					{
						previousMatches[i + 1] = previousMatches[i];
					}

					previousMatches[0].eliminations = pMatch->players[0]->s_iEliminations;
					previousMatches[0].gametype = 2;
					previousMatches[0].match_length = pMatch->players[0]->s_iSecondsSurvived;
					previousMatches[0].placement = pMatch->players[0]->s_Position;
					previousMatches[0].valid = true;
				}

				bInMatch = false;
				pMatch->Delete();
				pMatch = nullptr;
			}

		}


	}
	else
	{




		if (iCurrentTab == 0)DrawHistory();
		else if (iCurrentTab == 1)DrawSkill();
		else if (iCurrentTab == 2)
			DrawPlay();
		else if (iCurrentTab == 3)			
			DrawStatistics();
		else DrawSave();





		DrawUI();
	}



}

void game_t::Load(char* savegame)
{
	char fname[64];

	sprintf(fname, "%s.sav", savegame);

	file_t F;
	F.ReadInMemory(fname);

	if (F.size < 10)return;

	for (int i = 0; i < sizeof(game_t); i++)
	{
		*(((char*)this) + i) = *(F.loc_in_mem + i);
	}

}

void game_t::Save(char* savegame)
{
	char fname[64];

	sprintf(fname, "%s.sav", savegame);

	file_t F;
	F.loc_in_mem = (char*)this;
	F.size = sizeof(game_t);

	F.Dump(fname);

	printf("\n%s dumped!", fname);
}


void game_t::DrawSave()
{
	IWindow::RenderOverlay(315, 250, 320, 80, 192, 192, 192, 255);
	IWindow::RenderOverlay(645, 250, 320, 80, 192, 192, 192, 255);

	IWindow::RenderText(390, 270, 40, 0, 0, 0, 255, "Load");
	IWindow::RenderText(720, 270, 40, 0, 0, 0, 255, "Save");

	IWindow::RenderOverlay(315, 170, 650, 70, 64, 64, 64, 255);
	IWindow::RenderOverlay(317, 172, 646, 66, 0, 0, 0, 255);

	static bool text_selected = false;
	static char filename[32] = "\0";
	static char size = 0;




	if (text_selected)
	{
		IWindow::RenderOverlay(317, 172, 646, 66, 0, 32, 0, 255);
		for (int i = 0x41; i < 0x5B; i++)
		{
			if (GetAsyncKeyState(i) & 1 && size < 31)
			{
				filename[size] = i - 0x41 + 'a';
				size++;
			}
		}
		for (int i = 0x30; i < 0x3A; i++)			
			if (GetAsyncKeyState(i) & 1 && size < 31)
				{
					filename[size] = i - 0x30 + '0';
					size++;
				}

		if (GetAsyncKeyState(VK_BACK) & 1 && size > 0)
		{
			size--;
			filename[size] = '\0';
		}
	}
	else
	{
		for (int i = 0x41; i < 0x5B; i++)
			GetAsyncKeyState(i) & 1;
		for (int i = 0x30; i < 0x3A; i++)
			(GetAsyncKeyState(i) & 1 && size < 31);

		GetAsyncKeyState(VK_BACK) & 1;
		
	}
	if (size > 0)
		IWindow::RenderText(320, 190, 30, 255, 255, 255, 255, filename);
	else
		IWindow::RenderText(320, 190, 30, 128, 128, 128, 255, "default");

	if (g_Mouse.hasReleased(false) && g_Mouse.IsClickValid(false))
	{
		text_selected = false;
		if (g_Mouse.IsBetween(325, 250, 320, 80, g_Mouse.leftclickCoords.x, g_Mouse.leftclickCoords.y))
		{
			if (size > 0)Load(filename);
			else
				Load("default");
		}
		else if (g_Mouse.IsBetween(655, 250, 320, 80, g_Mouse.leftclickCoords.x, g_Mouse.leftclickCoords.y))
		{
			if (size > 0)Save(filename);
			else
				Save("default");
		}
		else if (g_Mouse.IsBetween(315, 170, 650, 70, g_Mouse.leftclickCoords.x, g_Mouse.leftclickCoords.y))
			text_selected = true;
	}


}

*/