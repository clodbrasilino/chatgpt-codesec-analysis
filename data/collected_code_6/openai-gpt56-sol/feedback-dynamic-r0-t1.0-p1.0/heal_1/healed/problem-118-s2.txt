#include <errno.h>
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

static char *duplicate_string(const char *string)
{
    size_t length;
    char *copy;

    length = strlen(string) + 1;
    copy = malloc(length);
    if (copy != NULL) {
        memcpy(copy, string, length);
    }

    return copy;
}

static int append_node(ListNode **head, ListNode **tail,
                       const char *start, size_t length)
{
    ListNode *node = malloc(sizeof(*node));

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

    if (input == NULL || delimiter == NULL || delimiter[0] == '\0') {
        errno = EINVAL;
        return NULL;
    }

    start = input;
    position = input;

    for (;;) {
        if (*position == '\0' || strstr(position, delimiter) == position) {
            if (position != start) {
                if (append_node(&head, &tail, start,
                                (size_t)(position - start)) != 0) {
                    int saved_errno = errno != 0 ? errno : ENOMEM;
                    free_list(head);
                    errno = saved_errno;
                    return NULL;
                }
            }

            if (*position == '\0') {
                break;
            }

            position += strlen(delimiter);
            start = position;
        } else {
            position++;
        }
    }

    return head;
}

static int print_list(const ListNode *head)
{
    const ListNode *node;

    for (node = head; node != NULL; node = node->next) {
        if (printf("%s\n", node->value) < 0) {
            return -1;
        }
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

    if (list == NULL) {
        if (errno != 0) {
            perror("string_to_list");
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    if (print_list(list) != 0) {
        free_list(list);
        return EXIT_FAILURE;
    }

    free_list(list);
    return EXIT_SUCCESS;
}