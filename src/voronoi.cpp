#include "voronoi.h"

namespace godot {
    Voronoi::Voronoi() = default;

    Voronoi::~Voronoi() {
        delete mapper;
        delete sites;
    }

    void Voronoi::_bind_methods() {
        ClassDB::bind_method(D_METHOD("initialize", "points", "bounds"),
                             &Voronoi::initialize);
        ClassDB::bind_method(D_METHOD("get_sites"), &Voronoi::get_sites);
    }

    void Voronoi::initialize(const PackedVector2Array &points,
                             const Rect2 &bounds) {
        mapper = new VoronoiMapper();

        jcv_point jcv_points[points.size()];

        for (int i = 0; i < points.size(); ++i) {
            Vector2 point = points[i];
            jcv_points[i] = jcv_point{point.x, point.y};
        }

        jcv_rect bounding_box = {{bounds.position.x, bounds.position.y},
                                 {bounds.size.x,     bounds.size.y}};

        jcv_diagram diagram;
        memset(&diagram, 0, sizeof(jcv_diagram));
        jcv_diagram_generate(points.size(), (const jcv_point *) jcv_points,
                             &bounding_box, nullptr, &diagram);

        mapper->map_sites(&diagram);
        sites = mapper->map_sites(&diagram);

        jcv_diagram_free(&diagram);
    }

    TypedArray<Site> Voronoi::get_sites() const {
        if (sites != nullptr) {
            return *sites;
        }

        Array arr;
        return arr;
    }
} // namespace godot