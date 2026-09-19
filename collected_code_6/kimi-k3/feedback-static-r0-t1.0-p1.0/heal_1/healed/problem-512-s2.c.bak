#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING,
    TYPE_TUPLE
} ElementType;

typedef struct Tuple Tuple;

typedef struct {
    ElementType type;
    union {
        int int_val;
        float float_val;
        char *str_val;
        Tuple *tuple_val;
    } data;
} Element;

struct Tuple {
    Element *elements;
    size_t count;
    size_t capacity;
};

Tuple *tuple_create(size_t capacity) {
    Tuple *t = malloc(sizeof(Tuple));
    if (t == NULL) {
        return NULL;
    }
    t->elements = malloc(sizeof(Element) * capacity);
    if (t->elements == NULL) {
        free(t);
        return NULL;
    }
    t->count = 0;
    t->capacity = capacity;
    return t;
}

int tuple_add_int(Tuple *t, int val) {
    if (t == NULL || t->count >= t->capacity) {
        return -1;
    }
    t->elements[t->count].type = TYPE_INT;
    t->elements[t->count].data.int_val = val;
    t->count++;
    return 0;
}

int tuple_add_float(Tuple *t, float val) {
    if (t == NULL || t->count >= t->capacity) {
        return -1;
    }
    t->elements[t->count].type = TYPE_FLOAT;
    t->elements[t->count].data.float_val = val;
    t->count++;
    return 0;
}

int tuple_add_string(Tuple *t, const char *val) {
    if (t == NULL || val == NULL || t->count >= t->capacity) {
        return -1;
    }
    t->elements[t->count].type = TYPE_STRING;
    t->elements[t->count].data.str_val = malloc(strlen(val) + 1);
    if (t->elements[t->count].data.str_val == NULL) {
        return -1;
    }
    strcpy(t->elements[t->count].data.str_val, val);
    t->count++;
    return 0;
}

int tuple_add_tuple(Tuple *t, Tuple *val) {
    if (t == NULL || val == NULL || t->count >= t->capacity) {
        return -1;
    }
    t->elements[t->count].type = TYPE_TUPLE;
    t->elements[t->count].data.tuple_val = val;
    t->count++;
    return 0;
}

void tuple_free(Tuple *t) {
    if (t == NULL) {
        return;
    }
    for (size_t i = 0; i < t->count; i++) {
        if (t->elements[i].type == TYPE_STRING) {
            free(t->elements[i].data.str_val);
        }
    }
    free(t->elements);
    free(t);
}

int elements_equal(const Element *e1, ElementType type, const void *data) {
    if (e1->type != type) {
        return 0;
    }
    switch (type) {
        case TYPE_INT:
            return e1->data.int_val == *(const int *)data;
        case TYPE_FLOAT:
            return e1->data.float_val == *(const float *)data;
        case TYPE_STRING:
            return strcmp(e1->data.str_val, (const char *)data) == 0;
        case TYPE_TUPLE:
            return 0;
    }
    return 0;
}

void count_element_recursive(const Tuple *t, ElementType target_type, 
                            const void *target_data, size_t *count) {
    if (t == NULL || count == NULL) {
        return;
    }
    for (size_t i = 0; i < t->count; i++) {
        if (t->elements[i].type == TYPE_TUPLE) {
            count_element_recursive(t->elements[i].data.tuple_val, 
                                   target_type, target_data, count);
        } else if (elements_equal(&t->elements[i], target_type, target_data)) {
            (*count)++;
        }
    }
}

size_t count_element(const Tuple *t, ElementType type, const void *data) {
    size_t count = 0;
    if (t == NULL || data == NULL) {
        return 0;
    }
    count_element_recursive(t, type, data, &count);
    return count;
}

void collect_all_elements(const Tuple *t, Element **arr, size_t *idx, size_t max) {
    if (t == NULL || arr == NULL || idx == NULL) {
        return;
    }
    for (size_t i = 0; i < t->count && *idx < max; i++) {
        if (t->elements[i].type == TYPE_TUPLE) {
            collect_all_elements(t->elements[i].data.tuple_val, arr, idx, max);
        } else {
            arr[*idx] = &t->elements[i];
            (*idx)++;
        }
    }
}

size_t count_total_elements(const Tuple *t) {
    size_t total = 0;
    if (t == NULL) {
        return 0;
    }
    for (size_t i = 0; i < t->count; i++) {
        if (t->elements[i].type == TYPE_TUPLE) {
            total += count_total_elements(t->elements[i].data.tuple_val);
        } else {
            total++;
        }
    }
    return total;
}

