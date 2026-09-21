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

static void discard_remaining_input(void)
{
    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != '\n' && ch != EOF);
}

static int read_line(char *buffer, size_t size)
{
    size_t len;

    if (buffer == NULL || size == 0 || size > (size_t)INT_MAX) {
        return -1;
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return -1;
    }

    buffer[size - 1] = '\0';

    len = strnlen(buffer, size);
    if (len > 0 && buffer[len - 1] != '\n' && len == size - 1) {
        discard_remaining_input();
        return -1;
    }

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[64];
    int n = 0;
    int result = 0;

    memset(buffer, 0, sizeof(buffer));

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