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

static int append_node(ListNode **head, ListNode **tail,
                       const char *start, size_t length)
{
    ListNode *node;

    if (length == SIZE_MAX) {
        errno = ENOMEM;
        return -1;
    }

    node = malloc(sizeof(*node));
    if (node == NULL) {
        return -1;
    }

    node->value = malloc(length + 1);
    if (node->value == NULL) {
        free(node);
        return -1;
    }

    memcpy(node->value, start, length);
    node->value[length] = '\0';
    node->next = NULL;

    if (*tail == NULL) {
        *head = node;
    } else {
        (*tail)->next = node;
    }

    *tail = node;
    return 0;
}

static ListNode *string_to_list(const char *input, const char *delimiter)
{
    ListNode *head = NULL;
    ListNode *tail = NULL;
    const char *start;
    const char *position;
    size_t delimiter_length;

    if (input == NULL || delimiter == NULL || delimiter[0] == '\0') {
        errno = EINVAL;
        return NULL;
    }

    delimiter_length = strlen(delimiter);
    start = input;

    while ((position = strstr(start, delimiter)) != NULL) {
        if (position != start &&
            append_node(&head, &tail, start,
                        (size_t)(position - start)) != 0) {
            int saved_errno = errno != 0 ? errno : ENOMEM;
            free_list(head);
            errno = saved_errno;
            return NULL;
        }

        start = position + delimiter_length;
    }

    if (*start != '\0' &&
        append_node(&head, &tail, start, strlen(start)) != 0) {
        int saved_errno = errno != 0 ? errno : ENOMEM;
        free_list(head);
        errno = saved_errno;
        return NULL;
    }

    errno = 0;
    return head;
}

static int print_list(const ListNode *head)
{
    const ListNode *node;
    int first = 1;

    if (fputc('[', stdout) == EOF) {
        return -1;
    }

    for (node = head; node != NULL; node = node->next) {
        const unsigned char *p;

        if (!first && fputs(", ", stdout) == EOF) {
            return -1;
        }

        if (fputc('\'', stdout) == EOF) {
            return -1;
        }

        for (p = (const unsigned char *)node->value; *p != '\0'; ++p) {
            if (*p == '\'' || *p == '\\') {
                if (fputc('\\', stdout) == EOF) {
                    return -1;
                }
            }

            if (fputc(*p, stdout) == EOF) {
                return -1;
            }
        }

        if (fputc('\'', stdout) == EOF) {
            return -1;
        }

        first = 0;
    }

    if (fputs("]\n", stdout) == EOF) {
        return -1;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    ListNode *list;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <delimiter>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    list = string_to_list(argv[1], argv[2]);

    if (list == NULL && errno != 0) {
        perror("string_to_list");
        return EXIT_FAILURE;
    }

    if (print_list(list) != 0) {
        int saved_errno = errno;
        free_list(list);
        errno = saved_errno;
        perror("print_list");
        return EXIT_FAILURE;
    }

    free_list(list);
    return EXIT_SUCCESS;
}