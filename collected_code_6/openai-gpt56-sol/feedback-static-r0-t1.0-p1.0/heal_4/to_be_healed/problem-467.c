#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <inttypes.h>
#include <ctype.h>
#include <sys/types.h>
 /* Possible weaknesses found:
  *  'CHAR_BIT' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

/* Possible weaknesses found:
 *  'CHAR_BIT' undeclared (first use in this function)
 *  'CHAR_BIT' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
 *  each undeclared identifier is reported only once for each function it appears in
 *  expanded from macro 'OCTAL_BUFFER_SIZE'
 */
#define OCTAL_BUFFER_SIZE ((sizeof(uintmax_t) * CHAR_BIT + 2U) / 3U + 1U)

static int decimal_to_octal(uintmax_t value, char *buffer, size_t size)
{
    int result;

    /* Possible weaknesses found:
     *  use of undeclared identifier 'CHAR_BIT'
     *  in expansion of macro 'OCTAL_BUFFER_SIZE'
     */
    if (buffer == NULL || size < OCTAL_BUFFER_SIZE) {
        return -1;
    }

    result = snprintf(buffer, size, "%jo", value);
    if (result < 0 || (size_t)result >= size) {
        return -1;
    }

    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    /* Possible weaknesses found:
     *  use of undeclared identifier 'CHAR_BIT'
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     *  in expansion of macro 'OCTAL_BUFFER_SIZE'
     */
    char output[OCTAL_BUFFER_SIZE];
    char *start;
    char *end;
    uintmax_t value;
    int status = EXIT_FAILURE;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        goto cleanup;
    }

    if (length > 0 && input[length - 1] == '\n') {
        input[--length] = '\0';
        if (length > 0 && input[length - 1] == '\r') {
            input[--length] = '\0';
        }
    } else if (!feof(stdin)) {
        goto cleanup;
    }

    start = input;
    while (*start != '\0' && isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-') {
        goto cleanup;
    }

    errno = 0;
    value = strtoumax(start, &end, 10);

    if (errno == ERANGE || end == start) {
        goto cleanup;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        goto cleanup;
    }

    if (decimal_to_octal(value, output, sizeof output) != 0) {
        goto cleanup;
    }

    if (printf("%s\n", output) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}