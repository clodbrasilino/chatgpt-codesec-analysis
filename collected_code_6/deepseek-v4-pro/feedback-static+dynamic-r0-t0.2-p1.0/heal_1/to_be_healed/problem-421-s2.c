#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concat_tuple(char **tuple, size_t size, const char *delimiter) {
    if (tuple == NULL || delimiter == NULL) {
        return NULL;
    }

    size_t total_length = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t delim_length = strlen(delimiter);

    for (size_t i = 0; i < size; i++) {
        if (tuple[i] == NULL) {
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        total_length += strlen(tuple[i]);
        if (i < size - 1) {
            total_length += delim_length;
        }
    }

    char *result = (char *)malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    result[0] = '\0';

    for (size_t i = 0; i < size; i++) {
        /* Possible weaknesses found:
         * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
         */
        strcat(result, tuple[i]);
        if (i < size - 1) {
            /* Possible weaknesses found:
             * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
             */
            strcat(result, delimiter);
        }
    }

    return result;
}

int main(void) {
    char *tuple1[] = {"Hello", "World", "C"};
    char *tuple2[] = {"one", "two", "three", "four"};
    char *tuple3[] = {"single"};
    char *empty_tuple[] = {};

    char *result1 = concat_tuple(tuple1, 3, "-");
    char *result2 = concat_tuple(tuple2, 4, ", ");
    char *result3 = concat_tuple(tuple3, 1, "|");
    char *result4 = concat_tuple(empty_tuple, 0, ",");
    /* Possible weaknesses found:
     *  Assignment 'result5=concat_tuple(NULL,3,"-")', assigned value is 0
     *  Calling function 'concat_tuple' returns 0
     */
    char *result5 = concat_tuple(NULL, 3, "-");
    char *result6 = concat_tuple(tuple1, 3, NULL);

    if (result1 != NULL) {
        printf("%s\n", result1);
        free(result1);
    }

    if (result2 != NULL) {
        printf("%s\n", result2);
        free(result2);
    }

    if (result3 != NULL) {
        printf("%s\n", result3);
        free(result3);
    }

    if (result4 != NULL) {
        printf("%s\n", result4);
        free(result4);
    }

    /* Possible weaknesses found:
     *  Condition 'result5!=NULL' is always false
     *  Condition 'result5!=NULL' is always false [knownConditionTrueFalse]
     */
    if (result5 != NULL) {
        printf("%s\n", result5);
        free(result5);
    }

    if (result6 != NULL) {
        printf("%s\n", result6);
        free(result6);
    }

    return 0;
}