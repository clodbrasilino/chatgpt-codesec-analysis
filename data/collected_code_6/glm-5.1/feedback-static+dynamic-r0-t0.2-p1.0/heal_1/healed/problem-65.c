#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

int list_sum(struct Node *head) {
    if (head == NULL) {
        return 0;
    }
    return head->data + list_sum(head->next);
}

struct Node *create_node(int data) {
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void free_list(struct Node *head) {
    while (head != NULL) {
        struct Node *temp = head;
        head = head->next;
        free(temp);
    }
}

int main(void) {
    struct Node *head = create_node(1);
    head->next = create_node(2);
    head->next->next = create_node(3);
    head->next->next->next = create_node(4);

    int sum = list_sum(head);
    printf("%d\n", sum);

    free_list(head);
    return 0;
}