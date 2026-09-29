#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 100

typedef struct Node {
    char *data;
    struct Node *hashNext;
    struct Node *next;
} Node;

typedef struct Hash {
    int count;
    struct Node **items;
} Hash;

Hash *createHashTable(int size) {
    Hash *hashTable = calloc(1, sizeof(Hash));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'hashTable' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    hashTable->count = size;
    hashTable->items = calloc(size, sizeof(Node *));
    
    return hashTable;
}

unsigned long hashFunction(char *str) {
    unsigned long i = 0;
    for(int j = 0; str[j]; j++)
        i += str[j];
    return i;
}

Node *createNode(char *data) {
    Node *newNode = calloc(1, sizeof(Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'newNode' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    newNode->data = data;
    newNode->hashNext = NULL;
    newNode->next = NULL;

    return newNode;
}

void hashAdd(Hash *hashTable, char *data) {
    unsigned long hashIndex = hashFunction(data);
    Node *newNode = createNode(data);
    newNode->hashNext = hashTable->items[hashIndex];
    hashTable->items[hashIndex] = newNode;
}

int hashSearch(Hash *hashTable, char *data) {
    unsigned long hashIndex = hashFunction(data);
    Node *node = hashTable->items[hashIndex];  

    while(node != NULL) {
        if(strcmp(node->data, data) == 0) return 1;
        node = node->hashNext;
    }
    return 0;
}

void removeDuplicates(char *str) {
    Hash *hashTable = createHashTable(MAX_CHAR);
    Node *start = NULL;
    Node *end = NULL;

    char *word = strtok(str, " ");
    while(word) {
        if(!hashSearch(hashTable, word)) {
            Node *newNode = createNode(word);
            hashAdd(hashTable, word);
            if(start == NULL) {
                start = newNode;
                end = start;
            } else {
                end->next = newNode;
                end = newNode;
            }
        }
        word = strtok(NULL, " ");
    }

    Node *temp = start;
    while(temp) {
        printf("%s ", temp->data);
        temp = temp->next;
    }

    printf("\n");
/* Possible weaknesses found:
 *  leak of 'hashTable' [CWE-401] [-Wanalyzer-malloc-leak]
 *  leak of 'end' [CWE-401] [-Wanalyzer-malloc-leak]
 *  leak of '<unknown>' [CWE-401] [-Wanalyzer-malloc-leak]
 *  leak of 'start' [CWE-401] [-Wanalyzer-malloc-leak]
 */
}

int main() {
    char str[MAX_CHAR] = "Hello world. This is a C program. Hello world. This is a C program.";
    removeDuplicates(str);

    return 0;
}