#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

static int trim_tuple(const Tuple *source, size_t k, Tuple *result)
{
    size_t new_size;
    size_t i;

    if (source == NULL || result == NULL) {
        return -1;
    }

    if (source->size < 2U * k) {
        return -1;
    }

    new_size = source->size - 2U * k;
    result->size = new_size;

    if (new_size == 0U) {
        result->elements = NULL;
        return 0;
    }

    result->elements = (int *)malloc(new_size * sizeof(int));
    if (result->elements == NULL) {
        result->size = 0U;
        return -1;
    }

    for (i = 0U; i < new_size; i++) {
        result->elements[i] = source->elements[k + i];
    }

    return 0;
}

static int trim_tuple_list(const Tuple *list, size_t count, size_t k, Tuple **out)
{
    Tuple *trimmed;
    size_t i;
    size_t j;

    if (list == NULL || out == NULL || count == 0U) {
        return -1;
    }

    trimmed = (Tuple *)malloc(count * sizeof(Tuple));
    if (trimmed == NULL) {
        return -1;
    }

    for (i = 0U; i < count; i++) {
        if (trim_tuple(&list[i], k, &trimmed[i]) != 0) {
            for (j = 0U; j < i; j++) {
                free(trimmed[j].elements);
            }
            free(trimmed);
            return -1;
        }
    }

    *out = trimmed;
    return 0;
}

static void free_tuple_list(Tuple *list, size_t count)
{
    size_t i;

    if (list == NULL) {
        return;
    }

    for (i = 0U; i < count; i++) {
        free(list[i].elements);
    }
    free(list);
}

static void print_tuple_list(const Tuple *list, size_t count)
{
    size_t i;
    size_t j;

    printf("[");
    for (i = 0U; i < count; i++) {
        printf("(");
        for (j = 0U; j < list[i].size; j++) {
            printf("%d", list[i].elements[j]);
            if (j + 1U < list[i].size) {
                printf(", ");
            }
        }
        printf(")");
        if (i + 1U < count) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(void)
{
    int data1[] = {5, 3, 2, 1, 4};
    int data2[] = {3, 4, 9, 2, 1};
    int data3[] = {9, 1, 2, 3, 5};
    int data4[] = {4, 8, 2, 1, 7};
    Tuple input[4];
    Tuple *output = NULL;
    size_t count = 4U;
    size_t k = 1U;

    input[0].elements = data1;
    input[0].size = 5U;
    input[1].elements = data2;
    input[1].size = 5U;
    input[2].elements = data3;
    input[2].size = 5U;
    input[3].elements = data4;
    input[3].size = 5U;

    printf("Original list: ");
    print_tuple_list(input, count);

    if (trim_tuple_list(input, count, k, &output) != 0) {
        fprintf(stderr, "Error: failed to trim tuple list\n");
        return EXIT_FAILURE;
    }

    printf("Trimmed list:  ");
    print_tuple_list(output, count);

    free_tuple_list(output, count);

    return EXIT_SUCCESS;
}