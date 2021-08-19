# Character
## Description
A character has a base movement speed of 6 units/second on land, and 4 units/second in water. If the character is reloading the weapon, the base movement speed gets multiplied by 0.55.  
A character while gliding/in-air/freefalling has a movement speed of 12.5.  
A character has health (0-100), and shield (0-100). Having 0 health means, the character has been eliminated, while having at least 1 health indicates an alive character.  
A character can carry up to 5 items in its inventory.  
There are 100 characters in the game. The one with index 0 is controlled by the user, the other 99 are controlled by the computer.  

## Actions of a character
**Jump off bus:** Jumps out of a bus, heading into freefalling state from 100 height.  
**Descend:** Faster descending in freefalling state. Not descending is 1.5 units/second, descending is 7.5 units/second.  
**Move:** Move into a specific direction.  
**Open chests/airdrops:** Start the opening period of chests/airdrops. Opening a chest is 0.45 seconds, opening an airdrop is 4 seconds.
**Pick up an item:** Put an item in the inventory if there is an empty inventory slot.  
**Drop an item:** If there is an unwanted item, a character can drop an item.  
**Swap to another item slot:** If there is another item slot, the character swaps to it.  
**Use an item:** Depending of the type of the item, the character can use it in a way.  
**Get eliminated:** This one can happen by other characters or the storm. When this happens, all the inventory gets dropped, and statistics are saved for the character.  



