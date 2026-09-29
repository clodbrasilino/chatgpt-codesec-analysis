#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char tuple[100];
    int frequency;
} Tuple;

typedef struct {
    Tuple *tuples;
    int size;
} TupleList;

void assign_frequency(TupleList *list, char *tuple) {
    for(int i = 0; i < list->size; i++) {
        if(strcmp(list->tuples[i].tuple, tuple) == 0) {
            list->tuples[i].frequency++;
            return;
        }
    }
    list->tuples = realloc(list->tuples, (list->size + 1) * sizeof(Tuple));
    strcpy(list->tuples[list->size].tuple, tuple);
    list->tuples[list->size].frequency = 1;
    list->size++;
}

int main() {
    TupleList list;
    list.tuples = NULL;
    list.size = 0;

    assign_frequency(&list, "tuple1");
    assign_frequency(&list, "tuple2");
    assign_frequency(&list, "tuple1");
    assign_frequency(&list, "tuple3");
    assign_frequency(&list, "tuple2");
    assign_frequency(&list, "tuple1");

    for(int i = 0; i < list.size; i++) {
        printf("Tuple: %s, Frequency: %d\n", list.tuples[i].tuple, list.tuples[i].frequency);
    }

    free(list.tuples);

    return 0;
}