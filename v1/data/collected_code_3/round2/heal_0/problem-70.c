#include <stdio.h>
#include <stdlib.h>

struct Tuple {
    int *arr;
    int len;
};

int checkEqualLength(struct Tuple *tuples, int n) {
    int length = tuples[0].len;
    for (int i = 1; i < n; i++) {
        if (tuples[i].len != length) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int n = 3;
    struct Tuple *tuples = malloc(n * sizeof(struct Tuple));
    for (int i = 0; i < n; i++) {
        tuples[i].len = 5;
        tuples[i].arr = malloc(tuples[i].len * sizeof(int));
    }

    if (checkEqualLength(tuples, n)) {
        printf("All tuples have equal length\n");
    } else {
        printf("All tuples do not have equal length\n");
    }

    for (int i = 0; i < n; i++) {
        free(tuples[i].arr);
    }
    free(tuples);

    return 0;
}