#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int *data;
    size_t length;
} Sublist;

int find_min_length_sublist(const Sublist *sublists, size_t count, size_t *min_index)
{
    size_t i;

    if (sublists == NULL || min_index == NULL || count == 0) {
        return -1;
    }

    *min_index = 0;
    for (i = 0; i < count; i++) {
        if (sublists[i].data == NULL && sublists[i].length > 0) {
            return -1;
        }
        if (sublists[i].length < sublists[*min_index].length) {
            *min_index = i;
        }
    }

    return 0;
}

static Sublist create_sublist(const int *values, size_t length)
{
    Sublist s;
    size_t i;

    s.data = NULL;
    s.length = 0;

    if (values == NULL || length == 0) {
        return s;
    }

    if (length > SIZE_MAX / sizeof(int)) {
        return s;
    }

    s.data = (int *)malloc(length * sizeof(int));
    if (s.data == NULL) {
        return s;
    }

    for (i = 0; i < length; i++) {
        s.data[i] = values[i];
    }
    s.length = length;

    return s;
}

int main(void)
{
    const int values1[] = {5, 2, 9, 1, 7};
    const int values2[] = {3, 8};
    const int values3[] = {6, 4, 10};
    const int values4[] = {11};

    Sublist sublists[4];
    const size_t count = 4;
    size_t min_index = 0;
    size_t i;
    int status = EXIT_SUCCESS;

    sublists[0] = create_sublist(values1, sizeof(values1) / sizeof(values1[0]));
    sublists[1] = create_sublist(values2, sizeof(values2) / sizeof(values2[0]));
    sublists[2] = create_sublist(values3, sizeof(values3) / sizeof(values3[0]));
    sublists[3] = create_sublist(values4, sizeof(values4) / sizeof(values4[0]));

    for (i = 0; i < count; i++) {
        if (sublists[i].data == NULL) {
            fprintf(stderr, "Error: memory allocation failed\n");
            status = EXIT_FAILURE;
            break;
        }
    }

    if (status == EXIT_SUCCESS) {
        if (find_min_length_sublist(sublists, count, &min_index) != 0) {
            fprintf(stderr, "Error: unable to find minimum length sublist\n");
            status = EXIT_FAILURE;
        } else {
            printf("Minimum length sublist: index %zu, length %zu\n",
                   min_index, sublists[min_index].length);
            printf("Elements: ");
            for (i = 0; i < sublists[min_index].length; i++) {
                printf("%d ", sublists[min_index].data[i]);
            }
            printf("\n");
        }
    }

    for (i = 0; i < count; i++) {
        free(sublists[i].data);
        sublists[i].data = NULL;
    }

    return status;
}