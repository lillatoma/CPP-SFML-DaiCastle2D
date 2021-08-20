# Demo Viewer
The Demo Viewer can be opened by clicking `Play` with an existing `.dem` file selected in the `Replays` menu.  
On opening a demo, the DemoViewer automatically starts, with the camera mode being `Free Camera`. 

## UI
The UI consists of `Kill Leaders`, `Time bar` and if the camera mode is `Free Camera`, `Player information`.

### Kill Leaders
Kill leaders shows 5 players with the most eliminations, showing their names, and elimination count.  
If the player is alive, their panel is blue, otherwise, it's red.  
Clicking on a blue panel will change the camera mode to `Following`, and start following the player assigned to the panel.  

### Time bar
The time bar shows the current time, and length of the demo.  
If the camera mode is `Following`, the eliminations and death of the followed player are visible on the timebar.  
Clicking on the timebar results in a time-jump.

### Player information
Player information shows the name, health, and armor values of the currently followed player.  
Two arrow buttons can be used to swap between players.



## Free Camera mode
With free camera mode, the user controls where the camera goes by using the bound movement buttons.  
Pressing the buttons `-` and `+` result in camera velocity changes.  
Scrolling the mousewheel changes the camera's width.  
Pressing the button bound to `Jump off bus` changes the camera mode to `Following`.  
## Following mode
With following mode, the camera follows a specific player.  
Scrolling the mousewheel changes the camera's width.  
Pressing the button bound to `Jump off bus` changes the camera mode to `Following`.  

