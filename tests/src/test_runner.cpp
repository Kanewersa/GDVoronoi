#include "test_runner.h"
#include "godot_cpp/variant/utility_functions.hpp"
using namespace godot;

void TestRunner::_bind_methods() {
    ClassDB::bind_method(D_METHOD("run_tests"), &TestRunner::run_tests);
}

void TestRunner::run_tests() {
    int result = doctest::Context(0, nullptr).run();

    get_tree()->quit(result);
}
