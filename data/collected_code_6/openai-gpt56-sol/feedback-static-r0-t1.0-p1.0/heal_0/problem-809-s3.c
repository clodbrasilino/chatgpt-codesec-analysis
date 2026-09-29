#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static bool is_each_element_smaller(const int first[], const int second[], size_t length)
{
    if ((first == NULL || second == NULL) && length != 0U) {
        return false;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (second[i] >= first[i]) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    const int first[] = {5, 10, 15, 20};
    const int second[] = {4, 9, 14, 19};
    const size_t first_length = sizeof(first) / sizeof(first[0]);
    const size_t second_length = sizeof(second) / sizeof(second[0]);

    if (first_length != second_length) {
        if (fputs("Tuple lengths do not match.\n", stderr) == EOF) {
            return 1;
        }
        return 1;
    }

    const bool result = is_each_element_smaller(first, second, first_length);

    if (printf("%s\n", result ? "true" : "false") < 0) {
        return 1;
    }

    return 0;
}