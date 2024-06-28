#include <assert.h>
#include "dict.h"
#include "key_value.h"
#include <stdlib.h>

struct _node_t {
    dict_t left;
    dict_t right;
    key_t key;
    value_t value;
};

static bool invrep(dict_t d) {
    bool res = true;
    if(d != NULL){
        if(d->left != NULL && d->right != NULL){
            if(key_less(d->key, d->left->key) || key_less(d->right->key, d->key)){
                res = false;
            }
        }else if(d->left != NULL){
            if(key_less(d->key, d->left->key)){
                res = false;
            }
        }else if(d->right != NULL){
            if(key_less(d->right->key, d->key)){
                res = false;
            }
        }
        return res && invrep(d->right) && invrep(d->left);
    }else{
        return res;
    }
}

dict_t dict_empty(void) {
    dict_t dict = NULL;
    assert(invrep(dict) && dict_length(dict) == 0u);
    return dict;
}

dict_t dict_add(dict_t dict, key_t word, value_t def) {
    assert(invrep(dict) && word != NULL && def != NULL);
    if(dict == NULL){
        dict = malloc(sizeof(struct _node_t));
        dict->key = word;
        dict->value = def;
        dict->left = NULL;
        dict->right = NULL;
    }else{
        if(key_eq(word, dict->key)){
            dict->value = def;
        }else if(key_less(word, dict->key)){
            dict->left = dict_add(dict->left, word, def);
        }else{
            dict->right = dict_add(dict->right, word, def);
        }
    }
    assert(invrep(dict) && key_eq(def, dict_search(dict, word)));
    return dict;
}

value_t dict_search(dict_t dict, key_t word) {
    assert(invrep(dict) && word != NULL);
    key_t def=NULL;
    if(dict != NULL){
        if(key_eq(word, dict->key)){
            def = dict->value;
        }else if(key_less(word, dict->key)){
            def = dict_search(dict->left, word);
        }else{
            def = dict_search(dict->right, word);
        }
    }
    assert((def != NULL) == dict_exists(dict, word));
    return def;
}

bool dict_exists(dict_t dict, key_t word) {
    assert(invrep(dict) && word != NULL);
    bool res = false;
    if(dict != NULL){
        if(key_eq(word, dict->key)){
            res = true;
        }else if(key_less(word, dict->key)){
            res = dict_exists(dict->left, word);
        }else{
            res = dict_exists(dict->right, word);
        }
    }
    assert(invrep(dict));
    return res;
}

unsigned int dict_length(dict_t dict) {
    assert(invrep(dict));
    size_t n = 0u;
    if(dict != NULL){
        n++;
        n = n + dict_length(dict->left) + dict_length(dict->right);
    }
    return n;
}

dict_t dict_remove(dict_t dict, key_t word) {
    assert(invrep(dict) && word != NULL);
    if(dict_exists(dict, word)){
        if(key_less(word, dict->key)){
            dict->left = dict_remove(dict->left, word);
        }else if(key_less(dict->key, word)){
            dict->right = dict_remove(dict->right, word);
        }else if(key_eq(word, dict->key)){
            if(dict->left == NULL && dict->right == NULL){
                dict->value = value_destroy(dict->value);
                dict->key = key_destroy(dict->key);
                free(dict);
                dict = NULL;
            }else if(dict->left == NULL){
                dict_t temp = dict;
                temp->key = key_destroy(temp->key);
                temp->value = value_destroy(temp->value);
                dict = dict->right;
                free(temp);
                temp = NULL;
            }else if(dict->right == NULL){
                dict_t temp = dict;
                temp->key = key_destroy(temp->key);
                temp->value = value_destroy(temp->value);
                dict = dict->left;
                free(temp);
                temp = NULL;
            }else{
                dict_t min = dict->right;
                while(min->left != NULL){
                    min = min->left;
                }
                dict->key = min->key;
                dict->value = min->value;
                dict->right = dict_remove(dict->right, min->key);
            }
        }
    }
    assert(invrep(dict) && !dict_exists(dict, word));
    return dict;
}


dict_t dict_remove_all(dict_t dict) {
    assert(invrep(dict));
    if(dict != NULL){
        dict->key = key_destroy(dict->key);
        dict->value = value_destroy(dict->value);
        dict->right = dict_remove_all(dict->right);
        dict->left = dict_remove_all(dict->left);
        free(dict);
        dict = NULL;
    }
    assert(invrep(dict) && dict_length(dict) == 0u);
    return dict;
}

void dict_dump(dict_t dict, FILE *file){
    assert(invrep(dict) && file != NULL);
    if(dict != NULL){
        dict_dump(dict->left, file);
        key_dump(dict->key, file);
        fprintf(file, " : ");
        value_dump(dict->value, file);
        fprintf(file, "\n");
        dict_dump(dict->right, file);
    }
}

dict_t dict_destroy(dict_t dict) {
    assert(invrep(dict));
    if(dict != NULL){
        dict = dict_remove_all(dict);
        dict = NULL;
    }
    assert(dict == NULL);
    return dict;
}

