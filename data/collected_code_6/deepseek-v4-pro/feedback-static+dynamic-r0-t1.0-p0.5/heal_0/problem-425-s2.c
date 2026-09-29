#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    int size;
} LinkedList;

LinkedList* create_list() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    if (list == NULL) {
        return NULL;
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

void append(LinkedList* list, int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        return;
    }
    new_node->data = value;
    new_node->next = NULL;
    
    if (list->head == NULL) {
        list->head = new_node;
    } else {
        Node* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    list->size++;
}

void free_list(LinkedList* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

int count_sublists_with_element(LinkedList* list, int element) {
    if (list == NULL || list->head == NULL) {
        return 0;
    }
    
    int count = 0;
    int n = list->size;
    Node* current = list->head;
    int* arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        return 0;
    }
    
    for (int i = 0; i < n; i++) {
        arr[i] = current->data;
        current = current->next;
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            for (int k = i; k <= j; k++) {
                if (arr[k] == element) {
                    count++;
                    break;
                }
            }
        }
    }
    
    free(arr);
    return count;
}

int main() {
    LinkedList* list = create_list();
    if (list == NULL) {
        return 1;
    }
    
    append(list, 1);
    append(list, 2);
    append(list, 3);
    append(list, 2);
    append(list, 1);
    
    int element = 2;
    int result = count_sublists_with_element(list, element);
    printf("Number of sublists containing %d: %d\n", element, result);
    
    free_list(list);
    return 0;
}