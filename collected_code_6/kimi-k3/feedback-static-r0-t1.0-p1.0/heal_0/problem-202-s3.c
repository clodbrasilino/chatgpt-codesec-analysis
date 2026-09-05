#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_even_chars(const char *str)
{
    size_t len;
    size_t i;
    size_t j;
    char *result;

    if (str == NULL) {
        return NULL;
    }

    len = strlen(str);
    result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    j = 0;
    for (i = 0; i < len; i++) {
        if (i % 2 == 0) {
            result[j] = str[i];
            j++;
        }
    }
    result[j] = '\0';

    return result;
}

int main(void)
{
    char *result;

    result = remove_even_chars("Hello, World!");
    if (result == NULL) {
        return EXIT_FAILURE;
    }

    printf("%s\n", result);
    free(result);

    return EXIT_SUCCESS;
}