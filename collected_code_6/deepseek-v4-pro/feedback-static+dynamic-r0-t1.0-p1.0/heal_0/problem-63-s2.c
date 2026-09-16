#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

int max_difference(Tuple *tuples, int size, int *error) {
    if (tuples == NULL || size <= 0) {
        *error = 1;
        return 0;
    }

    int max_diff = -1;
    int found = 0;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == j) continue;
            if (tuples[i].first == tuples[j].first || 
                tuples[i].first == tuples[j].second || 
                tuples[i].second == tuples[j].first || 
                tuples[i].second == tuples[j].second) {
                int diff = abs(tuples[i].first - tuples[i].second);
                if (!found || diff > max_diff) {
                    max_diff = diff;
                    found = 1;
                }
            }
        }
    }

    if (!found) {
        *error = 2;
        return 0;
    }

    *error = 0;
    return max_diff;
}

int main(void) {
    Tuple tuples[] = {
        {1, 3},
        {3, 5},
        {5, 7},
        {2, 4}
    };
    int size = sizeof(tuples) / sizeof(tuples[0]);
    int error = 0;

    int result = max_difference(tuples, size, &error);

    if (error == 0) {
        printf("%d\n", result);
    } else if (error == 1) {
        fprintf(stderr, "Invalid input parameters\n");
        return 1;
    } else if (error == 2) {
        fprintf(stderr, "No matching pairs found\n");
        return 1;
    }

    return 0;
}