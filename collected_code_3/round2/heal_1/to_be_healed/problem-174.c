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

Dictionary *createDictionary() {
    Dictionary *dictionary = (Dictionary *) malloc(sizeof(Dictionary));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'dictionary' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    dictionary->key = NULL;
    dictionary->values = NULL;
    return dictionary;
}

Node *createNode(char *value) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'newNode' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

void addValue(Dictionary *dictionary, char *key, char *value) {
    if (dictionary->key == NULL) {
        dictionary->key = key;
    }
    if (strcmp(dictionary->key, key) == 0) {
        Node *newNode = createNode(value);
        newNode->next = dictionary->values;
        dictionary->values = newNode;
    }
}

void printDictionary(Dictionary *dictionary) {
    printf("%s: ", dictionary->key);
    Node *current = dictionary->values;
    while (current != NULL) {
        printf("%s ", current->value);
        current = current->next;
    }
    printf("\n");
}

int main() {
    Dictionary *dictionary = createDictionary();
    addValue(dictionary, "fruit", "apple");
    addValue(dictionary, "fruit", "banana");
    addValue(dictionary, "fruit", "cherry");
    printDictionary(dictionary);
    return 0;
}