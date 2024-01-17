#include "voronoi_mapper.h"

namespace godot {
    VoronoiMapper::VoronoiMapper() = default;

    VoronoiMapper::~VoronoiMapper() = default;

    void VoronoiMapper::map_voronoi(const jcv_diagram *diagram) {
        const jcv_edge *jcv_edge = jcv_diagram_get_edges(diagram);

        while (jcv_edge) {
            Ref<Edge> edge = create_edge(jcv_edge);

            create_half_edges(jcv_edge->sites[0], edge->first_site, edge);
            if (jcv_edge->sites[1]) {
                create_half_edges(jcv_edge->sites[1], edge->second_site, edge);
            }

            jcv_edge = jcv_diagram_get_next_edge(jcv_edge);
        }
    }

    TypedArray<Site> VoronoiMapper::get_sites() {
        return sites;
    }

    TypedArray<GraphEdge> VoronoiMapper::get_half_edges() {
        return half_edges;
    }

    TypedArray<Edge> VoronoiMapper::get_edges() {
        return edges;
    }

    Ref<Site> VoronoiMapper::create_site(jcv_site *jcv_site) {
        Ref<Site> site(memnew(Site));
        sites_mapping[jcv_site->index] = site;

        site->position = Vector2(jcv_site->p.x, jcv_site->p.y);
        site->graph_edges = TypedArray<GraphEdge>();

        sites.append(site);

        return site;
    }

    Ref<Edge> VoronoiMapper::create_edge(const jcv_edge *jcv_edge) {
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

        edges.append(Variant(edge));

        return edge;
    }

    Ref<Site> VoronoiMapper::get_or_create_site(jcv_site *jcv_site) {
        if (sites_mapping.find(jcv_site->index) != sites_mapping.end()) {
            return sites_mapping[jcv_site->index];
        } else {
            return create_site(jcv_site);
        }
    }

    void VoronoiMapper::create_half_edges(jcv_site *jcv_site, const Ref<Site> &site, Ref<Edge> edge) {
        if (!site->graph_edges.is_empty()) {
            return;
        }

        const jcv_graphedge *jcv_graph_edge = jcv_site->edges;

        // Map graph edges, add edge to graph edges.
        while (jcv_graph_edge) {
            Ref<GraphEdge> graph_edge(memnew(GraphEdge));

            graph_edge->edge = edge;
            graph_edge->first_vertex =
                    Vector2(jcv_graph_edge->pos[0].x, jcv_graph_edge->pos[0].y);
            graph_edge->second_vertex =
                    Vector2(jcv_graph_edge->pos[1].x, jcv_graph_edge->pos[1].y);
            graph_edge->angle = jcv_graph_edge->angle;
            if (site == edge->first_site) {
                graph_edge->neighbor = edge->second_site;
            } else if (site == edge->second_site) {
                graph_edge->neighbor = edge->first_site;
            } else {
                ERR_PRINT("Could not find neighbor for half-edge.");
            }

            site->graph_edges.append(Variant(graph_edge));
            half_edges.append(Variant(graph_edge));

            jcv_graph_edge = jcv_graph_edge->next;
        }
    }
} // namespace godot
