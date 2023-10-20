/**
 * @file
 *
 * @ingroup
 * @brief each bbStatblock contains stats for a monster in the game.
 * This allows one AI Controller to be re-used for different monsters for example all melee units
 * statblock.csv contains a table of statblocks
 * */

typdef struct {
    char label[32];
    int skin;
    //AI_type / outer state

    int speed;
    int radius;
    float mass;
    int health;

    //etc

} bbStatblock;