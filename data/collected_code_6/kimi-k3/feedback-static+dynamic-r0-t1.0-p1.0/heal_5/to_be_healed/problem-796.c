#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    char *key;
    int value;
} DictItem;

typedef struct {
    DictItem *items;
    size_t size;
    size_t capacity;
} Dictionary;

int dict_init(Dictionary *dict, size_t initial_capacity) {
    if (dict == NULL || initial_capacity == 0) {
        return -1;
    }
    if (initial_capacity > SIZE_MAX / sizeof(DictItem)) {
        return -1;
    }
    dict->items = calloc(initial_capacity, sizeof(DictItem));
    if (dict->items == NULL) {
        return -1;
    }
    dict->size = 0;
    dict->capacity = initial_capacity;
    return 0;
}

int dict_add(Dictionary *dict, const char *key, int value) {
    if (dict == NULL || key == NULL || dict->items == NULL) {
        return -1;
    }
    if (dict->size >= dict->capacity) {
        size_t new_capacity;
        if (dict->capacity > SIZE_MAX / 2) {
            return -1;
        }
        new_capacity = dict->capacity * 2;
        if (new_capacity > SIZE_MAX / sizeof(DictItem)) {
            return -1;
        }
        DictItem *new_items = realloc(dict->items, new_capacity * sizeof(DictItem));
        if (new_items == NULL) {
            return -1;
        }
        dict->items = new_items;
        dict->capacity = new_capacity;
    }
    size_t key_len = strnlen(key, 256) + 1;
    if (key_len > 256) {
        return -1;
    }
    dict->items[dict->size].key = malloc(key_len);
    if (dict->items[dict->size].key == NULL) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(dict->items[dict->size].key, key, key_len - 1);
    dict->items[dict->size].key[key_len - 1] = '\0';
    dict->items[dict->size].value = value;
    dict->size++;
    return 0;
}

long dict_sum(const Dictionary *dict) {
    long sum = 0;
    size_t i;
    if (dict == NULL || dict->items == NULL) {
        return 0;
    }
    for (i = 0; i < dict->size; i++) {
        sum += dict->items[i].value;
    }
    return sum;
}

void dict_free(Dictionary *dict) {
    if (dict != NULL) {
        size_t i;
        for (i = 0; i < dict->size; i++) {
            free(dict->items[i].key);
        }
        free(dict->items);
        dict->items = NULL;
        dict->size = 0;
        dict->capacity = 0;
    }
}

int main(void) {
    Dictionary dict;
    long result;

    if (dict_init(&dict, 4) != 0) {
        fprintf(stderr, "Failed to initialize dictionary\n");
        return EXIT_FAILURE;
    }

    if (dict_add(&dict, "a", 10) != 0 ||
        dict_add(&dict, "b", 20) != 0 ||
        dict_add(&dict, "c", 30) != 0 ||
        dict_add(&dict, "d", 40) != 0 ||
        dict_add(&dict, "e", 50) != 0) {
        fprintf(stderr, "Failed to add items\n");
        dict_free(&dict);
        return EXIT_FAILURE;
    }

    result = dict_sum(&dict);
    printf("Sum of all items: %ld\n", result);

    dict_free(&dict);
    return EXIT_SUCCESS;
}