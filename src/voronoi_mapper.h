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
        virtual TypedArray<Site> *map_sites(const jcv_diagram *diagram) = 0;
    };

    class VoronoiMapper : public IVoronoiMapper {
    public:
        VoronoiMapper();

        ~VoronoiMapper();

        TypedArray<Site> *map_sites(const jcv_diagram *diagram) override;

    private:
        std::unordered_map<int, Ref<Site>> sites;

        Ref<Site> create_site(jcv_site *jcv_site);

        Ref<Site> get_or_create_site(jcv_site *jcv_site);

        void create_site_edges(jcv_site *jcv_site, const Ref<Site> &site, const Ref<Edge> &edge);
    };

}

#endif
