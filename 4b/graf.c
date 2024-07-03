#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphviz/gvc.h>
#include <graphviz/cdt.h>
#include <graphviz/pathplan.h>
#include <graphviz/cgraph.h>
#include "tree.h"


char* generate_record_label(item **items, int size) {
    int total_length = size * 6;
    for (int i = 0; i < size; i++) {
        total_length += strlen(items[i]->key);
    }
    total_length += 1;

    char *label = (char*)malloc(total_length);
    label[0] = '\0';

    for (int i = 0; i < size; i++) {
        char field[100];
        snprintf(field, sizeof(field), "<f%d> %s", i, items[i]->key);
        strcat(label, field);
        if (i < size - 1) {
            strcat(label, "|");
        }
    }

    return label;
}

void recur(Agraph_t *g, knot *elem, Agnode_t *parent, int parent_field) {
    if (elem == NULL) {
        return;
    }

    char *label = generate_record_label(elem->arr, elem->size);
    char node_name[100];
    snprintf(node_name, sizeof(node_name), "node_%p", (void*)elem);
    Agnode_t *n1 = agnode(g, node_name, 1);
    agset(n1, "label", label);
    agsafeset(n1, "shape", "record", "");
    free(label);

    if (parent != NULL) {
        char port_name[100];
        snprintf(port_name, sizeof(port_name), "f%d", parent_field);
        Agedge_t *e = agedge(g, parent, n1, NULL, 1);
        agset(e, "tailport", port_name);
    }

    for (int i = 0; i <= elem->size; ++i) {
        recur(g, elem->child[i], n1, i);
    }
}

// Function to create and render the graph
int graf(tree *tr) {
    Agraph_t *g;
    GVC_t *gvc;
    gvc = gvContext();
    g = agopen("g", Agdirected, NULL);
    recur(g, tr->root, NULL, 0);
    gvLayout(gvc, g, "dot");
    gvRenderFilename(gvc, g, "svg", "tree.svg");
    gvFreeLayout(gvc, g);
    agclose(g);
    gvFreeContext(gvc);
    return 0;
}
