#include "edge.h"

namespace godot {
    Edge::Edge() = default;

    Edge::~Edge() = default;

    void Edge::_bind_methods() {
        ClassDB::bind_method(D_METHOD("get_first_vertex"), &Edge::get_first_vertex);
        ClassDB::bind_method(D_METHOD("get_second_vertex"), &Edge::get_second_vertex);
        ClassDB::bind_method(D_METHOD("get_first_site"), &Edge::get_first_site);
        ClassDB::bind_method(D_METHOD("get_second_site"), &Edge::get_second_site);
        ClassDB::bind_method(D_METHOD("a"), &Edge::get_a);
        ClassDB::bind_method(D_METHOD("b"), &Edge::get_b);
        ClassDB::bind_method(D_METHOD("c"), &Edge::get_c);
    }

    godot::Vector2 Edge::get_first_vertex() const {
        return first_vertex;
    }

    godot::Vector2 Edge::get_second_vertex() const {
        return second_vertex;
    }

    Ref<Site> Edge::get_first_site() const {
        return first_site;
    }

    Ref<Site> Edge::get_second_site() const {
        return second_site;
    }

    float Edge::get_a() const {
        return a;
    }

    float Edge::get_b() const {
        return b;
    }

    float Edge::get_c() const {
        return c;
    }
}
