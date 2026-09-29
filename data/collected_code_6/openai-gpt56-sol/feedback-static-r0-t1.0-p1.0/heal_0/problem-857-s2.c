#include <stdio.h>
#include <stdlib.h>

typedef int (*map_function)(const char *);

static int print_string(const char *string)
{
    if (string == NULL) {
        return -1;
    }

    return printf("%s\n", string) < 0 ? -1 : 0;
}

static int map_strings(const char *const strings[], size_t count,
                       map_function function)
{
    size_t i;

    if ((strings == NULL && count != 0U) || function == NULL) {
        return -1;
    }

    for (i = 0U; i < count; ++i) {
        if (function(strings[i]) != 0) {
            return -1;
        }
    }

    return 0;
}

int main(void)
{
    const char *const strings[] = {
        "Apple",
        "Banana",
        "Cherry",
        "Date"
    };
    const size_t count = sizeof strings / sizeof strings[0];

    if (map_strings(strings, count, print_string) != 0) {
        fputs("Failed to list strings.\n", stderr);
        return EXIT_FAILURE;
    }

    if (fflush(stdout) == EOF) {
        fputs("Failed to flush output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}