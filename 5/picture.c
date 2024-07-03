#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include <graphviz/gvc.h>
#include <graphviz/cdt.h>
#include <graphviz/pathplan.h>
#include <graphviz/cgraph.h>

// Максимальное количество рёбер для упрощения примера (может быть увеличено при необходимости)
#define MAX_EDGES 1000

// Структура для хранения уникальных ключей рёбер
typedef struct {
    char keys[MAX_EDGES][512];
    int count;
} EdgeSet;

// Функция для генерации ключа ребра
char* generate_edge_key(const char* from, const char* to) {
    char* key = malloc(strlen(from) + strlen(to) + 7);
    sprintf(key, "%s->%s", from, to);
    return key;
}

// Функция для добавления ключа в набор уникальных ключей
int add_edge_key(EdgeSet* edge_set, const char* key) {
    for (int i = 0; i < edge_set->count; ++i) {
        if (strcmp(edge_set->keys[i], key) == 0) {
            return 0; // Ключ уже существует
        }
    }
    if (edge_set->count < MAX_EDGES) {
        strncpy(edge_set->keys[edge_set->count], key, 512);
        edge_set->count++;
        return 1; // Ключ успешно добавлен
    }
    return 0; // Набор переполнен
}

// Рекурсивная функция для добавления вершин и рёбер в граф
void recur(Agraph_t *g, VertexListNode* vNode, EdgeSet* edge_set) {
    while (vNode) {
        Vertex* vertex = vNode->vertex;
        char vertex_label[512];
        snprintf(vertex_label, sizeof(vertex_label), "%s\nPort:%u", vertex->name, vertex->port);
        Agnode_t *node = agnode(g, vertex_label, 1);
        agsafeset(node, "label", vertex_label, "");

        EdgeListNode* eNode = vertex->edgelist;
        while (eNode) {
            Edge* edge = &eNode->edge;
            Vertex* toVertex = edge->vertex;
            char to_vertex_label[256];
            snprintf(to_vertex_label, sizeof(to_vertex_label), "%s\nPort:%u", toVertex->name, toVertex->port);
            Agnode_t *toNode = agnode(g, to_vertex_label, 1);

            // Создание ключа для ребра
            char* edge_key = generate_edge_key(vertex_label, to_vertex_label);
            char* reverse_edge_key = generate_edge_key(to_vertex_label, vertex_label);

            // Проверка на существование ребра и обратного ребра
            if (add_edge_key(edge_set, edge_key) && add_edge_key(edge_set, reverse_edge_key)) {
                // Создание метки для рёбер с перечислением портов
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
            eNode = eNode->next;
        }

        vNode = vNode->next;
    }
}

// Функция для создания графического вывода
void grafic(Graf *graf) {
    Agraph_t *g;
    GVC_t *gvc;
    gvc = gvContext();
    g = agopen("g", Agundirected, NULL);  // Для неориентированного графа

    EdgeSet edge_set = { .count = 0 };

    recur(g, graf->vertexlist, &edge_set);

    gvLayout(gvc, g, "dot");
    gvRenderFilename(gvc, g, "svg", "graph.svg");
    gvFreeLayout(gvc, g);
    agclose(g);
    gvFreeContext(gvc);
}