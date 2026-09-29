#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
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

static int safe_size_multiply(size_t a, size_t b, size_t *result) {
    if (a > 0 && b > SIZE_MAX / a) {
        return 0;
    }
    *result = a * b;
    return 1;
}

static int safe_add(size_t a, size_t b, size_t *result) {
    if (a > SIZE_MAX - b) {
        return 0;
    }
    *result = a + b;
    return 1;
}

static void cleanup_partial(TupleList *result, int up_to) {
    for (int k = 0; k < up_to; k++) {
        free(result->tuples[k].elements);
        result->tuples[k].elements = NULL;
    }
    free(result->tuples);
    result->tuples = NULL;
    result->count = 0;
}

static TupleList join_tuples_impl(Tuple *tuples, int tuple_count) {
    TupleList result;
    result.tuples = NULL;
    result.count = 0;

    if (tuples == NULL || tuple_count <= 0) {
        return result;
    }

    qsort(tuples, (size_t)tuple_count, sizeof(Tuple), compare_tuples);

    result.tuples = malloc(sizeof(Tuple) * (size_t)tuple_count);
    if (result.tuples == NULL) {
        return result;
    }

    int result_count = 0;
    int i = 0;

    while (i < tuple_count) {
        int j = i;
        size_t total_size = 0;

        while (j < tuple_count && tuples[i].elements[0] == tuples[j].elements[0]) {
            size_t new_total;
            if (!safe_add(total_size, (size_t)tuples[j].size, &new_total)) {
                cleanup_partial(&result, result_count);
                return result;
            }
            total_size = new_total;
            j++;
        }

        if (total_size > (size_t)INT_MAX) {
            cleanup_partial(&result, result_count);
            return result;
        }

        size_t alloc_size;
        if (!safe_size_multiply(total_size, sizeof(int), &alloc_size)) {
            cleanup_partial(&result, result_count);
            return result;
        }

        if (total_size == 0) {
            result.tuples[result_count].elements = NULL;
            result.tuples[result_count].size = 0;
            result_count++;
            i = j;
            continue;
        }

        result.tuples[result_count].elements = malloc(alloc_size);
        if (result.tuples[result_count].elements == NULL) {
            cleanup_partial(&result, result_count);
            return result;
        }

        result.tuples[result_count].size = (int)total_size;
        size_t pos = 0;

        for (int k = i; k < j; k++) {
            size_t copy_bytes;
            if (!safe_size_multiply((size_t)tuples[k].size, sizeof(int), &copy_bytes)) {
                free(result.tuples[result_count].elements);
                result.tuples[result_count].elements = NULL;
                cleanup_partial(&result, result_count);
                return result;
            }

            if (copy_bytes > 0) {
                size_t available = alloc_size - pos;
                if (copy_bytes > available) {
                    free(result.tuples[result_count].elements);
                    result.tuples[result_count].elements = NULL;
                    cleanup_partial(&result, result_count);
                    return result;
                }
                memcpy((char *)result.tuples[result_count].elements + pos,
                       tuples[k].elements, copy_bytes);
            }

            pos += copy_bytes;
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
        list->tuples[i].elements = NULL;
    }
    free(list->tuples);
    list->tuples = NULL;
    list->count = 0;
}

int main(void) {
    int elements1[] = {1, 2, 3};
    int elements2[] = {1, 4};
    int elements3[] = {2, 5, 6, 7};
    int elements4[] = {2, 8};
    int elements5[] = {3, 9};

    Tuple t1 = {elements1, 3};
    Tuple t2 = {elements2, 2};
    Tuple t3 = {elements3, 4};
    Tuple t4 = {elements4, 2};
    Tuple t5 = {elements5, 2};

    Tuple tuples[] = {t1, t2, t3, t4, t5};
    int tuple_count = (int)(sizeof(tuples) / sizeof(tuples[0]));

    TupleList result = join_tuples_impl(tuples, tuple_count);

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