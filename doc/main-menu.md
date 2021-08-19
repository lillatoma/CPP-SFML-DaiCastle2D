# Main Menu
## Left side
### Character View
The Character View shows how the user's character looks like with the currently equipped cosmetics.  
There are three render-modes for the character view:  
- **Skin:** Shows the currently equipped character skin.  
- **Glider:** Shows the currently equipped glider with the character under.  
- **Wrap:** Shows the curretly equipped character skin with a random item that has the currently equipped weapon wrap.  
Choosing between the render-modes can be done by clicking on the appropriate buttons on the right side of the Character View.  
Under the character view, there is a button called Locker. Clicking on this button opens the Inventory menu.  

### Settings and Credits button
Clicking on the Settings button opens the `Settings` menu. In the `Settings` menu, the user can customize some properties.  
Clicking on the Credits button opens the `Credits` menu. In the `Credits` menu, credits are given to the creator of the game, visuals, and sounds.

## Center side
### Mini-map
A preview of the map (`BigSize.map; BigSize.chest; BigSize.label`) is visible. On this minimap, POI names are not drawn. In order to get familiar with the map in-depth, the user should use the map editor tool (DaiCastle MapEditor v2.exe) or play matches.

## Right side
### Player Profile
The Player Profile shows the name, the level, tier and arena progress, and current challenges of the user.

**Player Name:** In a white bar, with black text, the user's playername is displayed. Clicking in the white box lets the user edit their playername. The game supports playernames up to 64 characters.  
**Level Bar:** The level bar shows which level the user is at. It shows the XP progress to the next level. Leveling up gives tier-stars or tier-bars to the player.  
**Tier Bar:** The tier bar shows which tier the user is at. It shows the tier-star or tier-bar progress to the next tier. Getting a higher tier results in unlocking new cosmetics.  
**Arena Level:** The arena level bar shows which arena level the user is at. It shows the current points and the needed points for the next arena level. Getting a higher arena level results in tougher opponents in arena gamemode.  
**Challenge Bar:** A challenge bar shows a challenge that the user can finish to get tier-stars or tier-bars. Blue (normal difficulty) quests give 5, and red (hard difficulty) quests give 10 tier-stars or tier-bars. It shows the quest progress. If a named POI is displayed in the quest objective, hovering the mouse over the challenge will show where the POI is located on the Minimap. There are 2 challenge bars.  

### Replays and Statistics button
Clicking on the Replays button opens the `Replays` menu. In the `Replays` menu, the user can toggle demo recording and rewatch recorded replays.  
Clicking on the Statistics button opens the `Statistics` menu. In the `Statistics` menu, the user can see their statistics.

To restore the user statistics, level, tier, and arena progress to default, delete the file named `profile.md`. Playing a match or closing the application will recreate the file.

### Play button
On the bottom right, a big play button is visible. Clicking on the button will launch a match in the selected gamemode.  
The currently selected gamemode is visible above the Play button. Clicking on the arrow buttons result in sliding the currently selected gamemode.  
The currently available gamemodes: `Solo` and `Arena Solo`.  
In `Solo`, the game is free-for-all. Eliminating an opponent has no extra purpose than reducing the player-count.  
In `Arena Solo`, the game is free-for-all. Eliminating an opponent grants 50 progressive health gain to the eliminator.

### Quit button
On the top-right corner, a red button with an X in the middle is visible. Clicking on it opens the `Quit prompt`.
The `Quit prompt` is a panel with a question "Would you like to quit?" and two buttons `No` and `Yes`. Clicking on `No` closes the `Quit prompt`. Clicking on `Yes` saves the profile information to `profile.md`, saves the configuration to `cfg\config.cfg` and closes the application.
