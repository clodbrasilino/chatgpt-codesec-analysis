#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

#define MAX_SAFE_STR_LEN (SIZE_MAX / 4)

static int max3(int a, int b, int c) {
    int max = a;
    if (b > max) max = b;
    if (c > max) max = c;
    return max;
}

static size_t safe_strlen(const char *s, size_t maxlen) {
    size_t len = 0;
    if (s == NULL) return 0;
    while (len < maxlen && s[len] != '\0') {
        len++;
    }
    return len;
}

char* findLCS(const char* X, const char* Y, const char* Z) {
    if (X == NULL || Y == NULL || Z == NULL) {
        return NULL;
    }

    size_t m = safe_strlen(X, MAX_SAFE_STR_LEN);
    size_t n = safe_strlen(Y, MAX_SAFE_STR_LEN);
    size_t o = safe_strlen(Z, MAX_SAFE_STR_LEN);

    if (m == 0 || n == 0 || o == 0) {
        char* empty = (char*)malloc(1);
        if (empty != NULL) {
            empty[0] = '\0';
        }
        return empty;
    }

    if (m > SIZE_MAX - 1 || n > SIZE_MAX - 1 || o > SIZE_MAX - 1) {
        return NULL;
    }

    size_t dim1 = m + 1;
    size_t dim2 = n + 1;
    size_t dim3 = o + 1;

    if (dim1 > SIZE_MAX / dim2) {
        return NULL;
    }
    size_t partial = dim1 * dim2;
    if (partial > SIZE_MAX / dim3) {
        return NULL;
    }
    size_t table_size = partial * dim3;

    if (table_size > SIZE_MAX / sizeof(int)) {
        return NULL;
    }

    int* L = (int*)calloc(table_size, sizeof(int));
    if (L == NULL) {
        return NULL;
    }

    for (size_t i = 1; i <= m; i++) {
        for (size_t j = 1; j <= n; j++) {
            for (size_t k = 1; k <= o; k++) {
                size_t idx = i * dim2 * dim3 + j * dim3 + k;
                if (X[i-1] == Y[j-1] && Y[j-1] == Z[k-1]) {
                    size_t prev_idx = (i-1) * dim2 * dim3 + (j-1) * dim3 + (k-1);
                    L[idx] = L[prev_idx] + 1;
                } else {
                    size_t idx1 = (i-1) * dim2 * dim3 + j * dim3 + k;
                    size_t idx2 = i * dim2 * dim3 + (j-1) * dim3 + k;
                    size_t idx3 = i * dim2 * dim3 + j * dim3 + (k-1);
                    L[idx] = max3(L[idx1], L[idx2], L[idx3]);
                }
            }
        }
    }

    int lcs_length = L[m * dim2 * dim3 + n * dim3 + o];
    
    if (lcs_length < 0 || (size_t)lcs_length > SIZE_MAX - 1) {
        free(L);
        return NULL;
    }

    char* lcs = (char*)malloc((size_t)lcs_length + 1);
    if (lcs == NULL) {
        free(L);
        return NULL;
    }

    size_t i = m, j = n, k = o;
    int pos = lcs_length;
    lcs[pos] = '\0';

    while (i > 0 && j > 0 && k > 0 && pos > 0) {
        if (X[i-1] == Y[j-1] && Y[j-1] == Z[k-1]) {
            lcs[--pos] = X[i-1];
            i--;
            j--;
            k--;
        } else {
            size_t idx1 = (i-1) * dim2 * dim3 + j * dim3 + k;
            size_t idx2 = i * dim2 * dim3 + (j-1) * dim3 + k;
            size_t idx3 = i * dim2 * dim3 + j * dim3 + (k-1);
            
            if (L[idx1] >= L[idx2] && L[idx1] >= L[idx3]) {
                i--;
            } else if (L[idx2] >= L[idx1] && L[idx2] >= L[idx3]) {
                j--;
            } else {
                k--;
            }
        }
    }

    free(L);
    return lcs;
}

int main(void) {
    const char* str1 = "AGGT12";
    const char* str2 = "12TXAYB";
    const char* str3 = "12XBA";

    char* result = findLCS(str1, str2, str3);
    
    if (result == NULL) {
        fprintf(stderr, "Error: Memory allocation failed or invalid input\n");
        return EXIT_FAILURE;
    }

    printf("String 1: %s\n", str1);
    printf("String 2: %s\n", str2);
    printf("String 3: %s\n", str3);
    printf("Longest Common Subsequence: %s\n", result);
    
    size_t result_len = safe_strlen(result, MAX_SAFE_STR_LEN);
    printf("Length: %zu\n", result_len);

    free(result);
    return EXIT_SUCCESS;
}