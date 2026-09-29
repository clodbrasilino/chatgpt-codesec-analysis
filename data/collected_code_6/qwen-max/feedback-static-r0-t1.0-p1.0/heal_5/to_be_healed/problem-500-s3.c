#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate_list(char **list, int count) {
    size_t total_len = 0;
    for (int i = 0; i < count; i++) {
        if (list[i] == NULL) return NULL;
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        total_len += strlen(list[i]) + 1;
    }
    total_len += count - 1;
    char *result = malloc(total_len);
    if (result == NULL) {
        return NULL;
    }
    *result = '\0';
    for (int i = 0; i < count; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t remaining_len = total_len - strlen(result) - 1;
        /* Possible weaknesses found:
         *  Checking if unsigned expression 'remaining_len' is less than zero. [unsignedLessThanZero]
         */
        if (remaining_len <= 0) return NULL;
        /* Possible weaknesses found:
         * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
         */
        strncat(result, list[i], remaining_len);
        if (i < count - 1) {
            /* Possible weaknesses found:
             * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. Risk is low because the source is a constant character. (risk 1, buffer)
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            strncat(result, " ", remaining_len - strlen(result) - 1);
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
        fprintf(stderr, "Memory allocation or string operation failed\n");
        return 1;
    }
    return 0;
}