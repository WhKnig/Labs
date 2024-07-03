#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include <string.h>

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

int add_vertex(Graf* g, const char* name, unsigned port)
{
    if (find_vertex(g, name)) return 1;
    VertexListNode* new_vertex_node = (VertexListNode*)calloc(1, sizeof(VertexListNode));
    Vertex* new_vertex = (Vertex*)calloc(1, sizeof(Vertex));

    new_vertex_node->vertex = new_vertex;
    new_vertex_node->next = g->vertexlist;
    g->vertexlist = new_vertex_node;

    new_vertex->port = port;
    new_vertex->name = (char*)malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(new_vertex->name, name);
    return 0;
}

static EdgeListNode* create_edge(unsigned *ports, int len, Vertex* v)
{
    EdgeListNode* new_edge = (EdgeListNode*)calloc(1, sizeof(EdgeListNode));
    new_edge->edge.ports = (unsigned*)malloc(sizeof(unsigned) * len);
    memcpy(new_edge->edge.ports, ports, sizeof(unsigned) * len);
    new_edge->edge.vertex = v;
    new_edge->edge.ports_len = len;
    return new_edge;
}

int add_edge(Graf* g, unsigned *ports, int len, const char* v1, const char* v2)
{
    VertexListNode* v_1 = find_vertex(g, v1);
    VertexListNode* v_2 = find_vertex(g, v2);
    if (!(v_1 && v_2))
        return 1;
    EdgeListNode* cur = v_1->vertex->edgelist;
    while (cur)
    {
        if (cur->edge.vertex == v_2->vertex)
            return 1;
        cur = cur->next;
    }
    EdgeListNode* new_edge1 = create_edge(ports, len, v_1->vertex);
    EdgeListNode* new_edge2 = create_edge(ports, len, v_2->vertex);
    new_edge2->next = v_1->vertex->edgelist;
    v_1->vertex->edgelist = new_edge2;
    if (strcmp(v1, v2))
    {
        new_edge1->next = v_2->vertex->edgelist;
        v_2->vertex->edgelist = new_edge1;
    }
    return 0;
}

static void free_edge(EdgeListNode* eln)
{
    free(eln->edge.ports);
    free(eln);
}

static void free_vertex(Vertex* v)
{
    free(v->name);
    free(v);
}

int del_vertex(Graf* g, const char* name)
{
    VertexListNode* v1 = find_vertex(g, name);
    if (!v1)
        return 1;

    EdgeListNode* cur = v1->vertex->edgelist, *search_cur, *prev = NULL, *buf_cur;

    while (cur)
    {
        search_cur = cur->edge.vertex->edgelist;
        if (cur->edge.vertex != v1->vertex)
        {
            while (search_cur)
            {
                if (!strcmp(search_cur->edge.vertex->name, name))
                {
                    if (!prev)
                    {
                        cur->edge.vertex->edgelist = search_cur->next;
                    }
                    else
                    {
                        prev->next = search_cur->next;
                    }
                    free_edge(search_cur);
                    break;
                }
                prev = search_cur;
                search_cur = search_cur->next;
            }
        }
        buf_cur = cur->next;
        free_edge(cur);
        cur = buf_cur;
    }
    VertexListNode* cur_v = g->vertexlist, * prev_v = NULL;
    while (cur_v)
    {
        if (cur_v == v1)
        {
            if (!prev_v)
            {
                g->vertexlist = cur_v->next;
            }
            else
            {
                prev_v->next = cur_v->next;
            }
            break;
        }
        prev_v = cur_v;
        cur_v = cur_v->next;
    }
    free_vertex(v1->vertex);
    free(v1);
    return 0;
}

