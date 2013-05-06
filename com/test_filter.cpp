#include <math.h>
#include <stdio.h>
#include "test_data.h"
#include "butterworth.h"


int main() {
    bw_state state = {0, 0};

    for (int i = 0; i < sizeof(data)/sizeof(data[0]); i++) {
        unsigned int dd = 1023-data[i];
        printf("%u %u\n", dd, butterworth(&state, dd));
    }
}



// 101 - 2 srr + 101 z + 2 srr z

// y(30*pi+bq)
    // return (2*pi*hz*(xp + x) - 2*hz*((bq*pi - hz)*yp))/(30*pi+hz)
/*

X *  60*Pi*srr*(1 + z)}
Y * 2*srr*(30*Pi - srr + 30*Pi*z + srr*z)

*/


