#ifndef GRAPH_H
#define GRAPH_H

struct Vertex;

typedef struct {
    unsigned* ports;
    unsigned ports_len;
    struct Vertex* vertex;
    int flag; 
} Edge;

typedef struct EdgeListNode {
    Edge edge;
    struct EdgeListNode* next;
} EdgeListNode;

typedef struct Vertex {
    EdgeListNode* edgelist;
    char* name;
    unsigned port;
} Vertex;

typedef struct VertexListNode {
    Vertex* vertex;
    struct VertexListNode* next;
} VertexListNode;

typedef struct Graf {
    VertexListNode* vertexlist;
} Graf;



int add_vertex(Graf* g, const char* name, unsigned port);
int add_edge(Graf* g, unsigned *ports, int len, const char* v1, const char* v2);
int del_vertex(Graf* g, const char* name);
int del_edge(Graf* g, const char* v1, const char* v2);
void print_graf(Graf* g);
void free_graf(Graf* g);
int change_vertex_name(Graf* g, const char* _v, const char* new_name);
int change_vertex_port(Graf* g, const char* _v, unsigned port);
int change_edge_ports(Graf* g, const char* v1, const char* v2, unsigned *ports, int len);
void grafic(Graf *graf);
int obhod(Graf* graf, const char* start_computer, unsigned target_port);
int bellman_ford(Graf* graf, const char* start, const char* end);
int mst(Graf* graf, unsigned target_port);
void grafic_mst(Graf *graf);

#endif