#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>

typedef enum {
    TYPE_INT,
    TYPE_DOUBLE,
    TYPE_FLOAT,
    TYPE_LONG,
    TYPE_CHAR
} DataType;

typedef union {
    int int_val;
    double double_val;
    float float_val;
    long long_val;
    char char_val;
} DataValue;

typedef struct Node {
    DataType type;
    DataValue value;
    struct Node *next;
} Node;

static double node_to_double(const Node *node) {
    switch (node->type) {
        case TYPE_INT:
            return (double)node->value.int_val;
        case TYPE_DOUBLE:
            return node->value.double_val;
        case TYPE_FLOAT:
            return (double)node->value.float_val;
        case TYPE_LONG:
            return (double)node->value.long_val;
        case TYPE_CHAR:
            return (double)node->value.char_val;
        default:
            return -DBL_MAX;
    }
}

double find_max_value(const Node *head) {
    if (head == NULL) {
        fprintf(stderr, "Error: Empty list\n");
        exit(EXIT_FAILURE);
    }

    double max_val = node_to_double(head);
    const Node *current = head->next;

    while (current != NULL) {
        double current_val = node_to_double(current);
        if (current_val > max_val) {
            max_val = current_val;
        }
        current = current->next;
    }

    return max_val;
}

Node *create_node(DataType type, DataValue value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->type = type;
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}

int main(void) {
    Node *head = NULL;
    Node *tail = NULL;
    DataValue val;

    val.int_val = 42;
    head = create_node(TYPE_INT, val);
    tail = head;

    val.double_val = 75.5;
    tail->next = create_node(TYPE_DOUBLE, val);
    tail = tail->next;

    val.float_val = 10.2f;
    tail->next = create_node(TYPE_FLOAT, val);
    tail = tail->next;

    val.long_val = 100L;
    tail->next = create_node(TYPE_LONG, val);
    tail = tail->next;

    val.char_val = 'Z';
    tail->next = create_node(TYPE_CHAR, val);

    double max_val = find_max_value(head);
    printf("Maximum value: %.2f\n", max_val);

    free_list(head);
    return 0;
}