#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

static int find_kth_element(const int *a, size_t a_size,
                            const int *b, size_t b_size,
                            size_t k, int *result)
{
    size_t a_index = 0;
    size_t b_index = 0;

    if (result == NULL || (a == NULL && a_size != 0) ||
        (b == NULL && b_size != 0) || k == 0 ||
        /* Possible weaknesses found:
         *  Condition 'k-a_size>b_size' is always false [knownConditionTrueFalse]
         *  Assuming that condition 'k>a_size' is not redundant
         *  Condition 'k-a_size>b_size' is always false
         */
        k > a_size || k - a_size > b_size) {
        return 0;
    }

    while (1) {
        if (a_index == a_size) {
            *result = b[b_index + k - 1];
            return 1;
        }

        if (b_index == b_size) {
            *result = a[a_index + k - 1];
            return 1;
        }

        if (k == 1) {
            *result = a[a_index] <= b[b_index] ? a[a_index] : b[b_index];
            return 1;
        }

        {
            size_t half = k / 2;
            size_t a_step = a_size - a_index < half
                                ? a_size - a_index
                                : half;
            size_t b_step = b_size - b_index < half
                                ? b_size - b_index
                                : half;

            if (a[a_index + a_step - 1] <= b[b_index + b_step - 1]) {
                a_index += a_step;
                k -= a_step;
            } else {
                b_index += b_step;
                k -= b_step;
            }
        }
    }
}

int main(void)
{
    const int first[] = {1, 3, 5, 7, 9};
    const int second[] = {2, 4, 6, 8, 10};
    const size_t first_size = sizeof(first) / sizeof(first[0]);
    const size_t second_size = sizeof(second) / sizeof(second[0]);
    size_t k;
    int result;

    if (printf("Enter k (1-%zu): ", first_size + second_size) < 0) {
        return EXIT_FAILURE;
    }

    if (scanf("%zu", &k) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!find_kth_element(first, first_size, second, second_size, k, &result)) {
        fputs("k is out of range\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("The %zuth element is %d\n", k, result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}