#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>

#define MAX_INPUT_LENGTH 128

static int is_perfect_square(unsigned long long number)
{
    unsigned long long low = 1;
    unsigned long long high = number;

    while (low <= high) {
        unsigned long long mid = low + (high - low) / 2;
        unsigned long long quotient = number / mid;

        if (mid == quotient && number % mid == 0) {
            return 1;
        }

        if (mid < quotient) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return 0;
}

static int read_line(FILE *stream, char **line)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_INPUT_LENGTH + 2];
    size_t length;

    if (stream == NULL || line == NULL) {
        errno = EINVAL;
        return -1;
    }

    *line = NULL;

    if (fgets(buffer, sizeof buffer, stream) == NULL) {
        return feof(stream) ? 0 : -1;
    }

    length = 0;
    while (buffer[length] != '\0' && buffer[length] != '\n') {
        ++length;
    }

    if (buffer[length] == '\n') {
        buffer[length] = '\0';
    } else if (!feof(stream)) {
        int ch;

        do {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = fgetc(stream);
        } while (ch != '\n' && ch != EOF);

        if (ch == EOF && ferror(stream)) {
            return -1;
        }

        errno = EOVERFLOW;
        return -1;
    }

    *line = malloc(length + 1);
    if (*line == NULL) {
        return -1;
    }

    for (size_t i = 0; i <= length; ++i) {
        (*line)[i] = buffer[i];
    }

    return 1;
}

int main(void)
{
    char *input = NULL;
    char *start;
    char *end;
    unsigned long long number;
    int status;

    errno = 0;
    status = read_line(stdin, &input);

    if (status <= 0) {
        fputs("Failed to read input.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    start = input;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-' ||
        !isdigit((unsigned char)*start)) {
        fputs("Invalid positive integer.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoull(start, &end, 10);

    if (errno == ERANGE || end == start || number == 0) {
        fputs("Invalid positive integer.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid positive integer.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    puts(is_perfect_square(number) ? "Odd" : "Even");

    free(input);
    return EXIT_SUCCESS;
}