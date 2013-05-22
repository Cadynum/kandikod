#pragma once

struct object_t {
	float min, max; // mm
	float maxforce, thresholdforce; // N
};

// ordna med minst max först!
const object_t objects[] = {
	{30, 85, 2, 2}
};

const unsigned objects_len = sizeof(objects)/sizeof(object_t);

inline static bool object_stop(double dist, double force) {
	for(unsigned i = 0; i != objects_len; i++) {
		const object_t *obj = objects+i;
		if (dist <= obj->max && force >= obj->maxforce) {
			return true;
		}
	}
	return false;
}