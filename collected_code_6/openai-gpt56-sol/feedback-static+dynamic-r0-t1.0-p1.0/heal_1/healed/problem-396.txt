#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int starts_and_ends_with_same_character(const char *string, int *result)
{
    size_t length;

    if (string == NULL || result == NULL) {
        return -1;
    }

    length = strlen(string);
    *result = length > 0 && string[0] == string[length - 1];

    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    int result;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        return 1;
    }

    if (length > 0 && input[length - 1] == '\n') {
        input[--length] = '\0';
    }

    if (length > 0 && input[length - 1] == '\r') {
        input[--length] = '\0';
    }

    if (starts_and_ends_with_same_character(input, &result) != 0) {
        free(input);
        return 1;
    }

    printf("%s\n", result ? "Yes" : "No");

    free(input);
    return 0;
}