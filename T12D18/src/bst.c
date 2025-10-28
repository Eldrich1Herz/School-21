#include "bst.h"

#include <stdlib.h>

t_btree *bstree_create_node(int item) {
    t_btree *root;
    root = (t_btree *)malloc(sizeof(t_btree));
    if (root == NULL) {
        return NULL;
    }
    root->item = item;
    root->left = NULL;
    root->right = NULL;
    root->parent = NULL;

    return root;
}

int cmpf(int a, int b) { return a > b; }

void bstree_insert(t_btree *root, int item, int (*cmpf)(int, int)) {
    if (root == NULL) {
        return;  // Нельзя вставлять в NULL корень
    }

    t_btree *elem = root, *twink = NULL;

    t_btree *new_elem = malloc(sizeof(t_btree));
    if (new_elem == NULL) {
        return;  // Проверка на успешное выделение памяти
    }
    new_elem->item = item;
    new_elem->left = NULL;
    new_elem->right = NULL;

    while (elem != NULL) {
        twink = elem;
        if (cmpf(item, elem->item))
            elem = elem->right;
        else
            elem = elem->left;
    }

    new_elem->parent = twink;

    // twink гарантированно не NULL, так как root не NULL
    if (cmpf(item, twink->item))
        twink->right = new_elem;
    else
        twink->left = new_elem;
}
