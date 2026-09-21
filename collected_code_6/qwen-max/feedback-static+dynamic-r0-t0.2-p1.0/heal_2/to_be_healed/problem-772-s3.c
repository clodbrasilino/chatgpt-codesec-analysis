#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* remove_k_length_words(const char *str, int k) {
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
            size_t token_len = strlen(token) + 1;
            /* Possible weaknesses found:
             *  Common realloc mistake: 'result' nulled but not freed upon failure [memleakOnRealloc]
             */
            result = realloc(result, len + token_len + 1);
            if (result == NULL) {
                free(temp);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + len, token, token_len);
            len += token_len - 1; // Exclude the null terminator
            result[len] = ' ';
            len++;
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
    const char str[] = "This is a test string with some words of length five";
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