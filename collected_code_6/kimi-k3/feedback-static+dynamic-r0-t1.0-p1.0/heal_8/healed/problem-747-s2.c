#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

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

void findLCS(const char *X, const char *Y, const char *Z, int m, int n, int o) {
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
    char *lcs = (char *)malloc((size_t)(index + 1) * sizeof(char));
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

int read_input(char *buffer, size_t size, const char *prompt) {
    printf("%s", prompt);
    if (fgets(buffer, (int)size, stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return -1;
    }
    
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else if (len == size - 1 && !feof(stdin)) {
        fprintf(stderr, "Input exceeds maximum length\n");
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return -1;
    }
    return 0;
}

int main() {
    char X[MAX_LEN + 1];
    char Y[MAX_LEN + 1];
    char Z[MAX_LEN + 1];
    size_t m, n, o;

    if (read_input(X, sizeof(X), "Enter first string: ") != 0) {
        return EXIT_FAILURE;
    }
    
    if (read_input(Y, sizeof(Y), "Enter second string: ") != 0) {
        return EXIT_FAILURE;
    }
    
    if (read_input(Z, sizeof(Z), "Enter third string: ") != 0) {
        return EXIT_FAILURE;
    }

    m = strnlen(X, MAX_LEN + 1);
    n = strnlen(Y, MAX_LEN + 1);
    o = strnlen(Z, MAX_LEN + 1);

    if (m > MAX_LEN || n > MAX_LEN || o > MAX_LEN) {
        fprintf(stderr, "Input exceeds maximum length\n");
        return EXIT_FAILURE;
    }

    findLCS(X, Y, Z, (int)m, (int)n, (int)o);

    return EXIT_SUCCESS;
}