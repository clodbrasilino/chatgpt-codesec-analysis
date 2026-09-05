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

void free_list(struct Node *head) {
    struct Node *current = head;
    struct Node *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

int main(void) {
    struct Node *head = malloc(sizeof(struct Node));
    if (head == NULL) {
        return 1;
    }
    head->data = 10;

    head->next = malloc(sizeof(struct Node));
    if (head->next == NULL) {
        free(head);
        return 1;
    }
    head->next->data = 20;

    head->next->next = malloc(sizeof(struct Node));
    if (head->next->next == NULL) {
        free(head->next);
        free(head);
        return 1;
    }
    head->next->next->data = 30;
    head->next->next->next = NULL;

    int total = list_sum(head);
    printf("%d\n", total);

    free_list(head);

    return 0;
}