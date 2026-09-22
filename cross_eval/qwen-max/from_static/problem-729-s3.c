#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void add_to_list(Node** head, int data) {
    Node* new_node = create_node(data);
    if (*head == NULL) {
        *head = new_node;
    } else {
        Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

Node* add_lists(Node* list1, Node* list2) {
    Node* result = NULL;
    Node* current1 = list1;
    Node* current2 = list2;
    
    while (current1 != NULL || current2 != NULL) {
        int sum = (current1 ? current1->data : 0) + (current2 ? current2->data : 0);
        add_to_list(&result, sum);
        
        if (current1) current1 = current1->next;
        if (current2) current2 = current2->next;
    }
    
    return result;
}

void free_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    Node* list1 = NULL;
    add_to_list(&list1, 1);
    add_to_list(&list1, 2);
    add_to_list(&list1, 3);

    Node* list2 = NULL;
    add_to_list(&list2, 4);
    add_to_list(&list2, 5);
    add_to_list(&list2, 6);

    Node* result = add_lists(list1, list2);

    for (Node* current = result; current != NULL; current = current->next) {
        printf("%d ", current->data);
    }

    free_list(list1);
    free_list(list2);
    free_list(result);

    return 0;
}