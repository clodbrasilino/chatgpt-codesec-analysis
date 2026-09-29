#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 100003

typedef struct Node {
    long long key;
    long long value;
    struct Node* next;
} Node;

Node* hashTable[HASH_SIZE] = {NULL};

long long get_hash(long long key) {
    return key % HASH_SIZE;
}

long long get_value(long long key) {
    long long hash = get_hash(key);
    Node* current = hashTable[hash];
    while (current != NULL) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    return -1;
}

void insert_value(long long key, long long value) {
    long long hash = get_hash(key);
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        exit(EXIT_FAILURE);
    }
    newNode->key = key;
    newNode->value = value;
    newNode->next = hashTable[hash];
    hashTable[hash] = newNode;
}

long long find_max_sum(long long n) {
    if (n == 0) {
        return 0;
    }
    
    long long cached_value = get_value(n);
    if (cached_value != -1) {
        return cached_value;
    }
    
    long long sum = find_max_sum(n / 2) + find_max_sum(n / 3) + find_max_sum(n / 4) + find_max_sum(n / 5);
    long long max_val = (sum > n) ? sum : n;
    
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
    
    long long result = find_max_sum(n);
    printf("%lld\n", result);
    
    free_hash_table();
    
    return EXIT_SUCCESS;
}