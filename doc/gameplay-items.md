# Items
## Description
An item can either be a healing item or a weapon.  
An item can either be a consumable or non-consumable item.  
For weapons, there are 4 different types:  
**Single-shot weapons:** These weapons shoot only one hitscan bullet once. For example: Assault rifle.  
**Multi-shot weapons:** These weapons shoot multiple hitscan bullets once. For example: Shotgun.  
**Projectile weapons:** These weapons shoot a projectile that travels over time. For example: Sniper rifle.  
**Explosive weapon:** These weapons shoot an explosive projectile that travels over time. This explosive projectile deals AOE damage. For example: Rocket launcher.  
For healing items, there are 3 different types:  
**White heals:**  These heals only heal the Health of a character.  
**Shield heals:** These heals only heal the Shield of a character.  
**Slurptype heals:** These heals add an effect to the character that constantly heals them up to a limit.  

## Attributes of weapons
**iType:** Specifies the type of the item. 0-3. 0 is single-shot, 1 is multi-shot, 2 is projectile and 3 is explosive.  
**bAuto:** True if the weapon is automatic, false if semi-automatic.  
**iDamageStart:** Specifies the point blank damage of the weapon.  
**iDamageEnd:** Specifies the max range damage of the weapon.  
**fRange:** Specifies the distance in units that the weapon's bullet travels in.  
**iBullets:** Amount of ammunition currently in the magazine.  
**iMaxBullets:** Maximum amount of ammunition in the magazine.  
**iBulletConsumption:** Ammunition cost of shooting. 
**iPellets:** Amount of bullets shot at once. Only used with multi-shot weapons.  
**iReloadMethod:** Decides if the full mag gets reloaded on Reload Finish, or only a singular ammo.  
**fReloadTime:** Time in seconds the weapon takes to do a reload cycle.  
**fProjectileSpeed:** Velocity in units/second of a projectile. Only used with projetile and explosive weapons.  
**fProjectileSpeedMax:** Maximum velocity in units/second of a projectile. Only used with explosive weapons.  
**fBloomMinSize:** Minimum amount of bullet spread for the weapon.  
**fBloomMovingMinSize:** Minimum amount of bullet spread for the weapon while the character is moving.  
**fBloomMaxSize:** Maximum amount of bullet spread for the weapon.  
**fBloomStandingDecrease:** The amount the spread decreases in a seconds while the character is standing.  
**fBloomMovingDecrease:** The amount the spread decreases in a seconds while the character is moving.  
**fBloomShootIncrease:** The amount the spread increases upon a shot.  
**fFireRate:** The amount of bullets can be shot in a second.  
**fPulloutTime:** The time in seconds the weapon takes to be equipped.  
**fWeaponWeight:** Movement modifier for the weapon.  
**fAudibleDistance:** Distance in units that the weapon is audible in.  
**iRarity:** Specifies the rarity of the weapon.  

## Attributes of heals
**iType:** Specifies the type of the item. 4-6. 4 is white heal, 5 is shield heal, 6 is slurptype.  
**iBullets:** Number of healing items of a type currently in a stack.  
**iMaxBullets:** Number of healing items of a type maximum in a stack.  
**iHealAmount:** The amount of health or shield the healing item can heal maximum.  
**iHealMax:** The amount of health or shield that the healing item can't surpass.  
**fHealTime:** Time in seconds the healing item takes to consume.  
**fHealRateProgressive:** Health/shield in seconds a progressive healing item heals.  
**fAudibleDistance:** Distance in units that the weapon is audible in.  
**iRarity:** Specifies the rarity of the healing item.  

