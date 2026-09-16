#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
    size_t length;
} List;

List* find_max_length_list(List** lists, size_t num_lists) {
    if (lists == NULL || num_lists == 0) {
        return NULL;
    }

    List* max_list = lists[0];
    for (size_t i = 1; i < num_lists; ++i) {
        if (lists[i] != NULL && (max_list == NULL || lists[i]->length > max_list->length)) {
            max_list = lists[i];
        }
    }

    return max_list;
}

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node != NULL) {
        new_node->data = data;
        new_node->next = NULL;
    }
    return new_node;
}

void append(List* list, int data) {
    if (list == NULL) return;

    Node* new_node = create_node(data);
    if (new_node == NULL) return;

    if (list->head == NULL) {
        list->head = new_node;
    } else {
        Node* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    list->length++;
}

void free_list(List* list) {
    if (list == NULL) return;
    Node* current = list->head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

int main() {
    List* list1 = (List*)malloc(sizeof(List));
    if (list1 == NULL) return 1;
    list1->head = NULL;
    list1->length = 0;
    
    List* list2 = (List*)malloc(sizeof(List));
    if (list2 == NULL) {
        free_list(list1);
        return 1;
    }
    list2->head = NULL;
    list2->length = 0;

    List* list3 = (List*)malloc(sizeof(List));
    if (list3 == NULL) {
        free_list(list1);
        free_list(list2);
        return 1;
    }
    list3->head = NULL;
    list3->length = 0;

    append(list1, 1);
    append(list1, 2);

    append(list2, 3);
    append(list2, 4);
    append(list2, 5);

    append(list3, 6);

    List* lists[] = {list1, list2, list3};
    size_t num_lists = sizeof(lists) / sizeof(lists[0]);

    /* Possible weaknesses found:
     *  Variable 'max_list' can be declared as pointer to const [constVariablePointer]
     */
    List* max_list = find_max_length_list(lists, num_lists);

    if (max_list != NULL) {
        printf("Maximum list length: %zu\n", max_list->length);
    }

    free_list(list1);
    free_list(list2);
    free_list(list3);

    return 0;
}