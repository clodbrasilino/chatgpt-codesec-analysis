#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

typedef enum {
    TYPE_INT,
    TYPE_STRING,
    TYPE_TUPLE
} ElementType;

typedef struct TupleElement {
    ElementType type;
    union {
        int int_value;
        char *str_value;
        struct TupleElement **tuple_elements;
    } data;
    int tuple_size;
} TupleElement;

typedef struct {
    char *key;
    int count;
} FrequencyEntry;

typedef struct {
    FrequencyEntry *entries;
    int size;
    int capacity;
} FrequencyTable;

void init_freq_table(FrequencyTable *table) {
    table->entries = NULL;
    table->size = 0;
    table->capacity = 0;
}

void add_frequency(FrequencyTable *table, const char *key) {
    for (int i = 0; i < table->size; i++) {
        if (strcmp(table->entries[i].key, key) == 0) {
            table->entries[i].count++;
            return;
        }
    }
    
    if (table->size >= table->capacity) {
        int new_capacity = (table->capacity == 0) ? 16 : table->capacity * 2;
        if (new_capacity > SIZE_MAX / sizeof(FrequencyEntry)) {
            exit(EXIT_FAILURE);
        }
        FrequencyEntry *new_entries = realloc(table->entries, new_capacity * sizeof(FrequencyEntry));
        if (!new_entries) {
            exit(EXIT_FAILURE);
        }
        table->entries = new_entries;
        table->capacity = new_capacity;
    }
    
    table->entries[table->size].key = strdup(key);
    if (!table->entries[table->size].key) {
        exit(EXIT_FAILURE);
    }
    table->entries[table->size].count = 1;
    table->size++;
}

void count_frequency_recursive(TupleElement *element, FrequencyTable *table) {
    if (!element) return;
    
    switch (element->type) {
        case TYPE_INT: {
            char buffer[32];
            int written = snprintf(buffer, sizeof(buffer), "%d", element->data.int_value);
            if (written < 0 || (size_t)written >= sizeof(buffer)) {
                exit(EXIT_FAILURE);
            }
            add_frequency(table, buffer);
            break;
        }
        case TYPE_STRING:
            add_frequency(table, element->data.str_value);
            break;
        case TYPE_TUPLE:
            for (int i = 0; i < element->tuple_size; i++) {
                count_frequency_recursive(element->data.tuple_elements[i], table);
            }
            break;
    }
}

void count_element_frequency(TupleElement *root, FrequencyTable *table) {
    init_freq_table(table);
    count_frequency_recursive(root, table);
}

void print_frequency_table(FrequencyTable *table) {
    for (int i = 0; i < table->size; i++) {
        printf("%s: %d\n", table->entries[i].key, table->entries[i].count);
    }
}

void free_frequency_table(FrequencyTable *table) {
    for (int i = 0; i < table->size; i++) {
        free(table->entries[i].key);
    }
    free(table->entries);
    table->entries = NULL;
    table->size = 0;
    table->capacity = 0;
}

TupleElement *create_int_element(int value) {
    TupleElement *element = malloc(sizeof(TupleElement));
    if (!element) return NULL;
    element->type = TYPE_INT;
    element->data.int_value = value;
    element->tuple_size = 0;
    return element;
}

TupleElement *create_string_element(const char *str) {
    TupleElement *element = malloc(sizeof(TupleElement));
    if (!element) return NULL;
    element->type = TYPE_STRING;
    element->data.str_value = strdup(str);
    if (!element->data.str_value) {
        free(element);
        return NULL;
    }
    element->tuple_size = 0;
    return element;
}

TupleElement *create_tuple_element(TupleElement **elements, int count) {
    if (count < 0) return NULL;
    
    TupleElement *element = malloc(sizeof(TupleElement));
    if (!element) return NULL;
    
    element->type = TYPE_TUPLE;
    element->tuple_size = count;
    
    if (count == 0) {
        element->data.tuple_elements = NULL;
        return element;
    }
    
    if (count > SIZE_MAX / sizeof(TupleElement*)) {
        free(element);
        return NULL;
    }
    
    element->data.tuple_elements = malloc(count * sizeof(TupleElement*));
    if (!element->data.tuple_elements) {
        free(element);
        return NULL;
    }
    
    size_t copy_size = (size_t)count * sizeof(TupleElement*);
    if (copy_size > SIZE_MAX) {
        free(element->data.tuple_elements);
        free(element);
        return NULL;
    }
    
    for (int i = 0; i < count; i++) {
        element->data.tuple_elements[i] = elements[i];
    }
    
    return element;
}

void free_element(TupleElement *element) {
    if (!element) return;
    
    switch (element->type) {
        case TYPE_INT:
            break;
        case TYPE_STRING:
            free(element->data.str_value);
            break;
        case TYPE_TUPLE:
            for (int i = 0; i < element->tuple_size; i++) {
                free_element(element->data.tuple_elements[i]);
            }
            free(element->data.tuple_elements);
            break;
    }
    free(element);
}

int main(void) {
    TupleElement *int1 = create_int_element(1);
    TupleElement *int2 = create_int_element(2);
    TupleElement *int3 = create_int_element(1);
    TupleElement *str1 = create_string_element("hello");
    TupleElement *str2 = create_string_element("world");
    TupleElement *str3 = create_string_element("hello");
    
    if (!int1 || !int2 || !int3 || !str1 || !str2 || !str3) {
        free_element(int1);
        free_element(int2);
        free_element(int3);
        free_element(str1);
        free_element(str2);
        free_element(str3);
        return EXIT_FAILURE;
    }
    
    TupleElement *inner_tuple_elements[] = {int2, str2, int3};
    TupleElement *inner_tuple = create_tuple_element(inner_tuple_elements, 3);
    if (!inner_tuple) {
        free_element(int1);
        free_element(int2);
        free_element(int3);
        free_element(str1);
        free_element(str2);
        free_element(str3);
        return EXIT_FAILURE;
    }
    
    TupleElement *outer_tuple_elements[] = {int1, str1, inner_tuple, str3};
    TupleElement *outer_tuple = create_tuple_element(outer_tuple_elements, 4);
    if (!outer_tuple) {
        free_element(inner_tuple);
        free_element(str3);
        return EXIT_FAILURE;
    }
    
    FrequencyTable freq_table;
    count_element_frequency(outer_tuple, &freq_table);
    print_frequency_table(&freq_table);
    
    free_frequency_table(&freq_table);
    free_element(outer_tuple);
    
    return 0;
}