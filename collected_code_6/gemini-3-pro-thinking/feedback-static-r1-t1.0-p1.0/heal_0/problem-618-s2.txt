#include <stdlib.h>

typedef struct Node {
    double data;
    struct Node* next;
} Node;

void free_list(Node* head) {
    Node* current = head;
    Node* next_node = NULL;

    while (current != NULL) {
        next_node = current->next;
        free(current);
        current = next_node;
    }
}

Node* create_node(double data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }

    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

Node* divide_lists(const Node* numerator, const Node* denominator) {
    if (numerator == NULL || denominator == NULL) {
        return NULL;
    }

    Node* result_head = NULL;
    Node* result_tail = NULL;

    while (numerator != NULL && denominator != NULL) {
        if (denominator->data == 0.0) {
            free_list(result_head);
            return NULL;
        }

        Node* new_node = create_node(numerator->data / denominator->data);
        if (new_node == NULL) {
            free_list(result_head);
            return NULL;
        }

        if (result_head == NULL) {
            result_head = new_node;
            result_tail = new_node;
        } else {
            result_tail->next = new_node;
            result_tail = new_node;
        }

        numerator = numerator->next;
        denominator = denominator->next;
    }

    if (numerator != NULL || denominator != NULL) {
        free_list(result_head);
        return NULL;
    }

    return result_head;
}

int main(void) {
    Node* num_head = create_node(10.0);
    if (num_head == NULL) {
        return EXIT_FAILURE;
    }
    
    num_head->next = create_node(20.0);
    if (num_head->next == NULL) {
        free_list(num_head);
        return EXIT_FAILURE;
    }

    Node* den_head = create_node(2.0);
    if (den_head == NULL) {
        free_list(num_head);
        return EXIT_FAILURE;
    }
    
    den_head->next = create_node(5.0);
    if (den_head->next == NULL) {
        free_list(num_head);
        free_list(den_head);
        return EXIT_FAILURE;
    }

    Node* result_head = divide_lists(num_head, den_head);
    if (result_head == NULL) {
        free_list(num_head);
        free_list(den_head);
        return EXIT_FAILURE;
    }

    free_list(num_head);
    free_list(den_head);
    free_list(result_head);

    return EXIT_SUCCESS;
}