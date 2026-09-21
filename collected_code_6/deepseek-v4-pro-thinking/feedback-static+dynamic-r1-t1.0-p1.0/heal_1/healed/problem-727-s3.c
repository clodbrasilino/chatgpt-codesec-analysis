#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *remove_non_alphanumeric(const char *input)
{
    if (input == NULL) return NULL;

    size_t out_len = 0;
    for (const char *p = input; *p != '\0'; p++) {
        if (isalnum((unsigned char)*p)) {
            out_len++;
        }
    }

    char *result = malloc(out_len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t i = 0;
    for (const char *p = input; *p != '\0'; p++) {
        if (isalnum((unsigned char)*p)) {
            result[i++] = *p;
        }
    }
    result[i] = '\0';
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