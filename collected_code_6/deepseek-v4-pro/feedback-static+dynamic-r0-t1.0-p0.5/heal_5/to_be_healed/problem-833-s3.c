#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **keys;
    int count;
    int capacity;
} Dictionary;

Dictionary *dict_create(void) {
    Dictionary *dict = malloc(sizeof(Dictionary));
    if (!dict) return NULL;
    dict->keys = malloc(sizeof(char *) * 8);
    if (!dict->keys) {
        free(dict);
        return NULL;
    }
    dict->count = 0;
    dict->capacity = 8;
    return dict;
}

int dict_add(Dictionary *dict, const char *key) {
    if (!dict || !key) return -1;
    
    size_t key_len = strnlen(key, 256);
    if (key_len >= 256) return -1;

    if (dict->count >= dict->capacity) {
        int new_capacity = dict->capacity * 2;
        char **new_keys = realloc(dict->keys, sizeof(char *) * new_capacity);
        if (!new_keys) return -1;
        dict->keys = new_keys;
        dict->capacity = new_capacity;
    }
    
    dict->keys[dict->count] = malloc(key_len + 1);
    if (!dict->keys[dict->count]) return -1;
    
    if (key_len > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dict->keys[dict->count], key, key_len);
    }
    dict->keys[dict->count][key_len] = '\0';
    dict->count++;
    return 0;
}

char **dict_get_keys(Dictionary *dict, int *key_count) {
    if (!dict || !key_count) return NULL;
    if (dict->count == 0) {
        *key_count = 0;
        return NULL;
    }
    char **keys_copy = malloc(sizeof(char *) * dict->count);
    if (!keys_copy) {
        *key_count = 0;
        return NULL;
    }
    for (int i = 0; i < dict->count; i++) {
        size_t key_len = strnlen(dict->keys[i], 256);
        if (key_len >= 256) {
            for (int j = 0; j < i; j++) {
                free(keys_copy[j]);
            }
            free(keys_copy);
            *key_count = 0;
            return NULL;
        }
        keys_copy[i] = malloc(key_len + 1);
        if (!keys_copy[i]) {
            for (int j = 0; j < i; j++) {
                free(keys_copy[j]);
            }
            free(keys_copy);
            *key_count = 0;
            return NULL;
        }
        if (key_len > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(keys_copy[i], dict->keys[i], key_len);
        }
        keys_copy[i][key_len] = '\0';
    }
    *key_count = dict->count;
    return keys_copy;
}

void dict_free(Dictionary *dict) {
    if (!dict) return;
    for (int i = 0; i < dict->count; i++) {
        free(dict->keys[i]);
    }
    free(dict->keys);
    free(dict);
}

void free_keys_list(char **keys, int count) {
    if (!keys) return;
    for (int i = 0; i < count; i++) {
        free(keys[i]);
    }
    free(keys);
}

int main(void) {
    Dictionary *dict = dict_create();
    if (!dict) return 1;

    if (dict_add(dict, "apple") != 0 ||
        dict_add(dict, "banana") != 0 ||
        dict_add(dict, "cherry") != 0) {
        dict_free(dict);
        return 1;
    }

    int key_count = 0;
    char **keys = dict_get_keys(dict, &key_count);
    if (keys) {
        for (int i = 0; i < key_count; i++) {
            printf("%s\n", keys[i]);
        }
        free_keys_list(keys, key_count);
    }

    dict_free(dict);
    return 0;
}