int process_click_drawables(int x, int y, int right_click);

#define BBDRAWABLE_CLICK

#define LEFT_CLICK  0
#define RIGHT_CLICK 1
#define PASS        0   //pass click command to next nearest drawable
#define DONT_PASS   1   //STUB: I would usually store this in constants.h


#include "../headers/bbDrawable.h"
#include "../headers/bbTerrainSquare.h"

int cow_onclick( int drawable_int, int mousebutton){
    if (mousebutton == RIGHT_CLICK){
        return PASS;          //nothing happens when you right click this drawable
    }
    bbDrawable* drawable = bbDrawable_Pool_Lookup(drawable_int);
    drawable->health = drawable->health - 55;
    drawable->display_health_until = Current_Time + 180;

    printf("you clicked a cow\n");
    return DONT_PASS;
}

//loop through visible drawables, return DONT_PASS if one onclick function returns DONT_PASS
//Otherwise return PASS, hand over to a different click handler.
int bbTerrainSquare_onclick(int Square_i, int Square_j, bbScreenCoords SC, int mousebutton){

    //if (Square_i < 0 || Square_i >= SQUARES_PER_MAP ||Square_j < 0 || Square_j >= SQUARES_PER_MAP ) {
        //printf("Square_i = %d, Square_j = %d\n", Square_i, Square_j);
    //   return PASS;
    //}

    bbTerrainSquare* TS = &bbTerrainSquare_grid[Square_i][ Square_j];
    int drawable_int = TS->bbDrawable_tail;
    if (drawable_int == -1) return PASS;

    while(drawable_int != -1){

        //printf("drawable_int =%d\n", drawable_int);
        bbDrawable* drawable = bbDrawable_Pool_Lookup(drawable_int);

        //is mouse within hitbox?
        bbMapCoords MC = drawable->location;
        bbScreenCoords  drawable_SC = bbMapCoords_getScreenCoords_centre(MC);

        int top = drawable_SC.y - drawable->Hit_Box.top;
        int bottom = top + drawable->Hit_Box.height;
        int left = drawable_SC.x - drawable->Hit_Box.left;
        int right = left + drawable->Hit_Box.width;

        //is SC within hitbox
        //printf("did we get this far?\n");
        if(SC.x > left && SC.x < right && SC.y > top && SC.y < bottom) {


            int flag = cow_onclick(drawable_int, mousebutton);

            if (flag == DONT_PASS) return DONT_PASS;

        };
        drawable_int = drawable->Square_Prev;






    }
    return PASS;
}

int bbTerrainSquare_onclick_visible(bbScreenCoords SC, int mousebutton){

    bbScreenCoords sc;
    bbMapCoords TopLeft, TopRight, BottomLeft, BottomRight;

    //not sure if I should add VIEWPORT_TOP and VIEWPORT_LEFT
    //Im going to say no
    sc.x = 0;
    sc.y = -viewpoint.k;

    TopLeft = bbScreenCoords_getMapCoords_k0(sc);

    sc.x = VIEWPORT_WIDTH;
    sc.y = -viewpoint.k;

    TopRight = bbScreenCoords_getMapCoords_k0(sc);

    sc.x = 0;
    sc.y = VIEWPORT_HEIGHT + ELEVATION_MAX -viewpoint.k;

    BottomLeft = bbScreenCoords_getMapCoords_k0(sc);

    sc.x = VIEWPORT_WIDTH;
    sc.y = VIEWPORT_HEIGHT + ELEVATION_MAX -viewpoint.k;

    BottomRight = bbScreenCoords_getMapCoords_k0(sc);


    bbSquareCoords LeftCorner;
    bbSquareCoords RightCorner;

    LeftCorner.i = floordiv(TopLeft.i,POINTS_PER_SQUARE);
    LeftCorner.j = floordiv(BottomLeft.j,POINTS_PER_SQUARE);

    if (LeftCorner.i < 0) LeftCorner.i = 0;
    if (LeftCorner.j < 0) LeftCorner.j = 0;

    RightCorner.i = floordiv(BottomRight.i,POINTS_PER_SQUARE);
    RightCorner.j = floordiv(TopRight.j,POINTS_PER_SQUARE);

    if (RightCorner.i > SQUARES_PER_MAP-1) RightCorner.i = SQUARES_PER_MAP-1;
    if (RightCorner.j > SQUARES_PER_MAP-1) RightCorner.j = SQUARES_PER_MAP-1;
    //indexing starts at zero

    int m,n;

    for (n = LeftCorner.j; n <= RightCorner.j; n++){
        for (m = RightCorner.i; m >= LeftCorner.i; m--){

            //printf("n=%d, m=%d\n", n, m);
            int flag = bbTerrainSquare_onclick(m, n, SC, mousebutton);
            if (flag == DONT_PASS) {
                return DONT_PASS;
            }
        }
    }
    return PASS;
}

int process_click_drawables(int x, int y, int right_click){
    bbScreenCoords SC;
    SC.x = x;
    SC.y = y;
    return bbTerrainSquare_onclick_visible(SC, right_click);
}