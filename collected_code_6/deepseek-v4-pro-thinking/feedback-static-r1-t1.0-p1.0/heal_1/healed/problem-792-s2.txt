#include <stdio.h>
#include <stddef.h>

typedef struct Node {
    struct Node *next;
} Node;

int count_lists(const Node *head) {
    int count = 0;
    while (head != NULL) {
        ++count;
        head = head->next;
    }
    return count;
}

int main(void) {
    Node node3 = { NULL };
    Node node2 = { &node3 };
    Node node1 = { &node2 };

    printf("%d\n", count_lists(&node1));
    return 0;
}