#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *value;
    struct Node *next;
} Node;

typedef struct {
    char *key;
    Node *values;
} Dictionary;

Dictionary *createDictionary(int size) {
    Dictionary *dict = malloc(sizeof(Dictionary) * size);
    for (int i = 0; i < size; i++) {
        dict[i].key = NULL;
        dict[i].values = NULL;
    }
    return dict;
}

Node *createNode(char *value) {
    Node *newNode = malloc(sizeof(Node));
    newNode->value = strdup(value);
    newNode->next = NULL;
    return newNode;
}

void addValue(Dictionary *dict, int size, char *key, char *value) {
    for (int i = 0; i < size; i++) {
        if (dict[i].key == NULL) {
            dict[i].key = strdup(key);
            dict[i].values = createNode(value);
            return;
        }
        if (strcmp(dict[i].key, key) == 0) {
            Node *current = dict[i].values;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = createNode(value);
            return;
        }
    }
}

void printDictionary(Dictionary *dict, int size) {
    for (int i = 0; i < size; i++) {
        if (dict[i].key != NULL) {
            printf("%s: ", dict[i].key);
            Node *current = dict[i].values;
            while (current != NULL) {
                printf("%s ", current->value);
                current = current->next;
            }
            printf("\n");
        }
    }
}

int main() {
    int size = 5;
    Dictionary *dict = createDictionary(size);

    addValue(dict, size, "key1", "value1");
    addValue(dict, size, "key1", "value2");
    addValue(dict, size, "key2", "value3");
    addValue(dict, size, "key2", "value4");
    addValue(dict, size, "key3", "value5");

    printDictionary(dict, size);

    return 0;
}