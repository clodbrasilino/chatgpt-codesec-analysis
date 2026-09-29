#include <stdio.h>
#include <stdlib.h>

typedef struct CharNode {
    unsigned char value;
    struct CharNode *next;
} CharNode;

static void free_list(CharNode *head)
{
    while (head != NULL) {
        CharNode *next = head->next;
        free(head);
        head = next;
    }
}

static int string_to_list(const char *string, CharNode **result)
{
    CharNode *head = NULL;
    CharNode *tail = NULL;

    if (string == NULL || result == NULL) {
        return -1;
    }

    *result = NULL;

    while (*string != '\0') {
        CharNode *node = malloc(sizeof(*node));

        if (node == NULL) {
            free_list(head);
            return -1;
        }

        node->value = (unsigned char)*string;
        node->next = NULL;

        if (head == NULL) {
            head = node;
        } else {
            tail->next = node;
        }

        tail = node;
        string++;
    }

    *result = head;
    return 0;
}

static int print_list(const CharNode *head)
{
    const CharNode *node = head;

    while (node != NULL) {
        if (fputc(node->value, stdout) == EOF) {
            return -1;
        }

        node = node->next;
    }

    if (fputc('\n', stdout) == EOF) {
        return -1;
    }

    return fflush(stdout) == EOF ? -1 : 0;
}

int main(int argc, char **argv)
{
    CharNode *list = NULL;

    if (argc != 2) {
        const char *program = "program";

        if (argc > 0 && argv != NULL && argv[0] != NULL) {
            program = argv[0];
        }

        fprintf(stderr, "Usage: %s <string>\n", program);
        return EXIT_FAILURE;
    }

    if (argv == NULL || argv[1] == NULL) {
        fputs("Invalid string argument.\n", stderr);
        return EXIT_FAILURE;
    }

    if (string_to_list(argv[1], &list) != 0) {
        fputs("Failed to convert the string to a list.\n", stderr);
        return EXIT_FAILURE;
    }

    if (print_list(list) != 0) {
        free_list(list);
        fputs("Failed to write the list.\n", stderr);
        return EXIT_FAILURE;
    }

    free_list(list);
    return EXIT_SUCCESS;
}