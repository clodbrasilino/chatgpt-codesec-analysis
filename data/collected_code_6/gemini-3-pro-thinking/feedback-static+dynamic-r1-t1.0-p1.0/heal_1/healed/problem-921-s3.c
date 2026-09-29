#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    int *data;
    size_t num_tuples;
} Chunk;

typedef struct {
    Chunk *chunks;
    size_t num_chunks;
    size_t tuple_size;
} ChunkList;

void free_chunk_list(ChunkList *list) {
    if (!list) {
        return;
    }
    if (list->chunks) {
        for (size_t i = 0; i < list->num_chunks; ++i) {
            free(list->chunks[i].data);
        }
        free(list->chunks);
    }
    free(list);
}

ChunkList* chunk_tuples(const int *source, size_t total_tuples, size_t tuple_size, size_t chunk_size) {
    if (!source || total_tuples == 0 || tuple_size == 0 || chunk_size == 0) {
        return NULL;
    }

    if (chunk_size > SIZE_MAX / tuple_size) {
        return NULL;
    }
    if ((chunk_size * tuple_size) > SIZE_MAX / sizeof(int)) {
        return NULL;
    }
    if (total_tuples > SIZE_MAX / tuple_size) {
        return NULL;
    }
    if ((total_tuples * tuple_size) > SIZE_MAX / sizeof(int)) {
        return NULL;
    }

    ChunkList *list = malloc(sizeof(ChunkList));
    if (!list) {
        return NULL;
    }

    size_t num_chunks = (total_tuples / chunk_size) + ((total_tuples % chunk_size) != 0 ? 1 : 0);
    list->num_chunks = num_chunks;
    list->tuple_size = tuple_size;

    list->chunks = calloc(num_chunks, sizeof(Chunk));
    if (!list->chunks) {
        free(list);
        return NULL;
    }

    for (size_t i = 0; i < num_chunks; ++i) {
        size_t tuples_in_this_chunk = chunk_size;
        if (i == num_chunks - 1) {
            size_t remainder = total_tuples % chunk_size;
            if (remainder != 0) {
                tuples_in_this_chunk = remainder;
            }
        }

        list->chunks[i].num_tuples = tuples_in_this_chunk;
        
        size_t elements_to_copy = tuples_in_this_chunk * tuple_size;
        list->chunks[i].data = malloc(elements_to_copy * sizeof(int));

        if (!list->chunks[i].data) {
            list->num_chunks = i;
            free_chunk_list(list);
            return NULL;
        }

        size_t offset = i * chunk_size * tuple_size;
        for (size_t j = 0; j < elements_to_copy; ++j) {
            list->chunks[i].data[j] = source[offset + j];
        }
    }

    return list;
}

int main(void) {
    size_t total_tuples = 10;
    size_t tuple_size = 3;
    size_t chunk_size = 4;
    
    if (total_tuples > SIZE_MAX / tuple_size || (total_tuples * tuple_size) > SIZE_MAX / sizeof(int)) {
        return EXIT_FAILURE;
    }

    size_t total_elements = total_tuples * tuple_size;
    int *source = malloc(total_elements * sizeof(int));
    if (!source) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < total_elements; ++i) {
        source[i] = (int)i;
    }

    ChunkList *result = chunk_tuples(source, total_tuples, tuple_size, chunk_size);
    if (!result) {
        free(source);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < result->num_chunks; ++i) {
        printf("Chunk %zu:\n", i);
        for (size_t j = 0; j < result->chunks[i].num_tuples; ++j) {
            printf("  Tuple %zu: ", j);
            for (size_t k = 0; k < result->tuple_size; ++k) {
                printf("%d ", result->chunks[i].data[j * result->tuple_size + k]);
            }
            printf("\n");
        }
    }

    free_chunk_list(result);
    free(source);

    return EXIT_SUCCESS;
}