# Settings Menu
In the settings menu, the user can define their on preferences.  
There are 3 tabs: `Controls`; `Video` and `Audio`.
## Controls
### Toggleable button: Directional movement
Directional movement changes the way the character moves by default.  
With it disabled, moving forward result in the character moving to north.
With it enabled, moving forward result in the character moving forward.  
### Binding buttons
Here the scheme of binding buttons is visible.
![controls_button](https://user-images.githubusercontent.com/87643779/130115645-e7ec0385-0a6b-4ea4-846c-db58c8ed3ab4.png)  
Clicking on `Unbind button` unbinds both Primary and Secondary keys.  
Clicking on `Primary key` or `Secondary key` opens up a `Button-press prompt`.

### Button-press prompt
A blue panel with the text "Press a key". Pressing a valid key on the keyboard will result in the prompt disappearing, and the key being bound to the action as `Primary` or `Secondary` key depending on which one opened the prompt.  

### Action keys
Action keys take action in the game when pressing or holding the attached `Primary` or `Secondary` key.

**Move forward:** Makes the character go forward. With `Directional movement` disabled, it makes the character go North.  
**Move backward:** Makes the character go backward. With `Directional movement` disabled, it makes the character go South.  
**Move left:** Makes the character go left. With `Directional movement` disabled, it makes the character go West.  
**Move right:** Makes the character go right. With `Directional movement` disabled, it makes the character go East.  
**Alternative:** Changes the way the previous move action keys work. Holding Alternative swaps between Directional and Non-directional movement.  
**Shoot:** Fires the weapon. Opens a chest or airdrop.  
**Reload weapon:** Reloads the equipped weapon if it's possible.  
**Slot 1-5:** Changes the equipped weapon to the one in Slot 1-5.  

**Drop item:** Drops the currently equipped weapon out of the inventory.  
**Open inventory:** Opens the inventory of the player.  
**Open map:** Opens the minimap.  
**Jump off:** When the player is on the bus, it makes the player jump out of bus.  
**Descend:** When the player is in the air, it makes tha player descend faster.  
**Close Menu:** Button to go back to the previous menu.  
**Swap Player:** When the user is spectating, pressing this button changes the currently watched player.  
**Place Marker:** When the minimap is open, pressing this button on the minimap places a marker.  
**Remove Marker:** When the minimap is open, pressing this button removes the marker.  
**Open Console:** Opens and closes the console.  
**Console enter:** Evaluates the currently written console command.  

## Video
### Slider: Brightness
The brightness slider changes the brightness of the game. (In reality, it draws a transparent black overlay, and Brightness changes its transparency.)  
Changes the value of `g_brightness` between 0.5 and 1.  

### Resolution
Changes the resolution of the window. The resolutions might not be valid in full-screen mode.  
The available resolutions are the following: `640x480`; `800x600`; `1024x768`; `1280x960`; `1440x1080`; `640x360`; `1024x576`; `1280x720`; `1600x900`; `1920x1080`; `640x400`; `1280x800`; `1680x1050` and `1680x720`.  
Changes only apply after clicking on the `Apply` button.

### Toggleable button: Full screen
Changes between full-screen and windowed modes.  
With it enabled, the renderwindow occupies the entire screen.  
With it disabled, the renderwindow is a window.  
Changes only apply after clicking on the `Apply` button.  

### Apply button
Finalizes changes in `Resolution` and `Full screen` behaviour.

## Audio
### Slider: Master volume
The Master volume slider changes the overall loudness of the game.  
Changes the value of `mastervolume` between 0 and 1.

## Back button
In the top left corner, there is a yellow button with the text "Back".  
Clicking on this button directs the user back to the `Main Menu`.

## Quit button
On the top-right corner, a red button with an X in the middle is visible. Clicking on it opens the `Quit prompt`.
The `Quit prompt` is a panel with a question "Would you like to quit?" and two buttons `No` and `Yes`. Clicking on `No` closes the `Quit prompt`. Clicking on `Yes` saves the profile information to `profile.md`, saves the configuration to `cfg\config.cfg` and closes the application.
