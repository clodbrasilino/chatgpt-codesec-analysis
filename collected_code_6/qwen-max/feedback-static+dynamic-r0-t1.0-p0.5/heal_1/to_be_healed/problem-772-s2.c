#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* remove_k_length_words(char *str, int k) {
    char *result = NULL;
    char *token = strtok(str, " ");
    while (token != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (strlen(token) != k) {
            if (result == NULL) {
                result = strdup(token);
            } else {
                /* Possible weaknesses found:
                 * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
                 */
                size_t len1 = strlen(result);
                /* Possible weaknesses found:
                 * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
                 *  Common realloc mistake: 'result' nulled but not freed upon failure [memleakOnRealloc]
                 */
                result = realloc(result, len1 + 1 + strlen(token) + 1);
                if (result) {
                    /* Possible weaknesses found:
                     * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). Risk is low because the source is a constant character. (risk 1, buffer)
                     */
                    strcat(result, " ");
                    /* Possible weaknesses found:
                     * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
                     */
                    strcat(result, token);
                }
            }
        }
        token = strtok(NULL, " ");
    }
    return result;
}

int main() {
    char str[] = "This is a test string with some words of length four";
    int k = 4;
    char *new_str = remove_k_length_words(str, k);
    if (new_str) {
        printf("%s\n", new_str);
        free(new_str);
    }
    return 0;
}