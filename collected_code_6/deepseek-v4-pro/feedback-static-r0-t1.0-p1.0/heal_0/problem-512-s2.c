#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef enum {
    TYPE_INT,
    TYPE_STRING,
    TYPE_TUPLE
} ElementType;

typedef struct Element {
    ElementType type;
    union {
        long long int_val;
        char *str_val;
        struct Element *tuple_val;
    } data;
    size_t tuple_size;
    struct Element *next;
} Element;

typedef struct {
    Element *head;
    size_t size;
} Tuple;

typedef struct FrequencyEntry {
    char *key;
    long long count;
    struct FrequencyEntry *next;
} FrequencyEntry;

typedef struct {
    FrequencyEntry *head;
    size_t size;
} FrequencyMap;

static Tuple *tuple_create(void) {
    Tuple *tuple = (Tuple *)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }
    tuple->head = NULL;
    tuple->size = 0;
    return tuple;
}

static Element *element_create_int(long long value) {
    Element *element = (Element *)malloc(sizeof(Element));
    if (element == NULL) {
        return NULL;
    }
    element->type = TYPE_INT;
    element->data.int_val = value;
    element->tuple_size = 0;
    element->next = NULL;
    return element;
}

static Element *element_create_string(const char *value) {
    Element *element = (Element *)malloc(sizeof(Element));
    if (element == NULL) {
        return NULL;
    }
    element->data.str_val = (char *)malloc(strlen(value) + 1);
    if (element->data.str_val == NULL) {
        free(element);
        return NULL;
    }
    strcpy(element->data.str_val, value);
    element->type = TYPE_STRING;
    element->tuple_size = 0;
    element->next = NULL;
    return element;
}

static Element *element_create_tuple(Tuple *tuple) {
    Element *element = (Element *)malloc(sizeof(Element));
    if (element == NULL) {
        return NULL;
    }
    element->type = TYPE_TUPLE;
    element->data.tuple_val = (Element *)malloc(sizeof(Element));
    if (element->data.tuple_val == NULL) {
        free(element);
        return NULL;
    }
    element->data.tuple_val->type = TYPE_TUPLE;
    element->data.tuple_val->data.tuple_val = (Element *)malloc(sizeof(Element));
    if (element->data.tuple_val->data.tuple_val == NULL) {
        free(element->data.tuple_val);
        free(element);
        return NULL;
    }
    element->data.tuple_val->data.tuple_val->type = TYPE_TUPLE;
    element->data.tuple_val->data.tuple_val->data.tuple_val = tuple->head;
    element->data.tuple_val->data.tuple_val->tuple_size = tuple->size;
    element->data.tuple_val->data.tuple_val->next = NULL;
    element->data.tuple_val->tuple_size = tuple->size;
    element->data.tuple_val->next = NULL;
    element->tuple_size = tuple->size;
    element->next = NULL;
    return element;
}

static void tuple_add_element(Tuple *tuple, Element *element) {
    if (tuple == NULL || element == NULL) {
        return;
    }
    if (tuple->head == NULL) {
        tuple->head = element;
    } else {
        Element *current = tuple->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = element;
    }
    tuple->size++;
}

static void tuple_free(Tuple *tuple) {
    if (tuple == NULL) {
        return;
    }
    Element *current = tuple->head;
    while (current != NULL) {
        Element *next = current->next;
        if (current->type == TYPE_STRING) {
            free(current->data.str_val);
        } else if (current->type == TYPE_TUPLE) {
            Tuple nested;
            nested.head = current->data.tuple_val->data.tuple_val->data.tuple_val;
            nested.size = current->data.tuple_val->data.tuple_val->tuple_size;
            tuple_free(&nested);
            free(current->data.tuple_val->data.tuple_val);
            free(current->data.tuple_val);
        }
        free(current);
        current = next;
    }
    tuple->head = NULL;
    tuple->size = 0;
}

static FrequencyMap *frequency_map_create(void) {
    FrequencyMap *map = (FrequencyMap *)malloc(sizeof(FrequencyMap));
    if (map == NULL) {
        return NULL;
    }
    map->head = NULL;
    map->size = 0;
    return map;
}

static void frequency_map_increment(FrequencyMap *map, const char *key) {
    if (map == NULL || key == NULL) {
        return;
    }
    FrequencyEntry *current = map->head;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            current->count++;
            return;
        }
        current = current->next;
    }
    FrequencyEntry *entry = (FrequencyEntry *)malloc(sizeof(FrequencyEntry));
    if (entry == NULL) {
        return;
    }
    entry->key = (char *)malloc(strlen(key) + 1);
    if (entry->key == NULL) {
        free(entry);
        return;
    }
    strcpy(entry->key, key);
    entry->count = 1;
    entry->next = map->head;
    map->head = entry;
    map->size++;
}

