#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <string.h>

static int closest_smaller(int n, int *result)
{
    if (result == NULL) {
        return -1;
    }
    if (n == INT_MIN) {
        return -1;
    }
    *result = n - 1;
    return 0;
}

static int parse_int(const char *str, int *value)
{
    char *endptr = NULL;
    long parsed;

    if (str == NULL || value == NULL) {
        return -1;
    }

    errno = 0;
    parsed = strtol(str, &endptr, 10);

    if (errno == ERANGE) {
        return -1;
    }
    if (endptr == str) {
        return -1;
    }
    if (*endptr != '\0' && *endptr != '\n') {
        return -1;
    }
    if (parsed > INT_MAX || parsed < INT_MIN) {
        return -1;
    }

    *value = (int)parsed;
    return 0;
}

static int read_line(char *buffer, size_t size)
{
    size_t len;
    int ch;

    if (buffer == NULL || size == 0) {
        return -1;
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return -1;
    }

    len = strnlen(buffer, size);
    if (len > 0 && buffer[len - 1] != '\n' && len == size - 1) {
        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);
        return -1;
    }

    return 0;
}

int main(void)
{
    char buffer[64];
    int n = 0;
    int result = 0;

    if (read_line(buffer, sizeof(buffer)) != 0) {
        fprintf(stderr, "Error: failed to read input\n");
        return EXIT_FAILURE;
    }

    if (parse_int(buffer, &n) != 0) {
        fprintf(stderr, "Error: invalid integer input\n");
        return EXIT_FAILURE;
    }

    if (closest_smaller(n, &result) != 0) {
        fprintf(stderr, "Error: no smaller integer representable\n");
        return EXIT_FAILURE;
    }

    if (printf("%d\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}