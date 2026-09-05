#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum {
    TYPE_INT,
    TYPE_TUPLE
} ElementType;

typedef struct {
    ElementType type;
    union {
        int int_val;
        struct {
            int a;
            int b;
        } tuple_val;
    } data;
} ListElement;

typedef struct ListNode {
    ListElement element;
    struct ListNode *next;
} ListNode;

size_t count_until_tuple(const ListNode *head) {
    size_t count = 0;
    const ListNode *current = head;

    while (current != NULL) {
        if (current->element.type == TYPE_TUPLE) {
            break;
        }
        count++;
        current = current->next;
    }

    return count;
}

ListNode *create_node_int(int val) {
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    if (node == NULL) {
        exit(EXIT_FAILURE);
    }
    node->element.type = TYPE_INT;
    node->element.data.int_val = val;
    node->next = NULL;
    return node;
}

ListNode *create_node_tuple(int a, int b) {
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    if (node == NULL) {
        exit(EXIT_FAILURE);
    }
    node->element.type = TYPE_TUPLE;
    node->element.data.tuple_val.a = a;
    node->element.data.tuple_val.b = b;
    node->next = NULL;
    return node;
}

void append_node(ListNode **head, ListNode *new_node) {
    if (head == NULL || new_node == NULL) {
        free(new_node);
        return;
    }
    if (*head == NULL) {
        *head = new_node;
    } else {
        ListNode *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

void free_list(ListNode *head) {
    ListNode *current = head;
    while (current != NULL) {
        ListNode *next = current->next;
        free(current);
        current = next;
    }
}

int main(void) {
    ListNode *head = NULL;

    append_node(&head, create_node_int(10));
    append_node(&head, create_node_int(20));
    append_node(&head, create_node_int(30));
    append_node(&head, create_node_tuple(1, 2));
    append_node(&head, create_node_int(40));

    size_t count = count_until_tuple(head);
    printf("%zu\n", count);

    free_list(head);
    head = NULL;

    return 0;
}