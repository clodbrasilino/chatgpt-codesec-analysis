#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'UINT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

static int count_tilings(unsigned int n, uint64_t *result)
{
    uint64_t previous = UINT64_C(1);
    uint64_t current = UINT64_C(3);

    if (result == NULL) {
        return -1;
    }

    if ((n & 1U) != 0U) {
        *result = UINT64_C(0);
        return 0;
    }

    if (n == 0U) {
        *result = previous;
        return 0;
    }

    for (unsigned int i = 4U; i <= n; i += 2U) {
        if (current > UINT64_MAX / UINT64_C(4)) {
            return -1;
        }

        uint64_t product = UINT64_C(4) * current;

        if (product < previous) {
            return -1;
        }

        previous = current;
        current = product - previous;

        if (i == n) {
            break;
        }
    }

    *result = current;
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    int ch;
    char *end = NULL;
    uintmax_t value;
    uint64_t result;
    int status = EXIT_FAILURE;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length == capacity) {
            size_t new_capacity = capacity == 0U ? 64U : capacity * 2U;

            if (new_capacity <= capacity) {
                goto cleanup;
            }

            char *new_input = realloc(input, new_capacity);

            if (new_input == NULL) {
                goto cleanup;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin) || (ch == EOF && length == 0U)) {
        goto cleanup;
    }

    if (length == capacity) {
        if (capacity == SIZE_MAX) {
            goto cleanup;
        }

        char *new_input = realloc(input, capacity + 1U);

        if (new_input == NULL) {
            goto cleanup;
        }

        input = new_input;
        capacity++;
    }

    input[length] = '\0';

    errno = 0;
    value = strtoumax(input, &end, 10);

    /* Possible weaknesses found:
     *  'UINT_MAX' undeclared (first use in this function)
     *  use of undeclared identifier 'UINT_MAX'
     *  each undeclared identifier is reported only once for each function it appears in
     */
    if (errno == ERANGE || end == input || value > UINT_MAX) {
        goto cleanup;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        end++;
    }

    if (*end != '\0') {
        goto cleanup;
    }

    if (count_tilings((unsigned int)value, &result) != 0) {
        goto cleanup;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}