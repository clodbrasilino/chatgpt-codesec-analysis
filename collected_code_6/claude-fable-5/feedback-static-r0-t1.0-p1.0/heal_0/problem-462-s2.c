#include <stdio.h>
#include <stdlib.h>

static void print_combination(const int *arr, const int *indices, size_t k)
{
    size_t i;

    printf("{ ");
    for (i = 0; i < k; i++) {
        printf("%d ", arr[indices[i]]);
    }
    printf("}\n");
}

static int combine_recursive(const int *arr, size_t n, int *indices,
                             size_t k, size_t start, size_t depth)
{
    size_t i;

    if (depth == k) {
        print_combination(arr, indices, k);
        return 0;
    }

    for (i = start; i < n; i++) {
        indices[depth] = (int)i;
        if (combine_recursive(arr, n, indices, k, i + 1, depth + 1) != 0) {
            return -1;
        }
    }

    return 0;
}

int find_all_combinations(const int *arr, size_t n)
{
    int *indices;
    size_t k;

    if (arr == NULL || n == 0) {
        return -1;
    }

    indices = malloc(n * sizeof(*indices));
    if (indices == NULL) {
        return -1;
    }

    for (k = 1; k <= n; k++) {
        if (combine_recursive(arr, n, indices, k, 0, 0) != 0) {
            free(indices);
            return -1;
        }
    }

    free(indices);
    return 0;
}

int main(void)
{
    int list[] = { 1, 2, 3, 4 };
    size_t n = sizeof(list) / sizeof(list[0]);

    if (find_all_combinations(list, n) != 0) {
        fprintf(stderr, "Failed to generate combinations\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}