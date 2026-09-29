#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int key;
    int value;
    struct Node *next;
} Node;

typedef struct {
    Node **buckets;
    int size;
} Dictionary;

Dictionary *dictionary_create(int size) {
    Dictionary *dict = malloc(sizeof(Dictionary));
    if (dict == NULL) {
        return NULL;
    }
    dict->buckets = calloc(size, sizeof(Node *));
    if (dict->buckets == NULL) {
        free(dict);
        return NULL;
    }
    dict->size = size;
    return dict;
}

bool dictionary_insert(Dictionary *dict, int key, int value) {
    if (dict == NULL) {
        return false;
    }
    int index = abs(key) % dict->size;
    Node *current = dict->buckets[index];
    while (current != NULL) {
        if (current->key == key) {
            current->value = value;
            return true;
        }
        current = current->next;
    }
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        return false;
    }
    new_node->key = key;
    new_node->value = value;
    new_node->next = dict->buckets[index];
    dict->buckets[index] = new_node;
    return true;
}

bool dictionary_all_values_same(Dictionary *dict) {
    if (dict == NULL || dict->buckets == NULL) {
        return true;
    }
    int reference_value = 0;
    bool reference_set = false;
    for (int i = 0; i < dict->size; i++) {
        Node *current = dict->buckets[i];
        while (current != NULL) {
            if (!reference_set) {
                reference_value = current->value;
                reference_set = true;
            } else if (current->value != reference_value) {
                return false;
            }
            current = current->next;
        }
    }
    return true;
}

void dictionary_destroy(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }
    if (dict->buckets != NULL) {
        for (int i = 0; i < dict->size; i++) {
            Node *current = dict->buckets[i];
            while (current != NULL) {
                Node *temp = current;
                current = current->next;
                free(temp);
            }
        }
        free(dict->buckets);
    }
    free(dict);
}

int main(void) {
    Dictionary *dict1 = dictionary_create(10);
    if (dict1 == NULL) {
        return EXIT_FAILURE;
    }
    dictionary_insert(dict1, 1, 42);
    dictionary_insert(dict1, 2, 42);
    dictionary_insert(dict1, 3, 42);
    if (dictionary_all_values_same(dict1)) {
        printf("Dictionary 1: All values are the same\n");
    } else {
        printf("Dictionary 1: Values differ\n");
    }
    Dictionary *dict2 = dictionary_create(10);
    if (dict2 == NULL) {
        dictionary_destroy(dict1);
        return EXIT_FAILURE;
    }
    dictionary_insert(dict2, 1, 42);
    dictionary_insert(dict2, 2, 99);
    dictionary_insert(dict2, 3, 42);
    if (dictionary_all_values_same(dict2)) {
        printf("Dictionary 2: All values are the same\n");
    } else {
        printf("Dictionary 2: Values differ\n");
    }
    dictionary_destroy(dict1);
    dictionary_destroy(dict2);
    return EXIT_SUCCESS;
}