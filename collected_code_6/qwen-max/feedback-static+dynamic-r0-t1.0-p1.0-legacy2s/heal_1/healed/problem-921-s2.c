#include <stdio.h>
#include <stdlib.h>

#define TUPLE_SIZE 4

typedef struct {
    int values[TUPLE_SIZE];
} Tuple;

Tuple* create_tuple(const int arr[]) {
    Tuple *t = (Tuple*) malloc(sizeof(Tuple));
    if (t) {
        for (int i = 0; i < TUPLE_SIZE; ++i) {
            t->values[i] = arr[i];
        }
    }
    return t;
}

void free_tuple(Tuple *t) {
    free(t);
}

int get_chunk_size(int total, int chunk_count) {
    if (chunk_count <= 0 || total <= 0) {
        return 0;
    }
    return (total + chunk_count - 1) / chunk_count;
}

Tuple** chunk_tuples(Tuple *tuples[], int count, int chunk_size, int *chunks_count) {
    *chunks_count = get_chunk_size(count, chunk_size);

    if (*chunks_count == 0) {
        return NULL;
    }

    Tuple **chunks = (Tuple**) malloc(*chunks_count * sizeof(Tuple*));
    if (!chunks) {
        return NULL;
    }

    for (int i = 0; i < *chunks_count; ++i) {
        chunks[i] = (Tuple*) malloc(chunk_size * sizeof(Tuple));
        if (!chunks[i]) {
            while (i--) {
                free(chunks[i]);
            }
            free(chunks);
            return NULL;
        }
        int start = i * chunk_size;
        int end = (i + 1) * chunk_size < count ? (i + 1) * chunk_size : count;
        for (int j = start; j < end; ++j) {
            chunks[i][j - start] = *tuples[j];
        }
    }
    return chunks;
}

int main() {
    const int data[5][TUPLE_SIZE] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16},
        {17, 18, 19, 20}
    };

    Tuple *tuples[5];
    for (int i = 0; i < 5; ++i) {
        tuples[i] = create_tuple(data[i]);
    }

    int chunk_count;
    Tuple **chunks = chunk_tuples(tuples, 5, 2, &chunk_count);

    if (chunks) {
        for (int i = 0; i < chunk_count; ++i) {
            for (int j = 0; j < 2; ++j) {
                for (int k = 0; k < TUPLE_SIZE; ++k) {
                    printf("%d ", chunks[i][j].values[k]);
                }
                printf("\n");
            }
            printf("---\n");
        }
        for (int i = 0; i < 5; ++i) {
            free_tuple(tuples[i]);
        }
        for (int i = 0; i < chunk_count; ++i) {
            free(chunks[i]);
        }
        free(chunks);
    } else {
        for (int i = 0; i < 5; ++i) {
            free_tuple(tuples[i]);
        }
    }

    return 0;
}