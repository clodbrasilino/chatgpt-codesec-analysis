#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    unsigned char value;
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

static int string_to_list(const char *string, ListNode **out_head)
{
    ListNode *head = NULL;
    ListNode **tail = &head;

    if (string == NULL || out_head == NULL) {
        return 0;
    }

    while (*string != '\0') {
        ListNode *node = malloc(sizeof(*node));

        if (node == NULL) {
            free_list(head);
            return 0;
        }

        node->value = (unsigned char)*string;
        node->next = NULL;
        *tail = node;
        tail = &node->next;
        ++string;
    }

    *out_head = head;
    return 1;
}

static int print_list(const ListNode *head)
{
    if (fputc('[', stdout) == EOF) {
        return 0;
    }

    while (head != NULL) {
        if (fprintf(stdout, "%u", (unsigned int)head->value) < 0) {
            return 0;
        }

        if (head->next != NULL && fputs(", ", stdout) == EOF) {
            return 0;
        }

        head = head->next;
    }

    return fputs("]\n", stdout) != EOF;
}

int main(int argc, char **argv)
{
    ListNode *list = NULL;
    int status = EXIT_SUCCESS;

    if (argc != 2) {
        const char *program_name = "program";

        if (argc > 0 && argv != NULL && argv[0] != NULL) {
            program_name = argv[0];
        }

        if (fprintf(stderr, "Usage: %s <string>\n", program_name) < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    if (argv == NULL || argv[1] == NULL ||
        !string_to_list(argv[1], &list)) {
        fputs("Failed to convert the string to a list.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!print_list(list)) {
        fputs("Failed to write the list.\n", stderr);
        status = EXIT_FAILURE;
    }

    free_list(list);
    return status;
}