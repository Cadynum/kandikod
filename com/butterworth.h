#pragma once

struct bw_state {
    unsigned int yp, xp;
};

unsigned int butterworth(bw_state *s, unsigned int x);