#include <stdio.h>
#include <stdlib.h>

int check_equal_length(int **tuples, int num_tuples, const int *lengths) {
    if (num_tuples <= 0 || lengths == NULL) {
        return 0;
    }
    if (tuples == NULL) {
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
    int *tuples1[] = {t0, t1, t2};
    /* Possible weaknesses found:
     *  Variable 'lengths1' can be declared as const array [constVariable]
     */
    int lengths1[] = {3, 3, 3};
    int result1 = check_equal_length(tuples1, 3, lengths1);
    printf("%d\n", result1);

    int t3[] = {1, 2};
    int t4[] = {3, 4, 5};
    int *tuples2[] = {t3, t4};
    /* Possible weaknesses found:
     *  Variable 'lengths2' can be declared as const array [constVariable]
     */
    int lengths2[] = {2, 3};
    int result2 = check_equal_length(tuples2, 2, lengths2);
    printf("%d\n", result2);

    return 0;
}