//insert the Headername here
#ifndef RANDOMMAPGENERATOR_H
#define RANDOMMAPGENERATOR_H

#include "core/reference.h"

class RandomMapGenerator : public Reference {
	GDCLASS(RandomMapGenerator, Reference);

	int height_ = 0;
	int width_ = 0;


protected:
	static void _bind_methods();

public:
	RandomMapGenerator();

	int** get_generated_map(int width, int height);

};

#endif
