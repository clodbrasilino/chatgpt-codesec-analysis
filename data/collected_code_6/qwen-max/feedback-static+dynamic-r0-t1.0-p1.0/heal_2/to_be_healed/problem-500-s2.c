#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected '  Hi there How are you', got HithereHowareyou
  *  test case 0 failed: expected '  hello there have a rocky day', got hellotherehavearockyday
  *  test case 2 failed: expected '  Part of the journey is end', got Partofthejourneyisend
  */

char* concatenate_elements(char **list, int length) {
    if (length <= 0) return NULL;

    size_t total_length = 0;
    for (int i = 0; i < length; ++i) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        total_length += strlen(list[i]) + 1;
    }

    char *result = malloc(total_length * sizeof(char));
    if (result == NULL) return NULL;
    result[0] = '\0';

    for (int i = 0; i < length; ++i) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
         */
        strncat(result, list[i], total_length - strlen(result) - 1);
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