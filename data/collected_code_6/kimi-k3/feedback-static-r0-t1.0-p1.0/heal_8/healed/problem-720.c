#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    char *key;
    char *value;
} DictEntry;

typedef struct {
    DictEntry *entries;
    size_t size;
    size_t capacity;
} Dictionary;

typedef struct {
    void **items;
    size_t size;
    size_t capacity;
} Tuple;

static size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    if (str == NULL) {
        return 0;
    }
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

static int safe_memcpy(void *dest, size_t dest_size, const void *src, size_t count) {
    if (dest == NULL || src == NULL) {
        return -1;
    }
    if (count > dest_size) {
        return -1;
    }
    if (count == 0) {
        return 0;
    }
    if (dest_size > 0 && (uintptr_t)dest + dest_size < (uintptr_t)dest) {
        return -1;
    }
    if ((uintptr_t)src + count < (uintptr_t)src) {
        return -1;
    }
    uintptr_t dest_start = (uintptr_t)dest;
    uintptr_t dest_end = dest_start + dest_size;
    uintptr_t src_start = (uintptr_t)src;
    uintptr_t src_end = src_start + count;
    
    if ((dest_start < src_end) && (src_start < dest_end)) {
        return -1;
    }
    memmove(dest, src, count);
    return 0;
}

static int safe_mul_size(size_t a, size_t b, size_t *result) {
    if (result == NULL) {
        return -1;
    }
    if (a == 0 || b == 0) {
        *result = 0;
        return 0;
    }
    if (a > SIZE_MAX / b) {
        return -1;
    }
    *result = a * b;
    return 0;
}

Dictionary *dict_create(void) {
    Dictionary *dict = malloc(sizeof(Dictionary));
    if (dict == NULL) {
        return NULL;
    }
    dict->size = 0;
    dict->capacity = 4;
    dict->entries = calloc(dict->capacity, sizeof(DictEntry));
    if (dict->entries == NULL) {
        free(dict);
        return NULL;
    }
    return dict;
}

int dict_add(Dictionary *dict, const char *key, const char *value) {
    if (dict == NULL || key == NULL || value == NULL) {
        return -1;
    }
    if (dict->size >= dict->capacity) {
        size_t new_capacity;
        if (safe_mul_size(dict->capacity, 2, &new_capacity) != 0) {
            return -1;
        }
        size_t alloc_size;
        if (safe_mul_size(new_capacity, sizeof(DictEntry), &alloc_size) != 0) {
            return -1;
        }
        DictEntry *new_entries = realloc(dict->entries, alloc_size);
        if (new_entries == NULL) {
            return -1;
        }
        dict->entries = new_entries;
        dict->capacity = new_capacity;
    }
    size_t key_len = safe_strlen(key, SIZE_MAX - 1);
    if (key_len == 0 || key_len == SIZE_MAX - 1) {
        return -1;
    }
    key_len++;
    dict->entries[dict->size].key = malloc(key_len);
    if (dict->entries[dict->size].key == NULL) {
        return -1;
    }
    if (safe_memcpy(dict->entries[dict->size].key, key_len, key, key_len) != 0) {
        free(dict->entries[dict->size].key);
        dict->entries[dict->size].key = NULL;
        return -1;
    }
    size_t value_len = safe_strlen(value, SIZE_MAX - 1);
    if (value_len == SIZE_MAX - 1) {
        free(dict->entries[dict->size].key);
        dict->entries[dict->size].key = NULL;
        return -1;
    }
    value_len++;
    dict->entries[dict->size].value = malloc(value_len);
    if (dict->entries[dict->size].value == NULL) {
        free(dict->entries[dict->size].key);
        dict->entries[dict->size].key = NULL;
        return -1;
    }
    if (safe_memcpy(dict->entries[dict->size].value, value_len, value, value_len) != 0) {
        free(dict->entries[dict->size].key);
        free(dict->entries[dict->size].value);
        dict->entries[dict->size].key = NULL;
        dict->entries[dict->size].value = NULL;
        return -1;
    }
    dict->size++;
    return 0;
}

void dict_free(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }
    for (size_t i = 0; i < dict->size; i++) {
        free(dict->entries[i].key);
        free(dict->entries[i].value);
    }
    free(dict->entries);
    free(dict);
}

Tuple *tuple_create(void) {
    Tuple *tuple = malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }
    tuple->size = 0;
    tuple->capacity = 4;
    tuple->items = calloc(tuple->capacity, sizeof(void *));
    if (tuple->items == NULL) {
        free(tuple);
        return NULL;
    }
    return tuple;
}

int tuple_add_dict(Tuple *tuple, Dictionary *dict) {
    if (tuple == NULL || dict == NULL) {
        return -1;
    }
    if (tuple->size >= tuple->capacity) {
        size_t new_capacity;
        if (safe_mul_size(tuple->capacity, 2, &new_capacity) != 0) {
            return -1;
        }
        size_t alloc_size;
        if (safe_mul_size(new_capacity, sizeof(void *), &alloc_size) != 0) {
            return -1;
        }
        void **new_items = realloc(tuple->items, alloc_size);
        if (new_items == NULL) {
            return -1;
        }
        tuple->items = new_items;
        tuple->capacity = new_capacity;
    }
    tuple->items[tuple->size] = dict;
    tuple->size++;
    return 0;
}

void tuple_free(Tuple *tuple) {
    if (tuple == NULL) {
        return;
    }
    for (size_t i = 0; i < tuple->size; i++) {
        dict_free((Dictionary *)tuple->items[i]);
    }
    free(tuple->items);
    free(tuple);
}

int main(void) {
    Tuple *tuple = tuple_create();
    if (tuple == NULL) {
        fprintf(stderr, "Failed to create tuple\n");
        return EXIT_FAILURE;
    }

    Dictionary *dict1 = dict_create();
    if (dict1 == NULL) {
        fprintf(stderr, "Failed to create dictionary\n");
        tuple_free(tuple);
        return EXIT_FAILURE;
    }

    if (dict_add(dict1, "name", "Alice") != 0) {
        fprintf(stderr, "Failed to add entry to dictionary\n");
        dict_free(dict1);
        tuple_free(tuple);
        return EXIT_FAILURE;
    }

    if (dict_add(dict1, "age", "30") != 0) {
        fprintf(stderr, "Failed to add entry to dictionary\n");
        dict_free(dict1);
        tuple_free(tuple);
        return EXIT_FAILURE;
    }

    if (tuple_add_dict(tuple, dict1) != 0) {
        fprintf(stderr, "Failed to add dictionary to tuple\n");
        dict_free(dict1);
        tuple_free(tuple);
        return EXIT_FAILURE;
    }

    Dictionary *retrieved = (Dictionary *)tuple->items[0];
    if (retrieved != NULL) {
        for (size_t i = 0; i < retrieved->size; i++) {
            if (retrieved->entries[i].key != NULL && retrieved->entries[i].value != NULL) {
                printf("%s: %s\n", retrieved->entries[i].key, retrieved->entries[i].value);
            }
        }
    }

    tuple_free(tuple);
    return EXIT_SUCCESS;
}