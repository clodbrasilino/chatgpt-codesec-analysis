#include <stdio.h>
#include <inttypes.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strspn'
  */

int count_hex_numbers(int from, int to) {
    if (from > to) return 0;
    int count = 0;
    for (int i = from; i <= to; i++) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char buf[9];
        snprintf(buf, 9, "%x", i);
        /* Possible weaknesses found:
         *  call to undeclared library function 'strlen' with type 'unsigned long (const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  call to undeclared library function 'strspn' with type 'unsigned long (const char *, const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  include '<string.h>' or provide a declaration of 'strlen'
         *  include the header <string.h> or explicitly provide a declaration for 'strlen'
         *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         *  implicit declaration of function 'strspn' [-Wimplicit-function-declaration]
         *  include the header <string.h> or explicitly provide a declaration for 'strspn'
         */
        if (strspn(buf, "0123456789abcdef") == strlen(buf)) count++;
    }
    return count;
}

int main() {
    int from, to;
    printf("Enter the range (from to): ");
    scanf("%d %d", &from, &to);
    int result = count_hex_numbers(from, to);
    printf("Count: %d\n", result);
    return 0;
}