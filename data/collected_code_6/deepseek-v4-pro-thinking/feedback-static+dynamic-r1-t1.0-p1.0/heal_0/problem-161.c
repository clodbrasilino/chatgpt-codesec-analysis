#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

bool contains(const Node *head, int value) {
    while (head != NULL) {
        if (head->data == value) {
            return true;
        }
        head = head->next;
    }
    return false;
}

void remove_elements(Node **head, const Node *other) {
    if (head == NULL || *head == NULL || other == NULL) {
        return;
    }

    Node **current = head;
    while (*current != NULL) {
        if (contains(other, (*current)->data)) {
            Node *temp = *current;
            *current = (*current)->next;
            free(temp);
        } else {
            current = &(*current)->next;
        }
    }
}

void free_list(Node *head) {
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp);
    }
}

int main(void) {
    Node *list1 = NULL;
    Node *list2 = NULL;
    int arr1[] = {1, 2, 3, 4, 5, 2};
    int arr2[] = {2, 4};
    size_t len1 = sizeof(arr1) / sizeof(arr1[0]);
    size_t len2 = sizeof(arr2) / sizeof(arr2[0]);

    for (size_t i = len1; i > 0; i--) {
        Node *n = malloc(sizeof(*n));
        if (n == NULL) {
            free_list(list1);
            free_list(list2);
            return EXIT_FAILURE;
        }
        n->data = arr1[i - 1];
        n->next = list1;
        list1 = n;
    }

    for (size_t i = len2; i > 0; i--) {
        Node *n = malloc(sizeof(*n));
        if (n == NULL) {
            free_list(list1);
            free_list(list2);
            return EXIT_FAILURE;
        }
        n->data = arr2[i - 1];
        n->next = list2;
        list2 = n;
    }

    remove_elements(&list1, list2);

    for (const Node *p = list1; p != NULL; p = p->next) {
        printf("%d\n", p->data);
    }

    free_list(list1);
    free_list(list2);
    return EXIT_SUCCESS;
}