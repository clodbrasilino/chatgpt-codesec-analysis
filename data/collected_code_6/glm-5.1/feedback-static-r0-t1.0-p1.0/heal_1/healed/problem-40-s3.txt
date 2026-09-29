#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    int count;
    struct Node *next;
} Node;

Node *create_node(int key) {
    Node *n = (Node *)malloc(sizeof(Node));
    if (!n) {
        exit(EXIT_FAILURE);
    }
    n->key = key;
    n->count = 1;
    n->next = NULL;
    return n;
}

void insert_or_update(Node **head, int key) {
    if (!head) {
        return;
    }
    Node *current = *head;
    Node *prev = NULL;
    while (current) {
        if (current->key == key) {
            current->count++;
            return;
        }
        prev = current;
        current = current->next;
    }
    Node *new_node = create_node(key);
    if (prev) {
        prev->next = new_node;
    } else {
        *head = new_node;
    }
}

void free_list(Node *head) {
    Node *current = head;
    while (current) {
        Node *next = current->next;
        free(current);
        current = next;
    }
}

void find_frequency(int *const *lists, const int *sizes, int num_lists, Node **frequency_map) {
    if (!lists || !sizes || !frequency_map) {
        return;
    }
    *frequency_map = NULL;
    for (int i = 0; i < num_lists; i++) {
        if (!lists[i] && sizes[i] > 0) {
            free_list(*frequency_map);
            *frequency_map = NULL;
            return;
        }
        for (int j = 0; j < sizes[i]; j++) {
            insert_or_update(frequency_map, lists[i][j]);
        }
    }
}

void print_frequency(const Node *head) {
    const Node *current = head;
    while (current) {
        printf("%d: %d\n", current->key, current->count);
        current = current->next;
    }
}

int main(void) {
    int list1[] = {1, 2, 3, 2};
    int list2[] = {2, 4, 1};
    int list3[] = {5, 1, 2};

    int *lists[] = {list1, list2, list3};
    const int sizes[] = {4, 3, 3};
    int num_lists = 3;

    Node *frequency_map = NULL;
    find_frequency(lists, sizes, num_lists, &frequency_map);

    print_frequency(frequency_map);

    free_list(frequency_map);
    frequency_map = NULL;

    return 0;
}