#include <stdio.h>
#include <stddef.h>

struct Node {
    int data;
    struct Node *next;
};

int list_sum(const struct Node *head) {
    if (head == NULL) {
        return 0;
    }
    return head->data + list_sum(head->next);
}

int main(void) {
    struct Node node3 = {30, NULL};
    struct Node node2 = {20, &node3};
    struct Node node1 = {10, &node2};

    printf("%d\n", list_sum(&node1));

    return 0;
}