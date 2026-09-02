#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
} Tuple;

typedef struct {
    Tuple *tuples;
    int count;
} TupleList;

int get_last_element(Tuple tuple) {
    return tuple.data[tuple.size - 1];
}

int compare_tuples(const void *a, const void *b) {
    /* Possible weaknesses found:
     *  Variable 'tuple_a' can be declared as pointer to const [constVariablePointer]
     */
    Tuple *tuple_a = (Tuple *)a;
    /* Possible weaknesses found:
     *  Variable 'tuple_b' can be declared as pointer to const [constVariablePointer]
     */
    Tuple *tuple_b = (Tuple *)b;
    return get_last_element(*tuple_a) - get_last_element(*tuple_b);
}

void sort_tuples_by_last_element(TupleList *list) {
    if (list == NULL || list->tuples == NULL || list->count <= 0) {
        return;
    }
    qsort(list->tuples, list->count, sizeof(Tuple), compare_tuples);
}

/* Possible weaknesses found:
 *  Parameter 'data' can be declared as pointer to const [constParameterPointer]
 */
Tuple create_tuple(int *data, int size) {
    Tuple tuple;
    tuple.size = size;
    tuple.data = (int *)malloc(size * sizeof(int));
    if (tuple.data != NULL) {
        for (int i = 0; i < size; i++) {
            tuple.data[i] = data[i];
        }
    }
    return tuple;
}

void free_tuple_list(TupleList *list) {
    if (list == NULL) {
        return;
    }
    for (int i = 0; i < list->count; i++) {
        free(list->tuples[i].data);
    }
    free(list->tuples);
    list->tuples = NULL;
    list->count = 0;
}

void print_tuple_list(TupleList *list) {
    for (int i = 0; i < list->count; i++) {
        printf("(");
        for (int j = 0; j < list->tuples[i].size; j++) {
            printf("%d", list->tuples[i].data[j]);
            if (j < list->tuples[i].size - 1) {
                printf(", ");
            }
        }
        printf(") ");
    }
    printf("\n");
}

int main() {
    int data1[] = {1, 3};
    int data2[] = {2, 1};
    int data3[] = {4, 2};
    int data4[] = {3, 0};
    int data5[] = {5, 4};

    TupleList list;
    list.count = 5;
    list.tuples = (Tuple *)malloc(list.count * sizeof(Tuple));
    
    if (list.tuples == NULL) {
        return 1;
    }

    list.tuples[0] = create_tuple(data1, 2);
    list.tuples[1] = create_tuple(data2, 2);
    list.tuples[2] = create_tuple(data3, 2);
    list.tuples[3] = create_tuple(data4, 2);
    list.tuples[4] = create_tuple(data5, 2);

    for (int i = 0; i < list.count; i++) {
        if (list.tuples[i].data == NULL) {
            for (int j = 0; j < i; j++) {
                free(list.tuples[j].data);
            }
            free(list.tuples);
            return 1;
        }
    }

    printf("Original list: ");
    print_tuple_list(&list);

    sort_tuples_by_last_element(&list);

    printf("Sorted list: ");
    print_tuple_list(&list);

    free_tuple_list(&list);

    return 0;
}