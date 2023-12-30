#ifndef VORONOI_VORONOI_H
#define VORONOI_VORONOI_H

#include "voronoi_mapper.h"
#include <cstdio>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/variant/packed_vector2_array.hpp>
#include <godot_cpp/variant/rect2.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include <map>

namespace godot {
    class IVoronoi {
    public:
        virtual void initialize(const PackedVector2Array &points, const Rect2 &bounds) = 0;

        virtual TypedArray<Site> get_sites() const = 0;
    };

    class Voronoi : public RefCounted, public IVoronoi {
    GDCLASS(Voronoi, RefCounted);

    private:
        TypedArray<Site> *sites = nullptr;

    protected:
        static void _bind_methods();

        VoronoiMapper *mapper = nullptr;

    public:
        Voronoi();

        ~Voronoi() override;

        void initialize(const PackedVector2Array &points, const Rect2 &bounds) override;

        TypedArray<Site> get_sites() const override;
    };
} // namespace godot

#endif
