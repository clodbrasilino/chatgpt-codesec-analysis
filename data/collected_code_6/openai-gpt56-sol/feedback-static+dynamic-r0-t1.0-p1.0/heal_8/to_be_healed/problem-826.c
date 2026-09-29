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
    unsigned long long smallest = a;
    unsigned long long middle = b;
    unsigned long long largest = c;
    unsigned long long temporary;

    if (a == 0 || b == 0 || c == 0) {
        return TRIANGLE_INVALID;
    }

    if (smallest > middle) {
        temporary = smallest;
        smallest = middle;
        middle = temporary;
    }

    if (middle > largest) {
        temporary = middle;
        middle = largest;
        largest = temporary;
    }

    if (smallest > middle) {
        temporary = smallest;
        smallest = middle;
        middle = temporary;
    }

    if (smallest <= largest - middle) {
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

static int read_line(FILE *stream, char *buffer, size_t capacity)
{
    size_t length = 0;
    int ch;

    if (stream == NULL || buffer == NULL || capacity < 2) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stream)) != '\n' && ch != EOF) {
        if (length + 1 >= capacity) {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((ch = fgetc(stream)) != '\n' && ch != EOF) {
            }
            buffer[0] = '\0';
            return 0;
        }

        buffer[length++] = (char)ch;
    }

    if (ch == EOF && (ferror(stream) || length == 0)) {
        buffer[0] = '\0';
        return 0;
    }

    if (length > 0 && buffer[length - 1] == '\r') {
        --length;
    }

    buffer[length] = '\0';
    return 1;
}

static int read_side(const char *prompt, unsigned long long *side)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    char *start;
    char *end;
    unsigned long long value;

    if (prompt == NULL || side == NULL) {
        return 0;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return 0;
    }

    if (!read_line(stdin, buffer, sizeof(buffer))) {
        return 0;
    }

    start = buffer;
    while (*start != '\0' && isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-' || *start == '+') {
        return 0;
    }

    errno = 0;
    end = NULL;
    value = strtoull(start, &end, 10);

    if (end == start || errno == ERANGE || value == 0 ||
        value > ULLONG_MAX) {
        return 0;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
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