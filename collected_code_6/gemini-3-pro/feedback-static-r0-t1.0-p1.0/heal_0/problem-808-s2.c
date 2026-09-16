#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

bool contains_k(Tuple *tuples, size_t num_tuples, int k) {
    if (tuples == NULL) {
        return false;
    }

    for (size_t i = 0; i < num_tuples; i++) {
        if (tuples[i].elements == NULL) {
            continue;
        }
        for (size_t j = 0; j < tuples[i].size; j++) {
            if (tuples[i].elements[j] == k) {
                return true;
            }
        }
    }
    return false;
}

int main(void) {
    int t1_data[] = {1, 2, 3};
    int t2_data[] = {4, 5, 6};
    
    Tuple tuples[2];
    tuples[0].elements = t1_data;
    tuples[0].size = sizeof(t1_data) / sizeof(t1_data[0]);
    
    tuples[1].elements = t2_data;
    tuples[1].size = sizeof(t2_data) / sizeof(t2_data[0]);

    int k1 = 5;
    if (contains_k(tuples, 2, k1)) {
        printf("Tuples contain %d\n", k1);
    } else {
        printf("Tuples do not contain %d\n", k1);
    }

    int k2 = 7;
    if (contains_k(tuples, 2, k2)) {
        printf("Tuples contain %d\n", k2);
    } else {
        printf("Tuples do not contain %d\n", k2);
    }

    return 0;
}