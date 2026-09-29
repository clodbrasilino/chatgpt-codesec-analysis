#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static bool have_common_element(const int *list1, size_t length1,
                                const int *list2, size_t length2)
{
    if ((list1 == NULL && length1 != 0U) ||
        (list2 == NULL && length2 != 0U)) {
        return false;
    }

    for (size_t i = 0U; i < length1; ++i) {
        for (size_t j = 0U; j < length2; ++j) {
            if (list1[i] == list2[j]) {
                return true;
            }
        }
    }

    return false;
}

int main(void)
{
    const int list1[] = {1, 2, 3, 4};
    const int list2[] = {5, 6, 3, 8};
    const size_t length1 = sizeof list1 / sizeof list1[0];
    const size_t length2 = sizeof list2 / sizeof list2[0];

    const bool result = have_common_element(list1, length1, list2, length2);

    if (printf("%s\n", result ? "true" : "false") < 0) {
        return 1;
    }

    return 0;
}