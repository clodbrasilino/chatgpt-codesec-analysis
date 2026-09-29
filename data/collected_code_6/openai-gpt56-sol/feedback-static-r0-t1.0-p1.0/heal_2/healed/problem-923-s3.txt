#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int read_line(FILE *stream, char **line, size_t *length)
{
    size_t capacity = 128;
    size_t used = 0;
    char *buffer;

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
        int ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream) || used == 0) {
                free(buffer);
                return -1;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (ch == '\r') {
            int next = fgetc(stream);

            if (next == EOF) {
                if (ferror(stream)) {
                    free(buffer);
                    return -1;
                }
            } else if (next != '\n' && ungetc(next, stream) == EOF) {
                free(buffer);
                return -1;
            }

            break;
        }

        if (used > SIZE_MAX - 2) {
            free(buffer);
            return -1;
        }

        if (used + 1 >= capacity) {
            size_t required = used + 2;
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity < required) {
                new_capacity = required;
            }

            if (new_capacity <= capacity) {
                free(buffer);
                return -1;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[used++] = (char)ch;
    }

    buffer[used] = '\0';
    *line = buffer;
    *length = used;
    return 0;
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

    if (len1 < len2) {
        const char *temporary_string = str1;
        size_t temporary_length = len1;

        str1 = str2;
        len1 = len2;
        str2 = temporary_string;
        len2 = temporary_length;
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

            if (str1[i - 1] == str2[j - 1]) {
                dp[j] = diagonal + 1;
            } else {
                size_t left = dp[j - 1];
                dp[j] = (left < above ? left : above) + 1;
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
    size_t result = 0;
    int status = EXIT_FAILURE;

    if (read_line(stdin, &str1, &len1) != 0) {
        goto cleanup;
    }

    if (read_line(stdin, &str2, &len2) != 0) {
        goto cleanup;
    }

    if (shortest_common_supersequence_length(
            str1, len1, str2, len2, &result) != 0) {
        goto cleanup;
    }

    if (printf("%zu\n", result) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(str2);
    free(str1);
    return status;
}