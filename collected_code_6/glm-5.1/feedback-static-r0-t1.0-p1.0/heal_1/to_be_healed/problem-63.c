#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'tuples' can be declared as pointer to const [constParameterPointer]
 */
int find_max_difference(int *tuples, int num_tuples) {
    if (tuples == NULL || num_tuples <= 0) {
        return 0;
    }

    int max_diff = 0;

    for (int i = 0; i < num_tuples; i++) {
        int a = tuples[i * 2];
        int b = tuples[i * 2 + 1];
        int diff = a > b ? a - b : b - a;
        if (diff > max_diff) {
            max_diff = diff;
        }
    }

    return max_diff;
}

int main(void) {
    int tuples[] = {1, 5, 9, 2, 7, 3, 10, 1};
    int num_tuples = sizeof(tuples) / sizeof(tuples[0]) / 2;

    int max_diff = find_max_difference(tuples, num_tuples);

    printf("%d\n", max_diff);

    return 0;
}