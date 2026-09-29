#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concat_elements(const char *array[], size_t count) {
    if (count == 0) return NULL;

    size_t total_length = 0;
    for (size_t i = 0; i < count; ++i) {
        if (array[i] != NULL) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            total_length += strlen(array[i]);
        }
    }

    total_length += count - 1;
    
    char *result = (char *)malloc(total_length + 1);
    if (result == NULL) return NULL;

    result[0] = '\0';
    for (size_t i = 0; i < count; ++i) {
        if (i > 0 && array[i] != NULL) {
            /* Possible weaknesses found:
             * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. Risk is low because the source is a constant character. (risk 1, buffer)
             */
            strncat(result, " ", 1);
        }
        if (array[i] != NULL) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = strlen(array[i]);
            if (len > 0) {
                /* Possible weaknesses found:
                 * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
                 */
                strncat(result, array[i], len);
            }
        }
    }

    return result;
}

int main() {
    const char *elements[] = {"Hello", "World", "!"};
    size_t count = sizeof(elements) / sizeof(elements[0]);

    char *combined = concat_elements(elements, count);
    if (combined != NULL) {
        printf("%s\n", combined);
        free(combined);
    }

    return 0;
}