#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

void sort_tuples(Tuple *tuples, size_t num_tuples) {
    if (!tuples || num_tuples == 0) {
        return;
    }

    for (size_t i = 0; i < num_tuples - 1; i++) {
        for (size_t j = 0; j < num_tuples - i - 1; j++) {
            if (tuples[j].size == 0 || tuples[j + 1].size == 0) {
                continue;
            }
            int last_j = tuples[j].elements[tuples[j].size - 1];
            int last_next_j = tuples[j + 1].elements[tuples[j + 1].size - 1];
            
            if (last_j > last_next_j) {
                Tuple temp = tuples[j];
                tuples[j] = tuples[j + 1];
                tuples[j + 1] = temp;
            }
        }
    }
}

int main(void) {
    int arr1[] = {1, 3};
    int arr2[] = {3, 2, 1};
    int arr3[] = {4, 6, 5};
    int arr4[] = {9};
    int arr5[] = {7, 8, 2};

    Tuple tuples[] = {
        {arr1, 2},
        {arr2, 3},
        {arr3, 3},
        {arr4, 1},
        {arr5, 3}
    };

    size_t num_tuples = sizeof(tuples) / sizeof(tuples[0]);

    sort_tuples(tuples, num_tuples);

    for (size_t i = 0; i < num_tuples; i++) {
        printf("(");
        for (size_t j = 0; j < tuples[i].size; j++) {
            printf("%d", tuples[i].elements[j]);
            if (j < tuples[i].size - 1) {
                printf(", ");
            }
        }
        printf(") ");
    }
    printf("\n");

    return 0;
}