void print_frequencies(const Tuple *t) {
    if (t == NULL) {
        return;
    }
    size_t total = count_total_elements(t);
    if (total == 0) {
        printf("Tuple is empty\n");
        return;
    }
    Element **all = malloc(sizeof(Element *) * total);
    if (all == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    size_t idx = 0;
    collect_all_elements(t, all, &idx, total);
    
    int *processed = calloc(total, sizeof(int));
    if (processed == NULL) {
        free(all);
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    
    printf("Element frequencies:\n");
    for (size_t i = 0; i < total; i++) {
        if (processed[i]) {
            continue;
        }
        size_t freq = 1;
        for (size_t j = i + 1; j < total; j++) {
            if (!processed[j] && all[i]->type == all[j]->type) {
                int match = 0;
                switch (all[i]->type) {
                    case TYPE_INT:
                        match = (all[i]->data.int_val == all[j]->data.int_val);
                        break;
                    case TYPE_FLOAT:
                        match = (all[i]->data.float_val == all[j]->data.float_val);
                        break;
                    case TYPE_STRING:
                        match = (strcmp(all[i]->data.str_val, all[j]->data.str_val) == 0);
                        break;
                    case TYPE_TUPLE:
                        break;
                }
                if (match) {
                    freq++;
                    processed[j] = 1;
                }
            }
        }
        switch (all[i]->type) {
            case TYPE_INT:
                printf("  %d: %zu\n", all[i]->data.int_val, freq);
                break;
            case TYPE_FLOAT:
                printf("  %.2f: %zu\n", all[i]->data.float_val, freq);
                break;
            case TYPE_STRING:
                printf("  \"%s\": %zu\n", all[i]->data.str_val, freq);
                break;
            case TYPE_TUPLE:
                break;
        }
    }
    free(processed);
    free(all);
}

int main(void) {
    Tuple *outer = tuple_create(10);
    if (outer == NULL) {
        fprintf(stderr, "Failed to create tuple\n");
        return EXIT_FAILURE;
    }
    
    Tuple *inner1 = tuple_create(5);
    if (inner1 == NULL) {
        fprintf(stderr, "Failed to create tuple\n");
        tuple_free(outer);
        return EXIT_FAILURE;
    }
    
    Tuple *inner2 = tuple_create(5);
    if (inner2 == NULL) {
        fprintf(stderr, "Failed to create tuple\n");
        tuple_free(inner1);
        tuple_free(outer);
        return EXIT_FAILURE;
    }
    
    if (tuple_add_int(outer, 1) != 0 ||
        tuple_add_string(outer, "apple") != 0 ||
        tuple_add_float(outer, 2.5f) != 0) {
        fprintf(stderr, "Failed to add elements\n");
        tuple_free(inner2);
        tuple_free(inner1);
        tuple_free(outer);
        return EXIT_FAILURE;
    }
    
    if (tuple_add_int(inner1, 2) != 0 ||
        tuple_add_string(inner1, "apple") != 0 ||
        tuple_add_int(inner1, 1) != 0) {
        fprintf(stderr, "Failed to add elements\n");
        tuple_free(inner2);
        tuple_free(inner1);
        tuple_free(outer);
        return EXIT_FAILURE;
    }
    
    if (tuple_add_string(inner2, "banana") != 0 ||
        tuple_add_int(inner2, 2) != 0 ||
        tuple_add_float(inner2, 2.5f) != 0) {
        fprintf(stderr, "Failed to add elements\n");
        tuple_free(inner2);
        tuple_free(inner1);
        tuple_free(outer);
        return EXIT_FAILURE;
    }
    
    if (tuple_add_tuple(outer, inner1) != 0 ||
        tuple_add_int(outer, 3) != 0 ||
        tuple_add_tuple(outer, inner2) != 0) {
        fprintf(stderr, "Failed to add elements\n");
        tuple_free(inner2);
        tuple_free(inner1);
        tuple_free(outer);
        return EXIT_FAILURE;
    }
    
    print_frequencies(outer);
    
    int target = 2;
    printf("\nFrequency of integer %d: %zu\n", target, 
           count_element(outer, TYPE_INT, &target));
    
    const char *target_str = "apple";
    printf("Frequency of string \"%s\": %zu\n", target_str,
           count_element(outer, TYPE_STRING, target_str));
    
    float target_float = 2.5f;
    printf("Frequency of float %.2f: %zu\n", target_float,
           count_element(outer, TYPE_FLOAT, &target_float));
    
    tuple_free(inner2);
    tuple_free(inner1);
    tuple_free(outer);
    
    return EXIT_SUCCESS;
}