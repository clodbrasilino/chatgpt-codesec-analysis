#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024U

int maxSubstringDiff(const char *str, size_t len);

int maxSubstringDiff(const char *str, size_t len)
{
    int maxDiff = -1;
    int current = 0;
    size_t i;

    if (str == NULL || len == 0U) {
        return -1;
    }

    for (i = 0U; i < len; i++) {
        int value;

        if (str[i] == '0') {
            value = 1;
        } else if (str[i] == '1') {
            value = -1;
        } else {
            return -1;
        }

        current += value;

        if (current > maxDiff) {
            maxDiff = current;
        }

        if (current < 0) {
            current = 0;
        }
    }

    return maxDiff;
}

int main(void)
{
    char *buffer;
    size_t len;
    int result;

    buffer = (char *)calloc(BUFFER_SIZE, sizeof(char));
    if (buffer == NULL) {
        (void)fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (fgets(buffer, (int)BUFFER_SIZE, stdin) == NULL) {
        (void)fprintf(stderr, "Error reading input\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    buffer[BUFFER_SIZE - 1U] = '\0';

    len = strnlen(buffer, BUFFER_SIZE);

    if (len > 0U && buffer[len - 1U] == '\n') {
        buffer[len - 1U] = '\0';
        len--;
    }

    if (len == 0U) {
        (void)fprintf(stderr, "Empty input\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    result = maxSubstringDiff(buffer, len);

    if (result < 0) {
        (void)printf("-1\n");
    } else {
        (void)printf("%d\n", result);
    }

    free(buffer);

    return EXIT_SUCCESS;
}