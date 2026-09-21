#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char** split_at_uppercase(const char *str, int *count) {
    if (str == NULL || count == NULL) return NULL;
    *count = 0;
    const char *start = str;
    while (*str != '\0') {
        if (isupper((unsigned char)*str)) {
            size_t length = str - start;
            /* Possible weaknesses found:
             *  incompatible integer to pointer conversion passing 'int' to parameter of type 'void *' [-Wint-conversion]
             *  passing argument 1 of 'realloc' makes pointer from integer without a cast [-Wint-conversion]
             */
            char **result = (char **)realloc(*count ? *count - 1 : 0, (*count + 2) * sizeof(char *));
            if (result == NULL) {
                /* Possible weaknesses found:
                 *  incompatible integer to pointer conversion passing 'int' to parameter of type 'void *' [-Wint-conversion]
                 *  passing argument 1 of 'free' makes pointer from integer without a cast [-Wint-conversion]
                 */
                free(*count ? *count - 1 : 0);
                return NULL;
            }
            result[*count] = (char *)malloc(length * sizeof(char));
            if (result[*count] == NULL) {
                for (int i = 0; i < *count; i++) free(result[i]);
                free(result);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result[*count], start, length);
            result[*count][length] = '\0';
            start = str;
            (*count)++;
        }
        str++;
    }

    if (start != str) {
        size_t length = str - start;
        /* Possible weaknesses found:
         *  incompatible integer to pointer conversion passing 'int' to parameter of type 'void *' [-Wint-conversion]
         *  passing argument 1 of 'realloc' makes pointer from integer without a cast [-Wint-conversion]
         */
        char **result = (char **)realloc(*count ? *count - 1 : 0, (*count + 2) * sizeof(char *));
        if (result == NULL) {
            /* Possible weaknesses found:
             *  incompatible integer to pointer conversion passing 'int' to parameter of type 'void *' [-Wint-conversion]
             *  passing argument 1 of 'free' makes pointer from integer without a cast [-Wint-conversion]
             */
            free(*count ? *count - 1 : 0);
            return NULL;
        }
        result[*count] = (char *)malloc(length * sizeof(char));
        if (result[*count] == NULL) {
            for (int i = 0; i < *count; i++) free(result[i]);
            free(result);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result[*count], start, length);
        result[*count][length] = '\0';
        (*count)++;
    }

    /* Possible weaknesses found:
     *  incompatible integer to pointer conversion passing 'int' to parameter of type 'void *' [-Wint-conversion]
     *  passing argument 1 of 'realloc' makes pointer from integer without a cast [-Wint-conversion]
     */
    char **final_result = (char **)realloc(*count ? *count - 1 : 0, (*count + 1) * sizeof(char *));
    if (final_result == NULL) {
        for (int i = 0; i < *count; i++) free(final_result[i]);
        free(final_result);
        return NULL;
    }
    /* Possible weaknesses found:
     *  expected 'void *' but argument is of type 'int'
     *  passing argument to parameter here
     */
    final_result[*count] = NULL;
    /* Possible weaknesses found:
     *  expected 'void *' but argument is of type 'int'
     *  passing argument to parameter '__ptr' here
     */
    return final_result;
}

void free_split_result(char **split_result, int count) {
    for (int i = 0; i < count; i++) free(split_result[i]);
    free(split_result);
}

int main() {
    const char *input = "ExampleOfAStringWithUpperCases";
    int count = 0;
    char **split_result = split_at_uppercase(input, &count);
    if (split_result) {
        for (int i = 0; i < count; i++) {
            printf("%s\n", split_result[i]);
        }
        free_split_result(split_result, count);
    } else {
        fprintf(stderr, "Failed to split string.\n");
    }
    return 0;
}