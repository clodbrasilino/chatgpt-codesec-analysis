#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *key;
    char *value;
    struct Node *next;
} Node;

typedef struct {
    char *key;
    Node *head;
} KeyValuePair;

KeyValuePair* createKeyValuePair(char *key) {
    KeyValuePair *pair = (KeyValuePair*)malloc(sizeof(KeyValuePair));
    pair->key = strdup(key);
    pair->head = NULL;
    return pair;
}

void addValueToKeyValuePair(KeyValuePair *pair, char *value) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->key = strdup(pair->key);
    newNode->value = strdup(value);
    newNode->next = pair->head;
    pair->head = newNode;
}

KeyValuePair* findKeyValuePair(KeyValuePair *pairs[], int size, char *key) {
    for (int i = 0; i < size; i++) {
        if (pairs[i] && strcmp(pairs[i]->key, key) == 0) {
            return pairs[i];
        }
    }
    return NULL;
}

void printKeyValuePair(KeyValuePair *pair) {
    printf("%s: ", pair->key);
    Node *current = pair->head;
    while (current) {
        printf("%s -> ", current->value);
        current = current->next;
    }
    printf("NULL\n");
}

void freeKeyValuePair(KeyValuePair *pair) {
    Node *current = pair->head;
    while (current) {
        Node *temp = current;
        current = current->next;
        free(temp->key);
        free(temp->value);
        free(temp);
    }
    free(pair->key);
    free(pair);
}

int main() {
    KeyValuePair *dictionary[100];
    int dictionarySize = 0;

    char *keys[] = {"a", "b", "a", "c", "b", "a"};
    char *values[] = {"1", "2", "3", "4", "5", "6"};
    int n = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < n; i++) {
        KeyValuePair *pair = findKeyValuePair(dictionary, dictionarySize, keys[i]);
        if (pair) {
            addValueToKeyValuePair(pair, values[i]);
        } else {
            dictionary[dictionarySize] = createKeyValuePair(keys[i]);
            addValueToKeyValuePair(dictionary[dictionarySize], values[i]);
            dictionarySize++;
        }
    }

    for (int i = 0; i < dictionarySize; i++) {
        printKeyValuePair(dictionary[i]);
        freeKeyValuePair(dictionary[i]);
    }

    return 0;
}