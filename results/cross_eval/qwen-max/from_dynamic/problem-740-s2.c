#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *key;
    char *value;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
} Dictionary;

Dictionary* newDictionary() {
    Dictionary *dict = (Dictionary*) malloc(sizeof(Dictionary));
    dict->head = NULL;
    return dict;
}

void addKeyValuePair(Dictionary *dict, const char *key, const char *value) {
    Node *newNode = (Node*) malloc(sizeof(Node));
    newNode->key = strdup(key);
    newNode->value = strdup(value);
    newNode->next = dict->head;
    dict->head = newNode;
}

void freeDictionary(Dictionary *dict) {
    Node *current = dict->head;
    while (current) {
        Node *temp = current;
        current = current->next;
        free(temp->key);
        free(temp->value);
        free(temp);
    }
    free(dict);
}

void tupleToDict(const char *tuple[], int len, Dictionary *dict) {
    for (int i = 0; i < len - 1; i += 2) {
        addKeyValuePair(dict, tuple[i], tuple[i + 1]);
    }
}

int main() {
    const char *tuple[] = {"key1", "value1", "key2", "value2", "key3", "value3"};
    int len = sizeof(tuple) / sizeof(tuple[0]);

    Dictionary *dict = newDictionary();
    tupleToDict(tuple, len, dict);

    Node *current = dict->head;
    while (current) {
        printf("%s: %s\n", current->key, current->value);
        current = current->next;
    }

    freeDictionary(dict);
    return 0;
}