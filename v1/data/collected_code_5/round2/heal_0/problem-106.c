#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Tuple;

void add_lists_to_tuples(Tuple *tuples, int *list, int size) {
    for(int i = 0; i < size; i++) {
        tuples[i].x += list[i];
        tuples[i].y += list[i];
    }
}

int main(){
    int size = 5;
    Tuple *tuples = (Tuple*) malloc(sizeof(Tuple) * size);
    if(tuples == NULL) {
        printf("Memory allocation failed.\n");
        return 0;
    }

    for(int i = 0; i < size; i++) {
        tuples[i].x = i;
        tuples[i].y = i;
    }

    int *list = (int*) malloc(sizeof(int) * size);
    if(list == NULL) {
        printf("Memory allocation failed.\n");
        return 0;
    }

    for(int i = 0; i < size; i++) {
        list[i] = i;
    }

    add_lists_to_tuples(tuples, list, size);

    for(int i = 0; i < size; i++) {
        printf("Tuple %d: (%d, %d)\n", i, tuples[i].x, tuples[i].y);
    }

    free(tuples);
    free(list);

    return 0;
}