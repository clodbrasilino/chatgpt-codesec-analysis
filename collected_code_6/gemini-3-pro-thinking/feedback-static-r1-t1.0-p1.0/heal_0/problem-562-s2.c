#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

struct SublistNode {
    int data;
    struct SublistNode *next;
};

struct ListNode {
    struct SublistNode *sublist_head;
    struct ListNode *next;
};

size_t get_max_sublist_length(const struct ListNode *head) {
    size_t max_length = 0;
    const struct ListNode *current_list = head;

    while (current_list != NULL) {
        size_t current_length = 0;
        const struct SublistNode *current_sublist = current_list->sublist_head;

        while (current_sublist != NULL) {
            current_length++;
            current_sublist = current_sublist->next;
        }

        if (current_length > max_length) {
            max_length = current_length;
        }

        current_list = current_list->next;
    }

    return max_length;
}

void free_sublist(struct SublistNode *head) {
    struct SublistNode *current = head;
    while (current != NULL) {
        struct SublistNode *temp = current;
        current = current->next;
        free(temp);
    }
}

void free_list(struct ListNode *head) {
    struct ListNode *current = head;
    while (current != NULL) {
        struct ListNode *temp = current;
        current = current->next;
        if (temp->sublist_head != NULL) {
            free_sublist(temp->sublist_head);
        }
        free(temp);
    }
}

struct SublistNode *build_sublist(size_t length) {
    struct SublistNode *head = NULL;
    struct SublistNode *tail = NULL;

    for (size_t i = 0; i < length; i++) {
        struct SublistNode *node = malloc(sizeof(struct SublistNode));
        if (node == NULL) {
            free_sublist(head);
            return NULL;
        }
        node->data = 0;
        node->next = NULL;

        if (head == NULL) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }

    return head;
}

int main(void) {
    struct ListNode *head = NULL;
    struct ListNode *tail = NULL;

    const size_t lengths[] = {3, 8, 2, 5, 1};
    const size_t num_lists = sizeof(lengths) / sizeof(lengths[0]);

    for (size_t i = 0; i < num_lists; i++) {
        struct SublistNode *sublist = build_sublist(lengths[i]);
        if (sublist == NULL && lengths[i] > 0) {
            free_list(head);
            return EXIT_FAILURE;
        }

        struct ListNode *node = malloc(sizeof(struct ListNode));
        if (node == NULL) {
            free_sublist(sublist);
            free_list(head);
            return EXIT_FAILURE;
        }

        node->sublist_head = sublist;
        node->next = NULL;

        if (head == NULL) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }

    size_t max_length = get_max_sublist_length(head);
    printf("%zu\n", max_length);

    free_list(head);

    return EXIT_SUCCESS;
}