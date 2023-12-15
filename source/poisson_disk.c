/**
 * @file
 *
 * @ingroup 
 * @brief This header file contains code for spawning non-overlapping circular swarms of drawables / aicontrollers
 */
#include <math.h>
#include "../headers/geometry.h"

/** Use Poisson Disk to first find a suitable spot for the swarm and then spawn a swarm of objects using the given spawn function */
 int spawn_swarm (int number, int radius, int avoidance_distance, int spacing, void(*function)(bbMapCoords);


 bbMapCoords random_point (bbMapCoords centre, int inner_radius, int outer_radius){

     int i, j;
     while (1){

         i = 2 * outer_radius * rand() / RAND_MAX - outer_radius;
         j = 2 * outer_radius * rand() / RAND_MAX - outer_radius;

         int radius = sqrt(i*i+j*j);

         if (radius > inner_radius && radius < outer_radius) break;
     }

     bbMapCoords result = centre;
     result.i += i;
     result.j += j;

     return result;

 }

 bbMapCoords swarm_spawn_point(int radius, int avoidance_Distance){
     while(1) {
         //generate a random point on the map

         //test if this conflicts with existing swarm and break
     }
     return point;
 }

 int spawn_swarm_at (bbMapCoords centre, int radius, int spacing, int number, void(*function)(bbMapCoords)){
     //use Poisson Disk to spawn thing on map
 }