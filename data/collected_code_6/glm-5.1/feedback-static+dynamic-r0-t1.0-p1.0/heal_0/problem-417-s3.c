#include <stdio.h>
#include <stdlib.h>

int find_common_first(int **tuples, int num_tuples, int tuple_size) {
    if (num_tuples == 0 || tuple_size == 0 || tuples == NULL) {
        return -1;
    }
    int candidate = tuples[0][0];
    for (int i = 1; i < num_tuples; i++) {
        if (tuples[i] == NULL) {
            return -1;
        }
        if (tuples[i][0] != candidate) {
            return -1;
        }
    }
    return candidate;
}

int main() {
    int t0[] = {5, 10};
    int t1[] = {5, 20};
    int t2[] = {5, 30};
    int t3[] = {6, 40};

    int *tuples_match[] = {t0, t1, t2};
    int *tuples_no_match[] = {t0, t1, t3};

    int result1 = find_common_first(tuples_match, 3, 2);
    int result2 = find_common_first(tuples_no_match, 3, 2);

    printf("%d\n", result1);
    printf("%d\n", result2);

    return 0;
}