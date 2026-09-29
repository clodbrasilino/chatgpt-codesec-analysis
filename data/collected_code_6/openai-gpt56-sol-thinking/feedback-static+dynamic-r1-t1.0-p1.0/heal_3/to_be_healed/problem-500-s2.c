#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected '  hello there have a rocky day', got hello there have a rocky day
  *  test case 2 failed: expected '  Part of the journey is end', got Part of the journey is end
  *  test case 1 failed: expected '  Hi there How are you', got Hi there How are you
  */

char *concatenate_elements(const char *const elements[], size_t count)
{
    size_t *lengths = NULL;
    size_t total_length = 0;
    size_t offset = 0;
    char *result;

    if (count > 0 && elements == NULL) {
        return NULL;
    }

    if (count > SIZE_MAX / sizeof(*lengths)) {
        return NULL;
    }

    if (count > 0) {
        lengths = malloc(count * sizeof(*lengths));
        if (lengths == NULL) {
            return NULL;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (elements[i] == NULL) {
            free(lengths);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        lengths[i] = strlen(elements[i]);

        if (lengths[i] > SIZE_MAX - total_length) {
            free(lengths);
            return NULL;
        }

        total_length += lengths[i];
    }

    if (count > 1) {
        size_t separator_count = count - 1;

        if (separator_count > SIZE_MAX - total_length) {
            free(lengths);
            return NULL;
        }

        total_length += separator_count;
    }

    if (total_length == SIZE_MAX) {
        free(lengths);
        return NULL;
    }

    result = malloc(total_length + 1);
    if (result == NULL) {
        free(lengths);
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        if (i > 0) {
            result[offset++] = ' ';
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + offset, elements[i], lengths[i]);
        offset += lengths[i];
    }

    result[offset] = '\0';
    free(lengths);

    return result;
}

int main(void)
{
    const char *elements[] = {
        "", "", "hello", "there", "have", "a", "rocky", "day"
    };
    const size_t count = sizeof(elements) / sizeof(elements[0]);
    char *result = concatenate_elements(elements, count);

    if (result == NULL) {
        fputs("Failed to concatenate elements.\n", stderr);
        return EXIT_FAILURE;
    }

    if (puts(result) == EOF) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}