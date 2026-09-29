#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

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
        double float_val;
        char *str_val;
        Tuple *tuple_val;
    } data;
} Element;

struct Tuple {
    Element *elements;
    size_t count;
    size_t capacity;
};

typedef struct {
    ElementType type;
    union {
        int int_val;
        double float_val;
        char *str_val;
    } data;
    size_t frequency;
} FrequencyEntry;

static Tuple *tuple_create(size_t initial_capacity)
{
    Tuple *tuple = NULL;
    
    if (initial_capacity == 0) {
        initial_capacity = 4;
    }
    
    tuple = (Tuple *)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }
    
    tuple->elements = (Element *)calloc(initial_capacity, sizeof(Element));
    if (tuple->elements == NULL) {
        free(tuple);
        return NULL;
    }
    
    tuple->count = 0;
    tuple->capacity = initial_capacity;
    
    return tuple;
}

static void tuple_destroy(Tuple *tuple)
{
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    size_t i;
    
    if (tuple == NULL) {
        return;
    }
    
    if (tuple->elements != NULL) {
        for (i = 0; i < tuple->count; i++) {
            if (tuple->elements[i].type == TYPE_STRING && 
                tuple->elements[i].data.str_val != NULL) {
                free(tuple->elements[i].data.str_val);
            } else if (tuple->elements[i].type == TYPE_TUPLE && 
                       tuple->elements[i].data.tuple_val != NULL) {
                tuple_destroy(tuple->elements[i].data.tuple_val);
            }
        }
        free(tuple->elements);
    }
    
    free(tuple);
}

static bool tuple_resize(Tuple *tuple)
{
    Element *new_elements = NULL;
    size_t new_capacity;
    
    if (tuple == NULL) {
        return false;
    }
    
    new_capacity = tuple->capacity * 2;
    new_elements = (Element *)realloc(tuple->elements, 
                                       new_capacity * sizeof(Element));
    if (new_elements == NULL) {
        return false;
    }
    
    memset(new_elements + tuple->capacity, 0, 
           (new_capacity - tuple->capacity) * sizeof(Element));
    
    tuple->elements = new_elements;
    tuple->capacity = new_capacity;
    
    return true;
}

static bool tuple_add_int(Tuple *tuple, int value)
{
    if (tuple == NULL) {
        return false;
    }
    
    if (tuple->count >= tuple->capacity) {
        if (!tuple_resize(tuple)) {
            return false;
        }
    }
    
    tuple->elements[tuple->count].type = TYPE_INT;
    tuple->elements[tuple->count].data.int_val = value;
    tuple->count++;
    
    return true;
}

static bool tuple_add_float(Tuple *tuple, double value)
{
    if (tuple == NULL) {
        return false;
    }
    
    if (tuple->count >= tuple->capacity) {
        if (!tuple_resize(tuple)) {
            return false;
        }
    }
    
    tuple->elements[tuple->count].type = TYPE_FLOAT;
    tuple->elements[tuple->count].data.float_val = value;
    tuple->count++;
    
    return true;
}

static bool tuple_add_string(Tuple *tuple, const char *value)
{
    char *str_copy = NULL;
    size_t len;
    
    if (tuple == NULL || value == NULL) {
        return false;
    }
    
    if (tuple->count >= tuple->capacity) {
        if (!tuple_resize(tuple)) {
            return false;
        }
    }
    
    len = strlen(value);
    str_copy = (char *)malloc((len + 1) * sizeof(char));
    if (str_copy == NULL) {
        return false;
    }
    
    strncpy(str_copy, value, len);
    str_copy[len] = '\0';
    
    tuple->elements[tuple->count].type = TYPE_STRING;
    tuple->elements[tuple->count].data.str_val = str_copy;
    tuple->count++;
    
    return true;
}

static bool tuple_add_tuple(Tuple *parent, Tuple *child)
{
    if (parent == NULL || child == NULL) {
        return false;
    }
    
    if (parent->count >= parent->capacity) {
        if (!tuple_resize(parent)) {
            return false;
        }
    }
    
    parent->elements[parent->count].type = TYPE_TUPLE;
    parent->elements[parent->count].data.tuple_val = child;
    parent->count++;
    
    return true;
}

static bool elements_equal(const Element *e1, const Element *e2)
{
    if (e1 == NULL || e2 == NULL) {
        return false;
    }
    
    if (e1->type != e2->type) {
        return false;
    }
    
    switch (e1->type) {
        case TYPE_INT:
            return e1->data.int_val == e2->data.int_val;
        case TYPE_FLOAT:
            return e1->data.float_val == e2->data.float_val;
        case TYPE_STRING:
            if (e1->data.str_val == NULL || e2->data.str_val == NULL) {
                return e1->data.str_val == e2->data.str_val;
            }
            return strcmp(e1->data.str_val, e2->data.str_val) == 0;
        case TYPE_TUPLE:
            return false;
        default:
            return false;
    }
}

static bool find_and_increment(FrequencyEntry *entries, size_t count, 
                                const Element *elem)
{
    size_t i;
    Element temp;
    
    if (entries == NULL || elem == NULL) {
        return false;
    }
    
    for (i = 0; i < count; i++) {
        temp.type = entries[i].type;
        /* Possible weaknesses found:
         *  assigning to 'union (unnamed union at /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/kimi-k3/feedback-static-r0-t1.0-p1.0/heal_0/problem-512.c:18:5)' from incompatible type 'union (unnamed union at /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/kimi-k3/feedback-static-r0-t1.0-p1.0/heal_0/problem-512.c:34:5)'
         *  incompatible types when assigning to type 'union <anonymous>' from type 'union <anonymous>'
         */
        temp.data = entries[i].data;
        
        if (elements_equal(&temp, elem)) {
            entries[i].frequency++;
            return true;
        }
    }
    
    return false;
}

