# Demos

## Architecture of demos
The most basic information holder object in memory is called a `demo_data`. It holds 32 bytes of information.  
`demo_data` objects can be converted, and used as a placeholder for demo events, such as `player_health`, `player_position`, or `chestopen`.  
Demo events only contain the necessary information, reducing the size from 32 bytes.  
In order to know what information the demo event holds, the first 4 bytes are used for type identification.  
Demo events are put into a holder object called a `tick`. A `tick` should contain the tick-id, and all the Demo events.  
The demo is built up by `tick` objects and the `metadata`.  
The `metadata` contains information about the players in the match, such as their names, and selected cosmetics, the demo tickbase, positions of the bus, and information about the storm.  

## Recording of a demo
If `Record demos` is enabled, the demo recording process starts at the beginning of a match.  
Demo recording is run in a separate thread.  
The match creates tick snapshots every `1/tickBase` seconds, and their pointers are put into a fixed size array as it's first non `nullptr` element.  
These snapshots contain the player information, such as position, health, etc., and precompiled `demo_data` for events.  
The demo recorder thread waits until a non-`nullptr` pointer to a snapshot is present, analyzes it, and creates a `tick` for the demo file.  
After the `tick` is created, it marks the pointer `nullptr` again, and deletes the processed information from the memory.  
This is done to avoid multi-threading memory accessing problems.  

## Analyzing a demo
For analyzing, the demo recording tool saves the previous tick as reference, to detect changes in the current one.  
Keyframes are added to the demo every 2 seconds, containing all information of players, and updates servertime in the demo.  

## Demo events
- **starttick**: Beginning of a tick. (8 bytes)  
- **playerhealth**: Updates health and shield of a player. (16 bytes)  
- **playerposition**: Updates the position and altitude of a player. (20 bytes)  
- **playerjumpout**: Marks the tick a player jumped out. (8 bytes)
- **keyframe**: Keyframe. (8 bytes)  
- **demo_end**: End of the demo file. (4 bytes)  
- **playerrotate**: Updates the rotation of a player. (12 bytes)  
- **weaponspawn**: A new item spawns at a position. (20 bytes)  
- **weaponpickup**: An item was picked up. (8 bytes)  
- **weapondrop**: A picked up item was dropped at a position. (16 bytes)  
- **playerweaponchange**: Updates the current item of a player. (16 bytes)  
- **shoteffect**: An effect of a gunshot from a point to another one. (24 bytes)  
- **airdropspawn**: An airdrop was spawned at a position. (16 bytes)  
- **airdropend**: An airdrop was opened. (8 bytes)  
- **timeupdate**: Updates daytime. (8 bytes)  
- **servertimeupdate**: Updates server-time. (8 bytes)  
- **breakwall**: A wall was broken at a position. (16 bytes)  
- **projectileadd**: Adds a projectile at a position with an angle and speed. (20 bytes)  
- **projectiledestruct**: A projectile was destroyed. (8 bytes)  
- **explosiveadd**: Adds an explosive projectile. (8 bytes)  
- **explosiveupdate**: Updates the position and angle of an explosive projectile. (16 bytes)  
- **explosivedestruct**: An explosive projectile was destroyed. (8 bytes)  
- **elimination**: A player was eliminated by a player. (12 bytes)  


