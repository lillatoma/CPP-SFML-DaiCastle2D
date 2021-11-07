# Console

The console can be used to run commands while in game.  
The console window can render 15 older console messages. The user can use mouse scrollwheel or the slider on the right to scroll.  
Pressing the button that the `Open Console` action key is bound to opens or closes the console.  
One line of console code should only contain a single command.  
The console input field counts as a line.  
In the console, the input can either be a `ConVar` command or a `NonCVar` command.  

## ConVars

### mastervolume
Changes the loudness of all sounds. Must be between 0 and 1. Default is 0.5.  
### gm_cheats
1 or higher grants access to cheat commands.  
### fps_enable
1 or higher enables the fps counter. 
### fps_max
Changing this command sets the framerate of the application. 0 is unlimited fps.  
### p_movement_type
Changes the Directional movement in the Settings.  
### con_silent
1 or higher: only echo and error messages show in the console.  
### g_res_x
Changes the width of resolution.  
### g_res_y
Changes the height of resolution.  
### g_brightness
Changes the brightness of the screen. Must be between 0 and 1.
### g_fullscreen
1 or higher sets the game fullscreen. Otherwise the game is windowed.  
### m_record_replay
1 or higher enables demo recording on match start. 
### demo_framerate
Sets the framerate of the recording footage in demos.
### demo_timescale
Sets the timescale of the recording footage in demos. demo_framerate overwrites it.
### ch_bot_stop
Cheat. 1 or higher disables bot thinking. 
### ch_show_players_on_map
Cheat. 1 or higher shows other players on minimap while the player is alive.
### ch_debug_info
Cheat. 1 or higher draws debug information on screen.
### ch_teleportmarker
Cheat. 1 or higher teleports the player to the marker on marker place.
### ch_debug_mode
Cheat. Unused.

## NonCVar commands
### player
Can only be used with an active match  
Format: "player" <-- Logs the alive players and the kill-leaders  
Format: "player help" <-- Logs the available commands  
Format: "player id" <-- Logs information about the player with id 'id'  
Format: "player id kill" <-- Kills the player with id 'id'  
Format: "player id teleport x y" <-- Teleports the player with id 'id' to ('x','y')  
Format: "player id god" <-- Makes the player with id 'id' invincible  
Format: "player id health hp sp" <-- Changes the players health values to ('hp','sp')  
### clear
Clears the console from messages
### echo
Repeats the input  
Format: "echo anything"  
Ignores if the console is silent  
### camera
This command can only be used with an active match  
Format: "camera" <-- Logs the currently followed player  
Format: "camera id" <-- Changes the currently followed player to the one with id 'id'  
### spawn
Spawns an object under the currently viewed player  
Only works with a match currently played  
Format: "spawn chest" <- Spawns a chest  
Format: "spawn randomitem" <- Spawns a random item from the lootpool  
Format: "spawn item wpnName" <- Spawns an item (check wpnNames)  
Format: "spawn item idx" <- Spawns an item with listindex idx  
Format: "spawn player idx" <- Spawns the player with index idx (Revives it with no inventory)  
Format: "spawn player_floating idx" <- Spawns player with index idx (Revives it with no inventory in the air)  
Format: "spawn wpnName" <- Spawns an item (check wpnNames)  
### time
This command can only be used with an active match   
Format: "time" <-- Logs the current daytime   
Format: "time dt" <-- Changes the current daytime to 'dt'  
### dps
Format: "dps dist" <-- Lists the weapons by dps at distance 'dist'  
Format: "dps dist max" <-- Lists the top 'max' weapons by dps at distance 'dist'  
### commands
Format: "commands" <-- Lists the commands
### convars
Format: "convars" <--- Lists the console variables
### find
Format: "find something" <-- Lists all the commands and convars containing 'something'
### bind
Format: "bind button cmd" <-- Binds the action key "cmd" to the button "button"   
Format: "bind keylist" <-- Lists the names of buttons   
Format: "bind cmdlist" <-- Lists the names of actions   
### unbind
Format: "unbind button cmd" <-- Unbinds the action key "cmd" from the button "button"   
Format: "unbind keylist" <-- Lists the names of buttons   
Format: "unbind cmdlist" <-- Lists the names of actions   
Format: "unbind all" <-- Unbinds all buttons   
### exec
Format: "exec cfgname.cfg" <-- Executes each line in cfgname.cfg  
Note: cfgname.cfg must be present in the cfg\ folder  
Note: recursive executing of commands is forbidden
### quit
Format: "quit" <-- Quits the application
### quit_prompt
Format: "quit_prompt" <-- Opens the quit prompt
### record
Format: "record" <-- Starts exporting of images
### stoprecord
Format: "stoprecord" <-- Stops exporting of images
### layer
Edits or adds a demo render layer.
### bot
This command can only be used with an active match  
Format: "bot difficulties" <-- Lists the indexes of bots for all difficulties  
Format: "bot difficulties_alive" <--Lists the indexes of alive bots for all difficulties  







