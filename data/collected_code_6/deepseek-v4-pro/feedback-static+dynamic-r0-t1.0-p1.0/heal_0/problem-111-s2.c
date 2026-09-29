#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
} List;

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

List* create_list() {
    List* list = (List*)malloc(sizeof(List));
    if (list == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    list->head = NULL;
    return list;
}

void insert_node(List* list, int data) {
    Node* new_node = create_node(data);
    new_node->next = list->head;
    list->head = new_node;
}

int contains(Node* head, int value) {
    Node* current = head;
    while (current != NULL) {
        if (current->data == value) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

List* find_common_elements(List** lists, int num_lists) {
    List* common = create_list();
    
    if (num_lists <= 0 || lists == NULL) {
        return common;
    }
    
    if (num_lists == 1) {
        Node* current = lists[0]->head;
        while (current != NULL) {
            if (!contains(common->head, current->data)) {
                insert_node(common, current->data);
            }
            current = current->next;
        }
        return common;
    }
    
    Node* current = lists[0]->head;
    while (current != NULL) {
        int value = current->data;
        int is_common = 1;
        
        for (int i = 1; i < num_lists; i++) {
            if (!contains(lists[i]->head, value)) {
                is_common = 0;
                break;
            }
        }
        
        if (is_common && !contains(common->head, value)) {
            insert_node(common, value);
        }
        
        current = current->next;
    }
    
    return common;
}

void free_list(List* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

void print_list(List* list) {
    Node* current = list->head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    List* list1 = create_list();
    List* list2 = create_list();
    List* list3 = create_list();
    
    insert_node(list1, 1);
    insert_node(list1, 2);
    insert_node(list1, 3);
    insert_node(list1, 4);
    insert_node(list1, 5);
    
    insert_node(list2, 2);
    insert_node(list2, 3);
    insert_node(list2, 5);
    insert_node(list2, 7);
    insert_node(list2, 9);
    
    insert_node(list3, 2);
    insert_node(list3, 3);
    insert_node(list3, 5);
    insert_node(list3, 11);
    insert_node(list3, 13);
    
    List* lists[] = {list1, list2, list3};
    List* common = find_common_elements(lists, 3);
    
    printf("Common elements: ");
    print_list(common);
    
    free_list(common);
    free_list(list1);
    free_list(list2);
    free_list(list3);
    
    return 0;
}