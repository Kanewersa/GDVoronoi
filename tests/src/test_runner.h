#ifndef VORONOI_TEST_RUNNER_H
#define VORONOI_TEST_RUNNER_H

#include "godot_cpp/classes/resource.hpp"
#include "godot_cpp/classes/node3d.hpp"
#include "godot_cpp/classes/scene_tree.hpp"
#include "doctest.h"

using namespace godot;
class TestRunner : public SceneTree {
    GDCLASS(TestRunner, SceneTree);

private:

protected:
    static void _bind_methods();

public:

    void run_tests();
};

#endif //VORONOI_TEST_RUNNER_H
