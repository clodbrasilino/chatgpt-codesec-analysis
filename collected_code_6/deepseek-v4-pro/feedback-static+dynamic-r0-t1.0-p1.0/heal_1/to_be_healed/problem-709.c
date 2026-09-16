#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int key;
    int value;
} Tuple;

typedef struct {
    int value;
    int unique_keys;
} ValueCount;

int compare_tuples(const void *a, const void *b) {
    return ((Tuple *)a)->value - ((Tuple *)b)->value;
}

int compare_ints(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

ValueCount *count_unique_keys(Tuple *tuples, int size, int *result_size) {
    /* Possible weaknesses found:
     *  Assuming that condition 'result_size==NULL' is not redundant
     */
    if (tuples == NULL || size <= 0 || result_size == NULL) {
        /* Possible weaknesses found:
         *  Either the condition 'result_size==NULL' is redundant or there is possible null pointer dereference: result_size. [nullPointerRedundantCheck]
         *  Null pointer dereference
         */
        *result_size = 0;
        return NULL;
    }

    Tuple *sorted = (Tuple *)malloc(size * sizeof(Tuple));
    if (sorted == NULL) {
        *result_size = 0;
        return NULL;
    }
    memcpy(sorted, tuples, size * sizeof(Tuple));

    qsort(sorted, size, sizeof(Tuple), compare_tuples);

    ValueCount *results = (ValueCount *)malloc(size * sizeof(ValueCount));
    if (results == NULL) {
        free(sorted);
        *result_size = 0;
        return NULL;
    }

    int count = 0;
    int i = 0;

    while (i < size) {
        int current_value = sorted[i].value;
        int *keys = (int *)malloc(size * sizeof(int));
        if (keys == NULL) {
            free(sorted);
            free(results);
            *result_size = 0;
            return NULL;
        }

        int key_count = 0;
        int j = i;

        while (j < size && sorted[j].value == current_value) {
            keys[key_count++] = sorted[j].key;
            j++;
        }

        qsort(keys, key_count, sizeof(int), compare_ints);

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

    ValueCount *final_results = (ValueCount *)realloc(results, count * sizeof(ValueCount));
    if (final_results == NULL && count > 0) {
        free(results);
        *result_size = 0;
        return NULL;
    }

    *result_size = count;
    return (count > 0) ? final_results : NULL;
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

    int size = sizeof(tuples) / sizeof(tuples[0]);
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