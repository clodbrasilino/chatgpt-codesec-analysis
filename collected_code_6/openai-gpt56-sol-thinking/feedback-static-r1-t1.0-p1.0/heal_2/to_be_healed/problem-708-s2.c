#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    char value;
    struct ListNode *next;
} ListNode;

static void free_list(ListNode *head)
{
    while (head != NULL) {
        ListNode *next = head->next;
        free(head);
        head = next;
    }
}

static int string_to_list(const char *string, ListNode **result)
{
    ListNode *head = NULL;
    ListNode **tail = &head;

    if (string == NULL || result == NULL) {
        return -1;
    }

    *result = NULL;

    while (*string != '\0') {
        ListNode *node = malloc(sizeof(*node));

        if (node == NULL) {
            free_list(head);
            return -1;
        }

        node->value = *string;
        node->next = NULL;

        *tail = node;
        tail = &node->next;
        ++string;
    }

    *result = head;
    return 0;
}

static int print_list(const ListNode *head)
{
    if (fputc('[', stdout) == EOF) {
        return -1;
    }

    while (head != NULL) {
        if (fprintf(stdout, "'%c'%s", head->value,
                    head->next != NULL ? ", " : "") < 0) {
            return -1;
        }

        head = head->next;
    }

    if (fputs("]\n", stdout) == EOF) {
        return -1;
    }

    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    ListNode *list = NULL;
    int status = EXIT_SUCCESS;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (string_to_list(argv[1], &list) != 0) {
        fputs("Failed to convert string to list.\n", stderr);
        return EXIT_FAILURE;
    }

    if (print_list(list) != 0) {
        fputs("Failed to print list.\n", stderr);
        status = EXIT_FAILURE;
    }

    free_list(list);
    return status;
}