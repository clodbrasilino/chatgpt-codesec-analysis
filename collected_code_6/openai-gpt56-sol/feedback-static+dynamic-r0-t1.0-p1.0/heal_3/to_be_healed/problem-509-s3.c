#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int average_of_odds(unsigned long long limit, long double *average)
{
    if (average == NULL || limit == 0 || (limit % 2) == 0) {
        return -1;
    }

    *average = ((long double)limit + 1.0L) / 2.0L;
    return 0;
}

static int read_line(char **line)
{
    size_t length = 0;
    size_t capacity = 64;
    int ch;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length == capacity - 1) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return -1;
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

int main(void)
{
    char *input = NULL;
    char *end;
    unsigned long long limit;
    long double average;
    int read_result = read_line(&input);

    if (read_result <= 0) {
        fputs(read_result == 0 ? "Failed to read input.\n"
                              : "Unable to store input.\n",
              stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    limit = strtoull(input, &end, 10);

    if (errno == ERANGE || end == input) {
        fputs("Invalid number.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t') {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (average_of_odds(limit, &average) != 0) {
        fputs("Enter a positive odd number.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("Average: %.2Lf\n", average);
    return EXIT_SUCCESS;
}