#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int is_list;
    union {
        int value;
        struct {
            struct Node* head;
            struct Node* tail;
        } list;
    } data;
} Node;

typedef struct FlatNode {
    int value;
    struct FlatNode* next;
} FlatNode;

Node* create_int_node(int val) {
    Node* n = (Node*)malloc(sizeof(Node));
    if (!n) exit(EXIT_FAILURE);
    n->is_list = 0;
    n->data.value = val;
    return n;
}

Node* create_list_node(Node* head, Node* tail) {
    Node* n = (Node*)malloc(sizeof(Node));
    if (!n) exit(EXIT_FAILURE);
    n->is_list = 1;
    n->data.list.head = head;
    n->data.list.tail = tail;
    return n;
}

FlatNode* create_flat_node(int val) {
    FlatNode* n = (FlatNode*)malloc(sizeof(FlatNode));
    if (!n) exit(EXIT_FAILURE);
    n->value = val;
    n->next = NULL;
    return n;
}

void flatten_recursive(const Node* node, FlatNode** tail) {
    if (!node) return;
    if (!node->is_list) {
        FlatNode* fn = create_flat_node(node->data.value);
        (*tail)->next = fn;
        *tail = fn;
    } else {
        flatten_recursive(node->data.list.head, tail);
        flatten_recursive(node->data.list.tail, tail);
    }
}

FlatNode* flatten(const Node* root) {
    FlatNode dummy;
    dummy.next = NULL;
    FlatNode* tail = &dummy;
    flatten_recursive(root, &tail);
    return dummy.next;
}

void free_nested(Node* node) {
    if (!node) return;
    if (node->is_list) {
        free_nested(node->data.list.head);
        free_nested(node->data.list.tail);
    }
    free(node);
}

void free_flat(FlatNode* node) {
    while (node) {
        FlatNode* next = node->next;
        free(node);
        node = next;
    }
}

void print_flat(const FlatNode* node) {
    while (node) {
        printf("%d ", node->value);
        node = node->next;
    }
    printf("\n");
}

int main(void) {
    Node* n1 = create_int_node(1);
    const Node* n2 = create_int_node(2);
    /* Possible weaknesses found:
     *  Variable 'n3' is assigned a value that is never used. [unreadVariable]
     *  Variable 'n3' can be declared as pointer to const [constVariablePointer]
     */
    Node* n3 = create_int_node(3);
    Node* n4 = create_int_node(4);
    Node* n5 = create_int_node(5);
    Node* n6 = create_int_node(6);

    Node* inner_list = create_list_node((Node*)n2, create_list_node(n4, NULL));
    Node* outer_list = create_list_node(n1, create_list_node(inner_list, create_list_node(n5, create_list_node(n6, NULL))));

    FlatNode* flat = flatten(outer_list);
    print_flat(flat);

    free_flat(flat);
    free_nested(outer_list);

    return 0;
}