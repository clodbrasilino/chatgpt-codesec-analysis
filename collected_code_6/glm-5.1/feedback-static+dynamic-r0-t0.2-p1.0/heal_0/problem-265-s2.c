#include <stdio.h>
#include <stdlib.h>

int** split_list(const int* list, size_t list_len, size_t n, size_t* out_len, size_t** out_inner_lens) {
    if (list == NULL || n == 0 || out_len == NULL || out_inner_lens == NULL) {
        return NULL;
    }

    size_t num_chunks = (list_len + n - 1) / n;
    *out_len = num_chunks;

    int** result = (int**)malloc(num_chunks * sizeof(int*));
    if (result == NULL) {
        return NULL;
    }

    *out_inner_lens = (size_t*)malloc(num_chunks * sizeof(size_t));
    if (*out_inner_lens == NULL) {
        free(result);
        return NULL;
    }

    for (size_t i = 0; i < num_chunks; i++) {
        size_t start = i * n;
        size_t chunk_len = (start + n > list_len) ? (list_len - start) : n;
        (*out_inner_lens)[i] = chunk_len;

        result[i] = (int*)malloc(chunk_len * sizeof(int));
        if (result[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(result[j]);
            }
            free(*out_inner_lens);
            free(result);
            *out_inner_lens = NULL;
            *out_len = 0;
            return NULL;
        }

        for (size_t k = 0; k < chunk_len; k++) {
            result[i][k] = list[start + k];
        }
    }

    return result;
}

void free_split_list(int** split_list, size_t out_len, size_t* inner_lens) {
    if (split_list == NULL) {
        return;
    }
    for (size_t i = 0; i < out_len; i++) {
        free(split_list[i]);
    }
    free(split_list);
    free(inner_lens);
}

int main(void) {
    int list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t list_len = sizeof(list) / sizeof(list[0]);
    size_t n = 3;
    size_t out_len = 0;
    size_t* inner_lens = NULL;

    int** result = split_list(list, list_len, n, &out_len, &inner_lens);

    if (result != NULL) {
        for (size_t i = 0; i < out_len; i++) {
            for (size_t j = 0; j < inner_lens[i]; j++) {
                printf("%d ", result[i][j]);
            }
            printf("\n");
        }
        free_split_list(result, out_len, inner_lens);
    }

    return 0;
}