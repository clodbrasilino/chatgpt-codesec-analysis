#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* remove_k_length_words(char *str, int k) {
    char *result = NULL;
    char *token;
    char *temp = strdup(str);
    int len = 0;

    token = strtok(temp, " ");
    while (token != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (strlen(token) != k) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            len += strlen(token) + 1;
            /* Possible weaknesses found:
             *  Common realloc mistake: 'result' nulled but not freed upon failure [memleakOnRealloc]
             */
            result = realloc(result, len);
            if (result == NULL) {
                free(temp);
                return NULL;
            }
            /* Possible weaknesses found:
             * ASan: heap-buffer-overflow
             * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
             */
            strcat(result, token);
            /* Possible weaknesses found:
             * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). Risk is low because the source is a constant character. (risk 1, buffer)
             */
            strcat(result, " ");
        }
        token = strtok(NULL, " ");
    }

    if (len > 0) {
        result[len - 1] = '\0';
    } else {
        /* Possible weaknesses found:
         *  Common realloc mistake: 'result' nulled but not freed upon failure [memleakOnRealloc]
         */
        result = realloc(result, 1);
        if (result == NULL) {
            free(temp);
            return NULL;
        }
        *result = '\0';
    }

    free(temp);
    return result;
}

int main() {
    char str[] = "This is a test string with some words of length five";
    int k = 5;
    char *new_str = remove_k_length_words(str, k);

    if (new_str != NULL) {
        printf("%s\n", new_str);
        free(new_str);
    } else {
        printf("Memory allocation failed.\n");
    }

    return 0;
}