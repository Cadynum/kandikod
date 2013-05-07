#include "butterworth.h"


const unsigned long hz = 100;
// const double pi  = 3.14159265358979323846;
const unsigned long bq = 188; //188; //round(10 * 2 * pi);

unsigned int butterworth(bw_state *s, unsigned int x) {
	
    unsigned long ret = (bq*(((unsigned long)s->xp) + ((unsigned long)x)) - s->yp*(bq - 2*hz))/(bq+2*hz);
    s->yp = ret;
    s->xp = x;
    return (unsigned int) ret;
}