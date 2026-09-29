#include <stdio.h>
#include <stdlib.h>

typedef enum NodeType { VALUE, LIST } NodeType;

typedef struct Node {
    NodeType type;
    union {
        int value;
        struct Node *child;
    } data;
    struct Node *next;
} Node;

Node* create_value_node(int val) {
    Node *n = (Node*)malloc(sizeof(Node));
    if (!n) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    n->type = VALUE;
    n->data.value = val;
    n->next = NULL;
    return n;
}

Node* create_list_node(Node *child) {
    Node *n = (Node*)malloc(sizeof(Node));
    if (!n) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    n->type = LIST;
    n->data.child = child;
    n->next = NULL;
    return n;
}

int exists_in_list(int val, Node *head) {
    Node *curr = head;
    while (curr != NULL) {
        if (curr->type == VALUE) {
            if (curr->data.value == val) {
                return 1;
            }
        } else if (curr->type == LIST) {
            if (exists_in_list(val, curr->data.child)) {
                return 1;
            }
        }
        curr = curr->next;
    }
    return 0;
}

static void find_elements_helper(Node *nested, Node *other, Node **result_head, Node **result_tail) {
    Node *curr = nested;
    while (curr != NULL) {
        if (curr->type == VALUE) {
            if (exists_in_list(curr->data.value, other)) {
                Node *new_node = create_value_node(curr->data.value);
                if (new_node) {
                    if (*result_tail == NULL) {
                        *result_head = new_node;
                        *result_tail = new_node;
                    } else {
                        (*result_tail)->next = new_node;
                        *result_tail = new_node;
                    }
                }
            }
        } else if (curr->type == LIST) {
            find_elements_helper(curr->data.child, other, result_head, result_tail);
        }
        curr = curr->next;
    }
}

Node* find_common_elements(Node *nested, Node *other) {
    Node *result_head = NULL;
    Node *result_tail = NULL;
    find_elements_helper(nested, other, &result_head, &result_tail);
    return result_head;
}

void free_list(Node *head) {
    while (head != NULL) {
        Node *next = head->next;
        if (head->type == LIST) {
            free_list(head->data.child);
        }
        free(head);
        head = next;
    }
}

void print_list(Node *head) {
    printf("[");
    Node *curr = head;
    while (curr != NULL) {
        if (curr->type == VALUE) {
            printf("%d", curr->data.value);
        } else if (curr->type == LIST) {
            print_list(curr->data.child);
        }
        if (curr->next != NULL) {
            printf(", ");
        }
        curr = curr->next;
    }
    printf("]");
}

Node* append_value(Node *head, int val) {
    Node *n = create_value_node(val);
    if (!n) {
        return head;
    }
    if (head == NULL) {
        return n;
    }
    Node *curr = head;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = n;
    return head;
}

int main(void) {
    Node *nested = NULL;
    nested = append_value(nested, 1);
    nested = append_value(nested, 2);

    Node *sub_list = NULL;
    sub_list = append_value(sub_list, 3);
    sub_list = append_value(sub_list, 4);

    Node *list_node = create_list_node(sub_list);
    if (list_node) {
        Node *curr = nested;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = list_node;
    }

    Node *other = NULL;
    other = append_value(other, 2);
    other = append_value(other, 4);
    other = append_value(other, 6);

    Node *result = find_common_elements(nested, other);

    printf("Nested List: ");
    print_list(nested);
    printf("\n");

    printf("Other List: ");
    print_list(other);
    printf("\n");

    printf("Common Elements: ");
    print_list(result);
    printf("\n");

    free_list(nested);
    free_list(other);
    free_list(result);

    return 0;
}