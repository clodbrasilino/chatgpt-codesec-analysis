#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *ints;
    float *floats;
    char **strings;
    int num_ints;
    int num_floats;
    int num_strings;
} Tuple;

void remove_ints(Tuple *tuple) {
    if(tuple->ints != NULL){
        free(tuple->ints);
        tuple->ints = NULL;
    }
    tuple->num_ints = 0;
}

void remove_floats(Tuple *tuple) {
    if(tuple->floats != NULL){
        free(tuple->floats);
        tuple->floats = NULL;
    }
    tuple->num_floats = 0;
}

void remove_strings(Tuple *tuple) {
    if(tuple->strings != NULL){
        for (int i = 0; i < tuple->num_strings; i++) {
            free(tuple->strings[i]);
        }
        free(tuple->strings);
        tuple->strings = NULL;
    }
    tuple->num_strings = 0;
}

int main() {
    Tuple tuple;
    tuple.ints = malloc(sizeof(int) * 5);
    tuple.floats = malloc(sizeof(float) * 5);
    tuple.strings = (char**)malloc(sizeof(char*) * 5);
    if(tuple.strings != NULL){
        for (int i = 0; i < 5; i++) {
            tuple.strings[i] = malloc(sizeof(char) * 20);
        }
    }
    tuple.num_ints = 5;
    tuple.num_floats = 5;
    tuple.num_strings = 5;

    remove_ints(&tuple);
    remove_floats(&tuple);
    remove_strings(&tuple);

    return 0;
}