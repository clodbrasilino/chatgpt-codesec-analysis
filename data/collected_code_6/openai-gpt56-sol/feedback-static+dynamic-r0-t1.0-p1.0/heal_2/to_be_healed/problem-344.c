#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strchr'
  *  include '<ctype.h>' or provide a declaration of 'isspace'
  */

static uint64_t integer_sqrt(uint64_t value)
{
    uint64_t result = 0;
    uint64_t bit = UINT64_C(1) << 62;

    while (bit > value) {
        bit >>= 2;
    }

    while (bit != 0) {
        if (value >= result + bit) {
            value -= result + bit;
            result = (result >> 1) + bit;
        } else {
            result >>= 1;
        }

        bit >>= 2;
    }

    return result;
}

static uint64_t count_odd_factors_in_range(uint64_t lower, uint64_t upper)
{
    uint64_t count;
    uint64_t square_count;

    if (lower > upper) {
        return 0;
    }

    count = upper - lower + UINT64_C(1);
    square_count = integer_sqrt(upper);

    if (lower != 0) {
        square_count -= integer_sqrt(lower - UINT64_C(1));
    }

    return count - square_count;
}

static int parse_uint64(const char **input, uint64_t *value)
{
    char *end;
    uintmax_t parsed;

    errno = 0;
    parsed = strtoumax(*input, &end, 10);

    if (end == *input || errno == ERANGE || parsed > UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    *input = end;
    return 1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char line[256];
    const char *cursor;
    uint64_t lower;
    uint64_t upper;
    /* Possible weaknesses found:
     *  The scope of the variable 'character' can be reduced. [variableScope]
     */
    int character;

    if (fgets(line, sizeof line, stdin) == NULL) {
        return 1;
    }

    /* Possible weaknesses found:
     *  include the header <string.h> or explicitly provide a declaration for 'strchr'
     *  implicit declaration of function 'strchr' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'strchr' with type 'char *(const char *, int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    if (strchr(line, '\n') == NULL) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((character = getchar()) != '\n' && character != EOF) {
        }
        return 1;
    }

    cursor = line;

    /* Possible weaknesses found:
     *  call to undeclared library function 'isspace' with type 'int (int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'isspace' [-Wimplicit-function-declaration]
     *  include the header <ctype.h> or explicitly provide a declaration for 'isspace'
     */
    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor == '-') {
        return 1;
    }

    if (!parse_uint64(&cursor, &lower)) {
        return 1;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor == '-') {
        return 1;
    }

    if (!parse_uint64(&cursor, &upper)) {
        return 1;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0' || lower > upper) {
        return 1;
    }

    printf("%" PRIu64 "\n", count_odd_factors_in_range(lower, upper));
    return 0;
}