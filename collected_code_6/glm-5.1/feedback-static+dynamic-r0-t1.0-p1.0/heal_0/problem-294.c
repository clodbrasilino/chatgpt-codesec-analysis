#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    TYPE_INT,
    TYPE_FLOAT
} DataType;

typedef struct Node {
    DataType type;
    union {
        int int_val;
        float float_val;
    } data;
    struct Node *next;
} Node;

Node *create_int_node(int val, Node *next) {
    Node *n = malloc(sizeof(Node));
    if (!n) return NULL;
    n->type = TYPE_INT;
    n->data.int_val = val;
    n->next = next;
    return n;
}

Node *create_float_node(float val, Node *next) {
    Node *n = malloc(sizeof(Node));
    if (!n) return NULL;
    n->type = TYPE_FLOAT;
    n->data.float_val = val;
    n->next = next;
    return n;
}

float find_max(Node *head) {
    if (!head) return 0.0f;
    float max_val;
    if (head->type == TYPE_INT) {
        max_val = (float)head->data.int_val;
    } else {
        max_val = head->data.float_val;
    }
    Node *current = head->next;
    while (current) {
        float current_val;
        if (current->type == TYPE_INT) {
            current_val = (float)current->data.int_val;
        } else {
            current_val = current->data.float_val;
        }
        if (current_val > max_val) {
            max_val = current_val;
        }
        current = current->next;
    }
    return max_val;
}

void free_list(Node *head) {
    Node *current = head;
    while (current) {
        Node *next = current->next;
        free(current);
        current = next;
    }
}

int main(void) {
    Node *list = create_int_node(10, 
                    create_float_node(25.5f, 
                        create_int_node(-5, 
                            create_float_node(15.2f, NULL))));
    if (!list) {
        return 1;
    }
    float max_val = find_max(list);
    printf("Maximum value: %.2f\n", max_val);
    free_list(list);
    return 0;
}