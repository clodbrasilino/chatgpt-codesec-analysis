#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *insert_before_each(struct Node *head, int val) {
    if (head == NULL) {
        return NULL;
    }

    struct Node *current = head;
    while (current != NULL) {
        struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
        if (new_node == NULL) {
            struct Node *temp = head;
            while (temp != NULL) {
                struct Node *next = temp->next;
                free(temp);
                temp = next;
            }
            return NULL;
        }
        new_node->data = val;
        new_node->next = current->next;
        current->next = new_node;

        int temp_data = current->data;
        current->data = new_node->data;
        new_node->data = temp_data;

        current = new_node->next;
    }
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
    struct Node *head = (struct Node *)malloc(sizeof(struct Node));
    if (head == NULL) {
        return 1;
    }
    struct Node *n1 = (struct Node *)malloc(sizeof(struct Node));
    if (n1 == NULL) {
        free(head);
        return 1;
    }
    struct Node *n2 = (struct Node *)malloc(sizeof(struct Node));
    if (n2 == NULL) {
        free(head);
        free(n1);
        return 1;
    }

    head->data = 1;
    head->next = n1;
    n1->data = 2;
    n1->next = n2;
    n2->data = 3;
    n2->next = NULL;

    head = insert_before_each(head, 0);

    struct Node *current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");

    free_list(head);

    return 0;
}