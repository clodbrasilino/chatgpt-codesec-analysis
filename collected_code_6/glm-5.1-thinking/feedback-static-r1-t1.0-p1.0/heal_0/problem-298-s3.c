#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
    struct Node *child;
} Node;

Node *create_node(int value) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->value = value;
    node->next = NULL;
    node->child = NULL;
    return node;
}

void free_list(Node *head) {
    if (head == NULL) {
        return;
    }
    Node *current = head;
    while (current != NULL) {
        Node *next_ptr = current->next;
        if (current->child != NULL) {
            free_list(current->child);
        }
        free(current);
        current = next_ptr;
    }
}

int exists_in_list(Node *head, int value) {
    Node *current = head;
    while (current != NULL) {
        if (current->value == value) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

int append_result(Node **result_head, Node **result_tail, int value) {
    Node *new_node = create_node(value);
    if (new_node == NULL) {
        return -1;
    }
    if (*result_head == NULL) {
        *result_head = new_node;
        *result_tail = new_node;
    } else {
        (*result_tail)->next = new_node;
        *result_tail = new_node;
    }
    return 0;
}

int find_nested_recursive(Node *nested_head, Node *target_head, Node **result_head, Node **result_tail) {
    if (nested_head == NULL) {
        return 0;
    }
    if (exists_in_list(target_head, nested_head->value)) {
        if (append_result(result_head, result_tail, nested_head->value) != 0) {
            return -1;
        }
    }
    if (nested_head->child != NULL) {
        if (find_nested_recursive(nested_head->child, target_head, result_head, result_tail) != 0) {
            return -1;
        }
    }
    if (nested_head->next != NULL) {
        if (find_nested_recursive(nested_head->next, target_head, result_head, result_tail) != 0) {
            return -1;
        }
    }
    return 0;
}

Node *find_nested_in_list(Node *nested_head, Node *target_head) {
    Node *result_head = NULL;
    Node *result_tail = NULL;
    if (find_nested_recursive(nested_head, target_head, &result_head, &result_tail) != 0) {
        free_list(result_head);
        return NULL;
    }
    return result_head;
}

void print_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    Node *t1 = create_node(2);
    Node *t2 = create_node(4);
    Node *t3 = create_node(6);
    if (t1 == NULL || t2 == NULL || t3 == NULL) {
        free_list(t1);
        free_list(t2);
        free_list(t3);
        return EXIT_FAILURE;
    }
    t1->next = t2;
    t2->next = t3;
    Node *target = t1;

    Node *n1 = create_node(1);
    Node *n2 = create_node(2);
    Node *n3 = create_node(3);
    Node *n4 = create_node(4);
    Node *n5 = create_node(5);
    if (n1 == NULL || n2 == NULL || n3 == NULL || n4 == NULL || n5 == NULL) {
        free_list(target);
        free_list(n1);
        free_list(n2);
        free_list(n3);
        free_list(n4);
        free_list(n5);
        return EXIT_FAILURE;
    }
    n1->next = n2;
    n2->next = n3;
    n2->child = n4;
    n4->next = n5;
    Node *nested = n1;

    Node *result = find_nested_in_list(nested, target);
    if (result != NULL) {
        print_list(result);
        free_list(result);
    }

    free_list(nested);
    free_list(target);

    return EXIT_SUCCESS;
}