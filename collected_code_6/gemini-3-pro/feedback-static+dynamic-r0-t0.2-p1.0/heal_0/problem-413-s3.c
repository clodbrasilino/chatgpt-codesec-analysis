#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct Node {
    Tuple data;
    struct Node* next;
} Node;

Tuple* extract_nth_element(Node* head, int n) {
    if (head == NULL || n < 0) {
        return NULL;
    }

    Node* current = head;
    int count = 0;

    while (current != NULL) {
        if (count == n) {
            Tuple* result = (Tuple*)malloc(sizeof(Tuple));
            if (result == NULL) {
                return NULL;
            }
            result->first = current->data.first;
            result->second = current->data.second;
            return result;
        }
        count++;
        current = current->next;
    }

    return NULL;
}

Node* create_node(int first, int second) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data.first = first;
    new_node->data.second = second;
    new_node->next = NULL;
    return new_node;
}

void free_list(Node* head) {
    Node* current = head;
    Node* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

int main(void) {
    Node* head = create_node(1, 2);
    if (head == NULL) return 1;
    
    head->next = create_node(3, 4);
    if (head->next == NULL) {
        free_list(head);
        return 1;
    }
    
    head->next->next = create_node(5, 6);
    if (head->next->next == NULL) {
        free_list(head);
        return 1;
    }

    int n = 1;
    Tuple* nth_tuple = extract_nth_element(head, n);

    if (nth_tuple != NULL) {
        printf("Element at index %d: (%d, %d)\n", n, nth_tuple->first, nth_tuple->second);
        free(nth_tuple);
    } else {
        printf("Element at index %d not found.\n", n);
    }

    free_list(head);

    return 0;
}