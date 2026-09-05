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

Dictionary *dict_create(size_t size) {
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

size_t dict_hash(const char *key, size_t size) {
    size_t hash = 0;
    while (*key) {
        hash = (hash * 31) + (size_t)(*key++);
    }
    return hash % size;
}

int dict_set(Dictionary *dict, const char *key, int value) {
    if (!dict || !key) return -1;
    size_t index = dict_hash(key, dict->size);
    Node *current = dict->buckets[index];
    while (current) {
        if (strcmp(current->key, key) == 0) {
            current->value = value;
            return 0;
        }
        current = current->next;
    }
    Node *new_node = malloc(sizeof(Node));
    if (!new_node) return -1;
    new_node->key = strdup(key);
    if (!new_node->key) {
        free(new_node);
        return -1;
    }
    new_node->value = value;
    new_node->next = dict->buckets[index];
    dict->buckets[index] = new_node;
    return 0;
}

int dict_add(Dictionary *dict, const char *key, int value) {
    if (!dict || !key) return -1;
    size_t index = dict_hash(key, dict->size);
    Node *current = dict->buckets[index];
    while (current) {
        if (strcmp(current->key, key) == 0) {
            current->value += value;
            return 0;
        }
        current = current->next;
    }
    return dict_set(dict, key, value);
}

Dictionary *dict_combine(Dictionary *dict1, Dictionary *dict2) {
    if (!dict1 || !dict2) return NULL;
    Dictionary *result = dict_create(dict1->size + dict2->size);
    if (!result) return NULL;
    size_t i;
    Node *current;
    for (i = 0; i < dict1->size; i++) {
        current = dict1->buckets[i];
        while (current) {
            if (dict_set(result, current->key, current->value) != 0) {
                return NULL;
            }
            current = current->next;
        }
    }
    for (i = 0; i < dict2->size; i++) {
        current = dict2->buckets[i];
        while (current) {
            if (dict_add(result, current->key, current->value) != 0) {
                return NULL;
            }
            current = current->next;
        }
    }
    return result;
}

void dict_free(Dictionary *dict) {
    if (!dict) return;
    size_t i;
    Node *current;
    Node *next;
    for (i = 0; i < dict->size; i++) {
        current = dict->buckets[i];
        while (current) {
            next = current->next;
            free(current->key);
            free(current);
            current = next;
        }
    }
    free(dict->buckets);
    free(dict);
}

void dict_print(Dictionary *dict) {
    if (!dict) return;
    size_t i;
    Node *current;
    for (i = 0; i < dict->size; i++) {
        current = dict->buckets[i];
        while (current) {
            printf("%s: %d\n", current->key, current->value);
            current = current->next;
        }
    }
}

int main(void) {
    Dictionary *dict1 = dict_create(16);
    if (!dict1) return EXIT_FAILURE;
    Dictionary *dict2 = dict_create(16);
    if (!dict2) {
        dict_free(dict1);
        return EXIT_FAILURE;
    }

    dict_set(dict1, "apple", 5);
    dict_set(dict1, "banana", 3);
    dict_set(dict2, "apple", 2);
    dict_set(dict2, "cherry", 7);

    Dictionary *combined = dict_combine(dict1, dict2);
    if (!combined) {
        dict_free(dict1);
        dict_free(dict2);
        return EXIT_FAILURE;
    }

    dict_print(combined);

    dict_free(dict1);
    dict_free(dict2);
    dict_free(combined);

    return EXIT_SUCCESS;
}