#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    TYPE_INT,
    TYPE_DICT
} ValueType;

typedef struct Dict Dict;
typedef struct Entry Entry;

struct Entry {
    char *key;
    ValueType type;
    union {
        int int_val;
        Dict *dict_val;
    } value;
    Entry *next;
};

struct Dict {
    Entry *head;
};

Dict *create_dict(void) {
    Dict *d = malloc(sizeof(Dict));
    if (d == NULL) {
        return NULL;
    }
    d->head = NULL;
    return d;
}

Entry *create_int_entry(const char *key, int val) {
    Entry *e = malloc(sizeof(Entry));
    if (e == NULL) {
        return NULL;
    }
    e->key = strdup(key);
    if (e->key == NULL) {
        free(e);
        return NULL;
    }
    e->type = TYPE_INT;
    e->value.int_val = val;
    e->next = NULL;
    return e;
}

Entry *create_dict_entry(const char *key, Dict *val) {
    Entry *e = malloc(sizeof(Entry));
    if (e == NULL) {
        return NULL;
    }
    e->key = strdup(key);
    if (e->key == NULL) {
        free(e);
        return NULL;
    }
    e->type = TYPE_DICT;
    e->value.dict_val = val;
    e->next = NULL;
    return e;
}

void add_entry(Dict *d, Entry *e) {
    if (d == NULL || e == NULL) {
        return;
    }
    e->next = d->head;
    d->head = e;
}

int find_depth(Dict *d) {
    if (d == NULL) {
        return 0;
    }
    int max_depth = 1;
    Entry *curr = d->head;
    while (curr != NULL) {
        if (curr->type == TYPE_DICT) {
            int sub_depth = find_depth(curr->value.dict_val);
            if (1 + sub_depth > max_depth) {
                max_depth = 1 + sub_depth;
            }
        }
        curr = curr->next;
    }
    return max_depth;
}

void free_dict(Dict *d) {
    if (d == NULL) {
        return;
    }
    Entry *curr = d->head;
    while (curr != NULL) {
        Entry *next = curr->next;
        if (curr->type == TYPE_DICT) {
            free_dict(curr->value.dict_val);
        }
        free(curr->key);
        free(curr);
        curr = next;
    }
    free(d);
}

int main(void) {
    Dict *d1 = create_dict();
    Dict *d2 = create_dict();
    Dict *d3 = create_dict();
    
    if (d1 == NULL || d2 == NULL || d3 == NULL) {
        free_dict(d3);
        free_dict(d2);
        free_dict(d1);
        return EXIT_FAILURE;
    }

    add_entry(d1, create_int_entry("a", 1));
    add_entry(d2, create_int_entry("b", 2));
    add_entry(d3, create_int_entry("c", 3));
    add_entry(d3, create_dict_entry("d", d2));
    add_entry(d1, create_dict_entry("e", d3));

    printf("Depth: %d\n", find_depth(d1));
    printf("Null Depth: %d\n", find_depth(NULL));

    free_dict(d1);

    return EXIT_SUCCESS;
}