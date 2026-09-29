#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *create_node(int value)
{
    struct Node *node = malloc(sizeof(struct Node));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->data = value;
    node->next = NULL;
    return node;
}

struct Node *append(struct Node *head, int value)
{
    struct Node *node = create_node(value);
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

struct Node *merge_sorted_lists(struct Node *list1, struct Node *list2)
{
    struct Node dummy;
    struct Node *tail = &dummy;
    dummy.next = NULL;

    while (list1 != NULL && list2 != NULL) {
        if (list1->data <= list2->data) {
            tail->next = list1;
            list1 = list1->next;
        } else {
            tail->next = list2;
            list2 = list2->next;
        }
        tail = tail->next;
    }

    if (list1 != NULL) {
        tail->next = list1;
    } else {
        tail->next = list2;
    }

    return dummy.next;
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
    struct Node *current = head;
    while (current != NULL) {
        struct Node *next = current->next;
        free(current);
        current = next;
    }
}

int main(void)
{
    struct Node *list1 = NULL;
    struct Node *list2 = NULL;
    struct Node *merged = NULL;

    list1 = append(list1, 1);
    list1 = append(list1, 3);
    list1 = append(list1, 5);
    list1 = append(list1, 7);

    list2 = append(list2, 2);
    list2 = append(list2, 4);
    list2 = append(list2, 6);
    list2 = append(list2, 8);

    printf("List 1: ");
    print_list(list1);
    printf("List 2: ");
    print_list(list2);

    merged = merge_sorted_lists(list1, list2);

    printf("Merged: ");
    print_list(merged);

    free_list(merged);

    return EXIT_SUCCESS;
}