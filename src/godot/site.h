#ifndef VORONOI_SITE_H
#define VORONOI_SITE_H

#include "godot_cpp/classes/object.hpp"
#include "godot_cpp/classes/ref_counted.hpp"
#include "godot_cpp/classes/resource.hpp"
#include "godot_cpp/core/class_db.hpp"
#include "godot_cpp/variant/array.hpp"
#include "godot_cpp/variant/vector2.hpp"
#include "graph_edge.h"

namespace godot {
    class GraphEdge;

    class Site : public Resource {
    GDCLASS(Site, Resource);

    protected:
        static void _bind_methods();

    public:
        Site();

        ~Site();

        Vector2 position;
        TypedArray<GraphEdge> *graph_edges;

        Vector2 get_position() const;

        TypedArray<GraphEdge> get_edges() const;
    };

} // namespace godot

#endif
