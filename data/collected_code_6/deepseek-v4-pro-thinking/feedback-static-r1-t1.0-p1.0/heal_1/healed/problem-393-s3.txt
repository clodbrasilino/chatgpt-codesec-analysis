#include <stdio.h>
#include <stddef.h>

typedef struct Node {
    struct Node *next;
} Node;

static size_t list_length(const Node *head) {
    size_t length = 0;
    while (head != NULL) {
        length++;
        head = head->next;
    }
    return length;
}

Node *find_max_length_list(Node * const lists[], size_t count) {
    if (lists == NULL || count == 0) {
        return NULL;
    }

    Node *max_list = lists[0];
    size_t max_length = list_length(max_list);
    size_t i;

    for (i = 1; i < count; i++) {
        size_t current_length = list_length(lists[i]);
        if (current_length > max_length) {
            max_length = current_length;
            max_list = lists[i];
        }
    }

    return max_list;
}

int main(void) {
    Node c = {NULL};
    Node b = {&c};
    Node a = {&b};

    Node d = {NULL};

    Node f = {NULL};
    Node e = {&f};

    Node *lists[] = { &a, &d, &e };
    size_t count = sizeof(lists) / sizeof(lists[0]);

    const Node *max = find_max_length_list(lists, count);
    if (max != NULL) {
        printf("%zu\n", list_length(max));
    }

    return 0;
}