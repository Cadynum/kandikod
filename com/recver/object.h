#pragma once

struct object_t {
	float min, max; // mm
	float maxforce, thresholdforce; // N
};

const object_t objects[] = {
	{3, 9, 10, 2}
};

const unsigned objects_len = sizeof(objects)/sizeof(object_t);

inline static bool object_stop(double dist, double force) {
	for(unsigned i = 0; i != objects_len; i++) {
		const object_t *obj = objects+i;
		if (dist <= obj->max && dist >= obj->min && force >= obj->maxforce) {
			return true;
		}
	}
	return false;
}