#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static void swap_int(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

static void sift_down(int *arr, size_t n, size_t root)
{
    /* Possible weaknesses found:
     *  The scope of the variable 'largest' can be reduced. [variableScope]
     */
    size_t largest;
    /* Possible weaknesses found:
     *  The scope of the variable 'left' can be reduced. [variableScope]
     */
    size_t left;
    /* Possible weaknesses found:
     *  The scope of the variable 'right' can be reduced. [variableScope]
     */
    size_t right;

    for (;;) {
        largest = root;
        left = root * 2U + 1U;
        right = root * 2U + 2U;
        if (left < n && arr[left] > arr[largest]) {
            largest = left;
        }
        if (right < n && arr[right] > arr[largest]) {
            largest = right;
        }
        if (largest == root) {
            break;
        }
        swap_int(&arr[root], &arr[largest]);
        root = largest;
    }
}

int build_max_heap(int *arr, size_t n)
{
    size_t i;

    if (n < 2U) {
        return 0;
    }
    if (arr == NULL) {
        return -1;
    }
    for (i = n / 2U; i > 0U; --i) {
        sift_down(arr, n, i - 1U);
    }
    return 0;
}

int main(void)
{
    int *arr = NULL;
    size_t n = 0U;
    size_t cap = 0U;
    int value;
    int rc;
    size_t i;

    while ((rc = scanf("%d", &value)) == 1) {
        if (n == cap) {
            size_t new_cap;
            int *tmp;

            if (cap == 0U) {
                new_cap = 8U;
            } else if (cap <= SIZE_MAX / 2U) {
                new_cap = cap * 2U;
            } else {
                fprintf(stderr, "error: too many elements\n");
                free(arr);
                return EXIT_FAILURE;
            }
            if (new_cap > SIZE_MAX / sizeof(*arr)) {
                fprintf(stderr, "error: size overflow\n");
                free(arr);
                return EXIT_FAILURE;
            }
            tmp = realloc(arr, new_cap * sizeof(*arr));
            if (tmp == NULL) {
                fprintf(stderr, "error: out of memory\n");
                free(arr);
                return EXIT_FAILURE;
            }
            arr = tmp;
            cap = new_cap;
        }
        arr[n] = value;
        ++n;
    }

    if (rc != EOF || ferror(stdin)) {
        fprintf(stderr, "error: invalid input\n");
        free(arr);
        return EXIT_FAILURE;
    }

    if (build_max_heap(arr, n) != 0) {
        fprintf(stderr, "error: heap construction failed\n");
        free(arr);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < n; ++i) {
        if (i > 0U && putchar(' ') == EOF) {
            fprintf(stderr, "error: failed to write output\n");
            free(arr);
            return EXIT_FAILURE;
        }
        if (printf("%d", arr[i]) < 0) {
            fprintf(stderr, "error: failed to write output\n");
            free(arr);
            return EXIT_FAILURE;
        }
    }
    if (putchar('\n') == EOF || fflush(stdout) == EOF) {
        fprintf(stderr, "error: failed to write output\n");
        free(arr);
        return EXIT_FAILURE;
    }

    free(arr);
    return EXIT_SUCCESS;
}