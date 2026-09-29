#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct Node {
    char key[MAX_SIZE];
    char value[MAX_SIZE];
    struct Node* next;
} Node;

typedef struct Dictionary {
    Node* head;
    int count;
} Dictionary;

Dictionary* createDictionary() {
    Dictionary* dictionary = (Dictionary*)malloc(sizeof(Dictionary));
    if (!dictionary) return NULL; 
    dictionary->head = NULL;
    dictionary->count = 0;
    return dictionary;
}

void insertKeyValuePair(Dictionary* dictionary, const char* key, const char* value) {
    if (!dictionary || !key || !value) return; 
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return; 
    
    strncpy(newNode->key, key, MAX_SIZE - 1);
    strncpy(newNode->value, value, MAX_SIZE - 1);
    newNode->key[MAX_SIZE - 1] = '\0';
    newNode->value[MAX_SIZE - 1] = '\0';
    newNode->next = NULL;
    
    if (dictionary->head == NULL) {
        dictionary->head = newNode;
    } else {
        Node* current = dictionary->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    dictionary->count++;
}

void groupKeyValuePairs(const char** input, int length) {
    if (!input || length <= 0) return; 
    Dictionary* dictionary = createDictionary();
    if (!dictionary) return;

    for (int i = 0; i < length; i+=2) {
        insertKeyValuePair(dictionary, input[i], input[i + 1]);
    }

    Node* current = dictionary->head;
    Node* nextNode = NULL;
    while (current != NULL) {
        printf("%s: %s\n", current->key, current->value);
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
    free(dictionary);
}

int main() {
    const char* input[] = {"key1", "value1", "key2", "value2", "key3", "value3"};
    int length = sizeof(input) / sizeof(input[0]);

    groupKeyValuePairs(input, length);

    return 0;
}