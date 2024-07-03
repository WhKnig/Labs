#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include "graph.h"

// obhod

typedef struct VisitedNode {
    char* name;
    struct VisitedNode* next;
} VisitedNode;


void add_visited(VisitedNode** visited, const char* name) {
    VisitedNode* new_node = malloc(sizeof(VisitedNode));
    new_node->name = strdup(name);
    new_node->next = *visited;
    *visited = new_node;
}


int is_visited(VisitedNode* visited, const char* name) {
    while (visited) {
        if (strcmp(visited->name, name) == 0) {
            return 1;
        }
        visited = visited->next;
    }
    return 0;
}


void free_visited(VisitedNode* visited) {
    while (visited) {
        VisitedNode* temp = visited;
        visited = visited->next;
        free(temp->name);
        free(temp);
    }
}


void dfs_iterative(Vertex* start, unsigned target_port) {
    VisitedNode* visited = NULL;
    Vertex* stack[1024];
    int stack_size = 0;

    stack[stack_size++] = start;

    while (stack_size > 0) {
        Vertex* current = stack[--stack_size];

        if (is_visited(visited, current->name)) {
            continue;
        }

        add_visited(&visited, current->name);
        if(current->port == target_port){printf("Computer: %s, Port: %u\n", current->name, current->port);}

        EdgeListNode* eNode = current->edgelist;
        while (eNode) {
            Edge* edge = &eNode->edge;
            for (unsigned i = 0; i < edge->ports_len; ++i) {
                if (edge->ports[i] == target_port) {
                    if (!is_visited(visited, edge->vertex->name)) {
                        stack[stack_size++] = edge->vertex;
                    }
                    break;
                }
            }
            eNode = eNode->next;
        }
    }

    free_visited(visited);
}


int obhod(Graf* graf, const char* start_computer, unsigned target_port) {
    VertexListNode* vNode = graf->vertexlist;
    while (vNode) {
        if (strcmp(vNode->vertex->name, start_computer) == 0) {
            dfs_iterative(vNode->vertex, target_port);
            return 0;
        }
        vNode = vNode->next;
    }
    return 1;
}


// __________________________________________________________________________________________________
// B-F

typedef struct {
    Vertex* vertex;
    int distance;
    Vertex* predecessor;
} BFNode;


Vertex* find_ver(Graf* graf, const char* name) {
    VertexListNode* vNode = graf->vertexlist;
    while (vNode) {
        if (strcmp(vNode->vertex->name, name) == 0) {
            return vNode->vertex;
        }
        vNode = vNode->next;
    }
    return NULL;
}


void initialize_single_source(BFNode* nodes, Graf* graf, Vertex* source) {
    VertexListNode* vNode = graf->vertexlist;
    int index = 0;
    while (vNode) {
        nodes[index].vertex = vNode->vertex;
        nodes[index].distance = INT_MAX;
        nodes[index].predecessor = NULL;
        if (vNode->vertex == source) {
            nodes[index].distance = 0;
        }
        vNode = vNode->next;
        index++;
    }
}


void relax(BFNode* u, BFNode* v) {
    if (u->distance != INT_MAX && v->distance > u->distance + 1) {
        v->distance = u->distance + 1;
        v->predecessor = u->vertex;
    }
}


