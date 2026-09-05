#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *create_node(int data) {
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

struct Node *remove_kth(struct Node *head, size_t k) {
    if (head == NULL) {
        return NULL;
    }

    if (k == 0) {
        struct Node *new_head = head->next;
        free(head);
        return new_head;
    }

    struct Node *current = head;
    size_t i = 0;

    while (current != NULL && i < k - 1) {
        current = current->next;
        i++;
    }

    if (current == NULL || current->next == NULL) {
        return head;
    }

    struct Node *target = current->next;
    current->next = target->next;
    free(target);

    return head;
}

void free_list(struct Node *head) {
    struct Node *current = head;
    while (current != NULL) {
        struct Node *next = current->next;
        free(current);
        current = next;
    }
}

int main(void) {
    struct Node *head = create_node(1);
    head->next = create_node(2);
    head->next->next = create_node(3);
    head->next->next->next = create_node(4);

    head = remove_kth(head, 2);

    struct Node *temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");

    free_list(head);

    return 0;
}