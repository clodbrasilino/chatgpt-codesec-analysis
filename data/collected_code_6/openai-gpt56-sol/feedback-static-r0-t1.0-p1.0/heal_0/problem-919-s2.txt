#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <limits.h>

static bool multiply_all(const int *items, size_t count, int *result)
{
    int product = 1;

    if (result == NULL || (items == NULL && count != 0U)) {
        return false;
    }

    for (size_t i = 0U; i < count; ++i) {
        if ((items[i] > 0 && product > INT_MAX / items[i]) ||
            (items[i] < 0 &&
             ((product > 0 && items[i] < INT_MIN / product) ||
              (product < 0 && product < INT_MAX / items[i])))) {
            return false;
        }

        product *= items[i];
    }

    *result = product;
    return true;
}

int main(void)
{
    const int items[] = {2, 3, 4, 5};
    const size_t count = sizeof(items) / sizeof(items[0]);
    int result;

    if (!multiply_all(items, count, &result)) {
        (void)fprintf(stderr, "Unable to multiply the list.\n");
        return 1;
    }

    if (printf("%d\n", result) < 0) {
        return 1;
    }

    return 0;
}