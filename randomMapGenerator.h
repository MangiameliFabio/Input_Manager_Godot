//insert the Headername here
#ifndef RANDOMMAPGENERATOR_H
#define RANDOMMAPGENERATOR_H

#include "core/reference.h"

class RandomMapGenerator : public Reference {
	GDCLASS(RandomMapGenerator, Reference);


protected:
	static void _bind_methods();

public:
	RandomMapGenerator();

	Array get_generated_map(int width, int height, int start, int end);

	int generate_number(int start, int end);

};

#endif
