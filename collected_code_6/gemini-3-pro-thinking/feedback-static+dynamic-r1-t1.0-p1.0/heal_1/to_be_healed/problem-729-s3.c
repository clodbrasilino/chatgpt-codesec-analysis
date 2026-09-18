#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

Node* create_node(int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

void free_list(Node* head) {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

int append_node(Node** head, int value) {
    if (head == NULL) {
        return -1;
    }
    Node* new_node = create_node(value);
    if (new_node == NULL) {
        return -1;
    }
    if (*head == NULL) {
        *head = new_node;
        return 0;
    }
    Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
    return 0;
}

Node* add_lists(const Node* l1, const Node* l2) {
    Node* head = NULL;
    Node** tail = &head;
    int carry = 0;

    while (l1 != NULL || l2 != NULL || carry != 0) {
        int sum = carry;
        if (l1 != NULL) {
            sum += l1->value;
            l1 = l1->next;
        }
        if (l2 != NULL) {
            sum += l2->value;
            l2 = l2->next;
        }
        
        carry = sum / 10;
        
        Node* new_node = create_node(sum % 10);
        if (new_node == NULL) {
            free_list(head);
            return NULL;
        }
        
        *tail = new_node;
        tail = &(new_node->next);
    }

    return head;
}

int main(void) {
    Node* l1 = NULL;
    Node* l2 = NULL;
    Node* result = NULL;

    if (append_node(&l1, 2) != 0 || append_node(&l1, 4) != 0 || append_node(&l1, 3) != 0) {
        free_list(l1);
        return EXIT_FAILURE;
    }

    if (append_node(&l2, 5) != 0 || append_node(&l2, 6) != 0 || append_node(&l2, 4) != 0) {
        free_list(l1);
        free_list(l2);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  Assignment 'result=add_lists(l1,l2)', assigned value is 0
     *  Calling function 'add_lists' returns 0
     */
    result = add_lists(l1, l2);
    /* Possible weaknesses found:
     *  Condition 'result==NULL' is always true
     *  Condition 'result==NULL' is always true [knownConditionTrueFalse]
     */
    if (result == NULL) {
        free_list(l1);
        free_list(l2);
        return EXIT_FAILURE;
    }

    const Node* current = result;
    while (current != NULL) {
        printf("%d", current->value);
        current = current->next;
        if (current != NULL) {
            printf(" -> ");
        }
    }
    printf("\n");

    free_list(l1);
    free_list(l2);
    free_list(result);

    return EXIT_SUCCESS;
}