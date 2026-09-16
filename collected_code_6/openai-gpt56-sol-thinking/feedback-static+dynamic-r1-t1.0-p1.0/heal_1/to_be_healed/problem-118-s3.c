#include <stdio.h>
#include <stdlib.h>

typedef struct CharNode {
    char value;
    struct CharNode *next;
} CharNode;

void free_list(CharNode *head)
{
    while (head != NULL) {
        CharNode *next = head->next;
        free(head);
        head = next;
    }
}

int string_to_list(const char *string, CharNode **result)
{
    CharNode *head = NULL;
    CharNode **tail = &head;

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

        node->value = *string;
        node->next = NULL;
        *tail = node;
        tail = &node->next;
        ++string;
    }

    *result = head;
    return 0;
}

int print_list(const CharNode *head)
{
    if (putchar('[') == EOF) {
        return -1;
    }

    while (head != NULL) {
        if (printf("'%c'%s", head->value, head->next != NULL ? ", " : "") < 0) {
            return -1;
        }
        head = head->next;
    }

    if (puts("]") == EOF) {
        return -1;
    }

    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    CharNode *list = NULL;
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