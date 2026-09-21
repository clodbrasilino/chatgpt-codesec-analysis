#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* remove_k_length_words(const char *str, int k) {
    char *result = NULL;
    size_t result_len = 0;
    char *token = strtok((char *)str, " ");
    while (token != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (strlen(token) != k) {
            if (result == NULL) {
                result = strdup(token);
                /* Possible weaknesses found:
                 * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
                 */
                if (result) result_len = strlen(result);
            } else {
                /* Possible weaknesses found:
                 * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
                 */
                size_t new_len = result_len + 1 + strlen(token) + 1;
                char *new_result = realloc(result, new_len);
                if (new_result) {
                    result = new_result;
                    /* Possible weaknesses found:
                     * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). Risk is low because the source is a constant character. (risk 1, buffer)
                     */
                    strcat(result, " ");
                    /* Possible weaknesses found:
                     * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
                     */
                    strcat(result, token);
                    result_len = new_len - 1;
                } else {
                    free(result);
                    return NULL;
                }
            }
        }
        token = strtok(NULL, " ");
    }
    return result ? result : strdup("");
}

int main() {
    const char str[] = "This is a test string with some words of length five";
    int k = 5;
    char *new_str = remove_k_length_words(str, k);
    printf("%s\n", new_str);
    free(new_str);
    return 0;
}