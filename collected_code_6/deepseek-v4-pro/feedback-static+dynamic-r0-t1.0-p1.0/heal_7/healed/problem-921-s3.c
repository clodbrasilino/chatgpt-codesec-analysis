#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t count;
    size_t chunk_size;
} TupleChunk;

typedef struct {
    TupleChunk *chunks;
    size_t count;
    size_t capacity;
} ChunkList;

void init_chunk_list(ChunkList *list) {
    list->chunks = NULL;
    list->count = 0;
    list->capacity = 0;
}

void free_chunk_list(ChunkList *list) {
    size_t i;
    if (list == NULL) {
        return;
    }
    for (i = 0; i < list->count; i++) {
        size_t j;
        for (j = 0; j < list->chunks[i].count; j++) {
            free(list->chunks[i].tuples[j].data);
        }
        free(list->chunks[i].tuples);
    }
    free(list->chunks);
    list->chunks = NULL;
    list->count = 0;
    list->capacity = 0;
}

int add_chunk(ChunkList *list, TupleChunk chunk) {
    if (list->count == list->capacity) {
        size_t new_capacity = list->capacity == 0 ? 8 : list->capacity * 2;
        if (new_capacity > SIZE_MAX / sizeof(TupleChunk)) {
            return 0;
        }
        TupleChunk *new_chunks = (TupleChunk *)realloc(list->chunks, new_capacity * sizeof(TupleChunk));
        if (new_chunks == NULL) {
            return 0;
        }
        list->chunks = new_chunks;
        list->capacity = new_capacity;
    }
    
    list->chunks[list->count] = chunk;
    list->count++;
    return 1;
}

static int copy_tuple_data(Tuple *dest, const Tuple *src) {
    size_t size_in_bytes;
    
    if (src->size > SIZE_MAX / sizeof(int)) {
        return 0;
    }
    
    if (src->size > 0 && src->data == NULL) {
        return 0;
    }
    
    if (src->size == 0) {
        dest->data = NULL;
        dest->size = 0;
        return 1;
    }
    
    size_in_bytes = src->size * sizeof(int);
    if (size_in_bytes == 0 && src->size > 0) {
        return 0;
    }
    
    dest->data = (int *)malloc(size_in_bytes);
    if (dest->data == NULL) {
        return 0;
    }
    
    if (src->data != NULL) {
        size_t i;
        for (i = 0; i < src->size; i++) {
            dest->data[i] = src->data[i];
        }
    }
    
    dest->size = src->size;
    return 1;
}

ChunkList chunk_tuples(const Tuple *tuples, size_t tuple_count, size_t n) {
    ChunkList result;
    size_t i;
    size_t current_chunk_size = 0;
    TupleChunk current_chunk;
    
    init_chunk_list(&result);
    
    if (tuples == NULL || n == 0 || tuple_count == 0) {
        return result;
    }
    
    if (n > SIZE_MAX / sizeof(Tuple)) {
        return result;
    }
    
    current_chunk.tuples = (Tuple *)malloc(n * sizeof(Tuple));
    if (current_chunk.tuples == NULL) {
        return result;
    }
    current_chunk.chunk_size = n;
    current_chunk.count = 0;
    
    for (i = 0; i < tuple_count; i++) {
        if (current_chunk_size == n) {
            if (!add_chunk(&result, current_chunk)) {
                size_t j;
                for (j = 0; j < current_chunk.count; j++) {
                    free(current_chunk.tuples[j].data);
                }
                free(current_chunk.tuples);
                free_chunk_list(&result);
                init_chunk_list(&result);
                return result;
            }
            current_chunk.tuples = (Tuple *)malloc(n * sizeof(Tuple));
            if (current_chunk.tuples == NULL) {
                free_chunk_list(&result);
                init_chunk_list(&result);
                return result;
            }
            current_chunk.chunk_size = n;
            current_chunk.count = 0;
            current_chunk_size = 0;
        }
        
        if (!copy_tuple_data(&current_chunk.tuples[current_chunk_size], &tuples[i])) {
            size_t j;
            for (j = 0; j < current_chunk_size; j++) {
                free(current_chunk.tuples[j].data);
            }
            free(current_chunk.tuples);
            free_chunk_list(&result);
            init_chunk_list(&result);
            return result;
        }
        
        current_chunk.count++;
        current_chunk_size++;
    }
    
    if (current_chunk_size > 0) {
        Tuple *shrunk_tuples = (Tuple *)realloc(current_chunk.tuples, current_chunk_size * sizeof(Tuple));
        if (shrunk_tuples != NULL) {
            current_chunk.tuples = shrunk_tuples;
        }
        current_chunk.chunk_size = current_chunk_size;
        if (!add_chunk(&result, current_chunk)) {
            size_t j;
            for (j = 0; j < current_chunk.count; j++) {
                free(current_chunk.tuples[j].data);
            }
            free(current_chunk.tuples);
            free_chunk_list(&result);
            init_chunk_list(&result);
            return result;
        }
    } else {
        free(current_chunk.tuples);
    }
    
    return result;
}

