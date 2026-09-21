#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_KEY_LENGTH 256
#define MAX_KEYS 100

typedef struct {
    char *keys[MAX_KEYS];
    size_t count;
} KeyList;

int add_key(KeyList *list, const char *key) {
    if (list == NULL || key == NULL) {
        return -1;
    }
    if (list->count >= MAX_KEYS) {
        return -1;
    }
    size_t key_len = strnlen(key, MAX_KEY_LENGTH);
    if (key_len == 0 || key_len >= MAX_KEY_LENGTH) {
        return -1;
    }
    if (key_len >= SIZE_MAX) {
        return -1;
    }
    list->keys[list->count] = malloc(key_len + 1);
    if (list->keys[list->count] == NULL) {
        return -1;
    }
    strncpy(list->keys[list->count], key, key_len);
    list->keys[list->count][key_len] = '\0';
    list->count++;
    return 0;
}

char **get_dictionary_keys(const KeyList *list, size_t *num_keys) {
    if (list == NULL || num_keys == NULL) {
        return NULL;
    }
    *num_keys = 0;
    if (list->count == 0 || list->count > MAX_KEYS) {
        return NULL;
    }
    if (list->count > SIZE_MAX / sizeof(char *)) {
        return NULL;
    }
    char **keys = calloc(list->count, sizeof(char *));
    if (keys == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < list->count; i++) {
        if (list->keys[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(keys[j]);
            }
            free(keys);
            return NULL;
        }
        size_t key_len = strnlen(list->keys[i], MAX_KEY_LENGTH);
        if (key_len == 0 || key_len >= MAX_KEY_LENGTH) {
            for (size_t j = 0; j < i; j++) {
                free(keys[j]);
            }
            free(keys);
            return NULL;
        }
        if (key_len >= SIZE_MAX) {
            for (size_t j = 0; j < i; j++) {
                free(keys[j]);
            }
            free(keys);
            return NULL;
        }
        keys[i] = malloc(key_len + 1);
        if (keys[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(keys[j]);
            }
            free(keys);
            return NULL;
        }
        strncpy(keys[i], list->keys[i], key_len);
        keys[i][key_len] = '\0';
    }
    *num_keys = list->count;
    return keys;
}

void free_keys(char **keys, size_t num_keys) {
    if (keys == NULL) {
        return;
    }
    for (size_t i = 0; i < num_keys; i++) {
        free(keys[i]);
    }
    free(keys);
}

void free_key_list(KeyList *list) {
    if (list == NULL) {
        return;
    }
    for (size_t i = 0; i < list->count; i++) {
        free(list->keys[i]);
        list->keys[i] = NULL;
    }
    list->count = 0;
}

int main(void) {
    KeyList dict = {0};
    if (add_key(&dict, "name") != 0) {
        fprintf(stderr, "Failed to add key\n");
        free_key_list(&dict);
        return EXIT_FAILURE;
    }
    if (add_key(&dict, "age") != 0) {
        fprintf(stderr, "Failed to add key\n");
        free_key_list(&dict);
        return EXIT_FAILURE;
    }
    if (add_key(&dict, "city") != 0) {
        fprintf(stderr, "Failed to add key\n");
        free_key_list(&dict);
        return EXIT_FAILURE;
    }
    size_t num_keys = 0;
    char **keys = get_dictionary_keys(&dict, &num_keys);
    if (keys == NULL) {
        fprintf(stderr, "Failed to retrieve keys\n");
        free_key_list(&dict);
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < num_keys; i++) {
        printf("%s\n", keys[i]);
    }
    free_keys(keys, num_keys);
    free_key_list(&dict);
    return EXIT_SUCCESS;
}