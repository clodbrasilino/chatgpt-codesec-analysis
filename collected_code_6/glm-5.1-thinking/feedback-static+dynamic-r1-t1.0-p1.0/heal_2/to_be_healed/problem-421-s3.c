#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Possible weaknesses found:
 *  expected 'const char * const*' but argument is of type 'char **'
 */
char *join_tuple(const char * const tuple[], size_t count, const char *delimiter) {
    if (tuple == NULL || delimiter == NULL || count == 0) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t delimiter_len = strlen(delimiter);
    size_t total_len = 1;

    for (size_t i = 0; i < count; i++) {
        if (tuple[i] == NULL) {
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        total_len += strlen(tuple[i]);
        if (i < count - 1) {
            total_len += delimiter_len;
        }
    }

    char *result = (char *)malloc(total_len);
    if (result == NULL) {
        return NULL;
    }

    char *ptr = result;
    size_t remaining = total_len;
    for (size_t i = 0; i < count; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t elem_len = strlen(tuple[i]);
        if (elem_len < remaining) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(ptr, tuple[i], elem_len);
            ptr += elem_len;
            remaining -= elem_len;
        } else {
            break;
        }
        if (i < count - 1) {
            if (delimiter_len < remaining) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(ptr, delimiter, delimiter_len);
                ptr += delimiter_len;
                remaining -= delimiter_len;
            } else {
                break;
            }
        }
    }
    *ptr = '\0';

    return result;
}

int main(void) {
    const char *tuple[] = {"apple", "banana", "cherry", "date"};
    size_t count = sizeof(tuple) / sizeof(tuple[0]);
    const char *delimiter = " | ";

    char *result = join_tuple(tuple, count, delimiter);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
        result = NULL;
    }

    const char *empty_tuple[] = {""};
    result = join_tuple(empty_tuple, 1, delimiter);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
        result = NULL;
    }

    char **null_tuple = NULL;
    /* Possible weaknesses found:
     *  Calling function 'join_tuple' returns 0
     *  Assignment 'result=join_tuple(null_tuple,count,delimiter)', assigned value is 0
     *  passing argument 1 of 'join_tuple' from incompatible pointer type [-Wincompatible-pointer-types]
     */
    result = join_tuple(null_tuple, count, delimiter);
    /* Possible weaknesses found:
     *  Condition 'result==NULL' is always true
     *  Condition 'result==NULL' is always true [knownConditionTrueFalse]
     */
    if (result == NULL) {
        printf("NULL input handled correctly\n");
    }

    return 0;
}