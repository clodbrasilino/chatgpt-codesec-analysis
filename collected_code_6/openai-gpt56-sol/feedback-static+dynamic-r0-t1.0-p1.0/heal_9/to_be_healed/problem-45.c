#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_TOKEN_LENGTH 128U

static uint64_t magnitude(int64_t value)
{
    if (value >= 0) {
        return (uint64_t)value;
    }

    return UINT64_C(0) - (uint64_t)value;
}

static uint64_t gcd_pair(uint64_t a, uint64_t b)
{
    while (b != UINT64_C(0)) {
        uint64_t remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

static int discard_token(int ch)
{
    while (ch != EOF && !isspace((unsigned char)ch)) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    }

    return ferror(stdin) ? -1 : 0;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
static int read_token(char token[MAX_TOKEN_LENGTH])
{
    size_t length = 0U;
    int ch;

    if (token == NULL) {
        return -1;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return -1;
    }

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (length + 1U >= MAX_TOKEN_LENGTH) {
            (void)discard_token(ch);
            token[0] = '\0';
            return -1;
        }

        token[length++] = (char)ch;
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    }

    if (ferror(stdin)) {
        token[0] = '\0';
        return -1;
    }

    token[length] = '\0';
    return 0;
}

static int read_size(size_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char token[MAX_TOKEN_LENGTH];
    char *end;
    uintmax_t parsed;

    if (value == NULL || read_token(token) != 0) {
        return -1;
    }

    if (token[0] == '-') {
        return -1;
    }

    errno = 0;
    parsed = strtoumax(token, &end, 10);

    if (errno == ERANGE ||
        end == token ||
        *end != '\0' ||
        parsed == UINTMAX_C(0) ||
        parsed > (uintmax_t)SIZE_MAX) {
        return -1;
    }

    *value = (size_t)parsed;
    return 0;
}

static int read_int64(int64_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char token[MAX_TOKEN_LENGTH];
    char *end;
    intmax_t parsed;

    if (value == NULL || read_token(token) != 0) {
        return -1;
    }

    errno = 0;
    parsed = strtoimax(token, &end, 10);

    if (errno == ERANGE ||
        end == token ||
        *end != '\0' ||
        parsed < (intmax_t)INT64_MIN ||
        parsed > (intmax_t)INT64_MAX) {
        return -1;
    }

    *value = (int64_t)parsed;
    return 0;
}

int main(void)
{
    size_t count;
    uint64_t result = UINT64_C(0);

    if (read_size(&count) != 0) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        int64_t value;

        if (read_int64(&value) != 0) {
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }

        result = gcd_pair(result, magnitude(value));
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}