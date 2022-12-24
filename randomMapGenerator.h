//insert the Headername here
#ifndef RANDOMMAPGENERATOR_H
#define RANDOMMAPGENERATOR_H

#include "core/reference.h"
#include <vector>

struct MapObject {
	std::vector<std::vector<size_t>> rule;
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
	Array get_generated_map(int width, int height);

	int generate_number() const;

	int add_new_object(float weight = 1, const Array &rule = Array());

	Array vector_to_gd_array(const std::vector<std::vector<size_t>>& vec);

	std::vector<std::vector<size_t>> gd_array_to_vector(Array array);
};

#endif
