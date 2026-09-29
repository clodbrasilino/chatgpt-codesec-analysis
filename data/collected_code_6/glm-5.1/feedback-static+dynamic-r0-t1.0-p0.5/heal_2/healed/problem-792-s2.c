#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    void *data;
    struct Node *next;
} Node;

size_t count_lists(Node **lists, size_t num_lists) {
    if (lists == NULL) {
        return 0;
    }

    size_t count = 0;
    for (size_t i = 0; i < num_lists; i++) {
        if (lists[i] != NULL) {
            count++;
        }
    }
    return count;
}

int main(void) {
    Node a = {(void*)1, NULL};
    Node b = {(void*)2, NULL};
    Node c = {(void*)3, NULL};

    Node *lists[] = {&a, NULL, &b, &c, NULL};
    size_t num_lists = sizeof(lists) / sizeof(lists[0]);

    size_t count = count_lists(lists, num_lists);
    printf("%zu\n", count);

    (void)a.data;
    (void)a.next;
    (void)b.data;
    (void)b.next;
    (void)c.data;
    (void)c.next;

    return 0;
}