#include <stdio.h>
#include <stdlib.h>

typedef struct Sublist {
    int *items;
    size_t count;
} Sublist;

typedef struct PackResult {
    Sublist *sublists;
    size_t count;
} PackResult;

static void free_pack_result(PackResult *result)
{
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    size_t i;

    if (result == NULL) {
        return;
    }
    if (result->sublists != NULL) {
        for (i = 0; i < result->count; i++) {
            free(result->sublists[i].items);
        }
        free(result->sublists);
        result->sublists = NULL;
    }
    result->count = 0;
}

static int pack_duplicates(const int *input, size_t length, PackResult *result)
{
    size_t i;
    size_t start;
    size_t run_length;
    size_t group_count;
    size_t j;
    Sublist *groups;

    if (result == NULL) {
        return -1;
    }
    result->sublists = NULL;
    result->count = 0;

    if (input == NULL || length == 0) {
        return 0;
    }

    group_count = 1;
    for (i = 1; i < length; i++) {
        if (input[i] != input[i - 1]) {
            group_count++;
        }
    }

    groups = calloc(group_count, sizeof(Sublist));
    if (groups == NULL) {
        return -1;
    }

    result->sublists = groups;
    result->count = group_count;

    start = 0;
    j = 0;
    for (i = 1; i <= length; i++) {
        if (i == length || input[i] != input[start]) {
            run_length = i - start;
            groups[j].items = malloc(run_length * sizeof(int));
            if (groups[j].items == NULL) {
                free_pack_result(result);
                return -1;
            }
            groups[j].count = run_length;
            {
                size_t k;
                for (k = 0; k < run_length; k++) {
                    groups[j].items[k] = input[start + k];
                }
            }
            j++;
            start = i;
        }
    }

    return 0;
}

static void print_pack_result(const PackResult *result)
{
    size_t i;
    size_t k;

    if (result == NULL) {
        return;
    }
    printf("[");
    for (i = 0; i < result->count; i++) {
        printf("[");
        for (k = 0; k < result->sublists[i].count; k++) {
            printf("%d", result->sublists[i].items[k]);
            if (k + 1 < result->sublists[i].count) {
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
    PackResult result;

    if (pack_duplicates(data, length, &result) != 0) {
        fprintf(stderr, "Failed to pack duplicates\n");
        return EXIT_FAILURE;
    }

    print_pack_result(&result);
    free_pack_result(&result);

    return EXIT_SUCCESS;
}