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

typedef bool (*TestFunc)();

TestFunc test_funcs[] = {

	test_1,
	test_2,
	test_3,
	test_4,
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
