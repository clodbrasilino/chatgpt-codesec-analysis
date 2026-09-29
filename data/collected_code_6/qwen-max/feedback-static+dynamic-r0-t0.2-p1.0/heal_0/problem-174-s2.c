#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct Node {
    char *value;
    struct Node *next;
} Node;

typedef struct {
    char *key;
    Node *head;
} DictionaryEntry;

typedef struct {
    DictionaryEntry **entries;
    int capacity;
    int size;
} Dictionary;

Node* create_node(char *value) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->value = strdup(value);
    node->next = NULL;
    return node;
}

Dictionary* create_dictionary(int capacity) {
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    dict->capacity = capacity;
    dict->size = 0;
    dict->entries = (DictionaryEntry **)calloc(capacity, sizeof(DictionaryEntry *));
    return dict;
}

int hash_function(char *key, int capacity) {
    unsigned long hash = 5381;
    int c;
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % capacity;
}

void add_to_dictionary(Dictionary *dict, char *key, char *value) {
    int index = hash_function(key, dict->capacity);
    Node *new_node = create_node(value);

    if (dict->entries[index] == NULL) {
        dict->entries[index] = (DictionaryEntry *)malloc(sizeof(DictionaryEntry));
        dict->entries[index]->key = strdup(key);
        dict->entries[index]->head = new_node;
        dict->size++;
    } else {
        Node *current = dict->entries[index]->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

void print_dictionary(Dictionary *dict) {
    for (int i = 0; i < dict->capacity; i++) {
        if (dict->entries[i] != NULL) {
            printf("%s: ", dict->entries[i]->key);
            Node *current = dict->entries[i]->head;
            while (current != NULL) {
                printf("%s -> ", current->value);
                current = current->next;
            }
            printf("NULL\n");
        }
    }
}

void free_dictionary(Dictionary *dict) {
    for (int i = 0; i < dict->capacity; i++) {
        if (dict->entries[i] != NULL) {
            Node *current = dict->entries[i]->head;
            while (current != NULL) {
                Node *temp = current;
                current = current->next;
                free(temp->value);
                free(temp);
            }
            free(dict->entries[i]->key);
            free(dict->entries[i]);
        }
    }
    free(dict->entries);
    free(dict);
}

int main() {
    KeyValuePair pairs[] = {
        {"a", "1"},
        {"b", "2"},
        {"a", "3"},
        {"b", "4"},
        {"c", "5"}
    };
    int num_pairs = sizeof(pairs) / sizeof(pairs[0]);

    Dictionary *dict = create_dictionary(10);

    for (int i = 0; i < num_pairs; i++) {
        add_to_dictionary(dict, pairs[i].key, pairs[i].value);
    }

    print_dictionary(dict);

    free_dictionary(dict);

    return 0;
}