int bellman_ford(Graf* graf, const char* start, const char* end) {
    
    int vertex_count = 0;
    VertexListNode* vNode = graf->vertexlist;
    while (vNode) {
        vertex_count++;
        vNode = vNode->next;
    }

   
    BFNode* nodes = malloc(sizeof(BFNode) * vertex_count);
    Vertex* start_vertex = find_ver(graf, start);
    Vertex* end_vertex = find_ver(graf, end);
    if (!start_vertex || !end_vertex) {
        free(nodes);
        return 1;
    }

    unsigned target_port = end_vertex->port;
    initialize_single_source(nodes, graf, start_vertex);

   
    for (int i = 1; i < vertex_count; ++i) {
        vNode = graf->vertexlist;
        while (vNode) {
            BFNode* u = NULL;
            for (int j = 0; j < vertex_count; ++j) {
                if (nodes[j].vertex == vNode->vertex) {
                    u = &nodes[j];
                    break;
                }
            }
            if (!u) {
                vNode = vNode->next;
                continue;
            }

            EdgeListNode* eNode = vNode->vertex->edgelist;
            while (eNode) {
                Edge* edge = &eNode->edge;
                for (unsigned int k = 0; k < edge->ports_len; ++k) {
                    if (edge->ports[k] == target_port) {
                        BFNode* v = NULL;
                        for (int j = 0; j < vertex_count; ++j) {
                            if (nodes[j].vertex == edge->vertex) {
                                v = &nodes[j];
                                break;
                            }
                        }
                        if (v) {
                            relax(u, v);
                        }
                    }
                }
                eNode = eNode->next;
            }
            vNode = vNode->next;
        }
    }

    
    BFNode* end_node = NULL;
    for (int j = 0; j < vertex_count; ++j) {
        if (nodes[j].vertex == end_vertex) {
            end_node = &nodes[j];
            break;
        }
    }



    if (end_node && end_node->distance < INT_MAX) {
        printf("Кратчайший путь (снизу вверх!!!) от %s до %s:\n", start, end);
        BFNode* current = end_node;
        while (current) {
            printf("%s(%u)\n", current->vertex->name, current->vertex->port);
            if (!current->predecessor) break;
            for (int j = 0; j < vertex_count; ++j) {
                if (nodes[j].vertex == current->predecessor) {
                    current = &nodes[j];
                    break;
                }
            }
            printf("▲\n");   
        }
    } else {
        free(nodes);
        return 2;
    }

    free(nodes);
    return 0;
}

// ______________________________________________________________________________________________________
// MST

#define MAX_EDGES 1000  // Максимальное количество ребер, можно изменить при необходимости

typedef struct {
    char* v1;
    char* v2;
} xedge;

static VertexListNode* find_vertex(Graf* g, const char* name)
{
    VertexListNode* cur = g->vertexlist;
    while (cur)
    {
        if (!strcmp(cur->vertex->name, name))
        {
            break;
        }
        cur = cur->next;
    }
    return cur;
}

void add_flagged_edge(xedge* flagged_edges, int* flagged_edges_count, const char* v1, const char* v2) {
    if (*flagged_edges_count >= MAX_EDGES) {
        fprintf(stderr, "Exceeded maximum number of edges\n");
        return;
    }
    flagged_edges[*flagged_edges_count].v1 = strdup(v1);
    flagged_edges[*flagged_edges_count].v2 = strdup(v2);
    (*flagged_edges_count)++;
}

void bellman_mst(Graf* graf, const char* start, const char* end, xedge* flagged_edges, int* flagged_edges_count) {
     int vertex_count = 0;
    VertexListNode* vNode = graf->vertexlist;
    while (vNode) {
        vertex_count++;
        vNode = vNode->next;
    }

   
    BFNode* nodes = malloc(sizeof(BFNode) * vertex_count);
    Vertex* start_vertex = find_ver(graf, start);
    Vertex* end_vertex = find_ver(graf, end);


    unsigned target_port = end_vertex->port;
    initialize_single_source(nodes, graf, start_vertex);

   
    for (int i = 1; i < vertex_count; ++i) {
        vNode = graf->vertexlist;
        while (vNode) {
            BFNode* u = NULL;
            for (int j = 0; j < vertex_count; ++j) {
                if (nodes[j].vertex == vNode->vertex) {
                    u = &nodes[j];
                    break;
                }
            }
            if (!u) {
                vNode = vNode->next;
                continue;
            }

            EdgeListNode* eNode = vNode->vertex->edgelist;
            while (eNode) {
                Edge* edge = &eNode->edge;
                for (unsigned int k = 0; k < edge->ports_len; ++k) {
                    if (edge->ports[k] == target_port) {
                        BFNode* v = NULL;
                        for (int j = 0; j < vertex_count; ++j) {
                            if (nodes[j].vertex == edge->vertex) {
                                v = &nodes[j];
                                break;
                            }
                        }
                        if (v) {
                            relax(u, v);
                        }
                    }
                }
                eNode = eNode->next;
            }
            vNode = vNode->next;
        }
    }

    
    BFNode* end_node = NULL;
    for (int j = 0; j < vertex_count; ++j) {
        if (nodes[j].vertex == end_vertex) {
            end_node = &nodes[j];
            break;
        }
    }

    if (end_node && end_node->distance < INT_MAX) {
        BFNode* current = end_node;
        while (current && current->predecessor) {
            Vertex* pred = current->predecessor;
            add_flagged_edge(flagged_edges, flagged_edges_count, pred->name, current->vertex->name);
            for (int j = 0; j < vertex_count; ++j) {
                if (nodes[j].vertex == pred) {
                    current = &nodes[j];
                    break;
                }
            }
        }
    }

    free(nodes);
    return;
}


