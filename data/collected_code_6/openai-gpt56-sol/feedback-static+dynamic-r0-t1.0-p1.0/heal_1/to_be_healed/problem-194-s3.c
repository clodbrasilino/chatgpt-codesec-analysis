#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strcspn'
  */

static int octal_to_decimal(const char *octal, uintmax_t *decimal)
{
    char *end = NULL;
    uintmax_t value;

    if (octal == NULL || decimal == NULL || *octal == '\0' || *octal == '-') {
        return 0;
    }

    errno = 0;
    value = strtoumax(octal, &end, 8);

    if (errno == ERANGE || end == octal || *end != '\0') {
        return 0;
    }

    *decimal = value;
    return 1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    uintmax_t decimal;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fprintf(stderr, "Failed to read input.\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  implicit declaration of function 'strcspn' [-Wimplicit-function-declaration]
     *  include the header <string.h> or explicitly provide a declaration for 'strcspn'
     *  call to undeclared library function 'strcspn' with type 'unsigned long (const char *, const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    input[strcspn(input, "\n")] = '\0';

    if (!octal_to_decimal(input, &decimal)) {
        fprintf(stderr, "Invalid octal number.\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIuMAX "\n", decimal);
    return EXIT_SUCCESS;
}