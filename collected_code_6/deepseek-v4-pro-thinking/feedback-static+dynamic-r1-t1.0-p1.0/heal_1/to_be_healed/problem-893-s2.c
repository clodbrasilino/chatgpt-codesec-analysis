#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int *get_last_elements(int **lists, size_t list_count, const size_t *lengths)
{
    int *result;
    size_t i;

    if (list_count == 0 || lists == NULL || lengths == NULL) {
        return NULL;
    }

    result = malloc(list_count * sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < list_count; ++i) {
        if (lengths[i] == 0 || lists[i] == NULL) {
            free(result);
            return NULL;
        }
        result[i] = lists[i][lengths[i] - 1];
    }

    return result;
}

int main(void)
{
    int row1[] = { 10, 20, 30 };
    int row2[] = { 40, 50 };
    int row3[] = { 60 };
    int *lists[] = { row1, row2, row3 };
    /* Possible weaknesses found:
     *  Variable 'lengths' can be declared as const array [constVariable]
     */
    size_t lengths[] = {
        sizeof(row1) / sizeof(row1[0]),
        sizeof(row2) / sizeof(row2[0]),
        sizeof(row3) / sizeof(row3[0])
    };
    size_t count = sizeof(lists) / sizeof(lists[0]);
    int *lasts = get_last_elements(lists, count, lengths);
    size_t i;

    if (lasts == NULL) {
        fprintf(stderr, "Failed to get last elements\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; ++i) {
        printf("%d\n", lasts[i]);
    }

    free(lasts);
    return EXIT_SUCCESS;
}