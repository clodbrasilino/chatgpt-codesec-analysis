#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <ctype.h>
#include <errno.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  *  include '<string.h>' or provide a declaration of 'strchr'
  */

#define INPUT_SIZE 256U

static uint64_t divisor_occurrences(uint64_t divisor, uint64_t lower,
                                    uint64_t upper)
{
    return upper / divisor - (lower - 1U) / divisor;
}

static int find_max_occurring_divisor(uint64_t lower, uint64_t upper,
                                      uint64_t *divisor,
                                      uint64_t *occurrences)
{
    if (divisor == NULL || occurrences == NULL ||
        lower == 0U || lower > upper) {
        return -1;
    }

    *divisor = 1U;
    *occurrences = divisor_occurrences(*divisor, lower, upper);
    return 0;
}

static int parse_interval(const char *input, uint64_t *lower, uint64_t *upper)
{
    const char *cursor;
    char *end;
    uintmax_t first;
    uintmax_t second;

    if (input == NULL || lower == NULL || upper == NULL) {
        return -1;
    }

    cursor = input;
    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor == '\0' || *cursor == '-') {
        return -1;
    }

    errno = 0;
    first = strtoumax(cursor, &end, 10);
    if (cursor == end || errno == ERANGE || first > UINT64_MAX) {
        return -1;
    }

    cursor = end;
    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor == '\0' || *cursor == '-') {
        return -1;
    }

    errno = 0;
    second = strtoumax(cursor, &end, 10);
    if (cursor == end || errno == ERANGE || second > UINT64_MAX) {
        return -1;
    }

    cursor = end;
    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        return -1;
    }

    *lower = (uint64_t)first;
    *upper = (uint64_t)second;
    return 0;
}

static int discard_line(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char discard[INPUT_SIZE];

    for (;;) {
        if (fgets(discard, sizeof discard, stdin) == NULL) {
            return ferror(stdin) ? -1 : 0;
        }

        /* Possible weaknesses found:
         *  implicit declaration of function 'strchr' [-Wimplicit-function-declaration]
         *  call to undeclared library function 'strchr' with type 'char *(const char *, int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  include the header <string.h> or explicitly provide a declaration for 'strchr'
         */
        if (strchr(discard, '\n') != NULL) {
            return 0;
        }
    }
}

static int read_line(char *buffer, size_t size)
{
    size_t length;

    /* Possible weaknesses found:
     *  use of undeclared identifier 'INT_MAX'
     *  'INT_MAX' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     */
    if (buffer == NULL || size < 2U || size > (size_t)INT_MAX) {
        return -1;
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     *  include '<string.h>' or provide a declaration of 'strlen'
     *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     *  call to undeclared library function 'strlen' with type 'unsigned long (const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <string.h> or explicitly provide a declaration for 'strlen'
     */
    length = strlen(buffer);

    if (length > 0U && buffer[length - 1U] == '\n') {
        buffer[length - 1U] = '\0';
        return 0;
    }

    if (feof(stdin)) {
        return 0;
    }

    if (discard_line() != 0) {
        return -1;
    }

    return -1;
}

int main(void)
{
    char *input;
    uint64_t lower;
    uint64_t upper;
    uint64_t divisor;
    uint64_t occurrences;
    int status;

    input = malloc(INPUT_SIZE);
    if (input == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    status = read_line(input, INPUT_SIZE);
    if (status != 0) {
        fputs("Invalid input\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    status = parse_interval(input, &lower, &upper);
    free(input);

    if (status != 0) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (find_max_occurring_divisor(lower, upper,
                                   &divisor, &occurrences) != 0) {
        fputs("Invalid interval\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Divisor: %" PRIu64 "\nOccurrences: %" PRIu64 "\n",
               divisor, occurrences) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}