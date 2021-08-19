# Storm
The storm is generated at the very beginning of a match, and forms, and shrinks during the match, eventually containing the entire island.  

## Generating the storm
At the beginning of the match, the storm middle points are generated.  
In non-arena gamemodes, the entirety of the next zone is in the current one. This restriction means that the midpoint of the next circle must be at maximum `currentRadius-nextRadius` distance from the current midpoint.  
In arena gamemodes, the final zones will be out of the current zone.  

## Attributes
### Phase 0 - Bus time 
**Diameter:** 2000  
**Damage:** 1  
**Beginning time:** 0:00  
### Phase 1 - Storm forming
**Diameter:** 2000  
**Damage:** 1  
**Beginning time:** 0:45  
### Phase 2 - First zone waiting time
**Diameter:** 2000  
**Damage:** 1  
**Beginning time:** 1:15  
### Phase 3 - First zone starts moving
**Diameter:** 2000  
**Damage:** 1  
**Beginning time:** 2:30  
### Phase 4 - Second zone waiting time
**Diameter:** 750  
**Damage:** 1  
**Beginning time:** 4:00  
### Phase 5 - Second zone starts moving
**Diameter:** 750  
**Damage:** 1  
**Beginning time:** 5:30  
### Phase 6 - Third zone waiting time
**Diameter:** 350  
**Damage:** 1  
**Beginning time:** 7:00  
### Phase 7 - Third zone starts moving
**Diameter:** 350  
**Damage:** 2  
**Beginning time:** 8:00  
### Phase 8 - Fourth zone waiting time
**Diameter:** 180  
**Damage:** 2  
**Beginning time:** 8:45  
### Phase 9 - Fourth zone starts moving
**Diameter:** 180  
**Damage:** 5  
**Beginning time:** 9:30  
### Phase 10 - Fifth zone waiting time
**Diameter:** 90  
**Damage:** 5  
**Beginning time:** 10:00  
### Phase 11 - Fifth zone starts moving
**Diameter:** 90  
**Damage:** 7  
**Beginning time:** 10:00  
### Phase 12 - Sixth zone starts moving
**Diameter:** 50  
**Damage:** 10  
**Beginning time:** 10:30  
### Phase 13 - Seventh zone starts moving
**Diameter:** 50  
**Damage:** 10  
**Beginning time:** 11:00    
### Phase 14 - Eighth zone starts moving
**Diameter:** 30  
**Damage:** 10  
**Beginning time:** 11:30  
### Phase 15 - Ninth zone starts moving
**Diameter:** 15  
**Damage:** 10  
**Beginning time:** 11:45
### Phase 16 - Tenth zone starts moving
**Diameter:** 5  
**Damage:** 10  
**Beginning time:** 12:00   
### Phase 17 - Zone shrinked
**Diameter:** 0  
**Damage:** 10  
**Beginning time:** 12:10  
### Phase 18 - End period
**Diameter:** 0  
**Damage:** 10  
**Beginning time:** 41:40    

## Calculating the current state of the storm
The current storm phase can be obtained knowing the `ServerTime`. The weight `(ServerTime - phaseBeginTime) / (nextPhaseBeginTime - phaseBeginTime)` is going to be referenced as `lambda`. Knowing the current and next storm phase's values, we can use `lambda * nextPhaseValue + (1 - lambda) * currentPhaseValue` to calculate the values for the current state. 

## Damaging
The storm damages players with the `Damage` value of the current storm. Damaging only starts after a player has spent at least 1000 ms in the storm, and damaging applies every 1000 ms. For example, this means, that in Phase 16, the storm deals 100 damage in 10 seconds.