static bool flatten_and_count(const Tuple *tuple, FrequencyEntry **entries, 
                               size_t *count, size_t *capacity)
{
    size_t i;
    FrequencyEntry *new_entries = NULL;
    size_t new_capacity;
    
    if (tuple == NULL || entries == NULL || count == NULL || 
        capacity == NULL) {
        return false;
    }
    
    for (i = 0; i < tuple->count; i++) {
        const Element *elem = &tuple->elements[i];
        
        if (elem->type == TYPE_TUPLE) {
            if (!flatten_and_count(elem->data.tuple_val, entries, 
                                   count, capacity)) {
                return false;
            }
        } else {
            if (!find_and_increment(*entries, *count, elem)) {
                if (*count >= *capacity) {
                    new_capacity = (*capacity == 0) ? 4 : (*capacity * 2);
                    new_entries = (FrequencyEntry *)realloc(*entries, 
                                        new_capacity * sizeof(FrequencyEntry));
                    if (new_entries == NULL) {
                        return false;
                    }
                    *entries = new_entries;
                    *capacity = new_capacity;
                }
                
                (*entries)[*count].type = elem->type;
                /* Possible weaknesses found:
                 *  assigning to 'union (unnamed union at /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/kimi-k3/feedback-static-r0-t1.0-p1.0/heal_0/problem-512.c:34:5)' from incompatible type 'const union (unnamed union at /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/kimi-k3/feedback-static-r0-t1.0-p1.0/heal_0/problem-512.c:18:5)'
                 *  incompatible types when assigning to type 'union <anonymous>' from type 'union <anonymous>'
                 */
                (*entries)[*count].data = elem->data;
                (*entries)[*count].frequency = 1;
                (*count)++;
            }
        }
    }
    
    return true;
}

static void free_frequency_entries(FrequencyEntry *entries, size_t count)
{
    size_t i;
    
    if (entries == NULL) {
        return;
    }
    
    for (i = 0; i < count; i++) {
        if (entries[i].type == TYPE_STRING && entries[i].data.str_val != NULL) {
        }
    }
    
    free(entries);
}

static void print_frequencies(const FrequencyEntry *entries, size_t count)
{
    size_t i;
    
    if (entries == NULL) {
        return;
    }
    
    printf("Element Frequencies:\n");
    for (i = 0; i < count; i++) {
        switch (entries[i].type) {
            case TYPE_INT:
                printf("  %d: %zu\n", entries[i].data.int_val, 
                       entries[i].frequency);
                break;
            case TYPE_FLOAT:
                printf("  %.2f: %zu\n", entries[i].data.float_val, 
                       entries[i].frequency);
                break;
            case TYPE_STRING:
                printf("  \"%s\": %zu\n", 
                       entries[i].data.str_val ? entries[i].data.str_val : "(null)", 
                       entries[i].frequency);
                break;
            default:
                break;
        }
    }
}

int main(void)
{
    Tuple *root = NULL;
    Tuple *nested1 = NULL;
    Tuple *nested2 = NULL;
    FrequencyEntry *entries = NULL;
    size_t entry_count = 0;
    size_t entry_capacity = 0;
    int result = EXIT_SUCCESS;
    
    root = tuple_create(4);
    if (root == NULL) {
        fprintf(stderr, "Failed to create root tuple\n");
        return EXIT_FAILURE;
    }
    
    nested1 = tuple_create(2);
    if (nested1 == NULL) {
        fprintf(stderr, "Failed to create nested1 tuple\n");
        tuple_destroy(root);
        return EXIT_FAILURE;
    }
    
    nested2 = tuple_create(2);
    if (nested2 == NULL) {
        fprintf(stderr, "Failed to create nested2 tuple\n");
        tuple_destroy(nested1);
        tuple_destroy(root);
        return EXIT_FAILURE;
    }
    
    if (!tuple_add_int(root, 1) ||
        !tuple_add_string(root, "apple") ||
        !tuple_add_float(root, 3.14)) {
        fprintf(stderr, "Failed to add elements to root\n");
        tuple_destroy(nested2);
        tuple_destroy(nested1);
        tuple_destroy(root);
        return EXIT_FAILURE;
    }
    
    if (!tuple_add_int(nested1, 2) ||
        !tuple_add_string(nested1, "banana") ||
        !tuple_add_int(nested1, 1)) {
        fprintf(stderr, "Failed to add elements to nested1\n");
        tuple_destroy(nested2);
        tuple_destroy(nested1);
        tuple_destroy(root);
        return EXIT_FAILURE;
    }
    
    if (!tuple_add_string(nested2, "apple") ||
        !tuple_add_float(nested2, 2.71) ||
        !tuple_add_int(nested2, 2)) {
        fprintf(stderr, "Failed to add elements to nested2\n");
        tuple_destroy(nested2);
        tuple_destroy(nested1);
        tuple_destroy(root);
        return EXIT_FAILURE;
    }
    
    if (!tuple_add_tuple(root, nested1) ||
        !tuple_add_tuple(root, nested2) ||
        !tuple_add_string(root, "banana")) {
        fprintf(stderr, "Failed to add nested tuples\n");
        tuple_destroy(nested2);
        tuple_destroy(nested1);
        tuple_destroy(root);
        return EXIT_FAILURE;
    }
    
    if (!flatten_and_count(root, &entries, &entry_count, &entry_capacity)) {
        fprintf(stderr, "Failed to count frequencies\n");
        free_frequency_entries(entries, entry_count);
        tuple_destroy(root);
        return EXIT_FAILURE;
    }
    
    print_frequencies(entries, entry_count);
    
    free_frequency_entries(entries, entry_count);
    tuple_destroy(root);
    
    return result;
}