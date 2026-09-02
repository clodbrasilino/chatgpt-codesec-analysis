#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
    struct List* next;
} List;

int count_frequency(List* list_of_lists, int target) {
    int frequency = 0;
    List* current_list = list_of_lists;
    
    while (current_list != NULL) {
        Node* current_node = current_list->head;
        while (current_node != NULL) {
            if (current_node->data == target) {
                frequency++;
            }
            current_node = current_node->next;
        }
        current_list = current_list->next;
    }
    
    return frequency;
}

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

List* create_list() {
    List* new_list = (List*)malloc(sizeof(List));
    if (new_list == NULL) {
        return NULL;
    }
    new_list->head = NULL;
    new_list->next = NULL;
    return new_list;
}

void add_to_list(List* list, int data) {
    Node* new_node = create_node(data);
    if (new_node == NULL) {
        return;
    }
    
    if (list->head == NULL) {
        list->head = new_node;
    } else {
        Node* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

void free_list(List* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

void free_all_lists(List* list_of_lists) {
    List* current = list_of_lists;
    while (current != NULL) {
        List* temp = current;
        free_list(current);
        current = current->next;
        free(temp);
    }
}

int main() {
    List* list1 = create_list();
    List* list2 = create_list();
    List* list3 = create_list();
    
    if (list1 == NULL || list2 == NULL || list3 == NULL) {
        if (list1 != NULL) free(list1);
        if (list2 != NULL) free(list2);
        if (list3 != NULL) free(list3);
        return 1;
    }
    
    add_to_list(list1, 1);
    add_to_list(list1, 2);
    add_to_list(list1, 3);
    add_to_list(list1, 2);
    
    add_to_list(list2, 2);
    add_to_list(list2, 5);
    add_to_list(list2, 2);
    
    add_to_list(list3, 7);
    add_to_list(list3, 8);
    add_to_list(list3, 2);
    
    list1->next = list2;
    list2->next = list3;
    
    int target = 2;
    int result = count_frequency(list1, target);
    printf("Frequency of %d: %d\n", target, result);
    
    free_all_lists(list1);
    
    return 0;
}