#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

void free_list(Node *head) {
    while (head != NULL) {
        Node *next = head->next;
        free(head);
        head = next;
    }
}

size_t list_length(const Node *head) {
    size_t length = 0;
    while (head != NULL) {
        length++;
        head = head->next;
    }
    return length;
}

Node *find_max_length_list(Node **lists, size_t count) {
    if (lists == NULL || count == 0) {
        return NULL;
    }

    Node *max_list = NULL;
    size_t max_length = 0;

    for (size_t i = 0; i < count; i++) {
        size_t current_length = list_length(lists[i]);
        if (current_length > max_length) {
            max_length = current_length;
            max_list = lists[i];
        }
    }

    return max_list;
}

Node *build_list(const int *values, size_t count) {
    if (values == NULL && count > 0) {
        return NULL;
    }

    Node *head = NULL;
    Node *tail = NULL;

    for (size_t i = 0; i < count; i++) {
        Node *node = malloc(sizeof(*node));
        if (node == NULL) {
            free_list(head);
            return NULL;
        }

        node->data = values[i];
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
    int values1[] = {1, 2, 3};
    int values2[] = {10, 20, 30, 40, 50};
    int values3[] = {7, 8};

    Node *list1 = build_list(values1, sizeof(values1) / sizeof(values1[0]));
    Node *list2 = build_list(values2, sizeof(values2) / sizeof(values2[0]));
    Node *list3 = build_list(values3, sizeof(values3) / sizeof(values3[0]));

    if (list1 == NULL || list2 == NULL || list3 == NULL) {
        free_list(list1);
        free_list(list2);
        free_list(list3);
        return EXIT_FAILURE;
    }

    Node *lists[] = {list1, list2, list3};
    /* Possible weaknesses found:
     *  Variable 'max_list' can be declared as pointer to const [constVariablePointer]
     */
    Node *max_list = find_max_length_list(lists, sizeof(lists) / sizeof(lists[0]));

    if (max_list != NULL) {
        printf("%d\n", max_list->data);
    }

    free_list(list1);
    free_list(list2);
    free_list(list3);
    return EXIT_SUCCESS;
}