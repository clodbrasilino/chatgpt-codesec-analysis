#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t count;
    int value;
} rle_run;

int rle_encode(const int *list, size_t len, rle_run **out, size_t *out_len) {
    if (out == NULL || out_len == NULL) {
        return -1;
    }
    *out = NULL;
    *out_len = 0;
    if (len > 0 && list == NULL) {
        return -1;
    }
    if (len > 0 && len > (size_t)-1 / sizeof(rle_run)) {
        return -1;
    }
    if (len == 0) {
        return 0;
    }
    rle_run *runs = malloc(len * sizeof(rle_run));
    if (runs == NULL) {
        return -1;
    }
    size_t run_count = 0;
    for (size_t i = 0; i < len; ) {
        int value = list[i];
        size_t j = i + 1;
        while (j < len && list[j] == value) {
            j++;
        }
        runs[run_count].count = j - i;
        runs[run_count].value = value;
        run_count++;
        i = j;
    }
    *out = runs;
    *out_len = run_count;
    return 0;
}

int rle_decode(const rle_run *runs, size_t run_count, int **out, size_t *out_len) {
    if (out == NULL || out_len == NULL) {
        return -1;
    }
    *out = NULL;
    *out_len = 0;
    if (run_count > 0 && runs == NULL) {
        return -1;
    }
    size_t total = 0;
    for (size_t i = 0; i < run_count; i++) {
        if (runs[i].count > (size_t)-1 - total) {
            return -1;
        }
        total += runs[i].count;
    }
    if (total > 0) {
        if (total > (size_t)-1 / sizeof(int)) {
            return -1;
        }
        int *decoded = malloc(total * sizeof(int));
        if (decoded == NULL) {
            return -1;
        }
        size_t pos = 0;
        for (size_t i = 0; i < run_count; i++) {
            for (size_t j = 0; j < runs[i].count; j++) {
                decoded[pos++] = runs[i].value;
            }
        }
        *out = decoded;
        *out_len = total;
    } else {
        *out = NULL;
        *out_len = 0;
    }
    return 0;
}

int main(void) {
    int list[] = {1, 1, 2, 2, 2, 3, 4, 4, 4, 4};
    size_t len = sizeof(list) / sizeof(list[0]);
    rle_run *runs = NULL;
    size_t run_count = 0;
    if (rle_encode(list, len, &runs, &run_count) != 0) {
        return 1;
    }
    for (size_t i = 0; i < run_count; i++) {
        printf("(%zu, %d)\n", runs[i].count, runs[i].value);
    }
    int *decoded = NULL;
    size_t decoded_len = 0;
    if (rle_decode(runs, run_count, &decoded, &decoded_len) != 0) {
        free(runs);
        return 1;
    }
    for (size_t i = 0; i < decoded_len; i++) {
        printf("%d ", decoded[i]);
    }
    printf("\n");
    free(decoded);
    free(runs);
    return 0;
}