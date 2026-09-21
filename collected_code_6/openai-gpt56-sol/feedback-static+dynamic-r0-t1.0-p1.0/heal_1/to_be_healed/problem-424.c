#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *extract_rear_elements(const char *const strings[], size_t count)
{
    char *result = calloc(count + 1, sizeof(*result));

    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        if (strings[i] == NULL) {
            free(result);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t length = strlen(strings[i]);

        if (length == 0) {
            free(result);
            return NULL;
        }

        result[i] = strings[i][length - 1];
    }

    return result;
}

int main(void)
{
    const char *strings[] = {"apple", "banana", "cherry", "date"};
    size_t count = sizeof(strings) / sizeof(strings[0]);
    char *rear_elements = extract_rear_elements(strings, count);

    if (rear_elements == NULL) {
        fputs("Failed to extract rear elements.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        printf("%c\n", rear_elements[i]);
    }

    free(rear_elements);
    return EXIT_SUCCESS;
}