#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int value;
    struct ListNode *next;
} ListNode;

static void free_list(ListNode *head)
{
    while (head != NULL) {
        ListNode *next = head->next;
        free(head);
        head = next;
    }
}

static bool append_item(ListNode **head, ListNode **tail, int value)
{
    if (head == NULL || tail == NULL) {
        return false;
    }

    ListNode *node = malloc(sizeof(*node));
    if (node == NULL) {
        return false;
    }

    node->value = value;
    node->next = NULL;

    if (*tail == NULL) {
        *head = node;
    } else {
        (*tail)->next = node;
    }

    *tail = node;
    return true;
}

static bool select_nth_item(const ListNode *head, size_t position, int *result)
{
    size_t index = 1;

    if (position == 0 || result == NULL) {
        return false;
    }

    while (head != NULL && index < position) {
        head = head->next;
        ++index;
    }

    if (head == NULL) {
        return false;
    }

    *result = head->value;
    return true;
}

static bool parse_position(const char *text, size_t *position)
{
    char *end = NULL;
    unsigned long long value;

    if (text == NULL || position == NULL ||
        text[0] < '0' || text[0] > '9') {
        return false;
    }

    errno = 0;
    value = strtoull(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        value == 0 || value > SIZE_MAX) {
        return false;
    }

    *position = (size_t)value;
    return true;
}

static bool parse_item(const char *text, int *item)
{
    const char *digits;
    char *end = NULL;
    long value;

    if (text == NULL || item == NULL || text[0] == '\0') {
        return false;
    }

    digits = text;
    if (*digits == '+' || *digits == '-') {
        ++digits;
    }

    if (*digits < '0' || *digits > '9') {
        return false;
    }

    errno = 0;
    value = strtol(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        value < INT_MIN || value > INT_MAX) {
        return false;
    }

    *item = (int)value;
    return true;
}

int main(int argc, const char *const argv[])
{
    ListNode *head = NULL;
    ListNode *tail = NULL;
    size_t position;
    int result;

    if (argc < 3) {
        const char *program = argc > 0 && argv[0] != NULL
                                ? argv[0]
                                : "program";
        fprintf(stderr, "Usage: %s position item [item ...]\n", program);
        return EXIT_FAILURE;
    }

    if (!parse_position(argv[1], &position)) {
        fprintf(stderr, "Invalid position: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    for (int i = 2; i < argc; ++i) {
        int item;

        if (!parse_item(argv[i], &item)) {
            fprintf(stderr, "Invalid item: %s\n", argv[i]);
            free_list(head);
            return EXIT_FAILURE;
        }

        if (!append_item(&head, &tail, item)) {
            fprintf(stderr, "Unable to allocate list item\n");
            free_list(head);
            return EXIT_FAILURE;
        }
    }

    if (!select_nth_item(head, position, &result)) {
        fprintf(stderr, "Position is outside the list\n");
        free_list(head);
        return EXIT_FAILURE;
    }

    printf("%d\n", result);
    free_list(head);
    return EXIT_SUCCESS;
}