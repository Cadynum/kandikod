#include "butterworth.h"


const double hz = 100;
const double pi  = 3.14159265358979323846;
const unsigned int bq = 188; //round(10 * 2 * pi);

unsigned int butterworth(bw_state *s, unsigned int x) {
    unsigned int ret = (bq*(s->xp + x) - s->yp*(bq - 2*hz))/(bq+2*hz);
    s->yp = ret;
    s->xp = x;
    return x;
}