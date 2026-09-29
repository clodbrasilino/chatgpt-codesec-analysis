#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool tuple_contains_only_k_elements(size_t tuple_length, size_t k)
{
    return tuple_length == k;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[])
{
    char *end = NULL;
    unsigned long long parsed_k;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <k> [tuple elements...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed_k = strtoull(argv[1], &end, 10);

    if (errno != 0 || end == argv[1] || *end != '\0' ||
        parsed_k > (unsigned long long)SIZE_MAX) {
        fprintf(stderr, "Invalid value for k: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    if (tuple_contains_only_k_elements((size_t)(argc - 2),
                                       (size_t)parsed_k)) {
        puts("true");
    } else {
        puts("false");
    }

    return EXIT_SUCCESS;
}