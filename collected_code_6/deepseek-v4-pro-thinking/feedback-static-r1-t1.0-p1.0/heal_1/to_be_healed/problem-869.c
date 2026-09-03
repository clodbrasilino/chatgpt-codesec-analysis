#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct IntNode {
    int data;
    struct IntNode *next;
} IntNode;

typedef struct ListNode {
    IntNode *sublist;
    struct ListNode *next;
} ListNode;

static void free_int_list(IntNode *head) {
    while (head != NULL) {
        IntNode *next = head->next;
        free(head);
        head = next;
    }
}

static IntNode *int_list_from_array(const int *values, size_t count) {
    IntNode *head = NULL;
    IntNode **tail = &head;

    for (size_t i = 0; i < count; ++i) {
        IntNode *node = malloc(sizeof(*node));
        if (node == NULL) {
            free_int_list(head);
            return NULL;
        }
        node->data = values[i];
        node->next = NULL;
        *tail = node;
        tail = &node->next;
    }

    return head;
}

static int list_append_sublist(ListNode **head, IntNode *sublist) {
    ListNode *node = malloc(sizeof(*node));
    if (node == NULL) {
        return 0;
    }

    node->sublist = sublist;
    node->next = NULL;

    if (*head == NULL) {
        *head = node;
    } else {
        ListNode *tail = *head;
        while (tail->next != NULL) {
            tail = tail->next;
        }
        tail->next = node;
    }

    return 1;
}

static void free_list_of_lists(ListNode *head) {
    while (head != NULL) {
        ListNode *next = head->next;
        free_int_list(head->sublist);
        free(head);
        head = next;
    }
}

static int add_sublist_from_array(ListNode **head, const int *values, size_t count) {
    /* Possible weaknesses found:
     *  Calling function 'int_list_from_array' returns 0
     *  Assignment 'sub=int_list_from_array(values,count)', assigned value is 0
     */
    IntNode *sub = int_list_from_array(values, count);
    /* Possible weaknesses found:
     *  Condition 'sub==NULL' is always true
     *  Condition 'sub==NULL' is always true [knownConditionTrueFalse]
     */
    if (sub == NULL) {
        return 0;
    }

    if (!list_append_sublist(head, sub)) {
        free_int_list(sub);
        return 0;
    }

    return 1;
}

static int sublist_outside_range(const IntNode *sublist, int low, int high) {
    if (sublist == NULL) {
        return 0;
    }

    for (const IntNode *p = sublist; p != NULL; p = p->next) {
        if (p->data >= low && p->data <= high) {
            return 0;
        }
    }

    return 1;
}

void remove_sublists_outside_range(ListNode **head, int low, int high) {
    if (head == NULL || *head == NULL) {
        return;
    }

    ListNode **indirect = head;

    while (*indirect != NULL) {
        ListNode *current = *indirect;

        if (sublist_outside_range(current->sublist, low, high)) {
            *indirect = current->next;
            free_int_list(current->sublist);
            free(current);
        } else {
            indirect = &current->next;
        }
    }
}

static void print_int_list(const IntNode *head) {
    printf("[");
    for (const IntNode *p = head; p != NULL; p = p->next) {
        printf("%d", p->data);
        if (p->next != NULL) {
            printf(", ");
        }
    }
    printf("]");
}

static void print_list_of_lists(const ListNode *head) {
    printf("[");
    for (const ListNode *p = head; p != NULL; p = p->next) {
        print_int_list(p->sublist);
        if (p->next != NULL) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(void) {
    ListNode *head = NULL;

    int values1[] = {1, 2, 3};
    int values2[] = {10, 20};
    int values3[] = {4, 15};

    if (!add_sublist_from_array(&head, values1, sizeof(values1) / sizeof(values1[0])) ||
        !add_sublist_from_array(&head, values2, sizeof(values2) / sizeof(values2[0])) ||
        !add_sublist_from_array(&head, values3, sizeof(values3) / sizeof(values3[0]))) {
        free_list_of_lists(head);
        return EXIT_FAILURE;
    }

    print_list_of_lists(head);
    remove_sublists_outside_range(&head, 5, 15);
    print_list_of_lists(head);

    free_list_of_lists(head);
    return EXIT_SUCCESS;
}