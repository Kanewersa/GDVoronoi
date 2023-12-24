#include "doctest.h"
#include "godot/site.h"
#include "voronoi.h"
#include <doctest/trompeloeil.hpp>
#include "jc_voronoi.h"

using namespace godot;

class MockMapper : public godot::VoronoiMapper {
public:
    MAKE_MOCK1(map_sites, TypedArray<Site>*(const jcv_diagram*), override);
};

class MockVoronoi : public godot::IVoronoi {
public:
    MAKE_MOCK2(initialize, void(const godot::PackedVector2Array&, const godot::Rect2&), override);
    MAKE_CONST_MOCK0(get_sites, godot::TypedArray<godot::Site>(), override);
};

TEST_SUITE("Voronoi Tests") {

    TEST_CASE("Constructor and Destructor") {
        godot::Voronoi* voronoi = new godot::Voronoi();
        CHECK(voronoi != nullptr);
        delete voronoi;
    }

    TEST_CASE("Voronoi with predefined sites") {
        MockVoronoi mockVoronoi;

        TypedArray<Site> sites = TypedArray<Site>();

        Ref<Site> site(memnew(Site));
        sites.push_back(Variant(site));

        ALLOW_CALL(mockVoronoi, get_sites()).RETURN(sites);
        TypedArray<Site> returned_sites = mockVoronoi.get_sites();

        CHECK(returned_sites.size() == 1);
    }

    TEST_CASE("initialize() with valid input") {
        godot::Voronoi voronoi;
        godot::PackedVector2Array points = PackedVector2Array();
        godot::Rect2 bounds;

        points.append(Vector2(5, 10));
        points.append(Vector2(10, 10));
        points.append(Vector2(15, 10));
        bounds = Rect2(0, 0, 20, 20);

        voronoi.initialize(points, bounds);

        CHECK(voronoi.get_sites().size() > 0);
    }
}