#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void free_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* next_node = current->next;
        free(current);
        current = next_node;
    }
}

void print_list(const Node* head) {
    const Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

Node* divide_lists(const Node* numerator, const Node* denominator) {
    if (numerator == NULL || denominator == NULL) {
        return NULL;
    }

    Node* result_head = NULL;
    Node* result_tail = NULL;

    const Node* curr_num = numerator;
    const Node* curr_den = denominator;

    while (curr_num != NULL && curr_den != NULL) {
        if (curr_den->data == 0) {
            free_list(result_head);
            return NULL;
        }

        Node* new_node = create_node(curr_num->data / curr_den->data);
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

        curr_num = curr_num->next;
        curr_den = curr_den->next;
    }

    return result_head;
}

int main(void) {
    Node* list1 = create_node(10);
    if (list1 == NULL) {
        return EXIT_FAILURE;
    }
    list1->next = create_node(20);
    if (list1->next == NULL) {
        free_list(list1);
        return EXIT_FAILURE;
    }
    list1->next->next = create_node(30);
    if (list1->next->next == NULL) {
        free_list(list1);
        return EXIT_FAILURE;
    }

    Node* list2 = create_node(2);
    if (list2 == NULL) {
        free_list(list1);
        return EXIT_FAILURE;
    }
    list2->next = create_node(5);
    if (list2->next == NULL) {
        free_list(list1);
        free_list(list2);
        return EXIT_FAILURE;
    }
    list2->next->next = create_node(6);
    if (list2->next->next == NULL) {
        free_list(list1);
        free_list(list2);
        return EXIT_FAILURE;
    }

    Node* result = divide_lists(list1, list2);
    if (result != NULL) {
        print_list(result);
    }

    free_list(list1);
    free_list(list2);
    free_list(result);

    return EXIT_SUCCESS;
}