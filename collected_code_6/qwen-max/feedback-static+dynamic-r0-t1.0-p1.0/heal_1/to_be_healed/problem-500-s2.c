#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected '  hello there have a rocky day', got <no output>
  *  test case 2 failed: expected '  Part of the journey is end', got <no output>
  *  test case 1 failed: expected '  Hi there How are you', got <no output>
  */

char* concatenate_elements(char **list, int length) {
    if (length <= 0) return NULL;

    char *result = malloc(1);
    if (result == NULL) return NULL;
    result[0] = '\0';

    for (int i = 0; i < length; ++i) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        const size_t len_result = strlen(result);
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        const size_t len_next = strlen(list[i]);
        const size_t new_len = len_result + len_next + 1;
        char *new_result = realloc(result, new_len);
        if (new_result == NULL) {
            free(result);
            return NULL;
        }
        result = new_result;
        /* Possible weaknesses found:
         * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
         */
        strcat(result + len_result, list[i]);
    }

    return result;
}

int main() {
    char *elements[] = {"Hello", " ", "World", "!"};
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