#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    TYPE_INT,
    TYPE_STRING,
    TYPE_TUPLE
} ElementType;

struct TupleElement;

typedef struct TupleElement {
    ElementType type;
    union {
        int int_val;
        char *str_val;
        struct {
            struct TupleElement **elements;
            size_t count;
        } tuple_val;
    } data;
} TupleElement;

typedef enum {
    KEY_INT,
    KEY_STRING
} KeyType;

typedef struct {
    KeyType type;
    union {
        int int_val;
        char *str_val;
    } key;
    size_t count;
} FreqNode;

typedef struct {
    FreqNode *nodes;
    size_t size;
    size_t capacity;
} FreqMap;

FreqMap* create_freq_map(void) {
    FreqMap *map = malloc(sizeof(FreqMap));
    if (!map) {
        return NULL;
    }
    map->capacity = 16;
    map->size = 0;
    map->nodes = malloc(map->capacity * sizeof(FreqNode));
    if (!map->nodes) {
        free(map);
        return NULL;
    }
    return map;
}

void free_freq_map(FreqMap *map) {
    if (!map) {
        return;
    }
    for (size_t i = 0; i < map->size; i++) {
        if (map->nodes[i].type == KEY_STRING) {
            free(map->nodes[i].key.str_val);
        }
    }
    free(map->nodes);
    free(map);
}

static int add_int_freq(FreqMap *map, int val) {
    for (size_t i = 0; i < map->size; i++) {
        if (map->nodes[i].type == KEY_INT && map->nodes[i].key.int_val == val) {
            map->nodes[i].count++;
            return 0;
        }
    }
    if (map->size >= map->capacity) {
        size_t new_cap = map->capacity * 2;
        FreqNode *new_nodes = realloc(map->nodes, new_cap * sizeof(FreqNode));
        if (!new_nodes) {
            return -1;
        }
        map->nodes = new_nodes;
        map->capacity = new_cap;
    }
    map->nodes[map->size].type = KEY_INT;
    map->nodes[map->size].key.int_val = val;
    map->nodes[map->size].count = 1;
    map->size++;
    return 0;
}

static int add_str_freq(FreqMap *map, const char *val) {
    if (!val) {
        return -1;
    }
    for (size_t i = 0; i < map->size; i++) {
        if (map->nodes[i].type == KEY_STRING && strcmp(map->nodes[i].key.str_val, val) == 0) {
            map->nodes[i].count++;
            return 0;
        }
    }
    if (map->size >= map->capacity) {
        size_t new_cap = map->capacity * 2;
        FreqNode *new_nodes = realloc(map->nodes, new_cap * sizeof(FreqNode));
        if (!new_nodes) {
            return -1;
        }
        map->nodes = new_nodes;
        map->capacity = new_cap;
    }
    char *str_copy = strdup(val);
    if (!str_copy) {
        return -1;
    }
    map->nodes[map->size].type = KEY_STRING;
    map->nodes[map->size].key.str_val = str_copy;
    map->nodes[map->size].count = 1;
    map->size++;
    return 0;
}

int count_frequencies(const TupleElement *element, FreqMap *map) {
    if (!element || !map) {
        return -1;
    }
    if (element->type == TYPE_INT) {
        return add_int_freq(map, element->data.int_val);
    } else if (element->type == TYPE_STRING) {
        return add_str_freq(map, element->data.str_val);
    } else if (element->type == TYPE_TUPLE) {
        for (size_t i = 0; i < element->data.tuple_val.count; i++) {
            if (count_frequencies(element->data.tuple_val.elements[i], map) != 0) {
                return -1;
            }
        }
        return 0;
    }
    return -1;
}

void print_frequencies(const FreqMap *map) {
    if (!map) {
        return;
    }
    for (size_t i = 0; i < map->size; i++) {
        if (map->nodes[i].type == KEY_INT) {
            printf("Integer %d: %zu\n", map->nodes[i].key.int_val, map->nodes[i].count);
        } else if (map->nodes[i].type == KEY_STRING) {
            printf("String '%s': %zu\n", map->nodes[i].key.str_val, map->nodes[i].count);
        }
    }
}

TupleElement* create_int_element(int val) {
    TupleElement *el = malloc(sizeof(TupleElement));
    if (el) {
        el->type = TYPE_INT;
        el->data.int_val = val;
    }
    return el;
}

TupleElement* create_str_element(const char *val) {
    if (!val) {
        return NULL;
    }
    TupleElement *el = malloc(sizeof(TupleElement));
    if (el) {
        el->type = TYPE_STRING;
        el->data.str_val = strdup(val);
        if (!el->data.str_val) {
            free(el);
            return NULL;
        }
    }
    return el;
}

TupleElement* create_tuple_element(size_t count) {
    TupleElement *el = malloc(sizeof(TupleElement));
    if (el) {
        el->type = TYPE_TUPLE;
        el->data.tuple_val.count = count;
        el->data.tuple_val.elements = calloc(count, sizeof(TupleElement*));
        if (!el->data.tuple_val.elements) {
            free(el);
            return NULL;
        }
    }
    return el;
}

void free_tuple_element(TupleElement *el) {
    if (!el) {
        return;
    }
    if (el->type == TYPE_STRING) {
        free(el->data.str_val);
    } else if (el->type == TYPE_TUPLE) {
        if (el->data.tuple_val.elements) {
            for (size_t i = 0; i < el->data.tuple_val.count; i++) {
                free_tuple_element(el->data.tuple_val.elements[i]);
            }
            free(el->data.tuple_val.elements);
        }
    }
    free(el);
}

int main(void) {
    TupleElement *root = create_tuple_element(4);
    if (!root) return EXIT_FAILURE;

    TupleElement *nested = create_tuple_element(2);
    if (!nested) {
        free_tuple_element(root);
        return EXIT_FAILURE;
    }

    nested->data.tuple_val.elements[0] = create_str_element("apple");
    nested->data.tuple_val.elements[1] = create_int_element(42);

    root->data.tuple_val.elements[0] = create_int_element(42);
    root->data.tuple_val.elements[1] = nested;
    root->data.tuple_val.elements[2] = create_str_element("apple");
    root->data.tuple_val.elements[3] = create_int_element(7);

    for (size_t i = 0; i < root->data.tuple_val.count; i++) {
        if (!root->data.tuple_val.elements[i]) {
            free_tuple_element(root);
            return EXIT_FAILURE;
        }
    }

    FreqMap *map = create_freq_map();
    if (!map) {
        free_tuple_element(root);
        return EXIT_FAILURE;
    }

    if (count_frequencies(root, map) == 0) {
        print_frequencies(map);
    }

    free_freq_map(map);
    free_tuple_element(root);

    return EXIT_SUCCESS;
}