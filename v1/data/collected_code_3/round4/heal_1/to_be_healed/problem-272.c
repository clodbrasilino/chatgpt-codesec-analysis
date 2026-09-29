#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

Tuple* create_tuple(int a, int b) {
    Tuple* new_tuple = (Tuple*)malloc(sizeof(Tuple));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'new_tuple' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    new_tuple->a = a;
    new_tuple->b = b;
    return new_tuple;
}

int extract_rear(Tuple* tuple) {
    return tuple->b;
}

int main() {
    Tuple* tuple_list[5];
    for(int i = 0; i < 5; i++) {
        tuple_list[i] = create_tuple(i, i+1);
    }

    for(int i = 0; i < 5; i++) {
        printf("%d\n", extract_rear(tuple_list[i]));
        free(tuple_list[i]);
    }

    return 0;
}