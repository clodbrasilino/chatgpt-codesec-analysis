#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    bool is_list;
    union {
        int value;
        struct {
            struct Node* head;
            struct Node* tail;
        } list;
    } data;
} Node;

Node* make_int(int val) {
    Node* n = (Node*)malloc(sizeof(Node));
    if (!n) exit(EXIT_FAILURE);
    n->is_list = false;
    n->data.value = val;
    return n;
}

Node* make_list(Node* head, Node* tail) {
    Node* n = (Node*)malloc(sizeof(Node));
    if (!n) exit(EXIT_FAILURE);
    n->is_list = true;
    n->data.list.head = head;
    n->data.list.tail = tail;
    return n;
}

bool list_equal(Node* a, Node* b) {
    if (a == NULL && b == NULL) return true;
    if (a == NULL || b == NULL) return false;
    if (a->is_list != b->is_list) return false;
    if (!a->is_list) return a->data.value == b->data.value;
    return list_equal(a->data.list.head, b->data.list.head) && list_equal(a->data.list.tail, b->data.list.tail);
}

bool is_subset(Node* a, Node* b) {
    if (a == NULL) return true;
    if (b == NULL) return false;
    if (list_equal(a, b)) return true;
    if (a->is_list && b->is_list) {
        if (is_subset(a, b->data.list.head)) return true;
        return is_subset(a, b->data.list.tail);
    }
    return false;
}

void free_list(Node* n) {
    if (n == NULL) return;
    if (n->is_list) {
        free_list(n->data.list.head);
        free_list(n->data.list.tail);
    }
    free(n);
}

int main(void) {
    Node* sublist = make_list(make_list(make_int(1), make_list(make_int(2), NULL)), NULL);
    Node* main_list = make_list(make_list(make_int(3), NULL), make_list(make_list(make_int(1), make_list(make_int(2), NULL)), NULL));
    
    bool result = is_subset(sublist, main_list);
    printf("%d\n", result);
    
    free_list(sublist);
    free_list(main_list);
    
    return 0;
}