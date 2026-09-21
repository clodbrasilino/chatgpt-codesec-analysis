#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
         * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
         */
        strcat(result, array[i]);
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