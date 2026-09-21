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

static int read_line(char **line)
{
    size_t capacity = 64;
    size_t length = 0;
    char *buffer;
    int ch;

    if (line == NULL) {
        return 0;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return 0;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ch == EOF && length == 0) {
        free(buffer);
        return 0;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

static int read_side(const char *prompt, unsigned long long *side)
{
    char *buffer;
    char *start;
    char *end;
    unsigned long long value;

    if (prompt == NULL || side == NULL) {
        return 0;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return 0;
    }

    if (!read_line(&buffer)) {
        return 0;
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-') {
        free(buffer);
        return 0;
    }

    errno = 0;
    value = strtoull(start, &end, 10);

    if (start == end || errno == ERANGE || value == 0) {
        free(buffer);
        return 0;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(buffer);
        return 0;
    }

    *side = value;
    free(buffer);
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