#include <stdio.h>
#include <stdlib.h>

static int compare_ints(const void *a, const void *b)
{
    const int lhs = *(const int *)a;
    const int rhs = *(const int *)b;

    return (lhs > rhs) - (lhs < rhs);
}

static int *find_common_elements(const int *const lists[],
                                 const size_t sizes[],
                                 size_t list_count,
                                 size_t *common_count)
{
    int *common = NULL;
    size_t current_count;

    if (common_count == NULL) {
        return NULL;
    }

    *common_count = 0;

    if (lists == NULL || sizes == NULL || list_count == 0 ||
        lists[0] == NULL || sizes[0] == 0) {
        return NULL;
    }

    if (sizes[0] > SIZE_MAX / sizeof(*common)) {
        return NULL;
    }

    common = malloc(sizes[0] * sizeof(*common));
    if (common == NULL) {
        return NULL;
    }

    current_count = sizes[0];

    for (size_t i = 0; i < current_count; ++i) {
        common[i] = lists[0][i];
    }

    qsort(common, current_count, sizeof(*common), compare_ints);

    size_t unique_count = 0;
    for (size_t i = 0; i < current_count; ++i) {
        if (unique_count == 0 || common[i] != common[unique_count - 1]) {
            common[unique_count++] = common[i];
        }
    }
    current_count = unique_count;

    for (size_t list_index = 1;
         list_index < list_count && current_count > 0;
         ++list_index) {
        if (lists[list_index] == NULL || sizes[list_index] == 0) {
            current_count = 0;
            break;
        }

        size_t write_index = 0;

        for (size_t i = 0; i < current_count; ++i) {
            int found = 0;

            for (size_t j = 0; j < sizes[list_index]; ++j) {
                if (common[i] == lists[list_index][j]) {
                    found = 1;
                    break;
                }
            }

            if (found != 0) {
                common[write_index++] = common[i];
            }
        }

        current_count = write_index;
    }

    if (current_count == 0) {
        free(common);
        return NULL;
    }

    *common_count = current_count;
    return common;
}

int main(void)
{
    const int list1[] = {1, 2, 3, 4, 5, 5};
    const int list2[] = {2, 3, 5, 7};
    const int list3[] = {0, 2, 3, 5, 8};
    const int list4[] = {2, 5, 9};

    const int *lists[] = {list1, list2, list3, list4};
    const size_t sizes[] = {
        sizeof(list1) / sizeof(list1[0]),
        sizeof(list2) / sizeof(list2[0]),
        sizeof(list3) / sizeof(list3[0]),
        sizeof(list4) / sizeof(list4[0])
    };

    size_t common_count = 0;
    int *common = find_common_elements(
        lists,
        sizes,
        sizeof(lists) / sizeof(lists[0]),
        &common_count
    );

    if (common == NULL) {
        if (common_count == 0) {
            puts("No common elements.");
            return EXIT_SUCCESS;
        }

        fputs("Failed to find common elements.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("Common elements:");
    for (size_t i = 0; i < common_count; ++i) {
        printf(" %d", common[i]);
    }
    putchar('\n');

    free(common);
    return EXIT_SUCCESS;
}