#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *key;
    int value;
    struct Node *next;
} Node;

typedef struct Dictionary {
    int size;
    Node **buckets;
} Dictionary;

Dictionary* create_dictionary(int capacity) {
    Dictionary *dict = malloc(sizeof(Dictionary));
    dict->size = capacity;
    dict->buckets = calloc(capacity, sizeof(Node*));
    return dict;
}

void add_to_dictionary(Dictionary *dict, const char *key, int value) {
    unsigned long hash = 5381;
    int len = strlen(key);
    for (int i = 0; i < len; i++) {
        hash = ((hash << 5) + hash) + key[i];
    }
    int index = hash % dict->size;

    Node *new_node = malloc(sizeof(Node));
    new_node->key = strdup(key);
    new_node->value = value;
    new_node->next = dict->buckets[index];
    dict->buckets[index] = new_node;
}

void free_dictionary(Dictionary *dict) {
    for (int i = 0; i < dict->size; i++) {
        Node *current = dict->buckets[i];
        while (current != NULL) {
            Node *temp = current;
            current = current->next;
            free(temp->key);
            free(temp);
        }
    }
    free(dict->buckets);
    free(dict);
}

void print_dictionary(Dictionary *dict) {
    for (int i = 0; i < dict->size; i++) {
        Node *current = dict->buckets[i];
        printf("[ ");
        while (current != NULL) {
            printf("%s: %d ", current->key, current->value);
            current = current->next;
        }
        printf("]\n");
    }
}

int main() {
    Dictionary *dict = create_dictionary(10);
    
    add_to_dictionary(dict, "apple", 1);
    add_to_dictionary(dict, "banana", 2);
    add_to_dictionary(dict, "apple", 3);
    add_to_dictionary(dict, "cherry", 4);

    print_dictionary(dict);

    free_dictionary(dict);
    return 0;
}