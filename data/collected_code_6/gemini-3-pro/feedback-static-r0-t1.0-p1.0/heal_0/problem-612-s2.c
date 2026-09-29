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

typedef struct {
    Node* first_elements;
    Node* last_elements;
} MergedLists;

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void append_node(Node** head, int data) {
    if (!head) return;
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

List* create_list_node(Node* head) {
    List* new_list = (List*)malloc(sizeof(List));
    if (!new_list) {
        exit(EXIT_FAILURE);
    }
    new_list->head = head;
    new_list->next = NULL;
    return new_list;
}

void append_list(List** head, Node* list_head) {
    if (!head) return;
    List* new_list = create_list_node(list_head);
    if (!*head) {
        *head = new_list;
        return;
    }
    List* temp = *head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = new_list;
}

void free_nodes(Node* head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

void free_lists(List* head) {
    while (head) {
        List* temp = head;
        free_nodes(head->head);
        head = head->next;
        free(temp);
    }
}

MergedLists merge_first_and_last(List* lists) {
    MergedLists result = {NULL, NULL};
    List* current_list = lists;

    while (current_list) {
        Node* current_node = current_list->head;
        if (current_node) {
            append_node(&(result.first_elements), current_node->data);
            
            while (current_node->next) {
                current_node = current_node->next;
            }
            append_node(&(result.last_elements), current_node->data);
        }
        current_list = current_list->next;
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
    List* lists = NULL;
    
    Node* list1 = NULL;
    append_node(&list1, 1);
    append_node(&list1, 2);
    append_node(&list1, 3);
    
    Node* list2 = NULL;
    append_node(&list2, 4);
    append_node(&list2, 5);
    
    Node* list3 = NULL;
    append_node(&list3, 6);
    
    append_list(&lists, list1);
    append_list(&lists, list2);
    append_list(&lists, list3);

    MergedLists merged = merge_first_and_last(lists);

    print_list(merged.first_elements);
    print_list(merged.last_elements);

    free_nodes(merged.first_elements);
    free_nodes(merged.last_elements);
    free_lists(lists);

    return 0;
}