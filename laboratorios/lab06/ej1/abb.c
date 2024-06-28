#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "abb.h"

struct _s_abb {
    abb_elem elem;
    struct _s_abb *left;
    struct _s_abb *right;
};

static bool elem_eq(abb_elem a, abb_elem b) {
    return a == b;
}

static bool elem_less(abb_elem a, abb_elem b) {
    return a < b;
}

static bool invrep(abb tree) {
    bool b = true;
    if(tree != NULL){
        if(tree->left != NULL && tree->right != NULL){
            if(tree->elem >= abb_min(tree->right) || tree->elem <= abb_max(tree->left)){
                b = false;
            }
        }else if(tree->left != NULL){
            if(tree->elem <= abb_max(tree->left)){
                b = false;
            }
        }else if(tree->right != NULL){
            if(tree->elem >= abb_max(tree->right)){
                b = false;
            }
        }
        return b && invrep(tree->left) && invrep(tree->right);
    }else{
        return b;
    }
    
}

abb abb_empty(void) {
    abb tree;
    tree = NULL;
    assert(invrep(tree) && abb_is_empty(tree));
    return tree;
}

abb abb_add(abb tree, abb_elem e) {
    assert(invrep(tree));
    if(tree == NULL){
        tree = malloc(sizeof(struct _s_abb));
        tree->elem = e;
        tree->left = NULL;
        tree->right = NULL;
    }else{
        if(elem_less(tree->elem, e)){
            tree->right = abb_add(tree->right, e);
        }else if(elem_less(e, tree->elem)){
            tree->left = abb_add(tree->left, e);
        }
    }
    assert(invrep(tree) && abb_exists(tree, e));
    return tree;
}

bool abb_is_empty(abb tree) {
    bool is_empty=false;
    assert(invrep(tree));
    is_empty = tree == NULL;
    return is_empty;
}

bool abb_exists(abb tree, abb_elem e) {
    bool exists=false;
    assert(invrep(tree));
    if(!abb_is_empty(tree)){
        if(elem_eq(tree->elem, e)){
            exists = true;
        }else{
            exists = (abb_exists(tree->left, e) || abb_exists(tree->right, e));
        }
    }
    assert(abb_length(tree)!=0 || !exists);
    return exists;
}

unsigned int abb_length(abb tree) {
    unsigned int length=0;
    assert(invrep(tree));
    if(!abb_is_empty(tree)){
        length++;
        length = length + abb_length(tree->left) + abb_length(tree->right);
    }
    assert(invrep(tree) && (abb_is_empty(tree) || length > 0));
    return length;
}

abb abb_remove(abb tree, abb_elem e) {
    assert(invrep(tree));
    if(abb_exists(tree, e)){
        if(e > tree->elem){
            tree->right = abb_remove(tree->right, e);
        }else if(e < tree->elem){
            tree->left = abb_remove(tree->left, e);
        }else{
            if(abb_is_empty(tree->left) && abb_is_empty(tree->right)){
                free(tree);
                tree = NULL;
            }else if(abb_is_empty(tree->left)){
                abb temp = tree;
                tree = tree->right;
                free(temp);
                temp = NULL;
            }else if(abb_is_empty(tree->right)){
                abb temp = tree;
                tree = tree->left;
                free(temp);
                temp = NULL;
            }else{
                tree->elem = abb_min(tree->right);
                tree->right = abb_remove(tree->right, tree->elem);
            }
        }
    }
    assert(invrep(tree) && !abb_exists(tree, e));
    return tree;
}


abb_elem abb_root(abb tree) {
    abb_elem root;
    assert(invrep(tree) && !abb_is_empty(tree));
    root = tree->elem;
    assert(abb_exists(tree, root));
    return root;
}

abb_elem abb_max(abb tree) {
    abb_elem max_e;
    assert(invrep(tree) && !abb_is_empty(tree));
    max_e = tree->elem;
    if(!abb_is_empty(tree->right)){
        max_e = abb_max(tree->right);
    }
    assert(invrep(tree) && abb_exists(tree, max_e));
    return max_e;
}

abb_elem abb_min(abb tree) {
    abb_elem min_e;
    assert(invrep(tree) && !abb_is_empty(tree));
    min_e = tree->elem;
    if(!abb_is_empty(tree->left)){
        min_e = abb_min(tree->left);
    }
    assert(invrep(tree) && abb_exists(tree, min_e));
    return min_e;
}

void abb_dump(abb tree, abb_ordtype ord) {
    assert(invrep(tree) && (ord==ABB_IN_ORDER  || 
                            ord==ABB_PRE_ORDER ||
                            ord==ABB_POST_ORDER));
    /*
     * c) Needs implementation: use the dump order indicated by `ord`
     *
     */

    // Implementing in-order as default
    if (tree != NULL && ord == ABB_IN_ORDER) {
        abb_dump(tree->left, ord);
        printf("%d ", tree->elem);
        abb_dump(tree->right, ord);
    }else if(tree != NULL && ord == ABB_PRE_ORDER){
        printf("%d ", tree->elem);
        abb_dump(tree->left, ord);
        abb_dump(tree->right, ord);
    }else if(tree != NULL && ord == ABB_POST_ORDER){
        abb_dump(tree->left, ord);
        abb_dump(tree->right, ord);
        printf("%d ", tree->elem);
    }
}

abb abb_destroy(abb tree) {
    assert(invrep(tree));
    if(!abb_is_empty(tree)){
        tree->left = abb_destroy(tree->left);
        tree->right = abb_destroy(tree->right);
        free(tree);
        tree = NULL;
    }
    assert(tree == NULL);
    return tree;
}

