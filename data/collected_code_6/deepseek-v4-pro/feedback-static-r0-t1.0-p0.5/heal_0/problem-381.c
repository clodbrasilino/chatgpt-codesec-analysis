#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int *data;
    int size;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
} List;

Node *create_node(int *data, int size) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (!node) return NULL;
    node->data = data;
    node->size = size;
    node->next = NULL;
    return node;
}

void list_append(List *list, int *data, int size) {
    Node *node = create_node(data, size);
    if (!node) return;
    if (!list->head) {
        list->head = node;
        return;
    }
    Node *current = list->head;
    while (current->next) {
        current = current->next;
    }
    current->next = node;
}

void list_free(List *list) {
    Node *current = list->head;
    while (current) {
        Node *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
    list->head = NULL;
}

int compare_nodes(Node *a, Node *b, int index) {
    if (index >= a->size || index >= b->size) return 0;
    if (a->data[index] < b->data[index]) return -1;
    if (a->data[index] > b->data[index]) return 1;
    return 0;
}

void sort_list_by_index(List *list, int index) {
    if (!list->head || !list->head->next) return;
    
    int swapped;
    Node *ptr1;
    Node *lptr = NULL;
    
    do {
        swapped = 0;
        ptr1 = list->head;
        
        while (ptr1->next != lptr) {
            if (compare_nodes(ptr1, ptr1->next, index) > 0) {
                int *temp_data = ptr1->data;
                int temp_size = ptr1->size;
                ptr1->data = ptr1->next->data;
                ptr1->size = ptr1->next->size;
                ptr1->next->data = temp_data;
                ptr1->next->size = temp_size;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

void print_list(List *list) {
    Node *current = list->head;
    while (current) {
        printf("[");
        for (int i = 0; i < current->size; i++) {
            printf("%d", current->data[i]);
            if (i < current->size - 1) printf(", ");
        }
        printf("] ");
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    List list = {0};
    
    int *arr1 = (int *)malloc(3 * sizeof(int));
    if (!arr1) return 1;
    arr1[0] = 3; arr1[1] = 1; arr1[2] = 4;
    list_append(&list, arr1, 3);
    
    int *arr2 = (int *)malloc(3 * sizeof(int));
    if (!arr2) {
        list_free(&list);
        return 1;
    }
    arr2[0] = 1; arr2[1] = 5; arr2[2] = 9;
    list_append(&list, arr2, 3);
    
    int *arr3 = (int *)malloc(3 * sizeof(int));
    if (!arr3) {
        list_free(&list);
        return 1;
    }
    arr3[0] = 2; arr3[1] = 6; arr3[2] = 5;
    list_append(&list, arr3, 3);
    
    printf("Before sorting: ");
    print_list(&list);
    
    sort_list_by_index(&list, 0);
    
    printf("After sorting by index 0: ");
    print_list(&list);
    
    sort_list_by_index(&list, 1);
    
    printf("After sorting by index 1: ");
    print_list(&list);
    
    list_free(&list);
    
    return 0;
}