Tuple *create_tuple(const int *data, size_t size) {
    Tuple *tuple;
    size_t size_in_bytes;
    
    if (data == NULL || size == 0) {
        return NULL;
    }
    
    if (size > SIZE_MAX / sizeof(int)) {
        return NULL;
    }
    
    tuple = (Tuple *)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }
    
    size_in_bytes = size * sizeof(int);
    if (size_in_bytes == 0 && size > 0) {
        free(tuple);
        return NULL;
    }
    
    tuple->data = (int *)malloc(size_in_bytes);
    if (tuple->data == NULL) {
        free(tuple);
        return NULL;
    }
    
    {
        size_t i;
        for (i = 0; i < size; i++) {
            tuple->data[i] = data[i];
        }
    }
    
    tuple->size = size;
    return tuple;
}

void free_tuples(Tuple *tuples, size_t count) {
    size_t i;
    if (tuples == NULL) {
        return;
    }
    for (i = 0; i < count; i++) {
        free(tuples[i].data);
    }
    free(tuples);
}

int main(void) {
    size_t i, j;
    Tuple *tuples;
    int data[][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
        {10, 11, 12},
        {13, 14, 15}
    };
    size_t tuple_count = sizeof(data) / sizeof(data[0]);
    size_t tuple_size = sizeof(data[0]) / sizeof(data[0][0]);
    size_t chunk_size = 2;
    ChunkList chunks;
    
    if (tuple_count > SIZE_MAX / sizeof(Tuple)) {
        return 1;
    }
    
    if (tuple_size > SIZE_MAX / sizeof(int)) {
        return 1;
    }
    
    tuples = (Tuple *)malloc(tuple_count * sizeof(Tuple));
    if (tuples == NULL) {
        return 1;
    }
    
    for (i = 0; i < tuple_count; i++) {
        size_t size_in_bytes = tuple_size * sizeof(int);
        if (size_in_bytes > SIZE_MAX / 2) {
            for (j = 0; j < i; j++) {
                free(tuples[j].data);
            }
            free(tuples);
            return 1;
        }
        
        tuples[i].data = (int *)malloc(size_in_bytes);
        if (tuples[i].data == NULL) {
            for (j = 0; j < i; j++) {
                free(tuples[j].data);
            }
            free(tuples);
            return 1;
        }
        
        {
            size_t k;
            for (k = 0; k < tuple_size; k++) {
                tuples[i].data[k] = data[i][k];
            }
        }
        
        tuples[i].size = tuple_size;
    }
    
    chunks = chunk_tuples(tuples, tuple_count, chunk_size);
    
    printf("Number of chunks: %zu\n", chunks.count);
    for (i = 0; i < chunks.count; i++) {
        printf("Chunk %zu (size: %zu):\n", i, chunks.chunks[i].chunk_size);
        for (j = 0; j < chunks.chunks[i].count; j++) {
            size_t k;
            printf("  Tuple %zu: [", j);
            for (k = 0; k < chunks.chunks[i].tuples[j].size; k++) {
                printf("%d", chunks.chunks[i].tuples[j].data[k]);
                if (k < chunks.chunks[i].tuples[j].size - 1) {
                    printf(", ");
                }
            }
            printf("]\n");
        }
    }
    
    free_tuples(tuples, tuple_count);
    free_chunk_list(&chunks);
    
    return 0;
}