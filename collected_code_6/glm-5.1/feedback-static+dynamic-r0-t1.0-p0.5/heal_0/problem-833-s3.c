#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *key;
    int value;
    struct Node *next;
} Node;

typedef struct {
    Node **buckets;
    size_t size;
} Dictionary;

Dictionary *dictionary_create(size_t size) {
    Dictionary *dict = malloc(sizeof(Dictionary));
    if (!dict) return NULL;
    dict->buckets = calloc(size, sizeof(Node *));
    if (!dict->buckets) {
        free(dict);
        return NULL;
    }
    dict->size = size;
    return dict;
}

int dictionary_insert(Dictionary *dict, const char *key, int value) {
    if (!dict || !key) return 0;
    size_t index = 0;
    for (size_t i = 0; key[i]; i++) {
        index = (index * 31 + key[i]) % dict->size;
    }
    Node *current = dict->buckets[index];
    while (current) {
        if (strcmp(current->key, key) == 0) {
            current->value = value;
            return 1;
        }
        current = current->next;
    }
    Node *new_node = malloc(sizeof(Node));
    if (!new_node) return 0;
    new_node->key = strdup(key);
    if (!new_node->key) {
        free(new_node);
        return 0;
    }
    new_node->value = value;
    new_node->next = dict->buckets[index];
    dict->buckets[index] = new_node;
    return 1;
}

char **dictionary_get_keys(Dictionary *dict, size_t *out_count) {
    if (!dict || !out_count) {
        if (out_count) *out_count = 0;
        return NULL;
    }
    size_t count = 0;
    for (size_t i = 0; i < dict->size; i++) {
        Node *current = dict->buckets[i];
        while (current) {
            count++;
            current = current->next;
        }
    }
    if (count == 0) {
        *out_count = 0;
        return NULL;
    }
    char **keys = malloc(count * sizeof(char *));
    if (!keys) {
        *out_count = 0;
        return NULL;
    }
    size_t index = 0;
    for (size_t i = 0; i < dict->size; i++) {
        Node *current = dict->buckets[i];
        while (current) {
            keys[index] = strdup(current->key);
            if (!keys[index]) {
                for (size_t j = 0; j < index; j++) {
                    free(keys[j]);
                }
                free(keys);
                *out_count = 0;
                return NULL;
            }
            index++;
            current = current->next;
        }
    }
    *out_count = count;
    return keys;
}

void dictionary_free(Dictionary *dict) {
    if (!dict) return;
    for (size_t i = 0; i < dict->size; i++) {
        Node *current = dict->buckets[i];
        while (current) {
            Node *next = current->next;
            free(current->key);
            free(current);
            current = next;
        }
    }
    free(dict->buckets);
    free(dict);
}

void free_keys(char **keys, size_t count) {
    if (!keys) return;
    for (size_t i = 0; i < count; i++) {
        free(keys[i]);
    }
    free(keys);
}

int main(void) {
    Dictionary *dict = dictionary_create(16);
    if (!dict) return EXIT_FAILURE;
    
    if (!dictionary_insert(dict, "apple", 1) ||
        !dictionary_insert(dict, "banana", 2) ||
        !dictionary_insert(dict, "cherry", 3)) {
        dictionary_free(dict);
        return EXIT_FAILURE;
    }
    
    size_t key_count = 0;
    char **keys = dictionary_get_keys(dict, &key_count);
    
    if (keys) {
        for (size_t i = 0; i < key_count; i++) {
            printf("%s\n", keys[i]);
        }
        free_keys(keys, key_count);
    }
    
    dictionary_free(dict);
    return EXIT_SUCCESS;
}