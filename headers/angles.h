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

}

int angles_16 (float i, float j){

    float x = j + i;
    float y = j - i;

    if (x>=0) { //vector (i, j) points to the right

        if ( y < x * -5.02733949212585 ) return 12;
        if ( y < x * -1.49660576266549 ) return 13;
        if ( y < x * -0.668178637919299 ) return 14;
        if ( y < x * -0.198912367379658 ) return 15;
        if ( y < x * 0.198912367379658 ) return 0;
        if ( y < x * 0.668178637919299 ) return 1;
        if ( y < x * 1.49660576266549 ) return 2;
        if ( y < x * 5.02733949212585 ) return 3;

        return 4;

    } else { //vector (i, j) points to the left

        if ( y < x * 5.02733949212585 ) return 12;
        if ( y < x * 1.49660576266549 ) return 13;
        if ( y < x * 0.668178637919299 ) return 14;
        if ( y < x * 0.198912367379658 ) return 15;
        if ( y < x * -0.198912367379658 ) return 0;
        if ( y < x * -0.668178637919299 ) return 1;
        if ( y < x * -1.49660576266549 ) return 2;
        if ( y < x * -5.02733949212585 ) return 3;

        return 4;

    }
}

int angles_32 (float i, float j){

    float x = j + i;
    float y = j - i;

    if (x >= 0){

        if ( y < x * -10.1531703876089 ) return 24;
        if ( y < x * -3.29655820893832 ) return 25;
        if ( y < x * -1.87086841178939 ) return 26;
        if ( y < x * -1.21850352558798 ) return 27;
        if ( y < x * -0.82067879082866 ) return 28;
        if ( y < x * -0.534511135950792 ) return 29;
        if ( y < x * -0.303346683607342 ) return 30;
        if ( y < x * -0.0984914033571645 ) return 31;
        if ( y < x *  0.0984914033571642 ) return 0;
        if ( y < x *  0.303346683607342 ) return 1;
        if ( y < x *  0.534511135950792 ) return 2;
        if ( y < x *  0.82067879082866 ) return 3;
        if ( y < x *  1.21850352558798 ) return 4;
        if ( y < x *  1.87086841178939 ) return 5;
        if ( y < x *  3.29655820893832 ) return 6;
        if ( y < x *  10.1531703876089 ) return 7;

        return 8;

    } else {

        if ( y < x *  10.1531703876089 ) return 24;
        if ( y < x *  3.29655820893832 ) return 23;
        if ( y < x *  1.87086841178939 ) return 22;
        if ( y < x *  1.21850352558798 ) return 21;
        if ( y < x *  0.82067879082866 ) return 20;
        if ( y < x *  0.534511135950792 ) return 19;
        if ( y < x *  0.303346683607342 ) return 18;
        if ( y < x *  0.0984914033571645 ) return 17;
        if ( y < x * -0.0984914033571642 ) return 16;
        if ( y < x * -0.303346683607342 ) return 15;
        if ( y < x * -0.534511135950792 ) return 14;
        if ( y < x * -0.82067879082866 ) return 13;
        if ( y < x * -1.21850352558798 ) return 12;
        if ( y < x * -1.87086841178939 ) return 11;
        if ( y < x * -3.29655820893832 ) return 10;
        if ( y < x * -10.1531703876089 ) return 9;

        return 8;

    }

}