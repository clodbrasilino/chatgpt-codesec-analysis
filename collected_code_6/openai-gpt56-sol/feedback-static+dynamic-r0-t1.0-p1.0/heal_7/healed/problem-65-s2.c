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

static int add_checked(int64_t left, int64_t right, int64_t *result)
{
    if ((right > 0 && left > INT64_MAX - right) ||
        (right < 0 && left < INT64_MIN - right)) {
        return 0;
    }

    *result = left + right;
    return 1;
}

static int list_sum(const Node *head, int64_t *sum)
{
    int64_t total = 0;

    while (head != NULL) {
        if (!add_checked(total, head->value, &total)) {
            return 0;
        }

        head = head->next;
    }

    *sum = total;
    return 1;
}

static int append_input(Node **head, Node **tail, const char *line)
{
    const char *cursor = line;

    for (;;) {
        char *end = NULL;
        intmax_t parsed;

        while (*cursor != '\0' &&
               isspace((unsigned char)*cursor) != 0) {
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

        if (*end != '\0' &&
            isspace((unsigned char)*end) == 0) {
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

static int grow_buffer(char **buffer, size_t *capacity, size_t required)
{
    size_t new_capacity;
    char *new_buffer;

    if (buffer == NULL || capacity == NULL || required == 0) {
        return 0;
    }

    if (*capacity >= required) {
        return 1;
    }

    new_capacity = *capacity != 0 ? *capacity : 256;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2) {
            new_capacity = required;
            break;
        }

        new_capacity *= 2;
    }

    new_buffer = realloc(*buffer, new_capacity);
    if (new_buffer == NULL) {
        return 0;
    }

    *buffer = new_buffer;
    *capacity = new_capacity;
    return 1;
}

static int read_line(FILE *stream, char **line, size_t *capacity)
{
    size_t length = 0;

    if (stream == NULL || line == NULL || capacity == NULL) {
        return -1;
    }

    for (;;) {
        int ch;

        if (length > SIZE_MAX - 2) {
            fprintf(stderr, "Input line too long.\n");
            return -1;
        }

        if (!grow_buffer(line, capacity, length + 2)) {
            fprintf(stderr, "Memory allocation failed.\n");
            return -1;
        }

        ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream)) {
                return -1;
            }

            if (length == 0) {
                return 0;
            }

            break;
        }

        (*line)[length++] = (char)(unsigned char)ch;

        if (ch == '\n') {
            break;
        }
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