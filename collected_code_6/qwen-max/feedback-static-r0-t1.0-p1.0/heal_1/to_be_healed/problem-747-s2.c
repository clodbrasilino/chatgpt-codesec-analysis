#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

/* Possible weaknesses found:
 *  Parameter 'Y' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'Z' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'X' can be declared as pointer to const [constParameterPointer]
 */
int lcsLength(char* X, char* Y, char* Z, int m, int n, int o) {
    int L[m+1][n+1][o+1];
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            for (int k = 0; k <= o; k++) {
                if (i == 0 || j == 0 || k == 0)
                    L[i][j][k] = 0;
                else if (X[i-1] == Y[j-1] && X[i-1] == Z[k-1])
                    L[i][j][k] = L[i-1][j-1][k-1] + 1;
                else
                    L[i][j][k] = (L[i-1][j][k] > L[i][j-1][k]) ? ((L[i-1][j][k] > L[i][j][k-1]) ? L[i-1][j][k] : L[i][j][k-1]) : ((L[i][j-1][k] > L[i][j][k-1]) ? L[i][j-1][k] : L[i][j][k-1]);
            }
        }
    }
    return L[m][n][o];
}

void printLCS(char** buf, int idx, char* X, char* Y, char* Z, int m, int n, int o, int lcsLen, int i, int j, int k) {
    if (i == 0 || j == 0 || k == 0) return;
    if (X[i-1] == Y[j-1] && X[i-1] == Z[k-1]) {
        (*buf)[idx] = X[i-1];
        printLCS(buf, idx-1, X, Y, Z, m, n, o, lcsLen, i-1, j-1, k-1);
    /* Possible weaknesses found:
     *  use of undeclared identifier 'L'
     *  each undeclared identifier is reported only once for each function it appears in
     *  'L' undeclared (first use in this function)
     */
    } else if (lcsLen == L[i-1][j][k])
        printLCS(buf, idx, X, Y, Z, m, n, o, lcsLen, i-1, j, k);
    /* Possible weaknesses found:
     *  use of undeclared identifier 'L'
     */
    else if (lcsLen == L[i][j-1][k])
        printLCS(buf, idx, X, Y, Z, m, n, o, lcsLen, i, j-1, k);
    else
        printLCS(buf, idx, X, Y, Z, m, n, o, lcsLen, i, j, k-1);
}

int main() {
    char X[] = "AGGT12";
    char Y[] = "12TXAYB";
    char Z[] = "12XBA";
    int m = strlen(X), n = strlen(Y), o = strlen(Z);

    int lcsLen = lcsLength(X, Y, Z, m, n, o);
    /* Possible weaknesses found:
     *  call to undeclared library function 'malloc' with type 'void *(unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <stdlib.h> or explicitly provide a declaration for 'malloc'
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     */
    char *lcsBuf = (char*)malloc((lcsLen + 1) * sizeof(char));
    lcsBuf[lcsLen] = '\0';
    printLCS(&lcsBuf, lcsLen-1, X, Y, Z, m, n, o, lcsLen, m, n, o);

    printf("LCS: %s\n", lcsBuf);
    /* Possible weaknesses found:
     *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
     *  include '<stdlib.h>' or provide a declaration of 'free'
     */
    free(lcsBuf);

    return 0;
}