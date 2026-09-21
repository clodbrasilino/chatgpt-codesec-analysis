#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100

int max3(int a, int b, int c) {
    int max = a;
    if (b > max) max = b;
    if (c > max) max = c;
    return max;
}

int max2(int a, int b) {
    return (a > b) ? a : b;
}

/* Possible weaknesses found:
 *  Parameter 'Y' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'X' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'Z' can be declared as pointer to const [constParameterPointer]
 */
void findLCS(char *X, char *Y, char *Z, int m, int n, int o) {
    int L[MAX_LEN + 1][MAX_LEN + 1][MAX_LEN + 1];
    int i, j, k;

    for (i = 0; i <= m; i++) {
        for (j = 0; j <= n; j++) {
            for (k = 0; k <= o; k++) {
                if (i == 0 || j == 0 || k == 0)
                    L[i][j][k] = 0;
                else if (X[i - 1] == Y[j - 1] && X[i - 1] == Z[k - 1])
                    L[i][j][k] = L[i - 1][j - 1][k - 1] + 1;
                else
                    L[i][j][k] = max3(L[i - 1][j][k], L[i][j - 1][k], L[i][j][k - 1]);
            }
        }
    }

    int index = L[m][n][o];
    char *lcs = (char *)malloc((index + 1) * sizeof(char));
    if (lcs == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    lcs[index] = '\0';

    i = m;
    j = n;
    k = o;
    while (i > 0 && j > 0 && k > 0) {
        if (X[i - 1] == Y[j - 1] && X[i - 1] == Z[k - 1]) {
            lcs[index - 1] = X[i - 1];
            i--;
            j--;
            k--;
            index--;
        } else if (L[i - 1][j][k] >= L[i][j - 1][k] && L[i - 1][j][k] >= L[i][j][k - 1])
            i--;
        else if (L[i][j - 1][k] >= L[i - 1][j][k] && L[i][j - 1][k] >= L[i][j][k - 1])
            j--;
        else
            k--;
    }

    printf("Longest Common Subsequence: %s\n", lcs);
    printf("Length: %d\n", L[m][n][o]);

    free(lcs);
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char X[MAX_LEN + 1];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char Y[MAX_LEN + 1];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char Z[MAX_LEN + 1];

    printf("Enter first string: ");
    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (scanf("%100s", X) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    printf("Enter second string: ");
    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (scanf("%100s", Y) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    printf("Enter third string: ");
    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (scanf("%100s", Z) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int m = strlen(X);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int n = strlen(Y);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int o = strlen(Z);

    findLCS(X, Y, Z, m, n, o);

    return EXIT_SUCCESS;
}