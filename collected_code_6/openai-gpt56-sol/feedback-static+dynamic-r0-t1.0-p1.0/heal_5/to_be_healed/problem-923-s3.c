#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int read_line(FILE *stream, char **line, size_t *length)
{
    size_t capacity = 128;
    size_t used = 0;
    char *buffer;
    int ch = EOF;

    if (stream == NULL || line == NULL || length == NULL) {
        return -1;
    }

    *line = NULL;
    *length = 0;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stream);

        if (ch == EOF || ch == '\n') {
            break;
        }

        if (used >= capacity - 1) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2;

            if (new_capacity <= used ||
                new_capacity > SIZE_MAX / sizeof(*buffer)) {
                free(buffer);
                return -1;
            }

            new_buffer = realloc(buffer, new_capacity * sizeof(*buffer));
            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[used++] = (char)(unsigned char)ch;
    }

    if (ch == EOF) {
        if (ferror(stream)) {
            free(buffer);
            return -1;
        }

        if (used == 0) {
            free(buffer);
            return 0;
        }
    }

    if (used > 0 && buffer[used - 1] == '\r') {
        --used;
    }

    buffer[used] = '\0';
    *line = buffer;
    *length = used;

    return 1;
}

static int shortest_common_supersequence_length(const char *str1,
                                                 size_t len1,
                                                 const char *str2,
                                                 size_t len2,
                                                 size_t *result)
{
    size_t *dp;
    size_t i;
    size_t j;

    if (str1 == NULL || str2 == NULL || result == NULL) {
        return -1;
    }

    if (len1 > SIZE_MAX - len2) {
        return -1;
    }

    if (len2 == SIZE_MAX ||
        len2 + 1 > SIZE_MAX / sizeof(*dp)) {
        return -1;
    }

    dp = malloc((len2 + 1) * sizeof(*dp));
    if (dp == NULL) {
        return -1;
    }

    for (j = 0; j <= len2; ++j) {
        dp[j] = j;
    }

    for (i = 1; i <= len1; ++i) {
        size_t diagonal = dp[0];

        dp[0] = i;

        for (j = 1; j <= len2; ++j) {
            size_t above = dp[j];

            if ((unsigned char)str1[i - 1] ==
                (unsigned char)str2[j - 1]) {
                dp[j] = diagonal + 1;
            } else {
                size_t minimum = dp[j - 1] < above ? dp[j - 1] : above;
                dp[j] = minimum + 1;
            }

            diagonal = above;
        }
    }

    *result = dp[len2];
    free(dp);
    return 0;
}

int main(void)
{
    char *str1 = NULL;
    char *str2 = NULL;
    size_t len1 = 0;
    size_t len2 = 0;
    size_t result;
    int status;

    status = read_line(stdin, &str1, &len1);
    if (status != 1) {
        free(str1);
        return EXIT_FAILURE;
    }

    status = read_line(stdin, &str2, &len2);
    if (status != 1) {
        free(str1);
        free(str2);
        return EXIT_FAILURE;
    }

    status = shortest_common_supersequence_length(
        str1, len1, str2, len2, &result);

    free(str1);
    free(str2);

    if (status != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}