/**
 * @file
 *
 * @ingroup 
 * @brief Provides code to decide what angle to display of a drawable and it's animations.
 */
 
 
 #define ANGLES


//-----------------------------INCLUDES----------------------------//

//-----------------------------STRUCTS------------------------------//

//-----------------------------GLOBALS------------------------------//

//-----------------------------FUNCTIONS------------------------------//

int angles_8 (float i, float j){

    float x = i + j;
    float y = j - i;
    
    const float tan_A = -2.4142135623730;
    const float tan_B = -0.4142135623731;
    //tan_C = -tab_B
    //tan_D = -tan_A
    //tan E = tan_A
    //tan_F = tan_B
    //tan_G = -tan_B
    //tan_H = -tan_A
    
    if (x>0){ //vector (i, j) points to the right
        
        if (y < x * tan_A)  return 6;
        if (y < x * tan_B)  return 7;
        if (y < x * -tan_B) return 0;
        if (y < x * -tan_A) return 1;
        
        return 2;
        
        
    
    } else { //vector (i, j) points to the left
        
        if (y < -x * tan_A)  return 6;
        if (y < -x * tan_B)  return 5;
        if (y < -x * -tan_B) return 4;
        if (y < -x * -tan_A) return 3;
        
        return 2;
        
    }
    
    assert(0==1);
}
