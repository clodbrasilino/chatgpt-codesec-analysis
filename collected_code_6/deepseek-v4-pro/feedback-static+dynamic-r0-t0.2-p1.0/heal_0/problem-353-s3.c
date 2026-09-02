#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    int size;
} List;

List *create_list() {
    List *list = (List *)malloc(sizeof(List));
    if (!list) return NULL;
    list->head = NULL;
    list->size = 0;
    return list;
}

void append(List *list, int value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (!new_node) return;
    new_node->data = value;
    new_node->next = NULL;
    if (!list->head) {
        list->head = new_node;
    } else {
        Node *current = list->head;
        while (current->next) {
            current = current->next;
        }
        current->next = new_node;
    }
    list->size++;
}

void free_list(List *list) {
    if (!list) return;
    Node *current = list->head;
    while (current) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

List **create_nested_list(int rows, int cols) {
    List **nested = (List **)malloc(rows * sizeof(List *));
    if (!nested) return NULL;
    for (int i = 0; i < rows; i++) {
        nested[i] = create_list();
        if (!nested[i]) {
            for (int j = 0; j < i; j++) {
                free_list(nested[j]);
            }
            free(nested);
            return NULL;
        }
        for (int j = 0; j < cols; j++) {
            append(nested[i], i * cols + j);
        }
    }
    return nested;
}

void free_nested_list(List **nested, int rows) {
    if (!nested) return;
    for (int i = 0; i < rows; i++) {
        free_list(nested[i]);
    }
    free(nested);
}

List **remove_column(List **nested, int rows, int cols, int col_to_remove) {
    if (!nested || rows <= 0 || cols <= 0 || col_to_remove < 0 || col_to_remove >= cols) {
        return nested;
    }
    
    List **new_nested = (List **)malloc(rows * sizeof(List *));
    if (!new_nested) return NULL;
    
    for (int i = 0; i < rows; i++) {
        new_nested[i] = create_list();
        if (!new_nested[i]) {
            for (int j = 0; j < i; j++) {
                free_list(new_nested[j]);
            }
            free(new_nested);
            return NULL;
        }
        
        Node *current = nested[i]->head;
        int col_index = 0;
        while (current) {
            if (col_index != col_to_remove) {
                append(new_nested[i], current->data);
            }
            current = current->next;
            col_index++;
        }
    }
    
    return new_nested;
}

void print_nested_list(List **nested, int rows) {
    if (!nested) return;
    for (int i = 0; i < rows; i++) {
        Node *current = nested[i]->head;
        while (current) {
            printf("%d ", current->data);
            current = current->next;
        }
        printf("\n");
    }
}

int main() {
    int rows = 3;
    int cols = 4;
    int col_to_remove = 1;
    
    List **nested = create_nested_list(rows, cols);
    if (!nested) {
        fprintf(stderr, "Failed to create nested list\n");
        return 1;
    }
    
    printf("Original nested list:\n");
    print_nested_list(nested, rows);
    
    List **new_nested = remove_column(nested, rows, cols, col_to_remove);
    if (!new_nested) {
        fprintf(stderr, "Failed to remove column\n");
        free_nested_list(nested, rows);
        return 1;
    }
    
    printf("\nNested list after removing column %d:\n", col_to_remove);
    print_nested_list(new_nested, rows);
    
    free_nested_list(nested, rows);
    free_nested_list(new_nested, rows);
    
    return 0;
}