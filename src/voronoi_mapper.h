#ifndef VORONOI_VORONOI_MAPPER_H
#define VORONOI_VORONOI_MAPPER_H

#include <unordered_map>
#include "godot_cpp/variant/array.hpp"
#include "godot_cpp/variant/vector2.hpp"
#include "godot/site.h"
#include "godot/edge.h"
#include "godot/graph_edge.h"
#include "godot_cpp/classes/ref.hpp"
#include "jc_voronoi.h"

namespace godot {
    class IVoronoiMapper {
    public:
        virtual void map_voronoi(const jcv_diagram *diagram) = 0;

        virtual ~IVoronoiMapper() = default;
    };

    class VoronoiMapper : public IVoronoiMapper {
    public:
        VoronoiMapper();

        ~VoronoiMapper();

        void map_voronoi(const jcv_diagram *diagram) override;

        TypedArray<Site> get_sites();
        TypedArray<GraphEdge> get_half_edges();
        TypedArray<Edge> get_edges();

    private:

        std::unordered_map<int, Ref<Site>> sites_mapping;

        TypedArray<Site> sites;
        TypedArray<GraphEdge> half_edges;
        TypedArray<Edge> edges;

        Ref<Site> create_site(jcv_site *jcv_site);

        Ref<Edge> create_edge(const jcv_edge *jcv_edge);

        Ref<Site> get_or_create_site(jcv_site *jcv_site);

        void create_half_edges(jcv_site *jcv_site, const Ref<Site> &site, Ref<Edge> edge);
    };

}

#endif
