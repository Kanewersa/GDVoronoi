#ifndef VORONOI_EDGE_H
#define VORONOI_EDGE_H

#include "site.h"
#include "godot_cpp/variant/vector2.hpp"
#include "godot_cpp/core/class_db.hpp"

namespace godot {
    class Site;

    class Edge : public Resource {
    GDCLASS(Edge, Resource);

    protected:
        static void _bind_methods();

    public:
        Ref<Site> first_site;
        Ref<Site> second_site;
        Vector2 first_vertex;
        Vector2 second_vertex;

        float a;
        float b;
        float c;

        Edge();

        Vector2 get_first_vertex() const;

        Vector2 get_second_vertex() const;

        Ref<Site> get_first_site() const;

        Ref<Site> get_second_site() const;

        float get_a() const;

        float get_b() const;

        float get_c() const;
    };
}

#endif
