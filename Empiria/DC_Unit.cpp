#include "DaiCastle.h"


int dc_unit::hasFreeSlot()
{
	for (int i = 0; i < 5; i++)
		if (!Items[i].bValidated)return i;
	return -1;
}

int dc_unit::getFirstNonHealSlot()
{
	for (int i = 0; i < 5; i++)
		if (Items[i].bValidated && Items[i].iType <= 3)return i;

	return -1;
}

bool dc_unit::hasWeapon()
{
	for (int i = 0; i < 5; i++)
		if (Items[i].bValidated && Items[i].iType <= 3)return true;
	return false;
}

int dc_unit::hasSpecificItem(int listid)
{
	for (int i = 0; i < 5; i++)
		if (Items[i].bValidated && Items[i].ListIndex == listid)return i;
	return -1;
}

int dc_unit::hasWhiteheal()
{
	for (int i = 0; i < 5; i++)
		if (Items[i].bValidated)
		{
			if(Items[i].ListIndex == 13)return i;
			if (Items[i].ListIndex == 14)return i;
			if (Items[i].ListIndex == 17)return i;
			if (Items[i].ListIndex == 18)return i;

		}
	return -1;
}

int dc_unit::hasShieldheal()
{
	for (int i = 0; i < 5; i++)
		if (Items[i].bValidated)
		{
			if (Items[i].ListIndex == 15)return i;
			if (Items[i].ListIndex == 16)return i;
			if (Items[i].ListIndex == 17)return i;
			if (Items[i].ListIndex == 18)return i;

		}
	return -1;
}
