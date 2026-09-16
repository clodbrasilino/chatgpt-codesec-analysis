#define _POSIX_C_SOURCE 200809L

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
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['python', 'programming'], got []
  *  test case 1 failed: expected ['lists', 'tuples', 'strings'], got []
  *  test case 2 failed: expected ['write', 'a', 'program'], got []
  */

static ListNode *string_to_list(const char *input, const char *delimiter)
{
    ListNode *head = NULL;
    ListNode *tail = NULL;
    char *copy;
    char *token;
    char *saveptr = NULL;

    if (input == NULL || delimiter == NULL || delimiter[0] == '\0') {
        errno = EINVAL;
        return NULL;
    }

    copy = strdup(input);
    if (copy == NULL) {
        return NULL;
    }

    token = strtok_r(copy, delimiter, &saveptr);

    while (token != NULL) {
        ListNode *node = malloc(sizeof(*node));

        if (node == NULL) {
            int saved_errno = errno;
            free(copy);
            free_list(head);
            errno = saved_errno != 0 ? saved_errno : ENOMEM;
            return NULL;
        }

        node->value = strdup(token);
        if (node->value == NULL) {
            int saved_errno = errno;
            free(node);
            free(copy);
            free_list(head);
            errno = saved_errno != 0 ? saved_errno : ENOMEM;
            return NULL;
        }

        node->next = NULL;

        if (tail == NULL) {
            head = node;
        } else {
            tail->next = node;
        }

        tail = node;
        token = strtok_r(NULL, delimiter, &saveptr);
    }

    free(copy);
    return head;
}

static int print_list(const ListNode *head)
{
    if (putchar('[') == EOF) {
        return -1;
    }

    for (const ListNode *node = head; node != NULL; node = node->next) {
        if (node != head && fputs(", ", stdout) == EOF) {
            return -1;
        }

        if (putchar('\'') == EOF || fputs(node->value, stdout) == EOF ||
            putchar('\'') == EOF) {
            return -1;
        }
    }

    if (puts("]") == EOF) {
        return -1;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    ListNode *list;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <delimiters>\n",
                argc > 0 ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    errno = 0;
    list = string_to_list(argv[1], argv[2]);

    if (list == NULL && argv[1][0] != '\0') {
        if (errno != 0) {
            perror("string_to_list");
            return EXIT_FAILURE;
        }
    }

    if (print_list(list) != 0) {
        free_list(list);
        return EXIT_FAILURE;
    }

    free_list(list);
    return EXIT_SUCCESS;
}