int del_edge(Graf* g, const char* v1, const char* v2)
{
    VertexListNode* v_1 = find_vertex(g, v1);
    VertexListNode* v_2 = find_vertex(g, v2);
    if (!(v_1 && v_2))
        return 1;

    EdgeListNode* cur = v_1->vertex->edgelist, * prev = NULL;
    while (cur)
    {
        if (cur->edge.vertex == v_2->vertex)
        {
            if (!prev)
            {
                v_1->vertex->edgelist = cur->next;
            }
            else
            {
                prev->next = cur->next;
            }
            free_edge(cur);
            break;
        }
        prev = cur;
        cur = cur->next;
    }

    cur = v_2->vertex->edgelist;
    prev = NULL;
    while (cur)
    {
        if (cur->edge.vertex == v_1->vertex)
        {
            if (!prev)
            {
                v_2->vertex->edgelist = cur->next;
            }
            else
            {
                prev->next = cur->next;
            }
            free_edge(cur);
            break;
        }
        prev = cur;
        cur = cur->next;
    }
    return 0;
}

void print_graf(Graf* g)
{
    printf("\n");
    VertexListNode* cur = g->vertexlist;
    EdgeListNode* cur_e;
    while (cur)
    {
        cur_e = cur->vertex->edgelist;
        printf("%s : ", cur->vertex->name);
        while (cur_e)
        {
            printf("%s", cur_e->edge.vertex->name);
            if (cur_e->next) {
                printf(", ");
            }
            cur_e = cur_e->next;
        }
        cur = cur->next;
        printf("\n");
    }
    printf("\n");
}

void free_graf(Graf* g)
{
    VertexListNode* cur = g->vertexlist, * buf;
    EdgeListNode* cur_e, * buf_e;
    while (cur)
    {
        cur_e = cur->vertex->edgelist;
        while (cur_e)
        {
            buf_e = cur_e->next;
            free_edge(cur_e);
            cur_e = buf_e;
        }
        buf = cur->next;
        free_vertex(cur->vertex);
        free(cur);
        cur = buf;
    }
    free(g);
}

int change_vertex_name(Graf* g, const char* _v, const char* new_name) {
    VertexListNode* v = find_vertex(g, _v);
    if (!v) return 1;

    v->vertex->name = (char*)realloc(v->vertex->name, sizeof(char)*(strlen(new_name) + 1));
    strcpy(v->vertex->name, new_name);
    return 0;
}

int change_vertex_port(Graf* g, const char* _v, unsigned port) {
    VertexListNode* v = find_vertex(g, _v);
    if (!v) return 1;
    v->vertex->port = port;
    return 0;
}

int change_edge_ports(Graf* g, const char* v1, const char* v2, unsigned *ports, int len) {
    if (!g || !g->vertexlist) return 1;
    VertexListNode* v_1 = find_vertex(g, v1);
    VertexListNode* v_2 = find_vertex(g, v2);
    if (!(v_1 && v_2)) return 1;

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
    if (!cur_e) return 1;

    cur_e = v_2->vertex->edgelist;
    while (cur_e) {
        if (cur_e->edge.vertex == v_1->vertex) {
            cur_v2 = cur_e;
            break;
        }
        cur_e = cur_e->next;
    }
    if (!cur_e) return 1;

    int old_len = cur_v1->edge.ports_len;
    unsigned *buf = (unsigned*)malloc(sizeof(unsigned) * old_len);
    memcpy(buf, cur_v1->edge.ports, sizeof(unsigned) * old_len);

    free(cur_v1->edge.ports);
    free(cur_v2->edge.ports);
    cur_v1->edge.ports_len = len;
    cur_v2->edge.ports_len = len;

    cur_v1->edge.ports = (unsigned*)malloc(sizeof(unsigned) * len);
    cur_v2->edge.ports = (unsigned*)malloc(sizeof(unsigned) * len);
    if (!(cur_v1->edge.ports && cur_v2->edge.ports)) {
        cur_v1->edge.ports = (unsigned*)malloc(sizeof(unsigned) * old_len);
        cur_v2->edge.ports = (unsigned*)malloc(sizeof(unsigned) * old_len);
        memcpy(cur_v1->edge.ports, buf, sizeof(unsigned) * old_len);
        memcpy(cur_v2->edge.ports, buf, sizeof(unsigned) * old_len);
        return 1;
    }
    memcpy(cur_v1->edge.ports, ports, sizeof(unsigned) * len);
    memcpy(cur_v2->edge.ports, ports, sizeof(unsigned) * len);
    free(buf);
    return 0;
}
