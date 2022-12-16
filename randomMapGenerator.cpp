#include "randomMapGenerator.h"

#include "core/math/random_number_generator.h"
#include "modules/gridmap/grid_map.h"
#include "scene/gui/grid_container.h"

RandomMapGenerator::RandomMapGenerator() {
}

Array RandomMapGenerator::get_generated_map(const int width, const int height, int start, int end) {
	Array generated_map;
	print_line("map array created");
	for (int x = 0; x < height; ++x) {
		Array col;
		for (int y = 0; y < width; ++y) {
			col.append(generate_number(start, end));
		}
		generated_map.append(col);
	}
	print_line("finish");
	return generated_map;
}

int RandomMapGenerator::generate_number(const int start, const int end) {
	RandomNumberGenerator rng;
	rng.randomize();
	return rng.randi_range(start, end);
}

//Bind all your methods used in this class
void RandomMapGenerator::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_generated_map", "width", "height", "start", "end"), &RandomMapGenerator::get_generated_map);
}
