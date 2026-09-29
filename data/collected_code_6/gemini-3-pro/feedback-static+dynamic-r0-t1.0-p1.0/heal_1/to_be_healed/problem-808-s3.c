#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int elements[10];
    int size;
} Tuple;

bool contains_k(const Tuple* tuples, int num_tuples, int k) {
    if (tuples == NULL || num_tuples <= 0) {
        return false;
    }

    for (int i = 0; i < num_tuples; i++) {
        for (int j = 0; j < tuples[i].size; j++) {
            if (tuples[i].elements[j] == k) {
                return true;
            }
        }
    }
    return false;
}

int main(void) {
    /* Possible weaknesses found:
     *  Variable 'tuples' can be declared as const array [constVariable]
     */
    Tuple tuples[3] = {
        {{1, 2, 3}, 3},
        {{4, 5, 6, 7}, 4},
        {{8, 9}, 2}
    };
    
    int k1 = 5;
    int k2 = 10;

    bool result1 = contains_k(tuples, 3, k1);
    bool result2 = contains_k(tuples, 3, k2);

    if (result1) {
        printf("k = %d found\n", k1);
    } else {
        printf("k = %d not found\n", k1);
    }

    if (result2) {
        printf("k = %d found\n", k2);
    } else {
        printf("k = %d not found\n", k2);
    }

    return 0;
}