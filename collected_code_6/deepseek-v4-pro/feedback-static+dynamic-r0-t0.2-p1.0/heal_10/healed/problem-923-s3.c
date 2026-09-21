#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

int shortest_supersequence_length(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return -1;
    }

    size_t len1 = strnlen(str1, (size_t)INT_MAX + 1UL);
    size_t len2 = strnlen(str2, (size_t)INT_MAX + 1UL);

    if (len1 > (size_t)INT_MAX || len2 > (size_t)INT_MAX) {
        return -1;
    }

    int n1 = (int)len1;
    int n2 = (int)len2;

    int **dp = (int **)calloc((size_t)(n1 + 1), sizeof(int *));
    if (dp == NULL) {
        return -1;
    }

    int i;
    for (i = 0; i <= n1; i++) {
        dp[i] = (int *)calloc((size_t)(n2 + 1), sizeof(int));
        if (dp[i] == NULL) {
            int k;
            for (k = 0; k < i; k++) {
                free(dp[k]);
            }
            free(dp);
            return -1;
        }
    }

    for (i = 0; i <= n1; i++) {
        int j;
        for (j = 0; j <= n2; j++) {
            if (i == 0) {
                dp[i][j] = j;
            } else if (j == 0) {
                dp[i][j] = i;
            } else if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = (dp[i - 1][j] < dp[i][j - 1] ? dp[i - 1][j] : dp[i][j - 1]) + 1;
            }
        }
    }

    int result = dp[n1][n2];

    for (i = 0; i <= n1; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

static void clear_input_buffer(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {}
}

static char *read_string_safely(const char *prompt, size_t buffer_size) {
    char *buffer = (char *)calloc(buffer_size, sizeof(char));
    if (buffer == NULL) {
        return NULL;
    }

    printf("%s", prompt);
    if (fgets(buffer, (int)buffer_size, stdin) == NULL) {
        free(buffer);
        return NULL;
    }

    size_t len = strnlen(buffer, buffer_size);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else {
        int found_newline = 0;
        size_t i;
        for (i = 0; i < buffer_size; i++) {
            if (buffer[i] == '\n') {
                buffer[i] = '\0';
                found_newline = 1;
                break;
            }
            if (buffer[i] == '\0') {
                found_newline = 1;
                break;
            }
        }
        if (!found_newline) {
            clear_input_buffer();
        }
    }

    return buffer;
}

int main(void) {
    size_t buffer_size = 256;

    char *str1 = read_string_safely("Enter first string: ", buffer_size);
    if (str1 == NULL) {
        return 1;
    }

    char *str2 = read_string_safely("Enter second string: ", buffer_size);
    if (str2 == NULL) {
        free(str1);
        return 1;
    }

    size_t len1 = strnlen(str1, buffer_size);
    size_t len2 = strnlen(str2, buffer_size);

    if (len1 >= buffer_size || len2 >= buffer_size) {
        free(str1);
        free(str2);
        return 1;
    }

    int length = shortest_supersequence_length(str1, str2);
    if (length == -1) {
        printf("Error computing shortest common supersequence.\n");
        free(str1);
        free(str2);
        return 1;
    }

    printf("Length of shortest common supersequence: %d\n", length);

    free(str1);
    free(str2);

    return 0;
}