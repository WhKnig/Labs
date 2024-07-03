#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphviz/gvc.h>
#include <graphviz/cdt.h>
#include <graphviz/pathplan.h>
#include <graphviz/cgraph.h>
#include "tree.h"

char* name_node(node *elem)
{
    int size = (13 + strlen(elem->key));
    char *name = (char*)calloc(size, sizeof(char));
    snprintf(name, size,"%s: %u", elem->key, elem->info);
    return name;
}      

void recur(Agraph_t *g,node *elem, Agnode_t *n2)
{
    Agnode_t *n1;
    char *name = name_node(elem);
    n1 = agnode(g, name,1);
    free(name);
    if (n2 != NULL)
    {
        agedge(g, n2, n1, 0, 1);
    }
    if (elem->left != NULL)
    {
        recur(g,elem->left,n1);
    }
    if(elem->right != NULL)
    {
        recur(g,elem->right,n1);
    }
}

int graf(tree *tr) 
{
    Agraph_t *g;
    GVC_t *gvc;
    gvc = gvContext();
    g = agopen("g",  Agdirected,0);
    recur(g,tr->head,NULL);
    gvLayout(gvc, g, "dot");
    gvRenderFilename(gvc, g, "svg", "tree.svg");
    gvFreeLayout(gvc, g);
    agclose(g);
    gvFreeContext(gvc);
    return 0;
}
