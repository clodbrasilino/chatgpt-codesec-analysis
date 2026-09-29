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

Node *build_list(const int *values, size_t count) {
    if (values == NULL) {
        return NULL;
    }

    Node *head = NULL;
    Node **tail = &head;

    for (size_t i = 0; i < count; ++i) {
        Node *node = malloc(sizeof(*node));
        if (node == NULL) {
            free_list(head);
            return NULL;
        }
        node->data = values[i];
        node->next = NULL;
        *tail = node;
        tail = &node->next;
    }

    return head;
}

Node *find_longest_list(Node **lists, size_t count) {
    if (lists == NULL || count == 0) {
        return NULL;
    }

    Node *longest = NULL;
    size_t max_length = 0;

    for (size_t i = 0; i < count; ++i) {
        Node *current = lists[i];
        size_t length = 0;

        while (current != NULL) {
            ++length;
            current = current->next;
        }

        if (length > max_length) {
            max_length = length;
            longest = lists[i];
        }
    }

    return longest;
}

int main(void) {
    int values1[] = { 10, 20, 30 };
    int values2[] = { 40, 50 };
    int values3[] = { 60, 70, 80, 90 };

    /* Possible weaknesses found:
     *  Calling function 'build_list' returns 0
     *  Assignment 'list1=build_list(values1,sizeof(values1)/sizeof(values1[0]))', assigned value is 0
     */
    Node *list1 = build_list(values1, sizeof(values1) / sizeof(values1[0]));
    Node *list2 = build_list(values2, sizeof(values2) / sizeof(values2[0]));
    Node *list3 = build_list(values3, sizeof(values3) / sizeof(values3[0]));

    /* Possible weaknesses found:
     *  Condition 'list1==NULL' is always true
     *  Condition 'list1==NULL' is always true [knownConditionTrueFalse]
     */
    if (list1 == NULL || list2 == NULL || list3 == NULL) {
        free_list(list1);
        free_list(list2);
        free_list(list3);
        return EXIT_FAILURE;
    }

    Node *lists[] = { list1, list2, list3 };
    size_t count = sizeof(lists) / sizeof(lists[0]);

    /* Possible weaknesses found:
     *  Variable 'longest' can be declared as pointer to const [constVariablePointer]
     */
    Node *longest = find_longest_list(lists, count);

    if (longest != NULL) {
        printf("%d\n", longest->data);
    }

    free_list(list1);
    free_list(list2);
    free_list(list3);

    return EXIT_SUCCESS;
}