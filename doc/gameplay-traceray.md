# Trace ray
## map.trace_ray
This function traces a ray between point A and point B and checks if any walls of the map were hit.
### Calculating if a specific wall was hit
Let's call the starting point `A` and ending point `B` of our ray. Let's also call the wall's starting point `X` and ending point `Y`. 
These are vectors, and for a vector `V` the coordinates will be called `V.x` and `V.y` respectively for the x and y coordinates.
Let's also call the direction vectors `D := B-A` and `Z := Y-X`.
To know if a wall was hit, we solve the equation system for `t1` and `t2`:  
- `A.x + t1 * D.x = X.x + t2 * Z.x`  
- `A.y + t1 * D.y = X.y + t2 * Z.y`  
If `t1` and `t2` are both between 0 and 1, that means that the ray hit the wall. In this case, the endpoint of the ray is `A.x + t1 * D.x`.

### Calculating the endpoint of a ray
Iterating the calculation in the previous point for each wall will result in the actual endpoint of the ray. 
With an excessive amount of walls, the calculation might get slow, so the walls were put into 50x50 sized chunks, and only the affected chunks are used.

## TracePlayers
This function traces a ray between point A and point B and checks if any players were hit.
This should probably be called with the end result of a `map.trace_ray` call.

### Calculating if a player was hit
We use the single-wall calculation in `map.trace_ray`, but we generate a wall for the player. 
This wall is 0.5 wide, and rotated perpendicularly to the ray. The cental point of this wall is the player's location.
The endpoint is obtained the same way as in `map.trace_ray`.

### Calculating the endpoint of a ray
Iterating the calculation in the previous point for each wall will result in the actual endpoint of the ray. 
