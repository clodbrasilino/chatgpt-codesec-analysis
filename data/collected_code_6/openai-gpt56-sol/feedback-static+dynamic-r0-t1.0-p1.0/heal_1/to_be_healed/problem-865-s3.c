#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef void (*MapFunction)(int);

static int map(const int *list, size_t length, MapFunction function)
{
    if ((list == NULL && length != 0U) || function == NULL) {
        return -1;
    }

    for (size_t i = 0U; i < length; ++i) {
        function(list[i]);
    }

    return 0;
}

static void print_value(int value)
{
    printf("%d ", value);
}

static int print_list_n_times(const int *list, size_t length, size_t count)
{
    if (list == NULL && length != 0U) {
        return -1;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (map(list, length, print_value) != 0 || putchar('\n') == EOF) {
            return -1;
        }
    }

    return ferror(stdout) ? -1 : 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    static const int list[] = {1, 2, 3, 4, 5};
    char *end = NULL;
    unsigned long parsed_count;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <count>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed_count = strtoul(argv[1], &end, 10);

    if (errno != 0 || end == argv[1] || *end != '\0' ||
        parsed_count > (unsigned long)SIZE_MAX) {
        fputs("Invalid count\n", stderr);
        return EXIT_FAILURE;
    }

    if (print_list_n_times(
            list,
            sizeof(list) / sizeof(list[0]),
            (size_t)parsed_count) != 0) {
        fputs("Output error\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}