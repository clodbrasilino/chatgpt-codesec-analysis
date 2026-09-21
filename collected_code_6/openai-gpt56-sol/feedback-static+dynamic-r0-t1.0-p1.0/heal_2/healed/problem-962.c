#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int parse_uint64(const char **text, uint64_t *value)
{
    char *end;
    uintmax_t parsed;

    if (text == NULL || *text == NULL || value == NULL) {
        return 0;
    }

    while (isspace((unsigned char)**text)) {
        ++*text;
    }

    if (**text == '\0' || **text == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(*text, &end, 10);

    if (end == *text || errno == ERANGE || parsed > UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    *text = end;
    return 1;
}

static int sum_even_naturals(uint64_t l, uint64_t r, uint64_t *result)
{
    uint64_t first;
    uint64_t last;
    uint64_t count;
    uint64_t a;
    uint64_t b;

    if (result == NULL || l == 0 || l > r) {
        return 0;
    }

    if ((l & UINT64_C(1)) != 0) {
        if (l == UINT64_MAX) {
            *result = 0;
            return 1;
        }
        first = l + UINT64_C(1);
    } else {
        first = l;
    }

    last = r - (r & UINT64_C(1));

    if (first > last) {
        *result = 0;
        return 1;
    }

    count = ((last - first) / UINT64_C(2)) + UINT64_C(1);

    if ((count & UINT64_C(1)) == 0) {
        a = count / UINT64_C(2);
        b = first + (last - first) / UINT64_C(2);
    } else {
        a = count;
        b = first / UINT64_C(2) + last / UINT64_C(2);
    }

    if (a != 0 && b > UINT64_MAX / a) {
        return 0;
    }

    *result = a * b;
    return 1;
}

int main(void)
{
    char input[256];
    const char *cursor;
    uint64_t l;
    uint64_t r;
    uint64_t sum;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        int ch;

        while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        }

        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = input;

    if (!parse_uint64(&cursor, &l) || !parse_uint64(&cursor, &r)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!sum_even_naturals(l, r, &sum)) {
        fputs("Invalid range or arithmetic overflow\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}