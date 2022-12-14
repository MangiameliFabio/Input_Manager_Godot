#include "randomMapGenerator.h"

RandomMapGenerator::RandomMapGenerator()  {}

int **RandomMapGenerator::get_generated_map(int width, int height) {
	int **array2D = 0;
	array2D = new int *[height];

	for (int h = 0; h < height; h++) {
		array2D[h] = new int[width];

		for (int w = 0; w < width; w++) {
			// fill in some initial values
			array2D[h][w] = 0;
		}
	}

	return array2D;
}

//Bind all your methods used in this class
void RandomMapGenerator::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_generated_map", "width", "height"), &RandomMapGenerator::get_generated_map);
}
