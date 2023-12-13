#include "graph_edge.h"

namespace godot {
    GraphEdge::GraphEdge() = default;

    GraphEdge::~GraphEdge() {

    }

    void GraphEdge::_bind_methods() {
        ClassDB::bind_method(D_METHOD("get_angle"), &GraphEdge::get_angle);
        ClassDB::bind_method(D_METHOD("get_first_vertex"), &GraphEdge::get_first_vertex);
        ClassDB::bind_method(D_METHOD("get_second_vertex"), &GraphEdge::get_second_vertex);
        ClassDB::bind_method(D_METHOD("get_edge"), &GraphEdge::get_edge);
        ClassDB::bind_method(D_METHOD("get_site"), &GraphEdge::get_site);
    }

    float GraphEdge::get_angle() const {
        return angle;
    }

    Vector2 GraphEdge::get_first_vertex() const {
        return first_vertex;
    }

    Vector2 GraphEdge::get_second_vertex() const {
        return second_vertex;
    }

    Ref<Edge> GraphEdge::get_edge() const {
        return edge;
    }

    Ref<Site> GraphEdge::get_site() const {
        return neighbor;
    }
}
