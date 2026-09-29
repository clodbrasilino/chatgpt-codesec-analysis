#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 1000003

typedef struct Node {
    unsigned long long key;
    unsigned long long value;
    struct Node* next;
} Node;

Node* hashTable[HASH_SIZE];

unsigned long long hashFunction(unsigned long long key) {
    return key % HASH_SIZE;
}

void insert(unsigned long long key, unsigned long long value) {
    unsigned long long hashIndex = hashFunction(key);
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        exit(EXIT_FAILURE);
    }
    newNode->key = key;
    newNode->value = value;
    newNode->next = hashTable[hashIndex];
    hashTable[hashIndex] = newNode;
}

int search(unsigned long long key, unsigned long long* value) {
    unsigned long long hashIndex = hashFunction(key);
    Node* current = hashTable[hashIndex];
    while (current != NULL) {
        if (current->key == key) {
            *value = current->value;
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void freeHashTable() {
    for (int i = 0; i < HASH_SIZE; i++) {
        Node* current = hashTable[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
        hashTable[i] = NULL;
    }
}

unsigned long long findMaxSum(unsigned long long n) {
    if (n == 0) {
        return 0;
    }
    
    unsigned long long cachedValue;
    if (search(n, &cachedValue)) {
        return cachedValue;
    }
    
    unsigned long long val1 = findMaxSum(n / 2);
    unsigned long long val2 = findMaxSum(n / 3);
    unsigned long long val3 = findMaxSum(n / 4);
    unsigned long long val4 = findMaxSum(n / 5);

    unsigned long long sum = 0;
    int overflow = 0;

    if (__builtin_add_overflow(val1, val2, &sum) ||
        __builtin_add_overflow(sum, val3, &sum) ||
        __builtin_add_overflow(sum, val4, &sum)) {
        overflow = 1;
    }
    
    /* Possible weaknesses found:
     *  Condition 'overflow' is always true [knownConditionTrueFalse]
     */
    unsigned long long result = (!overflow && sum > n) ? sum : (overflow ? (unsigned long long)-1 : n);
    
    insert(n, result);
    return result;
}

int main(void) {
    long long input_n;
    if (scanf("%lld", &input_n) != 1) {
        return EXIT_FAILURE;
    }
    
    if (input_n < 0) {
        return EXIT_FAILURE;
    }
    
    unsigned long long n = (unsigned long long)input_n;
    
    for (int i = 0; i < HASH_SIZE; i++) {
        hashTable[i] = NULL;
    }
    
    unsigned long long maxSum = findMaxSum(n);
    printf("%llu\n", maxSum);
    
    freeHashTable();
    
    return EXIT_SUCCESS;
}