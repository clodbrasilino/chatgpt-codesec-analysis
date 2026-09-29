#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int is_prime(uint64_t number)
{
    uint64_t divisor;

    if (number < 2U) {
        return 0;
    }

    if (number == 2U) {
        return 1;
    }

    if (number % 2U == 0U) {
        return 0;
    }

    for (divisor = 3U; divisor <= number / divisor; divisor += 2U) {
        if (number % divisor == 0U) {
            return 0;
        }
    }

    return 1;
}

static int sum_primes(uint64_t limit, uint64_t *sum)
{
    uint64_t number;
    uint64_t total = 0U;

    if (sum == NULL) {
        return -1;
    }

    for (number = 2U; number <= limit; ++number) {
        if (is_prime(number)) {
            if (number > UINT64_MAX - total) {
                return -1;
            }
            total += number;
        }

        if (number == UINT64_MAX) {
            break;
        }
    }

    *sum = total;
    return 0;
}

static int read_uint64(uint64_t *value)
{
    char buffer[256];
    char *cursor;
    char *end;
    uintmax_t parsed;
    size_t length;

    if (value == NULL) {
        return -1;
    }

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return -1;
    }

    length = 0U;
    while (length < sizeof(buffer) && buffer[length] != '\0') {
        ++length;
    }

    if (length == sizeof(buffer)) {
        return -1;
    }

    if (length > 0U && buffer[length - 1U] == '\n') {
        buffer[--length] = '\0';
        if (length > 0U && buffer[length - 1U] == '\r') {
            buffer[length - 1U] = '\0';
        }
    } else {
        int ch = fgetc(stdin);

        if (ch != '\n' && ch != EOF) {
            while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
            }
            return -1;
        }

        if (ch == EOF && ferror(stdin)) {
            return -1;
        }
    }

    cursor = buffer;
    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor == '-' || *cursor == '\0') {
        return -1;
    }

    errno = 0;
    parsed = strtoumax(cursor, &end, 10);

    if (errno == ERANGE || end == cursor || parsed > UINT64_MAX) {
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *value = (uint64_t)parsed;
    return 0;
}

int main(void)
{
    uint64_t limit;
    uint64_t sum;

    if (read_uint64(&limit) != 0) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (sum_primes(limit, &sum) != 0) {
        fputs("Unable to calculate the sum.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}