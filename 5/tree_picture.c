#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include <graphviz/gvc.h>
#include <graphviz/cdt.h>
#include <graphviz/pathplan.h>
#include <graphviz/cgraph.h>


#define MAX_EDGES 1000


typedef struct {
    char keys[MAX_EDGES][512];
    int count;
} EdgeSet;


char* generate_edge(const char* from, const char* to) {
    char* key = malloc(strlen(from) + strlen(to) + 7);
    sprintf(key, "%s->%s", from, to);
    return key;
}


int add_ed(EdgeSet* edge_set, const char* key) {
    for (int i = 0; i < edge_set->count; ++i) {
        if (strcmp(edge_set->keys[i], key) == 0) {
            return 0;
        }
    }
    if (edge_set->count < MAX_EDGES) {
        strncpy(edge_set->keys[edge_set->count], key, 512);
        edge_set->count++;
        return 1; 
    }
    return 0; 
}


void recur_tr(Agraph_t *g, VertexListNode* vNode, EdgeSet* edge_set) {
    while (vNode) {
        Vertex* vertex = vNode->vertex;
        int has_flagged_edge = 0;
        

        EdgeListNode* eNode = vertex->edgelist;
        while (eNode) {
            if (eNode->edge.flag == 1) {
                has_flagged_edge = 1;
                break;
            }
            eNode = eNode->next;
        }

        if (!has_flagged_edge) {
            vNode = vNode->next;
            continue;
        }

        char vertex_label[512];
        snprintf(vertex_label, sizeof(vertex_label), "%s\nPort:%u", vertex->name, vertex->port);
        Agnode_t *node = agnode(g, vertex_label, 1);
        agsafeset(node, "label", vertex_label, "");

        eNode = vertex->edgelist;
        while (eNode) {
            Edge* edge = &eNode->edge;
            if (edge->flag == 1) {
                Vertex* toVertex = edge->vertex;
                char to_vertex_label[256];
                snprintf(to_vertex_label, sizeof(to_vertex_label), "%s\nPort:%u", toVertex->name, toVertex->port);
                Agnode_t *toNode = agnode(g, to_vertex_label, 1);

       
                char* edge_key = generate_edge(vertex_label, to_vertex_label);
                char* reverse_edge_key = generate_edge(to_vertex_label, vertex_label);

                if (add_ed(edge_set, edge_key) && add_ed(edge_set, reverse_edge_key)) {
                 
                    char label[256] = "Ports: ";
                    char port_str[16];
                    for (unsigned i = 0; i < edge->ports_len; ++i) {
                        sprintf(port_str, "%u", edge->ports[i]);
                        strcat(label, port_str);
                        if (i < edge->ports_len - 1) {
                            strcat(label, ",");
                        }
                    }

                    Agedge_t *e = agedge(g, node, toNode, 0, 1);
                    agsafeset(e, "label", label, "");
                }

                free(edge_key);
                free(reverse_edge_key);
            }
            eNode = eNode->next;
        }

        vNode = vNode->next;
    }
}


void grafic_mst(Graf *graf) {
    Agraph_t *g;
    GVC_t *gvc;
    gvc = gvContext();
    g = agopen("g", Agundirected, NULL);

    EdgeSet edge_set = { .count = 0 };

    recur_tr(g, graf->vertexlist, &edge_set);

    gvLayout(gvc, g, "dot");
    gvRenderFilename(gvc, g, "svg", "graph_mst.svg");
    gvFreeLayout(gvc, g);
    agclose(g);
    gvFreeContext(gvc);
}
