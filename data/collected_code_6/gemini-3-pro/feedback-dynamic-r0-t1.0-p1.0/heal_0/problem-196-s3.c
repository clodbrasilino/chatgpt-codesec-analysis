#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    int length;
} Tuple;

typedef struct {
    Tuple *tuples;
    int count;
} TupleList;

TupleList* remove_tuples_of_length_k(TupleList *list, int k) {
    if (!list || !list->tuples) {
        return NULL;
    }

    TupleList *new_list = (TupleList *)malloc(sizeof(TupleList));
    if (!new_list) {
        return NULL;
    }

    new_list->tuples = (Tuple *)malloc(list->count * sizeof(Tuple));
    if (!new_list->tuples) {
        free(new_list);
        return NULL;
    }

    new_list->count = 0;

    for (int i = 0; i < list->count; i++) {
        if (list->tuples[i].length != k) {
            new_list->tuples[new_list->count].elements = (int *)malloc(list->tuples[i].length * sizeof(int));
            if (!new_list->tuples[new_list->count].elements) {
                for (int j = 0; j < new_list->count; j++) {
                    free(new_list->tuples[j].elements);
                }
                free(new_list->tuples);
                free(new_list);
                return NULL;
            }
            
            for (int j = 0; j < list->tuples[i].length; j++) {
                new_list->tuples[new_list->count].elements[j] = list->tuples[i].elements[j];
            }
            new_list->tuples[new_list->count].length = list->tuples[i].length;
            new_list->count++;
        }
    }

    return new_list;
}

void free_tuple_list(TupleList *list) {
    if (list) {
        if (list->tuples) {
            for (int i = 0; i < list->count; i++) {
                free(list->tuples[i].elements);
            }
            free(list->tuples);
        }
        free(list);
    }
}

int main(void) {
    TupleList list;
    list.count = 3;
    list.tuples = (Tuple *)malloc(list.count * sizeof(Tuple));
    if (!list.tuples) {
        return 1;
    }

    list.tuples[0].length = 2;
    list.tuples[0].elements = (int *)malloc(2 * sizeof(int));
    if (list.tuples[0].elements) {
        list.tuples[0].elements[0] = 1;
        list.tuples[0].elements[1] = 2;
    }

    list.tuples[1].length = 3;
    list.tuples[1].elements = (int *)malloc(3 * sizeof(int));
    if (list.tuples[1].elements) {
        list.tuples[1].elements[0] = 3;
        list.tuples[1].elements[1] = 4;
        list.tuples[1].elements[2] = 5;
    }

    list.tuples[2].length = 2;
    list.tuples[2].elements = (int *)malloc(2 * sizeof(int));
    if (list.tuples[2].elements) {
        list.tuples[2].elements[0] = 6;
        list.tuples[2].elements[1] = 7;
    }

    TupleList *filtered_list = remove_tuples_of_length_k(&list, 2);
    if (!filtered_list) {
        free_tuple_list(&list);
        return 1;
    }

    for (int i = 0; i < filtered_list->count; i++) {
        for (int j = 0; j < filtered_list->tuples[i].length; j++) {
            printf("%d ", filtered_list->tuples[i].elements[j]);
        }
        printf("\n");
    }

    free_tuple_list(filtered_list);
    
    for (int i = 0; i < list.count; i++) {
        free(list.tuples[i].elements);
    }
    free(list.tuples);

    return 0;
}