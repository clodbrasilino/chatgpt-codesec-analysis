#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 100003

typedef struct Node {
    unsigned long long key;
    unsigned long long value;
    struct Node* next;
} Node;

Node* hashTable[HASH_SIZE] = {NULL};

unsigned long long get_hash(unsigned long long key) {
    return key % HASH_SIZE;
}

unsigned long long get_value(unsigned long long key) {
    unsigned long long hash = get_hash(key);
    Node* current = hashTable[hash];
    while (current != NULL) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    return (unsigned long long)-1;
}

void insert_value(unsigned long long key, unsigned long long value) {
    unsigned long long hash = get_hash(key);
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        exit(EXIT_FAILURE);
    }
    newNode->key = key;
    newNode->value = value;
    newNode->next = hashTable[hash];
    hashTable[hash] = newNode;
}

unsigned long long find_max_sum(unsigned long long n) {
    if (n == 0) {
        return 0;
    }
    
    unsigned long long cached_value = get_value(n);
    if (cached_value != (unsigned long long)-1) {
        return cached_value;
    }
    
    unsigned long long a = find_max_sum(n / 2);
    unsigned long long b = find_max_sum(n / 3);
    unsigned long long c = find_max_sum(n / 4);
    unsigned long long d = find_max_sum(n / 5);
    
    unsigned long long sum = a + b + c + d;
    unsigned long long max_val = (sum > n) ? sum : n;
    
    insert_value(n, max_val);
    
    return max_val;
}

void free_hash_table() {
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

int main() {
    long long n;
    if (scanf("%lld", &n) != 1) {
        return EXIT_FAILURE;
    }
    
    if (n < 0) {
        return EXIT_FAILURE;
    }
    
    unsigned long long result = find_max_sum((unsigned long long)n);
    printf("%llu\n", result);
    
    free_hash_table();
    
    return EXIT_SUCCESS;
}