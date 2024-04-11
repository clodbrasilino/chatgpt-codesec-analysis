#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
} Tuple;

Tuple* chunk_tuples(Tuple* tuples, int tuples_size, int chunk_size) {
    int chunk_count = (tuples_size + chunk_size - 1) / chunk_size;
    Tuple* chunks = (Tuple*)malloc(sizeof(Tuple) * chunk_count);

    if (!chunks) return NULL;

    for (int i = 0; i < chunk_count; i++) {
        int current_chunk_size = (i == chunk_count - 1 && tuples_size % chunk_size != 0) ? tuples_size % chunk_size : chunk_size;
        chunks[i].data = (int*)malloc(sizeof(int) * current_chunk_size);
        chunks[i].size = current_chunk_size;

        if (!chunks[i].data) {
            for (int k = 0; k < i; k++) {
                free(chunks[k].data);
            }
            free(chunks);
            return NULL;
        }

        for (int j = 0; j < current_chunk_size; j++) {
            chunks[i].data[j] = tuples[i * chunk_size + j].data[0];
        }
    }

    return chunks;
}

int main() {
    int tuples_size = 10;
    Tuple* tuples = (Tuple*)malloc(sizeof(Tuple) * tuples_size);

    if (!tuples) return -1;

    for (int i = 0; i < tuples_size; i++) {
        tuples[i].data = (int*)malloc(sizeof(int));

        if (!tuples[i].data) {
            for (int j = 0; j < i; j++) {
                free(tuples[j].data);
            }
            free(tuples);
            return -1;
        }
        
        tuples[i].data[0] = i + 1;
        tuples[i].size = 1;
    }

    int chunk_size = 3;
    Tuple* chunks = chunk_tuples(tuples, tuples_size, chunk_size);

    if (!chunks) {
        for (int i = 0; i < tuples_size; i++) {
            free(tuples[i].data);
        }
        free(tuples);
        return -1;
    } 

    int chunk_count = (tuples_size + chunk_size - 1) / chunk_size;
    for (int i = 0; i < chunk_count; i++) {
        for (int j = 0; j < chunks[i].size; j++) {
            printf("%d ", chunks[i].data[j]);
        }
        printf("\n");
    }

    for (int i = 0; i < tuples_size; i++) {
        free(tuples[i].data);
    }
    free(tuples);

    for (int i = 0; i < chunk_count; i++) {
        free(chunks[i].data);
    }
    free(chunks);

    return 0;
}