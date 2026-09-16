#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Node {
    double value;
    struct Node *next;
} Node;

Node* create_node(double value) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) return NULL;
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

void add_to_list(Node **list, double value) {
    Node *new_node = create_node(value);
    if (*list == NULL) {
        *list = new_node;
    } else {
        Node *temp = *list;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

Node* map_powers(const double *bases, size_t base_count, const int *indices, size_t index_count) {
    if (base_count != index_count) return NULL;
    
    Node *result_list = NULL;
    for (size_t i = 0; i < base_count; ++i) {
        double power = pow(bases[i], indices[i]);
        add_to_list(&result_list, power);
    }
    return result_list;
}

void print_list(Node *list) {
    while (list != NULL) {
        printf("%.2f -> ", list->value);
        list = list->next;
    }
    printf("NULL\n");
}

void free_list(Node *list) {
    Node *current = list;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
}

int main() {
    double bases[] = {2.0, 3.0, 4.0};
    int indices[] = {1, 2, 3};
    size_t count = sizeof(bases) / sizeof(bases[0]);

    Node *mapped_list = map_powers(bases, count, indices, count);

    print_list(mapped_list);
    free_list(mapped_list);

    return 0;
}