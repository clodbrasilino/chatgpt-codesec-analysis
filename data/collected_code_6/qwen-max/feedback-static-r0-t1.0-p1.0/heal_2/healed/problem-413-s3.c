#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

Tuple* create_tuple(int first, int second) {
    Tuple* t = malloc(sizeof(Tuple));
    if (t == NULL) {
        return NULL;
    }
    t->first = first;
    t->second = second;
    return t;
}

void free_tuples(Tuple** tuples, int length) {
    for (int i = 0; i < length; i++) {
        free(tuples[i]);
    }
    free(tuples);
}

const Tuple* nth_element(const Tuple** tuples, int length, int n) {
    if (n >= 0 && n < length) {
        return tuples[n];
    } else {
        return NULL;
    }
}

int main() {
    int num_tuples = 5;
    Tuple** list_of_tuples = malloc(num_tuples * sizeof(Tuple*));
    
    for (int i = 0; i < num_tuples; i++) {
        list_of_tuples[i] = create_tuple(i, i * 2);
    }

    int n = 3;
    const Tuple* nth = nth_element(list_of_tuples, num_tuples, n);

    if (nth != NULL) {
        printf("The %dth element: (%d, %d)\n", n, nth->first, nth->second);
    } else {
        printf("Index out of bounds\n");
    }

    free_tuples(list_of_tuples, num_tuples);
    return 0;
}