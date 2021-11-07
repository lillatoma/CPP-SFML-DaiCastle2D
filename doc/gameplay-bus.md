# Bus

All players start on the bus. The bus travels from outside the island, over the island, and eventually leaves the island. Every player must jump out before the bus reaches the edge of the island. The players still on the bus at this point will get thrown out.

The bus travels at 30 units/second, and is 100 units high.

## Generating bus route
The bus route is randomly generated at the very beginning of the match.  
The bus travels at a random angle (-180° - 180° or 0 - 360 °), and travels over a random point in the center of the island. This random point is generated from (400,400) to (600,600).  
After the setting up of a match, players can jump out exactly after the bus travelled 200 units.  
Players can freely jump out between the square territory of (100,100) and (900,900).  
