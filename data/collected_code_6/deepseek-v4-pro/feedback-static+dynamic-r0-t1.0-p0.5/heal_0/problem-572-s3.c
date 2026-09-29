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

void append_node(Node** head, int data) {
    Node* new_node = create_node(data);
    if (new_node == NULL) {
        return;
    }
    
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    
    Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}

void free_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

void remove_two_duplicates(Node** head) {
    if (*head == NULL || (*head)->next == NULL) {
        return;
    }
    
    Node* current = *head;
    Node* prev = NULL;
    
    while (current != NULL && current->next != NULL) {
        if (current->data == current->next->data) {
            int duplicate_value = current->data;
            Node* temp = current;
            
            while (temp != NULL && temp->data == duplicate_value) {
                Node* to_delete = temp;
                temp = temp->next;
                free(to_delete);
            }
            
            if (prev == NULL) {
                *head = temp;
            } else {
                prev->next = temp;
            }
            
            current = temp;
        } else {
            prev = current;
            current = current->next;
        }
    }
}

void print_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    Node* list1 = NULL;
    Node* list2 = NULL;
    Node* list3 = NULL;
    
    append_node(&list1, 1);
    append_node(&list1, 2);
    append_node(&list1, 2);
    append_node(&list1, 3);
    append_node(&list1, 4);
    append_node(&list1, 4);
    append_node(&list1, 5);
    
    append_node(&list2, 1);
    append_node(&list2, 1);
    append_node(&list2, 2);
    append_node(&list2, 3);
    append_node(&list2, 3);
    append_node(&list2, 3);
    append_node(&list2, 4);
    
    append_node(&list3, 5);
    append_node(&list3, 5);
    append_node(&list3, 5);
    append_node(&list3, 6);
    append_node(&list3, 7);
    append_node(&list3, 7);
    
    printf("Original lists:\n");
    print_list(list1);
    print_list(list2);
    print_list(list3);
    
    remove_two_duplicates(&list1);
    remove_two_duplicates(&list2);
    remove_two_duplicates(&list3);
    
    printf("\nLists after removing duplicates:\n");
    print_list(list1);
    print_list(list2);
    print_list(list3);
    
    free_list(list1);
    free_list(list2);
    free_list(list3);
    
    return 0;
}