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

## Shooting a single-shot weapon
Casts a ray, and if the ray hits a wall or player, damage gets applied.  
## Shooting a multi-shot weapon
Casts a ray for each pellet, checks if they hit a wall or player. Damage gets applied after compressing the damage data.  
## Shooting a projectile weapon
Projectiles cast very short rays every frame to check if they hit anything. If the projectile reaches its maximum range, or hits a player or wall, it disappears, and applies damage if needed.  
## Shooting an explosive weapon
Exploive projectiles cast very short rays every frame to check if they hit anything. In case of hitting anything, the explosive projectile can bounce back, or explode instantly. If the explosive projectile reaches its maximum range, it explodes.



## Remarks and ideas
### Automatic weapon shooting
When shooting an automatic weapon, upon a weaponshot, the timer will get added `1 / fFireRate` instead of getting set to `1 / fFireRate`. This keeps the firerate of the weapon steady on framedrops and lower framerates.
### Bloom mechanic
Bloom mechanic was implemented to cover laser precision aiming. The way it works here is it randomly shoots bullets in an angle-territory. Moving characters should have less control on the gun, hence the bloomsize increases. Shooting also increases the bloom. Not shooting or standing still should help having more control over bloom.
### Explosives
Explosive projectiles, when destroyed cast 360 rays to calculate damage on objects in the explosion range. 
### Lootpool
The lootpool consists of all the weapons and healing items that are put into it, as many times as they are put into it. 
Opening a chest will result of a non-consumable and a consumable item to spawn from the lootpool. Getting an item from the lootpool does not change the lootpool itself.
