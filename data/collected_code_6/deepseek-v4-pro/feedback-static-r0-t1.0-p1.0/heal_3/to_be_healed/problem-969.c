#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    int *elements;
    int size;
} Tuple;

typedef struct {
    Tuple *tuples;
    int count;
} TupleList;

int compare_tuples(const void *a, const void *b) {
    const Tuple *ta = (const Tuple *)a;
    const Tuple *tb = (const Tuple *)b;
    if (ta->size == 0 || tb->size == 0)
        return 0;
    return ta->elements[0] - tb->elements[0];
}

TupleList join_tuples(Tuple *tuples, int tuple_count) {
    TupleList result;
    result.tuples = NULL;
    result.count = 0;

    if (tuples == NULL || tuple_count <= 0) {
        return result;
    }

    qsort(tuples, tuple_count, sizeof(Tuple), compare_tuples);

    result.tuples = malloc(sizeof(Tuple) * tuple_count);
    if (result.tuples == NULL) {
        return result;
    }

    int result_count = 0;
    int i = 0;

    while (i < tuple_count) {
        int j = i;
        size_t total_size = 0;
        while (j < tuple_count && tuples[i].elements[0] == tuples[j].elements[0]) {
            if (tuples[j].size < 0) {
                for (int k = 0; k < result_count; k++) {
                    free(result.tuples[k].elements);
                }
                free(result.tuples);
                result.tuples = NULL;
                result.count = 0;
                return result;
            }
            if (total_size > SIZE_MAX - (size_t)tuples[j].size) {
                for (int k = 0; k < result_count; k++) {
                    free(result.tuples[k].elements);
                }
                free(result.tuples);
                result.tuples = NULL;
                result.count = 0;
                return result;
            }
            total_size += (size_t)tuples[j].size;
            j++;
        }

        if (total_size > SIZE_MAX / sizeof(int)) {
            for (int k = 0; k < result_count; k++) {
                free(result.tuples[k].elements);
            }
            free(result.tuples);
            result.tuples = NULL;
            result.count = 0;
            return result;
        }

        result.tuples[result_count].elements = malloc(sizeof(int) * total_size);
        if (result.tuples[result_count].elements == NULL) {
            for (int k = 0; k < result_count; k++) {
                free(result.tuples[k].elements);
            }
            free(result.tuples);
            result.tuples = NULL;
            result.count = 0;
            return result;
        }

        result.tuples[result_count].size = (int)total_size;
        size_t pos = 0;
        for (int k = i; k < j; k++) {
            size_t copy_size = sizeof(int) * (size_t)tuples[k].size;
            if (pos + (size_t)tuples[k].size > total_size) {
                free(result.tuples[result_count].elements);
                for (int m = 0; m < result_count; m++) {
                    free(result.tuples[m].elements);
                }
                free(result.tuples);
                result.tuples = NULL;
                result.count = 0;
                return result;
            }
            if (copy_size > 0) {
                int *dest = result.tuples[result_count].elements + pos;
                size_t dest_remaining = (total_size - pos) * sizeof(int);
                if (copy_size > dest_remaining) {
                    free(result.tuples[result_count].elements);
                    for (int m = 0; m < result_count; m++) {
                        free(result.tuples[m].elements);
                    }
                    free(result.tuples);
                    result.tuples = NULL;
                    result.count = 0;
                    return result;
                }
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(dest, tuples[k].elements, copy_size);
            }
            pos += (size_t)tuples[k].size;
        }

        result_count++;
        i = j;
    }

    result.count = result_count;
    return result;
}

void free_tuple_list(TupleList *list) {
    if (list == NULL || list->tuples == NULL) {
        return;
    }
    for (int i = 0; i < list->count; i++) {
        free(list->tuples[i].elements);
    }
    free(list->tuples);
    list->tuples = NULL;
    list->count = 0;
}

int main(void) {
    int a1[] = {1, 2, 3};
    int a2[] = {1, 4};
    int a3[] = {2, 5, 6, 7};
    int a4[] = {2, 8};
    int a5[] = {3, 9};

    Tuple t1 = {a1, 3};
    Tuple t2 = {a2, 2};
    Tuple t3 = {a3, 4};
    Tuple t4 = {a4, 2};
    Tuple t5 = {a5, 2};

    Tuple tuples[] = {t1, t2, t3, t4, t5};
    int tuple_count = sizeof(tuples) / sizeof(tuples[0]);

    TupleList result = join_tuples(tuples, tuple_count);

    if (result.tuples == NULL) {
        return 1;
    }

    for (int i = 0; i < result.count; i++) {
        printf("(");
        for (int j = 0; j < result.tuples[i].size; j++) {
            printf("%d", result.tuples[i].elements[j]);
            if (j < result.tuples[i].size - 1) {
                printf(", ");
            }
        }
        printf(")\n");
    }

    free_tuple_list(&result);
    return 0;
}