#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stddef.h>

#define MAX_STRING_LENGTH 1048576

char *remove_non_alphanumeric(const char *input)
{
    size_t len = 0;
    size_t i;
    size_t alnum_count;
    char *result;
    size_t out;

    if (input == NULL)
        return NULL;

    while (len < MAX_STRING_LENGTH && input[len] != '\0')
        len++;

    if (len == MAX_STRING_LENGTH)
        return NULL;

    alnum_count = 0;
    for (i = 0; i < len; i++) {
        if (isalnum((unsigned char)input[i]))
            alnum_count++;
    }

    result = malloc(alnum_count + 1);
    if (result == NULL)
        return NULL;

    out = 0;
    for (i = 0; i < len; i++) {
        if (isalnum((unsigned char)input[i])) {
            result[out++] = input[i];
        }
    }
    result[out] = '\0';

    return result;
}

int main(void)
{
    char *cleaned = remove_non_alphanumeric("Hello, World! 123");
    if (cleaned != NULL) {
        puts(cleaned);
        free(cleaned);
    }
    return 0;
}