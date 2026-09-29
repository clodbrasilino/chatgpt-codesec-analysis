#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int add_k_to_elements(int *elements, size_t count, int k)
{
    if (elements == NULL && count != 0U) {
        return -1;
    }

    for (size_t i = 0; i < count; ++i) {
        if ((k > 0 && elements[i] > INT_MAX - k) ||
            (k < 0 && elements[i] < INT_MIN - k)) {
            return -1;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        elements[i] += k;
    }

    return 0;
}

static int parse_int(const char *text, int *value)
{
    char *end = NULL;
    long parsed;

    if (text == NULL || value == NULL) {
        return -1;
    }

    errno = 0;
    parsed = strtol(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed < INT_MIN || parsed > INT_MAX) {
        return -1;
    }

    *value = (int)parsed;
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[])
{
    int *elements;
    int k;
    size_t count;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s k element [element ...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (parse_int(argv[1], &k) != 0) {
        fprintf(stderr, "Invalid value for k\n");
        return EXIT_FAILURE;
    }

    count = (size_t)argc - 2U;

    if (count > SIZE_MAX / sizeof(*elements)) {
        fprintf(stderr, "Too many elements\n");
        return EXIT_FAILURE;
    }

    elements = malloc(count * sizeof(*elements));
    if (elements == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (parse_int(argv[i + 2U], &elements[i]) != 0) {
            fprintf(stderr, "Invalid element: %s\n", argv[i + 2U]);
            free(elements);
            return EXIT_FAILURE;
        }
    }

    if (add_k_to_elements(elements, count, k) != 0) {
        fprintf(stderr, "Integer overflow\n");
        free(elements);
        return EXIT_FAILURE;
    }

    putchar('(');

    for (size_t i = 0; i < count; ++i) {
        printf("%s%d", i == 0U ? "" : ", ", elements[i]);
    }

    puts(")");

    free(elements);
    return EXIT_SUCCESS;
}