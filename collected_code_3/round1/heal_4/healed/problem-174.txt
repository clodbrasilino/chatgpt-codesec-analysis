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
    if (size <= 0) {
        return NULL;
    }

    Dictionary *dict = (Dictionary *) malloc(sizeof(Dictionary) * size);
    if (!dict) {
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        dict[i].key = NULL;
        dict[i].values = NULL;
    }

    return dict;
}

Node *createNode(char *value) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    if (!newNode) {
        return NULL;
    }

    newNode->value = strdup(value);
    newNode->next = NULL;

    if (newNode->value == NULL) {
        free(newNode);
        return NULL;
    }

    return newNode;
}

void addValue(Dictionary *dict, int size, char *key, char *value) {
    if (!dict || !key || !value) {
        return;
    }

    for (int i = 0; i < size; i++) {
        if (dict[i].key == NULL) {
            dict[i].key = strdup(key);
            if (dict[i].key == NULL) {
                return;
            }
            dict[i].values = createNode(value);
            if (dict[i].values == NULL) {
                free(dict[i].key);
                return;
            }
            break;
        }

        if (strcmp(dict[i].key, key) == 0) {
            Node *current = dict[i].values;
            if (current != NULL){
                while (current->next != NULL) {
                    current = current->next;
                }
            }
            Node *newNode = createNode(value);
            if (newNode == NULL){
                return;
            }
            if (current == NULL){
                dict[i].values = newNode;
            } else {
                current->next = newNode;
            }
            break;
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

    if (dict) {
        addValue(dict, size, "key1", "value1");
        addValue(dict, size, "key1", "value2");
        addValue(dict, size, "key2", "value3");
        addValue(dict, size, "key2", "value4");
        addValue(dict, size, "key3", "value5");

        printDictionary(dict, size);
    }

    return 0;
}