#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEY_LEN 4096

typedef struct {
    char *key;
    int value;
} DictItem;

typedef struct {
    DictItem *items;
    size_t count;
    size_t capacity;
} Dictionary;

static char *safe_strdup(const char *src) {
    if (src == NULL) {
        return NULL;
    }
    
    size_t len = 0;
    while (src[len] != '\0' && len < MAX_KEY_LEN) {
        len++;
    }
    
    char *dest = malloc(len + 1);
    if (dest == NULL) {
        return NULL;
    }
    
    for (size_t i = 0; i < len; ++i) {
        dest[i] = src[i];
    }
    dest[len] = '\0';
    
    return dest;
}

char **get_dictionary_keys(const Dictionary *dict, size_t *out_count) {
    if (dict == NULL || out_count == NULL) {
        return NULL;
    }

    if (dict->count == 0) {
        *out_count = 0;
        return NULL;
    }

    char **keys = malloc(dict->count * sizeof(char *));
    if (keys == NULL) {
        *out_count = 0;
        return NULL;
    }

    for (size_t i = 0; i < dict->count; ++i) {
        if (dict->items[i].key == NULL) {
            keys[i] = NULL;
            continue;
        }

        keys[i] = safe_strdup(dict->items[i].key);
        if (keys[i] == NULL) {
            for (size_t j = 0; j < i; ++j) {
                free(keys[j]);
            }
            free(keys);
            *out_count = 0;
            return NULL;
        }
    }

    *out_count = dict->count;
    return keys;
}

void free_dictionary_keys(char **keys, size_t count) {
    if (keys == NULL) {
        return;
    }
    for (size_t i = 0; i < count; ++i) {
        free(keys[i]);
    }
    free(keys);
}

int dictionary_add(Dictionary *dict, const char *key, int value) {
    if (dict == NULL || key == NULL) {
        return -1;
    }

    if (dict->count >= dict->capacity) {
        size_t new_capacity = dict->capacity == 0 ? 4 : dict->capacity * 2;
        DictItem *new_items = realloc(dict->items, new_capacity * sizeof(DictItem));
        if (new_items == NULL) {
            return -1;
        }
        dict->items = new_items;
        dict->capacity = new_capacity;
    }

    dict->items[dict->count].key = safe_strdup(key);
    if (dict->items[dict->count].key == NULL) {
        return -1;
    }
    
    dict->items[dict->count].value = value;
    dict->count++;

    return 0;
}

void free_dictionary(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }
    if (dict->items != NULL) {
        for (size_t i = 0; i < dict->count; ++i) {
            free(dict->items[i].key);
        }
        free(dict->items);
    }
    dict->items = NULL;
    dict->count = 0;
    dict->capacity = 0;
}

int main(void) {
    Dictionary dict = {NULL, 0, 0};

    if (dictionary_add(&dict, "apple", 1) != 0) {
        free_dictionary(&dict);
        return EXIT_FAILURE;
    }
    if (dictionary_add(&dict, "banana", 2) != 0) {
        free_dictionary(&dict);
        return EXIT_FAILURE;
    }
    if (dictionary_add(&dict, "cherry", 3) != 0) {
        free_dictionary(&dict);
        return EXIT_FAILURE;
    }

    size_t keys_count = 0;
    char **keys = get_dictionary_keys(&dict, &keys_count);

    if (keys != NULL) {
        for (size_t i = 0; i < keys_count; ++i) {
            if (keys[i] != NULL) {
                printf("%s\n", keys[i]);
            }
        }
        free_dictionary_keys(keys, keys_count);
    }

    free_dictionary(&dict);
    return EXIT_SUCCESS;
}