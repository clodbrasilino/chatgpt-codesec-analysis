#include <stdio.h>
#include <stdlib.h>

typedef struct CharNode {
    char value;
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

    if (result == NULL) {
        return -1;
    }

    *result = NULL;

    if (string == NULL) {
        return -1;
    }

    while (*string != '\0') {
        CharNode *node = malloc(sizeof(*node));

        if (node == NULL) {
            free_list(head);
            return -1;
        }

        node->value = *string;
        node->next = NULL;

        if (tail == NULL) {
            head = node;
        } else {
            tail->next = node;
        }

        tail = node;
        ++string;
    }

    *result = head;
    return 0;
}

static int print_list(const CharNode *head)
{
    const CharNode *node;

    for (node = head; node != NULL; node = node->next) {
        if (fputc((unsigned char)node->value, stdout) == EOF) {
            return -1;
        }
    }

    if (fputc('\n', stdout) == EOF) {
        return -1;
    }

    if (fflush(stdout) == EOF) {
        return -1;
    }

    return 0;
}

int main(int argc, char *const argv[])
{
    CharNode *list = NULL;
    const char *program_name =
        argc > 0 && argv[0] != NULL ? argv[0] : "program";

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", program_name);
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