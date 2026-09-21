#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode {
    char *value;
    struct ListNode *next;
} ListNode;

static char *duplicate_range(const char *start, size_t length)
{
    char *copy;

    if (start == NULL || length == SIZE_MAX) {
        errno = EINVAL;
        return NULL;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    if (length != 0) {
        memcpy(copy, start, length);
    }

    copy[length] = '\0';
    return copy;
}

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

    if (head == NULL || tail == NULL || start == NULL) {
        errno = EINVAL;
        return -1;
    }

    node = malloc(sizeof(*node));
    if (node == NULL) {
        return -1;
    }

    node->value = duplicate_range(start, length);
    if (node->value == NULL) {
        free(node);
        return -1;
    }

    node->next = NULL;

    if (*tail == NULL) {
        *head = node;
    } else {
        (*tail)->next = node;
    }

    *tail = node;
    return 0;
}

static int string_to_list(const char *input, char delimiter, ListNode **result)
{
    ListNode *head = NULL;
    ListNode *tail = NULL;
    const char *token_start;
    const char *current;

    if (input == NULL || result == NULL || delimiter == '\0') {
        errno = EINVAL;
        return -1;
    }

    *result = NULL;
    token_start = input;

    for (current = input; *current != '\0'; ++current) {
        if (*current == delimiter) {
            size_t length = (size_t)(current - token_start);

            if (append_node(&head, &tail, token_start, length) != 0) {
                int saved_errno = errno;
                free_list(head);
                errno = saved_errno != 0 ? saved_errno : ENOMEM;
                return -1;
            }

            token_start = current + 1;
        }
    }

    if (append_node(&head, &tail, token_start,
                    (size_t)(current - token_start)) != 0) {
        int saved_errno = errno;
        free_list(head);
        errno = saved_errno != 0 ? saved_errno : ENOMEM;
        return -1;
    }

    *result = head;
    return 0;
}

static int print_list(const ListNode *head)
{
    const ListNode *node;

    for (node = head; node != NULL; node = node->next) {
        size_t length = strlen(node->value);

        if (length > 0 && fwrite(node->value, 1, length, stdout) != length) {
            return -1;
        }

        if (fputc('\n', stdout) == EOF) {
            return -1;
        }
    }

    return 0;
}

int main(int argc, char *argv[])
{
    ListNode *list = NULL;

    if (argc != 3 || argv[2][0] == '\0' || argv[2][1] != '\0') {
        fprintf(stderr, "Usage: %s <string> <delimiter>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    if (string_to_list(argv[1], argv[2][0], &list) != 0) {
        perror("string_to_list");
        return EXIT_FAILURE;
    }

    if (print_list(list) != 0) {
        int saved_errno = errno;
        free_list(list);
        errno = saved_errno != 0 ? saved_errno : EIO;
        perror("Failed to write output");
        return EXIT_FAILURE;
    }

    free_list(list);

    if (fflush(stdout) == EOF) {
        perror("Failed to flush output");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}