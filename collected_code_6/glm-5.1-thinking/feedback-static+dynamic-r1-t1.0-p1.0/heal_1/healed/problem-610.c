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

    struct Node *to_delete = temp->next;
    temp->next = to_delete->next;
    free(to_delete);

    return 0;
}

void print_list(struct Node *head) {
    struct Node *temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
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

    print_list(head);

    remove_kth(&head, 2);
    print_list(head);

    remove_kth(&head, 0);
    print_list(head);

    free_list(head);

    return 0;
}