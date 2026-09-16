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

struct Node *remove_kth(struct Node *head, size_t k)
{
    if (head == NULL) {
        return NULL;
    }
    if (k == 0) {
        struct Node *new_head = head->next;
        free(head);
        return new_head;
    }
    struct Node *current = head;
    size_t i;
    for (i = 0; i < k - 1; i++) {
        if (current->next == NULL) {
            return head;
        }
        current = current->next;
    }
    if (current->next == NULL) {
        return head;
    }
    struct Node *target = current->next;
    current->next = target->next;
    free(target);
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
    int i;

    for (i = 1; i <= 5; i++) {
        head = append(head, i * 10);
    }

    printf("Original list: ");
    print_list(head);

    head = remove_kth(head, 2);
    printf("After removing element at index 2: ");
    print_list(head);

    head = remove_kth(head, 0);
    printf("After removing element at index 0: ");
    print_list(head);

    head = remove_kth(head, 100);
    printf("After attempting to remove index 100: ");
    print_list(head);

    free_list(head);
    head = NULL;

    return EXIT_SUCCESS;
}