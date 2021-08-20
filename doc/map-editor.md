# Map Editor

## On launching the application
The map editor application is called `DaiCastle MapEditor v2.exe`.  
On launching the application, a console window pops up, and lists the loaded files, and the files added to the texture list.  
In the console window, in case of successful loading, texts pop up `Map succesfully loaded` and `Chests successfully loaded`.  
Below this part, the named POI's are listed with the number of chests that belong to them.  

## The looks
The application is a 1280x720 window.  
On the top, the coordinate of the camera, the camera's width, the total chest number, the daytime, and the current editmode is shown.  
On the right side, a button `Forward` is on top, below that the `Texture Selection tool` takes place, with the name of the texture listed under. 
Below it, the `Wall Health Editor` is visible, with the current wall-health, and 2 editor buttons. Next, there is the `Label Editor` tool that shows the current label, and radius of a POI to be placed next. Finally, there are 3 buttons, `Reset`, `Load` and `Save`.

![mapeditor](https://user-images.githubusercontent.com/87643779/130251718-f4dab880-ff77-4751-aee5-85a01fb920d3.PNG)

## Changing the position of the camera
Pressing the WASD keys moves the camera around.  
With the minimap open, clicking on a point with LMB (or holding it) on the map changes the camera's position to that point.  

## Changing editor tool
There are 6 tools the user can use for editing the map.  
- **Texture mode:** With this mode, the user can change the texture of the block below the mouse to the selected texture on left-click, or while holding the mouse.  
- **Wall mode:** With this mode, the user can place walls on the block below the mouse.  
- **Chest mode:** With this mode, the user can place and remove chests at the mouse's position.  
- **Label mode:** With this mode, the user can place a named POI.  
- **Texture mode + Paint:** With this mode the user can paint a bigger area. Works as a paint bucket tool.  
- **Copy texture:** With this mode, the user can select the texture of the block below the mouse.  

To change between tools, use the number keys 1-6.  

## Functionality of the objects on the right
### Forward button
![me_forward](https://user-images.githubusercontent.com/87643779/130251780-c970250c-0370-4cfb-84c2-4b589efb7a4d.PNG)  
Clicking on the Forward button will change the daytime.  
  
### Texture Selection tool
![me_texsel](https://user-images.githubusercontent.com/87643779/130251872-1e95f111-c5b5-459f-9372-5701aa2ccb56.PNG)  
The texture selection tool consists of 2 buttons, a texture between them, and a panel showing the name of that texture.  
The button on the left slides the texture to the previous one.  
The button on the right slides the texture to the next one.  
The texture that is shown is the `Selected texture`.  

### Wall Health Editor
![me_wallhealth](https://user-images.githubusercontent.com/87643779/130252070-91410475-05b2-4641-bf52-fc9b291065a7.PNG)  
The Wall Health Editor consists of a panel with the current `Wall-health` and 2 buttons.  
The left button reduces the wall-health by 25HP on click, until it reaches 0.  
The right button adds 25HP to the wall-health on click.  

### Label Editor
![me_label](https://user-images.githubusercontent.com/87643779/130252493-12b00482-f02c-4a4a-b6cf-2c59acdb37f8.PNG)  
The Label Editor consists of a writable panel containing the name of the placeable POI, and a panel showing the radius of that POI.  
By clicking in the writable panel, the user can type the name of the placeable POI. Spaces should be used. To finalize changes, the user has to click outside of the panel.  
To edit the radius, the user has to hold their left mouse button between the radius's panel.  
Holding the mouse on the left side reduces the radius, while holding on the right side increases it.  

### Reset, Load and Save buttons
![me_rls](https://user-images.githubusercontent.com/87643779/130252977-460eb1fc-b149-4467-a845-891b90529c8b.PNG)  
**Reset:** Clicking on this button removes all walls, chests and POIs, and changes all blocks to have the default `m_grs.png` as texture.  
**Load:** Loads the files called `BigSize.map`, `BigSize.chest` and `BigSize.label`.  
**Save:** Saves the files called `BigSize.map`, `BigSize.chest` and `BigSize.label`. Creates a copy of `BigSize.map` called `BiztMent.map`.  

## Using Texture mode
Texture mode can be used by clicking on a single block or holding the left mouse button, and dragging the mouse.  
The block the tool affects is highlighted by white.   
This mode is accessed by pressing 1.  

## Using Wall mode
Wall mode can be used by clicking or holding the left mouse button. Clicking places a single wall, while holding locks the wall-type.  
This means that holding the left mouse button after placing a Horizontal wall leads to only placing Horizontal walls until the next LMB release.  
The wall the tool affects is highlighted by white.  
This mode is accessed by pressing 2.  

## Using Chest mode
Chest mode can be used by releasing the left mouse button.  
On LMB release, a new chest is placed at the position of the mouse.  
To remove an existing chest, release the left mouse button on it. If the tool will remove a chest, it is highlighted by red.  
This mode is accessed by pressing 3.  

## Using Label mode
Label mode can be used by releasing the left mouse button.  
On LMB release, a new POI is placed, with it's center at the position of the mouse.  
To remove an existing POI, the label mode's label has to have the name of the POI, and the user has to click in the region of the POI.  
This mode is accessed by pressing 4.  

## Using Texture mode + Paint  
Texture mode + Paint can be used by clicking on a single block or holding the left mouse button, and dragging the mouse.  
The block the tool affects is highlighted by white.   
Double clicking will result in a Paint Bucket effect. The surrounding blocks will be painted with the Selected texture.  
**CAREFUL!!!** Paint Bucket should be used after enclosing the area it should affect by drawing with the Selected texture. Otherwise texture might flow out, and the program might crash.  
This mode is accessed by pressing 5.  

## Using Copy texture
Copy texture can be used by releasing the left mouse button.  
On LMB release, the texture of the block below the mouse gets selected as Selected texture.  
This mode is accessed by pressing 6.  

## Quick buttons 
`Ctrl + S`: Saves the files called `BigSize.map`, `BigSize.chest` and `BigSize.label`. Creates a copy of `BigSize.map` called `BiztMent.map`.  
`1`: Opens Texture mode.  
`2`: Opens Wall mode.  
`3`: Opens Chest mode.  
`4`: Opens Label mode.  
`5`: Opens Texture mode + Paint.  
`6`: Opens Copy texture.  
`W`: Moves the camera to North.  
`A`: Moves the camera to West.  
`S`: Moves the camera to South.  
`D`: Moves the camera to East.  
`M`: Opens/closes the minimap.  
