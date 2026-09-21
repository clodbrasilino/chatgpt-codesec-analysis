#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *extract_rear_elements(const char *const strings[], size_t count)
{
    char *result;
    size_t i;

    if (strings == NULL && count != 0U) {
        return NULL;
    }

    if (count == SIZE_MAX) {
        return NULL;
    }

    result = malloc(count + 1U);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0U; i < count; ++i) {
        size_t length;

        if (strings[i] == NULL) {
            free(result);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        length = strlen(strings[i]);
        if (length == 0U) {
            free(result);
            return NULL;
        }

        result[i] = strings[i][length - 1U];
    }

    result[count] = '\0';
    return result;
}

int main(void)
{
    const char *strings[] = {"apple", "banana", "cherry", "date"};
    const size_t count = sizeof(strings) / sizeof(strings[0]);
    char *rear_elements = extract_rear_elements(strings, count);

    if (rear_elements == NULL) {
        fputs("Failed to extract rear elements.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%s\n", rear_elements);
    free(rear_elements);

    return EXIT_SUCCESS;
}