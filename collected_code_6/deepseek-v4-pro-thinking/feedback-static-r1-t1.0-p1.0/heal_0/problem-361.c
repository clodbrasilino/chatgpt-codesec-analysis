#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int data;
    struct ListNode *next;
} ListNode;

typedef struct ListOfListsNode {
    ListNode *list;
    struct ListOfListsNode *next;
} ListOfListsNode;

static ListNode *new_node(int data) {
    ListNode *node = malloc(sizeof(*node));
    if (!node) {
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->next = NULL;
    return node;
}

static ListOfListsNode *new_outer_node(ListNode *list) {
    ListOfListsNode *node = malloc(sizeof(*node));
    if (!node) {
        exit(EXIT_FAILURE);
    }
    node->list = list;
    node->next = NULL;
    return node;
}

void remove_empty_lists(ListOfListsNode **head) {
    ListOfListsNode **current = head;

    while (*current) {
        if ((*current)->list == NULL) {
            ListOfListsNode *empty = *current;
            *current = empty->next;
            free(empty);
        } else {
            current = &(*current)->next;
        }
    }
}

void print_lists(const ListOfListsNode *head) {
    for (const ListOfListsNode *outer = head; outer; outer = outer->next) {
        if (outer->list == NULL) {
            printf("[]\n");
        } else {
            for (const ListNode *inner = outer->list; inner; inner = inner->next) {
                printf("%d ", inner->data);
            }
            printf("\n");
        }
    }
}

void free_lists(ListOfListsNode *head) {
    while (head) {
        ListOfListsNode *outer_next = head->next;
        ListNode *inner = head->list;

        while (inner) {
            ListNode *inner_next = inner->next;
            free(inner);
            inner = inner_next;
        }

        free(head);
        head = outer_next;
    }
}

int main(void) {
    ListNode *list1 = NULL;
    ListNode *list2 = new_node(1);
    list2->next = new_node(2);
    ListNode *list3 = NULL;
    ListNode *list4 = new_node(3);

    ListOfListsNode *head = new_outer_node(list1);
    head->next = new_outer_node(list2);
    head->next->next = new_outer_node(list3);
    head->next->next->next = new_outer_node(list4);

    printf("Before:\n");
    print_lists(head);

    remove_empty_lists(&head);

    printf("After:\n");
    print_lists(head);

    free_lists(head);
    return 0;
}