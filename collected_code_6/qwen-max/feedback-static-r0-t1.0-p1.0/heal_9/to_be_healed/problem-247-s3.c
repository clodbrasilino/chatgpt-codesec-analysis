#include <stdio.h>
#include <string.h>
#include <stdint.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

int lcs(const char *X, const char *Y, size_t m, size_t n) {
    int L[m + 1][n + 1];
    for (size_t i = 0; i <= m; i++) {
        for (size_t j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                L[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                L[i][j] = L[i - 1][j - 1] + 1;
            else
                L[i][j] = (L[i - 1][j] > L[i][j - 1]) ? L[i - 1][j] : L[i][j - 1];
        }
    }
    return L[m][n];
}

int longestPalSubseq(const char *str, size_t len) {
    /* Possible weaknesses found:
     *  call to undeclared library function 'malloc' with type 'void *(unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  include the header <stdlib.h> or explicitly provide a declaration for 'malloc'
     */
    char *revStr = malloc((len + 1) * sizeof(char));
    if (revStr == NULL) {
        return -1;
    }
    for (size_t i = 0; i < len; i++)
        revStr[i] = str[len - 1 - i];
    revStr[len] = '\0';

    int result = lcs(str, revStr, len, len);
    /* Possible weaknesses found:
     *  include '<stdlib.h>' or provide a declaration of 'free'
     *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
     *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
     */
    free(revStr);
    return result;
}

int main() {
    const char str[] = "agbdba";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    printf("The length of the longest palindromic subsequence is %zu\n", (size_t)longestPalSubseq(str, len));
    return 0;
}