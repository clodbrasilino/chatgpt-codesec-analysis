#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char key[100];
    char value[100];
    struct Node* next;
} Node;

typedef struct Dictionary {
    Node* head;
    int count;
} Dictionary;

Dictionary* createDictionary() {
    Dictionary* dictionary = (Dictionary*)malloc(sizeof(Dictionary));
    dictionary->head = NULL;
    dictionary->count = 0;
    return dictionary;
}

void insertKeyValuePair(Dictionary* dictionary, char* key, char* value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->key, key);
    strcpy(newNode->value, value);
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

void groupKeyValuePairs(char** input, int length) {
    Dictionary* dictionary = createDictionary();
    
    for (int i = 0; i < length; i++) {
        char* key = input[i];
        char* value = input[i + 1];
        
        insertKeyValuePair(dictionary, key, value);
        
        i++; // Skip to the next pair
    }
    
    // Print the dictionary
    Node* current = dictionary->head;
    while (current != NULL) {
        printf("%s: %s\n", current->key, current->value);
        current = current->next;
    }
}

int main() {
    char* input[] = {"key1", "value1", "key2", "value2", "key3", "value3"};
    int length = sizeof(input) / sizeof(input[0]);
    
    groupKeyValuePairs(input, length);
    
    return 0;
}