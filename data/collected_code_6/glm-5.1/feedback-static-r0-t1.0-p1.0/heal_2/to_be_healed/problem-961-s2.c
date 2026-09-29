#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strlen'
  */

int roman_to_int(const char *s) {
    if (s == NULL || *s == '\0') {
        return 0;
    }

    int total = 0;
    int prev_value = 0;

    /* Possible weaknesses found:
     *  call to undeclared library function 'strlen' with type 'unsigned long (const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     *  include the header <string.h> or explicitly provide a declaration for 'strlen'
     */
    for (int i = (int)strlen(s) - 1; i >= 0; i--) {
        int current_value = 0;
        switch (s[i]) {
            case 'I': current_value = 1; break;
            case 'V': current_value = 5; break;
            case 'X': current_value = 10; break;
            case 'L': current_value = 50; break;
            case 'C': current_value = 100; break;
            case 'D': current_value = 500; break;
            case 'M': current_value = 1000; break;
            default: return 0;
        }

        if (current_value < prev_value) {
            total -= current_value;
        } else {
            total += current_value;
        }
        prev_value = current_value;
    }

    return total;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <roman_numeral>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int result = roman_to_int(argv[1]);
    printf("%d\n", result);

    return EXIT_SUCCESS;
}