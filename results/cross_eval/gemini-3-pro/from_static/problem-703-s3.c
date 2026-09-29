#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *key;
    char *value;
    struct Node *next;
} Node;

typedef struct {
    Node **table;
    size_t size;
} Dictionary;

unsigned int hash(const char *key, size_t size) {
    unsigned int hashval = 0;
    for (; *key != '\0'; key++) {
        hashval = *key + 31 * hashval;
    }
    return hashval % size;
}

Dictionary *create_dictionary(size_t size) {
    if (size == 0) return NULL;
    Dictionary *dict = malloc(sizeof(Dictionary));
    if (!dict) return NULL;
    dict->size = size;
    dict->table = calloc(size, sizeof(Node *));
    if (!dict->table) {
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
    
    new_node->next = dict->table[index];
    dict->table[index] = new_node;
    return 1;
}

int contains_key(Dictionary *dict, const char *key) {
    if (!dict || !key) return 0;
    
    unsigned int index = hash(key, dict->size);
    Node *current = dict->table[index];
    
    while (current != NULL) {
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
        Node *current = dict->table[i];
        while (current != NULL) {
            Node *temp = current;
            current = current->next;
            free(temp->key);
            free(temp->value);
            free(temp);
        }
    }
    free(dict->table);
    free(dict);
}

int main(void) {
    Dictionary *dict = create_dictionary(100);
    if (!dict) return 1;

    if (!insert(dict, "apple", "A fruit")) {
        free_dictionary(dict);
        return 1;
    }
    if (!insert(dict, "car", "A vehicle")) {
        free_dictionary(dict);
        return 1;
    }

    if (contains_key(dict, "apple")) {
        printf("Key 'apple' is present in the dictionary.\n");
    } else {
        printf("Key 'apple' is not present in the dictionary.\n");
    }

    if (contains_key(dict, "banana")) {
        printf("Key 'banana' is present in the dictionary.\n");
    } else {
        printf("Key 'banana' is not present in the dictionary.\n");
    }

    free_dictionary(dict);
    return 0;
}