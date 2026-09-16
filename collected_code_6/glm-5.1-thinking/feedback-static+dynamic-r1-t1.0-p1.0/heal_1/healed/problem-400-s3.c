#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

typedef struct {
    Tuple key;
    int count;
} TupleFreq;

TupleFreq* extract_frequencies(const Tuple* list, int size, int* out_size) {
    if (list == NULL || out_size == NULL || size <= 0) {
        if (out_size != NULL) {
            *out_size = 0;
        }
        return NULL;
    }

    TupleFreq* freqs = (TupleFreq*)malloc(size * sizeof(TupleFreq));
    if (freqs == NULL) {
        *out_size = 0;
        return NULL;
    }

    *out_size = 0;

    for (int i = 0; i < size; i++) {
        Tuple current = list[i];
        if (current.a > current.b) {
            int temp = current.a;
            current.a = current.b;
            current.b = temp;
        }

        int found = 0;
        for (int j = 0; j < *out_size; j++) {
            if (freqs[j].key.a == current.a && freqs[j].key.b == current.b) {
                freqs[j].count++;
                found = 1;
                break;
            }
        }

        if (!found) {
            freqs[*out_size].key = current;
            freqs[*out_size].count = 1;
            (*out_size)++;
        }
    }

    TupleFreq* resized = (TupleFreq*)realloc(freqs, (*out_size) * sizeof(TupleFreq));
    if (resized != NULL) {
        return resized;
    }

    return freqs;
}

int main() {
    Tuple list[] = {{1, 2}, {2, 1}, {3, 4}, {4, 3}, {1, 2}, {5, 6}};
    int size = sizeof(list) / sizeof(list[0]);
    int unique_size = 0;

    TupleFreq* freqs = extract_frequencies(list, size, &unique_size);

    if (freqs != NULL) {
        for (int i = 0; i < unique_size; i++) {
            printf("(%d, %d): %d\n", freqs[i].key.a, freqs[i].key.b, freqs[i].count);
        }
        free(freqs);
    }

    return 0;
}