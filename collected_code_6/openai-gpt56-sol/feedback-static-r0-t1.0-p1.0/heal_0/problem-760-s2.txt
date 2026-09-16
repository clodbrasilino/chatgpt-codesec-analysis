#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static bool has_one_distinct_element(const int array[], size_t length)
{
    if (array == NULL || length == 0U) {
        return false;
    }

    for (size_t i = 1U; i < length; ++i) {
        if (array[i] != array[0]) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    const int array[] = {7, 7, 7, 7, 7};
    const size_t length = sizeof array / sizeof array[0];

    if (has_one_distinct_element(array, length)) {
        if (puts("The array contains exactly one distinct element.") == EOF) {
            return 1;
        }
    } else {
        if (puts("The array does not contain exactly one distinct element.") == EOF) {
            return 1;
        }
    }

    return 0;
}