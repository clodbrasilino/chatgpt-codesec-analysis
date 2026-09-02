#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_LONG
} DataType;

typedef struct Node {
    DataType type;
    union {
        int int_val;
        float float_val;
        double double_val;
        long long_val;
    } data;
    struct Node *next;
} Node;

double node_to_double(const Node *node) {
    if (!node) return (double)LLONG_MAX;
    
    switch (node->type) {
        case TYPE_INT:
            return (double)node->data.int_val;
        case TYPE_FLOAT:
            return (double)node->data.float_val;
        case TYPE_DOUBLE:
            return node->data.double_val;
        case TYPE_LONG:
            return (double)node->data.long_val;
        default:
            return (double)LLONG_MAX;
    }
}

double find_minimum(const Node *head) {
    if (!head) {
        return (double)LLONG_MAX;
    }
    
    double min_val = node_to_double(head);
    const Node *current = head->next;
    
    while (current) {
        double current_val = node_to_double(current);
        if (current_val < min_val) {
            min_val = current_val;
        }
        current = current->next;
    }
    
    return min_val;
}

Node *create_node(DataType type, void *value) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (!node) return NULL;
    
    node->type = type;
    node->next = NULL;
    
    switch (type) {
        case TYPE_INT:
            node->data.int_val = *(int *)value;
            break;
        case TYPE_FLOAT:
            node->data.float_val = *(float *)value;
            break;
        case TYPE_DOUBLE:
            node->data.double_val = *(double *)value;
            break;
        case TYPE_LONG:
            node->data.long_val = *(long *)value;
            break;
        default:
            free(node);
            return NULL;
    }
    
    return node;
}

void free_list(Node *head) {
    Node *current = head;
    while (current) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}

int main(void) {
    Node *head = NULL;
    
    int int_val = 42;
    float float_val = 3.14f;
    double double_val = -2.718;
    long long_val = 100L;
    
    Node *node1 = create_node(TYPE_INT, &int_val);
    Node *node2 = create_node(TYPE_FLOAT, &float_val);
    Node *node3 = create_node(TYPE_DOUBLE, &double_val);
    Node *node4 = create_node(TYPE_LONG, &long_val);
    
    if (!node1 || !node2 || !node3 || !node4) {
        free_list(node1);
        free_list(node2);
        free_list(node3);
        free_list(node4);
        return 1;
    }
    
    head = node1;
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    
    double min_val = find_minimum(head);
    printf("Minimum value: %f\n", min_val);
    
    free_list(head);
    return 0;
}