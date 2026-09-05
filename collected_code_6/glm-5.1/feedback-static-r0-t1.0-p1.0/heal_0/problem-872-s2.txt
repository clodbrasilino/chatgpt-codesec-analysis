#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    bool is_list;
    union {
        int value;
        struct {
            struct Node *head;
            struct Node *tail;
        } list;
    } data;
} Node;

Node *make_int(int value) {
    Node *n = malloc(sizeof(Node));
    n->is_list = false;
    n->data.value = value;
    return n;
}

Node *make_list(Node *head, Node *tail) {
    Node *n = malloc(sizeof(Node));
    n->is_list = true;
    n->data.list.head = head;
    n->data.list.tail = tail;
    return n;
}

Node *copy_list(Node *n) {
    if (n == NULL) return NULL;
    Node *c = malloc(sizeof(Node));
    c->is_list = n->is_list;
    if (n->is_list) {
        c->data.list.head = copy_list(n->data.list.head);
        c->data.list.tail = copy_list(n->data.list.tail);
    } else {
        c->data.value = n->data.value;
    }
    return c;
}

void free_list(Node *n) {
    if (n == NULL) return;
    if (n->is_list) {
        free_list(n->data.list.head);
        free_list(n->data.list.tail);
    }
    free(n);
}

bool equals(Node *a, Node *b) {
    if (a == NULL && b == NULL) return true;
    if (a == NULL || b == NULL) return false;
    if (a->is_list != b->is_list) return false;
    if (a->is_list) {
        return equals(a->data.list.head, b->data.list.head) && equals(a->data.list.tail, b->data.list.tail);
    }
    return a->data.value == b->data.value;
}

Node *remove_element(Node *list, Node *elem) {
    if (list == NULL) return NULL;
    if (equals(list, elem)) {
        Node *tail = list->data.list.tail;
        list->data.list.tail = NULL;
        free_list(list);
        return tail;
    }
    list->data.list.tail = remove_element(list->data.list.tail, elem);
    return list;
}

bool is_subset(Node *sub, Node *super) {
    if (sub == NULL) return true;
    Node *head = sub->data.list.head;
    Node *tail = sub->data.list.tail;
    Node *super_copy = copy_list(super);
    Node *curr = head;
    Node *sub_tail = tail;
    while (curr != NULL) {
        Node *super_curr = super_copy;
        bool found = false;
        Node *prev = NULL;
        while (super_curr != NULL) {
            if (equals(curr, super_curr->data.list.head)) {
                found = true;
                break;
            }
            prev = super_curr;
            super_curr = super_curr->data.list.tail;
        }
        if (!found) {
            free_list(super_copy);
            free_list(sub_tail);
            return false;
        }
        if (prev == NULL) {
            Node *next = super_copy->data.list.tail;
            super_copy->data.list.tail = NULL;
            free_list(super_copy);
            super_copy = next;
        } else {
            Node *target = prev->data.list.tail;
            prev->data.list.tail = target->data.list.tail;
            target->data.list.tail = NULL;
            free_list(target);
        }
        Node *next_sub = curr->data.list.tail;
        curr->data.list.tail = NULL;
        free_list(curr);
        curr = next_sub;
    }
    free_list(super_copy);
    return true;
}

int main() {
    Node *a1 = make_int(1);
    Node *a2 = make_int(2);
    Node *a3 = make_int(3);
    Node *list_a = make_list(a3, NULL);
    list_a = make_list(a2, list_a);
    list_a = make_list(a1, list_a);

    Node *b1 = make_int(4);
    Node *b2 = make_int(2);
    Node *b3 = make_int(1);
    Node *list_b = make_list(b3, NULL);
    list_b = make_list(b2, list_b);
    list_b = make_list(b1, list_b);

    Node *c1 = make_int(5);
    Node *c2 = make_int(6);
    Node *list_c = make_list(c2, NULL);
    list_c = make_list(c1, list_c);

    Node *nested_a = make_list(list_c, NULL);
    nested_a = make_list(list_a, nested_a);

    Node *nested_b = make_list(list_b, NULL);
    nested_b = make_list(list_c, nested_b);
    nested_b = make_list(list_a, nested_b);

    Node *sub1 = make_list(a3, NULL);
    sub1 = make_list(a1, sub1);
    Node *sub2 = make_list(copy_list(list_c), NULL);
    sub2 = make_list(sub1, sub2);

    bool res1 = is_subset(sub2, nested_b);
    bool res2 = is_subset(sub2, nested_a);

    printf("%d %d\n", res1, res2);

    free_list(nested_a);
    free_list(nested_b);
    free_list(sub2);

    return 0;
}