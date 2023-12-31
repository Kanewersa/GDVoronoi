#ifndef VORONOI_VORONOI_H
#define VORONOI_VORONOI_H

#include "jc_voronoi.h"
#include "voronoi_mapper.h"
#include <cstdio>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/variant/packed_vector2_array.hpp>
#include <godot_cpp/variant/rect2.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include <map>

namespace godot {
    class Voronoi : public Object {
        GDCLASS(Voronoi, Object
        );

    private:
        TypedArray<Site> *sites = nullptr;

    protected:
        static void _bind_methods();

        VoronoiMapper *mapper = nullptr;

    public:
        Voronoi();

        ~Voronoi() override;

        void initialize(const PackedVector2Array &points, const Rect2 &bounds);

        TypedArray<Site> get_sites() const;
    };
} // namespace godot

#endif
