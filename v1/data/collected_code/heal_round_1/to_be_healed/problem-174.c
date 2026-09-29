#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char key[100];
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char value[100];
    struct Node* next;
} Node;

typedef struct Dictionary {
    Node* head;
    int count;
} Dictionary;

Dictionary* createDictionary() {
    Dictionary* dictionary = (Dictionary*)malloc(sizeof(Dictionary));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'dictionary' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    dictionary->head = NULL;
    dictionary->count = 0;
    return dictionary;
}

void insertKeyValuePair(Dictionary* dictionary, char* key, char* value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    /* Possible weaknesses found:
     *  Cannot determine that 'key[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     *   Does not check for buffer overflows when copying to destination [MS-banned]  (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy  easily misused).
     */
    strcpy(newNode->key, key);
    /* Possible weaknesses found:
     *  Cannot determine that 'value[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     *   Does not check for buffer overflows when copying to destination [MS-banned]  (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy  easily misused).
     */
    strcpy(newNode->value, value);
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'newNode' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
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
        /* Possible weaknesses found:
         *  Cannot determine that 'input[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        char* key = input[i];
        /* Possible weaknesses found:
         *  Cannot determine that 'input[i+1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        char* value = input[i + 1];
        
        /* Possible weaknesses found:
         *  Cannot determine that 'key' is initialized [premium-bughuntingUninit]
         *  Cannot determine that 'value' is initialized [premium-bughuntingUninit]
         */
        insertKeyValuePair(dictionary, key, value);
        
        i++; // Skip to the next pair
    }
    
    // Print the dictionary
    Node* current = dictionary->head;
    while (current != NULL) {
        printf("%s: %s\n", current->key, current->value);
        /* Possible weaknesses found:
         *  leak of 'current' [CWE-401] [-Wanalyzer-malloc-leak]
         */
        current = current->next;
    }
/* Possible weaknesses found:
 *  leak of '<unknown>' [CWE-401] [-Wanalyzer-malloc-leak]
 *  leak of 'dictionary' [CWE-401] [-Wanalyzer-malloc-leak]
 */
}

int main() {
    char* input[] = {"key1", "value1", "key2", "value2", "key3", "value3"};
    int length = sizeof(input) / sizeof(input[0]);
    
    groupKeyValuePairs(input, length);
    
    return 0;
}