#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

static int maximum_difference(const char *str, int *result)
{
    if (str == NULL || result == NULL || *str == '\0') {
        return 0;
    }

    int current = 0;
    int maximum = INT_MIN;

    for (const char *p = str; *p != '\0'; ++p) {
        int value;

        if (*p == '0') {
            value = 1;
        } else if (*p == '1') {
            value = -1;
        } else {
            return 0;
        }

        if (current < 0) {
            current = value;
        } else {
            current += value;
        }

        if (current > maximum) {
            maximum = current;
        }
    }

    *result = maximum;
    return 1;
}

int main(void)
{
    char input[1000001];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    size_t length = strcspn(input, "\r\n");

    if (input[length] == '\0' && length == sizeof input - 1) {
        int ch = getchar();
        if (ch != '\n' && ch != '\r' && ch != EOF) {
            return EXIT_FAILURE;
        }
    }

    input[length] = '\0';

    int result;
    if (!maximum_difference(input, &result)) {
        return EXIT_FAILURE;
    }

    if (printf("%d\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}