#ifndef VORONOI_GRAPH_EDGE_H
#define VORONOI_GRAPH_EDGE_H

#include "edge.h"
#include "site.h"
#include "godot_cpp/classes/object.hpp"
#include "godot_cpp/core/class_db.hpp"

namespace godot {
    class Edge;

    class Site;

    class GraphEdge : public Resource {
    GDCLASS(GraphEdge, Resource);

    protected:
        static void _bind_methods();

    public:
        Ref<Site> neighbor;
        Ref<Edge> edge;
        Vector2 first_vertex;
        Vector2 second_vertex;
        float angle;

        GraphEdge();

        ~GraphEdge();

        float get_angle() const;

        godot::Vector2 get_first_vertex() const;

        godot::Vector2 get_second_vertex() const;

        Ref<Edge> get_edge() const;

        Ref<Site> get_site() const;
    };
}
#endif
