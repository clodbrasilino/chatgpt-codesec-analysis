#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    double value;
    struct Node* next;
} Node;

typedef enum {
    SUCCESS = 0,
    ERROR_NULL_POINTER,
    ERROR_MEMORY_ALLOCATION,
    ERROR_DIVISION_BY_ZERO,
    ERROR_LENGTH_MISMATCH
} StatusCode;

void free_list(Node* head);
StatusCode append_node(Node** head, Node** tail, double value);
StatusCode divide_lists(const Node* list1, const Node* list2, Node** result);

void free_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
}

StatusCode append_node(Node** head, Node** tail, double value) {
    if (head == NULL || tail == NULL) {
        return ERROR_NULL_POINTER;
    }

    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        return ERROR_MEMORY_ALLOCATION;
    }

    new_node->value = value;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
        *tail = new_node;
    } else {
        (*tail)->next = new_node;
        *tail = new_node;
    }

    return SUCCESS;
}

StatusCode divide_lists(const Node* list1, const Node* list2, Node** result) {
    if (list1 == NULL || list2 == NULL || result == NULL) {
        return ERROR_NULL_POINTER;
    }

    *result = NULL;
    Node* tail = NULL;
    const Node* curr1 = list1;
    const Node* curr2 = list2;

    while (curr1 != NULL && curr2 != NULL) {
        if (curr2->value == 0.0) {
            free_list(*result);
            *result = NULL;
            return ERROR_DIVISION_BY_ZERO;
        }

        Node* new_node = (Node*)malloc(sizeof(Node));
        if (new_node == NULL) {
            free_list(*result);
            *result = NULL;
            return ERROR_MEMORY_ALLOCATION;
        }

        new_node->value = curr1->value / curr2->value;
        new_node->next = NULL;

        if (*result == NULL) {
            *result = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }

        curr1 = curr1->next;
        curr2 = curr2->next;
    }

    if (curr1 != NULL || curr2 != NULL) {
        free_list(*result);
        *result = NULL;
        return ERROR_LENGTH_MISMATCH;
    }

    return SUCCESS;
}

int main(void) {
    Node* list1 = NULL;
    Node* tail1 = NULL;
    Node* list2 = NULL;
    Node* tail2 = NULL;
    Node* result = NULL;
    StatusCode status;

    if (append_node(&list1, &tail1, 10.0) != SUCCESS) {
        goto cleanup;
    }
    if (append_node(&list1, &tail1, 20.0) != SUCCESS) {
        goto cleanup;
    }
    if (append_node(&list1, &tail1, 30.0) != SUCCESS) {
        goto cleanup;
    }

    if (append_node(&list2, &tail2, 2.0) != SUCCESS) {
        goto cleanup;
    }
    if (append_node(&list2, &tail2, 4.0) != SUCCESS) {
        goto cleanup;
    }
    if (append_node(&list2, &tail2, 5.0) != SUCCESS) {
        goto cleanup;
    }

    status = divide_lists(list1, list2, &result);
    if (status == SUCCESS) {
        Node* curr = result;
        while (curr != NULL) {
            printf("%f\n", curr->value);
            curr = curr->next;
        }
    } else {
        printf("Error code: %d\n", status);
    }

cleanup:
    free_list(list1);
    free_list(list2);
    free_list(result);

    return 0;
}