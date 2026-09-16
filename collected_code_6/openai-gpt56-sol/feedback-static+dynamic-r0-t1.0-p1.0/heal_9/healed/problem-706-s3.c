#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static bool is_subset(const int subset[], size_t subset_size,
                      const int array[], size_t array_size)
{
    if (subset_size == 0U) {
        return true;
    }

    if (subset == NULL || array == NULL || array_size == 0U) {
        return false;
    }

    for (size_t i = 0U; i < subset_size; ++i) {
        bool found = false;

        for (size_t j = 0U; j < array_size; ++j) {
            if (subset[i] == array[j]) {
                found = true;
                break;
            }
        }

        if (!found) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    const int array[] = {1, 2, 3, 4, 5};
    const int subset[] = {2, 4, 5};

    const size_t array_size = sizeof array / sizeof array[0];
    const size_t subset_size = sizeof subset / sizeof subset[0];

    if (printf("%s\n",
               is_subset(subset, subset_size, array, array_size)
                   ? "Subset"
                   : "Not a subset") < 0) {
        return 1;
    }

    return 0;
}