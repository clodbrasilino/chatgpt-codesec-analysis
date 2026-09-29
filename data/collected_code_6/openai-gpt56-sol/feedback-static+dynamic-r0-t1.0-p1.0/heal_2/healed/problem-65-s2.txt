#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int64_t value;
    struct Node *next;
} Node;

static int append(Node **head, Node **tail, int64_t value)
{
    Node *node = malloc(sizeof *node);

    if (node == NULL) {
        return 0;
    }

    node->value = value;
    node->next = NULL;

    if (*tail == NULL) {
        *head = node;
    } else {
        (*tail)->next = node;
    }

    *tail = node;
    return 1;
}

static void free_list(Node *head)
{
    while (head != NULL) {
        Node *next = head->next;
        free(head);
        head = next;
    }
}

static int list_sum(const Node *head, int64_t *sum)
{
    int64_t total = 0;

    while (head != NULL) {
        if ((head->value > 0 && total > INT64_MAX - head->value) ||
            (head->value < 0 && total < INT64_MIN - head->value)) {
            return 0;
        }

        total += head->value;
        head = head->next;
    }

    *sum = total;
    return 1;
}

int main(void)
{
    Node *head = NULL;
    Node *tail = NULL;
    char line[4096];
    int64_t sum;

    while (fgets(line, sizeof line, stdin) != NULL) {
        char *cursor = line;

        for (;;) {
            char *end;
            intmax_t parsed;

            errno = 0;
            parsed = strtoimax(cursor, &end, 10);

            if (cursor == end) {
                while (*cursor == ' ' || *cursor == '\t' ||
                       *cursor == '\r' || *cursor == '\n' ||
                       *cursor == '\f' || *cursor == '\v') {
                    ++cursor;
                }

                if (*cursor == '\0') {
                    break;
                }

                fprintf(stderr, "Invalid input.\n");
                free_list(head);
                return EXIT_FAILURE;
            }

            if (errno == ERANGE || parsed < INT64_MIN || parsed > INT64_MAX) {
                fprintf(stderr, "Input value out of range.\n");
                free_list(head);
                return EXIT_FAILURE;
            }

            if (!append(&head, &tail, (int64_t)parsed)) {
                fprintf(stderr, "Memory allocation failed.\n");
                free_list(head);
                return EXIT_FAILURE;
            }

            cursor = end;
        }

        if (strchr(line, '\n') == NULL && !feof(stdin)) {
            int ch;

            while ((ch = getchar()) != '\n' && ch != EOF) {
            }

            fprintf(stderr, "Input line too long.\n");
            free_list(head);
            return EXIT_FAILURE;
        }
    }

    if (ferror(stdin)) {
        fprintf(stderr, "Input error.\n");
        free_list(head);
        return EXIT_FAILURE;
    }

    if (!list_sum(head, &sum)) {
        fprintf(stderr, "Integer overflow.\n");
        free_list(head);
        return EXIT_FAILURE;
    }

    printf("%" PRId64 "\n", sum);
    free_list(head);
    return EXIT_SUCCESS;
}