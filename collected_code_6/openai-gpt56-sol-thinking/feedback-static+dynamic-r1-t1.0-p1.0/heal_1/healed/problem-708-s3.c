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

static int string_to_list(const char *string, CharNode **out_list)
{
    CharNode *head = NULL;
    CharNode *tail = NULL;

    if (string == NULL || out_list == NULL) {
        return -1;
    }

    *out_list = NULL;

    while (*string != '\0') {
        CharNode *node = malloc(sizeof *node);

        if (node == NULL) {
            free_list(head);
            return -1;
        }

        node->value = *string++;
        node->next = NULL;

        if (tail == NULL) {
            head = node;
        } else {
            tail->next = node;
        }

        tail = node;
    }

    *out_list = head;
    return 0;
}

static int print_list(const CharNode *head)
{
    if (fputc('[', stdout) == EOF) {
        return -1;
    }

    while (head != NULL) {
        if (fprintf(stdout, "'%c'", head->value) < 0) {
            return -1;
        }

        if (head->next != NULL && fputs(", ", stdout) == EOF) {
            return -1;
        }

        head = head->next;
    }

    return fputs("]\n", stdout) == EOF ? -1 : 0;
}

int main(int argc, char *const argv[])
{
    CharNode *list = NULL;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (string_to_list(argv[1], &list) != 0) {
        fputs("Failed to create list.\n", stderr);
        return EXIT_FAILURE;
    }

    if (print_list(list) != 0) {
        fputs("Failed to print list.\n", stderr);
        free_list(list);
        return EXIT_FAILURE;
    }

    free_list(list);
    return EXIT_SUCCESS;
}