#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

Tuple *chunk_tuples(const int *arr, size_t count, size_t n, size_t *out_count);
void free_chunks(Tuple *chunks, size_t num_chunks);

Tuple *chunk_tuples(const int *arr, size_t count, size_t n, size_t *out_count)
{
    Tuple *chunks;
    size_t num_chunks;
    size_t i;

    if (out_count == NULL) {
        return NULL;
    }
    *out_count = 0;

    if (arr == NULL || n == 0 || count == 0) {
        return NULL;
    }

    num_chunks = count / n + ((count % n != 0) ? 1 : 0);

    if (num_chunks > SIZE_MAX / sizeof(*chunks)) {
        return NULL;
    }

    chunks = malloc(num_chunks * sizeof(*chunks));
    if (chunks == NULL) {
        return NULL;
    }

    for (i = 0; i < num_chunks; i++) {
        size_t start = i * n;
        size_t remaining = count - start;
        size_t chunk_size = (remaining < n) ? remaining : n;
        size_t j;

        chunks[i].data = malloc(chunk_size * sizeof(*chunks[i].data));
        if (chunks[i].data == NULL) {
            size_t k;
            for (k = 0; k < i; k++) {
                free(chunks[k].data);
                chunks[k].data = NULL;
            }
            free(chunks);
            return NULL;
        }
        chunks[i].size = chunk_size;

        for (j = 0; j < chunk_size; j++) {
            chunks[i].data[j] = arr[start + j];
        }
    }

    *out_count = num_chunks;
    return chunks;
}

void free_chunks(Tuple *chunks, size_t num_chunks)
{
    size_t i;

    if (chunks == NULL) {
        return;
    }

    for (i = 0; i < num_chunks; i++) {
        free(chunks[i].data);
        chunks[i].data = NULL;
    }
    free(chunks);
}

int main(void)
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t count = sizeof(arr) / sizeof(arr[0]);
    size_t n = 3;
    size_t num_chunks = 0;
    size_t i;
    Tuple *chunks;

    chunks = chunk_tuples(arr, count, n, &num_chunks);
    if (chunks == NULL) {
        fprintf(stderr, "Error: failed to chunk tuples\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < num_chunks; i++) {
        size_t j;
        printf("(");
        for (j = 0; j < chunks[i].size; j++) {
            printf("%d%s", chunks[i].data[j],
                   (j + 1 < chunks[i].size) ? ", " : "");
        }
        printf(")%s", (i + 1 < num_chunks) ? " " : "\n");
    }

    free_chunks(chunks, num_chunks);
    return EXIT_SUCCESS;
}