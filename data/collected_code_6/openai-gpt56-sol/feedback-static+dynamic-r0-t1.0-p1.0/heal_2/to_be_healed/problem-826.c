#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

typedef enum {
    TRIANGLE_INVALID,
    TRIANGLE_EQUILATERAL,
    TRIANGLE_ISOSCELES,
    TRIANGLE_SCALENE
} TriangleType;

static TriangleType get_triangle_type(unsigned long long a,
                                      unsigned long long b,
                                      unsigned long long c)
{
    if (a == 0 || b == 0 || c == 0 ||
        a > ULLONG_MAX - b || a + b <= c ||
        a > ULLONG_MAX - c || a + c <= b ||
        b > ULLONG_MAX - c || b + c <= a) {
        return TRIANGLE_INVALID;
    }

    if (a == b && b == c) {
        return TRIANGLE_EQUILATERAL;
    }

    if (a == b || a == c || b == c) {
        return TRIANGLE_ISOSCELES;
    }

    return TRIANGLE_SCALENE;
}

static int discard_line(void)
{
    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != '\n' && ch != EOF);

    return ch == '\n';
}

static int read_side(const char *prompt, unsigned long long *side)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char *end;
    unsigned long long value;
    size_t length;

    if (prompt == NULL || side == NULL) {
        return 0;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return 0;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    length = 0;
    while (length < sizeof buffer && buffer[length] != '\0') {
        ++length;
    }

    if (length == sizeof buffer) {
        return 0;
    }

    if (length > 0 && buffer[length - 1] != '\n' && !feof(stdin)) {
        discard_line();
        return 0;
    }

    end = buffer;
    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end == '-' || *end == '\0') {
        return 0;
    }

    errno = 0;
    value = strtoull(end, &end, 10);

    if (errno == ERANGE || value == 0) {
        return 0;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *side = value;
    return 1;
}

int main(void)
{
    unsigned long long a;
    unsigned long long b;
    unsigned long long c;
    TriangleType type;

    if (!read_side("Enter side 1: ", &a) ||
        !read_side("Enter side 2: ", &b) ||
        !read_side("Enter side 3: ", &c)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    type = get_triangle_type(a, b, c);

    switch (type) {
        case TRIANGLE_EQUILATERAL:
            puts("Equilateral triangle");
            break;
        case TRIANGLE_ISOSCELES:
            puts("Isosceles triangle");
            break;
        case TRIANGLE_SCALENE:
            puts("Scalene triangle");
            break;
        case TRIANGLE_INVALID:
        default:
            puts("Not a valid triangle");
            break;
    }

    return EXIT_SUCCESS;
}