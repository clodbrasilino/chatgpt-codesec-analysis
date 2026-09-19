#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    unsigned long long key;
    unsigned long long value;
    struct Node *next;
} Node;

#define TABLE_SIZE 10007

Node *memo[TABLE_SIZE];

void free_memo(void) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *curr = memo[i];
        while (curr != NULL) {
            Node *temp = curr;
            curr = curr->next;
            free(temp);
        }
        memo[i] = NULL;
    }
}

unsigned long long find_max_sum(unsigned long long n) {
    if (n == 0) {
        return 0;
    }
    if (n < 6) {
        return n;
    }

    unsigned long long hash = n % TABLE_SIZE;
    Node *curr = memo[hash];
    while (curr != NULL) {
        if (curr->key == n) {
            return curr->value;
        }
        curr = curr->next;
    }

    unsigned long long sum = find_max_sum(n / 2) + find_max_sum(n / 3) + find_max_sum(n / 4) + find_max_sum(n / 5);
    unsigned long long result = sum > n ? sum : n;

    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        return result;
    }
    newNode->key = n;
    newNode->value = result;
    newNode->next = memo[hash];
    memo[hash] = newNode;

    return result;
}

int main(void) {
    unsigned long long n;
    if (scanf("%llu", &n) != 1) {
        return 1;
    }

    for (int i = 0; i < TABLE_SIZE; i++) {
        memo[i] = NULL;
    }

    unsigned long long ans = find_max_sum(n);
    printf("%llu\n", ans);

    free_memo();

    return 0;
}