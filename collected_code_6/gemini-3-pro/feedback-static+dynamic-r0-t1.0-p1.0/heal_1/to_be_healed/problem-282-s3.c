#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void append(Node** head, int data) {
    if (!head) {
        return;
    }
    Node* new_node = create_node(data);
    if (!*head) {
        *head = new_node;
        return;
    }
    Node* temp = *head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = new_node;
}

void free_list(Node* head) {
    /* Possible weaknesses found:
     *  The scope of the variable 'temp' can be reduced. [variableScope]
     */
    Node* temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int contains(Node* head, int data) {
    while (head) {
        if (head->data == data) {
            return 1;
        }
        head = head->next;
    }
    return 0;
}

Node* subtract_lists(Node* list1, Node* list2) {
    Node* result = NULL;
    Node* temp = list1;
    
    while (temp) {
        if (!contains(list2, temp->data) && !contains(result, temp->data)) {
            append(&result, temp->data);
        }
        temp = temp->next;
    }
    
    return result;
}

void print_list(Node* head) {
    while (head) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main(void) {
    Node* list1 = NULL;
    Node* list2 = NULL;
    Node* result = NULL;

    append(&list1, 1);
    append(&list1, 2);
    append(&list1, 3);
    append(&list1, 4);
    append(&list1, 5);

    append(&list2, 2);
    append(&list2, 4);
    append(&list2, 6);

    result = subtract_lists(list1, list2);

    print_list(result);

    free_list(list1);
    free_list(list2);
    free_list(result);

    return EXIT_SUCCESS;
}