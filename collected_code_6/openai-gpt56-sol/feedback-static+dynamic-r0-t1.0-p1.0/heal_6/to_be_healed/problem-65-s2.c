#include <ctype.h>
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

static int append_input(Node **head, Node **tail, const char *line)
{
    const char *cursor = line;

    for (;;) {
        char *end;
        intmax_t parsed;

        while (*cursor != '\0' && isspace((unsigned char)*cursor)) {
            ++cursor;
        }

        if (*cursor == '\0') {
            return 1;
        }

        errno = 0;
        parsed = strtoimax(cursor, &end, 10);

        if (end == cursor) {
            fprintf(stderr, "Invalid input.\n");
            return 0;
        }

        if (errno == ERANGE || parsed < INT64_MIN || parsed > INT64_MAX) {
            fprintf(stderr, "Input value out of range.\n");
            return 0;
        }

        if (*end != '\0' && !isspace((unsigned char)*end)) {
            fprintf(stderr, "Invalid input.\n");
            return 0;
        }

        if (!append(head, tail, (int64_t)parsed)) {
            fprintf(stderr, "Memory allocation failed.\n");
            return 0;
        }

        cursor = end;
    }
}

static int read_line(FILE *stream, char **line, size_t *capacity)
{
    size_t length = 0;
    int ch = EOF;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stream);

        if (ch == EOF) {
            break;
        }

        if (length == SIZE_MAX - 1) {
            fprintf(stderr, "Input line too long.\n");
            return -1;
        }

        if (length + 1 >= *capacity) {
            size_t required = length + 2;
            size_t new_capacity;
            char *new_line;

            if (*capacity == 0) {
                new_capacity = 256;
            } else if (*capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = *capacity * 2;
            }

            if (new_capacity < required) {
                fprintf(stderr, "Input line too long.\n");
                return -1;
            }

            new_line = realloc(*line, new_capacity);
            if (new_line == NULL) {
                fprintf(stderr, "Memory allocation failed.\n");
                return -1;
            }

            *line = new_line;
            *capacity = new_capacity;
        }

        (*line)[length++] = (char)ch;

        if (ch == '\n') {
            break;
        }
    }

    if (length == 0 && ch == EOF) {
        return ferror(stream) ? -1 : 0;
    }

    (*line)[length] = '\0';
    return 1;
}

int main(void)
{
    Node *head = NULL;
    Node *tail = NULL;
    char *line = NULL;
    size_t capacity = 0;
    int64_t sum;

    for (;;) {
        int status = read_line(stdin, &line, &capacity);

        if (status == 0) {
            break;
        }

        if (status < 0) {
            if (ferror(stdin)) {
                fprintf(stderr, "Input error.\n");
            }

            free(line);
            free_list(head);
            return EXIT_FAILURE;
        }

        if (!append_input(&head, &tail, line)) {
            free(line);
            free_list(head);
            return EXIT_FAILURE;
        }
    }

    free(line);

    if (!list_sum(head, &sum)) {
        fprintf(stderr, "Integer overflow.\n");
        free_list(head);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", sum) < 0) {
        fprintf(stderr, "Output error.\n");
        free_list(head);
        return EXIT_FAILURE;
    }

    free_list(head);
    return EXIT_SUCCESS;
}