#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int index;
    int value;
} Tuple;

typedef struct {
    Tuple *tuple;
    int valid;
} Result;

Result extract_min_index(Tuple *tuples, int size) {
    Result result;
    result.tuple = NULL;
    result.valid = 0;

    if (tuples == NULL || size <= 0) {
        return result;
    }

    int min_index = INT_MAX;
    int min_pos = -1;

    for (int i = 0; i < size; i++) {
        if (tuples[i].index < min_index) {
            min_index = tuples[i].index;
            min_pos = i;
        }
    }

    if (min_pos != -1) {
        result.tuple = &tuples[min_pos];
        result.valid = 1;
    }

    return result;
}

int main(void) {
    Tuple tuples[] = {
        {5, 100},
        {2, 200},
        {8, 300},
        {1, 400},
        {3, 500}
    };
    int size = sizeof(tuples) / sizeof(tuples[0]);

    Result result = extract_min_index(tuples, size);

    if (result.valid) {
        printf("Index: %d, Value: %d\n", result.tuple->index, result.tuple->value);
    } else {
        printf("No valid tuple found.\n");
    }

    return 0;
}