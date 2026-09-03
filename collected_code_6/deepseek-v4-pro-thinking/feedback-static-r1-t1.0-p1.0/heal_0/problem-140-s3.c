#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    int value;
    size_t count;
} Freq;

static int compare_int_for_sort(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x > y) - (x < y);
}

static int compare_freq_key(const void *key, const void *elem) {
    int k = *(const int *)key;
    const Freq *f = (const Freq *)elem;
    return (k > f->value) - (k < f->value);
}

int *extract_singly(const Tuple *tuples, size_t n, size_t *out_size) {
    if (out_size != NULL) {
        *out_size = 0;
    }
    if (tuples == NULL || n == 0) {
        return NULL;
    }
    if (n > SIZE_MAX / 2) {
        return NULL;
    }
    size_t total = 2 * n;
    if (total > SIZE_MAX / sizeof(int)) {
        return NULL;
    }

    int *flat = malloc(total * sizeof(int));
    if (flat == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < n; ++i) {
        flat[2 * i] = tuples[i].first;
        flat[2 * i + 1] = tuples[i].second;
    }

    int *sorted = malloc(total * sizeof(int));
    if (sorted == NULL) {
        free(flat);
        return NULL;
    }
    for (size_t i = 0; i < total; ++i) {
        sorted[i] = flat[i];
    }
    qsort(sorted, total, sizeof(int), compare_int_for_sort);

    if (total > SIZE_MAX / sizeof(Freq)) {
        free(flat);
        free(sorted);
        return NULL;
    }

    Freq *freq = malloc(total * sizeof(Freq));
    if (freq == NULL) {
        free(flat);
        free(sorted);
        return NULL;
    }

    size_t unique = 0;
    size_t i = 0;
    while (i < total) {
        int value = sorted[i];
        size_t j = i + 1;
        while (j < total && sorted[j] == value) {
            ++j;
        }
        freq[unique].value = value;
        freq[unique].count = j - i;
        ++unique;
        i = j;
    }

    int *result = malloc(total * sizeof(int));
    if (result == NULL) {
        free(flat);
        free(sorted);
        free(freq);
        return NULL;
    }

    size_t count = 0;
    for (size_t k = 0; k < total; ++k) {
        int value = flat[k];
        Freq *found = bsearch(&value, freq, unique, sizeof(Freq), compare_freq_key);
        if (found != NULL && found->count == 1) {
            result[count++] = value;
        }
    }

    free(flat);
    free(sorted);
    free(freq);

    if (count == 0) {
        free(result);
        if (out_size != NULL) {
            *out_size = 0;
        }
        return NULL;
    }

    int *shrunk = realloc(result, count * sizeof(int));
    if (shrunk == NULL) {
        free(result);
        return NULL;
    }

    if (out_size != NULL) {
        *out_size = count;
    }
    return shrunk;
}

int main(void) {
    Tuple tuples[] = {
        {1, 2},
        {3, 4},
        {1, 5},
        {2, 6}
    };
    size_t out_size = 0;
    int *result = extract_singly(tuples, sizeof(tuples) / sizeof(tuples[0]), &out_size);
    if (result != NULL) {
        for (size_t i = 0; i < out_size; ++i) {
            printf("%d", result[i]);
            if (i + 1 < out_size) {
                printf(" ");
            }
        }
        printf("\n");
        free(result);
    } else {
        printf("No singly occurring elements.\n");
    }
    return 0;
}