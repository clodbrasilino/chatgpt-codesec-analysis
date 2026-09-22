#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
} List;

typedef struct {
    List **arrays;
    int row_count;
    int col_count;
} NestedList;

List* create_list(int *data, int size) {
    List *lst = (List*)malloc(sizeof(List));
    lst->data = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; ++i) {
        lst->data[i] = data[i];
    }
    lst->size = size;
    return lst;
}

NestedList* create_nested_list(int rows, int cols, int **data) {
    NestedList *nest_list = (NestedList*)malloc(sizeof(NestedList));
    nest_list->arrays = (List**)malloc(rows * sizeof(List*));
    for (int i = 0; i < rows; ++i) {
        nest_list->arrays[i] = create_list(data[i], cols);
    }
    nest_list->row_count = rows;
    nest_list->col_count = cols;
    return nest_list;
}

List* extract_column(NestedList *nl, int col) {
    if (col >= 0 && col < nl->col_count) {
        List *result = (List*)malloc(sizeof(List));
        result->data = (int*)malloc(nl->row_count * sizeof(int));
        result->size = nl->row_count;
        for (int i = 0; i < nl->row_count; ++i) {
            result->data[i] = nl->arrays[i]->data[col];
        }
        return result;
    }
    return NULL;
}

void free_list(List *lst) {
    if (lst) {
        free(lst->data);
        free(lst);
    }
}

void free_nested_list(NestedList *nl) {
    if (nl) {
        for (int i = 0; i < nl->row_count; ++i) {
            free_list(nl->arrays[i]);
        }
        free(nl->arrays);
        free(nl);
    }
}

void print_list(List *lst) {
    if (lst) {
        for (int i = 0; i < lst->size; ++i) {
            printf("%d ", lst->data[i]);
        }
        printf("\n");
    }
}

int main() {
    int data1[] = {1, 2, 3};
    int data2[] = {4, 5, 6};
    int data3[] = {7, 8, 9};

    int **data = (int**)(malloc(3 * sizeof(int*)));
    data[0] = data1;
    data[1] = data2;
    data[2] = data3;

    NestedList *nl = create_nested_list(3, 3, data);

    List *column = extract_column(nl, 1);
    print_list(column);

    free_list(column);
    free_nested_list(nl);

    return 0;
}