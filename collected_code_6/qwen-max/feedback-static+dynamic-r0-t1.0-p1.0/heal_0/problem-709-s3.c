#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    int value;
} Tuple;

typedef struct Node {
    char *key;
    struct Node *next;
} Node;

int countUniqueKeysForValue(Tuple *tuples, int size, int value) {
    if (!tuples || size <= 0) return 0;
    
    Node *hashTable[1000] = {NULL};
    int uniqueKeysCount = 0;

    for (int i = 0; i < size; ++i) {
        if (tuples[i].value == value) {
            char *key = tuples[i].key;
            int index = strlen(key) % 1000;

            Node *current = hashTable[index];
            Node *prev = NULL;
            while (current) {
                if (strcmp(current->key, key) == 0) break;
                prev = current;
                current = current->next;
            }

            if (!current) {
                Node *newNode = (Node *)malloc(sizeof(Node));
                newNode->key = strdup(key);
                newNode->next = NULL;
                if (prev) {
                    prev->next = newNode;
                } else {
                    hashTable[index] = newNode;
                }
                ++uniqueKeysCount;
            }
        }
    }

    for (int i = 0; i < 1000; ++i) {
        Node *current = hashTable[i];
        while (current) {
            Node *toDelete = current;
            current = current->next;
            free(toDelete->key);
            free(toDelete);
        }
    }

    return uniqueKeysCount;
}

int main() {
    Tuple tuples[] = {
        {"key1", 1},
        {"key2", 1},
        {"key1", 2},
        {"key3", 1},
        {"key4", 2},
        {"key5", 1}
    };
    int size = sizeof(tuples) / sizeof(tuples[0]);
    int value = 1;
    int result = countUniqueKeysForValue(tuples, size, value);
    printf("Unique keys for value %d: %d\n", value, result);
    return 0;
}