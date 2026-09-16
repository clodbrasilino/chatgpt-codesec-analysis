#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    size_t length;
} Tuple;

Tuple* create_tuple(size_t n) {
    Tuple *tuple = (Tuple *)malloc(sizeof(Tuple));
    if (tuple == NULL) return NULL;
    tuple->data = (int *)calloc(n, sizeof(int));
    if (tuple->data == NULL) {
        free(tuple);
        return NULL;
    }
    tuple->length = n;
    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (tuple) {
        if (tuple->data) free(tuple->data);
        free(tuple);
    }
}

Tuple** chunk_tuples(Tuple *source, size_t chunk_size) {
    if (source == NULL || source->length == 0 || chunk_size == 0) return NULL;
    
    size_t num_chunks = (source->length + chunk_size - 1) / chunk_size;
    Tuple **chunks = (Tuple **)calloc(num_chunks, sizeof(Tuple *));
    if (chunks == NULL) return NULL;

    for (size_t i = 0; i < num_chunks; ++i) {
        chunks[i] = create_tuple(chunk_size);
        if (chunks[i] == NULL) {
            for (size_t j = 0; j < i; ++j) free_tuple(chunks[j]);
            free(chunks);
            return NULL;
        }
        size_t start = i * chunk_size;
        size_t end = (i + 1) * chunk_size > source->length ? source->length : (i + 1) * chunk_size;
        for (size_t j = start; j < end; ++j) {
            chunks[i]->data[j - start] = source->data[j];
        }
    }

    return chunks;
}

void print_tuple(Tuple *tuple) {
    if (tuple == NULL || tuple->data == NULL) return;
    for (size_t i = 0; i < tuple->length; ++i) {
        printf("%d ", tuple->data[i]);
    }
    printf("\n");
}

int main() {
    const size_t n = 10;
    const size_t chunk_size = 3;

    Tuple *source = create_tuple(n);
    if (source == NULL) return 1;

    for (size_t i = 0; i < n; ++i) {
        source->data[i] = i + 1;
    }

    Tuple **chunks = chunk_tuples(source, chunk_size);
    if (chunks == NULL) {
        free_tuple(source);
        return 1;
    }

    for (size_t i = 0; i < (n + chunk_size - 1) / chunk_size; ++i) {
        print_tuple(chunks[i]);
        free_tuple(chunks[i]);
    }

    free(chunks);
    free_tuple(source);

    return 0;
}