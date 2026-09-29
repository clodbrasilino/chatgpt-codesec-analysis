#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected '  Hi there How are you', got HithereHowareyou
  *  test case 0 failed: expected '  hello there have a rocky day', got hellotherehavearockyday
  *  test case 2 failed: expected '  Part of the journey is end', got Partofthejourneyisend
  */

char *concat_elements(const char *array[], size_t count) {
    if (count == 0) return NULL;
    
    size_t total_length = 0;
    for (size_t i = 0; i < count; ++i) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        total_length += strlen(array[i]);
    }
    
    char *result = (char *)malloc(total_length + 1);
    if (result == NULL) return NULL;
    
    result[0] = '\0';
    for (size_t i = 0; i < count; ++i) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
         */
        strncat(result, array[i], strlen(array[i]) + 1);
    }
    
    return result;
}

int main() {
    const char *elements[] = {"Hello", " ", "World", "!"};
    size_t count = sizeof(elements) / sizeof(elements[0]);
    
    char *combined = concat_elements(elements, count);
    if (combined != NULL) {
        printf("%s\n", combined);
        free(combined);
    }
    
    return 0;
}