#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Sublist {
    Node* head;
    struct Sublist* next;
} Sublist;

int* get_first_elements(Sublist* list, int* count) {
    if (!list || !count) {
        if (count) *count = 0;
        return NULL;
    }

    int num_sublists = 0;
    Sublist* current_sublist = list;
    while (current_sublist) {
        num_sublists++;
        current_sublist = current_sublist->next;
    }

    int* first_elements = (int*)malloc(num_sublists * sizeof(int));
    if (!first_elements) {
        *count = 0;
        return NULL;
    }

    current_sublist = list;
    int index = 0;
    while (current_sublist) {
        if (current_sublist->head) {
            first_elements[index] = current_sublist->head->data;
        } else {
            first_elements[index] = 0; 
        }
        index++;
        current_sublist = current_sublist->next;
    }

    *count = num_sublists;
    return first_elements;
}

void free_sublists(Sublist* list) {
    while (list) {
        Node* current_node = list->head;
        while (current_node) {
            Node* temp_node = current_node;
            current_node = current_node->next;
            free(temp_node);
        }
        Sublist* temp_sublist = list;
        list = list->next;
        free(temp_sublist);
    }
}

int main() {
    Sublist* list = (Sublist*)malloc(sizeof(Sublist));
    if (!list) return 1;
    
    list->head = (Node*)malloc(sizeof(Node));
    if (!list->head) {
        free(list);
        return 1;
    }
    list->head->data = 10;
    list->head->next = NULL;
    
    list->next = (Sublist*)malloc(sizeof(Sublist));
    if (!list->next) {
        free_sublists(list);
        return 1;
    }
    
    list->next->head = (Node*)malloc(sizeof(Node));
    if (!list->next->head) {
        free_sublists(list);
        return 1;
    }
    list->next->head->data = 20;
    list->next->head->next = NULL;
    list->next->next = NULL;

    int count = 0;
    int* first_elements = get_first_elements(list, &count);

    if (first_elements) {
        for (int i = 0; i < count; i++) {
            printf("%d\n", first_elements[i]);
        }
        free(first_elements);
    }

    free_sublists(list);

    return 0;
}