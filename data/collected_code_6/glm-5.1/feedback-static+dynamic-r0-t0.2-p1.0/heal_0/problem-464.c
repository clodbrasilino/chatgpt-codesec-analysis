#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    char *key;
    int value;
    struct Node *next;
} Node;

typedef struct {
    Node **buckets;
    int size;
} Dictionary;

Dictionary *create_dictionary(int size) {
    Dictionary *dict = malloc(sizeof(Dictionary));
    dict->size = size;
    dict->buckets = calloc(size, sizeof(Node *));
    return dict;
}

void insert_dictionary(Dictionary *dict, char *key, int value) {
    unsigned int index = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        index = (index * 31 + key[i]) % dict->size;
    }
    Node *new_node = malloc(sizeof(Node));
    new_node->key = key;
    new_node->value = value;
    new_node->next = dict->buckets[index];
    dict->buckets[index] = new_node;
}

bool all_values_same(Dictionary *dict) {
    int first_value = 0;
    bool initialized = false;
    for (int i = 0; i < dict->size; i++) {
        Node *current = dict->buckets[i];
        while (current != NULL) {
            if (!initialized) {
                first_value = current->value;
                initialized = true;
            } else if (current->value != first_value) {
                return false;
            }
            current = current->next;
        }
    }
    return true;
}

void free_dictionary(Dictionary *dict) {
    for (int i = 0; i < dict->size; i++) {
        Node *current = dict->buckets[i];
        while (current != NULL) {
            Node *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(dict->buckets);
    free(dict);
}

int main() {
    Dictionary *dict = create_dictionary(10);
    insert_dictionary(dict, "a", 5);
    insert_dictionary(dict, "b", 5);
    insert_dictionary(dict, "c", 5);

    bool result = all_values_same(dict);
    printf("%d\n", result);

    free_dictionary(dict);

    Dictionary *dict2 = create_dictionary(10);
    insert_dictionary(dict2, "x", 10);
    insert_dictionary(dict2, "y", 20);

    result = all_values_same(dict2);
    printf("%d\n", result);

    free_dictionary(dict2);

    return 0;
}