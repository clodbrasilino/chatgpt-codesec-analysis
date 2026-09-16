#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

bool hasAllKElements(const Tuple *tuples, int n, int k) {
    if (k < 0 || n < 0) {
        return false;
    }
    if (k == 0) {
        return true;
    }
    if (tuples == NULL) {
        return false;
    }

    bool *seen = calloc((size_t)k + 1, sizeof(*seen));
    if (seen == NULL) {
        return false;
    }

    for (int i = 0; i < n; ++i) {
        int values[2] = {tuples[i].first, tuples[i].second};
        for (int j = 0; j < 2; ++j) {
            int value = values[j];
            if (value >= 1 && value <= k) {
                seen[value] = true;
            }
        }
    }

    bool result = true;
    for (int i = 1; i <= k; ++i) {
        if (!seen[i]) {
            result = false;
            break;
        }
    }

    free(seen);
    return result;
}

int main(void) {
    Tuple tuples[] = {{1, 2}, {2, 3}, {3, 4}};
    int n = (int)(sizeof(tuples) / sizeof(tuples[0]));
    int k = 4;

    if (hasAllKElements(tuples, n, k)) {
        printf("The tuple list contains all %d elements.\n", k);
    } else {
        printf("The tuple list does not contain all %d elements.\n", k);
    }

    return 0;
}