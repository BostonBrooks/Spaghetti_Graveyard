/**
 * @file
 *
 * @ingroup
 * @brief each bbSkin contains INNER_STATES_PER_SKIN animations. These are templates the animations used by bbAIControl objects.
 */
typedef struct {

    int drawables_int [INNER_STATES_PER_SKIN][ANIMATIONS_PER_DRAWABLE];
    int drawfunctions_int [INNER_STATES_PER_SKIN][ANIMATIONS_PER_DRAWABLE];


} bbSkin;

bbSkin bbSkins [NUMBER_OF_SKINS];

//Later we will put animations in a dictionary,
//lookup animations from dictionary then add to skins.

int bbSkin_init() {

    bbSkin* skin = &bbSkins[0];

    for (int i = 0; i < INNER_STATES_PER_SKIN; i++){

        skin->drawable_ints[i][0] = 19;
        skin->drawfunctions_int[i][0] = DRAW_BASIC;

        for (int j = 1; j < ANIMATIONS_PER_DRAWABLE; j++){

            skin->drawable_ints[i][j] = -1;

        }

    }

}