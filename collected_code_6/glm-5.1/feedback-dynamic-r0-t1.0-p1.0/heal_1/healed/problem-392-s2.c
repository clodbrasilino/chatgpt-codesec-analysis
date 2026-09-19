#include <stdio.h>
#include <stdlib.h>

struct Node {
    unsigned long long key;
    unsigned long long value;
    struct Node *next;
};

#define TABLE_SIZE 1000003

struct Node *hash_table[TABLE_SIZE];

unsigned long long find_max_sum(unsigned long long n) {
    if (n <= 1) {
        return n;
    }

    unsigned long long hash = n % TABLE_SIZE;
    struct Node *current = hash_table[hash];
    while (current != NULL) {
        if (current->key == n) {
            return current->value;
        }
        current = current->next;
    }

    unsigned long long sum = find_max_sum(n / 2) + find_max_sum(n / 3) + find_max_sum(n / 4) + find_max_sum(n / 5);
    unsigned long long result = (sum > n) ? sum : n;

    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }
    new_node->key = n;
    new_node->value = result;
    new_node->next = hash_table[hash];
    hash_table[hash] = new_node;

    return result;
}

void free_hash_table() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        struct Node *current = hash_table[i];
        while (current != NULL) {
            struct Node *temp = current;
            current = current->next;
            free(temp);
        }
        hash_table[i] = NULL;
    }
}

int main() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hash_table[i] = NULL;
    }

    unsigned long long n;
    if (scanf("%llu", &n) == 1) {
        printf("%llu\n", find_max_sum(n));
    }

    free_hash_table();
    return 0;
}