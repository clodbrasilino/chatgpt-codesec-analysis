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
        CharNode *node = malloc(sizeof *node);

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
    for (const CharNode *node = head; node != NULL; node = node->next) {
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

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char *argv[const])
{
    CharNode *list = NULL;

    if (argc != 2) {
        const char *program =
            argc > 0 && argv[0] != NULL ? argv[0] : "program";

        fprintf(stderr, "Usage: %s <string>\n", program);
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