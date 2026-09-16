#include <stdio.h>
#include <stdlib.h>

typedef struct IntNode {
    int data;
    struct IntNode *next;
} IntNode;

typedef struct ListNode {
    IntNode *list;
    struct ListNode *next;
} ListNode;

IntNode *int_node_new(int data) {
    IntNode *node = malloc(sizeof(*node));
    if (node == NULL) {
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->next = NULL;
    return node;
}

ListNode *list_node_new(IntNode *list) {
    ListNode *node = malloc(sizeof(*node));
    if (node == NULL) {
        exit(EXIT_FAILURE);
    }
    node->list = list;
    node->next = NULL;
    return node;
}

IntNode *append_int(IntNode *head, int data) {
    IntNode *node = int_node_new(data);
    if (head == NULL) {
        return node;
    }
    IntNode *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = node;
    return head;
}

ListNode *append_list(ListNode *head, IntNode *list) {
    ListNode *node = list_node_new(list);
    if (head == NULL) {
        return node;
    }
    ListNode *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = node;
    return head;
}

void remove_empty_lists(ListNode **head) {
    if (head == NULL) {
        return;
    }
    ListNode *current = *head;
    ListNode *previous = NULL;
    while (current != NULL) {
        if (current->list == NULL) {
            ListNode *to_remove = current;
            if (previous == NULL) {
                *head = current->next;
                current = *head;
            } else {
                previous->next = current->next;
                current = current->next;
            }
            free(to_remove);
        } else {
            previous = current;
            current = current->next;
        }
    }
}

void free_int_list(IntNode *head) {
    while (head != NULL) {
        IntNode *next = head->next;
        free(head);
        head = next;
    }
}

void free_list_of_lists(ListNode *head) {
    while (head != NULL) {
        ListNode *next = head->next;
        free_int_list(head->list);
        free(head);
        head = next;
    }
}

void print_list_of_lists(const ListNode *head) {
    int index = 0;
    while (head != NULL) {
        printf("list %d:", index);
        const IntNode *current = head->list;
        while (current != NULL) {
            printf(" %d", current->data);
            current = current->next;
        }
        printf("\n");
        head = head->next;
        index++;
    }
}

int main(void) {
    ListNode *outer = NULL;

    IntNode *empty1 = NULL;
    IntNode *list1 = NULL;
    list1 = append_int(list1, 1);
    list1 = append_int(list1, 2);
    IntNode *empty2 = NULL;
    IntNode *list2 = NULL;
    list2 = append_int(list2, 3);

    outer = append_list(outer, empty1);
    outer = append_list(outer, list1);
    outer = append_list(outer, empty2);
    outer = append_list(outer, list2);

    print_list_of_lists(outer);

    remove_empty_lists(&outer);

    print_list_of_lists(outer);

    free_list_of_lists(outer);
    return 0;
}