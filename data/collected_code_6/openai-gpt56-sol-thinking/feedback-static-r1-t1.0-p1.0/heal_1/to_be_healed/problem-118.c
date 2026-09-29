#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    char value;
    struct ListNode *next;
} ListNode;

void free_list(ListNode *head)
{
    while (head != NULL) {
        ListNode *next = head->next;
        free(head);
        head = next;
    }
}

int string_to_list(const char *string, ListNode **out_head)
{
    ListNode **tail;

    if (string == NULL || out_head == NULL) {
        return 0;
    }

    *out_head = NULL;
    tail = out_head;

    while (*string != '\0') {
        ListNode *node = malloc(sizeof(*node));

        if (node == NULL) {
            free_list(*out_head);
            *out_head = NULL;
            return 0;
        }

        node->value = *string;
        node->next = NULL;
        *tail = node;
        tail = &node->next;
        ++string;
    }

    return 1;
}

int print_list(const ListNode *head)
{
    if (fputc('[', stdout) == EOF) {
        return 0;
    }

    while (head != NULL) {
        if (fprintf(stdout, "%u", (unsigned int)(unsigned char)head->value) < 0) {
            return 0;
        }

        if (head->next != NULL && fputs(", ", stdout) == EOF) {
            return 0;
        }

        head = head->next;
    }

    return fputs("]\n", stdout) != EOF;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    ListNode *list = NULL;
    int result = EXIT_SUCCESS;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!string_to_list(argv[1], &list)) {
        fputs("Failed to convert the string to a list.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!print_list(list)) {
        fputs("Failed to write the list.\n", stderr);
        result = EXIT_FAILURE;
    }

    free_list(list);
    return result;
}