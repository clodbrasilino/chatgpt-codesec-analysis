#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char* value;
    struct Node* next;
} Node;

typedef struct {
    char* key;
    Node* values;
} KeyValuePair;

KeyValuePair* dictionary[100];
int dictSize = 0;

Node* createNode(char* value) {
    Node* newNode = (Node*)malloc(sizeof(Node));

    if (newNode == NULL) {
        return NULL;
    }

    newNode->value = value;
    newNode->next = NULL;

    return newNode;
}

void addKeyValuePair(char* key, char* value) {
    Node* newNode;

    for (int i = 0; i < dictSize; i++) {
        if (strcmp(dictionary[i]->key, key) == 0) {
            Node* head = dictionary[i]->values;
            while (head->next != NULL) {
                head = head->next;
            }
            newNode = createNode(value);
            if(newNode == NULL){
                return;
            }
            head->next = newNode;
            return;
        }
    }
    
    KeyValuePair* newPair = (KeyValuePair*)malloc(sizeof(KeyValuePair));
    if(newPair == NULL){
        return;
    }
    
    newNode = createNode(value);
    if(newNode == NULL){
        free(newPair);
        return;
    }

    newPair->key = key;
    newPair->values = newNode;
    dictionary[dictSize++] = newPair;
}

void printDictionary() {
    for (int i = 0; i < dictSize; i++) {
        printf("%s: ", dictionary[i]->key);
        Node* head = dictionary[i]->values;
        while (head != NULL) {
            printf("%s ", head->value);
            head = head->next;
        }
        printf("\n");
    }
}

int main() {
    addKeyValuePair("key1", "value1");
    addKeyValuePair("key2", "value2");
    addKeyValuePair("key1", "value3");
    addKeyValuePair("key2", "value4");
    printDictionary();

    return 0;
}