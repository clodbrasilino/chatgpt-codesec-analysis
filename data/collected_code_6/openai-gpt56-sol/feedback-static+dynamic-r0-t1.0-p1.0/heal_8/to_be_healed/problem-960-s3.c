#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <ctype.h>
/* Possible weaknesses found:
 *  include '<string.h>' or provide a declaration of 'strchr'
 *  'errno' is defined in header '<errno.h>'; this is probably fixable by adding '#include <errno.h>'
 */
#include <stdint.h>
#include <stdint.h>
#include <stdint.h>

static int count_tilings(size_t n, uint64_t *result)
{
    uint64_t previous = 1;
    uint64_t current = 1;

    if (result == NULL) {
        return -1;
    }

    for (size_t i = 2; i <= n; ++i) {
        if (UINT64_MAX - current < previous) {
            return -1;
        }

        uint64_t next = current + previous;
        previous = current;
        current = next;
    }

    *result = current;
    return 0;
}

static int read_input(size_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char *start;
    char *end;
    uintmax_t input;

    if (value == NULL) {
        return -1;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     *  include the header <string.h> or explicitly provide a declaration for 'strchr'
     *  implicit declaration of function 'strchr' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'strchr' with type 'char *(const char *, int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    if (strchr(buffer, '\n') == NULL && !feof(stdin)) {
        int ch;

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        }

        return -1;
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '+' || *start == '-') {
        return -1;
    }

    /* Possible weaknesses found:
     *  each undeclared identifier is reported only once for each function it appears in
     *  use of undeclared identifier 'errno'
     *  'errno' undeclared (first use in this function)
     */
    errno = 0;
    input = strtoumax(start, &end, 10);

    /* Possible weaknesses found:
     *  'ERANGE' undeclared (first use in this function)
     *  use of undeclared identifier 'errno'
     *  use of undeclared identifier 'ERANGE'
     */
    if (errno == ERANGE || end == start || input > SIZE_MAX) {
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *value = (size_t)input;
    return 0;
}

int main(void)
{
    size_t input;
    uint64_t result;

    if (read_input(&input) != 0) {
        return EXIT_FAILURE;
    }

    if (count_tilings(input, &result) != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}