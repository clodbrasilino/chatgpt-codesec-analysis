#include <stdio.h>
#include <stdlib.h>

static int tuple_has_none(const void *const *tuple, size_t size, int *has_none)
{
    size_t i;

    if (tuple == NULL || has_none == NULL) {
        return -1;
    }

    *has_none = 0;

    for (i = 0; i < size; ++i) {
        if (tuple[i] == NULL) {
            *has_none = 1;
            break;
        }
    }

    return 0;
}

int main(void)
{
    long first = 1;
    const char *third = "value";
    const void *tuple[] = {&first, NULL, third};
    int has_none;

    if (tuple_has_none(tuple, sizeof(tuple) / sizeof(tuple[0]), &has_none) != 0) {
        fputs("failed to inspect tuple\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", has_none ? "true" : "false") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}