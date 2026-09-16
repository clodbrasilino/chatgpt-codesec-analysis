#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    int count;
    struct Node *next;
} Node;

Node *create_node(int key) {
    Node *n = malloc(sizeof(Node));
    if (!n) return NULL;
    n->key = key;
    n->count = 1;
    n->next = NULL;
    return n;
}

void insert_or_update(Node **head, int key) {
    Node *curr = *head;
    while (curr) {
        if (curr->key == key) {
            curr->count++;
            return;
        }
        curr = curr->next;
    }
    Node *n = create_node(key);
    if (n) {
        n->next = *head;
        *head = n;
    }
}

void free_list(Node *head) {
    Node *curr = head;
    while (curr) {
        Node *next = curr->next;
        free(curr);
        curr = next;
    }
}

Node *find_frequencies(int * const *lists, const int *sizes, int num_lists) {
    Node *head = NULL;
    for (int i = 0; i < num_lists; i++) {
        if (!lists[i] || sizes[i] < 0) continue;
        for (int j = 0; j < sizes[i]; j++) {
            insert_or_update(&head, lists[i][j]);
        }
    }
    return head;
}

int main(void) {
    int a[] = {1, 2, 2, 3};
    int b[] = {3, 4, 5};
    int c[] = {1, 5, 5};
    
    int *lists[] = {a, b, c};
    int sizes[] = {4, 3, 3};
    int num_lists = 3;
    
    Node *freq = find_frequencies(lists, sizes, num_lists);
    
    Node *curr = freq;
    while (curr) {
        printf("%d: %d\n", curr->key, curr->count);
        curr = curr->next;
    }
    
    free_list(freq);
    return 0;
}