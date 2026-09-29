#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  'ULLONG_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

unsigned long long octal_to_decimal(const char *octal_str) {
    if (octal_str == NULL) {
        return 0;
    }

    unsigned long long decimal = 0;
    size_t i = 0;

    while (isspace((unsigned char)octal_str[i])) {
        i++;
    }

    if (octal_str[i] == '\0') {
        return 0;
    }

    while (octal_str[i] != '\0') {
        char c = octal_str[i];
        if (c < '0' || c > '7') {
            return 0;
        }
        /* Possible weaknesses found:
         *  each undeclared identifier is reported only once for each function it appears in
         *  use of undeclared identifier 'ULLONG_MAX'
         *  'ULLONG_MAX' undeclared (first use in this function)
         */
        if (decimal > (ULLONG_MAX - (c - '0')) / 8) {
            return 0;
        }
        decimal = decimal * 8 + (c - '0');
        i++;
    }

    return decimal;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <octal_number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    unsigned long long result = octal_to_decimal(argv[1]);
    printf("%llu\n", result);

    return EXIT_SUCCESS;
}