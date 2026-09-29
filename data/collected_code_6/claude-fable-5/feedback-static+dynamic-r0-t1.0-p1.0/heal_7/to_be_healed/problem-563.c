#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *extract_quoted(const char *input)
{
    const char *start;
    const char *end;
    size_t length;
    char *result;

    if (input == NULL) {
        return NULL;
    }

    start = strchr(input, '"');
    if (start == NULL) {
        return NULL;
    }

    start++;
    end = strchr(start, '"');
    if (end == NULL) {
        return NULL;
    }

    length = (size_t)(end - start);

    if (length >= SIZE_MAX - 1U) {
        return NULL;
    }

    result = malloc(length + 1U);
    if (result == NULL) {
        return NULL;
    }

    if (length > 0U) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result, start, length);
    }
    result[length] = '\0';

    return result;
}

int main(void)
{
    const char *test = "The value is \"hello world\" in this string";
    char *extracted;

    extracted = extract_quoted(test);
    if (extracted == NULL) {
        if (fprintf(stderr, "No quoted value found or allocation failed\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Extracted: %s\n", extracted) < 0) {
        free(extracted);
        return EXIT_FAILURE;
    }

    free(extracted);
    return EXIT_SUCCESS;
}