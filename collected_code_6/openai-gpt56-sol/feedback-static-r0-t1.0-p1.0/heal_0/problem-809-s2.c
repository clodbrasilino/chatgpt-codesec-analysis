#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

bool tuple_elements_are_smaller(const int first[], const int second[], size_t length)
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
    const int second[] = {1, 9, 12, 18};
    const size_t length = sizeof(first) / sizeof(first[0]);

    if (length != sizeof(second) / sizeof(second[0])) {
        if (fprintf(stderr, "Tuple lengths do not match.\n") < 0) {
            return 1;
        }
        return 1;
    }

    const char *result = tuple_elements_are_smaller(first, second, length)
                             ? "true\n"
                             : "false\n";

    if (fputs(result, stdout) == EOF) {
        return 1;
    }

    return 0;
}