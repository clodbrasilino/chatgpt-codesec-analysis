#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>

static int print_lucky(size_t n, size_t limit)
{
    size_t cap;
    size_t count;
    size_t i;
    size_t r;
    size_t k;
    unsigned long long v;
    unsigned long long *a;

    cap = (limit / 2U) + 1U;
    if (cap > SIZE_MAX / sizeof(*a)) {
        return -1;
    }
    a = malloc(cap * sizeof(*a));
    if (a == NULL) {
        return -1;
    }

    count = 0U;
    for (v = 1ULL; v <= (unsigned long long)limit; v += 2ULL) {
        a[count] = v;
        count++;
    }

    i = 1U;
    while (i < count && a[i] <= (unsigned long long)count) {
        const unsigned long long step = a[i];
        size_t w = 0U;
        for (r = 0U; r < count; r++) {
            if (((unsigned long long)(r + 1U)) % step != 0ULL) {
                a[w] = a[r];
                w++;
            }
        }
        count = w;
        i++;
    }

    if (count < n) {
        free(a);
        return 0;
    }

    for (k = 0U; k < n; k++) {
        if (printf("%llu%c", a[k], (k + 1U == n) ? '\n' : ' ') < 0) {
            free(a);
            return -1;
        }
    }

    free(a);
    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    char *end;
    unsigned long parsed;
    size_t n;
    size_t limit;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <count>\n", (argc > 0) ? argv[0] : "lucky");
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    parsed = strtoul(argv[1], &end, 10);
    if (end == argv[1] || *end != '\0' || errno == ERANGE) {
        fprintf(stderr, "Invalid count value\n");
        return EXIT_FAILURE;
    }
    if (parsed == 0UL || parsed > 1000000UL) {
        fprintf(stderr, "Count must be between 1 and 1000000\n");
        return EXIT_FAILURE;
    }

    n = (size_t)parsed;
    limit = 1024U;

    for (;;) {
        const int rc = print_lucky(n, limit);
        if (rc == 1) {
            break;
        }
        if (rc == -1) {
            fprintf(stderr, "Resource error\n");
            return EXIT_FAILURE;
        }
        if (limit > SIZE_MAX / 2U) {
            fprintf(stderr, "Limit overflow\n");
            return EXIT_FAILURE;
        }
        limit *= 2U;
    }

    return EXIT_SUCCESS;
}