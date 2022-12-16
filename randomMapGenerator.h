//insert the Headername here
#ifndef RANDOMMAPGENERATOR_H
#define RANDOMMAPGENERATOR_H

#include "core/reference.h"
#include "thirdparty/embree/kernels/common/accel.h"

struct MapObject {
	Array rule;
	int index = 0;
	float weight = 0;
	boolean has_rule = false;
};

class RandomMapGenerator : public Reference {
	GDCLASS(RandomMapGenerator, Reference);

	std::vector<MapObject> map_objects_list_;

protected:
	static void _bind_methods();

public:
	RandomMapGenerator();

	Array get_generated_map(int width, int height);

	int generate_number();

	void add_new_object(float weight, const Array &rule);
};

#endif
