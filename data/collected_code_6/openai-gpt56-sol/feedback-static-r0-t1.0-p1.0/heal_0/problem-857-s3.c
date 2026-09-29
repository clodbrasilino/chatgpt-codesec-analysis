#include <stdio.h>
#include <stdlib.h>

typedef int (*MapFunction)(const char *);

static int print_string(const char *string)
{
    if (string == NULL) {
        return -1;
    }

    if (puts(string) == EOF) {
        return -1;
    }

    return 0;
}

static int map_strings(const char *const strings[], size_t count, MapFunction function)
{
    size_t i;

    if ((strings == NULL && count != 0U) || function == NULL) {
        return -1;
    }

    for (i = 0U; i < count; ++i) {
        if (strings[i] == NULL || function(strings[i]) != 0) {
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
    const size_t count = sizeof(strings) / sizeof(strings[0]);

    if (map_strings(strings, count, print_string) != 0) {
        (void)fputs("Failed to list strings.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}