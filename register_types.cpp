#include "register_types.h"
#include "core/class_db.h"
#include "randomMapGenerator.h"

void register_random_map_generator_types(){
	ClassDB::register_class<RandomMapGenerator>();
}

void unregister_random_map_generator_types() {
}
