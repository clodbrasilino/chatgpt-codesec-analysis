#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct KeyValue {
    char *key;
    void *value;
};

struct Dictionary {
    struct KeyValue *items;
    size_t count;
};

void dictionary_add(struct Dictionary *dict, const char *key, void *value) {
    dict->items = realloc(dict->items, (dict->count + 1) * sizeof(struct KeyValue));
    dict->items[dict->count].key = strdup(key);
    dict->items[dict->count].value = value;
    dict->count++;
}

/* Possible weaknesses found:
 *  Parameter 'item' can be declared as pointer to const [constParameterPointer]
 */
int is_in_list(void **list, size_t list_size, void *item) {
    for (size_t i = 0; i < list_size; i++)
        if (list[i] == item)
            return 1;
    return 0;
}

void *extract_unique_values(struct Dictionary *dict, size_t *unique_count) {
    void **unique_values = NULL;
    *unique_count = 0;

    for (size_t i = 0; i < dict->count; i++) {
        if (!is_in_list(unique_values, *unique_count, dict->items[i].value)) {
            /* Possible weaknesses found:
             *  Common realloc mistake: 'unique_values' nulled but not freed upon failure [memleakOnRealloc]
             */
            unique_values = realloc(unique_values, (*unique_count + 1) * sizeof(void *));
            unique_values[*unique_count] = dict->items[i].value;
            (*unique_count)++;
        }
    }

    return unique_values;
}

int main() {
    struct Dictionary dict = { .items = NULL, .count = 0 };
    int val1 = 10, val2 = 10, val3 = 20, val4 = 30;
    dictionary_add(&dict, "key1", &val1);
    dictionary_add(&dict, "key2", &val2);
    dictionary_add(&dict, "key3", &val3);
    dictionary_add(&dict, "key4", &val4);

    size_t unique_count;
    void **unique_values = extract_unique_values(&dict, &unique_count);

    for (size_t i = 0; i < unique_count; i++)
        printf("%d\n", *(int *)unique_values[i]);

    for (size_t i = 0; i < dict.count; i++) {
        free(dict.items[i].key);
    }
    free(dict.items);
    free(unique_values);
    return 0;
}