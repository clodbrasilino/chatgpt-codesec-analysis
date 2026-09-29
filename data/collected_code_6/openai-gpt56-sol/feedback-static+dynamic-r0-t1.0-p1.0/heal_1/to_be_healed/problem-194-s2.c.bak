#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strcspn'
  */

static int octal_to_decimal(const char *input, uintmax_t *result)
{
    char *end = NULL;
    uintmax_t value;

    if (input == NULL || result == NULL || *input == '\0') {
        return -1;
    }

    errno = 0;
    value = strtoumax(input, &end, 8);

    if (errno == ERANGE || end == input || *end != '\0') {
        return -1;
    }

    *result = value;
    return 0;
}

int main(void)
{
    char input[256];
    uintmax_t decimal;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  include the header <string.h> or explicitly provide a declaration for 'strcspn'
     *  call to undeclared library function 'strcspn' with type 'unsigned long (const char *, const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'strcspn' [-Wimplicit-function-declaration]
     */
    input[strcspn(input, "\n")] = '\0';

    if (octal_to_decimal(input, &decimal) != 0) {
        fputs("Invalid octal number\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIuMAX "\n", decimal) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}