void flag_ed(Graf* g, const char* v1, const char* v2, int fl)
{
    VertexListNode* v_1 = find_vertex(g, v1);
    VertexListNode* v_2 = find_vertex(g, v2);
    EdgeListNode* cur_e = NULL;
    EdgeListNode* cur_v1 = NULL;
    EdgeListNode* cur_v2 = NULL;

    cur_e = v_1->vertex->edgelist;
    while (cur_e) {
        if (cur_e->edge.vertex == v_2->vertex) {
            cur_v1 = cur_e;
            break;
        }
        cur_e = cur_e->next;
    }
   

    cur_e = v_2->vertex->edgelist;
    while (cur_e) {
        if (cur_e->edge.vertex == v_1->vertex) {
            cur_v2 = cur_e;
            break;
        }
        cur_e = cur_e->next;
    }
 
    if(fl == 1){
        cur_v1->edge.flag = 1;
        cur_v2->edge.flag = 1;}
    else{
        cur_v1->edge.flag = 0;
        cur_v2->edge.flag = 0;
    }
    return;
}

int mst(Graf* graf, unsigned target_port) {
    if (!graf || !graf->vertexlist) return 1;

    xedge* flagged_edges = malloc(MAX_EDGES * sizeof(xedge));
    int flagged_edges_count = 0;

    char** with_port = malloc(1 * sizeof(char*));
    char** without_port = malloc(1 * sizeof(char*));
    int with_count = 0;
    int without_count = 0;

   VertexListNode* current_vertex_node = graf->vertexlist;
    while (current_vertex_node != NULL) {
        if(current_vertex_node->vertex->port == target_port)
        {
            with_count++;
            if(with_count > 1){with_port = realloc(with_port, with_count*sizeof(char*));}
            with_port[with_count-1] = strdup(current_vertex_node->vertex->name);
        }
        else
        {
            without_count++;
            if(without_count > 1){without_port = realloc(without_port, without_count*sizeof(char*));}
            without_port[without_count-1] = strdup(current_vertex_node->vertex->name);
        }
        current_vertex_node = current_vertex_node->next;
    }
    if(with_count == 0){
        for (int i = 0; i < without_count; ++i) {
        free(without_port[i]);
        }
        free(with_port);
        free(without_port);
        return 1;
    }

    for (int i = 0; i < without_count; ++i) {
        for (int j = 0; j < with_count; ++j) {
            bellman_mst(graf, without_port[i], with_port[j], flagged_edges, &flagged_edges_count);
        }
    }

    for (int i = 0; i < with_count; ++i) {
        free(with_port[i]);
    }
    for (int i = 0; i < without_count; ++i) {
        free(without_port[i]);
    }
    free(with_port);
    free(without_port);

    for (int i = 0; i < flagged_edges_count; ++i) {
        flag_ed(graf, flagged_edges[i].v1, flagged_edges[i].v2, 1);
    }
    

    grafic_mst(graf);

 
    for (int i = 0; i < flagged_edges_count; ++i) {
        flag_ed(graf, flagged_edges[i].v1, flagged_edges[i].v2, 0);
    }

    // Освобождаем память, выделенную для flagged_edges
    for (int i = 0; i < flagged_edges_count; ++i) {
        free(flagged_edges[i].v1);
        free(flagged_edges[i].v2);
    }
    free(flagged_edges);

    return 0;
}