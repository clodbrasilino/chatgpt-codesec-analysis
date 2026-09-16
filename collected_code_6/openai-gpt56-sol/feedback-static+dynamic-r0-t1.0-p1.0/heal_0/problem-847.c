#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int value;
    struct ListNode *next;
} ListNode;

typedef struct {
    const ListNode *list;
} SingletonTuple;

static void free_list(ListNode *head)
{
    while (head != NULL) {
        ListNode *next = head->next;
        free(head);
        head = next;
    }
}

static int copy_list_from_singleton_tuple(const SingletonTuple *tuple, ListNode **copy)
{
    const ListNode *source;
    ListNode **destination;

    if (tuple == NULL || copy == NULL) {
        return -1;
    }

    *copy = NULL;
    source = tuple->list;
    destination = copy;

    while (source != NULL) {
        ListNode *node = malloc(sizeof(*node));

        if (node == NULL) {
            free_list(*copy);
            *copy = NULL;
            return -1;
        }

        node->value = source->value;
        node->next = NULL;
        *destination = node;
        destination = &node->next;
        source = source->next;
    }

    return 0;
}

static int print_list(const ListNode *head)
{
    while (head != NULL) {
        if (printf("%d%s", head->value, head->next != NULL ? " " : "\n") < 0) {
            return -1;
        }
        head = head->next;
    }

    return 0;
}

int main(void)
{
    ListNode third = {3, NULL};
    ListNode second = {2, &third};
    ListNode first = {1, &second};
    SingletonTuple tuple = {&first};
    ListNode *copy = NULL;

    if (copy_list_from_singleton_tuple(&tuple, &copy) != 0) {
        fputs("Failed to copy list\n", stderr);
        return EXIT_FAILURE;
    }

    if (print_list(copy) != 0) {
        free_list(copy);
        fputs("Failed to print list\n", stderr);
        return EXIT_FAILURE;
    }

    free_list(copy);
    return EXIT_SUCCESS;
}