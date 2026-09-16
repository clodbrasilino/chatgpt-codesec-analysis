#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
} List;

void free_list(List *list) {
    while (list->head) {
        Node *temp = list->head;
        list->head = list->head->next;
        free(temp);
    }
}

List* create_list() {
    List *new_list = (List*) malloc(sizeof(List));
    new_list->head = NULL;
    return new_list;
}

void insert_node(List *list, int data) {
    Node *new_node = (Node*) malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = list->head;
    list->head = new_node;
}

void print_list(List *list) {
    Node *current = list->head;
    while (current) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

List** create_nested_list(int rows, int cols) {
    List **nested_list = (List**) malloc(sizeof(List*) * rows);
    for (int i = 0; i < rows; ++i) {
        nested_list[i] = create_list();
        for (int j = 0; j < cols; ++j) {
            insert_node(nested_list[i], (i + 1) * 10 + j);
        }
    }
    return nested_list;
}

void free_nested_list(List **nested_list, int rows) {
    for (int i = 0; i < rows; ++i) {
        free_list(nested_list[i]);
        free(nested_list[i]);
    }
    free(nested_list);
}

void remove_column(List **nested_list, int col_index, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        Node *current = nested_list[i]->head;
        Node *prev = NULL;
        int index = 0;
        while (current && index != col_index) {
            prev = current;
            current = current->next;
            ++index;
        }
        if (current) {
            if (prev) {
                prev->next = current->next;
            } else {
                nested_list[i]->head = current->next;
            }
            free(current);
        }
    }
}

int main() {
    int rows = 3;
    int cols = 4;
    List **nested_list = create_nested_list(rows, cols);

    for (int i = 0; i < rows; ++i) {
        print_list(nested_list[i]);
    }

    int col_to_remove = 2;
    remove_column(nested_list, col_to_remove, rows, cols);

    printf("\nAfter removing column %d:\n", col_to_remove);
    for (int i = 0; i < rows; ++i) {
        print_list(nested_list[i]);
    }

    free_nested_list(nested_list, rows);
    return 0;
}