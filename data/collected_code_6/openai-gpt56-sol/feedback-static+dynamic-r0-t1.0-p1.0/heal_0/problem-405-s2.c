#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static bool tuple_contains(const int *tuple, size_t length, int element)
{
    if (tuple == NULL) {
        return false;
    }

    for (size_t i = 0; i < length; ++i) {
        if (tuple[i] == element) {
            return true;
        }
    }

    return false;
}

int main(void)
{
    const int tuple[] = {10, 20, 30, 40, 50};
    const size_t length = sizeof(tuple) / sizeof(tuple[0]);
    int element = 0;

    if (printf("Enter an integer: ") < 0) {
        return 1;
    }

    if (scanf("%d", &element) != 1) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (tuple_contains(tuple, length, element)) {
        if (puts("Element exists in the tuple.") == EOF) {
            return 1;
        }
    } else {
        if (puts("Element does not exist in the tuple.") == EOF) {
            return 1;
        }
    }

    return 0;
}