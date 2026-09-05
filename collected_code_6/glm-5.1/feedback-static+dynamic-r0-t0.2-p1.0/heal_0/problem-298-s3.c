#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int is_list;
    union {
        int value;
        struct {
            struct Node *items;
            size_t count;
        } list;
    } data;
    struct Node *next;
} Node;

Node *create_value_node(int val) {
    Node *n = (Node *)malloc(sizeof(Node));
    if (!n) exit(EXIT_FAILURE);
    n->is_list = 0;
    n->data.value = val;
    n->next = NULL;
    return n;
}

Node *create_list_node(Node *items, size_t count) {
    Node *n = (Node *)malloc(sizeof(Node));
    if (!n) exit(EXIT_FAILURE);
    n->is_list = 1;
    n->data.list.items = items;
    n->data.list.count = count;
    n->next = NULL;
    return n;
}

int value_in_list(int val, Node *list) {
    Node *curr = list;
    while (curr) {
        if (!curr->is_list && curr->data.value == val) {
            return 1;
        }
        curr = curr->next;
    }
    return 0;
}

int list_in_list(Node *sub, Node *list) {
    Node *curr = list;
    while (curr) {
        if (curr->is_list && curr->data.list.count == sub->data.list.count) {
            size_t i;
            int match = 1;
            Node *s_curr = sub->data.list.items;
            Node *l_curr = curr->data.list.items;
            for (i = 0; i < sub->data.list.count; i++) {
                if (s_curr->is_list != l_curr->is_list) {
                    match = 0;
                    break;
                }
                if (s_curr->is_list) {
                    if (!list_in_list(s_curr, l_curr)) {
                        match = 0;
                        break;
                    }
                } else {
                    if (s_curr->data.value != l_curr->data.value) {
                        match = 0;
                        break;
                    }
                }
                s_curr = s_curr->next;
                l_curr = l_curr->next;
            }
            if (match) return 1;
        }
        curr = curr->next;
    }
    return 0;
}

Node *find_nested_elements(Node *a, Node *b) {
    Node *result = NULL;
    Node **tail = &result;
    Node *curr = a;
    while (curr) {
        if (curr->is_list) {
            if (list_in_list(curr, b)) {
                Node *n = (Node *)malloc(sizeof(Node));
                if (!n) exit(EXIT_FAILURE);
                n->is_list = 1;
                n->data.list.items = curr->data.list.items;
                n->data.list.count = curr->data.list.count;
                n->next = NULL;
                *tail = n;
                tail = &n->next;
            }
        } else {
            if (value_in_list(curr->data.value, b)) {
                Node *n = (Node *)malloc(sizeof(Node));
                if (!n) exit(EXIT_FAILURE);
                n->is_list = 0;
                n->data.value = curr->data.value;
                n->next = NULL;
                *tail = n;
                tail = &n->next;
            }
        }
        curr = curr->next;
    }
    return result;
}

void print_list(Node *n) {
    printf("[");
    Node *curr = n;
    while (curr) {
        if (curr->is_list) {
            print_list(curr->data.list.items);
        } else {
            printf("%d", curr->data.value);
        }
        if (curr->next) {
            printf(", ");
        }
        curr = curr->next;
    }
    printf("]");
}

void free_list(Node *n) {
    Node *curr = n;
    while (curr) {
        if (curr->is_list) {
            free_list(curr->data.list.items);
        }
        Node *tmp = curr;
        curr = curr->next;
        free(tmp);
    }
}

int main(void) {
    Node *a_sub1 = create_value_node(1);
    a_sub1->next = create_value_node(2);
    Node *a_n1 = create_list_node(a_sub1, 2);
    Node *a_n2 = create_value_node(3);
    Node *a_sub2 = create_value_node(4);
    a_sub2->next = create_value_node(5);
    Node *a_n3 = create_list_node(a_sub2, 2);
    a_n1->next = a_n2;
    a_n2->next = a_n3;

    Node *b_sub1 = create_value_node(1);
    b_sub1->next = create_value_node(2);
    Node *b_n1 = create_list_node(b_sub1, 2);
    Node *b_n2 = create_value_node(6);
    Node *b_sub2 = create_value_node(7);
    b_sub2->next = create_value_node(8);
    Node *b_n3 = create_list_node(b_sub2, 2);
    b_n1->next = b_n2;
    b_n2->next = b_n3;

    Node *result = find_nested_elements(a_n1, b_n1);

    printf("A: ");
    print_list(a_n1);
    printf("\nB: ");
    print_list(b_n1);
    printf("\nIntersection: ");
    print_list(result);
    printf("\n");

    free_list(a_n1);
    free_list(b_n1);
    free_list(result);

    return 0;
}