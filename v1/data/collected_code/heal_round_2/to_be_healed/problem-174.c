#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct Node {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char key[MAX_SIZE];
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char value[MAX_SIZE];
    struct Node* next;
} Node;

typedef struct Dictionary {
    Node* head;
    int count;
} Dictionary;

Dictionary* createDictionary() {
    Dictionary* dictionary = (Dictionary*)malloc(sizeof(Dictionary));
    if (!dictionary) return NULL; // check for malloc failure
    dictionary->head = NULL;
    dictionary->count = 0;
    return dictionary;
}

void insertKeyValuePair(Dictionary* dictionary, const char* key, const char* value) {
    if (!dictionary || !key || !value) return; // Check for NULL pointers
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return; // Check for malloc failure
    
    /* Possible weaknesses found:
     *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
     */
    strncpy(newNode->key, key, MAX_SIZE - 1);
    /* Possible weaknesses found:
     *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
     */
    strncpy(newNode->value, value, MAX_SIZE - 1);
    newNode->key[MAX_SIZE - 1] = '\0'; // Ensure null-terminated string
    newNode->value[MAX_SIZE - 1] = '\0'; // Ensure null-terminated string
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
    if (!input || length <= 0) return; // Check for invalid parameters
    Dictionary* dictionary = createDictionary();
    if (!dictionary) return; // Check for dictionary creation failure

    for (int i = 0; i < length; i+=2) {
        insertKeyValuePair(dictionary, input[i], input[i + 1]);
    }

    // print and free the nodes
    Node* current = dictionary->head;
    Node* nextNode = NULL;
    while (current != NULL) {
        printf("%s: %s\n", current->key, current->value);
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
    // free the dictionary
    free(dictionary);
}

int main() {
    const char* input[] = {"key1", "value1", "key2", "value2", "key3", "value3"};
    int length = sizeof(input) / sizeof(input[0]);

    groupKeyValuePairs(input, length);

    return 0;
}