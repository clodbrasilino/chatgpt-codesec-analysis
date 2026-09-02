#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Node {
    double data;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
    size_t size;
} List;

List *list_create(void) {
    List *list = (List *)malloc(sizeof(List));
    if (list == NULL) {
        return NULL;
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

int list_append(List *list, double value) {
    if (list == NULL) {
        return -1;
    }
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return -1;
    }
    new_node->data = value;
    new_node->next = NULL;
    
    if (list->head == NULL) {
        list->head = new_node;
    } else {
        Node *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    list->size++;
    return 0;
}

void list_destroy(List *list) {
    if (list == NULL) {
        return;
    }
    Node *current = list->head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

List *map_power(const int *bases, size_t size) {
    if (bases == NULL || size == 0) {
        return NULL;
    }
    
    List *result = list_create();
    if (result == NULL) {
        return NULL;
    }
    
    for (size_t i = 0; i < size; i++) {
        double value = pow((double)bases[i], (double)i);
        if (list_append(result, value) != 0) {
            list_destroy(result);
            return NULL;
        }
    }
    
    return result;
}

void list_print(List *list) {
    if (list == NULL) {
        printf("NULL\n");
        return;
    }
    
    Node *current = list->head;
    while (current != NULL) {
        printf("%.2f ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    int bases[] = {2, 3, 4, 5, 6};
    size_t size = sizeof(bases) / sizeof(bases[0]);
    
    List *result = map_power(bases, size);
    if (result == NULL) {
        fprintf(stderr, "Error: Failed to create list\n");
        return 1;
    }
    
    list_print(result);
    list_destroy(result);
    
    return 0;
}