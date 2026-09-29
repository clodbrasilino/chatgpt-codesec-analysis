#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'abs'
  */

int minSwaps(const char *s1, const char *s2) {
    int count[2] = {0, 0};
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len1 = strlen(s1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len2 = strlen(s2);
    if (s1[len1-1] != '\0' || s2[len2-1] != '\0') {
        return -1;
    }
    size_t len = (len1 < len2) ? len1 : len2;

    for (size_t i = 0; i < len; i++) {
        if (s1[i] != s2[i]) {
            if (s1[i] == '0' || s1[i] == '1') {
                count[s1[i] - '0']++;
            }
            if (s2[i] == '0' || s2[i] == '1') {
                count[s2[i] - '0']--;
            }
        }
    }

    /* Possible weaknesses found:
     *  include the header <stdlib.h> or explicitly provide a declaration for 'abs'
     *  call to undeclared library function 'abs' with type 'int (int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'abs' [-Wimplicit-function-declaration]
     */
    return (count[0] + count[1] != 0) ? -1 : (abs(count[0]) + abs(count[1])) / 2;
}

int main() {
    const char s1[] = "1100";
    const char s2[] = "1001";
    int result = minSwaps(s1, s2);
    if (result == -1) {
        printf("Not Possible\n");
    } else {
        printf("Minimum swaps required: %d\n", result);
    }
    return 0;
}