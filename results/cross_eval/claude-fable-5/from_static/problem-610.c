#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *create_node(int data)
{
    struct Node *node = malloc(sizeof(struct Node));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->next = NULL;
    return node;
}

struct Node *append(struct Node *head, int data)
{
    struct Node *node = create_node(data);
    if (head == NULL) {
        return node;
    }
    struct Node *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = node;
    return head;
}

struct Node *remove_kth(struct Node *head, size_t k, int *removed)
{
    if (head == NULL || removed == NULL) {
        return head;
    }
    if (k == 0) {
        struct Node *new_head = head->next;
        *removed = 1;
        free(head);
        return new_head;
    }
    struct Node *current = head;
    size_t i = 0;
    while (current->next != NULL && i < k - 1) {
        current = current->next;
        i++;
    }
    if (current->next == NULL) {
        *removed = 0;
        return head;
    }
    struct Node *target = current->next;
    current->next = target->next;
    free(target);
    *removed = 1;
    return head;
}

void print_list(const struct Node *head)
{
    const struct Node *current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void free_list(struct Node *head)
{
    while (head != NULL) {
        struct Node *next = head->next;
        free(head);
        head = next;
    }
}

int main(void)
{
    struct Node *head = NULL;
    int removed = 0;
    size_t k = 2;

    head = append(head, 10);
    head = append(head, 20);
    head = append(head, 30);
    head = append(head, 40);
    head = append(head, 50);

    printf("Original list: ");
    print_list(head);

    head = remove_kth(head, k, &removed);

    if (removed) {
        printf("List after removing element at index %zu: ", k);
        print_list(head);
    } else {
        printf("Index %zu is out of range\n", k);
    }

    free_list(head);
    head = NULL;

    return EXIT_SUCCESS;
}