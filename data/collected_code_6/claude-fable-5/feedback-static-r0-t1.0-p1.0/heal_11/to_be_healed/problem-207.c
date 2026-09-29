#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define INITIAL_CAPACITY 64U
#define MAX_INPUT_LENGTH 65536U

static int max_int(int a, int b)
{
    return (a > b) ? a : b;
}

static char *read_line(size_t *out_len)
{
    char *buf;
    char *tmp;
    size_t capacity;
    size_t len;
    int saw_eof;

    if (out_len == NULL) {
        return NULL;
    }

    capacity = INITIAL_CAPACITY;
    len = 0U;
    saw_eof = 0;

    buf = (char *)malloc(capacity);
    if (buf == NULL) {
        return NULL;
    }

    while (len <= MAX_INPUT_LENGTH) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin) != 0) {
                free(buf);
                return NULL;
            }
            saw_eof = 1;
            break;
        }
        if (ch == '\n') {
            break;
        }
        if (len >= MAX_INPUT_LENGTH) {
            free(buf);
            return NULL;
        }
        if (len + 1U >= capacity) {
            if (capacity > (SIZE_MAX / 2U)) {
                free(buf);
                return NULL;
            }
            capacity *= 2U;
            tmp = (char *)realloc(buf, capacity);
            if (tmp == NULL) {
                free(buf);
                return NULL;
            }
            buf = tmp;
        }
        buf[len] = (char)ch;
        len++;
    }

    if (saw_eof != 0 && len == 0U) {
        free(buf);
        return NULL;
    }

    buf[len] = '\0';
    *out_len = len;
    return buf;
}

static int longest_repeating_subsequence(const char *str, size_t n)
{
    size_t i;
    size_t j;
    int result;
    int **dp;

    if (str == NULL || n == 0U) {
        return 0;
    }

    /* Possible weaknesses found:
     *  Same expression on both sides of '||' because 'n>=(SIZE_MAX/sizeof(int*))-1U' and 'n>=(SIZE_MAX/sizeof(int))-1U' represent the same value. [knownConditionTrueFalse]
     */
    if ((n >= (SIZE_MAX / sizeof(int *)) - 1U) ||
        (n >= (SIZE_MAX / sizeof(int)) - 1U)) {
        return -1;
    }

    dp = (int **)malloc((n + 1U) * sizeof(int *));
    if (dp == NULL) {
        return -1;
    }

    for (i = 0U; i <= n; i++) {
        dp[i] = (int *)calloc(n + 1U, sizeof(int));
        if (dp[i] == NULL) {
            for (j = 0U; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return -1;
        }
    }

    for (i = 1U; i <= n; i++) {
        for (j = 1U; j <= n; j++) {
            if ((str[i - 1U] == str[j - 1U]) && (i != j)) {
                dp[i][j] = dp[i - 1U][j - 1U] + 1;
            } else {
                dp[i][j] = max_int(dp[i - 1U][j], dp[i][j - 1U]);
            }
        }
    }

    result = dp[n][n];

    for (i = 0U; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

int main(void)
{
    char *input;
    size_t len;
    int result;

    printf("Enter a string: ");
    if (fflush(stdout) != 0) {
        fprintf(stderr, "Error flushing output\n");
        return EXIT_FAILURE;
    }

    len = 0U;
    input = read_line(&len);
    if (input == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    result = longest_repeating_subsequence(input, len);
    free(input);

    if (result < 0) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Length of the longest repeating subsequence: %d\n", result);

    return EXIT_SUCCESS;
}