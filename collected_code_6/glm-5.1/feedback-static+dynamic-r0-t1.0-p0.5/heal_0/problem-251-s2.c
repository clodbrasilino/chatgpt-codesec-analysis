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
    head->data = 1;
    head->next = NULL;

    struct Node *n2 = (struct Node *)malloc(sizeof(struct Node));
    if (n2 == NULL) {
        free(head);
        return 1;
    }
    n2->data = 2;
    n2->next = NULL;
    head->next = n2;

    struct Node *n3 = (struct Node *)malloc(sizeof(struct Node));
    if (n3 == NULL) {
        free(n2);
        free(head);
        return 1;
    }
    n3->data = 3;
    n3->next = NULL;
    n2->next = n3;

    head = insert_before_each(head, 0);

    struct Node *curr = head;
    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");

    free_list(head);

    return 0;
}