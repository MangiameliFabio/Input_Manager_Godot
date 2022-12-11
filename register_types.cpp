#include "register_types.h"
#include "core/class_db.h"
#include "calculatorRef.h"
#include "calculatorNode.h"

void register_input_manager_godot_types(){
	ClassDB::register_class<CalculatorNode>();
	ClassDB::register_class<CalculatorRef>();
}

void unregister_input_manager_godot_types() {
}

