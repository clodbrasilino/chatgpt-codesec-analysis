#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode {
    char *value;
    struct ListNode *next;
} ListNode;

static void free_list(ListNode *head)
{
    while (head != NULL) {
        ListNode *next = head->next;
        free(head->value);
        free(head);
        head = next;
    }
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['lists', 'tuples', 'strings'], got <no output>
  *  test case 0 failed: expected ['python', 'programming'], got <no output>
  *  test case 2 failed: expected ['write', 'a', 'program'], got <no output>
  */

static ListNode *string_to_list(const char *input, const char *delimiter)
{
    ListNode *head = NULL;
    ListNode *tail = NULL;
    const char *start;
    size_t delimiter_length;

    if (input == NULL || delimiter == NULL || *delimiter == '\0') {
        errno = EINVAL;
        return NULL;
    }

    delimiter_length = strlen(delimiter);
    start = input;

    for (;;) {
        const char *end = strstr(start, delimiter);
        size_t length = end != NULL ? (size_t)(end - start) : strlen(start);

        if (length > 0) {
            ListNode *node = malloc(sizeof(*node));

            if (node == NULL) {
                free_list(head);
                errno = ENOMEM;
                return NULL;
            }

            node->value = malloc(length + 1);
            if (node->value == NULL) {
                free(node);
                free_list(head);
                errno = ENOMEM;
                return NULL;
            }

            memcpy(node->value, start, length);
            node->value[length] = '\0';
            node->next = NULL;

            if (tail == NULL) {
                head = node;
            } else {
                tail->next = node;
            }

            tail = node;
        }

        if (end == NULL) {
            break;
        }

        start = end + delimiter_length;
    }

    errno = 0;
    return head;
}

static int print_list(const ListNode *head)
{
    int first = 1;

    if (putchar('[') == EOF) {
        return -1;
    }

    for (const ListNode *node = head; node != NULL; node = node->next) {
        const unsigned char *p = (const unsigned char *)node->value;

        if (!first && fputs(", ", stdout) == EOF) {
            return -1;
        }

        if (putchar('\'') == EOF) {
            return -1;
        }

        while (*p != '\0') {
            if ((*p == '\\' || *p == '\'') && putchar('\\') == EOF) {
                return -1;
            }

            if (putchar((int)*p) == EOF) {
                return -1;
            }

            ++p;
        }

        if (putchar('\'') == EOF) {
            return -1;
        }

        first = 0;
    }

    return puts("]") == EOF ? -1 : 0;
}

static int process_input(const char *input, const char *delimiter)
{
    ListNode *list;

    errno = 0;
    list = string_to_list(input, delimiter);

    if (list == NULL && errno != 0) {
        perror("string_to_list");
        return -1;
    }

    if (print_list(list) != 0) {
        free_list(list);
        fputs("Failed to write output\n", stderr);
        return -1;
    }

    free_list(list);
    return 0;
}

int main(int argc, char **argv)
{
    int status;

    if (argc == 1) {
        char *line = NULL;
        size_t capacity = 0;
        ssize_t length = getline(&line, &capacity, stdin);

        if (length < 0) {
            free(line);

            if (ferror(stdin)) {
                perror("getline");
                return EXIT_FAILURE;
            }

            return EXIT_SUCCESS;
        }

        while (length > 0 &&
               (line[length - 1] == '\n' || line[length - 1] == '\r')) {
            line[--length] = '\0';
        }

        status = process_input(line, " ");
        free(line);
    } else if (argc == 2) {
        status = process_input(argv[1], " ");
    } else if (argc == 3) {
        status = process_input(argv[1], argv[2]);
    } else {
        fprintf(stderr, "Usage: %s [string [delimiter]]\n",
                argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    if (status != 0) {
        return EXIT_FAILURE;
    }

    if (fflush(stdout) == EOF) {
        fputs("Failed to flush output\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}