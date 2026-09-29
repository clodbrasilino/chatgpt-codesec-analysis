#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate_list(char **list, int count) {
    size_t total_len = 0;
    for (int i = 0; i < count; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        total_len += strlen(list[i]) + 1;
    }
    char *result = malloc(total_len);
    if (result == NULL) {
        return NULL;
    }
    result[0] = '\0';
    for (int i = 0; i < count; i++) {
        /* Possible weaknesses found:
         * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
         */
        strcat(result, list[i]);
        if (i < count - 1) {
            /* Possible weaknesses found:
             * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). Risk is low because the source is a constant character. (risk 1, buffer)
             */
            strcat(result, " ");
        }
    }
    return result;
}

int main() {
    char *words[] = {"Hello", "world", "this", "is", "C"};
    int count = sizeof(words) / sizeof(words[0]);
    char *concatenated = concatenate_list(words, count);
    if (concatenated != NULL) {
        printf("%s\n", concatenated);
        free(concatenated);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    return 0;
}