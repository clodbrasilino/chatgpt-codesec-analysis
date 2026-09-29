#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int is_list;
    union {
        int value;
        struct {
            struct Node *head;
            struct Node *tail;
        } list;
    } data;
} Node;

typedef struct IntListNode {
    int value;
    struct IntListNode *next;
} IntListNode;

Node *create_value(int v) {
    Node *n = (Node *)malloc(sizeof(Node));
    if (!n) exit(EXIT_FAILURE);
    n->is_list = 0;
    n->data.value = v;
    return n;
}

Node *create_list(Node *head, Node *tail) {
    Node *n = (Node *)malloc(sizeof(Node));
    if (!n) exit(EXIT_FAILURE);
    n->is_list = 1;
    n->data.list.head = head;
    n->data.list.tail = tail;
    return n;
}

IntListNode *create_int_node(int v, IntListNode *next) {
    IntListNode *n = (IntListNode *)malloc(sizeof(IntListNode));
    if (!n) exit(EXIT_FAILURE);
    n->value = v;
    n->next = next;
    return n;
}

int contains_value(IntListNode *list, int value) {
    IntListNode *curr = list;
    while (curr) {
        if (curr->value == value) return 1;
        curr = curr->next;
    }
    return 0;
}

IntListNode *find_nested_elements(Node *nested, IntListNode *flat) {
    if (!nested) return NULL;
    if (!nested->is_list) {
        if (contains_value(flat, nested->data.value)) {
            return create_int_node(nested->data.value, find_nested_elements(nested, flat));
        }
        return NULL;
    }
    IntListNode *head_res = find_nested_elements(nested->data.list.head, flat);
    IntListNode *tail_res = find_nested_elements(nested->data.list.tail, flat);
    if (head_res) {
        IntListNode *curr = head_res;
        while (curr->next) curr = curr->next;
        curr->next = tail_res;
        return head_res;
    }
    return tail_res;
}

void free_nested(Node *n) {
    if (!n) return;
    if (n->is_list) {
        free_nested(n->data.list.head);
        free_nested(n->data.list.tail);
    }
    free(n);
}

void free_int_list(IntListNode *n) {
    while (n) {
        IntListNode *next = n->next;
        free(n);
        n = next;
    }
}

void print_int_list(IntListNode *n) {
    while (n) {
        printf("%d ", n->value);
        n = n->next;
    }
    printf("\n");
}

int main(void) {
    Node *n1 = create_value(1);
    Node *n2 = create_value(2);
    Node *n3 = create_value(3);
    Node *n4 = create_value(4);
    Node *n5 = create_value(5);
    Node *inner = create_list(n2, create_list(n3, NULL));
    Node *nested = create_list(n1, create_list(inner, create_list(n4, create_list(n5, NULL))));

    IntListNode *flat = create_int_node(2, create_int_node(4, create_int_node(6, NULL)));

    IntListNode *result = find_nested_elements(nested, flat);
    print_int_list(result);

    free_nested(nested);
    free_int_list(flat);
    free_int_list(result);

    return 0;
}