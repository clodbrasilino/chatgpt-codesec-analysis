#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    int *data;
    size_t length;
} IntList;

typedef struct {
    IntList *lists;
    size_t count;
} ListOfLists;

static IntList *zip_lists(const ListOfLists *a, const ListOfLists *b, size_t *out_count)
{
    IntList *result = NULL;
    size_t n;
    size_t i;

    if (a == NULL || b == NULL || out_count == NULL) {
        return NULL;
    }

    if (a->lists == NULL || b->lists == NULL) {
        *out_count = 0;
        return NULL;
    }

    n = (a->count < b->count) ? a->count : b->count;
    if (n == 0) {
        *out_count = 0;
        return NULL;
    }

    result = calloc(n, sizeof(IntList));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < n; i++) {
        size_t len_a = a->lists[i].length;
        size_t len_b = b->lists[i].length;
        size_t total;

        if (len_a > SIZE_MAX - len_b) {
            size_t j;
            for (j = 0; j < i; j++) {
                free(result[j].data);
            }
            free(result);
            return NULL;
        }

        total = len_a + len_b;

        if (total > SIZE_MAX / sizeof(int)) {
            size_t j;
            for (j = 0; j < i; j++) {
                free(result[j].data);
            }
            free(result);
            return NULL;
        }

        if (total > 0) {
            result[i].data = malloc(total * sizeof(int));
            if (result[i].data == NULL) {
                size_t j;
                for (j = 0; j < i; j++) {
                    free(result[j].data);
                }
                free(result);
                return NULL;
            }
            if (len_a > 0 && a->lists[i].data != NULL) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result[i].data, a->lists[i].data, len_a * sizeof(int));
            }
            if (len_b > 0 && b->lists[i].data != NULL) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result[i].data + len_a, b->lists[i].data, len_b * sizeof(int));
            }
        } else {
            result[i].data = NULL;
        }
        result[i].length = total;
    }

    *out_count = n;
    return result;
}

static void free_zipped(IntList *zipped, size_t count)
{
    size_t i;

    if (zipped == NULL) {
        return;
    }
    for (i = 0; i < count; i++) {
        free(zipped[i].data);
    }
    free(zipped);
}

static void print_zipped(const IntList *zipped, size_t count)
{
    size_t i;
    size_t j;

    if (zipped == NULL) {
        printf("[]\n");
        return;
    }

    printf("[");
    for (i = 0; i < count; i++) {
        printf("[");
        for (j = 0; j < zipped[i].length; j++) {
            printf("%d", zipped[i].data[j]);
            if (j + 1 < zipped[i].length) {
                printf(", ");
            }
        }
        printf("]");
        if (i + 1 < count) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(void)
{
    int a0[] = {1, 2};
    int a1[] = {3, 4};
    int a2[] = {5, 6};
    int b0[] = {7, 8};
    int b1[] = {9, 10};
    int b2[] = {11, 12};

    IntList a_lists[3];
    IntList b_lists[3];
    ListOfLists a;
    ListOfLists b;
    IntList *zipped = NULL;
    size_t zipped_count = 0;

    a_lists[0].data = a0;
    a_lists[0].length = 2;
    a_lists[1].data = a1;
    a_lists[1].length = 2;
    a_lists[2].data = a2;
    a_lists[2].length = 2;

    b_lists[0].data = b0;
    b_lists[0].length = 2;
    b_lists[1].data = b1;
    b_lists[1].length = 2;
    b_lists[2].data = b2;
    b_lists[2].length = 2;

    a.lists = a_lists;
    a.count = 3;
    b.lists = b_lists;
    b.count = 3;

    zipped = zip_lists(&a, &b, &zipped_count);
    if (zipped == NULL) {
        fprintf(stderr, "Failed to zip lists or lists are empty\n");
        return EXIT_FAILURE;
    }

    print_zipped(zipped, zipped_count);
    free_zipped(zipped, zipped_count);

    return EXIT_SUCCESS;
}