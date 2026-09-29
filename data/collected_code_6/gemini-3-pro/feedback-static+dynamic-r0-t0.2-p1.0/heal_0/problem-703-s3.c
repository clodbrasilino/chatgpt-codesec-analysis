#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *key;
    char *value;
    struct Node *next;
} Node;

typedef struct {
    Node **buckets;
    size_t size;
} Dictionary;

unsigned int hash(const char *key, size_t size) {
    unsigned int hash_val = 0;
    while (*key) {
        hash_val = (hash_val << 5) + *key++;
    }
    return hash_val % size;
}

Dictionary* create_dictionary(size_t size) {
    if (size == 0) return NULL;
    Dictionary *dict = malloc(sizeof(Dictionary));
    if (!dict) return NULL;
    
    dict->size = size;
    dict->buckets = calloc(size, sizeof(Node*));
    if (!dict->buckets) {
        free(dict);
        return NULL;
    }
    return dict;
}

int insert(Dictionary *dict, const char *key, const char *value) {
    if (!dict || !key || !value) return 0;
    
    unsigned int index = hash(key, dict->size);
    Node *new_node = malloc(sizeof(Node));
    if (!new_node) return 0;
    
    new_node->key = strdup(key);
    if (!new_node->key) {
        free(new_node);
        return 0;
    }
    
    new_node->value = strdup(value);
    if (!new_node->value) {
        free(new_node->key);
        free(new_node);
        return 0;
    }
    
    new_node->next = dict->buckets[index];
    dict->buckets[index] = new_node;
    return 1;
}

int contains_key(const Dictionary *dict, const char *key) {
    if (!dict || !key) return 0;
    
    unsigned int index = hash(key, dict->size);
    Node *current = dict->buckets[index];
    
    while (current) {
        if (strcmp(current->key, key) == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void free_dictionary(Dictionary *dict) {
    if (!dict) return;
    
    for (size_t i = 0; i < dict->size; i++) {
        Node *current = dict->buckets[i];
        while (current) {
            Node *temp = current;
            current = current->next;
            free(temp->key);
            free(temp->value);
            free(temp);
        }
    }
    free(dict->buckets);
    free(dict);
}

int main(void) {
    Dictionary *dict = create_dictionary(10);
    if (!dict) {
        return EXIT_FAILURE;
    }
    
    if (!insert(dict, "apple", "fruit")) {
        free_dictionary(dict);
        return EXIT_FAILURE;
    }
    
    if (!insert(dict, "carrot", "vegetable")) {
        free_dictionary(dict);
        return EXIT_FAILURE;
    }
    
    if (contains_key(dict, "apple")) {
        printf("Key 'apple' is present.\n");
    } else {
        printf("Key 'apple' is not present.\n");
    }
    
    if (contains_key(dict, "banana")) {
        printf("Key 'banana' is present.\n");
    } else {
        printf("Key 'banana' is not present.\n");
    }
    
    free_dictionary(dict);
    return EXIT_SUCCESS;
}