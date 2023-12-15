/**
 * @file
 *
 * @ingroup 
 * @brief This header file contains code for spawning non-overlapping circular swarms of drawables / aicontrollers
 */

#include "../headers/geometry.h"

/** Use Poisson Disk to first find a suitable spot for the swarm and then spawn a swarm of objects using the given spawn function */
int spawn_swarm (int number, int radius, int avoidance_distance, int separation, void(*function)(bbMapCoords);

/** Use Poisson Disk to spawn a swarm of objects using the given spawn function */
int spawn_swarm_at (bbMapCoords centre, int radius, int spacing, int number, void(*function)(bbMapCoords))