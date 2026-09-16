#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

static Node *node_create(int data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

static int list_append(Node **head, int data)
{
    Node *node = node_create(data);
    if (node == NULL) {
        return -1;
    }
    if (*head == NULL) {
        *head = node;
        return 0;
    }
    Node *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = node;
    return 0;
}

static void list_free(Node **head)
{
    while (*head != NULL) {
        Node *temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

static int list_remove_kth(Node **head, int k)
{
    if (head == NULL || *head == NULL || k <= 0) {
        return -1;
    }

    Node *current = *head;

    if (k == 1) {
        *head = current->next;
        free(current);
        return 0;
    }

    Node *prev = NULL;
    int index = 1;

    while (current != NULL && index < k) {
        prev = current;
        current = current->next;
        index++;
    }

    if (current == NULL) {
        return -1;
    }

    prev->next = current->next;
    free(current);
    return 0;
}

static void list_print(const Node *head)
{
    const Node *current = head;
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf(" ");
        }
        current = current->next;
    }
    printf("\n");
}

int main(void)
{
    Node *head = NULL;

    if (list_append(&head, 10) != 0 ||
        list_append(&head, 20) != 0 ||
        list_append(&head, 30) != 0 ||
        list_append(&head, 40) != 0) {
        list_free(&head);
        return EXIT_FAILURE;
    }

    list_print(head);

    if (list_remove_kth(&head, 2) != 0) {
        list_free(&head);
        return EXIT_FAILURE;
    }

    list_print(head);

    list_free(&head);
    return EXIT_SUCCESS;
}