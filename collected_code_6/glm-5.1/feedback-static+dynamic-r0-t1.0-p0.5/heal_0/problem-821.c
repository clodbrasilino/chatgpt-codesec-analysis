#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **keys;
    char **values;
    size_t size;
    size_t capacity;
} Dictionary;

Dictionary *dict_create(size_t capacity) {
    Dictionary *dict = malloc(sizeof(Dictionary));
    if (!dict) return NULL;
    dict->keys = malloc(capacity * sizeof(char *));
    dict->values = malloc(capacity * sizeof(char *));
    if (!dict->keys || !dict->values) {
        free(dict->keys);
        free(dict->values);
        free(dict);
        return NULL;
    }
    dict->size = 0;
    dict->capacity = capacity;
    return dict;
}

int dict_insert(Dictionary *dict, const char *key, const char *value) {
    if (!dict || !key || !value) return -1;
    if (dict->size >= dict->capacity) return -1;
    dict->keys[dict->size] = strdup(key);
    dict->values[dict->size] = strdup(value);
    if (!dict->keys[dict->size] || !dict->values[dict->size]) {
        free(dict->keys[dict->size]);
        free(dict->values[dict->size]);
        return -1;
    }
    dict->size++;
    return 0;
}

void dict_free(Dictionary *dict) {
    if (!dict) return;
    for (size_t i = 0; i < dict->size; i++) {
        free(dict->keys[i]);
        free(dict->values[i]);
    }
    free(dict->keys);
    free(dict->values);
    free(dict);
}

Dictionary *dict_merge(const Dictionary *d1, const Dictionary *d2) {
    if (!d1 || !d2) return NULL;
    size_t total_capacity = d1->size + d2->size;
    if (total_capacity < d1->size) return NULL;
    Dictionary *merged = dict_create(total_capacity);
    if (!merged) return NULL;
    for (size_t i = 0; i < d1->size; i++) {
        if (dict_insert(merged, d1->keys[i], d1->values[i]) != 0) {
            dict_free(merged);
            return NULL;
        }
    }
    for (size_t i = 0; i < d2->size; i++) {
        size_t j;
        int found = 0;
        for (j = 0; j < d1->size; j++) {
            if (strcmp(d2->keys[i], d1->keys[j]) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) {
            if (dict_insert(merged, d2->keys[i], d2->values[i]) != 0) {
                dict_free(merged);
                return NULL;
            }
        }
    }
    return merged;
}

int main(void) {
    Dictionary *d1 = dict_create(4);
    Dictionary *d2 = dict_create(4);
    if (!d1 || !d2) {
        dict_free(d1);
        dict_free(d2);
        return 1;
    }
    dict_insert(d1, "a", "1");
    dict_insert(d1, "b", "2");
    dict_insert(d2, "b", "3");
    dict_insert(d2, "c", "4");
    Dictionary *merged = dict_merge(d1, d2);
    if (!merged) {
        dict_free(d1);
        dict_free(d2);
        return 1;
    }
    for (size_t i = 0; i < merged->size; i++) {
        printf("%s: %s\n", merged->keys[i], merged->values[i]);
    }
    dict_free(d1);
    dict_free(d2);
    dict_free(merged);
    return 0;
}