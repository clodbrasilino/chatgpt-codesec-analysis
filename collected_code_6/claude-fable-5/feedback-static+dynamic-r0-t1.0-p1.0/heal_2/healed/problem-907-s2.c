#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

static long *compute_lucky(size_t n, size_t *found)
{
    size_t limit = 128;
    long *a = NULL;

    if (n == 0 || found == NULL) {
        return NULL;
    }

    for (;;) {
        size_t count = 0;
        size_t i;
        size_t idx;

        if (limit > (SIZE_MAX / sizeof(long)) / 2) {
            free(a);
            return NULL;
        }

        free(a);
        a = malloc((limit / 2 + 1) * sizeof(long));
        if (a == NULL) {
            return NULL;
        }

        for (i = 1; i <= limit; i += 2) {
            a[count++] = (long)i;
        }

        idx = 1;
        while (idx < count && a[idx] <= (long)count) {
            size_t step = (size_t)a[idx];
            size_t kept = 0;
            size_t j;

            for (j = 0; j < count; j++) {
                if ((j + 1) % step != 0) {
                    a[kept++] = a[j];
                }
            }
            count = kept;
            idx++;
        }

        if (count >= n) {
            *found = n;
            return a;
        }

        limit *= 2;
    }
}

static int print_lucky_numbers(size_t n)
{
    size_t found = 0;
    size_t i;
    long *lucky;

    if (n == 0) {
        return -1;
    }

    lucky = compute_lucky(n, &found);
    if (lucky == NULL || found < n) {
        free(lucky);
        return -1;
    }

    for (i = 0; i < n; i++) {
        if (printf("%ld\n", lucky[i]) < 0) {
            free(lucky);
            return -1;
        }
    }

    free(lucky);
    return 0;
}

int main(int argc, const char *const argv[])
{
    unsigned long value;
    char *endptr = NULL;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoul(argv[1], &endptr, 10);
    if (errno != 0 || endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "Invalid number: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    if (value == 0 || value > 1000000UL) {
        fprintf(stderr, "n must be between 1 and 1000000\n");
        return EXIT_FAILURE;
    }

    if (print_lucky_numbers((size_t)value) != 0) {
        fprintf(stderr, "Failed to compute lucky numbers\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}