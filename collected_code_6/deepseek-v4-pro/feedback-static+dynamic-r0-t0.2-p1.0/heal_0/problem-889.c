#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
    struct List *next;
} List;

Node *reverse_list(Node *head) {
    Node *prev = NULL;
    Node *current = head;
    Node *next = NULL;
    
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    
    return prev;
}

void reverse_all_lists(List *list_of_lists) {
    List *current_list = list_of_lists;
    
    while (current_list != NULL) {
        current_list->head = reverse_list(current_list->head);
        current_list = current_list->next;
    }
}

Node *create_node(int data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

List *create_list(void) {
    List *new_list = (List *)malloc(sizeof(List));
    if (new_list == NULL) {
        return NULL;
    }
    new_list->head = NULL;
    new_list->next = NULL;
    return new_list;
}

void append_node(Node **head, int data) {
    Node *new_node = create_node(data);
    if (new_node == NULL) {
        return;
    }
    
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    
    Node *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}

void print_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}

void free_all_lists(List *list_of_lists) {
    List *current_list = list_of_lists;
    while (current_list != NULL) {
        List *temp_list = current_list;
        free_list(current_list->head);
        current_list = current_list->next;
        free(temp_list);
    }
}

int main(void) {
    List *list_of_lists = create_list();
    if (list_of_lists == NULL) {
        return 1;
    }
    
    List *list1 = create_list();
    if (list1 == NULL) {
        free(list_of_lists);
        return 1;
    }
    append_node(&(list1->head), 1);
    append_node(&(list1->head), 2);
    append_node(&(list1->head), 3);
    
    List *list2 = create_list();
    if (list2 == NULL) {
        free_list(list1->head);
        free(list1);
        free(list_of_lists);
        return 1;
    }
    append_node(&(list2->head), 4);
    append_node(&(list2->head), 5);
    
    List *list3 = create_list();
    if (list3 == NULL) {
        free_list(list1->head);
        free(list1);
        free_list(list2->head);
        free(list2);
        free(list_of_lists);
        return 1;
    }
    append_node(&(list3->head), 6);
    append_node(&(list3->head), 7);
    append_node(&(list3->head), 8);
    append_node(&(list3->head), 9);
    
    list_of_lists->head = list1->head;
    list_of_lists->next = list2;
    list2->next = list3;
    
    printf("Original lists:\n");
    List *current = list_of_lists;
    while (current != NULL) {
        print_list(current->head);
        current = current->next;
    }
    
    reverse_all_lists(list_of_lists);
    
    printf("\nReversed lists:\n");
    current = list_of_lists;
    while (current != NULL) {
        print_list(current->head);
        current = current->next;
    }
    
    free_all_lists(list_of_lists);
    
    return 0;
}