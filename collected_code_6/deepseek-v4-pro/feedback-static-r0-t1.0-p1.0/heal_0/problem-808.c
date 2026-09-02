#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int *elements;
    int size;
} Tuple;

bool tuple_contains_k(Tuple *tuples, int tuple_count, int k) {
    for (int i = 0; i < tuple_count; i++) {
        for (int j = 0; j < tuples[i].size; j++) {
            if (tuples[i].elements[j] == k) {
                return true;
            }
        }
    }
    return false;
}

int main(void) {
    int elements1[] = {1, 2, 3};
    int elements2[] = {4, 5, 6};
    int elements3[] = {7, 8, 9};
    
    Tuple tuples[3];
    tuples[0].elements = elements1;
    tuples[0].size = 3;
    tuples[1].elements = elements2;
    tuples[1].size = 3;
    tuples[2].elements = elements3;
    tuples[2].size = 3;
    
    int k = 5;
    
    if (tuple_contains_k(tuples, 3, k)) {
        printf("Found %d in tuples\n", k);
    } else {
        printf("%d not found in tuples\n", k);
    }
    
    return 0;
}