/**
 * @file
 *
 * @ingroup
 * @brief A function returning an int >= 0 is considered a success.
 *  Negative values are used for passing flags.
 */

#ifndef FLAGS_H
#define FLAGS_H

#define F_SUCCESS               0
#define F_NONE                 -1    // sometimes -1 is used where F_NONE should be
#define F_CONTINUE             -2    // was NO_RETHUNK
#define F_REPEAT               -3    // was RETHUNK
#define F_BREAK                -4
#define F_DELETE               -5    // After iterating over object, remove object from any lists then delete object
#define F_ANNIHILATE           -6    // Dont use this, object should free it's own data and return F_DELETE
#define F_FULL                 -7

#endif //FLAGS_H