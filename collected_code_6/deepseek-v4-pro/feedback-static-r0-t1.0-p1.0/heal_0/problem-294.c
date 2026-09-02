#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_DOUBLE
} DataType;

typedef struct Node {
    DataType type;
    union {
        int int_value;
        float float_value;
        double double_value;
    } data;
    struct Node* next;
} Node;

Node* create_int_node(int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) return NULL;
    node->type = TYPE_INT;
    node->data.int_value = value;
    node->next = NULL;
    return node;
}

Node* create_float_node(float value) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) return NULL;
    node->type = TYPE_FLOAT;
    node->data.float_value = value;
    node->next = NULL;
    return node;
}

Node* create_double_node(double value) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) return NULL;
    node->type = TYPE_DOUBLE;
    node->data.double_value = value;
    node->next = NULL;
    return node;
}

void append_node(Node** head, Node* new_node) {
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}

void free_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

double node_to_double(const Node* node) {
    switch (node->type) {
        case TYPE_INT:
            return (double)node->data.int_value;
        case TYPE_FLOAT:
            return (double)node->data.float_value;
        case TYPE_DOUBLE:
            return node->data.double_value;
        default:
            return 0.0;
    }
}

int find_max_in_heterogeneous_list(Node* head, double* max_value) {
    if (head == NULL || max_value == NULL) {
        return 0;
    }

    double max = node_to_double(head);
    Node* current = head->next;

    while (current != NULL) {
        double value = node_to_double(current);
        if (value > max) {
            max = value;
        }
        current = current->next;
    }

    *max_value = max;
    return 1;
}

int main(void) {
    Node* list = NULL;
    double max_value;
    int max_found;

    Node* node1 = create_int_node(42);
    Node* node2 = create_float_node(3.14f);
    Node* node3 = create_double_node(2.71828);
    Node* node4 = create_int_node(100);
    Node* node5 = create_float_node(99.99f);
    Node* node6 = create_double_node(150.5);

    if (node1 == NULL || node2 == NULL || node3 == NULL || 
        node4 == NULL || node5 == NULL || node6 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free_list(list);
        return 1;
    }

    append_node(&list, node1);
    append_node(&list, node2);
    append_node(&list, node3);
    append_node(&list, node4);
    append_node(&list, node5);
    append_node(&list, node6);

    max_found = find_max_in_heterogeneous_list(list, &max_value);
    if (max_found) {
        printf("Maximum value: %.5f\n", max_value);
    } else {
        printf("List is empty or invalid parameters\n");
    }

    free_list(list);
    return 0;
}