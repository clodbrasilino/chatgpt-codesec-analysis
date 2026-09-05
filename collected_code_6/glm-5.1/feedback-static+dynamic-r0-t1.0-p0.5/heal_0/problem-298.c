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

int value_in_list(int val, Node *head) {
    Node *curr = head;
    while (curr) {
        if (!curr->is_list && curr->data.value == val) {
            return 1;
        }
        curr = curr->next;
    }
    return 0;
}

int nested_list_in_list(Node *nested_head, Node *flat_head) {
    Node *curr = nested_head;
    while (curr) {
        if (curr->is_list) {
            if (!nested_list_in_list(curr->data.list.items, flat_head)) {
                return 0;
            }
        } else {
            if (!value_in_list(curr->data.value, flat_head)) {
                return 0;
            }
        }
        curr = curr->next;
    }
    return 1;
}

Node *find_nested_elements(Node *nested_list, Node *flat_list) {
    Node *result = NULL;
    Node *tail = NULL;
    Node *curr = nested_list;

    while (curr) {
        if (curr->is_list) {
            if (nested_list_in_list(curr->data.list.items, flat_list)) {
                Node *new_node = create_list_node(curr->data.list.items, curr->data.list.count);
                if (!result) {
                    result = new_node;
                    tail = new_node;
                } else {
                    tail->next = new_node;
                    tail = new_node;
                }
            }
        }
        curr = curr->next;
    }

    return result;
}

void print_nested_list(Node *head) {
    Node *curr = head;
    printf("[");
    while (curr) {
        if (curr->is_list) {
            printf("[");
            for (size_t i = 0; i < curr->data.list.count; i++) {
                if (curr->data.list.items[i].is_list) {
                    printf("...");
                } else {
                    printf("%d", curr->data.list.items[i].data.value);
                }
                if (i < curr->data.list.count - 1) {
                    printf(", ");
                }
            }
            printf("]");
        } else {
            printf("%d", curr->data.value);
        }
        if (curr->next) {
            printf(", ");
        }
        curr = curr->next;
    }
    printf("]\n");
}

void free_list(Node *head) {
    Node *curr = head;
    while (curr) {
        Node *next = curr->next;
        free(curr);
        curr = next;
    }
}

int main(void) {
    Node *flat_list = create_value_node(1);
    flat_list->next = create_value_node(2);
    flat_list->next->next = create_value_node(3);
    flat_list->next->next->next = create_value_node(4);

    Node *sub1_items = (Node *)malloc(2 * sizeof(Node));
    if (!sub1_items) exit(EXIT_FAILURE);
    sub1_items[0].is_list = 0; sub1_items[0].data.value = 1; sub1_items[0].next = &sub1_items[1];
    sub1_items[1].is_list = 0; sub1_items[1].data.value = 2; sub1_items[1].next = NULL;
    Node *sub1 = create_list_node(sub1_items, 2);

    Node *sub2_items = (Node *)malloc(2 * sizeof(Node));
    if (!sub2_items) exit(EXIT_FAILURE);
    sub2_items[0].is_list = 0; sub2_items[0].data.value = 5; sub2_items[0].next = &sub2_items[1];
    sub2_items[1].is_list = 0; sub2_items[1].data.value = 6; sub2_items[1].next = NULL;
    Node *sub2 = create_list_node(sub2_items, 2);

    Node *sub3_items = (Node *)malloc(2 * sizeof(Node));
    if (!sub3_items) exit(EXIT_FAILURE);
    sub3_items[0].is_list = 0; sub3_items[0].data.value = 3; sub3_items[0].next = &sub3_items[1];
    sub3_items[1].is_list = 0; sub3_items[1].data.value = 4; sub3_items[1].next = NULL;
    Node *sub3 = create_list_node(sub3_items, 2);

    Node *nested_list = sub1;
    sub1->next = sub2;
    sub2->next = sub3;

    Node *result = find_nested_elements(nested_list, flat_list);

    print_nested_list(result);

    free_list(result);
    free_list(flat_list);
    free(sub1_items);
    free(sub2_items);
    free(sub3_items);
    free_list(nested_list);

    return 0;
}