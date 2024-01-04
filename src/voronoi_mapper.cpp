#include "voronoi_mapper.h"

namespace godot {
    VoronoiMapper::VoronoiMapper() = default;

    VoronoiMapper::~VoronoiMapper() = default;

    TypedArray<Site> *VoronoiMapper::map_sites(const jcv_diagram *diagram) {
        const jcv_edge *jcv_edge = jcv_diagram_get_edges(diagram);

        while (jcv_edge) {
            Ref<Edge> edge(memnew(Edge));

            edge->a = jcv_edge->a;
            edge->b = jcv_edge->b;
            edge->c = jcv_edge->c;

            edge->first_vertex = Vector2(jcv_edge->pos[0].x, jcv_edge->pos[0].y);
            edge->second_vertex = Vector2(jcv_edge->pos[1].x, jcv_edge->pos[1].y);

            edge->first_site = get_or_create_site(jcv_edge->sites[0]);
            if (jcv_edge->sites[1]) {
                edge->second_site = get_or_create_site(jcv_edge->sites[1]);
            }

            create_site_edges(jcv_edge->sites[0], edge->first_site, edge);
            if (jcv_edge->sites[1]) {
                create_site_edges(jcv_edge->sites[1], edge->second_site, edge);
            }


            jcv_edge = jcv_diagram_get_next_edge(jcv_edge);
        }

        TypedArray<Site> *mapped_sites = new TypedArray<Site>();

        for (std::pair<const int, Ref<Site>> &pair: sites) {
            mapped_sites->append(Variant(pair.second));
        }

        return mapped_sites;
    }

    Ref<Site> VoronoiMapper::create_site(jcv_site *jcv_site) {
        Ref<Site> site(memnew(Site));
        sites[jcv_site->index] = site;
        site->position = Vector2(jcv_site->p.x, jcv_site->p.y);
        site->graph_edges = TypedArray<GraphEdge>();

        return site;
    }

    Ref<Site> VoronoiMapper::get_or_create_site(jcv_site *jcv_site) {
        if (sites.find(jcv_site->index) != sites.end()) {
            return sites[jcv_site->index];
        } else {
            return create_site(jcv_site);
        }
    }

    void VoronoiMapper::create_site_edges(jcv_site *jcv_site, const Ref<Site> &site, Ref<Edge> edge) {
        if (!site->graph_edges.is_empty()) {
            return;
        }

        const jcv_graphedge *jcv_graph_edge = jcv_site->edges;

        // Map graph edges, add edge to graph edges.
        while (jcv_graph_edge) {
            Ref<GraphEdge> graph_edge(memnew(GraphEdge));

            // TODO: Fix memory error on engine exit when edge is assigned to graph_edge.
            //graph_edge->edge = edge;
            graph_edge->first_vertex =
                    Vector2(jcv_graph_edge->pos[0].x, jcv_graph_edge->pos[0].y);
            graph_edge->second_vertex =
                    Vector2(jcv_graph_edge->pos[1].x, jcv_graph_edge->pos[1].y);
            graph_edge->angle = jcv_graph_edge->angle;
            if (site == edge->first_site) {
                graph_edge->neighbor = edge->second_site;
            } else if (site == edge->second_site) {
                graph_edge->neighbor = edge->first_site;
            }

            site->graph_edges.append(Variant(graph_edge));
            jcv_graph_edge = jcv_graph_edge->next;
        }
    }
} // namespace godot
