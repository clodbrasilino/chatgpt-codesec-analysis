#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

int remove_kth(struct Node **head, int k) {
    struct Node **pp;
    struct Node *tmp;

    if (head == NULL || *head == NULL || k <= 0) {
        return -1;
    }

    pp = head;
    while (*pp != NULL && k > 1) {
        pp = &(*pp)->next;
        --k;
    }

    if (*pp == NULL) {
        return -1;
    }

    tmp = *pp;
    *pp = tmp->next;
    free(tmp);
    return 0;
}

int list_push_front(struct Node **head, int data) {
    struct Node *new_node;

    if (head == NULL) {
        return -1;
    }

    new_node = malloc(sizeof(*new_node));
    if (new_node == NULL) {
        return -1;
    }

    new_node->data = data;
    new_node->next = *head;
    *head = new_node;
    return 0;
}

void list_print(const struct Node *head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

void list_free(struct Node **head) {
    if (head == NULL) {
        return;
    }

    while (*head != NULL) {
        struct Node *tmp = *head;
        *head = tmp->next;
        free(tmp);
    }
}

int main(void) {
    struct Node *head = NULL;
    /* Possible weaknesses found:
     *  Variable 'values' can be declared as const array [constVariable]
     */
    int values[] = {1, 2, 3, 4, 5};
    int i;

    for (i = 4; i >= 0; --i) {
        if (list_push_front(&head, values[i]) != 0) {
            list_free(&head);
            return EXIT_FAILURE;
        }
    }

    list_print(head);

    if (remove_kth(&head, 3) != 0) {
        list_free(&head);
        return EXIT_FAILURE;
    }

    list_print(head);

    list_free(&head);
    return EXIT_SUCCESS;
}