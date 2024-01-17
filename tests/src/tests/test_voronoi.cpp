#include "doctest.h"
#include "godot/site.h"
#include "voronoi.h"
#include <doctest/trompeloeil.hpp>

using namespace godot;

class MockMapper : public godot::IVoronoiMapper {
public:
    MAKE_MOCK1 (map_voronoi, TypedArray<Site>(const jcv_diagram*), override);
};

class MockVoronoi : public godot::IVoronoi {
public:
    MAKE_MOCK2 (initialize, void(const godot::PackedVector2Array&, const godot::Rect2&), override);
    MAKE_CONST_MOCK0 (get_sites, godot::TypedArray<godot::Site>(), override);
};

TEST_SUITE("Voronoi") {

    TEST_CASE("Constructor and Destructor") {
        Ref<Voronoi> voronoi(memnew(Voronoi));
        CHECK_NE(voronoi.ptr(), nullptr);
        voronoi.unref();
    }

    TEST_CASE("get_sites() with predefined sites") {
        MockVoronoi mockVoronoi;

        TypedArray<Site> sites = TypedArray<Site>();

        Ref<Site> site(memnew(Site));
        sites.push_back(Variant(site));

        ALLOW_CALL(mockVoronoi, get_sites()).RETURN(sites);
        TypedArray<Site> returned_sites = mockVoronoi.get_sites();

        CHECK_EQ(returned_sites.size(), 1);
    }

    TEST_CASE("initialize() with valid input") {
        Ref<Voronoi> voronoi(memnew(Voronoi));
        godot::PackedVector2Array points = PackedVector2Array();
        godot::Rect2 bounds;

        points.append(Vector2(5, 10));
        points.append(Vector2(10, 10));
        points.append(Vector2(15, 10));
        bounds = Rect2(0, 0, 20, 20);

        voronoi->initialize(points, bounds);

        CHECK_EQ(voronoi->get_points(), points);
        CHECK_EQ(voronoi->get_bounds(), bounds);
        
        TypedArray<Site> sites = voronoi->get_sites();
        REQUIRE_EQ(sites.size(), 3);

        Site *first_site = Object::cast_to<Site>(sites[0]);
        Site *second_site = Object::cast_to<Site>(sites[1]);
        Site *third_site = Object::cast_to<Site>(sites[2]);

        // Check sites positions
        CHECK_EQ(first_site->position, Vector2(5, 10));
        CHECK_EQ(second_site->position, Vector2(10, 10));
        CHECK_EQ(third_site->position, Vector2(15, 10));

        // Check first site graph edges
        REQUIRE_EQ(first_site->graph_edges.size(), 4);
        GraphEdge *first_site_edges[] = {
                Object::cast_to<GraphEdge>(first_site->graph_edges[0]),
                Object::cast_to<GraphEdge>(first_site->graph_edges[1]),
                Object::cast_to<GraphEdge>(first_site->graph_edges[2]),
                Object::cast_to<GraphEdge>(first_site->graph_edges[3])
        };

        CHECK_EQ(first_site_edges[0]->first_vertex, Vector2(7.5f, 0.0f));
        CHECK_EQ(first_site_edges[0]->second_vertex, Vector2(7.5f, 20.0f));
        CHECK_EQ(first_site_edges[0]->angle, 0.0f);
        CHECK(first_site_edges[0]->neighbor.is_null());

        CHECK_EQ(first_site_edges[1]->first_vertex, Vector2(7.5f, 20.0f));
        CHECK_EQ(first_site_edges[1]->second_vertex, Vector2(0.0f, 20.0f));
        CHECK_EQ(first_site_edges[1]->angle, 1.69515133f);
        CHECK(first_site_edges[1]->neighbor.is_null());

        CHECK_EQ(first_site_edges[2]->first_vertex, Vector2(0.0f, 20.0f));
        CHECK_EQ(first_site_edges[2]->second_vertex, Vector2(0.0f, 0.0f));
        CHECK_EQ(first_site_edges[2]->angle, 3.14159274f);
        CHECK(first_site_edges[2]->neighbor.is_null());

        CHECK_EQ(first_site_edges[3]->first_vertex, Vector2(0.0f, 0.0f));
        CHECK_EQ(first_site_edges[3]->second_vertex, Vector2(7.5f, 0.0f));
        CHECK_EQ(first_site_edges[3]->angle, 4.58803415f);
        CHECK(first_site_edges[3]->neighbor.is_null());

        // Check second site graph edges
        REQUIRE_EQ(second_site->graph_edges.size(), 4);
        GraphEdge *second_site_edges[] = {
                Object::cast_to<GraphEdge>(second_site->graph_edges[0]),
                Object::cast_to<GraphEdge>(second_site->graph_edges[1]),
                Object::cast_to<GraphEdge>(second_site->graph_edges[2]),
                Object::cast_to<GraphEdge>(second_site->graph_edges[3])
        };

        CHECK_EQ(second_site_edges[0]->first_vertex, Vector2(12.5f, 0.0f));
        CHECK_EQ(second_site_edges[0]->second_vertex, Vector2(12.5f, 20.0f));
        CHECK_EQ(second_site_edges[0]->angle, 0.0f);
        CHECK(second_site_edges[0]->neighbor.is_null());

        CHECK_EQ(second_site_edges[1]->first_vertex, Vector2(12.5f, 20.0f));
        CHECK_EQ(second_site_edges[1]->second_vertex, Vector2(7.5f, 20.0f));
        CHECK_EQ(second_site_edges[1]->angle, 1.57079637f);
        CHECK(second_site_edges[1]->neighbor.is_null());

        CHECK_EQ(second_site_edges[2]->first_vertex, Vector2(7.5f, 20.0f));
        CHECK_EQ(second_site_edges[2]->second_vertex, Vector2(7.5f, 0.0f));
        CHECK_EQ(second_site_edges[2]->angle, 3.14159274f);
        CHECK(second_site_edges[2]->neighbor.is_null());

        CHECK_EQ(second_site_edges[3]->first_vertex, Vector2(7.5f, 0.0f));
        CHECK_EQ(second_site_edges[3]->second_vertex, Vector2(12.5f, 0.0f));
        CHECK_EQ(second_site_edges[3]->angle, 4.71238899f);
        CHECK(second_site_edges[3]->neighbor.is_null());
    }
}