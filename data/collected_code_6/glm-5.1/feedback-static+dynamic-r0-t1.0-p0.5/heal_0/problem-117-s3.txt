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
    if (!list || !list->items) return -1;
    if (list->count >= list->capacity) {
        size_t new_capacity = list->capacity == 0 ? 4 : list->capacity * 2;
        void **new_items = realloc(list->items, new_capacity * sizeof(void *));
        if (!new_items) return -1;
        list->items = new_items;
        list->capacity = new_capacity;
    }
    list->items[list->count++] = item;
    return 0;
}

void list_free(List *list, int free_items) {
    if (!list) return;
    if (list->items) {
        if (free_items) {
            for (size_t i = 0; i < list->count; i++) {
                free(list->items[i]);
            }
        }
        free(list->items);
    }
    free(list);
}

float *convert_list_to_floats(const List *list, size_t *out_count) {
    if (!list || !out_count) {
        if (out_count) *out_count = 0;
        return NULL;
    }
    if (list->count == 0) {
        *out_count = 0;
        return malloc(0);
    }
    float *floats = malloc(list->count * sizeof(float));
    if (!floats) {
        *out_count = 0;
        return NULL;
    }
    size_t valid_count = 0;
    for (size_t i = 0; i < list->count; i++) {
        if (!list->items[i]) continue;
        char *endptr = NULL;
        const char *str = (const char *)list->items[i];
        errno = 0;
        double val = strtod(str, &endptr);
        if (errno == ERANGE || endptr == str || *endptr != '\0') {
            continue;
        }
        if (val > 0 && val > (double)3.402823466e38F) continue;
        if (val < 0 && val < (double)-3.402823466e38F) continue;
        floats[valid_count++] = (float)val;
    }
    if (valid_count == 0) {
        free(floats);
        *out_count = 0;
        return malloc(0);
    }
    float *shrunk = realloc(floats, valid_count * sizeof(float));
    if (shrunk) {
        floats = shrunk;
    }
    *out_count = valid_count;
    return floats;
}

int main(void) {
    List *list = list_create(8);
    if (!list) return 1;
    
    char *str1 = strdup("3.14");
    char *str2 = strdup("-42");
    char *str3 = strdup("1e5");
    char *str4 = strdup("not_a_float");
    char *str5 = strdup("123abc");
    char *str6 = strdup("0");
    char *str7 = strdup("3.4028235e38");
    
    if (str1) list_append(list, str1);
    if (str2) list_append(list, str2);
    if (str3) list_append(list, str3);
    if (str4) list_append(list, str4);
    if (str5) list_append(list, str5);
    if (str6) list_append(list, str6);
    if (str7) list_append(list, str7);
    
    size_t float_count = 0;
    float *floats = convert_list_to_floats(list, &float_count);
    
    for (size_t i = 0; i < float_count; i++) {
        printf("%f\n", floats[i]);
    }
    
    free(floats);
    list_free(list, 1);
    
    return 0;
}