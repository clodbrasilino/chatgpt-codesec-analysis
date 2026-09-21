#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strspn'
  */

static int digit_sum_difference(const char *begin, const char *end)
{
    int even_sum = 0;
    int odd_sum = 0;

    if (begin < end && (*begin == '+' || *begin == '-')) {
        ++begin;
    }

    while (begin < end) {
        int digit = *begin - '0';

        if ((digit % 2) == 0) {
            even_sum += digit;
        } else {
            odd_sum += digit;
        }

        ++begin;
    }

    return even_sum - odd_sum;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];
    char *end;
    char *p;
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    p = input;
    while (isspace((unsigned char)*p)) {
        ++p;
    }

    errno = 0;
    (void)strtoll(p, &end, 10);

    if (errno == ERANGE || end == p) {
        return EXIT_FAILURE;
    }

    p = end;
    while (isspace((unsigned char)*p)) {
        ++p;
    }

    if (*p != '\0') {
        return EXIT_FAILURE;
    }

    if (p == input + sizeof input - 1 && input[sizeof input - 2] != '\n') {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
        return EXIT_FAILURE;
    }

    printf("%d\n", digit_sum_difference(
        /* Possible weaknesses found:
         *  include the header <string.h> or explicitly provide a declaration for 'strspn'
         *  call to undeclared library function 'strspn' with type 'unsigned long (const char *, const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  implicit declaration of function 'strspn' [-Wimplicit-function-declaration]
         */
        input + strspn(input, " \t\n\r\f\v"), end));

    return EXIT_SUCCESS;
}