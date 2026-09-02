#include <stdio.h>
#include <stdlib.h>

typedef struct Tuple {
    int value;
} Tuple;

int cumulative_sum(Tuple *tuples, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += tuples[i].value;
    }
    return sum;
}

int main() {
    int n;
    printf("Enter number of tuples: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input\n");
        return 1;
    }

    Tuple *tuples = (Tuple *)malloc(sizeof(Tuple) * n);
    if (tuples == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("Enter %d values:\n", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &tuples[i].value) != 1) {
            printf("Invalid input\n");
            free(tuples);
            return 1;
        }
    }

    int result = cumulative_sum(tuples, n);
    printf("Cumulative sum: %d\n", result);

    free(tuples);
    return 0;
}