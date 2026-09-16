#include <stdio.h>
#include <stdlib.h>

typedef enum { NODE_INT, NODE_TUPLE } NodeType;

typedef struct Node {
    NodeType type;
    union {
        int value;
        struct {
            struct Node *items;
            size_t count;
        } tuple;
    };
} Node;

Node create_int_node(int val) {
    Node n;
    n.type = NODE_INT;
    n.value = val;
    return n;
}

Node create_tuple_node(Node *items, size_t count) {
    Node n;
    n.type = NODE_TUPLE;
    n.tuple.items = items;
    n.tuple.count = count;
    return n;
}

typedef struct {
    int *even_numbers;
    size_t count;
    size_t capacity;
} EvenResult;

EvenResult extract_even(Node node) {
    EvenResult result;
    result.even_numbers = (int *)malloc(16 * sizeof(int));
    if (result.even_numbers == NULL) {
        result.count = 0;
        result.capacity = 0;
        return result;
    }
    result.count = 0;
    result.capacity = 16;

    if (node.type == NODE_INT) {
        if (node.value % 2 == 0) {
            result.even_numbers[0] = node.value;
            result.count = 1;
        }
    } else if (node.type == NODE_TUPLE) {
        for (size_t i = 0; i < node.tuple.count; i++) {
            EvenResult sub_result = extract_even(node.tuple.items[i]);
            for (size_t j = 0; j < sub_result.count; j++) {
                if (result.count >= result.capacity) {
                    size_t new_capacity = result.capacity * 2;
                    int *temp = (int *)realloc(result.even_numbers, new_capacity * sizeof(int));
                    if (temp == NULL) {
                        free(sub_result.even_numbers);
                        result.count = 0;
                        return result;
                    }
                    result.even_numbers = temp;
                    result.capacity = new_capacity;
                }
                result.even_numbers[result.count++] = sub_result.even_numbers[j];
            }
            free(sub_result.even_numbers);
        }
    }

    return result;
}

void free_node(Node node) {
    if (node.type == NODE_TUPLE) {
        for (size_t i = 0; i < node.tuple.count; i++) {
            free_node(node.tuple.items[i]);
        }
        free(node.tuple.items);
    }
}

int main(void) {
    Node inner_items[2];
    inner_items[0] = create_int_node(1);
    inner_items[1] = create_int_node(4);

    Node *outer_items = (Node *)malloc(3 * sizeof(Node));
    if (outer_items == NULL) {
        return 1;
    }
    outer_items[0] = create_int_node(2);
    outer_items[1] = create_tuple_node(inner_items, 2);
    outer_items[2] = create_int_node(6);

    Node root = create_tuple_node(outer_items, 3);

    EvenResult res = extract_even(root);

    for (size_t i = 0; i < res.count; i++) {
        printf("%d ", res.even_numbers[i]);
    }
    printf("\n");

    free(res.even_numbers);
    free_node(root);

    return 0;
}