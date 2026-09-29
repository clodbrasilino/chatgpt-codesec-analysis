#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 4096

struct DictItem {
    char *key;
    char *value;
};

struct Dictionary {
    struct DictItem *items;
    size_t count;
};

void free_dictionary(struct Dictionary *dict) {
    if (!dict) {
        return;
    }
    
    if (dict->items) {
        for (size_t i = 0; i < dict->count; i++) {
            free(dict->items[i].key);
            free(dict->items[i].value);
        }
        free(dict->items);
    }
    free(dict);
}

struct Dictionary* tuple_to_dict(const char **tuple, size_t tuple_len) {
    if (!tuple || tuple_len == 0 || tuple_len % 2 != 0) {
        return NULL;
    }

    struct Dictionary *dict = malloc(sizeof(struct Dictionary));
    if (!dict) {
        return NULL;
    }

    dict->count = tuple_len / 2;
    dict->items = malloc(dict->count * sizeof(struct DictItem));
    if (!dict->items) {
        free(dict);
        return NULL;
    }

    for (size_t i = 0; i < dict->count; i++) {
        dict->items[i].key = NULL;
        dict->items[i].value = NULL;
    }

    for (size_t i = 0; i < dict->count; i++) {
        if (!tuple[i * 2] || !tuple[i * 2 + 1]) {
            free_dictionary(dict);
            return NULL;
        }

        size_t key_len = strnlen(tuple[i * 2], MAX_STR_LEN);
        size_t val_len = strnlen(tuple[i * 2 + 1], MAX_STR_LEN);

        dict->items[i].key = malloc(key_len + 1);
        dict->items[i].value = malloc(val_len + 1);

        if (!dict->items[i].key || !dict->items[i].value) {
            free_dictionary(dict);
            return NULL;
        }

        strncpy(dict->items[i].key, tuple[i * 2], key_len);
        dict->items[i].key[key_len] = '\0';

        strncpy(dict->items[i].value, tuple[i * 2 + 1], val_len);
        dict->items[i].value[val_len] = '\0';
    }

    return dict;
}

int main(void) {
    const char *tuple[] = {
        "name", "Alice",
        "age", "30",
        "city", "New York",
        "occupation", "Engineer"
    };
    size_t tuple_len = sizeof(tuple) / sizeof(tuple[0]);

    struct Dictionary *dict = tuple_to_dict(tuple, tuple_len);
    if (!dict) {
        fprintf(stderr, "Failed to create dictionary.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < dict->count; i++) {
        printf("%s: %s\n", dict->items[i].key, dict->items[i].value);
    }

    free_dictionary(dict);
    
    return EXIT_SUCCESS;
}