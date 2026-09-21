#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { MAX_INPUT_LENGTH = 4096 };

static bool is_keith_number(unsigned long long number)
{
    unsigned long long sequence[sizeof(number) * CHAR_BIT];
    unsigned long long value = number;
    size_t count = 0;
    size_t index = 0;

    if (number < 10) {
        return false;
    }

    do {
        sequence[count++] = value % 10;
        value /= 10;
    } while (value != 0);

    for (size_t left = 0, right = count - 1; left < right; ++left, --right) {
        unsigned long long temporary = sequence[left];
        sequence[left] = sequence[right];
        sequence[right] = temporary;
    }

    for (;;) {
        unsigned long long sum = 0;

        for (size_t i = 0; i < count; ++i) {
            if (sequence[i] > ULLONG_MAX - sum) {
                return false;
            }
            sum += sequence[i];
        }

        if (sum == number) {
            return true;
        }

        if (sum > number) {
            return false;
        }

        sequence[index] = sum;
        index = (index + 1) % count;
    }
}

static int discard_remainder(FILE *stream)
{
    int character;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stream);
    } while (character != '\n' && character != EOF);

    if (character == EOF && ferror(stream)) {
        return -1;
    }

    return 0;
}

static char *read_line(FILE *stream)
{
    const size_t capacity = (size_t)MAX_INPUT_LENGTH + 2;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        errno = ENOMEM;
        return NULL;
    }

    errno = 0;

    if (fgets(buffer, (int)capacity, stream) == NULL) {
        int saved_errno = errno;

        free(buffer);

        if (ferror(stream)) {
            errno = saved_errno != 0 ? saved_errno : EIO;
        } else {
            errno = ENODATA;
        }

        return NULL;
    }

    char *newline = strchr(buffer, '\n');

    if (newline != NULL) {
        *newline = '\0';
        return buffer;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(buffer);

    if (length > (size_t)MAX_INPUT_LENGTH) {
        int result = discard_remainder(stream);
        free(buffer);
        errno = result == 0 ? EOVERFLOW : EIO;
        return NULL;
    }

    if (!feof(stream)) {
        int result = discard_remainder(stream);
        free(buffer);
        errno = result == 0 ? EOVERFLOW : EIO;
        return NULL;
    }

    return buffer;
}

int main(void)
{
    char *input = read_line(stdin);

    if (input == NULL) {
        if (errno == EOVERFLOW) {
            fputs("Input is too large.\n", stderr);
        } else if (errno == ENOMEM) {
            fputs("Failed to allocate memory.\n", stderr);
        } else {
            fputs("Failed to read input.\n", stderr);
        }

        return EXIT_FAILURE;
    }

    char *start = input;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-') {
        free(input);
        fputs("Invalid number.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    unsigned long long number = strtoull(start, &end, 10);

    if (errno == ERANGE || end == start) {
        free(input);
        fputs("Invalid number.\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        fputs("Invalid number.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%llu is %sa Keith number.\n",
           number,
           is_keith_number(number) ? "" : "not ");

    free(input);
    return EXIT_SUCCESS;
}