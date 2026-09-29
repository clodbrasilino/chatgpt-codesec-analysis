#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct {
    void **items;
    size_t count;
    size_t capacity;
} List;

List *list_create(size_t initial_capacity) {
    List *list = malloc(sizeof(List));
    if (!list) return NULL;
    list->items = malloc(initial_capacity * sizeof(void *));
    if (!list->items) {
        free(list);
        return NULL;
    }
    list->count = 0;
    list->capacity = initial_capacity;
    return list;
}

int list_append(List *list, void *item) {
    if (!list) return -1;
    if (list->count == list->capacity) {
        size_t new_capacity = list->capacity * 2;
        void **new_items = realloc(list->items, new_capacity * sizeof(void *));
        if (!new_items) return -1;
        list->items = new_items;
        list->capacity = new_capacity;
    }
    list->items[list->count++] = item;
    return 0;
}

void list_free(List *list) {
    if (!list) return;
    for (size_t i = 0; i < list->count; i++) {
        free(list->items[i]);
    }
    free(list->items);
    free(list);
}

float *convert_to_floats(const List *list, size_t *out_count) {
    if (!list || !out_count) return NULL;
    float *result = malloc(list->count * sizeof(float));
    if (!result) {
        *out_count = 0;
        return NULL;
    }
    size_t valid_count = 0;
    for (size_t i = 0; i < list->count; i++) {
        char *endptr = NULL;
        const char *str = (const char *)list->items[i];
        if (!str) continue;
        errno = 0;
        float val = strtof(str, &endptr);
        if (errno == 0 && endptr != str && *endptr == '\0') {
            result[valid_count++] = val;
        }
    }
    if (valid_count == 0) {
        free(result);
        *out_count = 0;
        return NULL;
    }
    float *shrunk_result = realloc(result, valid_count * sizeof(float));
    if (shrunk_result) {
        result = shrunk_result;
    }
    *out_count = valid_count;
    return result;
}

int main(void) {
    List *list = list_create(8);
    if (!list) return EXIT_FAILURE;
    
    list_append(list, strdup("3.14"));
    list_append(list, strdup("not_a_float"));
    list_append(list, strdup("42"));
    list_append(list, strdup("16.0"));
    list_append(list, strdup("1e-5"));
    list_append(list, strdup("123abc"));
    list_append(list, strdup("0"));
    list_append(list, strdup(""));

    size_t float_count = 0;
    float *floats = convert_to_floats(list, &float_count);
    
    if (floats) {
        for (size_t i = 0; i < float_count; i++) {
            printf("%f\n", floats[i]);
        }
        free(floats);
    }
    
    list_free(list);
    return EXIT_SUCCESS;
}