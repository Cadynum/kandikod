#include "butterworth.h"
#include "constants.h"

const unsigned long hz = 1000000/us_per_frame;


unsigned int butterworth(bw_state *s, unsigned int x) {
	
    unsigned long ret = (breakfreq*(((unsigned long)s->xp) + ((unsigned long)x)) - s->yp*(breakfreq - 2*hz))/(breakfreq+2*hz);
    s->yp = ret;
    s->xp = x;
    return (unsigned int) ret;
}