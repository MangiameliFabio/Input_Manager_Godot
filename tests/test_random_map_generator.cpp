/*************************************************************************/
/*  test_string.cpp                                                      */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2022 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2022 Godot Engine contributors (cf. AUTHORS.md).   */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#include "core/math/random_number_generator.h"
#include "core/os/main_loop.h"
#include "core/os/os.h"
#include "modules/random_map_generator/randomMapGenerator.h"

#include <sstream>
#include <string>

namespace TestRandomMapGenerator {

bool test_1() {
	OS::get_singleton()->print("Test 1: Add new Object with default values\n");
	auto rmg = new RandomMapGenerator();

	rmg->add_new_object();
	OS::get_singleton()->print("Object Added\n");

	bool control = true;

	if (rmg->get_map_objects_list().empty()) {
		OS::get_singleton()->print("map_object_list is empty\n");
		control = false;
	} else {
		OS::get_singleton()->print("map_object_list is not empty\n");
	}

	if (rmg->get_map_objects_list()[0].weight == 1.f &&
		rmg->get_map_objects_list()[0].rule.empty() &&
		rmg->get_map_objects_list()[0].has_rule == false) {
		OS::get_singleton()->print("Object was correctly initialized\n");
	} else {
		OS::get_singleton()->print("Object was not correctly initialized\n");
		control = false;
	}
	return control;
}

bool test_2() {
	OS::get_singleton()->print("\n\nTest 2: Add new Object with weight 2 and rule [[1][1]]\n");
	auto rmg = new RandomMapGenerator();
	OS::get_singleton()->print("Create Rule\n");
	Array rule;
	Array marks_for_rule;
	marks_for_rule.append(1);
	marks_for_rule.append(1);
	rule.append(marks_for_rule);

	rmg->add_new_object(2, rule);
	OS::get_singleton()->print("Object Added\n");

	bool control = true;

	if (rmg->get_map_objects_list().empty()) {
		OS::get_singleton()->print("map_object_list is empty\n");
		control = false;
	} else {
		OS::get_singleton()->print("map_object_list is not empty\n");
	}

	if (rmg->get_map_objects_list()[0].weight == 2.f &&
		rmg->get_map_objects_list()[0].rule == rule &&
		rmg->get_map_objects_list()[0].has_rule == true) {
		OS::get_singleton()->print("Object was correctly initialized\n");
	} else {
		OS::get_singleton()->print("Object was not correctly initialized\n");
		control = false;
	}
	return control;
}

bool test_3() {
	OS::get_singleton()->print("\n\nTest 3: Generate random number doesn't return -1\n");
	const auto rmg = new RandomMapGenerator();

	rmg->add_new_object();
	OS::get_singleton()->print("Object added\n");
	OS::get_singleton()->print("Generate number\n");

	return !(rmg->generate_number() == -1);
}

bool test_4() {
	OS::get_singleton()->print("\n\nTest 4: Generate a random number between 0 and 4\n");
	const auto rmg = new RandomMapGenerator();

	rmg->add_new_object();
	rmg->add_new_object();
	rmg->add_new_object();
	rmg->add_new_object();
	rmg->add_new_object();

	OS::get_singleton()->print("5 Objects added\n");

	OS::get_singleton()->print("Generate number\n");
	const int ran_num = rmg->generate_number();
	std::ostringstream oss;
	oss << "Generated number is " << ran_num << "\n";
	const std::string var = oss.str();
	OS::get_singleton()->print(var.c_str());

	return 0 <= rmg->generate_number() && rmg->generate_number() <= 4;
}

bool test_5() {
	OS::get_singleton()->print("\n\nTest 5: Generate Map\n");
	const auto rmg = new RandomMapGenerator();

	rmg->add_new_object();
	rmg->add_new_object();
	rmg->add_new_object();
	rmg->add_new_object();
	rmg->add_new_object();
	OS::get_singleton()->print("5 Objects added\n");

	bool control = true;

	Array map = rmg->get_generated_map(10, 10);
	OS::get_singleton()->print("Map generated\n");

	if (!(map.size() == 10)) {
		control = false;
		std::ostringstream oss;
		oss << "Map was generated with wrong size in y: " << map.size() << "\n";
		const std::string var = oss.str();
		OS::get_singleton()->print(var.c_str());
	}

	for (int i = 0; i < map.size(); ++i) {
		if (!(static_cast<Array>(map[i]).size() == 10)) {
			control = false;
			std::ostringstream oss;
			oss << "Map was generated with wrong size in x: " << static_cast<Array>(map[i]).size() << "\n";
			const std::string var = oss.str();
			OS::get_singleton()->print(var.c_str());
		}
		for (int t = 0; t < static_cast<Array>(map[i]).size(); ++t) {
			if (!(0 <= static_cast<int>(static_cast<Array>(map[i])[t]) && static_cast<int>(static_cast<Array>(map[i])[t]) <= 4)) {
				control = false;
				std::ostringstream oss;
				oss << "Tile has wrong index: " << static_cast<int>(static_cast<Array>(map[i])[t]) << "\n";
				const std::string var = oss.str();
				OS::get_singleton()->print(var.c_str());
			}
		}
	}
	if (control) {
		OS::get_singleton()->print("Map has been generated correct\n");
	}

	return control;
}

typedef bool (*TestFunc)();

TestFunc test_funcs[] = {

	test_1,
	test_2,
	test_3,
	test_4,
	test_5,
	nullptr

};

MainLoop *test() {
	/** A character length != wchar_t may be forced, so the tests won't work */

	ERR_FAIL_COND_V(sizeof(CharType) != sizeof(wchar_t), nullptr);

	int count = 0;
	int passed = 0;

	while (true) {
		if (!test_funcs[count]) {
			break;
		}
		bool pass = test_funcs[count]();
		if (pass) {
			passed++;
		}
		OS::get_singleton()->print("\t%s\n", pass ? "PASS" : "FAILED");

		count++;
	}

	OS::get_singleton()->print("\n\n\n");
	OS::get_singleton()->print("*************\n");
	OS::get_singleton()->print("***TOTALS!***\n");
	OS::get_singleton()->print("*************\n");

	OS::get_singleton()->print("Passed %i of %i tests\n", passed, count);

	return nullptr;
}
} // namespace TestString
