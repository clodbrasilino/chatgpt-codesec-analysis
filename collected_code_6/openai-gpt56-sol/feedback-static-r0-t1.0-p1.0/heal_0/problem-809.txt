#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static bool elements_are_smaller(const int first[], const int second[], size_t length)
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
    const size_t length = sizeof(first) / sizeof(first[0]);

    if (length != sizeof(second) / sizeof(second[0])) {
        (void)fprintf(stderr, "Tuple lengths do not match.\n");
        return 1;
    }

    if (elements_are_smaller(first, second, length)) {
        (void)printf("Every element in the second tuple is smaller.\n");
    } else {
        (void)printf("Not every element in the second tuple is smaller.\n");
    }

    return 0;
}