#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef void (*map_fn)(int, void *);

static int map(const int *list, size_t length, map_fn function, void *context)
{
    if ((list == NULL && length != 0U) || function == NULL) {
        return -1;
    }

    for (size_t i = 0U; i < length; ++i) {
        function(list[i], context);
    }

    return ferror(stdout) ? -1 : 0;
}

static void print_value(int value, void *context)
{
    const size_t *iteration = context;

    if (iteration != NULL) {
        printf("%d\n", value);
    }
}

static int print_list_n_times(const int *list, size_t length, size_t n)
{
    for (size_t iteration = 0U; iteration < n; ++iteration) {
        if (map(list, length, print_value, &iteration) != 0) {
            return -1;
        }
    }

    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    const int list[] = {1, 2, 3, 4, 5};
    char *end = NULL;
    unsigned long repetitions;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <nonnegative repetition count>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    repetitions = strtoul(argv[1], &end, 10);

    if (errno != 0 || end == argv[1] || *end != '\0' ||
        repetitions > (unsigned long)SIZE_MAX) {
        fprintf(stderr, "Invalid repetition count\n");
        return EXIT_FAILURE;
    }

    if (print_list_n_times(
            list,
            sizeof list / sizeof list[0],
            (size_t)repetitions) != 0) {
        fprintf(stderr, "Failed to print the list\n");
        return EXIT_FAILURE;
    }

    if (fflush(stdout) == EOF) {
        fprintf(stderr, "Failed to flush output\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}