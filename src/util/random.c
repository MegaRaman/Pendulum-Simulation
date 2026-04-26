#include <stdlib.h>
#include "util/random.h"

int get_rand_range(int min, int max) {
	int range = max - min + 1;
	return (rand() % range) - max;
}


