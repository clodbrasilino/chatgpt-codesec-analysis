#include <stdio.h>
#include <stdlib.h>

int check_equal_length(int **tuples, int num_tuples, const int *lengths) {
    if (num_tuples <= 0 || lengths == NULL) {
        return 0;
    }
    if (tuples == NULL) {
        return 0;
    }
    for (int i = 0; i < num_tuples; i++) {
        if (tuples[i] == NULL) {
            return 0;
        }
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
    int a[] = {1, 2, 3};
    int b[] = {4, 5, 6};
    int c[] = {7, 8, 9};
    int *tuples1[] = {a, b, c};
    const int lengths1[] = {3, 3, 3};
    int result1 = check_equal_length(tuples1, 3, lengths1);
    printf("%d\n", result1);

    int d[] = {10, 11};
    int *tuples2[] = {a, d};
    const int lengths2[] = {3, 2};
    int result2 = check_equal_length(tuples2, 2, lengths2);
    printf("%d\n", result2);

    int *tuples3[] = {a, NULL};
    const int lengths3[] = {3, 0};
    int result3 = check_equal_length(tuples3, 2, lengths3);
    printf("%d\n", result3);

    return 0;
}