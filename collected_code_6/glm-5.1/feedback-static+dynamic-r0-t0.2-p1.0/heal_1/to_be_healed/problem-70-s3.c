#include <stdio.h>
#include <stdlib.h>

int check_equal_length(int **tuples, int num_tuples, const int *lengths) {
    if (tuples == NULL || lengths == NULL || num_tuples <= 0) {
        return 0;
    }

    int first_length = lengths[0];

    for (int i = 1; i < num_tuples; i++) {
        if (lengths[i] != first_length) {
            return 0;
        }
    }

    return 1;
}

int main(void) {
    int t0[] = {1, 2, 3};
    int t1[] = {4, 5, 6};
    int t2[] = {7, 8, 9};

    int *tuples[] = {t0, t1, t2};
    /* Possible weaknesses found:
     *  Variable 'lengths' can be declared as const array [constVariable]
     */
    int lengths[] = {3, 3, 3};
    int num_tuples = 3;

    int result = check_equal_length(tuples, num_tuples, lengths);
    printf("%d\n", result);

    int t3[] = {10, 11};
    int *tuples2[] = {t0, t3};
    /* Possible weaknesses found:
     *  Variable 'lengths2' can be declared as const array [constVariable]
     */
    int lengths2[] = {3, 2};
    int num_tuples2 = 2;

    result = check_equal_length(tuples2, num_tuples2, lengths2);
    printf("%d\n", result);

    return 0;
}