#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int x;
    int y;
} Tuple;

typedef struct {
    Tuple tuple;
    int frequency;
} TupleFrequency;

Tuple create_tuple(int x, int y) {
    Tuple t;
    if (x < y) {
        t.x = x;
        t.y = y;
    } else {
        t.x = y;
        t.y = x;
    }
    return t;
}

bool tuples_equal(Tuple t1, Tuple t2) {
    return t1.x == t2.x && t1.y == t2.y;
}

TupleFrequency* extract_frequencies(Tuple* input_tuples, int input_size, int* output_size) {
    if (input_tuples == NULL || input_size <= 0 || output_size == NULL) {
        if (output_size != NULL) *output_size = 0;
        return NULL;
    }

    TupleFrequency* frequencies = (TupleFrequency*)malloc(input_size * sizeof(TupleFrequency));
    if (frequencies == NULL) {
        *output_size = 0;
        return NULL;
    }

    int unique_count = 0;

    for (int i = 0; i < input_size; i++) {
        Tuple current = create_tuple(input_tuples[i].x, input_tuples[i].y);
        bool found = false;

        for (int j = 0; j < unique_count; j++) {
            if (tuples_equal(frequencies[j].tuple, current)) {
                frequencies[j].frequency++;
                found = true;
                break;
            }
        }

        if (!found) {
            frequencies[unique_count].tuple = current;
            frequencies[unique_count].frequency = 1;
            unique_count++;
        }
    }

    *output_size = unique_count;

    TupleFrequency* resized = (TupleFrequency*)realloc(frequencies, unique_count * sizeof(TupleFrequency));
    if (resized != NULL) {
        frequencies = resized;
    }

    return frequencies;
}

int main() {
    Tuple input[] = {
        {1, 2}, {2, 1}, {3, 4}, {1, 2}, {4, 3}, {5, 6}
    };
    int input_size = sizeof(input) / sizeof(input[0]);
    int output_size = 0;

    TupleFrequency* frequencies = extract_frequencies(input, input_size, &output_size);

    if (frequencies != NULL) {
        for (int i = 0; i < output_size; i++) {
            printf("(%d, %d): %d\n", frequencies[i].tuple.x, frequencies[i].tuple.y, frequencies[i].frequency);
        }
        free(frequencies);
    }

    return 0;
}