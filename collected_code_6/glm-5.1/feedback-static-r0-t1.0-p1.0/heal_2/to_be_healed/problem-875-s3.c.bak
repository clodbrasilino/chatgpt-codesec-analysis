#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_min_diff(const int *tuples, int n) {
    if (tuples == NULL || n < 2) {
        return -1;
    }

    int min_diff = INT_MAX;
    
    for (int i = 0; i < n; i++) {
        if (tuples[i] < 0) {
            return -1;
        }
        for (int j = i + 1; j < n; j++) {
            int diff = abs(tuples[i] - tuples[j]);
            if (diff < min_diff) {
                min_diff = diff;
            }
        }
    }
    
    return min_diff;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc < 3) {
        return 1;
    }

    int n = argc - 1;
    int *tuples = (int *)malloc(n * sizeof(int));
    if (tuples == NULL) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        tuples[i] = atoi(argv[i + 1]);
    }

    int result = find_min_diff(tuples, n);
    
    printf("%d\n", result);

    free(tuples);
    tuples = NULL;

    return 0;
}