#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node **rows;
    int row_count;
    int col_count;
} NestedList;

NestedList *create_nested_list(int rows, int cols) {
    NestedList *list = (NestedList *)malloc(sizeof(NestedList));
    if (list == NULL) {
        return NULL;
    }
    
    list->rows = (Node **)calloc(rows, sizeof(Node *));
    if (list->rows == NULL) {
        free(list);
        return NULL;
    }
    
    list->row_count = rows;
    list->col_count = cols;
    
    for (int i = 0; i < rows; i++) {
        list->rows[i] = NULL;
        Node *tail = NULL;
        for (int j = 0; j < cols; j++) {
            Node *new_node = (Node *)malloc(sizeof(Node));
            if (new_node == NULL) {
                for (int k = 0; k < i; k++) {
                    Node *current = list->rows[k];
                    while (current != NULL) {
                        Node *temp = current;
                        current = current->next;
                        free(temp);
                    }
                }
                free(list->rows);
                free(list);
                return NULL;
            }
            new_node->data = i * cols + j;
            new_node->next = NULL;
            
            if (tail == NULL) {
                list->rows[i] = new_node;
            } else {
                tail->next = new_node;
            }
            tail = new_node;
        }
    }
    
    return list;
}

void free_nested_list(NestedList *list) {
    if (list == NULL) {
        return;
    }
    
    for (int i = 0; i < list->row_count; i++) {
        Node *current = list->rows[i];
        while (current != NULL) {
            Node *temp = current;
            current = current->next;
            free(temp);
        }
    }
    
    free(list->rows);
    free(list);
}

NestedList *remove_column(NestedList *list, int col_index) {
    if (list == NULL || col_index < 0 || col_index >= list->col_count) {
        return list;
    }
    
    for (int i = 0; i < list->row_count; i++) {
        Node *current = list->rows[i];
        Node *prev = NULL;
        int index = 0;
        
        while (current != NULL && index < col_index) {
            prev = current;
            current = current->next;
            index++;
        }
        
        if (current != NULL) {
            if (prev == NULL) {
                list->rows[i] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
        }
    }
    
    list->col_count--;
    return list;
}

void print_nested_list(NestedList *list) {
    if (list == NULL) {
        return;
    }
    
    for (int i = 0; i < list->row_count; i++) {
        Node *current = list->rows[i];
        while (current != NULL) {
            printf("%d ", current->data);
            current = current->next;
        }
        printf("\n");
    }
}

int main(void) {
    NestedList *list = create_nested_list(3, 4);
    if (list == NULL) {
        fprintf(stderr, "Failed to create nested list\n");
        return 1;
    }
    
    printf("Original list:\n");
    print_nested_list(list);
    
    list = remove_column(list, 1);
    
    printf("\nAfter removing column 1:\n");
    print_nested_list(list);
    
    free_nested_list(list);
    
    return 0;
}