#include "voronoi.h"

namespace godot {
    Voronoi::Voronoi() = default;

    Voronoi::~Voronoi() {
        delete mapper;
        jcv_diagram_free(&diagram);
    }

    void Voronoi::_bind_methods() {
        ClassDB::bind_method(D_METHOD("initialize", "points", "bounds"),
                             &Voronoi::initialize);
        ClassDB::bind_method(D_METHOD("get_sites"), &Voronoi::get_sites);
        ClassDB::bind_method(D_METHOD("get_edges"), &Voronoi::get_edges);
        ClassDB::bind_method(D_METHOD("get_half_edges"), &Voronoi::get_half_edges);
    }

    void Voronoi::initialize(const PackedVector2Array &voronoi_points,
                             const Rect2 &voronoi_bounds) {
        this->points = voronoi_points;
        this->bounds = voronoi_bounds;

        mapper = new VoronoiMapper();

        jcv_point jcv_points[points.size()];

        for (int i = 0; i < points.size(); ++i) {
            Vector2 point = points[i];
            jcv_points[i] = jcv_point{point.x, point.y};
        }

        jcv_rect bounding_box = {{bounds.position.x, bounds.position.y},
                                 {bounds.size.x,     bounds.size.y}};

        memset(&diagram, 0, sizeof(jcv_diagram));
        jcv_diagram_generate(points.size(), (const jcv_point *) jcv_points,
                             &bounding_box, nullptr, &diagram);

        mapper->map_voronoi(&diagram);
    }

    TypedArray<Edge> Voronoi::get_edges() const {
        return mapper->get_edges();
    }

    TypedArray<Site> Voronoi::get_sites() const {
        return mapper->get_sites();
    }

    TypedArray<GraphEdge> Voronoi::get_half_edges() const {
        return mapper->get_half_edges();
    }

    Rect2 Voronoi::get_bounds() {
        return bounds;
    }

    PackedVector2Array Voronoi::get_points() {
        return points;
    }
} // namespace godot
