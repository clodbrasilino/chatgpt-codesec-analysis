#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strlen'
  */

static int sum_odd_naturals(int64_t l, int64_t r, uint64_t *result)
{
    uint64_t first;
    uint64_t last;
    uint64_t count;
    uint64_t factor;

    if (result == NULL || l < 1 || r < l) {
        return 0;
    }

    first = (uint64_t)l;
    last = (uint64_t)r;

    if ((first & UINT64_C(1)) == 0) {
        ++first;
    }

    if ((last & UINT64_C(1)) == 0) {
        --last;
    }

    if (first > last) {
        *result = UINT64_C(0);
        return 1;
    }

    count = (last - first) / UINT64_C(2) + UINT64_C(1);
    factor = first / UINT64_C(2) + last / UINT64_C(2) +
             (first % UINT64_C(2) + last % UINT64_C(2)) / UINT64_C(2);

    if (factor != 0 && count > UINT64_MAX / factor) {
        return 0;
    }

    *result = count * factor;
    return 1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    char *cursor;
    char *end;
    intmax_t left_value;
    intmax_t right_value;
    uint64_t sum;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  include the header <string.h> or explicitly provide a declaration for 'strlen'
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'strlen' with type 'unsigned long (const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    if (input[0] != '\0' && input[strlen(input) - 1] != '\n' && !feof(stdin)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = input;

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    errno = 0;
    left_value = strtoimax(cursor, &end, 10);
    if (cursor == end || errno == ERANGE) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = end;
    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    errno = 0;
    right_value = strtoimax(cursor, &end, 10);
    if (cursor == end || errno == ERANGE) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = end;
    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0' ||
        left_value < INT64_MIN || left_value > INT64_MAX ||
        right_value < INT64_MIN || right_value > INT64_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!sum_odd_naturals((int64_t)left_value, (int64_t)right_value, &sum)) {
        fputs("Invalid range or arithmetic overflow\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}