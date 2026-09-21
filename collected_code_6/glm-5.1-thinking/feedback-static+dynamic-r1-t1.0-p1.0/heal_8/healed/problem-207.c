#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int longestRepeatingSubseq(const char *str, int n) {
    if (n <= 0) {
        return 0;
    }
    size_t size = (size_t)n + 1;
    if (size > SIZE_MAX / size || size > (SIZE_MAX / sizeof(int)) / size) {
        return -1;
    }
    int *dp = (int *)malloc(size * size * sizeof(int));
    if (dp == NULL) {
        return -1;
    }
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                dp[i * size + j] = 0;
            } else if (str[i - 1] == str[j - 1] && i != j) {
                dp[i * size + j] = 1 + dp[(i - 1) * size + (j - 1)];
            } else {
                dp[i * size + j] = max(dp[(i - 1) * size + j], dp[i * size + (j - 1)]);
            }
        }
    }
    int result = dp[n * size + n];
    free(dp);
    return result;
}

int main(void) {
    size_t capacity = 128;
    char *str = malloc(capacity);
    if (str == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    size_t len = 0;
    size_t buf_size = 1024;
    char *buf = malloc(buf_size);
    if (buf == NULL) {
        free(str);
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    while (fgets(buf, buf_size, stdin)) {
        size_t chunk_len = strlen(buf);
        const char *nl = strchr(buf, '\n');
        if (nl) {
            chunk_len = (size_t)(nl - buf);
        }
        if (len > SIZE_MAX - chunk_len - 1) {
            free(buf);
            free(str);
            fprintf(stderr, "Input too long\n");
            return 1;
        }
        while (len + chunk_len + 1 >= capacity) {
            if (capacity > SIZE_MAX / 2) {
                free(buf);
                free(str);
                fprintf(stderr, "Memory allocation failed\n");
                return 1;
            }
            capacity *= 2;
            char *temp = realloc(str, capacity);
            if (temp == NULL) {
                free(buf);
                free(str);
                fprintf(stderr, "Memory allocation failed\n");
                return 1;
            }
            str = temp;
        }
        snprintf(str + len, capacity - len, "%.*s", (int)chunk_len, buf);
        len += chunk_len;
        if (nl) {
            break;
        }
    }
    free(buf);
    str[len] = '\0';
    
    if (len >= INT_MAX) {
        fprintf(stderr, "Input too long\n");
        free(str);
        return 1;
    }
    int n = (int)len;
    int result = longestRepeatingSubseq(str, n);
    if (result >= 0) {
        printf("%d\n", result);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
        free(str);
        return 1;
    }
    free(str);
    return 0;
}