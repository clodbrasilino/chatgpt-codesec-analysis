#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

int compare(const void *a, const void *b) {
    return ((Tuple *)a)->first - ((Tuple *)b)->first;
}

void findSingles(Tuple *tuples, int n, int *result, int *count) {
    qsort(tuples, n, sizeof(Tuple), compare);
    for (int i = 0; i < n; i++) {
        if ((i == 0 || tuples[i].first != tuples[i-1].first) &&
            (i == n-1 || tuples[i].first != tuples[i+1].first)) {
            result[*count] = tuples[i].first;
            (*count)++;
        }
    }
}

int main() {
    Tuple tuples[] = {{2, 3}, {1, 4}, {1, 5}, {2, 6}};
    int n = 4;
    int *result = (int *)malloc(n * sizeof(int));
    int count = 0;

    findSingles(tuples, n, result, &count);

    for (int i = 0; i < count; i++) {
        printf("%d ", result[i]);
    }
    free(result);
    return 0;
}