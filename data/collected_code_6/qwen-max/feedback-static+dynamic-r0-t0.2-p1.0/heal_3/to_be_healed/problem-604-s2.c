#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverseWords(char *str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    char *temp = (char *)malloc(len + 1);
    if (temp == NULL) return;
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(temp, str, len + 1);

    char *word = strtok(temp, " ");
    if (word == NULL) {
        free(temp);
        return;
    }

    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        free(temp);
        return;
    }
    result[0] = '\0';

    while (word != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t result_len = strlen(result);
        if (result_len > 0) {
            /* Possible weaknesses found:
             * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. Risk is low because the source is a constant character. (risk 1, buffer)
             */
            strncat(result, " ", len - result_len);
        }
        /* Possible weaknesses found:
         * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
         */
        strncat(result, word, len - result_len - 1);
        word = strtok(NULL, " ");
    }

    for (size_t i = 0; i < len; i++) {
        for (size_t j = i + 1; j < len; j++) {
            if (result[j] == ' ') {
                int start = i, end = j - 1;
                while (start < end) {
                    char t = result[start];
                    result[start] = result[end];
                    result[end] = t;
                    start++;
                    end--;
                }
                i = j;
                break;
            }
        }
    }

    /* Possible weaknesses found:
     *  use of undeclared identifier 'i'
     *  'i' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     */
    int start = i, end = len - 1;
    while (start < end) {
        char t = result[start];
        result[start] = result[end];
        result[end] = t;
        start++;
        end--;
    }

    snprintf(str, len + 1, "%s", result);
    free(temp);
    free(result);
}

int main() {
    char str[] = "Hello World This is C";
    reverseWords(str);
    printf("%s\n", str);
    return 0;
}