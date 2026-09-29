#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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
    char buffer[256];

    while (fgets(buffer, sizeof buffer, stream) != NULL) {
        size_t i = 0;

        while (buffer[i] != '\0') {
            if (buffer[i] == '\n') {
                return 0;
            }
            ++i;
        }
    }

    return ferror(stream) ? -1 : 0;
}

static char *read_line(FILE *stream)
{
    enum { MAX_INPUT_LENGTH = 4096 };
    char *buffer;
    size_t capacity = MAX_INPUT_LENGTH + 2;
    size_t length = 0;

    buffer = malloc(capacity);
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

    while (buffer[length] != '\0' && buffer[length] != '\n') {
        ++length;
    }

    if (buffer[length] == '\n') {
        buffer[length] = '\0';
        return buffer;
    }

    if (length > MAX_INPUT_LENGTH) {
        int result = discard_remainder(stream);

        free(buffer);
        errno = result == 0 ? EOVERFLOW : EIO;
        return NULL;
    }

    return buffer;
}

int main(void)
{
    char *input;
    char *start;
    char *end;
    unsigned long long number;

    input = read_line(stdin);

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

    start = input;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-') {
        free(input);
        fputs("Invalid number.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoull(start, &end, 10);

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
           number, is_keith_number(number) ? "" : "not ");

    free(input);
    return EXIT_SUCCESS;
}