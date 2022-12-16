#include "randomMapGenerator.h"
#include "core/math/random_number_generator.h"

RandomMapGenerator::RandomMapGenerator() {
}

Array RandomMapGenerator::get_generated_map(const int width, const int height) {
	Array generated_map;
	print_line("map array created");
	//Create Base Array
	for (int y = 0; y < height; ++y) {
		Array col;
		for (int x = 0; x < width; ++x) {
			col.append(0);
		}
		generated_map.append(col);
	}

	// Apply randomizer
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			if (static_cast<int>(static_cast<Array>(generated_map[y])[x]) == 0) {
				const int gn = generate_number();
				if (map_objects_list_[gn].has_rule) {
					for (int rule_col = 0; rule_col < map_objects_list_[gn].rule.size(); ++rule_col) {
						for (int index = 0; index < static_cast<Array>(map_objects_list_[gn].rule[rule_col]).size(); ++index) {
							if (static_cast<int>(static_cast<Array>(map_objects_list_[gn].rule[rule_col])[index]) == 1) {
								if (y + rule_col >= height || x + index >= width) {
									continue;
								}
								if (static_cast<int>(static_cast<Array>(generated_map[y + rule_col])[x + index]) == 0) {
									static_cast<Array>(generated_map[y + rule_col])[x + index] = gn;
								}
							}
						}
					}
				} else {
					static_cast<Array>(generated_map[y])[x] = gn;
				}
			}

		}
	}
	print_line("finish");
	return generated_map;
}

int RandomMapGenerator::generate_number() {
	if (map_objects_list_.empty()) {
		print_line("No Objects registered for map generation");
		return 0;
	}
	float weight_sum = 0;
	for (const auto &object : map_objects_list_) {
		weight_sum += object.weight;
	}
	RandomNumberGenerator rng;
	rng.randomize();
	float rnd = rng.randf_range(0, weight_sum);

	for (int i = 0; i < static_cast<int>(map_objects_list_.size()); ++i) {
		if (rnd < map_objects_list_[i].weight)
			return i;
		rnd -= map_objects_list_[i].weight;
	}
	print_line("No Object could be chosen");
	return 0;
}

void RandomMapGenerator::add_new_object(const float weight, const Array &rule) {
	MapObject object;
	object.weight = weight;
	object.index = static_cast<int>(map_objects_list_.size()) + 1;
	if (!rule.empty()) {
		object.has_rule = true;
		object.rule = rule;
	}
	map_objects_list_.push_back(object);
}

//Bind all your methods used in this class
void RandomMapGenerator::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_generated_map", "width", "height"), &RandomMapGenerator::get_generated_map);
	ClassDB::bind_method(D_METHOD("add_new_object", "weight", "rule"), &RandomMapGenerator::add_new_object,DEFVAL(1.f),DEFVAL(Array()));
}
