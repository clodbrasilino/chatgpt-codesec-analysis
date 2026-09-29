#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
    Node *tail;
} List;

List* create_list() {
    List *list = (List*)malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void append_to_list(List *list, int value) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = NULL;
    
    if (list->head == NULL) {
        list->head = new_node;
        list->tail = new_node;
    } else {
        list->tail->next = new_node;
        list->tail = new_node;
    }
}

List** create_nested_list(int rows, int cols) {
    List **nested_list = (List**)malloc(rows * sizeof(List*));
    for (int i = 0; i < rows; ++i) {
        nested_list[i] = create_list();
        for (int j = 0; j < cols; ++j) {
            append_to_list(nested_list[i], i * cols + j);
        }
    }
    return nested_list;
}

void remove_column(List **nested_list, int column, int rows) {
    for (int i = 0; i < rows; ++i) {
        Node *current = nested_list[i]->head;
        Node *prev = NULL;
        
        while (current != NULL) {
            if (prev == NULL && column == 0) {
                Node *temp = current;
                nested_list[i]->head = current->next;
                free(temp);
                if (nested_list[i]->head == NULL) {
                    nested_list[i]->tail = NULL;
                }
                break;
            } else if (column > 0 && prev != NULL) {
                --column;
                if (column == 0) {
                    Node *temp = current;
                    prev->next = current->next;
                    free(temp);
                    if (prev->next == NULL) {
                        nested_list[i]->tail = prev;
                    }
                    break;
                }
            }
            prev = current;
            current = current->next;
        }
    }
}

void free_nested_list(List **nested_list, int rows) {
    for (int i = 0; i < rows; ++i) {
        Node *current = nested_list[i]->head;
        Node *next;
        
        while (current != NULL) {
            next = current->next;
            free(current);
            current = next;
        }
        free(nested_list[i]);
    }
    free(nested_list);
}

void print_nested_list(List **nested_list, int rows) {
    for (int i = 0; i < rows; ++i) {
        Node *current = nested_list[i]->head;
        while (current != NULL) {
            printf("%d ", current->value);
            current = current->next;
        }
        printf("\n");
    }
}

int main() {
    int rows = 3;
    int cols = 4;
    
    List **nested_list = create_nested_list(rows, cols);
    print_nested_list(nested_list, rows);
    
    int column_to_remove = 2;
    remove_column(nested_list, column_to_remove, rows);
    printf("After removing column %d:\n", column_to_remove);
    print_nested_list(nested_list, rows);
    
    free_nested_list(nested_list, rows);
    return 0;
}