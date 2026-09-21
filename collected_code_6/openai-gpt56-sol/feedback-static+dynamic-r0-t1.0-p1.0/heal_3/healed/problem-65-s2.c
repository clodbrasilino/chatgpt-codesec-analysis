#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

static int append_input(Node **head, Node **tail, const char *line)
{
    const char *cursor = line;

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
                return 1;
            }

            fprintf(stderr, "Invalid input.\n");
            return 0;
        }

        if (errno == ERANGE || parsed < INT64_MIN || parsed > INT64_MAX) {
            fprintf(stderr, "Input value out of range.\n");
            return 0;
        }

        if (!append(head, tail, (int64_t)parsed)) {
            fprintf(stderr, "Memory allocation failed.\n");
            return 0;
        }

        cursor = end;
    }
}

int main(void)
{
    Node *head = NULL;
    Node *tail = NULL;
    char *line = NULL;
    size_t capacity = 0;
    int64_t sum;

    for (;;) {
        size_t length = 0;
        int ch;

        while ((ch = fgetc(stdin)) != EOF) {
            char *new_line;
            size_t new_capacity;

            if (length + 1 >= capacity) {
                if (capacity > SIZE_MAX / 2) {
                    fprintf(stderr, "Input line too long.\n");
                    free(line);
                    free_list(head);
                    return EXIT_FAILURE;
                }

                new_capacity = capacity == 0 ? 256 : capacity * 2;
                new_line = realloc(line, new_capacity);

                if (new_line == NULL) {
                    fprintf(stderr, "Memory allocation failed.\n");
                    free(line);
                    free_list(head);
                    return EXIT_FAILURE;
                }

                line = new_line;
                capacity = new_capacity;
            }

            line[length++] = (char)ch;

            if (ch == '\n') {
                break;
            }
        }

        if (length == 0 && ch == EOF) {
            break;
        }

        line[length] = '\0';

        if (!append_input(&head, &tail, line)) {
            free(line);
            free_list(head);
            return EXIT_FAILURE;
        }

        if (ch == EOF) {
            break;
        }
    }

    free(line);

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