#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    int key;
    int value;
} Tuple;

typedef struct {
    int value;
    int unique_keys;
} ValueCount;

int compare_tuples(const void *a, const void *b) {
    int va = ((const Tuple *)a)->value;
    int vb = ((const Tuple *)b)->value;
    return (va > vb) - (va < vb);
}

int compare_ints(const void *a, const void *b) {
    int ia = *(const int *)a;
    int ib = *(const int *)b;
    return (ia > ib) - (ia < ib);
}

ValueCount *count_unique_keys(const Tuple *tuples, int size, int *result_size) {
    if (tuples == NULL || size <= 0 || result_size == NULL) {
        if (result_size != NULL) {
            *result_size = 0;
        }
        return NULL;
    }

    if ((size_t)size > SIZE_MAX / sizeof(Tuple)) {
        *result_size = 0;
        return NULL;
    }

    size_t allocation_size = (size_t)size * sizeof(Tuple);
    if (allocation_size == 0 && size > 0) {
        *result_size = 0;
        return NULL;
    }

    Tuple *sorted = (Tuple *)malloc(allocation_size);
    if (sorted == NULL) {
        *result_size = 0;
        return NULL;
    }

    size_t copy_size = (size_t)size * sizeof(Tuple);
    memcpy(sorted, tuples, copy_size);

    qsort(sorted, (size_t)size, sizeof(Tuple), compare_tuples);

    if ((size_t)size > SIZE_MAX / sizeof(ValueCount)) {
        free(sorted);
        *result_size = 0;
        return NULL;
    }

    size_t results_allocation = (size_t)size * sizeof(ValueCount);
    if (results_allocation == 0 && size > 0) {
        free(sorted);
        *result_size = 0;
        return NULL;
    }

    ValueCount *results = (ValueCount *)malloc(results_allocation);
    if (results == NULL) {
        free(sorted);
        *result_size = 0;
        return NULL;
    }

    int count = 0;
    int i = 0;

    while (i < size) {
        int current_value = sorted[i].value;

        int j = i;
        while (j < size && sorted[j].value == current_value) {
            j++;
        }

        int key_count = j - i;

        if (key_count <= 0) {
            free(sorted);
            free(results);
            *result_size = 0;
            return NULL;
        }

        if ((size_t)key_count > SIZE_MAX / sizeof(int)) {
            free(sorted);
            free(results);
            *result_size = 0;
            return NULL;
        }

        size_t keys_allocation = (size_t)key_count * sizeof(int);
        if (keys_allocation == 0 && key_count > 0) {
            free(sorted);
            free(results);
            *result_size = 0;
            return NULL;
        }

        int *keys = (int *)malloc(keys_allocation);
        if (keys == NULL) {
            free(sorted);
            free(results);
            *result_size = 0;
            return NULL;
        }

        for (int k = 0; k < key_count; k++) {
            keys[k] = sorted[i + k].key;
        }

        qsort(keys, (size_t)key_count, sizeof(int), compare_ints);

        int unique = 0;
        for (int k = 0; k < key_count; k++) {
            if (k == 0 || keys[k] != keys[k - 1]) {
                unique++;
            }
        }

        results[count].value = current_value;
        results[count].unique_keys = unique;
        count++;

        free(keys);
        i = j;
    }

    free(sorted);

    if (count == 0) {
        free(results);
        *result_size = 0;
        return NULL;
    }

    ValueCount *final_results = (ValueCount *)realloc(results, (size_t)count * sizeof(ValueCount));
    if (final_results == NULL) {
        free(results);
        *result_size = 0;
        return NULL;
    }

    *result_size = count;
    return final_results;
}

int main(void) {
    Tuple tuples[] = {
        {1, 10},
        {2, 10},
        {3, 20},
        {4, 20},
        {5, 20},
        {6, 10},
        {2, 30},
        {3, 30},
        {7, 40}
    };

    int size = (int)(sizeof(tuples) / sizeof(tuples[0]));
    int result_size = 0;

    ValueCount *results = count_unique_keys(tuples, size, &result_size);

    if (results != NULL) {
        for (int i = 0; i < result_size; i++) {
            printf("Value: %d, Unique Keys: %d\n", results[i].value, results[i].unique_keys);
        }
        free(results);
    } else {
        printf("No results or error occurred.\n");
    }

    return 0;
}