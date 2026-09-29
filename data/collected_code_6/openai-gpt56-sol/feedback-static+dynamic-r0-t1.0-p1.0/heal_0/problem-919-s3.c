#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <limits.h>

bool multiply_items(const int *items, size_t count, int *result)
{
    int product = 1;

    if (result == NULL || (items == NULL && count != 0U)) {
        return false;
    }

    for (size_t i = 0U; i < count; ++i) {
        if ((items[i] > 0 && (product > INT_MAX / items[i] ||
                             product < INT_MIN / items[i])) ||
            (items[i] < 0 && ((items[i] == -1 && product == INT_MIN) ||
                             (items[i] != -1 &&
                              (product > INT_MIN / items[i] ||
                               product < INT_MAX / items[i]))))) {
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
    int result = 0;

    if (!multiply_items(items, sizeof(items) / sizeof(items[0]), &result)) {
        fputs("Unable to multiply the list safely.\n", stderr);
        return 1;
    }

    if (printf("%d\n", result) < 0) {
        return 1;
    }

    return 0;
}