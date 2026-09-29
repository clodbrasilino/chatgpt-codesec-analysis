#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

int count_inversions(Tuple *tuples, int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (tuples[i].first > tuples[j].first ||
                (tuples[i].first == tuples[j].first && tuples[i].second > tuples[j].second)) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    Tuple *tuples = (Tuple *)malloc((size_t)n * sizeof(Tuple));
    if (tuples == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        if (scanf("%d %d", &tuples[i].first, &tuples[i].second) != 2) {
            fprintf(stderr, "Invalid tuple input\n");
            free(tuples);
            return 1;
        }
    }

    int inversions = count_inversions(tuples, n);
    printf("%d\n", inversions);

    free(tuples);
    return 0;
}