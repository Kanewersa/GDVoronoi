#include "test_runner.h"
using namespace godot;

void TestRunner::_bind_methods() {
    ClassDB::bind_method(D_METHOD("run_tests"), &TestRunner::run_tests);
}

void TestRunner::run_tests() {
    int result = doctest::Context(0, nullptr).run();

    quit(result);
}
