#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

Tuple* add_tuples(Tuple* tuple1, Tuple* tuple2) {
    if (tuple1 == NULL || tuple2 == NULL) {
        return NULL;
    }

    Tuple* result = (Tuple*) malloc(sizeof(Tuple));
    if (result == NULL) {
        return NULL;
    }

    result->first = tuple1->first + tuple2->first;
    result->second = tuple1->second + tuple2->second;

    return result;
}

int main() {
    Tuple tuple1 = {5, 7};
    Tuple tuple2 = {3, 8};

    Tuple* result = add_tuples(&tuple1, &tuple2);
    if(result !=NULL){
        printf("The result is {%d, %d}\n", result->first, result->second);
        free(result); 
    }

    return 0;
}