#include "randomMapGenerator.h"
#include "core/math/random_number_generator.h"

Array RandomMapGenerator::get_generated_map(const int width, const int height) {
	std::vector<std::vector<size_t>> base_map(height, std::vector<size_t>(width, 0));
	// Apply randomizer
	for (size_t y = 0; y < height; ++y) {
		//iterate grid
		for (size_t x = 0; x < width; ++x) {
			if (base_map[y][x] == 0) {
				const int gn = generate_number();
				//check for rule
				if (map_objects_list_[gn].has_rule) {
					//iterate through the rule
					for (size_t rule_col = 0; rule_col < map_objects_list_[gn].rule.size(); ++rule_col) {
						for (size_t rule_row = 0; rule_row < map_objects_list_[gn].rule[rule_col].size(); ++rule_row) {
							//apply rule if pos in rule array is > 0
							if (map_objects_list_[gn].rule[rule_col][rule_row] > 0) {
								if (y + rule_col >= height || x + rule_row >= width) {
									continue; //Continue if applying the rule would result in index out of bounds
								}
								//only change if pos in grid 0
								if (base_map[y + rule_col][x + rule_row] == 0) {
									//apply rule
									base_map[y + rule_col][x + rule_row] = gn;
								}
							}
						}
					}
				} else {
					base_map[y][x] = gn;
				}
			}
		}
	}
	print_line("finish");
	return vector_to_gd_array(base_map);
}

int RandomMapGenerator::generate_number() const {
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
	return -1;
}

int RandomMapGenerator::add_new_object(const float weight, const Array &rule) {
	MapObject object;
	object.weight = weight;
	if (!rule.empty()) {
		object.has_rule = true;
		object.rule = gd_array_to_vector(rule);
	}
	map_objects_list_.push_back(object);
	return map_objects_list_.size() - 1;
}

//Bind all your methods used in this class
void RandomMapGenerator::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_generated_map", "width", "height"), &RandomMapGenerator::get_generated_map);
	ClassDB::bind_method(D_METHOD("add_new_object", "weight", "rule"), &RandomMapGenerator::add_new_object,DEFVAL(1.f),DEFVAL(Array()));
}

Array RandomMapGenerator::vector_to_gd_array(const std::vector<std::vector<size_t>> &vec) {
	Array array;
	array.resize(vec.size());
	for (size_t y = 0; y < vec.size(); ++y) {
		Array col;
		col.resize(vec[0].size());
		for (size_t x = 0; x < vec[0].size(); ++x) {
			col[x] = vec[y][x];
		}
		array[y] = col;
	}
	return array;
}

std::vector<std::vector<size_t>> RandomMapGenerator::gd_array_to_vector(Array array) {
	std::vector<std::vector<size_t>> vec(array.size(), std::vector<size_t>(static_cast<Array>(array[0]).size()));
	for (size_t y = 0; y < vec.size(); y++) {
		for (size_t x = 0; x < vec[y].size(); x++) {
			vec[y][x] = static_cast<Array>(array[y])[x];
		}
	}
	return vec;
}
