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
        if (strlen(token) != k) {
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
             */
            strcat(result, token);
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