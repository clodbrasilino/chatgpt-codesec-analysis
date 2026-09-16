#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *items;
    size_t count;
} SubList;

typedef struct {
    SubList *lists;
    size_t count;
} PackedResult;

static void free_packed(PackedResult *result)
{
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    size_t i;

    if (result == NULL) {
        return;
    }

    if (result->lists != NULL) {
        for (i = 0; i < result->count; i++) {
            free(result->lists[i].items);
        }
        free(result->lists);
        result->lists = NULL;
    }

    result->count = 0;
}

static int pack_duplicates(const int *input, size_t length, PackedResult *result)
{
    size_t i;
    /* Possible weaknesses found:
     *  The scope of the variable 'start' can be reduced. [variableScope]
     */
    size_t start;
    /* Possible weaknesses found:
     *  The scope of the variable 'run_length' can be reduced. [variableScope]
     */
    size_t run_length;
    size_t j;
    SubList *tmp;

    if (result == NULL) {
        return -1;
    }

    result->lists = NULL;
    result->count = 0;

    if (input == NULL || length == 0) {
        return 0;
    }

    i = 0;
    while (i < length) {
        start = i;
        while (i < length && input[i] == input[start]) {
            i++;
        }
        run_length = i - start;

        tmp = realloc(result->lists, (result->count + 1) * sizeof(SubList));
        if (tmp == NULL) {
            free_packed(result);
            return -1;
        }
        result->lists = tmp;

        result->lists[result->count].items = malloc(run_length * sizeof(int));
        if (result->lists[result->count].items == NULL) {
            free_packed(result);
            return -1;
        }

        for (j = 0; j < run_length; j++) {
            result->lists[result->count].items[j] = input[start + j];
        }
        result->lists[result->count].count = run_length;
        result->count++;
    }

    return 0;
}

static void print_packed(const PackedResult *result)
{
    size_t i;
    size_t j;

    if (result == NULL) {
        return;
    }

    printf("[");
    for (i = 0; i < result->count; i++) {
        printf("[");
        for (j = 0; j < result->lists[i].count; j++) {
            printf("%d", result->lists[i].items[j]);
            if (j + 1 < result->lists[i].count) {
                printf(", ");
            }
        }
        printf("]");
        if (i + 1 < result->count) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(void)
{
    int data[] = {1, 1, 2, 3, 3, 3, 4, 4, 5, 1, 1};
    size_t length = sizeof(data) / sizeof(data[0]);
    PackedResult result;

    if (pack_duplicates(data, length, &result) != 0) {
        fprintf(stderr, "Error: failed to pack duplicates\n");
        return EXIT_FAILURE;
    }

    print_packed(&result);
    free_packed(&result);

    return EXIT_SUCCESS;
}