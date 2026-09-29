#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *key;
    struct Node *value;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
} Dictionary;

Dictionary* createDictionary() {
    Dictionary *dict = (Dictionary*)malloc(sizeof(Dictionary));
    dict->head = NULL;
    return dict;
}

void addKeyValuePair(Dictionary *dict, const char *key, const char *value) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->key = strdup(key);
    newNode->value = (Node*)malloc(sizeof(Node));
    newNode->value->key = strdup(value);
    newNode->value->value = NULL;
    newNode->value->next = NULL;
    newNode->next = dict->head;
    dict->head = newNode;
}

Dictionary* convertListsToNestedDict(char **keys, char **values, int length) {
    if (length == 0) return NULL;
    
    Dictionary *dict = createDictionary();
    for (int i = 0; i < length; ++i) {
        addKeyValuePair(dict, keys[i], values[i]);
    }
    return dict;
}

void printDictionary(Dictionary *dict, int indent) {
    for (int i = 0; i < indent; ++i) printf("  ");
    Node *current = dict->head;
    while (current != NULL) {
        printf("%s: ", current->key);
        if (current->value->key != NULL) {
            printf("%s\n", current->value->key);
        } else {
            printDictionary((Dictionary*)current->value, indent + 1);
        }
        current = current->next;
    }
}

void freeDictionary(Dictionary *dict) {
    Node *current = dict->head;
    while (current != NULL) {
        Node *temp = current;
        if (temp->value != NULL && temp->value->key == NULL) {
            freeDictionary((Dictionary*)temp->value);
        }
        free(temp->key);
        if (temp->value != NULL) {
            free(temp->value->key);
            free(temp->value);
        }
        current = current->next;
        free(temp);
    }
    free(dict);
}

int main() {
    char *keys[] = {"a", "b", "c"};
    char *values[] = {"1", "2", "3"};
    int length = sizeof(keys) / sizeof(keys[0]);

    Dictionary *nestedDict = convertListsToNestedDict(keys, values, length);
    printDictionary(nestedDict, 0);

    freeDictionary(nestedDict);
    return 0;
}