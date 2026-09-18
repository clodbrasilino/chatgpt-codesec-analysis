#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

void free_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* next_node = current->next;
        free(current);
        current = next_node;
    }
}

int insert_back(Node** head, int value) {
    if (head == NULL) {
        return -1;
    }
    
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        return -1;
    }
    
    new_node->data = value;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
    } else {
        Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    
    return 0;
}

int subtract_lists(const Node* list1, const Node* list2, Node** result_out) {
    if (result_out == NULL) {
        return -1;
    }

    *result_out = NULL;
    Node* result_tail = NULL;
    const Node* curr1 = list1;
    const Node* curr2 = list2;

    while (curr1 != NULL && curr2 != NULL) {
        Node* new_node = (Node*)malloc(sizeof(Node));
        if (new_node == NULL) {
            free_list(*result_out);
            *result_out = NULL;
            return -1;
        }

        new_node->data = curr1->data - curr2->data;
        new_node->next = NULL;

        if (*result_out == NULL) {
            *result_out = new_node;
            result_tail = new_node;
        } else {
            result_tail->next = new_node;
            result_tail = new_node;
        }

        curr1 = curr1->next;
        curr2 = curr2->next;
    }

    return 0;
}

void print_list(const Node* head) {
    const Node* current = head;
    while (current != NULL) {
        printf("%d\n", current->data);
        current = current->next;
    }
}

int main(void) {
    Node* list1 = NULL;
    Node* list2 = NULL;
    Node* result = NULL;
    int status = EXIT_SUCCESS;

    if (insert_back(&list1, 10) != 0) status = EXIT_FAILURE;
    if (status == EXIT_SUCCESS && insert_back(&list1, 20) != 0) status = EXIT_FAILURE;
    if (status == EXIT_SUCCESS && insert_back(&list1, 30) != 0) status = EXIT_FAILURE;

    if (status == EXIT_SUCCESS && insert_back(&list2, 5) != 0) status = EXIT_FAILURE;
    if (status == EXIT_SUCCESS && insert_back(&list2, 12) != 0) status = EXIT_FAILURE;
    if (status == EXIT_SUCCESS && insert_back(&list2, 18) != 0) status = EXIT_FAILURE;

    if (status == EXIT_SUCCESS && subtract_lists(list1, list2, &result) != 0) {
        status = EXIT_FAILURE;
    }

    if (status == EXIT_SUCCESS) {
        print_list(result);
    }

    free_list(list1);
    free_list(list2);
    free_list(result);

    return status;
}