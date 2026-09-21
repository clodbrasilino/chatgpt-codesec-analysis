#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *squeeze_char(const char *input, char target)
{
    size_t len;
    size_t i;
    size_t j;
    char *result;

    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input);
    result = malloc(len + 1U);
    if (result == NULL) {
        return NULL;
    }

    j = 0U;
    for (i = 0U; i < len; i++) {
        if ((input[i] == target) && (j > 0U) && (result[j - 1U] == target)) {
            continue;
        }
        result[j] = input[i];
        j++;
    }
    result[j] = '\0';

    return result;
}

int main(void)
{
    const char *text = "aaabbbcccaaa   hello   worldaaa";
    char *squeezed;

    squeezed = squeeze_char(text, 'a');
    if (squeezed == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    printf("Original: %s\n", text);
    printf("Squeezed: %s\n", squeezed);
    free(squeezed);
    squeezed = NULL;

    squeezed = squeeze_char(text, ' ');
    if (squeezed == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    printf("Squeezed spaces: %s\n", squeezed);
    free(squeezed);
    squeezed = NULL;

    return EXIT_SUCCESS;
}