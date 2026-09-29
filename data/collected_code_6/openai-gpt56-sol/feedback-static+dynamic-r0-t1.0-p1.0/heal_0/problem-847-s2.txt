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

static int copy_list_from_singleton_tuple(const SingletonTuple *tuple,
                                          ListNode **copy_out)
{
    const ListNode *source;
    ListNode **destination;

    if (tuple == NULL || copy_out == NULL) {
        return -1;
    }

    *copy_out = NULL;
    source = tuple->list;
    destination = copy_out;

    while (source != NULL) {
        ListNode *node = malloc(sizeof(*node));

        if (node == NULL) {
            free_list(*copy_out);
            *copy_out = NULL;
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
    const ListNode third = {3, NULL};
    const ListNode second = {2, &third};
    const ListNode first = {1, &second};
    const SingletonTuple tuple = {&first};
    ListNode *copy = NULL;
    int status;

    status = copy_list_from_singleton_tuple(&tuple, &copy);
    if (status != 0) {
        fputs("Failed to copy list\n", stderr);
        return EXIT_FAILURE;
    }

    status = print_list(copy);
    free_list(copy);

    if (status != 0) {
        fputs("Failed to print list\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}