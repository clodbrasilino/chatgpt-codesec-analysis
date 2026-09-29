#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static int ends_with_alphanumeric(const char *string, bool *result)
{
    const unsigned char *cursor;

    if (string == NULL || result == NULL) {
        return -1;
    }

    cursor = (const unsigned char *)string;
    while (*cursor != '\0') {
        ++cursor;
    }

    if (cursor == (const unsigned char *)string) {
        *result = false;
        return 0;
    }

    *result = isalnum(cursor[-1]) != 0;
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    bool result;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        return 1;
    }

    while (length > 0 &&
           (input[length - 1] == '\n' || input[length - 1] == '\r')) {
        input[--length] = '\0';
    }

    if (ends_with_alphanumeric(input, &result) != 0) {
        free(input);
        return 1;
    }

    puts(result ? "true" : "false");
    free(input);
    return 0;
}