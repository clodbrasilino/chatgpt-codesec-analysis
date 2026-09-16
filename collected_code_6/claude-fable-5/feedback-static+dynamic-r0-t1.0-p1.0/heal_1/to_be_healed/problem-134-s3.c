#include <stdio.h>
#include <stddef.h>

static const char *last_element_parity(const int arr[], size_t n, size_t p)
{
    unsigned int parity;
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    size_t i;

    if (arr == NULL || n == 0U) {
        return "invalid";
    }

    if ((n == 1U) || (p < (n - 1U))) {
        parity = (unsigned int)arr[n - 1U] & 1U;
    } else {
        parity = 0U;
        for (i = 0U; i < n; i++) {
            parity ^= ((unsigned int)arr[i] & 1U);
        }
    }

    if (parity == 0U) {
        return "even";
    }

    return "odd";
}

int main(void)
{
    int arr[] = { 7, 3, 5, 1, 4 };
    size_t n = sizeof(arr) / sizeof(arr[0]);
    size_t p = 2U;
    const char *result;

    result = last_element_parity(arr, n, p);

    if (printf("The last element is %s after %zu operations.\n", result, p) < 0) {
        return 1;
    }

    return 0;
}