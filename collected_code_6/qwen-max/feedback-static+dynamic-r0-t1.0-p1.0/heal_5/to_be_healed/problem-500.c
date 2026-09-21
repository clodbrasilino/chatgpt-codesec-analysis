#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected '  hello there have a rocky day', got <no output>
  *  test case 2 failed: expected '  Part of the journey is end', got <no output>
  *  test case 1 failed: expected '  Hi there How are you', got <no output>
  */

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
    for (size_t i = 0, offset = 0; i < count; ++i) {
        if (i > 0 && array[i] != NULL) {
            result[offset++] = ' ';
        }
        if (array[i] != NULL) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = strlen(array[i]);
            if (len > 0) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + offset, array[i], len);
                offset += len;
            }
        }
    }
    result[total_length] = '\0';

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