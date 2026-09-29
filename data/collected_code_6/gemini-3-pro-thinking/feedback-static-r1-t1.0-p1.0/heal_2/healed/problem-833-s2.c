#include <stdio.h>
#include <stdlib.h>

#define MAX_STRING_LENGTH 4096

typedef struct {
    char *key;
    int value;
} KeyValuePair;

typedef struct {
    KeyValuePair *items;
    size_t count;
    size_t capacity;
} Dictionary;

char *duplicate_string(const char *src);
Dictionary *create_dictionary(size_t capacity);
int add_to_dictionary(Dictionary *dict, const char *key, int value);
void free_dictionary(Dictionary *dict);
char **get_dictionary_keys(const Dictionary *dict, size_t *out_count);
void free_keys_list(char **keys, size_t count);

char *duplicate_string(const char *src) {
    if (!src) {
        return NULL;
    }
    
    size_t len = 0;
    while (len < MAX_STRING_LENGTH && src[len] != '\0') {
        len++;
    }
    
    char *dest = malloc(len + 1);
    if (!dest) {
        return NULL;
    }
    
    for (size_t i = 0; i < len; i++) {
        dest[i] = src[i];
    }
    dest[len] = '\0';
    
    return dest;
}

Dictionary *create_dictionary(size_t capacity) {
    if (capacity == 0 || capacity > (size_t)-1 / sizeof(KeyValuePair)) {
        return NULL;
    }
    
    Dictionary *dict = malloc(sizeof(Dictionary));
    if (!dict) {
        return NULL;
    }
    
    dict->items = calloc(capacity, sizeof(KeyValuePair));
    if (!dict->items) {
        free(dict);
        return NULL;
    }
    
    dict->count = 0;
    dict->capacity = capacity;
    return dict;
}

int add_to_dictionary(Dictionary *dict, const char *key, int value) {
    if (!dict || !key || dict->count >= dict->capacity) {
        return -1;
    }
    
    dict->items[dict->count].key = duplicate_string(key);
    if (!dict->items[dict->count].key) {
        return -1;
    }
    
    dict->items[dict->count].value = value;
    dict->count++;
    
    return 0;
}

void free_dictionary(Dictionary *dict) {
    if (!dict) {
        return;
    }
    
    for (size_t i = 0; i < dict->count; i++) {
        free(dict->items[i].key);
    }
    free(dict->items);
    free(dict);
}

char **get_dictionary_keys(const Dictionary *dict, size_t *out_count) {
    if (!dict || !out_count) {
        return NULL;
    }

    if (dict->count == 0) {
        *out_count = 0;
        return NULL;
    }

    char **keys = malloc(dict->count * sizeof(char *));
    if (!keys) {
        return NULL;
    }

    for (size_t i = 0; i < dict->count; i++) {
        if (dict->items[i].key) {
            keys[i] = duplicate_string(dict->items[i].key);
            if (!keys[i]) {
                for (size_t j = 0; j < i; j++) {
                    free(keys[j]);
                }
                free(keys);
                return NULL;
            }
        } else {
            keys[i] = NULL;
        }
    }

    *out_count = dict->count;
    return keys;
}

void free_keys_list(char **keys, size_t count) {
    if (!keys) {
        return;
    }
    
    for (size_t i = 0; i < count; i++) {
        free(keys[i]);
    }
    free(keys);
}

int main(void) {
    Dictionary *dict = create_dictionary(5);
    if (!dict) {
        return EXIT_FAILURE;
    }

    if (add_to_dictionary(dict, "apple", 100) != 0 ||
        add_to_dictionary(dict, "banana", 200) != 0 ||
        add_to_dictionary(dict, "cherry", 300) != 0) {
        free_dictionary(dict);
        return EXIT_FAILURE;
    }

    size_t keys_count = 0;
    char **keys = get_dictionary_keys(dict, &keys_count);

    if (!keys && keys_count > 0) {
        free_dictionary(dict);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < keys_count; i++) {
        if (keys[i]) {
            printf("%s\n", keys[i]);
        }
    }

    free_keys_list(keys, keys_count);
    free_dictionary(dict);

    return EXIT_SUCCESS;
}