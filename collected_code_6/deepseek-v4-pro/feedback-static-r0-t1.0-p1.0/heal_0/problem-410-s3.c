#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_CHAR
} DataType;

typedef struct Node {
    DataType type;
    union {
        int int_val;
        float float_val;
        double double_val;
        char char_val;
    } data;
    struct Node *next;
} Node;

double get_numeric_value(const Node *node) {
    if (node == NULL) {
        fprintf(stderr, "Error: Null node encountered\n");
        exit(EXIT_FAILURE);
    }
    
    switch (node->type) {
        case TYPE_INT:
            return (double)node->data.int_val;
        case TYPE_FLOAT:
            return (double)node->data.float_val;
        case TYPE_DOUBLE:
            return node->data.double_val;
        case TYPE_CHAR:
            return (double)node->data.char_val;
        default:
            fprintf(stderr, "Error: Unknown data type\n");
            exit(EXIT_FAILURE);
    }
}

double find_minimum(const Node *head) {
    if (head == NULL) {
        fprintf(stderr, "Error: Empty list\n");
        exit(EXIT_FAILURE);
    }
    
    double min_value = get_numeric_value(head);
    const Node *current = head->next;
    
    while (current != NULL) {
        double current_value = get_numeric_value(current);
        if (current_value < min_value) {
            min_value = current_value;
        }
        current = current->next;
    }
    
    return min_value;
}

Node *create_int_node(int value) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->type = TYPE_INT;
    node->data.int_val = value;
    node->next = NULL;
    return node;
}

Node *create_float_node(float value) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->type = TYPE_FLOAT;
    node->data.float_val = value;
    node->next = NULL;
    return node;
}

Node *create_double_node(double value) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->type = TYPE_DOUBLE;
    node->data.double_val = value;
    node->next = NULL;
    return node;
}

Node *create_char_node(char value) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->type = TYPE_CHAR;
    node->data.char_val = value;
    node->next = NULL;
    return node;
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
}

int main(void) {
    Node *head = create_int_node(42);
    head->next = create_float_node(3.14f);
    head->next->next = create_double_node(2.71828);
    head->next->next->next = create_char_node('A');
    head->next->next->next->next = create_int_node(-10);
    
    double min_value = find_minimum(head);
    printf("Minimum value: %.6f\n", min_value);
    
    free_list(head);
    
    return 0;
}