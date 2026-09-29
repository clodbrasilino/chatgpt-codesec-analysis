#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

int remove_kth(struct Node **head, int k) {
    if (head == NULL || *head == NULL || k < 0) {
        return -1;
    }

    struct Node *temp = *head;

    if (k == 0) {
        *head = temp->next;
        free(temp);
        return 0;
    }

    for (int i = 0; i < k - 1; i++) {
        if (temp->next == NULL) {
            return -1;
        }
        temp = temp->next;
    }

    if (temp->next == NULL) {
        return -1;
    }

    struct Node *node_to_remove = temp->next;
    temp->next = node_to_remove->next;
    free(node_to_remove);

    return 0;
}

struct Node *create_node(int data) {
    struct Node *new_node = malloc(sizeof(struct Node));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void free_list(struct Node *head) {
    struct Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void print_list(struct Node *head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main(void) {
    struct Node *head = create_node(10);
    head->next = create_node(20);
    head->next->next = create_node(30);
    head->next->next->next = create_node(40);

    print_list(head);

    remove_kth(&head, 2);
    print_list(head);

    remove_kth(&head, 0);
    print_list(head);

    if (remove_kth(&head, 10) != 0) {
        printf("Invalid index handled correctly.\n");
    }

    free_list(head);
    return 0;
}