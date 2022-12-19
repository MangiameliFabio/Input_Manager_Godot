//insert the Headername here
#ifndef RANDOMMAPGENERATOR_H
#define RANDOMMAPGENERATOR_H

#include "core/reference.h"
#include <vector>

struct MapObject {
	Array rule;
	float weight = 0;
	bool has_rule = false;
};

class RandomMapGenerator : public Reference {
	GDCLASS(RandomMapGenerator, Reference);

	std::vector<MapObject> map_objects_list_;

//Getter
public:
	std::vector<MapObject> get_map_objects_list() const {
		return map_objects_list_;
	}

protected:
	static void _bind_methods();

public:
	RandomMapGenerator();

	Array get_generated_map(int width, int height);

	int generate_number();

	void add_new_object(float weight = 1, const Array &rule = Array());
};

#endif
