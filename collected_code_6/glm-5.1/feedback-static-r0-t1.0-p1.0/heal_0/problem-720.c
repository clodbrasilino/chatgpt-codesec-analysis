#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    int capacity;
    int size;
} Tuple;

typedef struct {
    char **keys;
    char **values;
    int capacity;
    int size;
} Dictionary;

Tuple* tuple_create(int capacity) {
    Tuple *t = (Tuple*)malloc(sizeof(Tuple));
    if (!t) return NULL;
    t->items = (char**)malloc(capacity * sizeof(char*));
    if (!t->items) {
        free(t);
        return NULL;
    }
    t->capacity = capacity;
    t->size = 0;
    return t;
}

void tuple_free(Tuple *t) {
    if (t) {
        for (int i = 0; i < t->size; i++) {
            free(t->items[i]);
        }
        free(t->items);
        free(t);
    }
}

Dictionary* dictionary_create(int capacity) {
    Dictionary *d = (Dictionary*)malloc(sizeof(Dictionary));
    if (!d) return NULL;
    d->keys = (char**)malloc(capacity * sizeof(char*));
    if (!d->keys) {
        free(d);
        return NULL;
    }
    d->values = (char**)malloc(capacity * sizeof(char*));
    if (!d->values) {
        free(d->keys);
        free(d);
        return NULL;
    }
    d->capacity = capacity;
    d->size = 0;
    return d;
}

void dictionary_free(Dictionary *d) {
    if (d) {
        for (int i = 0; i < d->size; i++) {
            free(d->keys[i]);
            free(d->values[i]);
        }
        free(d->keys);
        free(d->values);
        free(d);
    }
}

int tuple_add_dictionary(Tuple *t, Dictionary *d) {
    if (!t || !d) return -1;
    if (t->size >= t->capacity) return -1;
    
    char *serialized_dict = (char*)malloc(4096 * sizeof(char));
    if (!serialized_dict) return -1;
    
    serialized_dict[0] = '{';
    serialized_dict[1] = '\0';
    
    for (int i = 0; i < d->size; i++) {
        strcat(serialized_dict, d->keys[i]);
        strcat(serialized_dict, ": ");
        strcat(serialized_dict, d->values[i]);
        if (i < d->size - 1) {
            strcat(serialized_dict, ", ");
        }
    }
    strcat(serialized_dict, "}");
    
    char *dict_copy = strdup(serialized_dict);
    free(serialized_dict);
    if (!dict_copy) return -1;
    
    t->items[t->size++] = dict_copy;
    return 0;
}

int main() {
    Tuple *t = tuple_create(5);
    if (!t) return 1;
    
    Dictionary *d = dictionary_create(5);
    if (!d) {
        tuple_free(t);
        return 1;
    }
    
    d->keys[0] = strdup("name");
    d->values[0] = strdup("C");
    d->size = 1;
    
    if (!d->keys[0] || !d->values[0]) {
        dictionary_free(d);
        tuple_free(t);
        return 1;
    }
    
    if (tuple_add_dictionary(t, d) != 0) {
        dictionary_free(d);
        tuple_free(t);
        return 1;
    }
    
    printf("Tuple[0]: %s\n", t->items[0]);
    
    dictionary_free(d);
    tuple_free(t);
    
    return 0;
}