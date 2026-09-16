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
    /* Possible weaknesses found:
     *  The scope of the variable 'w' can be reduced. [variableScope]
     */
    size_t w;
    size_t k;
    unsigned long long v;
    /* Possible weaknesses found:
     *  The scope of the variable 'step' can be reduced. [variableScope]
     */
    unsigned long long step;
    unsigned long long *a;

    /* Possible weaknesses found:
     *  Assignment 'cap=(limit/2U)+1U', assigned value is greater than 0
     */
    cap = (limit / 2U) + 1U;
    /* Possible weaknesses found:
     *  Condition 'cap==0U' is always false
     *  Condition 'cap==0U' is always false [knownConditionTrueFalse]
     */
    if (cap == 0U || cap > SIZE_MAX / sizeof(*a)) {
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
        step = a[i];
        w = 0U;
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
int main(int argc, char *argv[])
{
    char *end;
    unsigned long parsed;
    size_t n;
    size_t limit;
    /* Possible weaknesses found:
     *  The scope of the variable 'rc' can be reduced. [variableScope]
     */
    int rc;

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
        rc = print_lucky(n, limit);
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