static void frequency_map_free(FrequencyMap *map) {
    if (map == NULL) {
        return;
    }
    FrequencyEntry *current = map->head;
    while (current != NULL) {
        FrequencyEntry *next = current->next;
        free(current->key);
        free(current);
        current = next;
    }
    map->head = NULL;
    map->size = 0;
    free(map);
}

static void element_to_string(Element *element, char *buffer, size_t buffer_size) {
    if (element == NULL || buffer == NULL || buffer_size == 0) {
        return;
    }
    switch (element->type) {
        case TYPE_INT:
            snprintf(buffer, buffer_size, "%lld", element->data.int_val);
            break;
        case TYPE_STRING:
            snprintf(buffer, buffer_size, "%s", element->data.str_val);
            break;
        case TYPE_TUPLE:
            snprintf(buffer, buffer_size, "tuple");
            break;
        default:
            buffer[0] = '\0';
            break;
    }
}

static void count_element_frequency_recursive(Element *element, FrequencyMap *map) {
    if (element == NULL || map == NULL) {
        return;
    }
    char buffer[256];
    element_to_string(element, buffer, sizeof(buffer));
    frequency_map_increment(map, buffer);
    if (element->type == TYPE_TUPLE) {
        Element *nested_element = element->data.tuple_val->data.tuple_val->data.tuple_val;
        size_t count = element->data.tuple_val->data.tuple_val->tuple_size;
        for (size_t i = 0; i < count && nested_element != NULL; i++) {
            count_element_frequency_recursive(nested_element, map);
            nested_element = nested_element->next;
        }
    }
}

static void count_element_frequency(Tuple *tuple, FrequencyMap *map) {
    if (tuple == NULL || map == NULL) {
        return;
    }
    Element *current = tuple->head;
    while (current != NULL) {
        count_element_frequency_recursive(current, map);
        current = current->next;
    }
}

static void print_frequency_map(FrequencyMap *map) {
    if (map == NULL) {
        return;
    }
    FrequencyEntry *current = map->head;
    while (current != NULL) {
        printf("%s: %lld\n", current->key, current->count);
        current = current->next;
    }
}

int main(void) {
    Tuple *tuple = tuple_create();
    if (tuple == NULL) {
        return 1;
    }

    Element *int_element = element_create_int(42);
    if (int_element == NULL) {
        tuple_free(tuple);
        free(tuple);
        return 1;
    }
    tuple_add_element(tuple, int_element);

    Element *str_element = element_create_string("hello");
    if (str_element == NULL) {
        tuple_free(tuple);
        free(tuple);
        return 1;
    }
    tuple_add_element(tuple, str_element);

    Element *int_element2 = element_create_int(42);
    if (int_element2 == NULL) {
        tuple_free(tuple);
        free(tuple);
        return 1;
    }
    tuple_add_element(tuple, int_element2);

    Tuple *nested_tuple = tuple_create();
    if (nested_tuple == NULL) {
        tuple_free(tuple);
        free(tuple);
        return 1;
    }

    Element *nested_int = element_create_int(7);
    if (nested_int == NULL) {
        tuple_free(nested_tuple);
        free(nested_tuple);
        tuple_free(tuple);
        free(tuple);
        return 1;
    }
    tuple_add_element(nested_tuple, nested_int);

    Element *nested_str = element_create_string("world");
    if (nested_str == NULL) {
        tuple_free(nested_tuple);
        free(nested_tuple);
        tuple_free(tuple);
        free(tuple);
        return 1;
    }
    tuple_add_element(nested_tuple, nested_str);

    Element *nested_tuple_element = element_create_tuple(nested_tuple);
    if (nested_tuple_element == NULL) {
        tuple_free(nested_tuple);
        free(nested_tuple);
        tuple_free(tuple);
        free(tuple);
        return 1;
    }
    tuple_add_element(tuple, nested_tuple_element);

    Element *str_element2 = element_create_string("hello");
    if (str_element2 == NULL) {
        tuple_free(tuple);
        free(tuple);
        return 1;
    }
    tuple_add_element(tuple, str_element2);

    FrequencyMap *map = frequency_map_create();
    if (map == NULL) {
        tuple_free(tuple);
        free(tuple);
        return 1;
    }

    count_element_frequency(tuple, map);
    print_frequency_map(map);

    frequency_map_free(map);
    tuple_free(tuple);
    free(tuple);
    tuple_free(nested_tuple);
    free(nested_tuple);

    return 0;
}