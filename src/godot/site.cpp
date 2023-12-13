#include "site.h"

namespace godot {
    Site::Site() = default;

    Site::~Site() = default;

    void Site::_bind_methods() {
        ClassDB::bind_method(D_METHOD("get_position"), &Site::get_position);
        ClassDB::bind_method(D_METHOD("get_edges"), &Site::get_edges);
    }

    TypedArray<GraphEdge> Site::get_edges() const {
        if (graph_edges != nullptr) {
            return *graph_edges;
        }

        Array arr;
        return arr;
    }

    Vector2 Site::get_position() const { return position; }

} // namespace godot
