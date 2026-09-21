#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate_elements(char **list, int length) {
    if (length <= 0) return NULL;

    size_t total_length = 0;
    for (int i = 0; i < length; ++i) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        total_length += strlen(list[i]);
    }
    total_length += length - 1;

    char *result = malloc(total_length + 1);
    if (result == NULL) return NULL;
    result[0] = '\0';

    for (int i = 0; i < length; ++i) {
        /* Possible weaknesses found:
         * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
         */
        strcat(result, list[i]);
        if (i < length - 1) {
            /* Possible weaknesses found:
             * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). Risk is low because the source is a constant character. (risk 1, buffer)
             */
            strcat(result, " ");
        }
    }

    return result;
}

int main() {
    char *elements[] = {"Hello", "", "World", ""};
    int num_elements = 4;

    char *concatenated = concatenate_elements(elements, num_elements);
    if (concatenated != NULL) {
        printf("%s\n", concatenated);
        free(concatenated);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }

    return 0;
}